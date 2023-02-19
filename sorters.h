#ifndef SORTERS_H
#define SORTERS_H

#include <vector>

class Sorters {
public:
    static void bubbleSort(std::vector<int> &v);

    static void iverson1Sort(std::vector<int> &v);

    static void iverson12Sort(std::vector<int> &v);

    static void selectionSort(std::vector<int> &v);

    static void insertionSort(std::vector<int> &v);

    static void binaryInsertionSort(std::vector<int> &v);

    static void mergeSort(std::vector<int> &v);

    static void quickSort(std::vector<int> &v);

    static void heapSort(std::vector<int> &v);

    static void radixSort(std::vector<int> &v);

    static void countSort(std::vector<int> &v);

    static void shellSortCiura(std::vector<int> &v);

    static void shellSortShell(std::vector<int> &v);

private:
    static void quickSortHelper(std::vector<int> &v, int left, int right);

    static int quickSortPartitionHelper(std::vector<int> &v, int left, int right);

    static void radixSortCountHelper(std::vector<int> &v, int radix);
};

#endif
