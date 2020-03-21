#include <random>
#include <fstream>
#include <vector>
#include <iostream>

using std::cout;
using std::discrete_distribution;
using std::endl;
using std::ifstream;
using std::mt19937;
using std::ofstream;
using std::string;
using std::vector;

constexpr size_t kFileSize = 10ULL * 1024 * 1024 * 1024;
const string kInFilename = "gen_data/top500.in";
const string kOutFilename = "data/data.in";

/*
generate random url
*/
string
randomUrl()
{
    string s;
    for (int i = 0; i < 10; ++i)
        s += rand() % 26 + 'a';
    s += ".error";
    return s;
}

int main()
{
    system("rm -rf ./data");
    system("mkdir data");

    vector<string> urls;
    vector<size_t> weights;
    mt19937 gen;
    string url;
    size_t i = 500;
    ifstream fin(kInFilename);
    ofstream fout(kOutFilename);

    while (fin >> url)
    {
        urls.push_back(url);    // urls: top500
        weights.push_back(i--); // weights: [500,499,...,1]
    }

    weights.push_back(1122750); // assume top500/total = 1%

    discrete_distribution<int> dist(weights.begin(), weights.end());
    gen.seed(time(nullptr));
    size_t cur = 0;
    while (cur < kFileSize)
    {
        int pos = dist(gen);
        if (pos == 500)
        {
            url = randomUrl();
        }
        else
        {
            url = urls[pos];
        }
        cur += url.size();
        fout << url << endl;
    }
}
