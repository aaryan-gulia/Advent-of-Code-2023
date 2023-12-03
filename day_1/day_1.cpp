//
//  main.cpp
//  aoc_1
//
//  Created by Aaryan Gulia on 02/12/2023.
//

#include <iostream>
#include <fstream>
#include <string>
#include <set>

using namespace std;

unordered_map<string, string> makeNumMap(){
    unordered_map<string, string> myMap;

    // Add key-value pairs
    myMap["zero"] = "0";
    myMap["one"] = "1";
    myMap["two"] = "2";
    myMap["three"] = "3";
    myMap["four"] = "4";
    myMap["five"] = "5";
    myMap["six"] = "6";
    myMap["seven"] = "7";
    myMap["eight"] = "8";
    myMap["nine"] = "9";

    return myMap;
}

vector<string> getKeys(unordered_map<string, string> myMap){
    vector<string> keys;
    transform(myMap.begin(), myMap.end(), back_inserter(keys), [](auto pair){return pair.first;});
    return keys;
}

int Solution1(){
    fstream newfile;
    newfile.open("input.txt",ios::in); //open a file to perform read operation using file object
    int sum = 0;
    if (newfile.is_open()){ //checking whether the file is open
        string input;
        while(getline(newfile, input)){ //read data from file object and put it into string.
            size_t first_int = input.find_first_of("123456789");
            size_t last_int = input.find_last_of("123456789");
            string first = input.substr(first_int, 1);
            string last = input.substr(last_int, 1);
            int num = 10 * stoi(first) + stoi(last);
            sum += num;
        }
        newfile.close(); //close the file object.
        return sum;
    }
    else{
        throw runtime_error("FILE DID NOT OPEN");
    }
    return sum;
    
}

int Solution2(){
    fstream newfile;
    newfile.open("input.txt",ios::in); //open a file to perform read operation using file object
    unordered_map<string, string> numMap = makeNumMap();
    vector<string> keys = getKeys(numMap);
    int sum = 0;
    
    if (newfile.is_open()){ //checking whether the file is open
        string input;
        while(getline(newfile, input)){ //read data from file object and put it into string.
            size_t first_int = input.find_first_of("123456789");
            size_t last_int = input.find_last_of("123456789");
            
            
            vector<vector<size_t>> positions;
            set<vector<size_t>> lastPositions;
            transform(keys.begin(), keys.end(),back_inserter(positions), [input](string key){ return
                vector<size_t> {input.find(key), input.find(key) + key.size()};});
            vector<size_t> firstCharInt = *(min_element(positions.begin(), positions.end()));
            string firstStringInt;
            if(firstCharInt[0] < input.size())
                firstStringInt = input.substr(firstCharInt[0], firstCharInt[1] - firstCharInt[0]);
            
            
            transform(keys.begin(), keys.end(),inserter(lastPositions, lastPositions.begin()), [input](string key){ return
                vector<size_t> {input.rfind(key), input.rfind(key) + key.size()};});
            vector<size_t> lastCharInt;
            if((*(min_element(lastPositions.begin(), lastPositions.end())))[0] < input.size())
                lastCharInt = *(--(lastPositions.lower_bound(vector<size_t> {input.size(), 0})));
            else
                lastCharInt = *((lastPositions.lower_bound(vector<size_t> {input.size(), 0})));
            string lastStringInt;
            if(lastCharInt[0] < input.size())
                lastStringInt = input.substr(lastCharInt[0], lastCharInt[1] - lastCharInt[0]);
            else
                lastCharInt[0] = 0;
            
            
            string first = (first_int < firstCharInt[0]? input.substr(first_int, 1) : numMap[firstStringInt]);
            
            string last = (last_int >= lastCharInt[0]? input.substr(last_int, 1) : numMap[lastStringInt]);

            int num = 10 * stoi(first) + stoi(last);
            sum += num;
        }
        newfile.close(); //close the file object.
    }
    else{
        throw runtime_error("FILE DID NOT OPEN");
    }
    return sum;
}

int main(){
    
    cout<<"Answer for 1st part: "<< Solution1()<<"\n";
    cout<<"Answer for 2nd part: "<< Solution2()<<"\n";
    
    return 0;
}
