// Ekaterina Li
// Class (CECS 325-01)
// Project Name (Prog 3 – SortRace)
// Due Date (12/06/2023)
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.

#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: mysort input_file output_file" << endl;
        return 1;
    }

    ifstream inputFile(argv[1]);
    if (!inputFile) {
        cerr << "Error: Could not open the input file." << endl;
        return 1;
    }

    ofstream outputFile(argv[2]);
    if (!outputFile) {
        cerr << "Error: Could not open the output file." << endl;
        inputFile.close();
        return 1;
    }

    const int MAX_SIZE = 1000000; // Set the maximum size of the array
    int numbers[MAX_SIZE];
    int number;
    int count = 0;

    // Read numbers from the input file into the array
    while (inputFile >> number && count < MAX_SIZE) {
        numbers[count] = number;
        count++;
    }

    // Sorting the numbers using bubble sort
    bubbleSort(numbers, count);

    // Output the sorted numbers to the output file
    for (int i = 0; i < count; i++) {
        outputFile << numbers[i] << endl;
    }

    cout << "Numbers sorted and saved to " << argv[2] << endl;

    inputFile.close();
    outputFile.close();
    return 0;
}