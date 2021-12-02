#ifndef COIN
#include "Coin.h"
#endif

#include <string>
#include <iostream>
using namespace std;

//fallback
Coin :: Coin(){
  CoinValue=0.00;
  CoinName="NULL";
  RegisterCount=0;
  CustomerCount=0;
}

//CONSTRUTOR
Coin :: Coin(string name, double value, double regcount){
  this->CoinValue=value;
  this->CoinName=name;
  this->RegisterCount=regcount;
}

Coin :: Coin(string name, double value, double regcount, double custcount, double retcount){
  this->CoinValue=value;
  this->CoinName=name;
  this->RegisterCount=regcount;
  this->CustomerCount=custcount;
  this->ReturnCount=retcount;
}

void Coin :: setCoinValue(double CoinValue){
  this->CoinValue=CoinValue;
}
double Coin :: getCoinValue(){
  return CoinValue;
}

void Coin :: setCoinName(string name){
  this->CoinName=name;
}
string Coin :: getCoinName(){
  return CoinName;
}

void Coin :: setRegisterCount(double RegisterCount){
  this->RegisterCount=RegisterCount;
}
double Coin :: getRegisterCount(){
  return RegisterCount;
}

void Coin :: setCustomerCount(double CustomerCount){
  this->CustomerCount=CustomerCount;
}
double Coin :: getCustomerCount(){
  return CustomerCount;
}

void Coin :: setReturnCount(double ReturnCount){
  this->ReturnCount=ReturnCount;
}
double Coin :: getReturnCount(){
  return ReturnCount;
}