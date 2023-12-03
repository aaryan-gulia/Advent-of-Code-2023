//
//  main.cpp
//  day_2
//
//  Created by Aaryan Gulia on 03/12/2023.
//

#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;

unordered_map<string, int> breakSubGame(string subGame){
    string digits = "123456789";
    unordered_map<string, int>subGameMap;
    unsigned int totalCubes = 0;
    while(true){
        auto lastLetterP = subGame.find(",");
        if(lastLetterP == -1) lastLetterP = subGame.size();
        string cubes = subGame.substr(0, lastLetterP);
        auto firstNumCubesP = cubes.find_first_of("1234567890");
        auto lastNumCubesP = cubes.find_last_of("1234567890");
        int numCubes = stoi(subGame.substr(firstNumCubesP, lastNumCubesP - firstNumCubesP + 1));
        string color = cubes.substr(lastNumCubesP + 2, lastLetterP - lastNumCubesP - 1);
        subGameMap[color] = numCubes;
        
        totalCubes += numCubes;
        
        if(lastLetterP == subGame.size()) break;
        subGame = subGame.substr(lastLetterP + 1 , subGame.size() - lastLetterP);
    }
    
    subGameMap["sum"] = totalCubes;
    return subGameMap;
}

vector<unordered_map<string, int>> breakGame(string game){
    vector<unordered_map<string, int>> gameVec;
    while(true){
        auto lastLetterP = game.find(";");
        if(lastLetterP == -1) lastLetterP = game.size();
        string subGame = game.substr(0, lastLetterP);
        gameVec.push_back(breakSubGame(subGame));
        
        if(lastLetterP == game.size()) break;
        game = game.substr(lastLetterP + 1 , game.size() - lastLetterP);
    }
    return gameVec;
}

int Solution1(unordered_map<int, vector<unordered_map<string, int>>>& gameMap){
    unsigned int sum = 0;
    for(int gameNo = 1; gameNo <= 100; gameNo++){
        bool possible = true;
        for(auto subGame: gameMap[gameNo]){
            if(subGame["green"]>13 || subGame["red"]>12 || subGame["blue"]>14 || subGame["sum"]>37){
                possible = false;
            }
        }
        if(possible) sum += gameNo;
    }
    return sum;
}

void completeCubes(unordered_map<string, int>& subGame, string key){
    if(auto findColor = subGame.find(key); findColor == subGame.end()){
        subGame[key] = 0;
    }
}

unsigned int getMin(unordered_map<string, int> subGame, string color, unsigned int min){
    completeCubes(subGame, color);
    min = (subGame[color] > min? subGame[color] : min);
    return min;
}

int Solution2(unordered_map<int, vector<unordered_map<string, int>>>& gameMap){
    unsigned int sum = 0;
    for(int gameNo = 1; gameNo <= 100; gameNo++){
        unsigned int power = 0;
        unsigned int minGreen = 0,  minRed = 0, minBlue = 0;
        for(auto subGame: gameMap[gameNo]){
            minGreen = getMin(subGame, "green", minGreen);
            minRed = getMin(subGame, "red", minRed);
            minBlue = getMin(subGame, "blue", minBlue);
        }
        power = minRed * minBlue * minGreen;
        sum += power;
    }
    return sum;
}

int main() {
    
    fstream inputFile;
    inputFile.open("input.txt", ios::in);
    
    if (inputFile.is_open()){
        string game;
        unsigned int gameNo = 0;
        unordered_map<int, vector<unordered_map<string, int>>> gameMap;
        while(getline(inputFile, game)){
            size_t startP = game.find(":");
            game = game.substr(startP,game.size() - startP);
            gameMap[++gameNo] = breakGame(game);
        }
        inputFile.close();
        cout<<"Solution to the 1st question is: "<<Solution1(gameMap)<<endl;
        cout<<"Solution to the 2nd question is: "<<Solution2(gameMap)<<endl;
    }
    
    else{
        throw runtime_error("FILE DID NOT OPEN");
    }
    
    return 0;
}
