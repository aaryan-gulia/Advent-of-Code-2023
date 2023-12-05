//
//  main.cpp
//  day_4
//
//  Created by Aaryan Gulia on 05/12/2023.
//

#include <iostream>
#include <fstream>
#include<numeric>

using namespace std;

vector<int> breakString(string entry){
    vector<int> num_vec;
    while(true){
        size_t firstDig = entry.find_first_of("1234567890");
        if(firstDig == -1) break;
        entry = entry.substr(firstDig , entry.size() - firstDig);
        firstDig = entry.find_first_of("1234567890");
        size_t lastDig = entry.find_first_of(" ");
        if(lastDig == -1) lastDig = entry.size();
        string num = entry.substr(firstDig, lastDig - firstDig);
        num_vec.push_back(stoi(num));
        entry = entry.substr(lastDig + 1 , entry.size() - lastDig);
    }
    return num_vec;
}

int Solution1(vector<vector<int>> win_vec, vector<vector<int>> my_vec){
    vector<int> my_wins (win_vec[0].size() + my_vec[0].size());
    unsigned int sum = 0;
    for(int i = 0; i < win_vec.size(); i++){
        unsigned int prod = 0;
        sort(win_vec[i].begin(),win_vec[i].end());
        sort(my_vec[i].begin(), my_vec[i].end());
        auto last_win = set_intersection(win_vec[i].begin(), win_vec[i].end(), my_vec[i].begin(), my_vec[i].end(), my_wins.begin());
        if (my_wins.begin() != last_win)
            prod = pow(2, last_win - my_wins.begin() - 1);
        sum += prod;
    }
    return sum;
}

int Solution2(vector<vector<int>> win_vec, vector<vector<int>> my_vec){
    vector<int> my_wins (win_vec[0].size() + my_vec[0].size());
    vector<size_t> instances (win_vec.size(),1);
    unsigned int sum = 0;
    for(int i = 0; i < win_vec.size(); i++){
        sort(win_vec[i].begin(),win_vec[i].end());
        sort(my_vec[i].begin(), my_vec[i].end());
        auto last_win = set_intersection(win_vec[i].begin(), win_vec[i].end(), my_vec[i].begin(), my_vec[i].end(), my_wins.begin());
        
        size_t num_wins = (last_win - my_wins.begin());
        size_t copies = instances[i];
        
        for(int j = 1; j <= num_wins; j++){
            instances[i + j] += copies;
        }
    }
    sum = accumulate(instances.begin(), instances.end(), 0);
    
    return sum;
}

int main() {
    
    fstream inputFile;
    inputFile.open("input.txt", ios::in);
    vector<vector<int>> win_vec;
    vector<vector<int>> my_vec;
    
    if (inputFile.is_open()){
        string line;
        while(getline(inputFile, line)){
            size_t start_win = line.find(":");
            size_t end_win = line.find("|");
            string win_str = line.substr(start_win, end_win - start_win);
            string my_str = line.substr(end_win + 1, line.size() - end_win - 1);
            my_str.append(" ");
            win_vec.push_back(breakString(win_str));
            my_vec.push_back(breakString(my_str));
        }

        inputFile.close();
    }
    
    else{
        throw runtime_error("FILE DID NOT OPEN");
    }
    
    cout<<"Solution for 1st Question is: " << Solution1(win_vec, my_vec) << endl;
    cout<<"Solution for 2nd Question is: " << Solution2(win_vec, my_vec) << endl;
    
    return 0;
    
}
