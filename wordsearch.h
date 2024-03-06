#ifndef WORDSEARCH_H
#define WORDSEARCH_H

#include <QObject>
#include <QThread>
#include "search/IterativeSearch.h"
#include <random>
#include <algorithm>

class WordSearch : public QThread
{
    Q_OBJECT

public:
    void run() override;
public slots:
    void search(const QString& search);

signals:
    void searchResult(const std::string& search, std::shared_ptr<const SearchResult> result);
private:
    std::condition_variable searchChanged;
    std::mutex searchChangedMutex;
    std::string currentSearch;
};

#endif // WORDSEARCH_H
