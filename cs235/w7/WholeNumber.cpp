#include "WholeNumber.h"

WholeNumber::WholeNumber(WholeNumber & num)
{
	this->num = num.num;
}

WholeNumber& WholeNumber::operator=(WholeNumber & rhs)
{
	this->num = rhs.num;
	return *this;
}

WholeNumber& WholeNumber::operator+=(WholeNumber & lhs, const WholeNumber & rhs)
{
	
}

WholeNumber WholeNumber::operator+(const WholeNumber & lhs, const WholeNumber & rhs)
{
	
}

ostream& WholeNumber::operator<<(ostream & out, WholeNumber & obj)
{
	ListIterator<int> it = obj.begin();
	if (obj.degree() > 1)
	{

	}
}
