//
//  main.cpp
//  day_3
//
//  Created by Aaryan Gulia on 03/12/2023.
//
#include <iostream>
#include <fstream>
#include <map>

using namespace std;

vector<string> getFileVec(){
    fstream inputFile;
    inputFile.open("input.txt", ios::in);
    vector<string> fileVec;
    if (inputFile.is_open()){
        string line;
        while(getline(inputFile, line)){
            line.insert(0, ".");
            line.insert(line.size(), ".");
            fileVec.push_back(line);
        }

        inputFile.close();
    }
    
    else{
        throw runtime_error("FILE DID NOT OPEN");
    }
    return fileVec;
}

int Solution1(){
    int sum = 0;
    int lineNo = 0;
    vector<string> fileVec = getFileVec();
    for(string line:fileVec){
        int lineLost = 0;
        while(true){
            size_t intStart = line.find_first_of("1234567890");
            if(intStart == string::npos) break;
            size_t intEnd = line.substr(intStart, line.size() - intStart).find_first_not_of("1234567890");
            int num = stoi(line.substr(intStart, intEnd));
            
            string searchZone;
            if(lineNo > 0)
                searchZone.append(fileVec[lineNo-1].substr(lineLost + intStart - 1, intEnd + 2));
            if(lineNo < fileVec.size()-1)
                searchZone.append(fileVec[lineNo+1].substr(lineLost + intStart - 1, intEnd + 2));
            searchZone.append(fileVec[lineNo].substr(lineLost + intStart - 1, intEnd + 2));
            if(searchZone.find_first_not_of("1234567890.") != string::npos){
                sum += num;
            }
            
            line = line.substr(intStart + intEnd, line.size() - intEnd);
            lineLost += intStart + intEnd;
        }
        lineNo++;
    }
    return sum;
}



int Solution2(){
    int sum = 0;
    unsigned int lineNo = 0;
    map<vector<size_t>, vector<int>> starMap;
    vector<string> fileVec = getFileVec();
    for(string line:fileVec){
        int lineLost = 0;
        while(true){
            size_t intStart = line.find_first_of("1234567890");
            if(intStart == string::npos) break;
            size_t intEnd = line.substr(intStart, line.size() - intStart).find_first_not_of("1234567890");
            int num = stoi(line.substr(intStart, intEnd));
            
            string searchZone;
            if(lineNo > 0){
                searchZone = fileVec[lineNo-1].substr(lineLost + intStart - 1, intEnd + 2);
                while(true){
                    size_t starP =  searchZone.find_first_of("*");
                    if(starP == string::npos) break;
                    vector<size_t> key = {lineNo-1, lineLost + intStart - 1 + starP};
                    starMap[key].push_back(num);
                    searchZone = searchZone.substr(starP + 1, searchZone.size() - starP - 1);
                }
            }
            if(lineNo < fileVec.size()-1){
                searchZone=(fileVec[lineNo+1].substr(lineLost + intStart - 1, intEnd + 2));
                while(true){
                    size_t starP =  searchZone.find_first_of("*");
                    if(starP == string::npos) break;
                    vector<size_t> key = {lineNo+1, lineLost + intStart - 1 + starP};
                    starMap[key].push_back(num);
                    searchZone = searchZone.substr(starP + 1, searchZone.size() - starP - 1);
                }
            }
            searchZone = (fileVec[lineNo].substr(lineLost + intStart - 1, intEnd + 2));
            while(true){
                size_t starP =  searchZone.find_first_of("*");
                if(starP == string::npos) break;
                vector<size_t> key = {lineNo, lineLost + intStart - 1 + starP};
                starMap[key].push_back(num);
                searchZone = searchZone.substr(starP + 1, searchZone.size() - starP - 1);
            }
    
            line = line.substr(intStart + intEnd, line.size() - intEnd);
            lineLost += intStart + intEnd;
        }
        lineNo++;
    }
    for(auto[key,value]:starMap){
        if(value.size() == 2){
            sum += (value[0] * value[1]);
        }
    }
    
    return sum;
}

int main() {
    cout<<"Solution to the 1st question: "<<Solution1()<<endl;
    cout<<"Solution to the 2nd question: "<<Solution2()<<endl;
    return 0;
}
