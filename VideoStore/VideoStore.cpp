//*****************
//Program Name: Final Exam (Video Store Information System)
//Author: Lindsey Mardona
//IDE Used: Visual Studio
//Program description: Utilizes customer and video object members and functions to provide the services of a video rental store.
//*****************

#include "Video.h"
#include "Customer.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

// functions to read in information
void loadVideos(ifstream&, vector<Video>&);
void loadCustomers(ifstream&, vector<Customer>&);

// functions to print information
void printMenu();
void printReportsMenu();
void printInventoryMenu();
void printCustomerMenu();
void printVideos(vector<Video>&);
int printAvailable(vector<Video>&);
int printUnavailable(vector<Video>&);
void printCustomers(vector<Customer>&);
void printOverdue(vector<Video>&, vector<Customer>&);
void plagiarism();

// functions to be called by the main menu
void checkOut(vector<Video>&, vector<Customer>&);
void checkIn(vector<Video>&);

// functions to be called by the run reports menu
string getFileName(const string);
void saveVideos(ofstream&, vector<Video>&);
void saveCustomers(ofstream&, vector<Customer>&);

// functions to be called by the inventory menu
void addVideo(vector<Video>&);
void removeVideo(vector<Video>&);
void updateVideo(vector<Video>&);

// functions to be called by the customer menu
void addCustomer(vector<Customer>&);
void removeCustomer(vector<Customer>&, vector<Video>&);
void updateCustomer(vector<Customer>&, vector<Video>&);

int main()
{
  // variables: constants, file names
  const string VIDEO_FILE = "videos.txt";
  const string CUSTOMER_FILE = "customers.txt";

  // variables: data structures
  vector<Video> videoList = {};
  vector<Customer> customerList = {};

  // variables: input & output members
  ifstream fin;
  ofstream fout;
  int input = 0;
  string fileName = "";

  // variables: loop management
  bool open = true;
  bool manage = true;

  // reading in video list information
  fin.open(VIDEO_FILE);
  loadVideos(fin, videoList);
  fin.close();

  // reading in customer information
  fin.open(CUSTOMER_FILE);
  loadCustomers(fin, customerList);
  fin.close();

  // main menu

  while (open) // keeps the menu running until the user indicates the loop to exit 
  {
    printMenu();
    cin >> input;

    switch (input)
    {
    case 1: // check out videos
      checkOut(videoList, customerList);
      break;

    case 2: // check in videos
      checkIn(videoList);
      break;

    case 3: // run reports
      manage = true;

      // customer sub-menu

      while (manage)
      {
        cout << endl;
        printReportsMenu(); // keeps the run reports sub-menu running until the user indicates the loop to exit 
        cin >> input;
        cout << endl;
        switch (input)
        {
        case 1: // overdue video report
          printOverdue(videoList, customerList);
          break;

        case 2: // write new video database
          fileName = getFileName(VIDEO_FILE);
          fout.open(fileName);
          saveVideos(fout, videoList);
          fout.close();
          break;

        case 3: // write new customer database
          fileName = getFileName(CUSTOMER_FILE);
          fout.open(fileName);
          saveCustomers(fout, customerList);
          fout.close();
          break;

        case 4: // return to main menu
          cout << endl << "Returning to the main menu..." << endl;
          manage = false; // discontinues the run reports management loop to return to the main menu
          break;

        default: // input validation
          cout << "Invalid choice, please try again." << endl;
          break;
        }
      }
      break;

    case 4: // manage inventory
      manage = true;

      // inventory sub-menu

      while (manage) // keeps the inventory sub-menu running until the user indicates the loop to exit 
      {
        cout << endl;
        printInventoryMenu();
        cin >> input;
        cout << endl;
        switch (input)
        {
        case 1: // add video to inventory
          addVideo(videoList);
          break;

        case 2: // remove video from inventory
          removeVideo(videoList);
          break;

        case 3: // update video data
          updateVideo(videoList);
          break;

        case 4: // return to main menu
          cout << endl << "Returning to the main menu..." << endl;
          manage = false; // discontinues the inventory management loop to return to the main menu
          break;

        default: // input validation
          cout << "Invalid choice, please try again." << endl;
          break;
        }
      }
      break;

    case 5: // manage customers
      manage = true;

      // customer sub-menu

      while (manage)
      {
        cout << endl;
        printCustomerMenu(); // keeps the customer sub-menu running until the user indicates the loop to exit 
        cin >> input;
        cout << endl;
        switch (input)
        {
        case 1: // list customers
          printCustomers(customerList);
          break;

        case 2: // add a customer
          addCustomer(customerList);
          break;

        case 3: // delete a customer
          removeCustomer(customerList, videoList);
          break;

        case 4: // update a customer
          updateCustomer(customerList, videoList);
          break;

        case 5: // return to main menu
          cout << endl << "Returning to the main menu..." << endl;
          manage = false; // discontinues the inventory management loop to return to the main menu
          break;

        default: // input validation
          cout << "Invalid choice, please try again." << endl;
          break;
        }
      }
      break;

    case 6: // quit
      cout << endl << "Thank you for your patronage. Goodbye!" << endl;
      open = false; // discontinues the program loop
      break;

    default: // input validation
      cout << "Invalid choice, please try again." << endl;
    }
    cout << endl;
  }

  plagiarism();
}

