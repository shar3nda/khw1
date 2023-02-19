//
// Created by johann on 19.02.23.
//

#ifndef KHW1_SORT_TESTER_H
#define KHW1_SORT_TESTER_H

#include <map>
#include <string>
#include <functional>
#include "sorters.h"

class SortTester {
public:
    SortTester() {
        sorters = std::unordered_map<std::string, std::function<void(std::vector<int> &)>>{
            {"BUBBLE_SORT", Sorters::bubbleSort},
            {"IVERSON1_SORT", Sorters::iverson1Sort},
            {"IVERSON12_SORT", Sorters::iverson12Sort},
            {"SELECTION_SORT", Sorters::selectionSort},
            {"INSERTION_SORT", Sorters::insertionSort},
            {"BINARY_INSERTION_SORT", Sorters::binaryInsertionSort},
            {"MERGE_SORT", Sorters::mergeSort},
            {"QUICK_SORT", Sorters::quickSort},
            {"HEAP_SORT", Sorters::heapSort},
            {"RADIX_SORT", Sorters::radixSort},
            {"COUNT_SORT", Sorters::countSort},
            {"SHELL_SORT_CIURA", Sorters::shellSortCiura},
            {"SHELL_SORT_SHELL", Sorters::shellSortShell}};
    }
    std::unordered_map<std::string, std::function<void(std::vector<int> &)>> sorters;
    std::vector<std::string> ArrayTypes{"RANDOM_0_5", "RANDOM_0_4000", "ALMOST_SORTED",
                                        "REVERSE_SORTED"};
    void test();

private:
    void runTest(const std::string &sorting_method, const std::string &array_type, std::vector<int> &v);

    void makeArray(std::vector<int> &v, const std::string &type);
};

#endif  // KHW1_SORT_TESTER_H
