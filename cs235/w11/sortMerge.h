/***********************************************************************
 * Module:
 *    Week 11, Sort Merge
 *    Brother Helfrich, CS 235
 * Author:
 *    Tyler Petersen
 * Summary:
 *    This program will implement the Merge Sort
 ************************************************************************/
#ifndef SORT_MERGE_H
#define SORT_MERGE_H


#include <list>
#include <vector>
#include <iomanip>
using namespace std;
template<class T>
void split (list<T> &list1,
            list<T> &list2,
            list<T> &list3);
template<class T>
void merge (list<T> &list1,
            list<T> &list2,
            list<T> &list3);
template<class T>
bool check (list<T> &list3);
/*************************************************************************
* This function sorts a linked list using a Natural Merge Sort.
* Input:  data -  linked list of data to be sorted.
* Output: data -  sorted linked list
**************************************************************************/
template<class T>
void sortMerge(T array[], int num)
{
  list<T> list1;
  list<T> list2;
  list<T> list3;
  for(int i = 0; i < num; i ++)
  {
    list3.push_back(array[i]);
  }

  cerr << endl;
  while (check(list3))
  {
    split(list1, list2, list3);
    merge(list1, list2, list3);
  }
  int i = 0;
  for(typename list<T>:: iterator it = list3.begin();
    it != list3.end(); ++it, i++)
  {
    array[i]=*it;
  }

}

template<class T>
void split (list<T> &list1,
            list<T> &list2,
            list<T> &list3)
{
  int whichList = 0;
  T temp1;
  T temp2;
  for(typename list<T>:: iterator it = list3.begin();
        it != list3.end(); )
  {
    temp1 = *it;
    if (list1.empty())
      list1.push_back(*it);
    if(++it == list3.end())
      break;
    temp2 = *it;
    if (temp2 < temp1)
    {
      whichList++;
    }
    if(whichList % 2 == 0)
    {
      list1.push_back(*it);
    }
    else
    {
      list2.push_back(*it);
    }
  }
  list3.clear();

}

template<class T>
void merge (list<T> &list1,
            list<T> &list2,
            list<T> &list3)
{
  int sizeLimit = list1.size() + list2.size();
  for(typename list<T>::iterator it1 = list1.begin(), it2 = list2.begin();list3.size() < sizeLimit;)
  {
    if(it1 == list1.end())
    {
      list3.push_back(*it2);
      it2++;
    }
    else if(it2 == list2.end())
    {
      list3.push_back(*it1);
      it1++;
    }
    else
    {
      if(*it1 <= *it2)
      {
        list3.push_back(*it1);
        it1++;
      }
      if (*it1 > *it2)
      {
        list3.push_back(*it2);
        it2++;
      }
    }
  }
  list1.clear();
  list2.clear();
  //cout << " \nList Three: \n";
  int counter = 0;

}

/**********************************************************************************/

template<class T>
bool check (list<T> &list3)
{
  T temp1;
  T temp2;
  bool truth = false;
  if (list3.empty())
    return false;
  for(typename list<T>:: iterator it = list3.begin();
        it != list3.end();)
  {
    temp1 = *it;
    if(++it == list3.end())
      break;
    temp2 = *it;
    if (temp2 < temp1)
    {
      truth = true;
    }
  }
  return truth;
}

#endif // SORT_MERGE_H
