//
// Created by david on 03.03.24.
//

#ifndef VECTOR_ITERATIVESEARCH_H
#define VECTOR_ITERATIVESEARCH_H

#include <utility>
#include <vector>
#include <memory>
#include "single_thread_search.h"
#include "multi_thread_search.h"

struct SearchResult
{
    SearchResult(std::string prefix, std::vector<std::string> result):
        prefix(std::move(prefix)), result(std::move(result))
    {}
    std::string prefix;
    std::vector<std::string> result;
};

/*
 * This class stores the search result of all previous searches,
 * if they are a substring of the current search,
 * so that the search is more efficient
 */
class IterativeSearch
{
private:
    // The complete word list is always saved as the first element of previousSearchResults
    std::vector<std::shared_ptr<const SearchResult>> previousSearchResults;
public:
    explicit IterativeSearch(const std::vector<std::string>& wordList)
    {
        // Initialize the previousSearchResults with the given word list for the empty prefix
        previousSearchResults.push_back(std::make_shared<const SearchResult>("", wordList));
    }

    /*
     * Search for the given prefix
     * Not thread-safe!! Do not execute in different threads simultaneously
     * Returns a shared pointer to the constant SearchResult object
     */
    std::shared_ptr<const SearchResult> search(const std::string& prefix)
    {
        // When the previous search result is not a substring of the new one, pop it from the vector
        // The first element in previousSearchResults always has the prefix "" and will therefore not be deleted
        while(prefix.compare(0, previousSearchResults.back()->prefix.length(), previousSearchResults.back()->prefix) != 0)
        {
            previousSearchResults.pop_back();
        }

        if(previousSearchResults.back()->prefix == prefix)
            return previousSearchResults.back();

        // Start a new search starting from the previous result that is a substring of prefix
        previousSearchResults.push_back(std::make_shared<SearchResult>(
            prefix,
            find_matching_prefix_multithreaded(
                previousSearchResults.back()->result.cbegin(),
                previousSearchResults.back()->result.cend(),
                prefix)
            ));
        return previousSearchResults.back();
    }
};


#endif //VECTOR_ITERATIVESEARCH_H
