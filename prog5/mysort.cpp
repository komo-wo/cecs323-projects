// Ekaterina Li
// Class (CECS 325-01)

// Project Name (Prog 5 – Sort Race with pthreads)
// Due Date (10/23/2023)
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.

#include <iostream>
#include <fstream>
#include <thread>
#include <algorithm>

using namespace std;

const int array_size = 1000000;
const int section_size = array_size / 8;

int numbers[array_size];

// Quicksort implementation
void quicksort(int start, int end) {
    if (start < end) {
        int pivot = numbers[start];
        int left = start + 1;
        int right = end;
        while (left <= right) {
            while (left <= end && numbers[left] <= pivot)
                left++;
            while (right > start && numbers[right] > pivot)
                right--;
            if (left < right)
                swap(numbers[left], numbers[right]);
        }
        swap(numbers[start], numbers[right]);
        quicksort(start, right - 1);
        quicksort(right + 1, end);
    }
}

// Function to be executed by each thread for sorting its section
void sort_thread(int start, int end) {
    quicksort(start, end - 1);
}

// Merge function for merging two sorted sections of the array
void merge_sections(int start1, int end1, int start2, int end2) {
    int temp[end2 - start1 + 1];
    int i = start1, j = start2, k = 0;

    while (i <= end1 && j <= end2) {
        if (numbers[i] <= numbers[j]) {
            temp[k++] = numbers[i++];
        } else {
            temp[k++] = numbers[j++];
        }
    }

    while (i <= end1) {
        temp[k++] = numbers[i++];
    }

    while (j <= end2) {
        temp[k++] = numbers[j++];
    }

    for (i = start1, k = 0; i <= end2; ++i, ++k) {
        numbers[i] = temp[k];
    }
}

int main() {
    // Reading numbers from "numbers.dat" and initializing the array
    ifstream fin("numbers.dat");
    if (!fin) {
        cerr << "Error: Could not open input file." << endl;
        return 1;
    }

    int num;
    int counter = 0;
    while (fin >> num) {
        numbers[counter] = num;
        counter++;
    }
    fin.close();

    // Sorting threads
    thread threads[8];
    for (int i = 0; i < 8; ++i) {
        int start = i * section_size;
        int end = start + section_size;
        threads[i] = thread(sort_thread, start, end);
    }

    for (int i = 0; i < 8; ++i) {
        threads[i].join();
    }

    // Merging sections
    merge_sections(0, section_size - 1, section_size, 2 * section_size - 1);
    merge_sections(2 * section_size, 3 * section_size - 1, 3 * section_size, 4 * section_size - 1);
    merge_sections(4 * section_size, 5 * section_size - 1, 5 * section_size, 6 * section_size - 1);
    merge_sections(6 * section_size, 7 * section_size - 1, 7 * section_size, array_size - 1);

    merge_sections(0, 2 * section_size - 1, 2 * section_size, 4 * section_size - 1);
    merge_sections(4 * section_size, 6 * section_size - 1, 6 * section_size, array_size - 1);

    merge_sections(0, 4 * section_size - 1, 4 * section_size, array_size - 1);

    // Printing sorted array
    for (int i = 0; i < array_size; ++i) {
        cout << numbers[i] << "\n";
    }

    return 0;
}
