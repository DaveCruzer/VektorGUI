//
// Created by david on 03.03.24.
//

#ifndef VECTOR_READ_DICTIONARY_H
#define VECTOR_READ_DICTIONARY_H

#include <memory>
#include <vector>
#include <fstream>

std::vector<std::string> read_dictionary(const std::string& filename)
{
    std::ifstream infile(filename);
    std::string line;
    std::vector<std::string> result;
    while(std::getline(infile, line))
    {
        result.emplace_back(line);
    }
    return result;
}

#endif //VECTOR_READ_DICTIONARY_H
