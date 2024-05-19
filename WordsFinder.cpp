//
// Created by nilerrors on 5/18/24.
//

#include "WordsFinder.h"
#include "AhoCorasick.hpp"

wfinder::WordsFinder::WordsFinder(const std::vector<std::string> &words, const wfinder::WordsOptions &options)
{
    this->words = words;
    this->options = options;
}

wfinder::WordsFinder::~WordsFinder() = default;

wfinder::SegmentedWords wfinder::WordsFinder::find_in_text(const std::string &text)
{
    if (aho_corasick == nullptr)
    {
        aho_corasick = std::make_unique<AhoCorasick>(words, options);
    }

    wfinder::SegmentedWords segmented_words = aho_corasick->find_in_text(&text);

    return segmented_words;
}
