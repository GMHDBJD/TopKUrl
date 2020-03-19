#include <fstream>
#include <functional>
#include <bitset>
#include <random>

#include "count_min_sketch.h"
#include "heap.h"

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

constexpr size_t kD = 5;
constexpr size_t kM = 100;
constexpr size_t kTopK = 100;

void countMinSketch(string filename, size_t d, size_t m)
{
    vector<vector<size_t>> sketch(d, vector<size_t>(m));
    ifstream fin(filename);
    string url;
    Heap heap;
    vector<pair<string, size_t>> result;

    while (fin >> url)
    {
        minstd_rand ran(hash<string>{}(url));
        size_t min_val = -1;
        for (int i = 0; i < d; i++)
        {
            min_val = min(min_val, ++sketch[i][ran() % m]);
        }

        if (!heap.size() == kTopK && heap.front().second >= min_val)
            continue;

        if (!heap.increase(url))
        {
            heap.push(make_pair(url, min_val));
        }
    }

    while (!heap.empty())
    {
        result.push_back(heap.pop());
    }

    ofstream fout("count_min_sketch/result/result.out");
    for (int i = result.size() - 1; i >= 0; --i)
        fout << result[i].first << ' ' << result[i].second << endl;
}

int main()
{
    system("rm -rf ./count_min_sketch");
    system("mkdir count_min_sketch count_min_sketch/result");
    countMinSketch("data/data.in", kD, kM);
}