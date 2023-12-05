//
//  main.cpp
//  day_5
//
//  Created by Aaryan Gulia on 05/12/2023.
//

#include <iostream>
#include <fstream>

using namespace std;

vector<long long> getSeedVec(){
    fstream inputFile;
    vector<long long> seedVec;
    inputFile.open("input.txt", ios::in);
    
    if (inputFile.is_open()){
        string line;
        while(getline(inputFile, line)){
            if(line.size() == 0) break;
            line.append(" ");
            while(true){
                size_t firstDig = line.find_first_of("1234567890");
                if(firstDig == -1) break;
                line = line.substr(firstDig , line.size() - firstDig);
                firstDig = line.find_first_of("1234567890");
                size_t lastDig = line.find_first_of(" ");
                if(lastDig == -1) lastDig = line.size();
                string num = line.substr(firstDig, lastDig - firstDig);
                seedVec.push_back(stoll(num));
                line = line.substr(lastDig + 1 , line.size() - lastDig);
            }
        }

        inputFile.close();
    }
    
    else{
        throw runtime_error("FILE DID NOT OPEN");
    }
    
    return seedVec;
}

unordered_map<string, vector<vector<long long>>> getMapVecs(){
    fstream inputFile;
    inputFile.open("input.txt", ios::in);
    unordered_map<string, vector<vector<long long>>> almanac;
    
    if (inputFile.is_open()){
        string line;
        string key;
        int lineNo = 1;
        while(getline(inputFile, line)){
            if (lineNo++ < 3) {
                continue;
            }
            if (line.size() == 0) {
                continue;
            }
            if (line.find(":") != string::npos){
                line  =  line.substr(0, line.find(" "));
                key = line;
                continue;
            }
            line.append(" ");
            vector<long long> currMap;
            while(true){
                size_t firstDig = line.find_first_of("1234567890");
                if(firstDig == string::npos) break;
                line = line.substr(firstDig , line.size() - firstDig);
                firstDig = line.find_first_of("1234567890");
                size_t lastDig = line.find_first_of(" ");
                if(lastDig == string::npos) lastDig = line.size();
                string num = line.substr(firstDig, lastDig - firstDig);
                currMap.push_back(stoll(num));
                line = line.substr(lastDig + 1 , line.size() - lastDig);
            }
            almanac[key].push_back(currMap);
            
        }

        inputFile.close();
    }
    
    else{
        throw runtime_error("FILE DID NOT OPEN");
    }
    
    return almanac;
}

long long getConversion(string conversion, long long fromNum, unordered_map<string, vector<vector<long long>>>  almanac){
    long long toNum = -1;
    vector<vector<long long>>& converter = almanac[conversion];
    
    for(vector<long long> range : converter){
        if(fromNum >= range[1] && fromNum < range[1] + range[2]){
            toNum = range[0] + (fromNum - range[1]);
            break;
        }
    }
    
    if(toNum == -1){
        toNum = fromNum;
    }
    
    return toNum;
}

long long Solution1(){
    long long minLoc = 9999999999;
    vector<long long> seeds = getSeedVec();
    unordered_map<string, vector<vector<long long>>>  almanac = getMapVecs();
    
    vector<string> conversions = {"seed-to-soil", "soil-to-fertilizer", "fertilizer-to-water", "water-to-light", "light-to-temperature", "temperature-to-humidity", "humidity-to-location"};
    
    for(long long seed: seeds){
        long long currNum = seed;
        for(string conversion: conversions){
            currNum = getConversion(conversion, currNum, almanac);
            if(conversion == "humidity-to-location"){
                minLoc = currNum < minLoc? currNum : minLoc;
            }
        }
    }
    return minLoc;
}

vector<vector<long long>> getConversion(string conversion, vector<vector<long long>> fromRanges, unordered_map<string, vector<vector<long long>>>  almanac){
    vector<vector<long long>>& converter = almanac[conversion];
    vector<vector<long long>> toRanges;
    for(int i = 0; i < fromRanges.size(); i++){
        auto range = fromRanges[i];
        bool copyRange = true;
        for(vector<long long> convertRange : converter){
            if(range[0] >= convertRange[1] && range[0] < convertRange[1] + convertRange[2]){
                if(range[1] < convertRange[1] + convertRange[2]){
                    vector<long long> toRange;
                    toRange.push_back(convertRange[0] + (range[0] - convertRange[1]));
                    toRange.push_back(convertRange[0] + (range[1] - convertRange[1]));
                    toRanges.push_back(toRange);
                }
                else{
                    vector<long long> toRange;
                    toRange.push_back(convertRange[0] + (range[0] - convertRange[1]));
                    toRange.push_back(convertRange[0] + (convertRange[1] + convertRange[2] - 1 - convertRange[1]));
                    toRanges.push_back(toRange);
                    range = {range[0] + convertRange[2], range[1]};
                }
                copyRange = false;
            }
            else if(convertRange[1] <= range[1] && convertRange[1] >= range[0]){
                if(range[1] < convertRange[1] + convertRange[2]){
                    vector<long long> toRange;
                    toRange.push_back(convertRange[0] + (convertRange[1] - convertRange[1]));
                    toRange.push_back(convertRange[0] + (range[1] - convertRange[1]));
                    toRanges.push_back(toRange);
                    range = {range[0], convertRange[1] - 1};
                }
                else{
                    vector<long long> toRange;
                    toRange.push_back(convertRange[0] + (convertRange[1] - convertRange[1]));
                    toRange.push_back(convertRange[0] + (convertRange[1] + convertRange[2] - 1 - convertRange[1]));
                    toRanges.push_back(toRange);
                    vector<long long> newRange = {convertRange[1] + convertRange[2], range[1]};
                    fromRanges.push_back(newRange);
                    range = {range[0], convertRange[1] - 1};
                }
                copyRange = false;
            }
        }
        if(copyRange){
            vector<long long> toRange;
            toRange.push_back(range[0]);
            toRange.push_back(range[1]);
            toRanges.push_back(toRange);
        }
    }
    return toRanges;
}

long long Solution2(){
    long long minLoc = 9999999999;
    vector<long long> seeds = getSeedVec();
    unordered_map<string, vector<vector<long long>>>  almanac = getMapVecs();
    
    vector<string> conversions = {"seed-to-soil", "soil-to-fertilizer", "fertilizer-to-water", "water-to-light", "light-to-temperature", "temperature-to-humidity", "humidity-to-location"};
    
    for(int i = 0; i < seeds.size(); i++){
        vector<vector<long long>> currRanges;
        currRanges.push_back(vector<long long>{seeds[i],seeds[i] + seeds[i+1] - 1});
        for(string conversion: conversions){
            currRanges = getConversion(conversion, currRanges, almanac);
            ;
        }
        for(vector<long long> range : currRanges){
            minLoc = range[0] < minLoc? range[0] : minLoc;
        }
        i++;
    }
    return minLoc;
}

int main() {
    
    cout<<"Solution for 1st Question is: " << Solution1() << endl;
    cout<<"Solution for 2nd Question is: " << Solution2() << endl;
    return 0;
    
}
