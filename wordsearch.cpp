#include "wordsearch.h"
#include "search/IterativeSearch.h"
#include "search/read_dictionary.h"

void WordSearch::run()
{
    IterativeSearch iterativeSearch(read_dictionary("/home/david/wordlist-german.txt"));
    std::string search = "";

    emit searchResult(search, iterativeSearch.search(""));
    while(true)
    {
        // Wait for currentSearch to update and copy the value to the search variable
        {
            std::unique_lock<std::mutex> lock(searchChangedMutex);
            while(search == currentSearch)
            {
                searchChanged.wait(lock);
            }
            search = currentSearch;
        }

        emit searchResult(search, iterativeSearch.search(search));
    }
}


void WordSearch::search(const QString& search)
{
    {
        std::lock_guard<std::mutex> lock(searchChangedMutex);
        currentSearch = search.toStdString();
    }
    searchChanged.notify_all();
}
