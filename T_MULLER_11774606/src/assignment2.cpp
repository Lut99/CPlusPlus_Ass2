/* ASSIGNMENT 2.cpp
 *   by Tim Muller (11774606)
 *
 * Created:
 *   3/4/2020, 11:11:31 AM
 * Last edited:
 *   3/19/2020, 5:14:19 PM
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

#include <iostream>
#include <cmath>

#include "assignment2.hpp"

using namespace std;


enum ParseState {
    character,
    number,
    escaping
};


std::string compress_stream(std::istream& s_raw, std::ostream& s_com, long& count_in, long& count_out) {
    // Read from the istream until we encounter eof
    char current_sequence = '\0';
    int sequence_length = 0;
    while(true) {
        char c;
        s_raw.get(c);
        if (s_raw.eof()) {
            break;
        } else if (s_raw.fail()) {
            // An error has occurred
            return "Could not read character from stream";
        }
        count_in++;
        
        if (c == current_sequence) {
            // If the character is the same as we have seen, just count
            sequence_length++;
        } else {
            // Otherwise, print the count if needed
            if (current_sequence != '\0' && sequence_length > 1) {
                s_com << sequence_length;
                count_out += to_string(sequence_length).size();
            }
            // Reset the vars
            current_sequence = c;
            sequence_length = 1;
            // Print the new var, with '\' if needed
            if (c == '\\' || (c >= '0' && c <= '9')) {
                s_com << '\\';
                count_out++;
            }
            s_com << c;
            count_out++;
        }
    }

    // Be sure to print remaining data
    if (current_sequence != '\0' && sequence_length > 1) {
        s_com << sequence_length;
        count_out += to_string(sequence_length).size();
    }
    
    // Stop success (return empty string)
    return "";
}

std::string decompress_stream(std::istream& s_com, std::ostream& s_raw, long& count_in, long& count_out) {
    // Read from the istream until we encounter eof
    int n = 0;
    char to_print = '\0';
    bool saw_character = false;
    ParseState state = character;
    while (true) {
        char c;
        s_com.get(c);
        if (s_com.eof()) {
            break;
        } else if (s_com.fail()) {
            // An error occurred
            return "Could not read character from stream";
        }
        count_in++;
        // Determine the next course of action based on the state
        switch(state) {
            case character:
                // If we encounter a '\\', escape
                if (c == '\\') {
                    state = escaping;
                    continue;
                } else if (c >= '0' && c <= '9') {
                    state = number;
                    n = (int) (c - '0');
                    continue;
                }
                // If we have already seen a character, print the previous one one time
                if (saw_character) {
                    s_raw << to_print;
                    count_out++;
                }
                to_print = c;
                saw_character = true;
                continue;
            case escaping:
                // Simply accept whatever character is here

                // If we have already seen a character, print the previous one one time
                if (saw_character) {
                    s_raw << to_print;
                    count_out++;
                }
                to_print = c;
                saw_character = true;
                state = character;
                continue;
            case number:
                if (c >= '0' && c <= '9') {
                    // Add this to the number
                    n *= 10;
                    n += (int) (c - '0');
                    continue;
                }

                // Print the character the computed number of times
                for (int i = 0; i < n; i++) {
                    s_raw << to_print;
                    count_out++;
                }
                // Put the currently read character back on the stream though
                s_com.putback(c);
                // Reset saw_character and go to state character
                saw_character = false;
                state = character;
                continue;
            default:
                // Should never happen
                continue;
        }
    }

    // Print the remaining found character
    if (saw_character) {
        s_raw << to_print;
        count_out++;
    }

    return "";
}