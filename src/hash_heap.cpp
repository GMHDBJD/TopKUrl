#include "hashing_heap.h"
#include <fstream>
#include <functional>
#include <unordered_map>
#include <cstdlib>
#include <queue>

using std::endl;
using std::greater;
using std::hash;
using std::ifstream;
using std::ios;
using std::make_pair;
using std::ofstream;
using std::pair;
using std::priority_queue;
using std::string;
using std::to_string;
using std::unordered_map;
using std::vector;

const string filename = "data/data.in";
constexpr int kShardingNums = 5;
constexpr int kTopK = 100;

void sharding(const string &filename, int sharding_nums)
{
    ifstream fin(filename);
    string url;
    while (fin >> url)
    {
        int num = hash<string>{}(url) % sharding_nums;
        ofstream fout("hash_heap/sharding/" + to_string(num) + ".out", ios::out | ios::app);
        fout << url << endl;
    }
    return;
}

void map(int sharding_nums)
{
    for (int i = 0; i < sharding_nums; i++)
    {
        ifstream fin("hash_heap/sharding/" + to_string(i) + ".out");
        if (!fin.is_open())
            continue;
        string url;
        unordered_map<string, int> hashtable;
        while (fin >> url)
            hashtable[url]++;
        ofstream fout("hash_heap/map/map.out", ios::out | ios::app);
        for (auto i : hashtable)
            fout << i.first << ' ' << i.second << endl;
    }
}

void reduce()
{
    ifstream fin("hash_heap/map/map.out");
    string url;
    int cnt;
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> heap;

    while (fin >> url >> cnt)
    {
        heap.push(make_pair(cnt, url));
        if (heap.size() > kTopK)
            heap.pop();
    }

    vector<pair<string, int>> result;
    while (!heap.empty())
    {
        result.push_back(make_pair(heap.top().second, heap.top().first));
        heap.pop();
    }

    ofstream fout("hash_heap/result/result.out");
    for (int i = result.size() - 1; i >= 0; --i)
        fout << result[i].first << ' ' << result[i].second << endl;
}

int main()
{
    system("rm -rf ./hash_heap");
    system("mkdir hash_heap hash_heap/sharding hash_heap/map hash_heap/result");
    sharding(filename, kShardingNums);
    map(kShardingNums);
    reduce();
}