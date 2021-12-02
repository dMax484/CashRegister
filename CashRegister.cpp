#ifndef CASHREGISTER
#include "CashRegister.h"
#endif

#include "Item.h"
#include "Coin.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>
using namespace std;

//constants
const double MaxPurchaseAmount = 120.00;
const int n=8; //number of types of Coins/Bills
const double Values [n] = {0.01,0.05,0.10,0.25,1.00,5.00,10.00,20.00}; //face value of each coin
const string CoinNames [n] = {"penny","nickel","dime","quarter","dollar","five","ten","twenty"};
const int RegisterCount [n] = {50,40,50,40,10,10,10,0}; //initial number of each coin available in Register

//Construct Register
CashRegister :: CashRegister(){
  //declare starting Coins
  NumberOfCustomers=0;
  Profit=0.0;
  ItemTotal=0.0;
  CustomerTotal=0.0;
  Difference=0.0;
  ReturningDifference=0.0; //initialize all amounts to 0
}

void CashRegister :: loadRegisterCoins(){
  for (int i=0;i<n;i++){
    Coin registerCoin(CoinNames[i],Values[i],RegisterCount[i]);
    RegisterCoins.push_back(registerCoin);
  }
}

void CashRegister :: loadCustomerCoins(){
  for (int i=0;i<n;i++){
    Coin customerCoin(CoinNames[i],Values[i],0,0,0);
    CustomerCoins.push_back(customerCoin);
  }
}

//stock Items from file
void CashRegister :: setRegisterItems(string InputFile){
  ifstream ItemInputFile;
  int q;
  double p;
  string n;           
  ItemInputFile.open(InputFile);
  if (ItemInputFile.is_open()) {
    while (ItemInputFile.good()){
      ItemInputFile >> q >> p >> n;
      Item item(q,p,0.0,n);
      RegisterItems.push_back(item);
    }
  }
  ItemInputFile.close();
}

//print Items in store, items are updated when items are purchased
void CashRegister :: printRegisterItems(){
  cout<<endl<<endl;
  cout<<"|-------------------------------------------------|"<<endl;
  cout<<left<<setw(17)<<setfill(' ')<<"| QUANTITY";
  cout<<left<<setw(25)<<setfill(' ')<<"ITEM";
  cout<<left<<setw(14)<<setfill(' ')<<"PRICE   |"<<endl;
  cout<<"|-------------------------------------------------|"<<endl;
  for (int i=0;i<RegisterItems.size();i++){ //luke: try to use something like this for the reciept
    RegisterItems.at(i).printItem();
  }
  cout<<"|-------------------------------------------------|"<<endl;
}

//Customer puts items in their "cart"
void CashRegister :: setCustomerItems(){
  cout<<endl<<"Please enter the items you would like to purchase:"<<endl;
  cout<<"(Enter \'S\' to stop)"<<endl<<endl;
  
  double CustomerItemCount=1;
  string ItemInput;
  double ItemCountInput;

  do{

    string ItemInput;
    cout<<"Item "<<CustomerItemCount<<": ";
    cin>>ItemInput;
    if(ItemInput == "S" || ItemInput == "s"){
      break;
    }
    bool flag=false;
    int ItemTracker=0;
    for(int i=0;i<(RegisterItems.size());i++){ 
      if (ItemInput == RegisterItems.at(i).getItemName()){
        CustomerItems.push_back(RegisterItems.at(i));
        CustomerItems.at(CustomerItemCount-1).setItemName(ItemInput);
        CustomerItems.at(CustomerItemCount-1).setCustomerQuantity(0.0);
        flag=true;
        ItemTracker=i;
      }
    }
    if (!flag){
      cout<<ItemInput<<" is an invalid item, please try again"<<endl;
      continue;
    }

    bool ItemCountFlag=false;
    do{
      cout<<"Please enter the number of "<<ItemInput<<" you would like to purchase: ";
      cin>>ItemCountInput;
      cout<<endl;
  
      double tempCompare=RegisterItems.at(ItemTracker).getItemInventory();
      calculateItemTotal();
      double tempTotal=0.0;
      tempTotal=(ItemTotal+(RegisterItems.at(ItemTracker).getPriceOfItem() * ItemCountInput));
      if (ItemCountInput <= tempCompare && ItemCountInput >= 0 && (tempTotal<MaxPurchaseAmount)){
            CustomerItems.at(CustomerItemCount-1).setCustomerQuantity(ItemCountInput); //set number of specific item customer is buying
            RegisterItems.at(ItemTracker).setItemInventory(RegisterItems.at(ItemTracker).getItemInventory()-ItemCountInput); //subtract
            CustomerItems.at(CustomerItemCount-1).setPriceOfItem(RegisterItems.at(ItemTracker).getPriceOfItem());
            RegisterItems.at(ItemTracker).setSoldCount(RegisterItems.at(ItemTracker).getSoldCount()+ItemCountInput); //add to sold count
            ItemCountFlag=true;
      }
      else if(tempTotal>=MaxPurchaseAmount){
        cout<<endl<<"You are buying too mamy items. Current total: "<<ItemTotal<<endl;
        cout<<"Please enter an appropriate number of "<<ItemInput<<endl;
      }
      else{
        cout<<"Please enter a valid number of "<<ItemInput<<endl;
      }
    } while (!ItemCountFlag);

    CustomerItemCount++;
    calculateItemTotal();

  } while (ItemInput != "S" && ItemInput != "s" && ItemTotal<MaxPurchaseAmount);
  return;
}

