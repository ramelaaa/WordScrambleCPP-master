/** @file WordScramble.cpp */

/** CSCI 235 */
/** Project 01*/
/** March 13, 2017*/

#include "WordScramble.h"

#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <iostream>
#include <cctype>
#include <ctime>

using namespace std;

WordScramble::WordScramble()
{
	//initialize variables
	attempts = 0;
	level = 1;
	lifeline = 5;
	points = 0;
}

void WordScramble::load_data()
{
	ifstream(myfile);
	myfile.open("words.txt");

	//store each line of the file into the vector raw_data
	while(!myfile.eof())
	{
		string temp;
		myfile >> temp;
		list_of_words.push_back(temp);
	}

	myfile.close();
}

void WordScramble::organize_by_levels()
{
	//words have be atleast length 3, at most 50...
	for(int i = 3; i<50; i++) 
	{
		vector<word_database> temp2; // hold info about words of same length
		word_database temp1; // hold info about indiviual word
		for(int j = 0; j<list_of_words.size(); j++) //picks word from vector
		{
			if(list_of_words[j].length() == i) //compare word to length
			{
				temp1.word = list_of_words[j]; // if word's length = length
				temp1.given_in_level_yet = false; // all will be like this to be used during the game
				temp2.push_back(temp1); // vector of all words of same length
			}	
		}
		if(temp2.size()>0)
		{
			the_levels.push_back(temp2); // 2d vector with each element containing words of the same length
		}
	}

	longest_word_size = the_levels[the_levels.size()-1][0].word.length();
	// needed to determine when/if player wins
}

void WordScramble::shuffle_level()
{
	srand(time(0));
	//vector of elements of the same length are shuffled
	random_shuffle(the_levels[level-1].begin(), the_levels[level-1].end());
}

void WordScramble::pick_word()
{
	for(int i = 0; i<the_levels[level-1].size(); i++)
	{
		//false meaing the user hasnt seen the word yet
		if(the_levels[level-1][i].given_in_level_yet == false) 
		{
			//assign variables
			current_word = the_levels[level-1][i].word;
			scrambled_word = the_levels[level-1][i].word;

			//update varible's information
			the_levels[level-1][i].given_in_level_yet = true;
			break;
		}
	}
	//shuffled scrambled_word, or else the word is just a copy of current word
	random_shuffle(scrambled_word.begin(), scrambled_word.end());
}

void WordScramble::present_current_game_board()
{
	//prints the following information
	cout << "Level: " << level << endl;
	cout << "Points: " << points << endl;
	cout << "Life Lines: " << lifeline << endl;
	cout << endl;
	cout << "Unscramble: " << scrambled_word << endl;
}

bool WordScramble::check_guess(string user_guess)
{
	//checks word
	if(user_guess == current_word)
	{
		return true; //word is correct
	}
	return false; // word is incorrect
}

bool WordScramble::life_line()
{
	// 0 lifelines means all where used
	if(lifeline>0)
	{
		char response;
		while(response != 'y' && response != 'n')
		{
			//offer user the choice to use a life line
			cout << "You only have one more chance left. Do you want to use a lifeline?(y/n)" << endl;
			cin >> response;
			response = tolower(response); // .....
			if(response == 'y') //pick a new word
			{
				shuffle_level(); // make choice random
				current_word = the_levels[level-1][0].word;
				scrambled_word = the_levels[level-1][0].word;

				//scrambled this to make it different from currect word
				random_shuffle(scrambled_word.begin(), scrambled_word.end());

				//update life-line
				lifeline--;
				return true;
			}
			else if(response == 'n') //choice not taken
			{
				return false;
			}
			else //bad input from user
			{
				cout << "Sorry, please enter your decision again." << endl;
				response = 'N';
			}
		}
	}
	else //lifelines = 0
	{
		cout << "Sorry, you have no more life lines!!!" << endl;	
	}
	return false;
}

void WordScramble::update()
{

	points++; //guess was correct


	// check is this is the last word of the last level
	if(current_word.length() == longest_word_size && points%3 == 0)
	{
		cout << "You win the game!!!" << endl;
		cout << "You scored " << points << " points!" << endl;
		exit(1);
	}
	else //increment level
	{
		if(points%3 == 0)
		{
			level++;
		}
	}
	
}

void WordScramble::save_stats()
{
	ofstream saved;
	saved.open("saved_stats.txt");

	//save information to file
	saved << level << endl;
	saved << lifeline << endl;
	saved << points << endl;
	saved << attempts << endl;
	saved << current_word << endl;
	saved << scrambled_word << endl;

	saved.close();
}

void WordScramble::save_words()
{
	ofstream saved_two;
	saved_two.open("saved_words.txt");

	//save information to file
	for(int i = 0; i<the_levels.size(); i++)
	{
		for(int j = 0; j<the_levels[i].size(); j++)
		{
			//false becuase the user did not see this word
			if(the_levels[i][j].given_in_level_yet == false)
			{
				saved_two << the_levels[i][j].word << endl;
			}
		}
	}

	saved_two.close();
}


void WordScramble::load_saved_data()
{
	ifstream(myfile);
	myfile.open("saved_words.txt");

	//store each line of the file into the vector raw_data
	while(!myfile.eof())
	{
		string temp;
		myfile >> temp;
		list_of_words.push_back(temp);
	}

	myfile.close();
}

void WordScramble::load_saved_stats()
{

	ifstream(stats_file);
	stats_file.open("saved_stats.txt");

	//hold information temporarily
	int loaded_level,loaded_lifeline,loaded_points, loaded_attempts;
	string game_word, scrambled_game_word;

	while(!stats_file.eof())
	{
		//read all the values, each written on different line
		stats_file >> loaded_level >> loaded_lifeline >> loaded_points >> loaded_attempts >> game_word >> scrambled_game_word;
	}

	//assign temporary variables to corresponding variable
	level = loaded_level;
	lifeline = loaded_lifeline;
	points = loaded_points;
	attempts = loaded_attempts;
    current_word = game_word;
	scrambled_word = scrambled_game_word;

}
