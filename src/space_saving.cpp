#include "heap.h"
#include <fstream>

using std::endl;
using std::ifstream;
using std::ofstream;

constexpr size_t kTopK = 100;

void spaceSaving(string filename, size_t d)
{
    ifstream fin(filename);
    string url;
    Heap heap;
    vector<pair<string, size_t>> result;

    while (fin >> url)
    {
        if (!heap.increase(url))
        {
            if (heap.size() < d)
            {
                heap.push(make_pair(url, 1));
            }
            else
            {
                auto min_val = heap.pop();
                heap.push(make_pair(url, min_val.second + 1));
            }
        }
    }

    while (!heap.empty() && result.size() < kTopK)
    {
        result.push_back(heap.pop());
    }

    ofstream fout("space_saving/result/result.out");
    for (int i = result.size() - 1; i >= 0; --i)
        fout << result[i].first << ' ' << result[i].second << endl;
}

int main()
{
    system("rm -rf ./space_saving");
    system("mkdir space_saving space_saving/result");
    spaceSaving("data/data.in", kTopK);
}