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

void newCustomerProcess(string name, City myCity){//City may need to be converted to pointer if the program is working improperly!
    string nearName;
    string endName;
    int priority;
    int distanceNear;
    int distanceEnd;
    string inputD;
        cout<<"enter nearest location name:"<<endl;
        getline(cin, nearName);
        cout<<"enter distance to nearest location:"<<endl;
        while(getline(cin, inputD)){
            try{
                distanceNear = stoi(inputD);
                break;
            }
            catch(...){
                cout<<"invalid input"<<endl;
                cout<<"enter distance to nearest location:"<<endl;
            }
        }
        cout<<"enter nearest location to destination:"<<endl;
        getline(cin, endName);
        cout<<"enter distance from destination to nearest location:"<<endl;
        while(getline(cin, inputD)){
        try{
            distanceEnd = stoi(inputD);
            break;
        }
        catch(...){
            cout<<"invalid input"<<endl;
            cout<<"enter distance to nearest location:"<<endl;
        }
    }
    cout<<"enter customer priority (1-5):"<<endl;
    while(getline(cin, inputD)){
        try{
            priority = stoi(inputD);
            break;
        }
        catch(...){
            cout<<"Invalid input"<<endl;
            cout<<"enter customer priority (1-5):"<<endl;
        }
    }
    myCity.addCustomer(nearName, endName,(distanceEnd+distanceNear), priority);
    return;
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
                    cout<<"Enter the Group name"<<endl;
                    getline(cin, line);
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