// functions to read in information

//*****************
//Function name: loadVideos
//Purpose: loads the video list information from a file
//List of parameters: 
//  ifstream& vin, a file stream to read from
//  vector<Video>& videoList, a vector containing all of the Video objects
//Return type: void
//*****************

void loadVideos(ifstream& vin, vector<Video>& videoList)
{
  string info = "";
  string title = "";
  int inventoryNumber = 0;
  bool checkedOut = 0;
  bool overdue = 0;
  int customer = 0;

  if (vin) // ensures the file is open
  {
    while (getline(vin, title))
    {
      getline(vin, info);
      stringstream ss(info);
      ss >> inventoryNumber >> checkedOut >> overdue >> customer; // taking in input and defining temporary attributes

      Video temp = Video(title, inventoryNumber, checkedOut, overdue, customer); // creates a temporary object using inputted attributes...
      videoList.push_back(temp); // ...and adds it to the vector
    }
  }
}

//*****************
//Function name: loadCustomers
//Purpose: loads the customer list information from a file
//List of parameters: 
//  ifstream& cfin, a file stream to read from
//  vector<Customer>& customerList, a vector containing all of the Customer objects
//Return type: void
//*****************

void loadCustomers(ifstream& cfin, vector<Customer>& customerList)
{
  int custNr = 0;
  string lName = "";
  string fName = "";

  if (cfin) // ensures the file is open
  {
    while (cfin >> lName >> fName >> custNr)
    {
      Customer temp = Customer(custNr, lName, fName);
      customerList.push_back(temp);
    }
  }
}

// functions to print information

//*****************
//Function name: printMenu
//Purpose: prints the main menu and its options
//Return type: void
//*****************

void printMenu()
{
  cout << "***VIDEO STORE MAIN MENU***" << endl;
  cout << "[1] Check out videos" << endl;
  cout << "[2] Check in videos" << endl;
  cout << "[3] Run reports" << endl;
  cout << "[4] Manage inventory" << endl;
  cout << "[5] Manage customers" << endl;
  cout << "[6] Quit" << endl;
  cout << "Your choice: ";
}

//*****************
//Function name: printReportsMenu
//Purpose: prints the run reports menu and its options
//Return type: void
//*****************

void printReportsMenu()
{
  cout << "***RUN REPORTS***" << endl;
  cout << "[1] Overdue video reports" << endl;
  cout << "[2] Write new video database" << endl;
  cout << "[3] Write new customer database" << endl;
  cout << "[4] Return to main menu" << endl;
  cout << "Your choice: ";
}

