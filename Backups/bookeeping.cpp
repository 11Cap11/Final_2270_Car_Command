#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main(){
     double earned = 10;
     ifstream myFile;
     string line;
     string line2;
     string date;
     double total = 0;
     vector<string> fileLines;
     myFile.open("bookKeeping.txt");
     if(myFile.is_open()){
          getline(myFile, line);
          getline(myFile, line);
          stringstream ss;
          ss << line;
          getline(ss, line2, '%');
          total = earned + stod(line2);
          while(getline(myFile, line)){
               fileLines.push_back(line);
          }
     }else{cout<<"File Not opened"<<endl;}
     cout<<"Enter a date with the format (month) (day) (year)"<<endl;
     getline(cin, date);
     ofstream outFile;
     outFile.open("bookKeeping.txt");
     if(outFile.is_open()){
          outFile<<"Total Earned;"<<endl;
          outFile<<total<<"$"<<endl;
          for(int i = 0; i < fileLines.size(); i++){
               outFile<<fileLines[i]<<endl;
          }
          outFile<<date<<","<<earned<<"$"<<endl;
     }
     myFile.close();
     outFile.close();
}
