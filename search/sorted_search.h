//
// Created by david on 05.03.24.
//

#ifndef VECTOR_SORTED_SEARCH_H
#define VECTOR_SORTED_SEARCH_H

#include <vector>
#include <memory>
#include <set>

typedef std::shared_ptr<const std::string> SharedString;

std::string next_string_value(const std::string& str)
{
    return "not implemented yet";
}

std::vector<SharedString> search_prefix_in_multiset(std::multiset<SharedString> word_list, const std::string& prefix)
{
    SharedString prefix_sp = std::make_shared<const std::string>(prefix);
    std::string prefix_next_word = next_string_value(prefix);
    prefix_next_word.back()++;
    SharedString prefix_next_word_sp = std::make_shared<const std::string>(prefix_next_word);
    return {word_list.lower_bound(prefix_sp), word_list.lower_bound(prefix_next_word_sp)};
}

#endif //VECTOR_SORTED_SEARCH_H
