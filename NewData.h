/** @file NewData.h */

/** CSCI 235 */
/** Project 01*/
/** March 13, 2017*/

#ifndef NewData_h
#define NewData_h

#include <vector>
#include <string>
using namespace std;

/** The purpose of this class is to parse new data entered from text file(command line argument) */

class NewData 
{
public:

	/**
	The function checks is the command line argument text file is 
	in the present directory. This is essesntial to all remaining functions 
	in the class.
	@param: command line argument argv[1] passed as a pointer
	@return: true if file is in directy, false if not
	*/
	bool does_file_exist(char* checkFile);

	/**
	This function will take command line arugemnt file and
	push each line into string vector named raw_data;
	@param: .txt file with list of words,from command line
	@post: each line in the file will be stored into vector
	*/
	void load_data(char* newfile);

	/**
	This function will check each character in a word to erase and non
	alphabetic characters. At the same time, the character will be 
	converted to lowercase. The data will be entered to list_of_words 
	vector if and only if the length of the remaining is three or more
	@pre: vector raw_data is filled
	@post: vector list_of words will be filled with correct data format.
	*/
	void remove_non_alpha_char();

	/**
	This function remove duplcate words in vector list of words
	@pre: words in list_of_words are in correct format
	@post: any duplicate words are removed.
	*/
	void remove_duplictes();

	/**
	This function remove any occurence words length occurrences that are 
	less than three. 
	@pre: vector list_of_words is in correct format and contains no duplicates
	@post: words length occurrenes less than 2 are removed
	*/
	void remove_words_less_then_length_three();

	/**
	This file will write to a .txt file words from list_of_words
	so that this information can be used for futre use.
	@pre: list_of_words vector is filled
	@post: a file will be created of updated with words from list_of_words
	*/
	void update_file();

private:
	//holds unparsed data;
	vector<string> raw_data;

	//hold data as it gets parsed
	//this is the final product of the class
	// will be written to a file when fully parsed for errors
	vector<string> list_of_words;
};

#endif