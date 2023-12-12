//
//  main.cpp
//  day_11
//
//  Created by Aaryan Gulia on 11/12/2023.
//

#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

vector<vector<long long>> expand2(vector<string>& original){
    vector<vector<long long>> expansionVector = {vector<long long>(),vector<long long>()};
    for(long long i = 0; i < original.size(); i++){
        if(all_of(original[i].begin(), original[i].end(), [](char a){return a == '.';})){
            expansionVector[0].push_back(i);
        }
    }
    for(long long i = 0; i < original[0].size(); i++){
        if(all_of(original.begin(),original.end(), [&](string a){return a[i] == '.';})){
            expansionVector[1].push_back(i);
        }
    }
    return expansionVector;
}

long long getDistance(vector<string>universe, vector<long long> coordinate, long long expSize){
    vector<vector<long long>> expVector = expand2(universe);
    long long totalDist = 0;
    long long num = 0;
    for(long long i = coordinate[0]; i < universe.size(); i++){
        string row = universe[i];
        long long prevcoord = 0;
        if(i == coordinate[0]) {
            row = row.substr(coordinate[1]+1, row.size() - coordinate[1] - 1);
            prevcoord += coordinate[1]+1;
        }
        while(true){
            long long gal = row.find("#");
            if(gal == string::npos) break;
            long long expCoef = count_if(expVector[0].begin(), expVector[0].end(), [&](long long a) -> bool {bool val = coordinate[0] < i? a > coordinate[0] && a <= i : a >= i && a < coordinate[0]; return val;});
            expCoef += count_if(expVector[1].begin(), expVector[1].end(), [&](long long a) -> bool {bool val = coordinate[1] < gal+prevcoord? a > coordinate[1] && a <= gal+prevcoord : a >= gal+prevcoord && a < coordinate[1]; return val;});
            long long dist = gal+prevcoord >coordinate[1]? i - coordinate[0] + gal + prevcoord - coordinate[1] : i - coordinate[0] - gal - prevcoord + coordinate[1] ;
            dist += expCoef * expSize;
            totalDist += dist;
            if(gal == row.size() - 1) break;
            row = row.substr(gal + 1, row.size() - gal - 1);
            prevcoord += gal + 1;
        }
    }
    return totalDist;
}

long long Solution(vector<string>universe, size_t qnum){
    long long sum = 0;
    long long expsize = qnum == 1? 1 : 999999;
    for(long long i = 0; i < universe.size(); i++){
        string row = universe[i];
        long long prevcoord = 0;
        while(true){
            long long gal = row.find("#");
            if(gal == string::npos) break;
            vector<long long>coord {i, gal + prevcoord};
            long long dist = getDistance(universe, coord,expsize);
            sum += dist;
            if(gal == row.size() - 1) break;
            row = row.substr(gal + 1, row.size() - gal - 1);
            prevcoord += gal + 1;
        }
    }
    
    return sum;
}

int main() {
    int galNum = 0;
    vector<string> input;
    fstream inputFile;
    inputFile.open("input.txt", ios::in);
    if(inputFile.is_open()){
        string line;
        while(getline(inputFile, line)){
            for(char& elem : line){
                if(elem == '#') ++galNum;
            }
            input.push_back(line);
        }
    }
    else{
        throw runtime_error("FILE DID NOT OPEN");
    }
    
    cout << "Solution to the 1st question is: "<<Solution(input, 1)<<endl;
    cout << "Solution to the 2nd question is: "<<Solution(input, 2)<<endl;
}
