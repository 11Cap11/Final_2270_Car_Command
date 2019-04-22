#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>

#include "City.hpp"
#include "PriorityQueue.hpp"

using namespace std;


void displayMenu(){
    cout << "============Main Menu============" << endl;
    cout << "1. Load City From a Text File" << endl;
    cout << "2. Add a Group to Priority Queue" << endl;
    cout << "3. Show Customer List" << endl;
    cout << "4. Serve Next Group" << endl;
    cout << "5. Automate"<<endl;
    cout << "6. Quit" << endl;
}

void newCustomerProcess(string name, City myCity)
{
    if(myCity.vertices.size() > 0)
    {
      bool validStart = false;
      bool validEnd = false;
      bool validPriority = false;

      string startLocation;
      string endLocation;
      string priority;
      int priorityInt;

      while(validStart == false && validEnd == false && validPriority == false)
      {
        cout << "Please enter a valid start location:" << endl;
        getline(cin, startLocation);
        for(int i = 0; i < myCity.vertices.size(); i++)
        {
          if(startLocation == myCity.vertices[i].name)
          {
            cout << "Location found..." << endl;
            validStart = true;
          }
        }
      }

      while(validStart == true && validEnd == false && validPriority == false)
      {
        cout << "Please enter a valid end location:" << endl;
        getline(cin, endLocation);
        for(int i = 0; i < myCity.vertices.size(); i++)
        {
          if(endLocation == myCity.vertices[i].name && endLocation != startLocation)
          {
            cout << "Location found..." << endl;
            validEnd = true;
          }
        }
      }

      while(validPriority == false)
      {
        cout << "Please enter a valid priority value between 1 and 5:"  << endl;
        getline(cin, priority);
        priorityInt = stoi(priority);

        if(priorityInt >= 1 && priorityInt <= 5)
        {
          cout << "Priority confirmed..." << endl;
          validPriority = true;
          cout << "Enqueueing customer traveling from " << startLocation << " to " << endLocation << " with priority level " << priority << endl;
        }
      }

      myCity.addCustomer(startLocation, endLocation, priorityInt);
      cout << "Customer enqued..." << endl;
      return;
    }

    else
    {
      cout << "Cannot add groups until city is initialized..." << endl;
    }
};

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
    while(getline(cin, choice)){
        try{
            switch(stoi(choice)){
                case 1:{
                    ifstream myFile;
                    myFile.open("cityFile.txt");
                    if(myFile.is_open()){
                        getline(myFile, line);
                        stringstream ss;
                        ss << line;
                        while(getline(ss, line2, ',')){
                            split.push_back(line2);
                            myCity.addVertex(line2);
                            cout<<"added: "<<line2<<endl;
                        }
                        getline(myFile, line);
                        stringstream ss2;
                        ss2 << line;
                        while(getline(ss2, line2, ',')){
                            bool b;
                            istringstream(line2) >> b;
                            charge.push_back(b);
                        }
                        counterV = 0;
                        while(getline(myFile, line)){
                            counterR = 0;
                            stringstream ss3;
                            ss3 << line;
                            while(getline(ss3, line2, ',')){
                                if(stoi(line2) > 0){
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
                case 2:{
                    newCustomerProcess(line, myCity);
                    break;  }
                case 3:{
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
                case 4:{
                    earned += myCity.serveCustomer();
                    break;}
                case 5:{
                    for(int i = 0; i < 10; i++){
                        earned += myCity.serveCustomer();
                    }
                    break;}
                case 6:{
                    return 0;}
                default:{
                    cout<<"invalid input"<<endl;
                    break;}
          }
        }
        catch(...){
            cout<<"invalid input"<<endl;
        }
        displayMenu();
    }
}
