/* ASSIGNMENT 2.hpp
 *   by Lut99
 *
 * Created:
 *   3/4/2020, 11:20:11 AM
 * Last edited:
 *   3/4/2020, 1:08:54 PM
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
**/

#ifndef ASSIGNMENT2_HPP
#define ASSIGNMENT2_HPP

#include <istream>
#include <ostream>

/* Reads from given input stream and writes the compressed version to the output stream. If at any point a failure occurs, an error message is returned. That string is empty upon success. */
std::string compress_stream(std::istream& s_raw, std::ostream& s_com);

/* Reads from given input stream and writes the decompressed version to the output stream. If at any point a failure occurs, an error message is returned. That string is empty upon success. */
std::string decompress_stream(std::istream& s_com, std::ostream& s_raw);

#endif