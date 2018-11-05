/*******************************************************************
*
*  FILE: WholeNumber.h
*
*  PURPOSE: Contains the class definition of a Whole Number which
*           allows arithmetic with numbers of infinite length.
*
*******************************************************************/
#ifndef WHOLE_NUMBER
#define WHOLE_NUMBER

#include "list.h"
using std::ostream;

class WholeNumber
{
public:
	WholeNumber() : degree(0) { num.push_front(0); }
	WholeNumber(unsigned int number) { num.push_front(number); }
	WholeNumber(WholeNumber& num);

	WholeNumber& operator=(WholeNumber& rhs);
	WholeNumber& operator+=(WholeNumber& lhs, const WholeNumber& rhs);
	WholeNumber operator+(const WholeNumber& lhs, const WholeNumber& rhs);
	ostream& operator<<(ostream& out, WholeNumber& obj);

	ListIterator<int> begin() { return num.begin(); }
	int degree() { return num.size(); }
private:
	List<int> num;
};

#endif