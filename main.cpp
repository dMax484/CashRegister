//***************************************************************************
//Cash Register Object Program
//November 2021
//CPSC 246 Group 6: Douglas Maxwell, Luke McElligott, Oleksii Dukhovenko
//This programs simulates a CashRegister that keeps track of items in a store
// and allows users to buy items with coins/bills.
//***************************************************************************

#include <iostream>
#include <vector>
#include <string>

//Include header files
#ifndef CASHREGISTER
#include "CashRegister.h"
#endif
#ifndef COIN
#include "Coin.h"
#endif
#ifndef ITEM
#include "Item.h"
#endif

using namespace std;

int main(){

  string InputFile="ItemInput.txt", OutputFile="Report.txt"; //Option to change input file
  //Declare Cash Register Object
  CashRegister Register;
  Register.loadRegisterCoins();              //Only need to set coins at the beginning of the day.
  Register.setRegisterItems(InputFile);      //Stock store Items using input file

  do{
    Register.loadCustomerCoins();         //initialize customer coins
    Register.printRegisterItems();        //Print store Items for Customer to see
    Register.setCustomerItems();          //Ask the user for items they would like to purchase
    Register.printItemTotal();            //Print Total for Customer
    Register.setCustomerCoins();          //Ask User to enter Coins for payment
    Register.CalculateDifference();       //Calculate difference between customer coins and and item total
    Register.calculateReturnCoins();      //Calculate coins to give back to customer
    Register.printReciept();              //Print receipt
    Register.setProfit();                 //add to overall profit
  } while (Register.newCustomer());       //new customer? return t/f

  Register.giveReport(OutputFile); //send report to file.
  return 0;
}