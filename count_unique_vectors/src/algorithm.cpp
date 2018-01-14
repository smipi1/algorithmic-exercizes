#include <iostream>
#include <map>
#include "algorithm.h"

using namespace std;

int abs_gcd(int a, int b) {
    if(a < 0)
        a = -a;
    if(b < 0)
        b = -b;
    while(a != b) {
        if(a > b) {
            a = a - b;
        } else {
            b = b - a;
        }
    }
    return a;
}

vector<int> toReducedVector(Point const& p)
{
    if(p.x == 0) {
        if(p.y > 0)
            return { 0, 1 };
        else
            return { 0, -1 };
    } else if(p.y == 0) {
        if(p.x > 0)
            return { 1, 0 };
        else
            return { -1, 0 };
    } else {
        int gcd = abs_gcd(p.x, p.y);
        return { p.x / gcd, p.y / gcd};
    }
}

int count_unique_vectors(vector<Point> const& positions)
{
    map<vector<int>, int> uniqueReducedVectors;

    for(auto iter: positions) {
        auto const v = toReducedVector(iter);
        uniqueReducedVectors[v]++;
    }
    return uniqueReducedVectors.size();
}
