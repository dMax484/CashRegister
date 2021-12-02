#include <vector>

#include "Item.h"
#include "Coin.h"

#ifndef CASHREGISTER
#define CASHREGISTER

using namespace std;

//TO DO: change customer coins and register coins to a vector of type COIN 

class CashRegister{
public: //methods
  //initialze how much the register has
  CashRegister();
  
  void loadRegisterCoins();
  void loadCustomerCoins();

  void setRegisterItems(string);
  void printRegisterItems();

  void setCustomerItems();

  void calculateItemTotal();
  void printItemTotal();

  //enter the users payment
  void setCustomerCoins();

  void calculateCustomerTotal();
  void printCustomerTotal();

  //calculates the change by finding difference between total and amount paid
  void CalculateDifference();

  void setReturningDifference();

  //determine the coins that need sent back to the customer
  void calculateReturnCoins();

  //receipt
  void printReciept();

  //Profit
  void setProfit();

  //set up register for new customer, return True if new customer
  bool newCustomer();

  void giveReport(string);
  
private: //cash register's data members
  vector <Coin> RegisterCoins;//the coins the register currently has
  vector <Coin> CustomerCoins; //the coins the customer is giving
  vector <Coin> ReturnCoins; //the coins being returned after purchase
  vector <Item> CustomerItems; //the items the customer is buying
  vector <Item> RegisterItems; //The items available in the store
  double ItemTotal; //Total for items in Customer's Cart
  double CustomerTotal; //Total value of coins entered
  double Difference; //holds the change the customer should get
  double ReturningDifference; //Hold coins coming back to Customer
  double Profit; //holds total profit for the day
  int NumberOfCustomers; //holds num of customers for the day
};

#endif