//*****************
//Function name: printInventoryMenu
//Purpose: prints the inventory menu and its options
//Return type: void
//*****************

void printInventoryMenu()
{
  cout << "***MANAGE INVENTORY***" << endl;
  cout << "[1] Add video to inventory" << endl;
  cout << "[2] Remove video from inventory" << endl;
  cout << "[3] Update video data" << endl;
  cout << "[4] Return to main menu" << endl;
  cout << "Your choice: ";
}

//*****************
//Function name: printCustomerMenu
//Purpose: prints the customer menu and its options
//Return type: void
//*****************

void printCustomerMenu()
{
  cout << "***MANAGE CUSTOMERS***" << endl;
  cout << "[1] List customers" << endl;
  cout << "[2] Add a customer" << endl;
  cout << "[3] Delete a customer" << endl;
  cout << "[4] Update a customer" << endl;
  cout << "[5] Return to main menu" << endl;
  cout << "Your choice: ";
}

//*****************
//Function name: printVideos
//Purpose: prints a lits of all videos registered in the system
//List of parameters: 
//  vector<Video>& videoList, a vector containing all of the Video objects 
//Return type: void
//*****************

void printVideos(vector<Video>& videoList)
{
  int count = 1; // to keep track of numbering for the list

  for (Video v : videoList)
  {
    cout << "[" << count++ << "] No. " << v.getInvNr() << " \"" << v.getTitle() << "\"" << endl;
  }
}

//*****************
//Function name: printAvailable
//Purpose: prints the list of videos that are available for rental  
//List of parameters: 
//  vector<Video>& videoList, a vector containing all of the Video objects 
//Returns: the number of videos that are currently available for rental 
//Return type: int
//*****************

int printAvailable(vector<Video>& videoList)
{
  int count = 1; // to keep track of numbering for the list

  for (Video v : videoList)
  {
    if (!v.getCheckedOut())
    {
      cout << "[" << count++ << "] No. " << v.getInvNr() << " \"" << v.getTitle() << "\"" << endl;
    }
  }

  return count;
}

//*****************
//Function name: printUnavailable
//Purpose: prints the list of videos that are unavailable, or currently checked out, for rental  
//List of parameters: 
//  vector<Video>& videoList, a vector containing all of the Video objects 
//Returns: the number of videos that are currently available for rental 
//Return type: int
//*****************

int printUnavailable(vector<Video>& videoList)
{
  int count = 1; // to keep track of numbering for the list

  for (Video v : videoList)
  {
    if (v.getCheckedOut())
    {
      cout << "[" << count++ << "] No. " << v.getInvNr() << " \"" << v.getTitle() << "\"" << endl;
    }
  }

  return count;
}

//*****************
//Function name: printCustomers
//Purpose: prints the list of customers 
//List of parameters: 
//  vector<Customer>& customerList, a vector containing all of the Customer objects 
//Return type: void
//*****************

void printCustomers(vector<Customer>& customerList)
{
  int count = 1; // to keep track of numbering for the list

  for (Customer c : customerList)
  {
    cout << "[" << count++ << "] " << c.getLName() << ", " << c.getFName() << " (No. " << c.getCustNr() << ")" << endl;
  }
}

//*****************
//Function name: printOverdue
//Purpose: prints a list containing the information of overdue videos
//Return type: void
//*****************

void printOverdue(vector<Video>& videoList, vector<Customer>& customerList)
{
  int customerNumber = 0;

  cout << "***OVERDUE VIDEOS***" << endl << endl;
  for (Video v : videoList)
  {
    if (v.getOverdue())
    {
      cout << "Inventory No. " << v.getInvNr() << " | Title: \"" << v.getTitle() << "\"" << endl;
      customerNumber = v.getCustomer();
      for (Customer c : customerList)
      {
        if (c.getCustNr() == customerNumber)
        {
          cout << "\tCustomer No. " << c.getCustNr() << " (" << c.getLName() << ", " << c.getFName() << ")" << endl << endl;
        }
      }
    }
  }
}

