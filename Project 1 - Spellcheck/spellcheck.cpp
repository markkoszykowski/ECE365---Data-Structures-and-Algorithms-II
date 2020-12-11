/*
        Mark Koszykowski
        ECE365 - DSA II
        Programming Assignment 1
*/

#include "hash.h"
#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <algorithm>
#include <cstring>

using namespace std;

void loadDict(hashTable* myDict, const string &dict);
void spellCheck(hashTable* myDict, const string &input, const string &output);

int main() {
        string dict, input, output;
        clock_t t1, t2;
        hashTable* myDict = new hashTable(50000);

        cout << "Enter name of dictionary: " << flush;
        cin >> dict;

        t1 = clock();
        loadDict(myDict, dict);
        t2 = clock();

        cout << "Total time (in seconds) to load dictionary: " << double(t2 - t1) / CLOCKS_PER_SEC << endl;

        cout << "Enter name of input file: " << flush;
        cin >> input;
        cout << "Enter name of output file: " << flush;
        cin >> output;

        t1 = clock();
        spellCheck(myDict, input, output);
        t2 = clock();

        cout << "Total time (in seconds) to check document: " << double(t2 - t1) / CLOCKS_PER_SEC << endl;

        return 0;
}

void loadDict(hashTable* myDict, const string &dict) {
        ifstream Dictionary;
        Dictionary.open(dict);
        
        if(Dictionary.is_open()) {
                string word;
                while(getline(Dictionary, word)) {
                        transform(word.begin(), word.end(), word.begin(), ::tolower);
                        myDict->insert(word);
                }
        }
        else {
                cerr << "Error: failed to open " << dict << " for reading: " << strerror(errno) << endl;
                exit(-1);
        }
}

void spellCheck(hashTable* myDict, const string &input, const string &output) {
        ifstream Input;
        Input.open(input);
        if(!(Input.is_open())) {
                cerr << "Error: failed to open " << input << " for reading: " << strerror(errno) << endl;
                exit(-1);
        }

        ofstream Output;
        Output.open(output);
        if(!(Output.is_open())) {
                cerr << "Error: failed to open " << output << " for reading: " << strerror(errno) << endl;
                exit(-1);
        }

        int lineNum = 0;
        bool hasNum = false;
        string line;

        while(getline(Input, line)) {
                string buf = "";
                ++lineNum;
                for(int i = 0; i < (line.length() + 1); i++) {
                        char c = tolower(line[i]);
                        if((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c == 39) || (c == 45)) {
                                buf.push_back(c);
                                if(c >= '0' && c <= '9') {
                                        hasNum = true;
                                }
                        }
                        else {
                                if(buf != "") {
                                        if(buf.length() > 20) {
                                                Output << "Long word at line " << lineNum << ", starts: " << buf.substr(0, 20) << endl;
                                        }
                                        else if(hasNum == false && !(myDict->contains(buf))) {
                                                Output << "Unknown word at line " << lineNum << ": " << buf << endl;
                                        }
                                }
                                buf = "";
                                hasNum = false;
                        }
                }
        }

        Input.close();
        Output.close();
}
