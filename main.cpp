#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "heap.h"
#include "MinMedianMaxSketch.h"
using namespace std;

template <typename T>
bool compare(T a, T b) { return a < b; }

int main(int argc, char *argv[])
{
    string word;
    string type_implement = argv[1];

    vector<int> insert_vec;
    vector<int> remove_vec;

    ifstream f_insert(argv[2]);
    ifstream remove(argv[3]);

    if (type_implement == "heap")
    {
    }
    if (type_implement == "minmedianmax")
    {
        // myfile.open();
        while (getline(f_insert, word))
        {
            insert_vec.push_back(stoi(word));
        }
        f_insert.close();
        sort(insert_vec.begin(), insert_vec.end());
        int mid = insert_vec.size() / 2;
        cout << insert_vec.size();
        vector<int> minheap = {insert_vec.begin() + mid, insert_vec.end()};
        //vector<int> maxheap = {insert_vec.begin(), insert_vec.begin() + mid - 1};
        cout << minheap.size();

        // while (getline(myfile2, el))
        // {
        //     remove_vec.push_back(el);
        // }
        // myfile.close();
    }
}
