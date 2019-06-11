#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <chrono>

#include "src/PairArray.h"
#include "src/AVLTree.h"
#include "src/PairMap.h"

using namespace std;

void RealTimeTest(Container<long long, long long> *container, string const &file_name) {
    srand(time(nullptr));

    ifstream input_files_array[4];
    ofstream output_files_array[4];

    long long price = 0;
    long long amount = 0;

    input_files_array[0].open("dataset1.log", ios::in);
    input_files_array[1].open("dataset2.log", ios::in);
    input_files_array[2].open("dataset3.log", ios::in);
    input_files_array[3].open("dataset4.log", ios::in);

    output_files_array[0].open("realtime_dataset1_" + file_name + ".log", ios::out);
    output_files_array[1].open("realtime_dataset2_" + file_name + ".log", ios::out);
    output_files_array[2].open("realtime_dataset3_" + file_name + ".log", ios::out);
    output_files_array[3].open("realtime_dataset4_" + file_name + ".log", ios::out);

    for (int i = 0; i < 4; i++)
        if (!input_files_array[i].is_open())// || !output_files_array[i].is_open())
            return;

    int count = 0;

    for (int i = 3; i < 4; i++) {
        while (!input_files_array[i].eof()) {
            input_files_array[i] >> price >> amount;
            if (amount) {
                count++;
                container->add(price, amount);
                output_files_array[i] << "first element of " << file_name << " : " << container->get_first().first << ' '
                                      << container->get_first().second << '\n';
                output_files_array[i] << "Total amount: " << container->get_sum_amount() << '\n';
                if ((count & 1) == 0)
                    output_files_array[i] << "Random price's amount: " << container->get(rand() % 1000000 + 1000000)
                                          << '\n';
                if (count % 20 == 0) {
                    auto topn_array = container->topn(10);
                    long long topn_size = container->get_topn_size();
                    output_files_array[i] << "top " << topn_size << " elements in " << file_name << " : ";
                    for (long long j = 0; j < topn_size; j++)
                        output_files_array[i]<< topn_array[j].first << ' '
                                              << topn_array[j].second << " | ";
                    output_files_array[i] << '\n';
                }
            } else
                container->remove(price);
        }
    }

    for (int i = 0; i < 4; i++) {
        input_files_array[i].close();
        output_files_array[i].close();
    }
}

void TimeTest(Container<long long, long long> *container, string const &file_name) {
    ifstream input_file;
    ofstream output_file;
    long long price;
    long long amount;

    input_file.open("dataset4.log", ios::in);
    output_file.open("time_test_dataset4_" + file_name + ".log", ios::out);

    if (!input_file.is_open() || !output_file.is_open())
        return;

    while (!input_file.eof()) {
        input_file >> price >> amount;
        if (amount)
            container->add(price, amount);
    }
    input_file.close();

    unsigned long long time = 0;
    for (int i = 0; i < 1000; i++) {
        chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
        container->get_first();
        chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
        time += chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();
    }
    output_file << time / 1000 << '\n';

    time = 0;
    for (int i = 0; i < 1000; i++) {
        chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
        container->get_sum_amount();
        chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
        time += chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();
    }
    output_file << time / 1000 << '\n';

    time = 0;
    for (int i = 0; i < 1000; i++) {
        chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
        container->get(rand() % 1000000 + 1000000);
        chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
        time += chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();
    }
    output_file << time / 1000 << '\n';

    for (unsigned int j = 2; j < 512; j <<= 1) {
        time = 0;
        for (int i = 0; i < 1000; i++) {
            chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
            container->topn(j);
            chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
            time += chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();
        }
        output_file << "j = " << j << " : " << time / 1000 << '\n';
    }

    output_file.close();

}


int main() {
    auto pair_array = new PairArray<long long, long long>();
    RealTimeTest(reinterpret_cast<Container<long long, long long> *>(pair_array), "array");
    delete pair_array;

    auto pair_map = new PairMap<long long, long long>();
    RealTimeTest(reinterpret_cast<Container<long long, long long> *>(pair_map), "map");
    delete pair_map;

    auto tree = new AVLTree<long long, long long>();
    RealTimeTest(reinterpret_cast<Container<long long, long long> *>(tree), "tree");
    delete tree;

    pair_array = new PairArray<long long, long long>();
    TimeTest(reinterpret_cast<Container<long long, long long> *>(pair_array), "array");
    delete pair_array;

    pair_map = new PairMap<long long, long long>();
    TimeTest(reinterpret_cast<Container<long long, long long> *>(pair_map), "map");
    delete pair_map;

    tree = new AVLTree<long long, long long>();
    TimeTest(reinterpret_cast<Container<long long, long long> *>(tree), "tree");
    delete tree;

    return 0;
}