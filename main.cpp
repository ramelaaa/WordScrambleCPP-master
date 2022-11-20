/** @file main.cpp */
/** CSCI 235 */
/** Project 01*/
/** March 13, 2017*/

#include "NewData.h"
#include "WordScramble.h"
#include "Files.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype>
using namespace std;

int main(int argc, char *argv[])
{
	/** Instances of each class */
	NewData userInput;
	WordScramble Game;
	Files check;

	//variable declaraton;
	string user_guess;
	bool use_lifeline;
	bool result; //was user's guess correct or incorrect
	char how_to_start_game;
	bool does_new_file_exist = false;
	bool best_stats;


	if(argc > 2) // can only have at most two arguments, else will quit
	{
		cout << "To many arguemnts!!!" << endl;
		exit(1);
	}
	else if(argc == 2)// user entered a second argument
	{
		does_new_file_exist = userInput.does_file_exist(argv[1]);
		if(does_new_file_exist == true) //parse the data
		{
			userInput.load_data(argv[1]);
			userInput.remove_non_alpha_char();
			userInput.remove_duplictes();
			userInput.remove_words_less_then_length_three();
			userInput.update_file();
			Game.load_data(); // load the data, game will commence and go to do/while loop
		}
		else//invalid argument 
		{
		cout << "Your file doesn't not exist." << endl; 
		}
	}
	

	if(does_new_file_exist == false) // if bad command line argument(2)
	{
		//check for saved data from quitted game and previouslt parsed data
		bool saved_stats = check.check_if_file_exists("saved_stats.txt");
		bool saved_words = check.check_if_file_exists("saved_words.txt");
		bool prev_game = check.check_if_file_exists("words.txt");
		
		while(how_to_start_game != 's' && how_to_start_game != 'l' && how_to_start_game != 'q')
		{

			if (saved_stats == true && prev_game == true) //data can be used
			{
				cout << "Press S to play a previously saved game." << endl;
			}
			if(prev_game == true) // data can be used
			{
				cout << "Press L to play a previously loaded game." << endl;
			}
			//there is not input that can be used for the game. game is invalid
			if( saved_stats == false && prev_game == false && prev_game == false) 
			{
				exit(1);
			}
			cout << "Press Q to Quit" << endl;

			cin >> how_to_start_game;

			how_to_start_game = tolower(how_to_start_game);

			if(how_to_start_game  == 's') // game will used saved data
			{
				Game.load_saved_stats();
				Game.load_saved_data();
				
			}
			else if(how_to_start_game == 'l') // game will use previously parsed data
			{
				Game.load_data();
			}
			else if(how_to_start_game == 'q')
			{
				exit(1);
			}
			else
			{
				cout << "Sorry. Try Again." << endl;	
			}	
		}	
	}

	Game.organize_by_levels(); // organize words by level

	cout << endl;
	//display title of game and rules
	cout << "Welcome to Word Scramble!" << endl;
	cout << "You will see three words per level." << endl;
	cout << "You will have three attempts per word." << endl;
	cout << "On your last attempt, you can use one of your five lifelines" << endl;
	cout << "You can quit the game anytime by pressing q" << endl;
	cout << "Good Luck!" << endl;
	cout << endl;

	do
	{
		use_lifeline = false; //default to prevent infinite loop
		cout << "---------------------"<< endl;
		//if saved game has been resumed, do not change word, as the player need to answer the last
		//word they've seen
		if(Game.attempts == 0 && how_to_start_game != 's') 
		{
			Game.shuffle_level();
			Game.pick_word();
				
		}
		// change so that above if statement can used in future iteration of do/while loop
		how_to_start_game = 'a'; 

		//present game propress
		Game.present_current_game_board();

		//offer life line option
		if(Game.attempts == 2)
		{
			use_lifeline = Game.life_line();
			if(use_lifeline == true)
			{
				continue;
			}
		}

		//get user guess and evaluate
		cout << "Enter your answer: " << ends;
		cin >> user_guess;
		
		//user can quit the game before answering
		if(user_guess == "q" || user_guess == "Q")
		{
			Game.save_stats();
			Game.save_words();
			exit(1);
		}
		// true if answer was correct, false if answer was incorrect
		else 
		{
			result = Game.check_guess(user_guess);
		}
		

		if(result == true) 
		{
			cout << "Correct!" << endl;
			Game.attempts = 0; //reset attempts for new word chances
			Game.update(); // increment points, and level, if possible
		}
		else //user gave wrong answer
		{	
			Game.attempts++;

			//game will terminate
			if(Game.attempts == 3)
			{
				cout << "Sorry, you lose." << endl;
				exit(1);
			}
			else
			{
				cout << "Sorry, wrong answer." << endl;
				cout << "You have " << 3-Game.attempts << " attempt(s) left." << endl;
				cout << "Try again!"<< endl;
			}
		}	
	}while(Game.attempts<3);	

	

	return 0;
}