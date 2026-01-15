// Katherine Kim
// Class (CECS 325-01)

// Project Name (Prog 4 – Sort Race with pthreads)
// Due Date (10/23/2023)
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.

#include <iostream>
#include <fstream>
#include <pthread.h>

using namespace std;

struct SortParams {
    int *pstart;
    int size;
};

void* bubbleSortThread(void* arg) {
    SortParams* params = (SortParams*)arg;
    int* arr = params->pstart;
    size_t n = params->size;
    
    for (size_t i = 0; i < n - 1; i++) {
        for (size_t j = 0; j < n - i - 1; j++) {
            // Swap if the element found is greater than the next element
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    
    return NULL;
}

void merge(int* sec1, int size1, int* sec2, int size2) {
    int temp[size1 + size2];
    int s1 = 0, s2 = 0, z = 0;

    while (s1 < size1 && s2 < size2) {
        if (sec1[s1] <= sec2[s2]) {
            temp[z] = sec1[s1];
            ++s1;
        } else {
            temp[z] = sec2[s2];
            ++s2;
        }
        ++z;
    }

    while (s1 < size1) {
        temp[z] = sec1[s1];
        ++s1;
        ++z;
    }

    while (s2 < size2) {
        temp[z] = sec2[s2];
        ++s2;
        ++z;
    }

    for (int i = 0; i < size1 + size2; ++i) {
        sec1[i] = temp[i];
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " input_file output_file" << endl;
        return 1;
    }

    ifstream fin(argv[1]);
    if (!fin) {
        cerr << "Error: Could not open input file." << endl;
        return 1;
    }

    int numbers[1000000];
    int num;
    int counter = 0;
    while (fin >> num) {
        numbers[counter] = num;
        counter++;
    }
    fin.close();

    pthread_t thread0, thread1, thread2, thread3, thread4, thread5, thread6, thread7, thread8, thread9;
    int iret0, iret1, iret2, iret3, iret4, iret5, iret6, iret7, iret8, iret9;
    
    SortParams params[10];
    
    params[0].pstart = numbers;
    params[0].size = 100000;

    params[1].pstart = numbers + 100000;
    params[1].size = 100000;

    params[2].pstart = numbers + 200000;
    params[2].size = 100000;
    
    params[3].pstart = numbers + 300000;
    params[3].size = 100000;
    
    params[4].pstart = numbers + 400000;
    params[4].size = 100000;
    
    params[5].pstart = numbers + 500000;
    params[5].size = 100000;
    
    params[6].pstart = numbers + 600000;
    params[6].size = 100000;
    
    params[7].pstart = numbers + 700000;
    params[7].size = 100000;
    
    params[8].pstart = numbers + 800000;
    params[8].size = 100000;
    
    params[9].pstart = numbers + 900000;
    params[9].size = 100000;
    
    iret0 = pthread_create(&thread0, NULL, bubbleSortThread, (void *)&params[0]);
    iret1 = pthread_create(&thread1, NULL, bubbleSortThread, (void *)&params[1]);
    iret2 = pthread_create(&thread2, NULL, bubbleSortThread, (void *)&params[2]);
    iret3 = pthread_create(&thread3, NULL, bubbleSortThread, (void *)&params[3]);
    iret4 = pthread_create(&thread4, NULL, bubbleSortThread, (void *)&params[4]);
    iret5 = pthread_create(&thread5, NULL, bubbleSortThread, (void *)&params[5]);
    iret6 = pthread_create(&thread6, NULL, bubbleSortThread, (void *)&params[6]);
    iret7 = pthread_create(&thread7, NULL, bubbleSortThread, (void *)&params[7]);
    iret8 = pthread_create(&thread8, NULL, bubbleSortThread, (void *)&params[8]);
    iret9 = pthread_create(&thread9, NULL, bubbleSortThread, (void *)&params[9]);

    pthread_join(thread0, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    pthread_join(thread4, NULL);
    pthread_join(thread5, NULL);
    pthread_join(thread6, NULL);
    pthread_join(thread7, NULL);
    pthread_join(thread8, NULL);
    pthread_join(thread9, NULL);

    // Merging sorted subarrays
    merge(numbers, 100000, numbers + 100000, 100000);
    merge(numbers + 200000, 100000, numbers + 300000, 100000);
    merge(numbers + 400000, 100000, numbers + 500000, 100000);
    merge(numbers + 600000, 100000, numbers + 700000, 100000);
    merge(numbers + 800000, 100000, numbers + 900000, 100000);

    // Merging 1&2, with 3&4
    merge(numbers, 200000, numbers + 200000, 200000);

    // Merging 5&6, with 7&8
    merge(numbers + 400000, 200000, numbers + 600000, 200000);

    // Merging 1&2&3&4 with 5&6&7&8
    merge(numbers, 400000, numbers + 400000, 400000);

    // Merging 1&2&3&4&5&6&7&8 with 9&10
    merge(numbers, 800000, numbers + 800000, 200000);

    ofstream fout(argv[2]);
    if (fout.is_open()) {
        for (int i = 0; i < 1000000; ++i) {
            fout << numbers[i] << " " << endl; // Separate numbers with spaces
        }
        fout.close();
    } else {
        cerr << "Error: Could not open output file." << endl;
        return 1;
    }

    return 0;
}
