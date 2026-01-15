// Katherine Kim
// Class (CECS 325-01)
// Project Name (Prog 6 – Three N Problem)
// Due Date (12/06/2023)
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.

#include <iostream>
#include <vector>
#include <limits>

using namespace std;

// Function to calculate the next term in the Collatz sequence
int collatz(int n, int steps, int &max, int &odds, int &evens) {
    // Check for integer overflow
    if (n <= 1) {
        throw overflow_error("Input less than 2");
    }

    // Update stats
    if (n % 2 == 0) {
        evens++;
    } else {
        odds++;
    }

    // Update maximum value
    if (n > max) {
        max = n;
    }

    // Print current step
    cout << "->(" << n << ")";

    // Base case for recursion
    if (n == 1) {
        cout << endl;
        return steps;
    }

    // Recursive step
    if (n % 2 == 0) {
        return collatz(n / 2, steps + 1, max, odds, evens);
    } else {
        // Check for potential overflow before computing 3n+1
        if (n > (numeric_limits<int>::max() - 1) / 3) {
            throw overflow_error("Integer overflow");
        }
        return collatz(3 * n + 1, steps + 1, max, odds, evens);
    }
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        // Ask for user input if no parameters provided
        int start;
        cout << "Enter a 3n+1 candidate number: ";
        cin >> start;

        int steps = 0, max = start, odds = 0, evens = 0;

        try {
            cout << "->(" << start << ")";
            steps = collatz(start, 0, max, odds, evens);
            cout << "steps:" << steps << endl;
            cout << "max:" << max << endl;
            cout << "odds:" << odds << endl;
            cout << "evens:" << evens << endl;
        } catch (overflow_error &e) {
            cerr << "Integer overflow or input less than 2" << endl;
        }

    } else {
        // Process command line arguments
        for (int i = 1; i < argc; ++i) {
            int num = stoi(argv[i]);
            int steps = 0, max = num, odds = 0, evens = 0;

            try {
                cout << "->(" << num << ")";
                steps = collatz(num, 0, max, odds, evens);
                cout << "start:" << num << endl;
                cout << "steps:" << steps << endl;
                cout << "max:" << max << endl;
                cout << "odds:" << odds << endl;
                cout << "evens:" << evens << endl;
            } catch (overflow_error &e) {
                cerr << "Integer overflow or input less than 2" << endl;
            }
        }
    }

    return 0;
}
