//
//  main.cpp
//  day_10
//
//  Created by Aaryan Gulia on 10/12/2023.
//

#include <iostream>
#include <fstream>

using namespace std;

string compPos(vector<size_t> pos1 , vector<size_t> pos2){
    string dir;
    if(pos2[0] - pos1[0] == 1){
        dir = "south";
    }
    else if (pos2[0] - pos1[0] == -1){
        dir = "north";
    }
    else if (pos2[1] - pos1[1] == 1){
        dir = "east";
    }
    else if (pos2[1] - pos1[1] == -1){
        dir = "west";
    }
    return dir;
}

vector<size_t> check_dir(vector<size_t> prevPos , vector<size_t> currPos, char pipe){
    vector<size_t> nextPos;
    switch (pipe){
        case '|': {
            nextPos = compPos(prevPos, currPos) == "south"? vector<size_t>{(currPos[0] + 1),currPos[1]}:vector<size_t>{(currPos[0] - 1),currPos[1]};
            break;
        }
        case '-': {
            nextPos = compPos(prevPos, currPos) == "east"? vector<size_t>{(currPos[0]),currPos[1] + 1}:vector<size_t>{(currPos[0]),currPos[1] - 1};
            break;
        }
        case 'L': {
            nextPos = compPos(prevPos, currPos) == "south"? vector<size_t>{(currPos[0]),currPos[1] + 1}:vector<size_t>{(currPos[0] - 1),currPos[1]};
            break;
        }
        case 'J': {
            nextPos = compPos(prevPos, currPos) == "south"? vector<size_t>{(currPos[0]),currPos[1] - 1}:vector<size_t>{(currPos[0] - 1),currPos[1]};
            break;
        }
        case '7': {
            nextPos = compPos(prevPos, currPos) == "east"? vector<size_t>{(currPos[0] + 1),currPos[1]}:vector<size_t>{(currPos[0]),currPos[1] - 1};
            break;
        }
        case 'F': {
            nextPos = compPos(prevPos, currPos) == "west"? vector<size_t>{(currPos[0] + 1),currPos[1]}:vector<size_t>{(currPos[0]),currPos[1] + 1};
            break;
        }
        case '.': {
            throw runtime_error("WE ARE GETTING A '.' !!");
            break;
        }
        case 'S': {
            
            break;
        }
    }
    return nextPos;
}

int Solution1(vector<string> sketch, vector<size_t> S_pos){
    int farLength = 0;
    vector<size_t> prevPos = S_pos;
    vector<size_t> currPos = {S_pos[0]+1,S_pos[1]};
    
    while(true){
        char pipe = sketch[currPos[0]][currPos[1]];
        if(pipe == 'S') break;
        vector<size_t> nextPos = check_dir(prevPos, currPos,pipe);
        prevPos = currPos;
        currPos = nextPos;
        farLength++;
    }
    return (farLength+1)/2;
}

int Solution2(vector<string> sketch, vector<size_t> S_pos){
    int farLength = 0;
    vector<size_t> prevPos = S_pos;
    vector<size_t> currPos = {S_pos[0]+1,S_pos[1]};
    vector<string> loop(sketch.size(), string(sketch[0].size(), '.'));
    
    int area = 0;
    while(true){
        char pipe = sketch[currPos[0]][currPos[1]];
        loop[currPos[0]][currPos[1]] = pipe;
        //Sho
        area += prevPos[0] * currPos[1] - currPos[0] * prevPos[1];
        if(pipe == 'S') break;
        vector<size_t> nextPos = check_dir(prevPos, currPos,pipe);
        farLength++;
        
        
        prevPos = currPos;
        currPos = nextPos;
    }
    area = abs(area) / 2;
    
    return area - (farLength + 1)/2 + 1;
}

int main() {
    vector<string> sketch;
    vector<size_t> S_pos;
    fstream inputFile;
    inputFile.open("input.txt", ios::in);
    if(inputFile.is_open()){
        string line;
        while(getline(inputFile, line)){
            size_t s_pos = line.find("S");
            if(s_pos != string::npos){
                S_pos.push_back(sketch.size());
                S_pos.push_back(s_pos);
            }
            sketch.push_back(line);
        }
    }
    else{
        throw runtime_error("THE FILE DID NOT OPEN");
    }
    cout << "Solution to the 1st question is: "<<Solution1(sketch, S_pos)<<endl;
    cout << "Solution to the 2nd question is: "<<Solution2(sketch, S_pos)<<endl;
}
