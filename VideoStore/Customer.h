/*
-----------------------
Customer
-----------------------
- custNr: int
- lName: string // last name
- fName: string // first name
-----------------------
+ Customer(int, string, string)
+ getCustNr() : int
+ getLName() : string
+ getFName() : string
+ setFName(string) : void
+ setLName(string) : void
+ setCustNr(int) : void
----------------------
*/

#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <iostream>
using namespace std;

class Customer
{
private:
  int custNr;
  string lName;
  string fName;

public:
  // constructor
  Customer(int custNr, string lName, string fName)
  { this->custNr = (custNr >= 1000 && custNr <= 9999) ? custNr : 0; // ensures customer number is a positive, 4-digit number
    this->lName = lName;
    this->fName = fName; }

  // accessors
  int getCustNr() // customer number getter
      { return custNr; }

  string getLName() // last name getter
      { return lName; }

  string getFName() // first name getter
      { return fName; }

  // mutators
  void setFName(string fName) // first name setter
      { this->fName = fName; }

  void setLName(string lName) // first name setter
      { this->lName = lName; }

  void setCustNr(int custNr) // customer number setter with validation; ensures customer number is a positive, 4-digit number, or 0
      { this->custNr = (custNr == 0 || (custNr >= 1000 && custNr <= 9999)) ? custNr : this->custNr; }
};

#endif