/***********************************************************************
 * Module:
 *    Week 12, Spell Check
 *    Brother Helfrich, CS 235
 * Author:
 *    <your name here>
 * Summary:
 *    This program will implement the spellCheck() function
 ************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include "spellCheck.h"
#include "hash.h"
#include "set.h"
#include <list>
#include <cctype>
using namespace std;

/*class SHash : public Hash <std::string>
{
public :
    SHash(int numBuckets) throw (const char * ) : Hash <std::string> (numBuckets) {}
    SHash(const SHash & rhs) throw (const char * ) : Hash <std::string> (rhs) {}

    int hash(const std::string & value)
    {
        int findItem = 0;
        for ( const char *word = value.c_str(); *word; word++ )
            findItem += *word;

        return findItem % size();
    }
};
*/

class SHash : public Hash <std::string>
{
public:
	SHash ( int numBuckets ) throw ( const char * ) : 
		Hash <string> ( numBuckets ) {}
	SHash ( const SHash & rhs ) throw ( const char * ) : 
		Hash <string> ( rhs ) {}

	// hash function for strings will add up all the ASCII values
	int hash ( const std::string & s ) const
	{
		int value = 0;

		for ( const char * p = s.c_str(); *p; p++ )
			value += *p;

		return value % capacity();
	}
};

/*****************************************
 * SPELL CHECK
 * Prompt the user for a file to spell-check
 ****************************************/
void spellCheck()
{
//    SHash<string> file;
    SHash dictionary(150);

//  	List <string> wrong;
  	Set<string> wrong;

    string fileName;

    cout << "What file do you want to check? ";
    cin >> fileName;

    ifstream fin;

    fin.open("/home/cs235/week12/dictionary.txt");
    if (fin.fail())
    	cerr << "Cannot find File";
    else
    {
		string data;
		while (fin >> data)
			dictionary.insert(data);

		fin.close();
    }

    fin.open(fileName.c_str());
    if (fin.fail())
    	std::cerr << "Error: File missing: " << fileName;
    else
    {
		string data;
		while (fin >> data)
		{
			string temp = data;
			temp[0] = tolower(temp[0]);
			if (!dictionary.find(temp))
				wrong.insert(data);
		}

		fin.close();
    }

	if (!wrong.empty())
	{
		cout << "Misspelled: ";
		SetIterator<string> it;
		for (it = wrong.begin(); it != wrong.end();)
		{
			cout << *it; 
			it++;
			if (it == wrong.end())
				break;
			else
				cout << ", ";
		}
		cout << endl;
	}
	else
	{
		cout << "File contains no spelling errors\n";
	}
}
