
#ifndef UNIT_TEST_HPP_
#define UNIT_TEST_HPP_

#include "hashing_heap.h"
#include "count_min_sketch.h"
#include "heap.h"
#include "space_saving.h"

#include <iostream>

using std::cout;
using std::endl;

namespace unittest
{
class Test
{

private:
    string filename = "data/data.in";

public:
    void shardingTest()
    {
        sharding(filename, 5);
    }
    void mapReduceTest()
    {
        mapReduce(5);
    }

    void countMinSketchTest()
    {
        countMinSketch("data/data.in", 5, 100);
    }

    void heapTest()
    {
        Heap heap;

        heap.push({1, "aaaa"});
        heap.push({1, "bbbb"});
        heap.push({1, "cccc"});
        heap.push({1, "dddd"});

        auto temp = heap.pop();
        cout << temp.first << " " << temp.second << endl;

        cout << heap.size() << endl;

        cout << heap.increase("aaaa") << endl;
        cout << heap.increase("bbbb") << endl;
        cout << heap.increase("bbbb") << endl;
        cout << heap.increase("cccc") << endl;
        cout << heap.increase("bbbb") << endl;
        cout << heap.increase("bbbb") << endl;
        cout << heap.increase("cccc") << endl;

        temp = heap.pop();
        cout << temp.first << " " << temp.second << endl;

        heap.push({1, "aaaa"});
        temp = heap.pop();
        cout << temp.first << " " << temp.second << endl;

        cout << heap.increase("cccc") << endl;
        cout << heap.increase("cccc") << endl;
        cout << heap.increase("cccc") << endl;
        cout << heap.increase("cccc") << endl;

        temp = heap.pop();
        cout << temp.first << " " << temp.second << endl;
        temp = heap.pop();
        cout << temp.first << " " << temp.second << endl;
    }

    void spaceSavingTest()
    {
        spaceSaving("data/data.in", 100);
    }
};
} // namespace unittest

#endif