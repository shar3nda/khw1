#include <random>
#include <chrono>
#include <fstream>
#include <iostream>
#include "sort_tester.h"
#include "sorters.h"

void SortTester::test() {
    for (int length = 50; length <= 300; length += 50) {
        std::vector<int> v(length);
        for (const auto &[method, sorter] : sorters) {
            for (const auto &array_type :
                 {RANDOM_0_5, RANDOM_0_4000, ALMOST_SORTED, REVERSE_SORTED}) {
                runTest(method, array_type, v);
            }
        }
    }
    for (int length = 100; length <= 4100; length += 100) {
        std::vector<int> v(length);
        for (const auto &[method, sorter] : sorters) {
            for (const auto &array_type :
                 {RANDOM_0_5, RANDOM_0_4000, ALMOST_SORTED, REVERSE_SORTED}) {
                runTest(method, array_type, v);
            }
        }
    }
}

void SortTester::runTest(std::string method, SortTester::ArrayType type,
                         std::vector<int> &v) {
    for (int i = 0; i < 50; i++) {
        std::ofstream outfile;
        outfile.open("results.csv", std::ios::out | std::ios::app);
        SortTester::makeArray(v, type);
        auto start = std::chrono::high_resolution_clock::now();
        sorters[method](v);
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        int64_t nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();

        outfile << method << ';' << type << ';' << v.size() << ';' << nanoseconds << std::endl;
        outfile.close();
    }
}

void SortTester::makeArray(std::vector<int> &v, SortTester::ArrayType type) {
    std::random_device rd;  // создаем объект для генерации случайных чисел
    std::mt19937 gen(rd());  // создаем генератор случайных чисел
    std::uniform_int_distribution<> distrib;  // создаем объект для равномерного распределения
    if (type == RANDOM_0_5) {
        distrib = std::uniform_int_distribution<>(0, 5);
    } else if (type == RANDOM_0_4000) {
        distrib = std::uniform_int_distribution<>(0, 4000);
    } else if (type == ALMOST_SORTED) {
        distrib = std::uniform_int_distribution<>(0, 4100);
    } else if (type == REVERSE_SORTED) {
        distrib = std::uniform_int_distribution<>(1, 4100);
    }
    for (size_t i = 0; i < v.size(); i++) {
        v[i] = distrib(gen);
    }
    if (type == ALMOST_SORTED) {
        std::sort(v.begin(), v.end());
        std::uniform_int_distribution<> distrib_index(0, v.size() - 1);
        for (int i = 0; i < static_cast<int>(v.size() / 50); i++) {
            int a = distrib_index(gen), b = distrib_index(gen);
            std::swap(v[a], v[b]);
        }
    } else if (type == REVERSE_SORTED) {
        std::sort(v.begin(), v.end());
        std::reverse(v.begin(), v.end());
    }
}
