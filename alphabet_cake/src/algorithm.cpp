/*
 * algorithm.cpp
 *
 *  Created on: 10 Jan 2018
 *      Author: smipi1
 */

#include "algorithm.h"

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void fill(string& row, int start, int end, char letter)
{
    for(int c = start; c <= end; c++) {

    }
}

bool isEmptyRow(int firstLetterIdx, const int nrows)
{
    return firstLetterIdx == nrows;
}

void fill_cake(int const nrows, int const ncols, vector<string> &rows)
{
    int firstRowIdx = nrows;
    int prevRowIdx = nrows;
    for(int row = 0; row < nrows; row++) {
        int firstLetterIdx = nrows;
        char firstLetter = 0;
        char prevLetter = 0;
        for(int col = 0; col < ncols; col++) {
            auto const letter = rows[row][col];
            if(letter != '?') {
                if(col < firstLetterIdx) {
                    firstLetter = letter;
                    firstLetterIdx = col;
                }
                prevLetter = letter;
            } else if(prevLetter) {
                rows[row][col] = prevLetter;
            }
        }
        if(isEmptyRow(firstLetterIdx, nrows)) {
            if(prevRowIdx != nrows) {
                rows[row] = rows[prevRowIdx];
            }
            continue;
        }
        if(row < firstRowIdx) {
            firstRowIdx = row;
        }
        prevRowIdx = row;
        for(int col = 0; col < firstLetterIdx; col++) {
            rows[row][col] = firstLetter;
        }
    }
    for(int row = 0; row < firstRowIdx; row++) {
        rows[row] = rows[firstRowIdx];
    }
}

int main(int argc, char *argv[])
{
    int noTestCases;
    cin >> noTestCases;

    for(int n = 0; n < noTestCases; n++) {
        int nrows, ncols;
        cin >> nrows >> ncols;

        vector<string> rows;

        for(int r = 0; r < nrows; r++) {
            string row;
            cin >> row;
            rows.push_back(row);
        }

        cout << "Case #" << n+1 << endl;

        fill_cake(nrows, ncols, rows);

        for(auto r : rows) {
            cout << r << endl;
        }
    }
    return 0;
}