//*****************
//Function name: plagiarism
//Purpose: prints student plagiarism statement
//Return type: void
//*****************

void plagiarism()
{
  cout << "I attest that this code is my original programming work, and that I received no help creating it."
    << endl << "I attest that I did not copy this code or any portion of this code from any source." << endl;
}

// functions to be called by the main menu

//*****************
//Function name: checkOut
//Purpose: allows a customer to check out a video, then updates the object & vector information accordingly
//List of parameters: 
//  vector<Video>& videoList, a vector containing all of the Video objects 
//  vector<Customer>& customerList, a vector containing all of the Customer objects
//Return type: void
//*****************

void checkOut(vector<Video>& videoList, vector<Customer>& customerList)
{
  int count = 1; // to locate the video available for check out
  int available = 0; // the number of available videos for check out
  int videoChoice = 0; // which video to be checked out
  int customerChoice = 0; // which customer to check out the video

  // selecting the video to be checked out
  cout << endl << "***VIDEO CHECK-OUT***" << endl;
  cout << "Select a video to check out: " << endl << endl;
  available = printAvailable(videoList);
  // input validation; ensures the input is within the range of the number of videos available for rental 
  while (videoChoice <= 0 || videoChoice >= available)
  {
    cout << "Enter your choice: ";
    cin >> videoChoice;
    if (videoChoice <= 0 || videoChoice >= available)
      cout << "Invalid input, please try again." << endl;
  }

  // selecting the customer to check out the video 
  cout << endl << "Choose the customer that rented this title: " << endl;
  printCustomers(customerList);
  // input validation; ensures the input is within the range of numbers of customers 
  while (customerChoice <= 0 || customerChoice >= customerList.size() + 1)
  {
    cout << "Enter your choice: ";
    cin >> customerChoice;
    if (customerChoice <= 0 || customerChoice >= customerList.size() + 1)
      cout << "Invalid input, please try again." << endl;
  }
  Customer c = customerList[customerChoice - 1]; // to access the attributes of the customer of choice 

  // updating the object information
  for (Video& v : videoList) // &v enables the object information to be manipulated 
  {
    if (!v.getCheckedOut() && videoChoice == count++) // locates the video in the vector 
    {
      v.setCheckedOut(true); // changes the checked out status 
      v.setCustomer(c.getCustNr()); // sets the customer number that checked out the video
      cout << v.getTitle() << " was successful checked out by " << c.getLName() << ", "
        << c.getFName() << " (Customer No. " << c.getCustNr() << ")." << endl;
    }
  }
}

//*****************
//Function name: checkIn
//Purpose: allows a customer to check in a video, then updates the object & vector information accordingly
//List of parameters: 
//  vector<Video>& videoList, a vector containing all of the Video objects 
//Return type: void
//*****************

void checkIn(vector<Video>& videoList)
{
  int count = 1; // to locate the video available for check out
  int available = 0; // the number of available videos for check out
  int videoChoice = 0; // which video to be checked out

  // selecting the video to be checked in
  cout << endl << "***VIDEO CHECK-IN***" << endl;
  cout << "Select a video to check in: " << endl << endl;
  available = printUnavailable(videoList);
  // input validation; ensures the input is within the range of the number of videos available for rental 
  while (videoChoice <= 0 || videoChoice >= available)
  {
    cout << "Enter your choice: ";
    cin >> videoChoice;
    if (videoChoice <= 0 || videoChoice >= available)
      cout << "Invalid input, please try again." << endl;
  }

  // updating the object information
  for (Video& v : videoList) // &v enables the object information to be manipulated 
  {
    if (v.getCheckedOut() && videoChoice == count++) // locates the video in the vector 
    {
      cout << v.getTitle() << " was successfully returned by Customer No. " << v.getCustomer() << "." << endl;
      v.setOverdue(false); // changes the overdue status
      v.setCheckedOut(false); // changes the checked out status 
      v.setCustomer(0); // resets the customer number
    }
  }
}

