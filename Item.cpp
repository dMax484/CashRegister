#ifndef ITEM
#include "Item.h"
#endif

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

Item :: Item(){
  ItemName="NULL";
  PriceOfItem=0.0;
  ItemInventory=0.0;
  CustomerQuantity=0.0;
  SoldCount=0.0;
}
Item :: Item(double ItemInventory,double PriceOfItem,double SoldCount,string ItemName){
  setItemInventory(ItemInventory);
  setPriceOfItem(PriceOfItem);
  setItemName(ItemName);
  setSoldCount(SoldCount);
}

void Item :: setItemName(string ItemName){
  this->ItemName=ItemName;
}
string Item :: getItemName(){
  return ItemName;
}
void Item :: setItemInventory(double ItemInventory){
  this->ItemInventory=ItemInventory;
}
double Item :: getItemInventory(){
  return this->ItemInventory;
}
void Item :: setPriceOfItem(double PriceOfItem){
  this->PriceOfItem=PriceOfItem;
}
double Item :: getPriceOfItem(){
  return this->PriceOfItem;
}

void Item :: setCustomerQuantity(double CustomerQuantity){
  this->CustomerQuantity=CustomerQuantity;
}

double Item :: getCustomerQuantity(){
  return this->CustomerQuantity;
}

void Item :: setSoldCount(double SoldCount){
  this->SoldCount=SoldCount;
}

double Item :: getSoldCount(){
  return this->SoldCount;
}

void Item :: printItem(){
  cout<<"| ";
  cout<<left<<setw(15)<<setfill(' ')<<ItemInventory;
  cout<<setw(25)<<setfill(' ')<<ItemName;
  cout<<setw(1)<<setfill(' ')<<'$';
  cout<<setw(5)<<PriceOfItem<<setw(3)<<right<<'|'<<endl;
}