//calculate total for items in cart
void CashRegister :: calculateItemTotal(){
  ItemTotal=0.0;
  for (int i=0;i<CustomerItems.size();i++){
    ItemTotal += (CustomerItems.at(i).getPriceOfItem() * (CustomerItems.at(i).getCustomerQuantity())); //total = total+(item*quanity)
  }
}

//print total for items in cart
void CashRegister :: printItemTotal(){
  calculateItemTotal();
  cout<<endl<<"The total is: $"<<ItemTotal<<endl<<endl;
}

//enter the users payment
void CashRegister :: setCustomerCoins(){
  cout<<"Please enter your payment: "<<endl;
  for (int i=0;i<n;i++){
    bool flag=false;
    do{
      int CustomerCount;
      cout<<"Number of "<<CoinNames[i]<<"(s):  ";
      cin>>CustomerCount;
      if (CustomerCount >= 0){
        CustomerCoins.at(i).setCustomerCount(CustomerCount); //add coin to customer count
        RegisterCoins.at(i).setRegisterCount(RegisterCoins.at(i).getRegisterCount() + CustomerCount); //add coin to register
        RegisterCoins.at(i).setReturnCount(0.0);
        flag=true;
      }
      else{
        cout<<"Please re-enter a valid amount"<<endl;
      }
    } while (!flag);
  }
  calculateCustomerTotal();
  printCustomerTotal();
}

//calculate the amount customer entered
void CashRegister :: calculateCustomerTotal(){
  CustomerTotal=0.0;
  for (int i=0;i<CustomerCoins.size();i++){
    //cout<<CustomerTotal<<" + ("<<CustomerCoins.at(i).getCoinValue()<<" * "<<CustomerCoins.at(i).getCustomerCount()<<endl;
    CustomerTotal += (CustomerCoins.at(i).getCoinValue() * CustomerCoins.at(i).getCustomerCount()); //total = total+(coin*quanity)
  }
}

//print the total that customer entered
void CashRegister :: printCustomerTotal(){
  calculateCustomerTotal();
  cout<<endl<<"ENTERED TOTAL: $"<<CustomerTotal<<endl<<endl;
}

//calculates the change by finding difference between total and amount paid. checks if user entered enough
void CashRegister :: CalculateDifference(){
  calculateItemTotal(); //gets the amount the customer should pay
  calculateCustomerTotal();
  Difference = 0.0;
  Difference = CustomerTotal - ItemTotal;
  while (Difference < 0.0){ //check if enough money was entered
    cout<<"You did not give enough money."<<endl;
    setCustomerCoins();                         //ask to enter new set of coins
    Difference = CustomerTotal - ItemTotal;
  }
  cout << "CASH BACK: $" << Difference << endl<<endl;
}

//difference used for returning coins
void CashRegister :: setReturningDifference(){
  ReturningDifference=0.0;
  for (int i=0;i<CustomerCoins.size();i++){
    ReturningDifference += (CustomerCoins.at(i).getCoinValue() * CustomerCoins.at(i).getReturnCount()); //total = total+(coin*quanity)
  }
}

//calculate cashback using loop to return most apporpriate coin to customer
void CashRegister :: calculateReturnCoins(){

  double tempDifference=Difference-ReturningDifference;
  do{
    for(int i=(n-1);i>=0;i--){
      if (tempDifference>=RegisterCoins.at(i).getCoinValue() && RegisterCoins.at(i).getRegisterCount() > 0){ //check if coin is available to give away
        CustomerCoins.at(i).setReturnCount(CustomerCoins.at(i).getReturnCount() + 1); //give coin to return count
        RegisterCoins.at(i).setRegisterCount(RegisterCoins.at(i).getRegisterCount() - 1); //take coin away from register
        CustomerCoins.at(i).setCustomerCount(CustomerCoins.at(i).getCustomerCount() + 1); //give coin to customer
        break;
      }
      else if (tempDifference > 0.001 && tempDifference <= 0.01){ //included to give extra penny for random error
      CustomerCoins.at(0).setReturnCount(CustomerCoins.at(0).getReturnCount() + 1); 
      RegisterCoins.at(0).setRegisterCount(RegisterCoins.at(0).getRegisterCount() - 1); 
      CustomerCoins.at(0).setCustomerCount(CustomerCoins.at(0).getCustomerCount() + 1);
      break;
      }
    }
    
    setReturningDifference();
    tempDifference=Difference-ReturningDifference;
    //cout<<tempDifference<<endl;
  } while (tempDifference > 0.001); //very small number. tempDifference does not come out to exactly 0 all the time
}

