#include "hashing_heap.h"
#include "heap.h"
#include <fstream>
#include <functional>
#include <unordered_map>
#include <cstdlib>
#include <queue>
#include <algorithm>

using std::endl;
using std::greater;
using std::hash;
using std::ifstream;
using std::ios;
using std::make_pair;
using std::ofstream;
using std::pair;
using std::string;
using std::to_string;
using std::unordered_map;
using std::vector;

const string filename = "data/data.in";
constexpr size_t kShardingNums = 5;
constexpr size_t kTopK = 100;

void sharding(const string &filename, size_t sharding_nums)
{
    ifstream fin(filename);
    string url;
    while (fin >> url)
    {
        size_t num = hash<string>{}(url) % sharding_nums;
        ofstream fout("hash_heap/sharding/" + to_string(num) + ".out", ios::out | ios::app);
        fout << url << endl;
    }
    return;
}

void mapReduce(size_t sharding_nums)
{
    Heap heap;
    unordered_map<string, size_t> hashtable;
    for (int i = 0; i < sharding_nums; i++)
    {
        ifstream fin("hash_heap/sharding/" + to_string(i) + ".out");
        if (!fin.is_open())
            continue;
        string url;
        while (fin >> url)
            hashtable[url]++;

        for (auto i : hashtable)
        {
            heap.push(i);
            if (heap.size() > kTopK)
                heap.pop();
        }

        hashtable.clear();
    }
    vector<pair<string, size_t>> result;
    while (!heap.empty())
    {
        result.push_back(heap.pop());
    }
    ofstream fout("hash_heap/result/result.out");
    for (int i = result.size() - 1; i >= 0; --i)
        fout << result[i].first << ' ' << result[i].second << endl;
}

int main()
{
    system("rm -rf ./hash_heap");
    system("mkdir hash_heap hash_heap/sharding hash_heap/result");
    sharding(filename, kShardingNums);
    mapReduce(kShardingNums);
}