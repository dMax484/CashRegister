#ifndef COIN
#define COIN

#include <vector>
#include <string>
using namespace std;

class Coin {
public: //methods

  Coin();

  //Constructor used to build coin name, value, and count in the register (ex. penny("penny",0.01,50))
  Coin(string name, double value, double count);
  //Constructor for Customer Coins
  Coin(string name, double value, double regcount, double custcount, double retcount);
  
  void setCoinValue(double);
  double getCoinValue();
  
  void setCoinName(string name);
  string getCoinName();

  void setRegisterCount(double);
  double getRegisterCount();
  
  void setCustomerCount(double);
  double getCustomerCount();

  void setReturnCount(double);
  double getReturnCount();

private: //data members
  
  double CoinValue; //ex .01
  string CoinName; //ex "penny"
  
  double RegisterCount; 
  double CustomerCount;
  double ReturnCount;

};

#endif