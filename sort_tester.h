//
// Created by johann on 19.02.23.
//

#ifndef KHW1_SORT_TESTER_H
#define KHW1_SORT_TESTER_H

#include <map>
#include <functional>
#include "sorters.h"

class SortTester {
public:
    SortTester() {
        sorters = std::map<SortMethod, std::function<void(std::vector<int> &)>>{
            {BUBBLE_SORT, Sorters::bubbleSort},
            {IVERSON1_SORT, Sorters::iverson1Sort},
            {IVERSON12_SORT, Sorters::iverson12Sort},
            {SELECTION_SORT, Sorters::selectionSort},
            {INSERTION_SORT, Sorters::insertionSort},
            {BINARY_INSERTION_SORT, Sorters::binaryInsertionSort},
            {MERGE_SORT, Sorters::mergeSort},
            {QUICK_SORT, Sorters::quickSort},
            {HEAP_SORT, Sorters::heapSort},
            {RADIX_SORT, Sorters::radixSort},
            {COUNT_SORT, Sorters::countSort},
            {SHELL_SORT_CIURA, Sorters::shellSortCiura},
            {SHELL_SORT_SHELL, Sorters::shellSortShell}};
    }
    enum SortMethod {
        BUBBLE_SORT,
        IVERSON1_SORT,
        IVERSON12_SORT,
        SELECTION_SORT,
        INSERTION_SORT,
        BINARY_INSERTION_SORT,
        MERGE_SORT,
        QUICK_SORT,
        HEAP_SORT,
        RADIX_SORT,
        COUNT_SORT,
        SHELL_SORT_CIURA,
        SHELL_SORT_SHELL
    };
    std::map<SortMethod, std::function<void(std::vector<int> &)>> sorters;
    enum ArrayType { RANDOM_0_5, RANDOM_0_4000, ALMOST_SORTED, REVERSE_SORTED };
    void test();

private:
    void runTest(SortMethod method, ArrayType type, int length);

    std::vector<int> makeArray(ArrayType type, int length);
};

#endif  // KHW1_SORT_TESTER_H
