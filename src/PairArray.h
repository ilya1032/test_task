#ifndef TEST_TASK_PAIRARRAY_H
#define TEST_TASK_PAIRARRAY_H

#include <iostream>
#include <utility>
#include <deque>
#include "Container.h"

template<class Key, class Data>
class PairArray : public Container<Key, Data> {
public:
    PairArray() {
        size = 0;
        max_size = 100;
        pair_array = new std::pair<Key, Data>[max_size];
        topn_array = nullptr;
    }

    ~PairArray() {
        if (!topn_array)
            delete[] topn_array;
        delete[] pair_array;
    }

    void add(Key price, Data amount) {
        if (size == 0) {
            pair_array[0] = std::make_pair(price, amount);
            size++;
            return;
        }
        long long index = binarySearch(pair_array, 0, size, price);
        if (index != -1) {
            pair_array[index].second = amount;
            return;
        }
        if (size == max_size)
            resize();
        for (index = size; (pair_array[index - 1].first < price) && (index > 0); index--)
            pair_array[index] = pair_array[index - 1];
        pair_array[index] = std::make_pair(price, amount);
        size++;
    }

    void remove(Key price) {
        long long index = 0;
        while (pair_array[index].first != price) {
            if (index == size)
                return;
            index++;
        }
        for (; index < size - 1; index++)
            pair_array[index] = pair_array[index + 1];
        size--;
    }

    std::pair<Key, Data> get_first() {
        if (this->size) {
            return pair_array[0];
        } else {
            return std::make_pair(-1, -1);
        }
    }

    Data get(Key price) {
        long long index = binarySearch(pair_array, 0, size, price);
        if (index != -1) {
            return pair_array[index].second;
        } else {
            return 0;
        }

    }

    std::pair<Key, Data> *topn(long long n) {
        delete[] topn_array;
        if (n > size) {
            this->set_topn_size(size);
        } else {
            this->set_topn_size(n);
        }
        topn_array = new std::pair<Key, Data>[this->get_topn_size()];
        for (long long i = 0; i < this->get_topn_size(); i++)
            topn_array[i] = pair_array[i];
        return topn_array;
    }

    unsigned long long get_sum_amount() {
        long long index = 0;
        unsigned long long sum = 0;
        while (index != size) {
            sum += pair_array[index++].second;
        }
        return sum;
    }


    long long binarySearch(std::pair<long long, long long> arr[], long long low, long long high, long long key) {
        size_t first = low;
        size_t last = high;

        while (first < last) {
            size_t mid = first + (last - first) / 2;

            if (key <= arr[mid].first)
                last = mid;
            else
                first = mid + 1;
        }

        if (last < size && arr[last].first == key) {
            return last;
        } else {
            return -1;
        }

//        if (high < low)
//            return -1;
//        long long mid = (low + high) / 2; /*low + (high - low)/2;*/
//        if (key == arr[mid].first)
//            return mid;
//        if (key > arr[mid].first)
//            return binarySearch(arr, (mid + 1), high, key);
//        return binarySearch(arr, low, (mid - 1), key);
    }

    long long get_size() { return size; }

    void print() {
        for (int i = 0; i < size; i++)
            std::cout << pair_array[i].first << ' ';
        std::cout << '\n';
    }

private:
    long long size;
    long long max_size;
    int delta = 100;
    std::pair<Key, Data> *pair_array;
    std::pair<Key, Data> *topn_array;

    void resize() {
        max_size += delta;
        auto temp = new std::pair<long long, long long>[max_size];
        for (long long i = 0; i < size; i++)
            temp[i] = pair_array[i];
        delete pair_array;
        pair_array = temp;
        temp = nullptr;
    }
};


#endif //TEST_TASK_PAIRARRAY_H
