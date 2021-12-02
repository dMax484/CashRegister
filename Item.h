#include <string>
#include <iostream>
#include <fstream>

using namespace std;

#ifndef ITEM
#define ITEM

class Item {
public: //methods

  Item(); //constructor
  Item(double,double,double,string);//constructor to set inventory,price,name

  void setItemName(string);
  string getItemName();

  void setItemInventory(double);
  double getItemInventory();

  void setPriceOfItem(double);
  double getPriceOfItem();

  void setCustomerQuantity(double);
  double getCustomerQuantity();

  void setSoldCount(double);
  double getSoldCount();
  
  void printItem();

private: //data members

  string ItemName;   //holds item name
  double ItemInventory; //keeps track of how much of an item there is
  double PriceOfItem; //indicates the price of the item
  double CustomerQuantity; //indicateds number of item in customer's cart
  double SoldCount; //indicates number of items sold
};
#endif