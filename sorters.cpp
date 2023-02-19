#include <vector>
#include <chrono>
#include <fstream>
#include <random>
#include "sorters.h"
#include "heapsort.h"

void Sorters::bubbleSort(std::vector<int> &v) {
    for (size_t i = 0; i < v.size(); i++) {
        for (size_t j = 0; j < v.size() - 1; j++) {
            // Обмениваем элементы местами, если они не упорядочены
            if (v[j] > v[j + 1]) {
                std::swap(v[j], v[j + 1]);
            }
        }
    }
}

void Sorters::selectionSort(std::vector<int> &v) {
    for (size_t i = 0; i < v.size(); i++) {
        int min = i;
        for (size_t j = i + 1; j < v.size(); j++) {
            // Ищем минимальный элемент в оставшейся части массива
            if (v[j] < v[min]) {
                min = j;
            }
        }
        // "Опускаем" найденный минимальный элемент на текущую позицию
        std::swap(v[i], v[min]);
    }
}

void Sorters::insertionSort(std::vector<int> &v) {
    for (size_t i = 1; i < v.size(); i++) {
        int j = i;
        // Опускаем новый элемент на нужную позицию в отсортированной части массива
        while (j > 0 && v[j] < v[j - 1]) {
            std::swap(v[j], v[j - 1]);
            j--;
        }
    }
}

void Sorters::mergeSort(std::vector<int> &v) {
    if (v.size() <= 1) {
        return;
    }
    // Определяем середину массива
    int mid = v.size() / 2;
    std::vector<int> left(v.begin(), v.begin() + mid);
    std::vector<int> right(v.begin() + mid, v.end());
    // Сортируем обе половины рекурсивно
    mergeSort(left);
    mergeSort(right);
    int i = 0, j = 0, k = 0;
    while (i < static_cast<int>(left.size()) && j < static_cast<int>(right.size())) {
        // Берем меньший из двух передних элементов в отсортированных половинах
        // и помещаем его в результирующий массив
        if (left[i] < right[j]) {
            v[k] = left[i];
            i++;
        } else {
            v[k] = right[j];
            j++;
        }
        k++;
    }

    // Если в половинах остались элементы, то добавляем их в результирующий массив
    while (i < static_cast<int>(left.size())) {
        v[k] = left[i];
        i++;
        k++;
    }
    while (j < static_cast<int>(right.size())) {
        v[k] = right[j];
        j++;
        k++;
    }
}

void Sorters::quickSort(std::vector<int> &v) {
    // Вызываем добавочную функцию от границ исходного массива
    quickSortHelper(v, 0, v.size() - 1);
}

void Sorters::quickSortHelper(std::vector<int> &v, int left, int right) {
    if (left < right) {
        // Выбираем опорный элемент и рекурсивно сортируем
        // элементы слева и справа от него
        int pivot = quickSortPartitionHelper(v, left, right);
        quickSortHelper(v, left, pivot - 1);
        quickSortHelper(v, pivot + 1, right);
    }
}

int Sorters::quickSortPartitionHelper(std::vector<int> &v, int left, int right) {
    // Выбираем первый элемент в качестве опорного
    int pivot = v[left];
    int k = right;
    for (int i = right; i > left; i--) {
        // Если элемент больше опорного, то меняем его с элементом с индексом k
        if (v[i] > pivot) {
            std::swap(v[i], v[k--]);
        }
    }
    // Меняем опорный элемент с элементом с индексом k
    std::swap(v[left], v[k]);
    return k;
}

