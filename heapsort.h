#ifndef KHW1_HEAPSORT_H
#define KHW1_HEAPSORT_H

#include <vector>
#include <string>
#include <stack>
#include <utility>
#include <iostream>

template <class ValueType>
class Heap {
public:
    Heap() {
        heap = std::vector<ValueType>();
    }

    template <class Iterator>
    Heap(Iterator begin, Iterator end) {
        for (Iterator it = begin; it != end; ++it) {
            insert(*it);
        }
    }

    Heap(std::initializer_list<ValueType> init_list) {
        for (const ValueType &val : init_list) {
            insert(val);
        }
    }

    Heap(const Heap &other) {
        heap = other.heap;
    }

    Heap &operator=(const Heap &other) {
        heap = other.heap;
        return *this;
    }

    Heap(Heap &&other) {
        heap = std::move(other.heap);
    }
    Heap &operator=(Heap &&other) {
        heap = std::move(other.heap);
        return *this;
    }

    ~Heap() {
        heap.clear();
    }

    size_t size() const {
        return heap.size();
    }

    bool empty() const {
        return heap.empty();
    }

    void insert(const ValueType &num) {
        heap.push_back(num);
        heapifyUp(heap.size() - 1);
    }

    ValueType extract() {
        ValueType root = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);
        return root;
    }

    std::vector<ValueType> heap;

private:
    void heapifyDown(size_t i) {
        size_t smallest = i, left = 2 * i + 1, right = 2 * i + 2;
        if ((left < size()) && (heap[left] < heap[smallest])) {
            smallest = left;
        }
        if ((right < size()) && (heap[right] < heap[smallest])) {
            smallest = right;
        }
        if (smallest != i) {
            std::swap(heap[i], heap[smallest]);
            heapifyDown(smallest);
        }
    }
    void heapifyUp(size_t i) {
        size_t parent = (i - 1) / 2;
        if ((i != 0) && (heap[parent] > heap[i])) {
            std::swap(heap[parent], heap[i]);
            heapifyUp(parent);
        }
    }
};

#endif //KHW1_HEAPSORT_H
