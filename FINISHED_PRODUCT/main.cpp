#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>

#include "City.hpp"
#include "PriorityQueue.hpp"

using namespace std;


void displayMenu(){//Displays the menu for user each time they call a function
    cout << "============Main Menu============" << endl;
    cout << "1. Load City From a Text File" << endl;
    cout << "2. Add a Customer Order" << endl;
    cout << "3. Print Locations" << endl;
    cout << "4. Print Queue" << endl;
    cout << "5. Serve Next Customer" << endl;
    cout << "6. Automate" << endl;
    cout << "7. Finish Day" << endl;
    cout << "8. Quit" << endl;
    return;
}
/*This function is a helper for option 2.
 It will take in input from the use about the added trip and call the appropriate member functions*/
void newCustomerProcess(string name, City myCity){
    if(myCity.vertices.size() > 0){} //Check to see if the cityFile has been loaded in
      bool validStart = false; //Declares a boolean, validStart, and sets it equal to false
      bool validEnd = false; //Declares a boolean, validEnd, and sets it equal to false
      bool validPriority = false; //Declares a boolean, validPriority, and set it equal to false

      string startLocation; //Declares a string, startLocation
      string endLocation; //Declares a string, endLocation
      string priority; //Declares a string, priority
      int priorityInt; //Declares an integer, priorityInt

      while(validStart == false && validEnd == false && validPriority == false){ //A while loop used to ensure the user inputs a valid start location
        cout << "Please enter a valid start location:" << endl; //Prompts user for input and recieves and stores it in startLocation
        getline(cin, startLocation);
        for(int i = 0; i < myCity.vertices.size(); i++){ //A for loop used to check the list of vertices for a valid matching location, once found sets validStart to true
          if(startLocation == myCity.vertices[i].name){
            cout << "Location found..." << endl;
            validStart = true;
          }
        }
      }

      while(validStart == true && validEnd == false && validPriority == false){ //A while loop used after recieving a valid start location to ensure the user inputs a valid end location
        cout << "Please enter a valid end location:" << endl; //Prompts the user for input and stores it in endLocation
        getline(cin, endLocation);
        for(int i = 0; i < myCity.vertices.size(); i++){ //A for loop used to check the list of vertices for a valid matching location that is not the same as startLocation //When the location is found, sets validEnd to true
          if(endLocation == myCity.vertices[i].name && endLocation != startLocation){
            cout << "Location found..." << endl;
            validEnd = true;
          }
        }
      }

      while(validPriority == false){ //A while loop used to ensure the user inputs a valid priority level
        cout << "Please enter a valid priority value between 1 and 5:"  << endl; //Prompts user to input an integer between one and five, and stores it in priority
        getline(cin, priority);
        priorityInt = stoi(priority); //Converts priority into an integer value, and stores the value in priorityInt

        if(priorityInt >= 1 && priorityInt <= 5){ //Runs a check to see that the inputed value is less than or equal to 5 but greater than or equal to 1
          cout << "Priority confirmed..." << endl; //Tells user the priority is confirmed and sets validPriority to true
          validPriority = true;
          cout << "Enqueueing customer traveling from " << startLocation << " to " << endLocation << " with priority level " << priority << endl;
        }
      }

      myCity.addCustomer(startLocation, endLocation, priorityInt); //Adds customer with proper arguements to priority queue
      cout << "Customer enqued..." << endl; //Outputs a final message alerting the user the enque was successful
      return;
    }

    else{ //When the city has not been initialzed, outputs message to the user and ends function
      cout << "Cannot add groups until city is initialized..." << endl;
    }
};
/* This function is called from option 7. It reflects the necessary calculations
and bookeeping each day involving earnings from that day's services. As the car
takes on customers throughout each day, the total earnings will saved to a variable.
This function reads from a file containing previous entries from previous days and
also the total recorded earnings of the business. It then updates the total and adds a new entry.*/
void bookKeeping(double earned){
     ifstream myFile;//We call an ifstream to get information from the file before we can write to it.
     string line;
     string line2;
     string date;
     double total = 0;
     vector<string> fileLines;//This vector helps us hold the previous entries so that when we overwrite the file they are not lost.
     myFile.open("bookKeeping.txt");//We want to open the desired file.
     if(myFile.is_open()){//If it doesn't open for some reason, we don't want to try and interact with it and cause errors or crash the program.
          getline(myFile, line);
          getline(myFile, line);
          stringstream ss;//Use a stringstream to parse the line.
          ss << line;
          getline(ss, line2, '$');//Get all of the numbers before the dollar sign which isn't a double.
          total = earned + stod(line2);//Add our day's total to the total earnings from the past.
          while(getline(myFile, line)){
               fileLines.push_back(line);
          }
     }else{cout<<"File Not opened"<<endl;}//Catch error when the file didn't open.
     cout<<"Enter a date with the format (month) (day) (year)"<<endl;
     getline(cin, date);
     ofstream outFile;//Initialize an outfile to write to file.
     outFile.open("bookKeeping.txt");//Picking our specific file.
     if(outFile.is_open()){//Again, we want to check if it's open so things don't break.
          outFile<<"Total Earned;"<<endl;
          outFile<<total<<"$"<<endl;
          for(int i = 0; i < fileLines.size(); i++){//Output all of the lines that were in the file before.
               outFile<<fileLines[i]<<endl;
          }
          outFile<<date<<","<<earned<<"$"<<endl;//New entry.
     }
     myFile.close();
     outFile.close();//Close the files so it doesn't break!
}
int main(){
    displayMenu();
    string choice;
    City myCity;
    ifstream myFile;
    string line;
    string line2;
    string city;
    vector<string> split;
    vector<bool> charge;
    int counterV;
    int counterR;
    int distance = 0;
    double earned = 0.0;
    while(getline(cin, choice)){//We are using this while loop to continually take input from the user and run the program until they select quite.
        try{//We use a try catch so that it's harder to break the program with inputs that don't fit the stoi() command for our switch.
            switch(stoi(choice)){//When the user inputs something that doesn't match the format of our switch statement,
                case 1:{//It will either be caught by the default case of the switch or the try{}, catch(){} logic of our main.
                    ifstream myFile;
                    myFile.open("cityFile.txt");//Opening an initial read file of locations.
                    if(myFile.is_open()){//Sanity Checks
                        getline(myFile, line);//Gets first line with locations
                        stringstream ss;//use a stringstream to parse
                        ss << line;
                        while(getline(ss, line2, ',')){//we want to parse over all of the delimiters and strings in between.
                            split.push_back(line2);//Add it to the split vector so we can use it later.
                            myCity.addVertex(line2);//add the location to the locations vector where it acts as a vertex of our graph.
                            cout<<"added: "<<line2<<endl;
                        }
                        getline(myFile, line);//Next line, Involves charging stations. This is a bool vector. We didn't really end up using this in the
                                             //Way we originally intended, but it's still available.
                        stringstream ss2;    //Stringstream parse
                        ss2 << line;
                        while(getline(ss2, line2, ',')){//Iterates over line being parsed.
                            bool b;
                            istringstream(line2) >> b;//This is a way to convert a string input into a bool using stringstream.
                            charge.push_back(b);
                        }
                        counterV = 0;//Counter has to reset before readin so that it is not a garbage value.
                        while(getline(myFile, line)){//We use this while loop to read the rest of the lines of the file since they will all be read the same way.
                            counterR = 0;//this counter has to be reset within the loop as it is used for iteration on each line of the file.
                            stringstream ss3;//another parse
                            ss3 << line;
                            while(getline(ss3, line2, ',')){//iterates over each line
                                if(stoi(line2) > 0){//We only wanna add edges/roads if the value is greater than zero because -1 means none, and 0 for each location is itself in the list.
                                    myCity.addRoad(split[counterV], split[counterR], stoi(line2));
                                    cout<<"Adding road from "<<split[counterV]<<" to "<<split[counterR]<<" with distance "<<line2<<endl;
                                }
                                counterR++;
                            }
                            counterV++;
                        }

                    }
                    else{
                        cout<<"Error: file not opened"<<endl;
                    }
                    break;}
                case 2:{ //Prompts user for information to add a customer to the queue
                    newCustomerProcess(line, myCity);
                    break;}
                case 3:{ //Prints traversal of city, with option for BST or DFT
                    cout<<"Would you like to print Depth first(1) or Breadth first (2)?"<<endl;
                    while(getline(cin, line)){
                        if(line == "1"){
                            myCity.printDFT();
                            break;
                        }
                        if(line == "2"){
                            myCity.printBFT();
                            break;
                        }
                        else{
                            cout<<"Invalid input, please input integer 1 or 2"<<endl;
                        }
                    };
                    break;}

                case 4:{ //Outputs a list of customers currently awaiting service
                    myCity.printCustomers();
                    break;}
                case 5:{ //Serves a single customer
                    earned += myCity.serveCustomer();
                    break;}
                case 6:{ //Automatically serves all customers in the priority queue
                    for(int i = 0; i < 10; i++){
                        earned += myCity.serveCustomer();
                    }
                    break;}
               case 7:{ //Ends the day and stores profit value in a .txt file using the bookKeeping function
                    bookKeeping(earned);
                    earned = 0;
                    break;}
               case 8:{ //Ends the program
                    cout<<"Goodbye"<<endl;
                    return 0;}
               default:{ //If the input is not valid
                    cout<<"invalid input"<<endl;
                    break;}
          }
        }
        catch(...){ //If the input is not valid
            cout<<"invalid input"<<endl;
        }
        displayMenu(); //Displays menu to the user
    }
}