// functions to be called by the run reports menu

//*****************
//Function name: getFileName
//Purpose: takes in a valid string to use as a file name
//List of parameters: 
//  const string FILE, the name of a file that should not be overwritten or changed
//Returns: a unique file name
//Return type: string
//*****************

string getFileName(const string FILE)
{
  bool invalid = true;
  string fileName = "";

  while (invalid)
  {
    invalid = false;
    cout << "Enter a file name to save the new database to: ";
    cin >> fileName;
    if (fileName == FILE)
    {
      cout << "The file name cannot match the original input file. Please try again." << endl << endl;
      invalid = true;
    }
  }

  return fileName;
}

//*****************
//Function name: saveVideos
//Purpose: saves the video list information to a file
//List of parameters: 
//  ofstream& vin, a file stream to read into
//  vector<Video>& videoList, a vector containing all of the Video objects
//Return type: void
//*****************

void saveVideos(ofstream& fout, vector<Video>& videoList)
{
  for (Video v : videoList)
  {
    fout << v.getTitle() << endl;
    fout << v.getInvNr() << " " << v.getCheckedOut() << " " << v.getOverdue() << " " << v.getCustomer() << endl;
  }
}

//*****************
//Function name: saveCustomers
//Purpose: saves the customer list information to a file
//List of parameters: 
//  ofstream& vin, a file stream to read into
//  vector<Customer>& customerList, a vector containing all of the Customer objects
//Return type: void
//*****************

void saveCustomers(ofstream& fout, vector<Customer>& customerList)
{
  for (Customer c : customerList)
  {
    fout << c.getLName() << endl << c.getFName() << endl << c.getCustNr() << endl;
  }
}

// functions to be called by the inventory menu

//*****************
//Function name: addVideo
//Purpose: adds a new Video object to the vector of videos 
//List of parameters: 
//  vector<Video>& videoList, a vector containing all of the Video objects 
//Return type: void
//*****************

void addVideo(vector<Video>& videoList)
{
  string title = "";
  int inventoryNumber = 0;
  bool validInput = false;

  cout << "Enter a video title to add: ";
  cin.ignore();
  getline(cin, title);
  while (!validInput) // ensures input is a valid inventory number
  {
    cout << "Enter its inventory number: ";
    validInput = true;
    cin >> inventoryNumber;

    // input validation is determined by two things: 
    if (inventoryNumber < 100 || inventoryNumber > 999) // validation 1: inventory number is a positive, 3-digit number
    {
      validInput = false;
      cout << "Invalid input. Input must be a positive, 3-digit number. Please try again." << endl;
    }

    for (Video v : videoList) // validation 2: inventory number does not already exist 
    {
      if (v.getInvNr() == inventoryNumber)
      {
        validInput = false;
        cout << "Invalid input. Inventory number is already registered. Please try again." << endl;
      }
    }
  }

  Video temp = Video(title, inventoryNumber, 0, 0, 0); // creates a temporary object using inputted attributes...
  videoList.push_back(temp); // ...and adds it to the vector
  cout << "Video \"" << temp.getTitle() << "\" (No. " << temp.getInvNr() << ") was successfully added to the database." << endl;
}

//*****************
//Function name: removeVideo
//Purpose: removes a Video object from the vector of videos 
//List of parameters: 
//  vector<Video>& videoList, a vector containing all of the Video objects 
//Return type: void
//*****************

