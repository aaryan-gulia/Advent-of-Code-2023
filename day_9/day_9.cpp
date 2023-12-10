//
//  main.cpp
//  day_9
//
//  Created by Aaryan Gulia on 10/12/2023.
//

#include <iostream>
#include <fstream>

using namespace std;

vector<vector<int>> makeDiffVector(vector<int> currVec){
    vector<vector<int>> diffVector;
    diffVector.push_back(currVec);
    while(true){
        if(all_of(currVec.begin(), currVec.end(), [](auto a){return a == 0;})) break;
        vector<int> addVec;
        transform(currVec.begin(), (currVec.end()-1), (currVec.begin()+1), back_inserter(addVec), [](auto a, auto b){return b - a;});
        diffVector.push_back(addVec);
        currVec = addVec;
    }
    return diffVector;
}

int getPrediction(vector<vector<int>> diffVector, int multiplier){
    int nextPred = 0;
    for(int i = diffVector.size() - 1; i > 0; i--){
        if (multiplier == 1) nextPred = multiplier * nextPred + *(--diffVector[i-1].end());
        else if (multiplier == -1) nextPred = multiplier * nextPred + *(diffVector[i-1].begin());
    }
    return nextPred;
}

int Solution(int qnum, vector<vector<int>> inputVector){
    int sum = 0;
    int multiplier = qnum == 1? 1 : -1;
    for(auto history : inputVector){
        vector<vector<int>> diffVector = makeDiffVector(history);
        int pred = getPrediction(diffVector, multiplier);
        sum += pred;
    }
    return sum;
}

int main() {
    vector<vector<int>> inputVector;
    fstream inputFile;
    inputFile.open("input.txt",ios::in);
    if(inputFile.is_open()){
        string line;
        while(getline(inputFile, line)){
            vector<int> currVec;
            while(true){
                size_t numEnd = line.find(" ");
                if (numEnd == string::npos){
                    currVec.push_back(stoi(line.substr(0, line.size())));
                    inputVector.push_back(currVec);
                    break;
                }
                currVec.push_back(stoi(line.substr(0, numEnd)));
                line = line.substr(numEnd + 1, line.size() - numEnd - 1);
            }
        }
    }
    else{
        throw runtime_error("THE FILE DID NOT OPEN");
    }
    
    cout << "Solution to the 1st question is: "<<Solution(1, inputVector)<<endl;
    cout << "Solution to the 2nd question is: "<<Solution(2, inputVector)<<endl;
    
}
