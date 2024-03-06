//
// Created by david on 02.03.24.
//

#ifndef VECTOR_MULTI_THREAD_SEARCH_H
#define VECTOR_MULTI_THREAD_SEARCH_H

#include <thread>
#include "single_thread_search.h"

const unsigned int DEFAULT_NUM_THREADS = 4;


/*
 * Takes an iterator to the first and after the last element of a list of shared strings
 * Spreads the search across num_threads many threads, checks hardware concurrency if num_threads is 0 (default)
 * Returns all the strings that match the given prefix
 */
template<typename Iterator>
std::vector<std::string> find_matching_prefix_multithreaded(Iterator first, Iterator last, const std::string& prefix, unsigned int num_threads = 0)
{
    static_assert(std::is_same<typename Iterator::value_type, std::string>());

    if(num_threads == 0)
    {
        num_threads = std::thread::hardware_concurrency();
        // std::thread::hardware_concurrency() might return 0 if it isn't successful
        if (num_threads == 0)
            num_threads = DEFAULT_NUM_THREADS;
    }

    // Split the vector into (roughly) equal parts and run the search on each part in a separate thread
    std::vector<std::thread> threads;
    std::vector<std::vector<std::string>> threadResults(num_threads);
    unsigned int num_words = last-first;
    Iterator lastSplit = first;
    for(unsigned int i = 0; i < num_threads; i++)
    {
        Iterator nextSplit = first + (((i+1) * num_words) / num_threads);
        // Run the search for the elements between the iterators lastSplit and nextSplit
        threads.emplace_back(find_matching_words<Iterator>, lastSplit, nextSplit, prefix, std::ref(threadResults[i]));
        lastSplit = nextSplit;
    }

    // Wait for the threads to complete running
    for(auto& thread: threads)
        thread.join();

    // Combine all results into one vector
    std::vector<std::string> allResults;
    for(auto& threadResult: threadResults)
    {
        std::move(threadResult.begin(), threadResult.end(), std::back_inserter(allResults));
    }
    return allResults;
}

#endif //VECTOR_MULTI_THREAD_SEARCH_H
