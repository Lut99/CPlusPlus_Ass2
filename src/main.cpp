/* MAIN.cpp
 *   by Lut99
 *
 * Created:
 *   3/4/2020, 11:26:01 AM
 * Last edited:
 *   3/4/2020, 1:08:29 PM
 * Auto updated?
 *   Yes
 *
 * Description:
 *   The main file includes the io part of the program, which is separated
 *   for testing.
**/

#include <iostream>
#include <fstream>

#include "assignment2.hpp"

using namespace std;


enum RunMode {
    compress,
    decompress,
    help
};

struct Options {
    string input;
    string output;
    RunMode mode;
};


/* Parses the given command line arguments according to the specification */
Options parse_input(int argc, char** argv) {
    Options to_ret;

    // Begin looping
    for (int i = 0; i < argc; i++) {
        cout << argv[i] << endl;
    }
}


/* Entry point for the program */
int main(int argc, char** argv) {
    // To start, we will try to parse input
    Options opt = parse_input(argc, argv);
}