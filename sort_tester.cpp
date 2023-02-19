#include <random>
#include <chrono>
#include <fstream>
#include "sort_tester.h"
#include "sorters.h"

void SortTester::test() {
}

void SortTester::runTest(SortTester::SortMethod method, SortTester::ArrayType type, int length) {
    std::vector<int> v = SortTester::makeArray(type, length);
    auto start = std::chrono::high_resolution_clock::now();
    sorters[method](v);
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    int64_t nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();
    std::ofstream outfile;
    outfile.open("results.csv", std::ios_base::app);
    outfile << method << ';' << type << ';' << length << ';' << nanoseconds << std::endl;
}

std::vector<int> SortTester::makeArray(SortTester::ArrayType type, int length) {
    std::vector<int> v(length);
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
    for (int i = 0; i < 50; i++) {
        v[i] = distrib(gen);
    }
    if (type == ALMOST_SORTED) {
        std::sort(v.begin(), v.end());
        for (int i = 0; i < 10; i++) {
            v[i] = distrib(gen);
        }
    } else if (type == REVERSE_SORTED) {
        std::sort(v.begin(), v.end());
        std::reverse(v.begin(), v.end());
    }
    return v;
}
