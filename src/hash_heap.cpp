#include "hashing_heap.h"
#include "heap.h"
#include "stream.h"
#include <fstream>
#include <iostream>
#include <functional>
#include <unordered_map>
#include <cstdlib>
#include <queue>
#include <algorithm>

using std::cout;
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
constexpr size_t kShardingNums = 500;
constexpr size_t kTopK = 100;

/*
sharding file to small file by hash
*/
void sharding(const string &filename, size_t sharding_nums)
{
    Stream fin(filename);
    Stream fouts[kShardingNums];
    for (int i = 0; i < kShardingNums; ++i)
    {
        fouts[i].open("hash_heap/sharding/" + to_string(i) + ".out", "w");
    }
    string url;
    while (fin >> url)
    {
        size_t num = hash<string>{}(url) % sharding_nums;
        fouts[num] << url << "\n";
    }
    return;
}

/*
count url in small file and write TopK to result
*/
void mapReduce(size_t sharding_nums)
{
    Heap heap;
    unordered_map<string, size_t> hashtable;
    for (int i = 0; i < sharding_nums; i++)
    {
        Stream fin("hash_heap/sharding/" + to_string(i) + ".out");
        string url;
        while (fin >> url)
            hashtable[url]++;

        for (auto i : hashtable)
        {
            heap.push(make_pair(i.second, i.first));
            if (heap.size() > kTopK)
                heap.pop();
        }

        hashtable.clear();
    }
    vector<pair<size_t, string>> result;
    while (!heap.empty())
    {
        result.push_back(heap.pop());
    }
    ofstream fout("hash_heap/result/result.out");
    for (int i = result.size() - 1; i >= 0; --i)
        fout << result[i].second << ' ' << result[i].first << endl;
}

int main()
{
    system("rm -rf ./hash_heap");
    system("mkdir hash_heap hash_heap/sharding hash_heap/result");

    clock_t t;

    t = clock();
    cout << "sharding..." << endl;

    sharding(filename, kShardingNums);

    t = clock() - t;
    cout << "time taken in sharding: " << t / CLOCKS_PER_SEC << " seconds" << endl;

    cout << "map reduce..." << endl;
    t = clock();

    mapReduce(kShardingNums);

    t = clock() - t;
    cout << "time taken in map reduce: " << t / CLOCKS_PER_SEC << " seconds" << endl;
}