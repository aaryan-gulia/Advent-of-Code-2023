//
//  main.cpp
//  day_8
//
//  Created by Aaryan Gulia on 08/12/2023.
//

#include <iostream>
#include <fstream>
#include <map>
#include <numeric>

using namespace std;

int Solution1(map<string, vector<string>> nodeMap, string directions){
    int numSteps = 0;
    int direction = 0;
    string currNode = "AAA";
    while(true){
        int directionChoice = (directions[direction++] == 'L') ? 0 : 1;
        currNode = nodeMap[currNode][directionChoice];
        numSteps++;
        if (currNode == "ZZZ") break;
        if (direction == directions.size()) direction = 0;
    }
    
    return numSteps;
}

long long subSolution1(map<string, vector<string>> nodeMap, string directions, string currNode){
    long long numSteps = 0;
    long long direction = 0;
    while(true){
        long long directionChoice = (directions[direction++] == 'L') ? 0 : 1;
        currNode = nodeMap[currNode][directionChoice];
        numSteps++;
        if (*(--(currNode.end())) == 'Z') break;
        if (direction == directions.size()) direction = 0;
    }
    
    return numSteps;
}

long long Solution2(map<string, vector<string>> nodeMap, string directions){
    
    vector<string> aKeys;
    
    for_each(nodeMap.begin(), nodeMap.end(), [&](auto a){if(*(--(a.first.end())) == 'A') aKeys.push_back(a.first);});
    
    vector<long long> stepsVec;
    
    for(string node : aKeys){
        stepsVec.push_back(subSolution1(nodeMap, directions, node));
    }
    
    long long numSteps = accumulate(stepsVec.begin(), stepsVec.end(),(long long) 1,[](long long a, long long b){return abs(a * b) / gcd(a, b);});
    
    return numSteps;
}



int main() {
    map<string, vector<string>> nodeMap;
    string directions;
    fstream inputFile;
    inputFile.open("input.txt", ios::in);
    if(inputFile.is_open()){
        string line;
        while(getline(inputFile, line)){
            if(line.size() == 0) continue;
            if(line.size() > 30){
                directions.append(line);
                continue;
            }
            string key = line.substr(0, line.find(" "));
            line = line.substr(line.find("(")+1, line.size() - line.find("(") - 1);
            nodeMap[key].push_back(line.substr(0, line.find(",")));
            nodeMap[key].push_back(line.substr(line.find(" ") + 1, line.find(",")));
        }
    }
    else{
        throw runtime_error("FILE DID NOT OPEN");
    }
    
    cout << "Solution to the 1st question is: "<<Solution1(nodeMap, directions)<<endl;
    cout << "Solution to the 2nd question is: "<<Solution2(nodeMap, directions)<<endl;
    
}
