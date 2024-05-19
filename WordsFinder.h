//
// Created by nilerrors on 5/18/24.
//

#ifndef WFINDER_WORDSFINDER_H
#define WFINDER_WORDSFINDER_H

#include <string>
#include <unordered_map>
#include <queue>
#include <memory>
#include "WordSegmenter.h"
#include "AhoCorasick.hpp"

namespace wfinder
{

class WordsFinder
{
public:
    explicit WordsFinder(const std::vector<std::string> &words, const WordsOptions &options = {
            .ignore_case = false,
            .whole_word = true,
            .allowed_word_characters = REAL_ALPHANUM,
    });

    virtual ~WordsFinder();

    SegmentedWords find_in_text(const std::string &text);

private:
    std::vector<std::string> words;
    WordsOptions options;
    std::unique_ptr<AhoCorasick> aho_corasick;
};

}

#endif //WFINDER_WORDSFINDER_H
