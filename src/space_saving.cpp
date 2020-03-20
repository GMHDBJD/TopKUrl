#include "heap.h"
#include <fstream>
#include <iostream>

using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;

constexpr size_t kTopK = 100;
constexpr size_t kD = 3200;

void spaceSaving(string filename, size_t d)
{
    ifstream fin(filename);
    string url;
    Heap heap;
    vector<pair<size_t, string>> result;

    while (fin >> url)
    {
        if (!heap.increase(url))
        {
            if (heap.size() < d)
            {
                heap.push(make_pair(1, url));
            }
            else
            {
                auto min_val = heap.pop();
                heap.push(make_pair(min_val.first + 1, url));
            }
        }
    }
    while (heap.size() > kTopK)
    {
        heap.pop();
    }

    while (!heap.empty() && result.size() < kTopK)
    {
        result.push_back(heap.pop());
    }

    ofstream fout("space_saving/result/result.out");
    for (int i = result.size() - 1; i >= 0; --i)
        fout << result[i].second << ' ' << result[i].first << endl;
}

int main()
{
    system("rm -rf ./space_saving");
    system("mkdir space_saving space_saving/result");

    clock_t t;

    t = clock();
    cout << "sapce save..." << endl;

    spaceSaving("data/data.in", kD);

    t = clock() - t;
    cout << "time taken in space save: " << t / CLOCKS_PER_SEC << " seconds" << endl;
}
