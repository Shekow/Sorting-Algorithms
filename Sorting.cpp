#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

namespace Sorting
{
    template<class T, class C> 
    void insertionSort(T begin, T end, C comp)
    {
        for (T it = begin + 1, it2; it != end; it++)
        {
            auto element = *it;
            for (it2 = it - 1; it2 - begin >= 0 && comp(element, *it2); it2--)
                *(it2 + 1) = *(it2);
            *++it2 = element;
        }
    }
    template<class T> 
    void insertionSort(T begin, T end)
    {
        insertionSort(begin, end, less());
    }

    template<class T, class C>
    void selectionSort(T begin, T end, C comp)
    {
        for (T it = begin; it != end - 1; it++)
        {
            T next = it;
            for (T it2 = it; it2 != end; it2++)
                if (comp(*it2, *next))
                    next = it2;
            swap(*it, *next);
        }
    }
    template<class T> 
    void selectionSort(T begin, T end)
    {
        selectionSort(begin, end, less());
    }

    template<class T, class C>
    void bubbleSort(T begin, T end, C comp)
    {
        for (T it = begin; it != end - 1; it++)
        {
            for (T it2 = end - 1; it2 != it; it2--)
                if (comp(*it2, *(it2 - 1)))
                    swap(*it2, *(it2 - 1));
        }
    }
    template<class T> 
    void bubbleSort(T begin, T end)
    {
        bubbleSort(begin, end, less());
    }

    template<class T, class C>
    void shellSort(T begin, T end, C comp)
    {
        for (size_t gap = end - begin; gap > 0; gap /= 2)
        {
            for (T it = begin + gap, it2; it != end; it++)
            {
                auto element = *it;
                for (it2 = it - gap; it2 - begin >= 0 && comp(element, *it2); it2 -= gap)
                    *(it2 + gap) = *(it2);
                *(it2 + gap) = element;
            }
        }
    }
    template<class T> 
    void shellSort(T begin, T end)
    {
        shellSort(begin, end, less());
    }

    template<class T, class C>
    void mergeSort(T begin, T end, C comp)
    {
        size_t size = (end - begin);
        if (size <= 1)
            return;
        T mid = begin + size / 2;
        vector firstPart(begin, mid);
        vector secondPart(mid, end);
        mergeSort(firstPart.begin(), firstPart.end(), comp);
        mergeSort(secondPart.begin(), secondPart.end(), comp);
        T mainIt = begin;
        for (T it1 = firstPart.begin(), it2 = secondPart.begin(); mainIt != end; mainIt++)
        {
            if (it2 == secondPart.end() || (it1 != firstPart.end() && comp(*it1, *it2)))
                *mainIt = *it1++;
            else
                *mainIt = *it2++;
        }
    }
    template<class T> 
    void mergeSort(T begin, T end)
    {
        mergeSort(begin, end, less());
    }

    template<class T, class C>
    void quickSort(T begin, T end, C comp)
    {
        if (end - begin <= 1)
            return;
        T mid = begin + (end - begin) / 2, cuIt = begin;
        vector<T> tmp{begin, mid, end};
        insertionSort(tmp.begin(), tmp.end(), [&comp](T it1, T it2){
            return comp(*it1, *it2);
        });
        T pivot = tmp[1];
        swap(*pivot, *begin);
        for (T it = begin + 1; it != end; it++)
            if (comp(*it, *begin))
                swap(*++cuIt, *it);
        swap(*cuIt, *begin);
        quickSort(begin, cuIt, comp);
        quickSort(cuIt + 1, end, comp);
    }
    template<class T> 
    void quickSort(T begin, T end)
    {
        quickSort(begin, end, less());
    }

    template<class T, class C>
    void heapSort(T begin, T end, C comp)
    {
        auto firstChild = [&](T it){
            return begin + 2 * (it - begin) + 1;
        };
        auto secondChild = [&](T it){
            return firstChild(it) + 1;
        };
        auto heapify = [&](T it, T end){
            while (firstChild(it) < end)
            {
                T next = firstChild(it);
                if (secondChild(it) < end && comp(*secondChild(it), *firstChild(it)))
                    next = secondChild(it);
                if (comp(*next, *it))
                    swap(*next, *it), it = next;
                else
                    break;
            }
        };
        size_t size = end - begin;
        for (T it = end - 1; it >= begin; it--)
            heapify(it, end);
        for (T it  = end - 1; it > begin; it--)
            swap(*it, *begin), heapify(begin, it);
        reverse(begin, end);
    }
    template<class T> 
    void heapSort(T begin, T end)
    {
        heapSort(begin, end, less());
    }

    template<class T, class K>
    void countSort(T begin, T end, K key)
    {
        size_t maxKey = 0, size = end - begin;
        for (T it = begin; it != end; it++)
            maxKey = max(maxKey, key(*it));
        vector<size_t> freq(maxKey + 1);
        vector sorted(begin, end);

        for (T it = begin; it != end; it++)
            freq[key(*it)]++;
        for (size_t i = 1; i <= maxKey; i++)
            freq[i] += freq[i - 1];
        
        for (T it = end - 1; it >= begin; it--)
            sorted[--freq[key(*it)]] = *it;
        for (T it1 = begin, it2 = sorted.begin(); it1 != end; it1++, it2++)
            *it1 = *it2;
    }
    template<class T> 
    void countSort(T begin, T end)
    {
        countSort(begin, end, [](auto e){
            return size_t(e);
        });
    }

    template<class T, class K>
    void radixSort(T begin, T end, K key)
    {
        auto countDigits = [](size_t n){
            size_t ctr = 0;
            while (n)
                ctr++, n /= 10;
            return ctr;
        };
        size_t k = 10, maxDigits = 0, size = end - begin;
        vector<size_t> freq(k);
        vector sorted(begin, end);
        
        for (T it = begin; it != end; it++)
            maxDigits = max(maxDigits, countDigits(key(*it)));

        for (size_t d = 0, pos = 1; d < maxDigits; d++, pos *= 10)
        {
            for (size_t i = 0; i < k; i++)
                freq[i] = 0;
            for (T it = begin; it != end; it++)
                freq[(*it / pos) % k]++;
            for (size_t i = 1; i < k; i++)
                freq[i] += freq[i - 1];

            for (T it = end - 1; it >= begin; it--)
                sorted[--freq[(*it / pos) % k]] = *it;
            for (T it1 = begin, it2 = sorted.begin(); it1 != end; it1++, it2++)
                *it1 = *it2;
        }
    }
    template<class T> 
    void radixSort(T begin, T end)
    {
        radixSort(begin, end, [](auto e){
            return size_t(e);
        });
    }
}