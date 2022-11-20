/**@file Files.h */

/** CSCI 235 */
/** Project 01*/
/** March 13, 2017*/

#ifndef FILES_h
#define FILES_h

#include <string>
#include <cstring>
#include <fstream>
using namespace std;


/** The purpose of the class is to determine whether text files
 are in the present directory. */
class Files
{

public:

	/**
	This function will determine if a file is valid in the directory 
	can can be used in the program
	@param: filename given as astring
	@return: true if file is in directory, false if not.
	*/
	bool check_if_file_exists(string filename);
};

#endif
