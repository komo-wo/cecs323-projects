// Katherine Kim
// Class (CECS 325-01)

// Project Name (Prog 4 – Sort Race with pthreads)
// Due Date (10/09/2023)
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.

#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cerr << "Usage: generate COUNT MIN MAX" << endl;
        return 1;
    }

    cout << "argv[0]:" << argv[0] << endl;
    cout << "argv[1]:" << argv[1] << endl;
    cout << "argv[2]:" << argv[2] << endl;
    cout << "argv[3]:" << argv[3] << endl;

    int count = stoi(argv[1]);
    int min = stoi(argv[2]);
    int max = stoi(argv[3]);

    ofstream fout("numbers.dat");

    if (!fout) {
        cerr << "Error: Could not open numbers.dat for writing." << endl;
        return 1;
    }

    srand(time(0));

    for (int i = 0; i < count; ++i) {
        int num = min + rand() % (max - min + 1);
        fout << num << endl;
    }

    fout.close();
    return 0;
}
