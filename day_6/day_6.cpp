//
//  main.cpp
//  day_6
//
//  Created by Aaryan Gulia on 06/12/2023.
//

#include <iostream>
#include <fstream>

using namespace std;

unordered_map<string, vector<int>> getContainer(){
    unordered_map<string, vector<int>> tdContainer;
    fstream inputFile;
    inputFile.open("input.txt", ios::in);
    if(inputFile.is_open()){
        string line;
        while(getline(inputFile, line)){
            if(line.size() == 0) break;
            string key = line.substr(0, line.find(":"));
            while(true){
                auto firstInt = line.find_first_of("1234567890");
                if(firstInt == string::npos) break;
                line = line.substr(line.find_first_of("1234567890"), line.size() - line.find_first_of("1234567890"));
                firstInt = line.find_first_of("1234567890");
                auto lastInt = line.find(" ");
                if(lastInt == string::npos) lastInt = line.size();
                int num = stoi(line.substr(firstInt, lastInt - firstInt));
                line = line.substr(lastInt, line.size() - lastInt);
                tdContainer[key].push_back(num);
            }
        }
    }
    return tdContainer;
}

long long getWays(long long time, long long distance){
    long long ways = 0;
    for(int i = 0; i <= time; i++){
        if(i * (time - i) > distance)
           ways++;
    }
    return ways;
}

int Solution1(){
    int prod = 1;
    unordered_map<string, vector<int>> input = getContainer();
    for(int i = 0; i < input["Time"].size(); i++){
        int numWays = getWays(input["Time"][i], input["Distance"][i]);
        prod *= numWays;
    }
    
    return prod;
}

long long Solution2(){
    long long time = 61677571;
    long long distance = 430103613071150;
    return(getWays(time, distance));
}

int main() {
    cout << "Solution to the 1st question is: "<<Solution1()<<endl;
    cout << "Solution to the 2nd question is: "<<Solution2()<<endl;
}
