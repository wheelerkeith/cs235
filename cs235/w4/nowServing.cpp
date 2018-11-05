/***********************************************************************
 * Implementation:
 *    NOW SERVING
 * Summary:
 *    This will contain the implementation for nowServing() as well as any
 *    other function or class implementations you may need
 * Author
 *    <your names here>
 **********************************************************************/

#include <iostream>     // for ISTREAM, OSTREAM, CIN, and COUT
#include <string>       // for STRING
#include <sstream>
#include <cassert>      // for ASSERT
#include "nowServing.h" // for nowServing() prototype
#include "deque.h"      // for DEQUE
using namespace std;

/************************************************
 * NOW SERVING
 * The interactive function allowing the user to
 * handle help requests in the Linux lab
 ***********************************************/
void nowServing()
{
   // instructions
   cout << "Every prompt is one minute.  The following input is accepted:\n";
   cout << "\t<class> <name> <#minutes>    : a normal help request\n";
   cout << "\t!! <class> <name> <#minutes> : an emergency help request\n";
   cout << "\tnone                         : no new request this minute\n";
   cout << "\tfinished                     : end simulation\n";

   // your code here
   string input;
   Request current;
   Deque<Request> nowServing;
   int i = 0;

   for (;;)
   {
      cout << "<" << i++ << "> ";
      if (i == 1)
         cin.ignore();
      getline(cin, input);
      stringstream ss(input);
      
      if (input == "finished")
         break;
      
      if (input != "none")
      {
         Request request;
         
         if (input[0] == '!')
         {
            string urgent; // creates dummy value for !!
            request.urgent = true;
            ss >> urgent; // store !! so input stream moves on to course
         }
         
         ss >> request.course
            >> request.student
            >> request.minutes;
         
         if (request.urgent)
         {
            nowServing.push_front(request);
         }
         else
         {
            nowServing.push_back(request);
         }
      }
      
      if (!nowServing.empty() && current.minutes == 0)
      {
         current = nowServing.front();
         nowServing.pop_front();
      }
      
      if (current.minutes)
      {
         if (!current.urgent)
         {
            cout << "\tCurrently serving " << current.student << " for class "
                 << current.course << ". Time left: " << current.minutes << endl;
         }
         else
         {
            cout << "\tEmergency for " << current.student << " for class "
                 << current.course << ". Time left: " << current.minutes << endl;
         }
         
         current.minutes--;
      }
   }
   
   // end
   cout << "End of simulation\n";
}