void removeVideo(vector<Video>& videoList)
{
  int choice = 0;

  cout << "Select a video to remove: " << endl << endl;
  printVideos(videoList);

  // input validation; ensures the input is within the range of the number of videos registered in the system 
  while (choice <= 0 || choice > videoList.size())
  {
    cout << "Enter your choice: ";
    cin >> choice;
    if (choice <= 0 || choice > videoList.size())
      cout << "Invalid input, please try again." << endl;
  }

  videoList.erase(videoList.begin() + choice - 1); // deletes the object at the index of choice
  cout << "Video \"" << videoList[choice - 1].getTitle() << "\" (No. " << videoList[choice - 1].getInvNr() 
    << ") was successfully removed from the database." << endl;
}

//*****************
//Function name: updateVideo
//Purpose: updates the information of a Video object in the vector of videos 
//List of parameters: 
//  vector<Video>& videoList, a vector containing all of the Video objects 
//Return type: void
//*****************

void updateVideo(vector<Video>& videoList)
{
  int choice = 0;
  char update = 'a';
  string title = "";
  int inventoryNumber = 0;
  bool validInput = false;

  // choosing a video to update

  cout << "Select a video to update: " << endl << endl;
  printVideos(videoList);

  // input validation; ensures the input is within the range of the number of videos registered in the system 
  while (choice <= 0 || choice > videoList.size())
  {
    cout << "Enter your choice: ";
    cin >> choice;
    if (choice <= 0 || choice > videoList.size())
      cout << "Invalid input, please try again." << endl;
  }

  // updating the title of the video

  cout << endl << "Current title: \"" << videoList[choice - 1].getTitle() << "\"" << endl;

  // input validation; ensures the input is a y or an n
  while (toupper(update) != 'Y' && toupper(update) != 'N')
  {
    cout << "Update title? Y/N: ";
    cin >> update;
    if (toupper(update) != 'Y' && toupper(update) != 'N')
      cout << "Invalid input, please try again." << endl;
  }

  // updating data
  if (toupper(update) == 'Y')
  {
    cout << "Enter new title: ";
    cin.ignore();
    getline(cin, title);
    videoList[choice - 1].setTitle(title);
    cout << "Title of Video No. " << videoList[choice - 1].getInvNr() 
      << " was successfully updated to \"" << videoList[choice - 1].getTitle() << "\"." << endl;
  }

  // updating the inventory number of the video

  update = 'a'; // resets the value of update
  cout << endl << "Current inventory number: #" << videoList[choice - 1].getInvNr() << "" << endl;

  // input validation; ensures the input is a y or an n

  while (toupper(update) != 'Y' && toupper(update) != 'N')
  {
    cout << endl << "Update inventory number? Y/N: ";
    cin >> update;
    if (toupper(update) != 'Y' && toupper(update) != 'N')
      cout << "Invalid input, please try again." << endl;
  }

  // updating data
  if (toupper(update) == 'Y')
  {
    while (!validInput) // ensures input is a valid inventory number
    {
      cout << "Enter new inventory number: ";
      validInput = true;
      cin >> inventoryNumber;

      // input validation is determined by two things: 
      if (inventoryNumber < 100 || inventoryNumber > 999) // validation 1: inventory number is a positive, 3-digit number
      {
        validInput = false;
        cout << "Invalid input. Input must be a positive, 3-digit number. Please try again." << endl;
      }

      for (Video v : videoList) // validation 2: inventory number does not already exist 
      {
        if (v.getInvNr() == inventoryNumber)
        {
          validInput = false;
          cout << "Invalid input. Inventory number is already registered. Please try again." << endl;
        }
      }
    }
    videoList[choice - 1].setInvNr(inventoryNumber);
    cout << "Inventory number of \"" << videoList[choice - 1].getTitle() << "\" was successfully updated to " << videoList[choice - 1].getInvNr() << "." << endl;
  }
  
}

// functions to be called by the customer menu

//*****************
//Function name: addCustomer
//Purpose: adds a new Customer object to the vector of customers 
//List of parameters: 
//  vector<Customer>& customerList, a vector containing all of the Customer objects 
//Return type: void
//*****************

