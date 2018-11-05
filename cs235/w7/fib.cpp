using namespace std;
#include <iostream>

main()
{
   int fib0 = 0;
   int fib1 = 1;
   int newfib = 0;

   for (int i = 2; i < 100; ++i)
   {
      newfib = fib0 + fib1;
      cout << "Fib #" << i << " = " << newfib << endl;
      fib0 = fib1;
      fib1 = newfib;
   }
}
