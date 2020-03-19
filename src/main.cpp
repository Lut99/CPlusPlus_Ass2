/* MAIN.cpp
 *   by Lut99
 *
 * Created:
 *   3/4/2020, 11:26:01 AM
 * Last edited:
 *   3/19/2020, 12:40:08 PM
 * Auto updated?
 *   Yes
 *
 * Description:
 *   The main file includes the io part of the program, which is separated
 *   for testing.
**/

#include <iostream>
#include <fstream>
#include <cerrno>
#include <cstring>

#include "assignment2.hpp"

using namespace std;


const char TAB[] = "    ";


enum RunMode {
    compress,
    decompress,
    help,
    undefined
};


struct Options {
    string input;
    string output;
    RunMode mode;
};


/* Prints how the usage string of the file. */
void print_usage() {
    cerr << "MyCompress <flag> [<input-filename>] [<output-filename>]" << endl;
}
/* Prints information about this program and it's arguments. */
void print_help() {
    cerr << endl << "Name" << endl << endl;
    cerr << TAB << "MyCompress" << endl << endl;
    cerr << "Synopsis" << endl << endl;
    cerr << TAB;
    print_usage();
    cerr << endl << "Description" << endl << endl;
    cerr << TAB << "Compresses and decompresses text files." << endl;
    cerr << TAB << "If no output filename is given it writes to standard output (stdout)." << endl;
    cerr << TAB << "If no input filename is given it reads from standard input (stdin)." << endl << endl;
    cerr << "Options for <flag>" << endl << endl;
    cerr << TAB << "-h" << TAB << "give this usage information and exit" << endl;
    cerr << TAB << "-c" << TAB << "compress the input file and write result to output file" << endl;
    cerr << TAB << "-d" << TAB << "decompress the input file and write result to output file" << endl << endl;
    cerr << "Example usage" << endl << endl;
    cerr << TAB << "MyCompress -c input.txt output-txt # compress input.txt to output.txt" << endl;
    cerr << TAB << "cat output.txt | MyCompress -d # read from stdin, decompress to stdout" << endl << endl;
}

/* Parses the given command line arguments according to the specification */
Options* parse_input(int argc, char** argv) {
    Options to_ret;
    to_ret.mode = undefined;

    // Begin looping
    int positional_arguments = 0;
    for (int i = 1; i < argc; i++) {
        char* arg = argv[i];

        // Check if it begins with a '-'
        if (arg[0] == '-') {
            // Switch to the correct flag
            switch(arg[1]) {
                case 'c':
                    to_ret.mode = compress;
                    break;
                case 'd':
                    to_ret.mode = compress;
                    break;
                case 'h':
                    to_ret.mode = help;
                    return new Options(to_ret);
                default:
                    cerr << "Specify either '-c' or '-d' (for help, use '-h')" << endl;
                    return nullptr;
            }
        } else {
            switch(positional_arguments) {
                case 0:
                    // Store as input file
                    to_ret.input = string(arg);
                    positional_arguments++;
                    break;
                case 1:
                    // Store as output file
                    to_ret.output = string(arg);
                    positional_arguments++;
                    break;
                default:
                    print_usage();
                    return nullptr;
            }
        }
    }

    // Check if at least one flag is specified
    if (to_ret.mode == undefined) {
        cerr << "Specify either '-c' or '-d' (for help, use '-h')" << endl;
        return nullptr;
    }

    return new Options(to_ret);
}


/* Entry point for the program */
int main(int argc, char** argv) {
    // To start, we will try to parse input
    Options* opt = parse_input(argc, argv);
    // If it's a nullptr, stop
    if (opt == nullptr) {
        return -1;
    } else if (opt->mode == help) {
        print_help();
        // Don't forget to clear the Options dict
        delete opt;
        return 0;
    }

    // Open files if needed
    istream* in;
    ostream* out;
    if (opt->input.empty()) {
        in = &cin;
    } else {
        ifstream* fin = new ifstream(opt->input);
        if (!fin->is_open()) {
            cerr << "Could not open file \"" << opt->input << "\": " << strerror(errno) << endl;
            delete fin;
            delete opt;
            return -1;
        }
        in = (istream*) fin;
    }
    if (opt->output.empty()) {
        out = &cout;
    } else {
        ofstream* fout = new ofstream(opt->output);
        if (!fout->is_open()) {
            cerr << "Could not open file \"" << opt->input << "\": " << strerror(errno) << endl;
            delete in;
            delete fout;
            delete opt;
            return -1;
        }
        out = (ostream*) fout;
    }

    // Run the compression / decompression
    if (opt->mode == compress) {
        string res = compress_stream(*in, *out);
        if (!res.empty()) {
            cerr << res << endl;
        }
    } else {
        string res = decompress_stream(*in, *out);
        if (!res.empty()) {
            cerr << res << endl;
        }
    }

    // Don't forget to clear the allocated memory
    delete opt;
    if (!opt->input.empty()) {
        delete in;
    }
    if (!opt->output.empty()) {
        delete out;
    }

    return 0;
}