void addCustomer(vector<Customer>& customerList)
{
  string fName = "";
  string lName = "";
  int custNr = 0;
  bool validInput = false;

  cout << "Enter the first name of a customer to add: ";
  cin.ignore();
  getline(cin, fName);

  cout << "Enter the last name of a customer to add: ";
  getline(cin, lName);

  while (!validInput) // ensures input is a valid customer number
  {
    cout << "Enter the customer number of a customer to add: ";
    validInput = true;
    cin >> custNr;

    // input validation is determined by two things: 
    if (custNr < 1000 || custNr > 9999) // validation 1: customer number is a positive, 4-digit number
    {
      validInput = false;
      cout << "Invalid input. Input must be a positive, 4-digit number. Please try again." << endl;
    }

    for (Customer c : customerList) // validation 2: customer number does not already exist 
    {
      if (c.getCustNr() == custNr)
      {
        validInput = false;
        cout << "Invalid input. Customer number is already registered. Please try again." << endl;
      }
    }
  }

  // formatting names with capitalization
  lName[0] = toupper(lName[0]);
  for (int i = 1; i < lName.length(); i++)
  {
    if (lName[i - 1] == ' ')
      lName[i] = toupper(lName[i]);
  }

  fName[0] = toupper(fName[0]);
  for (int i = 1; i < fName.length(); i++)
  {
    if (fName[i - 1] == ' ')
      fName[i] = toupper(fName[i]);
  }

  Customer temp = Customer(custNr, lName, fName); // creates a temporary object using inputted attributes...
  customerList.push_back(temp); // ...and adds it to the vector
  cout << "Customer " << temp.getFName() << " " << temp.getLName() << " (No. " << temp.getCustNr() 
    << ") was successfully added to the database." << endl;
}

//*****************
//Function name: removeCustomer
//Purpose: removes a Customer object from the vector of customers 
//List of parameters: 
//  vector<Customer>& customerList, a vector containing all of the Customer objects 
//Return type: void
//*****************

void removeCustomer(vector<Customer>& customerList, vector<Video>& videoList)
{
  int choice = 0;

  cout << "Select a customer to remove: " << endl << endl;
  printCustomers(customerList);

  // input validation; ensures the input is within the range of the number of customers registered in the system 
  while (choice <= 0 || choice > customerList.size())
  {
    cout << "Enter your choice: ";
    cin >> choice;
    if (choice <= 0 || choice > customerList.size())
      cout << "Invalid input, please try again." << endl;
  }

  for (Video v : videoList) // adjusts the customer information in the Video object accordingly
  {
    if (v.getCustomer() == customerList[choice - 1].getCustNr())
    {
      v.setCustomer(0);
    }
  }

  cout << "Customer " << customerList[choice - 1].getFName() << " " << customerList[choice - 1].getLName()
    << " (No. " << customerList[choice - 1].getCustNr() << ") was successfully removed from the database." << endl;
  customerList.erase(customerList.begin() + choice - 1); // deletes the object at the index of choice
}

//*****************
//Function name: updateCustomer
//Purpose: updates the information of a Customer object in the vector of customers 
//List of parameters: 
//  vector<Customer>& customerList, a vector containing all of the Customer objects 
//Return type: void
//*****************

