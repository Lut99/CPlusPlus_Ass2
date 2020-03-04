/* ASSIGNMENT 2.cpp
 *   by Tim Muller (11774606)
 *
 * Created:
 *   3/4/2020, 11:11:31 AM
 * Last edited:
 *   3/4/2020, 1:09:26 PM
 * Auto updated?
 *   Yes
 *
 * Description:
 *   The code for the second assignment. It allows for compression and
 *   decompression for a given txt file or from the stdin. The compression is
 *   a simple, run-length compression, which outputs each string of recurring
 *   characters as the character followed by the number of times it occurs. For
 *   digits, we prepend them with '\' to indicate that these are the characters
 *   and not a length. This also means we prepend '\' with another backslash to
 *   avoid escaping the character that follows it.
**/

#include "assignment2.hpp"

using namespace std;


std::string compress_stream(std::istream& s_raw, std::ostream& s_com) {
    // Read from the istream until we encounter eof
    char current_sequence = '\0';
    int sequence_length = 0;
    while(true) {
        char c;
        s_raw >> c;
        if (c == '\n' || c == ' ' || c == '\t') {
            s_com << "LMAO";
        }
        if (s_raw.eof()) {
            break;
        } else if (s_raw.fail()) {
            // An error has occurred
            return "Could not read character from stream";
        }
        
        if (c == current_sequence) {
            // If the character is the same as we have seen, just count
            sequence_length++;
        } else {
            // Otherwise, print the count if needed
            if (current_sequence != '\0' && sequence_length > 1) {
                s_com << sequence_length;
            }
            // Reset the vars
            current_sequence = c;
            sequence_length = 1;
            // Print the new var, with '\' if needed
            if (c == '\\' || (c >= '0' && c <= '9')) {
                s_com << '\\';
            }
            s_com << c;
        }
    }

    // Be sure to print remaining data
    if (current_sequence != '\0' && sequence_length > 1) {
        s_com << sequence_length;
    }
    
    // Stop success (return empty string)
    return "";
}

std::string decompress_stream(std::istream& s_com, std::ostream& s_raw) {
    // Read from the istream until we encounter eof
    while (!s_com.eof()) {
        
    }
}