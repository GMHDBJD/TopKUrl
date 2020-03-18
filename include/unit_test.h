
#ifndef UNIT_TEST_HPP_
#define UNIT_TEST_HPP_

#include "hashing_heap.h"

#include <iostream>
#include <fstream>

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
    void mapTest()
    {
        map(5);
    }
    void reduceTest()
    {
        reduce();
    }
};
} // namespace unittest

#endif