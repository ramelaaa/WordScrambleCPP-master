/** @file WordScramble.h */

/** CSCI 235 */
/** Project 01*/
/** March 13, 2017*/

#ifndef WordScramble_h
#define WordScramble_h

#include <fstream>
#include <vector>
#include <string>
using namespace std;

/** These functions related to the actual game data and game play*/

class WordScramble
{
	public:

	//Constructor to initialize level,points, and lifeline in private below
	WordScramble();

	//public varible to determine whether to end game or not in the main
	int attempts;

	/**
	This function will open the file in the directory.
	This file will not contain duplicates, non alphabetic characters,
	words less than length 3, and three words of each word length.
	This the data from thie file will be stored directly into a vector
	named list_of_words.
	@pre: .txt file is in directory
	@post: data will be stored into file
	*/
	void load_data();

	/**
	This function will organize words by level based in the length
	@param: none
	@pre: data structure is created, list_of_words is filled
	@post: words of the same length is will conatained separatly in 2d vector
	*/
	void organize_by_levels();

	// format to store data in vector
	struct word_database
	{
		string word;
		bool given_in_level_yet;
	};

	/**
	This function shuffle to current level in the game to keep the flow of words random.
	@pre: vector is full
	@post: vector is in a different order than it was before
	*/
	void shuffle_level();

	/**
	This function picks a word to display to the user
	The function grabs a word from the current level. The original word is stored in the private 
	section of the class with variable name current_word. A copy of the word is make to scrambled_word 
	variable and is then shuffled. It is this shuffled word that is presented to the user.
	@pre: level is shuffled and vector is filled
	@post: current_word and scrambled_word has a new value, but are not equal to one another
	*/
	void pick_word();

	/**
	This function contains cout statments that tell the user the number of
	points and lifelines they have and what level their are on. This function
	also present the scrambled_word variable
	@pre: variable in private section have value
	@post: varble values are printed, except currect_word(answer) 
	*/
	void present_current_game_board();

	/**
	This functio compares the user's guess to the answer and return a bool to 
	determine how to continue the game. It does this by determining os the two strings 
	are equal.
	@pre: current_word has a value, user entered a string anser
	@return: true if strings match, false if not
	*/
	bool check_guess(string user_guess);

	/**
	This function determines wheter a lifeline can be used.
	If so, the current_word and scrambled_word is changed. This is differenct
	from the above function as the bool value associated with word is not considered
	in the word's eligibility to be used.
	@pre: lifelines is greater in zero, attempts is equal to 2
	@post: if a lifeline can be used, a new word is chosen, is not, word doesnt change.
	@return: true if word can be swapped, false if not
	*/
	bool life_line();

	/**
	This function updates the level and points if the user guess the correct word.
	A correct guess increments the word by one.
	A three correct guesses increments the level.
	@pre: values in private are intialized
	@post: values are updated to reflect status of the game
	*/
	void update(); 

	/**
	This function saved unused words that the user has not seen when they quit the game
	These words are written to a file saved_stats.txt. 
	The words that ware written are determined by their bool variable associated in the struct. 
	If the value is false, the words get written
	@pre: vector is populated, user has quit the game
	@post: words not seen in the game are written to a file
	*/
	void save_words();

	/**
	This function saves the variables, level, lifeline, points, current_word, scrambled_word
	and attempts to a file. This is done when the user quits the game. The information 
	is written to file named saved_stats.txt.
	@pre: vector is full, user quits the game
	@post: file is written to with the variable values
	*/
	void save_stats();

	/**
	This function reads the file saved_words.txt and populated the vector with them.
	This is done when the player wanted to continue a saved game.
	These values are read and used in the variable in the private section below
	@pre: file is there, user want to coninut saved game
	@post: game is restored with the read value that are saved in private section below

	*/
	void load_saved_data();

	/**
	This function reads the file saved_words.txt. This data is used to fill the vector to
	be used in the game. This will comence when the user continues a saved game. The file 
	being read is a subset of the words.txt file.
	@pre: file is there, user wants to play saved game
	@post: vector is populated with words in this file only
	*/
	void load_saved_stats();

	
	private:
	//game data
		vector<string> list_of_words;
		vector< vector< word_database> > the_levels;
		int longest_word_size;

	//user and game information
		int level; 
		int lifeline;
		int points; 
		string current_word;
		string scrambled_word;
	
};

#endif