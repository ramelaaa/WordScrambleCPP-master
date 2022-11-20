/** @file NewData.cpp */

/** CSCI 235 */
/** Project 01*/
/** March 13, 2017*/

#include "NewData.h"

#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <cctype>
#include <algorithm>

using namespace std;

/**
The function checks is the command line argument text file is 
in the present directory. This is essesntial to all remaining functions 
in the class.
@param: command line argument argv[1] passed as a pointer
@return: true if file is in directy, false if not
*/
bool NewData::does_file_exist(char* checkFile)
{
	ifstream is_file_there(checkFile);
	if(is_file_there.good())
	{
		return true;
	}
	else
	{
		return false;
	}
	//return is_file_there;
}

/**
This function will take command line arugemnt file and
push each line into string vector named raw_data;
@param: .txt file with list of words,from command line
@post: each line in the file will be stored into vector
*/

void NewData::load_data(char* newfile)
{
	ifstream wordfile(newfile);

	while(!wordfile.eof())
	{
		string line;
		getline(wordfile, line);
		line.erase(line.find_last_not_of(" \n\r\t")+1);
		raw_data.push_back(line);
		line.clear();
	}
}

/**
This function will check each character in a word to erase and non
alphabetic characters. At the same time, the character will be 
converted to lowercase. The data will be entered to list_of_words 
vector if and only if the length of the remaining is three or more
@pre: vector raw_data is filled
@post: vector list_of words will be filled with correct data format.
*/
void NewData::remove_non_alpha_char()
{
	string temp = ""; //empty string to hold correct characters for words
	string line;
	for(int j = 0; j<raw_data.size(); j++) // chooses an element from raw_data //rawdata
	{
		line = raw_data[j]; //holds element from the vector
		for(int i = 0; i<line.length(); i++) // chooses individual element from string
		{
			if(isalpha(line[i]) && i+1 == line.length())
			{
				temp += line[i];
				if(temp.length()>2)
				{
					list_of_words.push_back(temp);	
				}
				temp.clear();
			}
			else if(isalpha(line[i])) 
			{
				line[i] = tolower(line[i]);
				temp += line[i]; //appends character to temp
			}
			else
			{
				if(temp.length()>2) // word is of correct size
				{
					list_of_words.push_back(temp);
					//cout << temp << endl;
				}
				temp.clear();
			}
		}
	}
}

/**
This function remove duplcate words in vector list of words
@pre: words in list_of_words are in correct format
@post: any duplicate words are removed.
*/

void NewData::remove_duplictes()
{
	//any duplcate words will be removed 
	sort(list_of_words.begin(), list_of_words.end());
	for(int i = 0; i<list_of_words.size()-1; i++)
	{
		if(list_of_words[i] == list_of_words[i+1])
		{
			list_of_words.erase(list_of_words.begin()+i);
		}
	}
}

/**
This function remove any occurence words length occurrences that are 
less than three. 
@pre: vector list_of_words is in correct format and contains no duplicates
@post: words length occurrenes less than 2 are removed
*/
void NewData::remove_words_less_then_length_three()
{
	vector<int> word_lengths; // hold length of each word in list_of_words
	vector<int> words_to_cut; // words of this length must be removed

	//obtain the length of each word and push into vector
	for(int i = 0; i<list_of_words.size(); i++) 
	{
		word_lengths.push_back(list_of_words[i].length());
	}

	//sort the lengths
	sort(word_lengths.begin(),word_lengths.end());

	//**********  compare lengths to one another
	int counter = 1;
	for(int i = 0; i<word_lengths.size(); i++)
	{
		if(word_lengths[i] == word_lengths[i+1])
		{
			counter ++;
		}
		else
		{
			if(counter < 3)
			{
				words_to_cut.push_back(word_lengths[i]);
			}
			counter = 1;
		}
	}
	
	//remove the words whose lengths do not occure at least three times
	for(int i = 0; i<words_to_cut.size(); i++) // pick a length to cut
	{
		// pick a words from list_of_words
		for(int j = 0; j< list_of_words.size(); j++) 
		{
			//if true, the element in list_of_words is erased
			if(words_to_cut[i] == list_of_words[j].length())
			{
				list_of_words.erase(list_of_words.begin()+j);
			}
		}
	}
}

/**
This file will write to a .txt file words from list_of_words
so that this information can be used for futre use.
@pre: list_of_words vector is filled
@post: a file will be created of updated with words from list_of_words
*/

void NewData::update_file()
{
	ofstream myfile;
	myfile.open("words.txt");
	
	//each word will be written to file
	for(int i = 0; i<list_of_words.size(); i++)
	{
		myfile << list_of_words[i] << endl;
	}
	myfile.close();
}
