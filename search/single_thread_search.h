//
// Created by david on 01.03.24.
//

#ifndef VECTOR_SINGLE_THREAD_SEARCH_H
#define VECTOR_SINGLE_THREAD_SEARCH_H

#include <string>
#include <vector>
#include <list>

/*
 * Takes an iterator to the first and after the last element of a list of shared strings
 * Writes all the strings that match the given prefix in the result vector
 */
template<typename Iterator>
void find_matching_words(const Iterator first, const Iterator last, const std::string& prefix, std::vector<std::string>& result)
{
    static_assert(std::is_same<typename Iterator::value_type, std::string>());
    for(auto current = first; current != last; current++)
    {
        // Compares prefix.length() many characters, starting at position 0.
        // When (*current)->length() < prefix.length(), compare returns -1
        if(current->compare(0, prefix.length(), prefix) == 0)
        {
            result.push_back(*current);
        }
    }
}

#endif //VECTOR_SINGLE_THREAD_SEARCH_H
