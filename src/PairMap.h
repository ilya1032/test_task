//
// Created by ilya1032 on 11.06.19.
//

#ifndef TEST_TASK_PAIRMAP_H
#define TEST_TASK_PAIRMAP_H

#include <utility>
#include <map>
#include "Container.h"

template<class Key, class Data>
class PairMap : public Container<Key, Data> {
public:
    PairMap() {
        pair_map = new std::map<long long, long long>();
        topn_array = nullptr;
    }

    ~PairMap() {
        if (!topn_array)
            delete[] topn_array;
        delete pair_map;
    }

    void add(Key price, Data amount) {
        auto temp = pair_map->find(price);
        if (temp == pair_map->end()) {
            pair_map->insert(std::make_pair(price, amount));
            return;
        } else {
            pair_map->at(price) = amount;
            return;
        }
    }

    void remove(Key price) {
        if (!pair_map->count(price))
            return;
        pair_map->erase(price);
    }

    std::pair<Key, Data> get_first() {
        return *(pair_map->rbegin());
    }

    Data get(Key price) {
        auto temp = pair_map->find(price);
        if (temp != pair_map->end())
            return pair_map->find(price)->second;
        else
            return 0;
    }

    unsigned long long get_sum_amount() {
        long long sum = 0;
        for (auto iter = pair_map->begin(); iter != pair_map->end(); iter++)
            sum += iter->second;
        return sum;
    }

    std::pair<Key, Data> *topn(long long n) {
        delete[] topn_array;
        if (n > pair_map->size()) {
            this->set_topn_size(pair_map->size());
        } else {
            this->set_topn_size(n);
        }
        long long size = this->get_topn_size();
        topn_array = new std::pair<long long, long long>[size];
        auto iter = pair_map->rbegin();
        for (int i = 0; i < size; i++)
            topn_array[i] = *(iter++);
        return topn_array;
    }

private:
    std::map<Key, Data> *pair_map;
    std::pair<Key, Data> *topn_array;
};


#endif //TEST_TASK_PAIRMAP_H
