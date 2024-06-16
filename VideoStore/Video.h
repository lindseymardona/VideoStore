/*
-----------------------
Video
-----------------------
- title: string
- inventoryNumber: int
- checkedOut: bool
- overdue: bool
- customer: int //represents which customer is currently renting the video
-----------------------
+ Video (string, int, bool, bool, int)
+ getTitle() : string
+ getInvNr() : int
+ getCheckedOut() : bool
+ getOverdue() : bool
+ getCustomer() : int
+ setTitle(string) : void
+ setInvNr(int) : void
+ setCheckedOut(bool) : void
+ setOverdue(bool) : void
+ setCustomer(int) : void
----------------------
*/

#ifndef VIDEO_H
#define VIDEO_H
#include <iostream>
using namespace std;

class Video
{
private:
  string title;
  int inventoryNumber;
  bool checkedOut;
  bool overdue;
  int customer;

public:
  // constructor
  Video(string title, int inventoryNumber, bool checkedOut, bool overdue, int customer)
      { this->title = title;
        // ensures inventory number is a positive, 3-digit number
        this->inventoryNumber = (inventoryNumber >= 100 && inventoryNumber <= 999) ? inventoryNumber : 0;
        this->checkedOut = checkedOut;
        this->overdue = overdue;
        // ensures customer number is a positive, 4-digit number, or 0
        this->customer = (customer == 0 || (customer >= 1000 && customer <= 9999)) ? customer : this->customer; }

  // accessors 
  string getTitle() // title getter
      { return title; }

  int getInvNr() // inventory number getter
      { return inventoryNumber; }

  bool getCheckedOut() // checked out status getter
      { return checkedOut; }

  bool getOverdue() // overdue status getter
      { return overdue; }

  int getCustomer() // customer number getter
      { return customer; }

  // mutators
  void setTitle(string title) // title setter
      { this->title = title; }

  void setInvNr(int inventoryNumber) // input number setter with validation; ensures inventoryNumber is a positive, 3-digit number
      { this->inventoryNumber = (inventoryNumber >= 100 && inventoryNumber <= 999) ? inventoryNumber : this->customer; }

  void setCheckedOut(bool checkedOut) // checked out status setter
      { this->checkedOut = checkedOut; }

  void setOverdue(bool overdue) // overdue status setter
      { this->overdue = overdue; }

  void setCustomer(int customer) // customer number setter with validation; ensures customer number is a positive, 4-digit number, or 0
      { this->customer = (customer == 0 || (customer >= 1000 && customer <= 9999)) ? customer : this->customer; }
};

#endif