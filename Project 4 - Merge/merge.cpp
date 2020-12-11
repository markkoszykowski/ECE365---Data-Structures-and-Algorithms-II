/*
        Mark Koszykowski
        ECE365 - DSA II
        Programming Assignment 4
*/

#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

bool mat[1001][1001];

void merge(const string &A, const string &B, string &C, ofstream &output);

int main() {
        string inFile, outFile;
        string A, B, C;

        cout << "Enter name of input file: ";
        cin >> inFile;

        cout << "Enter name of output file: ";
        cin >> outFile;

        ifstream input (inFile);
        ofstream output (outFile);

        while(getline(input, A) && getline(input, B) && getline(input, C)) {
                merge(A, B, C, output);
        }

        return 0;
}

void merge(const string &A, const string &B, string &C, ofstream &output) {
        memset(mat, false, sizeof(mat));

        string cCopy = C;

        int m = A.length();
        int n = B.length();
        
        if(m + n != C.length()) {
                output << "*** NOT A MERGE ***" << endl;
                return;
        }
        
        for(int i = 0; i <= m; i++) {
                for(int j = 0; j <= n; j++) {
                        if(i == 0 && j == 0) {
                                mat[i][j] = true;
                        }
                        else if(i == 0) {
                                if(B.at(j - 1) == C.at(j - 1)) {
                                        mat[i][j] = mat[i][j - 1];
                                }
                        }
                        else if(j == 0) {
                                if(A.at(i - 1) == C.at(i - 1)) {
                                        mat[i][j] = mat[i - 1][j];
                                }
                        }
                        else if(A.at(i - 1) == C.at(i + j - 1) && B.at(j - 1) != C.at(i + j - 1)) {
                                mat[i][j] = mat[i - 1][j];
                        }
                        else if(A.at(i - 1) != C.at(i + j - 1) && B.at(j - 1) == C.at(i + j - 1)) {
                                mat[i][j] = mat[i][j - 1];
                        }
                        else if(A.at(i - 1) == C.at(i + j - 1) && B.at(j - 1) == C.at(i + j - 1)) {
                                mat[i][j] = mat[i - 1][j] || mat[i][j - 1];
                        }
                }
        }
        
        if(mat[m][n]) {
                int j = n;
                for(int i = m; i > 0; i--) {
                        while(1) {
                                if(mat[i][j] && (j == 0 || !mat[i][j - 1])) {
                                        C.at(i + j - 1) -= 32;
                                        break;
                                }
                                j -= 1;
                        }
                }                                        
                output << C << endl;
        }
        else {
                output << "*** NOT A MERGE ***" << endl;
        }
        return;
}
