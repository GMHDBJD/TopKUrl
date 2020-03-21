#include <fstream>
#include <functional>
#include <bitset>
#include <random>
#include <iostream>

#include "count_min_sketch.h"
#include "heap.h"

using std::cout;
using std::endl;
using std::hash;
using std::ifstream;
using std::make_pair;
using std::min;
using std::minstd_rand;
using std::ofstream;
using std::pair;
using std::string;
using std::vector;

constexpr size_t kD = 10;
constexpr size_t kM = 1000000;
constexpr size_t kTopK = 100;

void countMinSketch(string filename, size_t d, size_t m)
{
    vector<vector<size_t>> sketch(d, vector<size_t>(m));
    ifstream fin(filename);
    string url;
    Heap heap;
    vector<pair<size_t, string>> result;

    while (fin >> url)
    {
        /*
            hash(url) as seed
            generate d random value
        */
        minstd_rand ran(hash<string>{}(url));
        size_t min_val = -1;
        for (int i = 0; i < d; i++)
        {
            min_val = min(min_val, ++sketch[i][ran() % m]);
        }

        if (heap.size() < kTopK)
        {
            if (!heap.increase(url))
            {
                heap.push(make_pair(min_val, url));
            }
        }
        else
        {
            if (min_val > heap.front().first)
            {
                if (!heap.increase(url))
                {
                    heap.pop();
                    heap.push(make_pair(min_val, url));
                }
            }
        }
    }

    while (!heap.empty())
    {
        result.push_back(heap.pop());
    }

    ofstream fout("count_min_sketch/result/result.out");
    for (int i = result.size() - 1; i >= 0; --i)
        fout << result[i].second << ' ' << result[i].first << endl;
}

int main()
{
    system("rm -rf ./count_min_sketch");
    system("mkdir count_min_sketch count_min_sketch/result");
    clock_t t;

    t = clock();
    cout << "count min sketch..." << endl;

    countMinSketch("data/data.in", kD, kM);

    t = clock() - t;
    cout << "time taken in count min sketch: " << t / CLOCKS_PER_SEC << " seconds" << endl;
}