void Sorters::binaryInsertionSort(std::vector<int> &v) {
    for (size_t i = 1; i < v.size(); i++) {
        // Ищем место для вставки элемента с помощью бинарного поиска
        int left = 0, right = i - 1, mid;
        while (left <= right) {
            mid = (left + right) / 2;
            if (v[i] < v[mid]) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        // Вставляем элемент в найденное место
        int temp = v[i];
        for (int j = i; j > left; j--) {
            v[j] = v[j - 1];
        }
        v[left] = temp;
    }
}

void Sorters::heapSort(std::vector<int> &v) {
    // Создаем кучу из исходного массива
    Heap<int> heap(v.begin(), v.end());
    // Извлекаем элементы из кучи
    for (size_t i = 0; i < v.size(); ++i) {
        v[i] = heap.extract();
    }
}

void Sorters::radixSort(std::vector<int> &v) {
    int max_elem = v[0];
    // Находим максимальный элемент
    for (size_t i = 1; i < v.size(); i++) {
        if (v[i] > max_elem) {
            max_elem = v[i];
        }
    }
    // Вызываем сортировку подсчетом для каждого разряда
    for (int radix = 1; max_elem / radix > 0; radix *= 256) {
        radixSortCountHelper(v, radix);
    }
}

void Sorters::radixSortCountHelper(std::vector<int> &v, int radix) {
    std::vector<int> output(v.size());
    std::vector<int> count(256);
    // Заполняем массив подсчетов нулями
    for (size_t i = 0; i < 256; ++i) {
        count[i] = 0;
    }
    // Выполняем подсчет количества элементов
    for (size_t i = 0; i < v.size(); ++i) {
        ++count[(v[i] / radix) % 256];
    }
    // Аккумулируем сумму
    for (size_t i = 1; i < 256; ++i) {
        count[i] += count[i - 1];
    }
    // Заполняем выходной массив
    for (int i = static_cast<int>(v.size() - 1); i >= 0; --i) {
        output[count[(v[i] / radix) % 256] - 1] = v[i];
        --count[(v[i] / radix) % 256];
    }

    for (int i = 0; i < static_cast<int>(v.size()); ++i) {
        v[i] = output[i];
    }
}

void Sorters::countSort(std::vector<int> &v) {
    int max_elem = v[0];
    for (size_t i = 1; i < v.size(); ++i) {
        if (v[i] > max_elem) {
            max_elem = v[i];
        }
    }
    // count[i] - количество вхождений i в исходный массив
    std::vector<int> count(max_elem + 1, 0);
    for (size_t i = 0; i < v.size(); ++i) {
        ++count[v[i]];
    }
    // Заполняем выходной массив
    int ind = 0;
    for (int i = 0; i < max_elem + 1; ++i) {
        for (int j = 0; j < count[i]; ++j) {
            v[ind++] = i;
        }
    }
}

void Sorters::shellSortCiura(std::vector<int> &v) {
    // Последовательность Циура
    std::vector<int> gaps = {701, 301, 132, 57, 23, 10, 4, 1};
    for (const int &gap : gaps) {
        for (size_t i = gap; i < v.size(); ++i) {
            // Запоминаем текущий элемент
            int temp = v[i];
            int j = i;
            // Выполняем сортировку вставками
            while (j >= gap && v[j - gap] > temp) {
                v[j] = v[j - gap];
                j -= gap;
            }
            // Приравниваем j-й элемент к запомненному
            v[j] = temp;
        }
    }
}

void Sorters::shellSortShell(std::vector<int> &v) {
    // Последовательность Шелла
    for (int gap = static_cast<int>(v.size() / 2); gap > 0; gap /= 2) {
        for (size_t i = gap; i < v.size(); ++i) {
            // Запоминаем текущий элемент
            int temp = v[i];
            int j = i;
            // Выполняем сортировку вставками
            while (j >= gap && v[j - gap] > temp) {
                v[j] = v[j - gap];
                j -= gap;
            }
            // Приравниваем j-й элемент к запомненному
            v[j] = temp;
        }
    }
}

void Sorters::iverson1Sort(std::vector<int> &v) {
    for (size_t i = 0; i < v.size(); i++) {
        // Подсчитываем количество обменов
        int swaps = 0;
        for (size_t j = 0; j < v.size() - 1; j++) {
            // Обмениваем элементы местами, если они не упорядочены
            if (v[j] > v[j + 1]) {
                std::swap(v[j], v[j + 1]);
                ++swaps;
            }
        }
        // Если обменов не было, то массив отсортирован
        if (swaps == 0) {
            break;
        }
    }
}

void Sorters::iverson12Sort(std::vector<int> &v) {
    for (size_t i = 0; i < v.size(); i++) {
        // Определяем границу, до которой нужно сортировать
        int bound = static_cast<int>(v.size() - i - 1);
        int t = 0;
        for (int j = 0; j < bound; j++) {
            // Обмениваем элементы местами, если они не упорядочены
            if (v[j] > v[j + 1]) {
                std::swap(v[j], v[j + 1]);
                t = j + 1;
            }
        }
        if (t == 0) {
            break;
        }
    }
}


