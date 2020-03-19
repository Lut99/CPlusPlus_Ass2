/* ASSIGNMENT 2.hpp
 *   by Lut99
 * 
 * Assignment 2
 *
 * Created:
 *   3/4/2020, 11:20:11 AM
 * Last edited:
 *   3/19/2020, 5:19:26 PM
 * Auto updated?
 *   Yes
 *
 * Description:
 *   The code for the second assignment. It allows for compression and 
 *   decompression for a given txt file or from the stdin. The compression
 *   is  a simple, run-length compression, which outputs each string of
 *   recurring characters as the character followed by the number of times
 *   it occurs. For digits, we prepend them with '\' to indicate that these
 *   are the characters and not a length. This also means we prepend '\'
 *   with another backslash to avoid escaping the character that follows
 *   it.
 *
 * This file is compiled and tested on Ubuntu 18.04 and compiled with g++. See
 *   the Makefile to see the precise options.
**/

#ifndef ASSIGNMENT2_HPP
#define ASSIGNMENT2_HPP

#include <istream>
#include <ostream>

/* Reads from given input stream and writes the compressed version to the output stream. If at any point a failure occurs, an error message is returned. That string is empty upon success. */
std::string compress_stream(std::istream& s_raw, std::ostream& s_com, long& count_in, long& count_out);

/* Reads from given input stream and writes the decompressed version to the output stream. If at any point a failure occurs, an error message is returned. That string is empty upon success. */
std::string decompress_stream(std::istream& s_com, std::ostream& s_raw, long& count_in, long& count_out);

#endif