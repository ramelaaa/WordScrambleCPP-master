/**@file Files.cpp */

/** CSCI 235 */
/** Project 01*/
/** March 13, 2017*/


#include "Files.h"

#include <fstream>
#include <string>
#include <cstring>
using namespace std;

/**
This function will determine if a file is valid in the directory can can be used in the program
@param: filename given as astring
@return: true if file is in directory, false if not.
*/
bool Files::check_if_file_exists(string filename)
{
	ifstream myfile(filename);

	if(myfile) // is present
	{
		return true;
	}
	else // is not present
	{
		return false;
	}
}