void updateCustomer(vector<Customer>& customerList, vector<Video>& videoList)
{
  int choice = 0;
  char update = 'a';
  string fName = "";
  string lName = "";
  int custNr = 0;
  bool validInput = false;

  // choosing a video to update

  cout << "Select a customer to update: " << endl << endl;
  printCustomers(customerList);

  // input validation; ensures the input is within the range of the number of customers registered in the system 
  while (choice <= 0 || choice > customerList.size())
  {
    cout << "Enter your choice: ";
    cin >> choice;
    if (choice <= 0 || choice > customerList.size())
      cout << "Invalid input, please try again." << endl;
  }

  // updating the first name of the customer

  cout << endl << "Current first name: " << customerList[choice - 1].getFName() << endl;

  // input validation; ensures the input is a y or an n
  while (toupper(update) != 'Y' && toupper(update) != 'N')
  {
    cout << "Update first name? Y/N: ";
    cin >> update;
    if (toupper(update) != 'Y' && toupper(update) != 'N')
      cout << "Invalid input, please try again." << endl;
  }

  // updating data
  if (toupper(update) == 'Y')
  {
    cout << "Enter new first name: ";
    cin.ignore();
    getline(cin, fName);

    // formatting name with capitalization
    fName[0] = toupper(fName[0]);
    for (int i = 1; i < fName.length(); i++)
    {
      if (fName[i - 1] == ' ')
        fName[i] = toupper(fName[i]);
    }

    customerList[choice - 1].setFName(fName);
    cout << "First name of Customer No. " << customerList[choice - 1].getCustNr() 
      << " was successfully updated to \"" << customerList[choice - 1].getFName() << "\"." << endl;
  }

  // updating the last name of the customer

  update = 'a'; // resets the value of update
  cout << endl << "Current last name: " << customerList[choice - 1].getLName() << endl;

  // input validation; ensures the input is a y or an n
  while (toupper(update) != 'Y' && toupper(update) != 'N')
  {
    cout << "Update first name? Y/N: ";
    cin >> update;
    if (toupper(update) != 'Y' && toupper(update) != 'N')
      cout << "Invalid input, please try again." << endl;
  }

  // updating data
  if (toupper(update) == 'Y')
  {
    cout << "Enter new last name: ";
    cin.ignore();
    getline(cin, lName);

    // formatting name with capitalization
    lName[0] = toupper(lName[0]);
    for (int i = 1; i < lName.length(); i++)
    {
      if (lName[i - 1] == ' ')
        lName[i] = toupper(lName[i]);
    }

    customerList[choice - 1].setLName(lName);
    cout << "Last name of Customer No. " << customerList[choice - 1].getCustNr()
      << " was successfully updated to \"" << customerList[choice - 1].getLName() << "\"." << endl;
  }

  // updating the customer number of the customer

  update = ' '; // resets the value of update
  cout << endl << "Current customer number: " << customerList[choice - 1].getCustNr() << endl;

  // input validation; ensures the input is a y or an n
  while (toupper(update) != 'Y' && toupper(update) != 'N')
  {
    cout << "Update customer number? Y/N: ";
    cin >> update;
    if (toupper(update) != 'Y' && toupper(update) != 'N')
      cout << "Invalid input, please try again." << endl;
  }

  // updating data
  if (toupper(update) == 'Y')
  {
    while (!validInput) // ensures input is a valid customer number
    {
      cout << "Enter new customer number: ";
      validInput = true;
      cin >> custNr;

      // input validation is determined by two things: 
      if (custNr < 1000 || custNr > 9999) // validation 1: customer number is a positive, 4-digit number
      {
        cout << "Invalid input. Input must be a positive, 4-digit number. Please try again." << endl;
        validInput = false;
      }

      for (Customer c : customerList) // validation 2: customer number does not already exist 
      {
        if (c.getCustNr() == custNr)
        {
          validInput = false;
          cout << "Invalid input. Customer number is already registered. Please try again." << endl;
        }
      }

      for (Video v : videoList) // adjusts the customer information in the Video object accordingly
      {
        if (v.getCustomer() == customerList[choice - 1].getCustNr())
        {
          v.setCustomer(custNr);
        }
      }
    }
    customerList[choice - 1].setCustNr(custNr);
    cout << "Inventory number of \"" << customerList[choice - 1].getFName() << " " << customerList[choice - 1].getLName()
      << "\" was successfully updated to " << customerList[choice - 1].getCustNr() << "." << endl;
  }
}