//
//  main.cpp
//  day_7
//
//  Created by Aaryan Gulia on 07/12/2023.
//

#include <iostream>
#include <fstream>
#include <map>

using namespace std;

unordered_map<string, int> getInputMap(){
    unordered_map<string, int> inputMap;
    fstream inputFile;
    inputFile.open("input.txt", ios::in);
    if(inputFile.is_open()){
        string line;
        while(getline(inputFile, line)){
            auto space = line.find(" ");
            string key = line.substr(0, space);
            int num = stoi(line.substr(space + 1, line.size() - space - 1));
            inputMap[key] = num;
        }
    }
    else{
        throw runtime_error("FILE DID NOT OPEN");
    }
    return inputMap;
}

enum Types{
    high_card = 0,
    one_pair = 1,
    two_pair = 2,
    three_kind = 3,
    full_house = 4,
    four_kind = 5,
    five_kind = 6
};
enum FaceCards{
    A = 14,
    T = 10,
    J1 = 11,
    J2 = 1,
    Q = 12,
    K = 13
};

FaceCards getFaceCard1(char card){
    FaceCards faceCard = A;
    switch (card) {
        case 'A':
            faceCard = A;
            break;
        case 'T':
            faceCard = T;
            break;
        case 'J':
            faceCard = J1;
            break;
        case 'Q':
            faceCard = Q;
            break;
        case 'K':
            faceCard = K;
            break;
    }
    return faceCard;
}

FaceCards getFaceCard2(char card){
    FaceCards faceCard = A;
    switch (card) {
        case 'A':
            faceCard = A;
            break;
        case 'T':
            faceCard = T;
            break;
        case 'J':
            faceCard = J2;
            break;
        case 'Q':
            faceCard = Q;
            break;
        case 'K':
            faceCard = K;
            break;
    }
    return faceCard;
}


Types getType1(string hand){
    Types currType = high_card;
    
    unordered_map<char, int> counter;

    for (int i = 0; i < hand.length(); i++) {
        counter[hand[i]]++;
    }
    if(counter.size() == 1){
        currType = five_kind;
    }
    else if (counter.size() == 2){
        if((counter.begin()) -> second < 4 && (++counter.begin()) -> second < 4){
            currType = full_house;
        }
        else{
            currType = four_kind;
        }
    }
    else if (counter.size() == 3){
        auto it = counter.begin();
        if(it++ -> second == 2 || it++ -> second == 2 || it -> second == 2){
            currType = two_pair;
        }
        else{
            currType = three_kind;
        }
    }
    else if (counter.size() == 4){
        currType = one_pair;
    }
    return currType;
}

Types getType2(string hand){
    Types currType = high_card;
    
    unordered_map<char, int> counter;
    int Jcount = 0;

    for (int i = 0; i < hand.length(); i++) {
        if(hand[i] == 'J'){
            Jcount++;
            continue;
        }
        counter[hand[i]]++;
    }

    map<int, char> revCounter;
    for_each(counter.begin(), counter.end(), [&](auto a){revCounter[a.second] = a.first;});
    char maxCard = (--revCounter.end()) -> second;
    if(Jcount > 0)counter[maxCard] += Jcount;
    Jcount = 0;
    
    if(counter.size() == 1){
        currType = five_kind;
    }
    else if (counter.size() == 2){
        if((counter.begin()) -> second < 4 && (++counter.begin()) -> second < 4){
            currType = full_house;
        }
        else{
            currType = four_kind;
        }
    }
    else if (counter.size() == 3){
        auto it = counter.begin();
        if(it++ -> second == 2 || it++ -> second == 2 || it -> second == 2){
            currType = two_pair;
        }
        else{
            currType = three_kind;
        }
    }
    else if (counter.size() == 4){
        currType = one_pair;
    }
    return currType;
}

int Solution(int num){
    
    unordered_map<string,int> hands = getInputMap();
    multimap<vector<int>,int> rankedHands;
    
    for(auto& hand : hands){
        vector<int> key;
        if(num == 1){
            key.push_back(getType1(hand.first));
        }
        if(num == 2){
            key.push_back(getType2(hand.first));
        }
        for(char card : hand.first){
            if(isdigit(card) != 0){
                key.push_back(card - '0');
            }
            else{
                if(num == 1) key.push_back(getFaceCard1(card));
                if(num == 2) key.push_back(getFaceCard2(card));
            }
        }
        rankedHands.insert(pair<vector<int>, int> (key, hand.second));
    }
    
    int sum = 0;
    size_t i = 0;
    for(auto& hand : rankedHands){
        sum += hand.second * ++i;
    }
    
    return sum;
}


int main() {
    
    cout << "Solution to the 1st question is: "<<Solution(1)<<endl;
    cout << "Solution to the 2nd question is: "<<Solution(2)<<endl;
    return 0;
}
