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
#include "dollars.h"
#include <vector>
#include <sstream>
#include <list>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ostream;
using std::ios;
using namespace custom;


/******************************************
 * DISPLAY
 * Display the contents of the queue
 ******************************************/
ostream & operator << (ostream & out, custom::queue <Dollars> q) 
{
   out << "{ ";
   while (!q.empty())
   {
      out << q.front() << ' ';
      q.pop();
   }
   out << '}';

   return out;
}

/************************************************
 * STOCKS BUY SELL
 * The interactive function allowing the user to
 * buy and sell stocks
 ***********************************************/
void stocksBuySell()
{
   // instructions
   cout << "This program will allow you to buy and sell stocks. "
        << "The actions are:\n";
   cout << "  buy 200 $1.57   - Buy 200 shares at $1.57\n";
   cout << "  sell 150 $2.15  - Sell 150 shares at $2.15\n";
   cout << "  display         - Display your current stock portfolio\n";
   cout << "  quit            - Display a final report and quit the program\n";

   // your code here...
   
   
   std::string str="buy 300 $1.57";
                                            
      try
   {
      string str;
      string firstWord;
      string str2;
      string secondWord;
      size_t pos;
      string thirdWord;
      string str3;
      Dollars price;
      int count = 0;
      
      int numStock = 0;

      
      queue <Dollars> stocksQ;
      queue <Dollars> stocksQ2;
      queue <int> numStocksQ;
      queue <int> numStocksQ2;
      list <int> numSell;
      list <Dollars> sellHistory;
      
      list <int> numSell2;
      list <Dollars> sellHistory2;
      
      Dollars proceeds = 0;

      
      cin.ignore();
      do
      {
        cout << "> ";
      
        cin >> firstWord;
          if (firstWord == "buy") //BUY
          {
            cin >> secondWord;
            cin >> thirdWord;
            if(thirdWord[0] == '$')
            {
              thirdWord = thirdWord.substr (1, 10);
              thirdWord = thirdWord.substr(0, str2.find(" "));
            }
            
            stringstream geek(secondWord);
            geek >> numStock;
            stringstream pGeek(thirdWord);
            pGeek >> price;
 
            stocksQ.push(price); //store value of stock

            numStocksQ.push(numStock);//store number of stock 
          }
          else if (firstWord == "sell") //SELL
          {
            cin >> secondWord; 
            cin >> thirdWord;
            if(thirdWord[0] == '$')
            {
              thirdWord = thirdWord.substr (1, 10);
              thirdWord = thirdWord.substr(0, str2.find(" "));
            }
            
            stringstream geek(secondWord);
            geek >> numStock;
            stringstream pGeek(thirdWord);
            pGeek >> price;
            
            while (numStock != 0)
            {
              if(numStock < numStocksQ.front()) //number sold < number bought at front of queue
              {
                numStocksQ.front() -= numStock; //subtract the number of stocks from front
                numSell.push_back(numStock);  //list: get number sold
                sellHistory.push_back(price); //list: get $ value of each
                sellHistory.push_back((price - stocksQ.front()) * numStock); //list: total profit
                count++;
                numStock = 0; //exit loop
              }
              if(numStock >= numStocksQ.front()) //number sold > number bought at front of queue
              {
                numSell.push_back(numStocksQ.front()); //list: get number sold
                sellHistory.push_back(price); //list: get
                sellHistory.push_back((price - stocksQ.front()) * numStocksQ.front());
                numStock -= numStocksQ.front();
                numStocksQ.pop();
                stocksQ.pop();
                count++;
              }
            }
          }
          else if (firstWord == "display") //DISPLAY
          {
            stocksQ2 = stocksQ;
            numStocksQ2 = numStocksQ;
            
            if (!stocksQ2.empty())
            {
              cout << "Currently held:\n";
              
              while (!stocksQ2.empty())
              {
                 cout << "\tBought " << numStocksQ2.front() << " shares at " << stocksQ2.front() << endl;
                 numStocksQ2.pop();
                 stocksQ2.pop(); 
              }          
              numStocksQ2.clear();
              stocksQ2.clear(); 
            }
                     
             
            if (!numSell.empty())
            {
              cout << "Sell History:\n";
              
              numSell2 = numSell;
              sellHistory2 = sellHistory;
              
              while (!numSell2.empty())
              {
                cout << "\tSold " << numSell2.front() << " shares at " << sellHistory2.front();
                sellHistory2.pop_front(); 
                cout << " for a profit of " << sellHistory2.front() << endl;
                proceeds += sellHistory2.front();
                sellHistory2.pop_front();
                numSell2.pop_front();
              }
              numStocksQ2.clear();
              stocksQ2.clear();
             }
             cout << "Proceeds: " << proceeds << endl; 
             proceeds = 0;
            }  
          }
      while (firstWord != "quit"); //QUIT

   }
   catch (const char * sError)
   {
      cout << sError << endl;
   }
   
}


