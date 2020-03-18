#ifndef HASHING_PRIORITY_QUEUE_H_
#define HASHING_PRIORITY_QUEUE_H_

#include <string>
using std::string;

void sharding(const string &filename, int sharding_nums);

void map(int sharding_nums);

void reduce();

#endif