//receipt
void CashRegister :: printReciept(){

  char userRecieptInput;
  cout<< "Would you like your reciept? (y/n)"<<endl;
  cin>>userRecieptInput;
  if(userRecieptInput=='y' || userRecieptInput=='Y')
    cout<<"here you go: "<<endl<<endl;
  else{
    cout<<"Please come again!";
    return;
  }
  
  cout <<left<< "|-----------------------------------------------|" << endl;
  cout<<setw(48)<<'|';
  cout<<'|'<<endl;
  cout << "|                    Reciept                    |" << endl;
  cout<<setw(48)<<'|';
  cout<<'|'<<endl;
  cout << "|-----------------------------------------------|" << endl;
  
  //loop to gather information on what was purchased
  for (int i = 0; i < CustomerItems.size(); i++){
    // quantity   name   price
    cout<<'|';
    cout<<setw(32)<<setfill(' ')<<CustomerItems.at(i).getItemName();
    cout<<setw(5)<<setfill(' ')<<CustomerItems.at(i).getCustomerQuantity()<<"x   $";
    cout<<setw(5)<<setfill(' ')<<CustomerItems.at(i).getPriceOfItem()<<'|'<<endl;
  }
  cout<<setw(48)<<'|';
  cout<<'|'<<endl;

  // runs functions where the variables are needed
  calculateItemTotal();

  cout << "|-----------------------------------------------|" << endl;

  // get the total
  cout <<'|'<< setw(40)<< setfill(' ') << "TOTAL: " <<'$' <<setw(6)<< ItemTotal << '|'<<endl;
    
  // get how much the customer paid
  cout <<'|'<< setw(40)<< setfill(' ') << "CUSTOMER PAID: " << '$' <<setw(6)<< CustomerTotal << '|'<< endl;

  // get the change the user should recieve
  cout <<'|'<< setw(40)<< setfill(' ') << "CHANGE: " << '$' <<setw(6)<< Difference << '|'<< endl;
  cout << "|-----------------------------------------------|" << endl;
  cout <<'|'<< setw(47)<< setfill(' ') << "CASH BACK DETAILS: " << '|'<<endl;
  for (int i=0;i<n;i++){
    cout<<'|'<<right<<setw(18)<<CustomerCoins.at(i).getReturnCount()<<"  x  ";
    cout<<left<<setw(8)<<CoinNames[i]<<setw(16)<<"(s)"<<'|'<<endl;
  }
  cout << "|-----------------------------------------------|" << endl;
  cout << endl;
}

//referenced after each successful purchase
void CashRegister :: setProfit(){
  Profit += ItemTotal;
}

//clear CustomerCart, CustomerCoins, return coins
//keep profit, 
bool CashRegister :: newCustomer(){
  char NewCustomerUserInput;
    cout<<endl<<"New customer? (y/n)";
    cin>>NewCustomerUserInput;
    if (NewCustomerUserInput=='y' || NewCustomerUserInput=='Y'){
      NumberOfCustomers++; //increment customer number
      //reset necessary values
      ItemTotal=0.0;
      CustomerTotal=0.0;
      Difference=0.0;
      ReturningDifference=0.0;
      CustomerItems.clear(); //clear customer cart
      for (int i=0;i<n;i++){ //clear customer coin counts
        CustomerCoins.at(i).setCustomerCount(0);
        CustomerCoins.at(i).setReturnCount(0);
      }
      return true;
    }
    else
      return false;
}

//give report to file
void CashRegister :: giveReport(string OutputFile){
  
  cout<<endl<<"DAY OVER"<<endl;
  cout<<"Writing Report to \""<<OutputFile<<"\"..."<<endl<<"..."<<endl;
  // current date/time based on current system
  time_t now = time(0);
  char* dt = ctime(&now);

  ofstream Report;          
  Report.open(OutputFile);
  if (Report.is_open()) {
    Report <<"REPORT FOR :\t"<<dt<<endl;
    Report <<"NUMBER OF CUSTOMERS: "<<NumberOfCustomers+1<<endl;
    Report <<"PROFIT FOR THE DAY: $"<<Profit<<endl<<endl;
    Report <<"ITEMS SOLD: ";
    for (int i=0;i<RegisterItems.size();i++){
      if(RegisterItems.at(i).getSoldCount() > 0.0){
        Report <<endl<< RegisterItems.at(i).getSoldCount() <<"  x  " <<RegisterItems.at(i).getItemName();
      }
    }
  }
  Report.close();
  cout<<"Report Written."<<endl<<endl;
  cout<<"GOODBYE."<<endl;
}