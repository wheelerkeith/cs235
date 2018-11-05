/***********************************************************************
 * Header:
 *    NOW SERVING
 * Summary:
 *    This will contain just the prototype for nowServing(). You may
 *    want to put other class definitions here as well.
 * Author
 *    <your names here>
 ************************************************************************/

#ifndef NOW_SERVING_H
#define NOW_SERVING_H

#include "deque.h"     // for DEQUE
#include <string>

// the interactive nowServing program
void nowServing();

struct Request
{
	std::string student;
	std::string course;
	int minutes;
	bool urgent;

	Request() : minutes(0), urgent(false), student("\0"), course("\0") {}
};

#endif // NOW_SERVING_H

