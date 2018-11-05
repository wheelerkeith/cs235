/***********************************************************************
 * Implementation:
 *    STOCK
 * Summary:
 *    This will contain the implementation for stocksBuySell() as well
 *    as any other function or class implementation you need
 * Author
 *    <your names here>
 **********************************************************************/

#include <iostream>    // for ISTREAM, OSTREAM, CIN, and COUT
#include <string>      // for STRING
#include <cassert>     // for ASSERT
#include "stock.h"     // for STOCK_TRANSACTION
#include "queue.h"     // for QUEUE
#include <sstream>     // for SSTREAM
#include "dollars.h"   // for DOLLARS
#include <iomanip>     // for manipulating iostream
using namespace std;


/************************************************
 * STRUCT: STOCK
 * A struct for holding the price and amount of a
 *  a stock.
 ***********************************************/
struct Stock
{
  int amount;
  double value;
  Stock(): amount(0), value(0) {}
  Stock(int incAmount, double incValue): amount(incAmount), value (incValue) {}
};
/************************************************
 * STRUCT: SELLHISTORY
 * A struct for holding the amount, value sold at,
 *  and profit of a sold stock.
 ***********************************************/
struct SellHistory
{
  int amount;
  double value;
  double profit;
  SellHistory(): amount(0), value(0), profit(0) {}
  SellHistory(int incAmount, double incValue, double incProfit):
          amount(incAmount), value (incValue), profit(incProfit) {}
};

Stock parse(string choice);
void buy(Queue<Stock> & portfolio, string & choice);
void sell(Queue<Stock> & portfolio, Queue<SellHistory> & sel,  string & choice);
void display(Queue<SellHistory> sel, Queue<Stock> portfolio);

/************************************************
 * STOCKS BUY SELL
 * The interactive function allowing the user to
 * buy and sell stocks
 ***********************************************/
void stocksBuySell()
{
  Queue<Stock> portfolio;
  Queue<SellHistory> sel;
  string choice;

  cout << "This program will allow you to buy and sell stocks. "
       << "The actions are:\n";
  cout << "  buy 200 $1.57   - Buy 200 shares at $1.57\n";
  cout << "  sell 150 $2.15  - Sell 150 shares at $2.15\n";
  cout << "  display         - Display your current stock portfolio\n";
  cout << "  quit            - Display a final report and quit the program\n";

  //this will ignore the previous part of the program, clearing up cin.
  cin.ignore();

  //fancy way of doing infinite loop I HAVE to say 'break' to.
  for(;;)
  {
    cout << "> ";
    //getline gets the spaces
    getline(cin, choice);
    if (choice[0] == 'q')
    {
       break;
    }
    else if (choice[0] == 's')
    {
      sell(portfolio, sel, choice);
    }
    else if (choice[0] == 'b')
    {
      buy(portfolio, choice);
    }
    else if (choice[0] == 'd')
    {
      display(sel, portfolio);
    }
    else
    {
      cout << "Incorrect command\n";
    }
    //I prefer t = t() instead of "". Makes more sense to me.
    choice = string();
  }
}
/************************************************
 * PARSE
 * This function parses the string into portfolio
 *  values.
 ***********************************************/
 Stock parse(string choice)
{
  //this is so I can throw away part of the stringstream
  string garbage = string();
  int amount = 0;
  double price = 0;
  //streams in the whole line
  stringstream ss(choice);
  //throw away first word
  ss >> garbage;
  //toss in second
  ss >> amount;
  //third is tricky, have to remove $
  // so we use garbage to take it, then stream from that.
  garbage = string();
  ss >> garbage;
  //remove $
  if (garbage[0] == '$')
    garbage.erase(0, 1);
  stringstream ss1 (garbage);
  //now it fits in better
  ss1 >> price;
  Stock stock(amount,price);
  return stock;
}
/************************************************
 * BUY
 * This function adds to the portfolio
 ***********************************************/
void buy(Queue<Stock> & portfolio, string & choice)
{
    portfolio.push(parse(choice));
}
/************************************************
 * SELL
 * This function sells from the portfolio
 ***********************************************/
void sell(Queue<Stock> & portfolio, Queue<SellHistory> & sel,  string & choice)
{
  //sellstock keeps the data in order of what we're selling.
  Stock sellstock (parse(choice));
  double profit = 0;
  //incase we overflow
  int total = sellstock.amount;
  //current stocks being sold
  int current = 0;
  //a while statement is needed to handle overflow
  while (sellstock.amount != 0)
  {
    //if it's empty, means we're out of stocks to sell.
    if (portfolio.empty())
    {
      cout << "Insufficient stocks to sell, sold " << total - sellstock.amount <<"\n";
      break;
    }
    //this is to pop off stocks we no longer own, and keep going
    else if (sellstock.amount >= portfolio.front().amount)
    {
      current = portfolio.front().amount;
      profit = ((current * sellstock.value) - (current * portfolio.front().value));
      sellstock.amount -= portfolio.front().amount;
      SellHistory sellFile(portfolio.front().amount, sellstock.value, profit);
      sel.push(sellFile);
      portfolio.pop();
    }
    //or if we break off only a small portion of the stocks we're selling.
    else
    {
      current = portfolio.front().amount;
      profit = ((sellstock.amount * sellstock.value) - (sellstock.amount * portfolio.front().value));
      cout << profit << endl;
      SellHistory sellFile(sellstock.amount, sellstock.value, profit);
      sel.push(sellFile);
      portfolio.front().amount -= sellstock.amount;
      profit = 0;
      sellstock.amount = 0;
    }
  }
}
/************************************************
 * DISPLAY
 * This function displays the current set of stocks
 ***********************************************/
void display(Queue<SellHistory> sel, Queue<Stock> portfolio)
{
  //don't display stats for things that don't exist
  if (!portfolio.empty())
    cout << "Currently held:\n";
  //while statement will empty bin. This is passed by value, not reference
  while (!portfolio.empty())
  {
    //convert to display better
    Dollars pValue (portfolio.front().value);
    cout << "\tBought " << portfolio.front().amount
         << " shares at " << pValue<< endl;
    portfolio.pop();
  }
  //proceeds come from how much money you made at sell history... I think.
  double proceeds = 0;
  if (!sel.empty())
    cout << "Sell History:\n";
  while (!sel.empty())
  {
    Dollars value (sel.front().value);
    Dollars profit (sel.front().profit);
    cout << "\tSold " << sel.front().amount << " shares at ";
    cout << value << " for a profit of " << profit << endl;
    proceeds += sel.front().profit;
    sel.pop();
  }
  Dollars displayProceeds(proceeds);
  cout << "Proceeds: " << displayProceeds << endl;
}
