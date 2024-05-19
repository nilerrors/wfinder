//
// Created by nilerrors on 5/18/24.
//

#include <algorithm>
#include "WordSegmenter.h"

wfinder::WordSegmenter::WordSegmenter(const WordSegmenter::Options &options)
{
    this->options = options;
}

wfinder::WordSegmenter::~WordSegmenter() = default;

wfinder::SegmentedWords wfinder::WordSegmenter::segment(const std::string *text) const
{
    wfinder::SegmentedWords words;

    size_t start = 0;
    bool in_word = false;

    for (size_t i = 0; i < text->size(); i++)
    {
        char c = text->at(i);

        if (options.words_in_lowercase)
        {
            c = static_cast<char>(std::tolower(c));
        }

        if (options.allowed_word_characters.find(c) != std::string::npos)
        {
            if (!in_word)
            {
                start = i;
                in_word = true;
            }
        }
        else
        {
            if (in_word)
            {
                size_t end = i;
                wfinder::SegmentedWord segmented_word = {text->substr(start, end - start), text, start};
                if (options.words_in_lowercase)
                {
                    std::transform(
                            segmented_word.word.begin(), segmented_word.word.end(), segmented_word.word.begin(),
                            [](char c) { return static_cast<char>(std::tolower(c)); });
                }
                words.push_back(segmented_word);
                in_word = false;
            }
        }
    }

    if (in_word)
    {
        words.push_back({text->substr(start, text->size() - start), text, start});
    }

    return words;
}
