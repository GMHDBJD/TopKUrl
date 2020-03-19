#ifndef HEAP_H_
#define HEAP_H_

#include <vector>
#include <map>
#include <algorithm>
#include <utility>

using std::map;
using std::pair;
using std::push_heap;
using std::string;
using std::swap;
using std::vector;

class Heap
{
private:
    vector<pair<string, size_t>> data_;
    map<string, size_t> hashtable_;

    void fixHeap(size_t pos)
    {

        if (pos < data_.size() / 2)
        {
            size_t left_pos = pos * 2 + 1;
            size_t right_pos = left_pos + 1;
            size_t next_pos = pos;
            if (left_pos < data_.size() && data_[left_pos].second < data_[next_pos].second)
                next_pos = left_pos;
            if (right_pos < data_.size() && data_[right_pos].second < data_[next_pos].second)
                next_pos = right_pos;
            if (next_pos != pos)
            {
                swap(hashtable_[data_[pos].first], hashtable_[data_[next_pos].first]);
                swap(data_[pos], data_[next_pos]);
                return fixHeap(next_pos);
            }
        }
    }

public:
    void push(const pair<string, size_t> &p)
    {
        data_.push_back(p);
        size_t pos = data_.size() - 1;
        hashtable_[p.first] = pos;
        size_t parent_pos = (pos + 1) / 2 - 1;
        while (pos > 0 && data_[parent_pos].second > data_[pos].second)
        {
            swap(hashtable_[data_[pos].first], hashtable_[data_[parent_pos].first]);
            swap(data_[pos], data_[parent_pos]);
            pos = parent_pos;
            parent_pos = (pos + 1) / 2 - 1;
        }
    }

    bool increase(string key)
    {
        auto iter = hashtable_.find(key);
        if (iter != hashtable_.end())
        {
            ++data_[iter->second].second;
            fixHeap(iter->second);
            return true;
        }
        else
        {
            return false;
        }
    }

    size_t size() const
    {
        return data_.size();
    }

    pair<string, size_t> pop()
    {
        auto front = data_.front();
        auto back = data_.back();
        data_[0] = back;
        hashtable_[back.first] = 0;
        hashtable_.erase(front.first);
        data_.pop_back();
        fixHeap(0);
        return front;
    }

    bool empty() const
    {
        return data_.empty();
    }

    const pair<string, size_t> &front() const
    {
        return data_.front();
    }

};

#endif