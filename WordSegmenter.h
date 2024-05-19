//
// Created by nilerrors on 5/18/24.
//

#ifndef WFINDER_WORDSEGMENTER_H
#define WFINDER_WORDSEGMENTER_H

#include <string>
#include <vector>

namespace wfinder
{

struct WordsOptions
{
    bool ignore_case = false;
    bool whole_word = true;
    std::string allowed_word_characters;
};

struct SegmentedWord
{
    std::string word;
    const std::string *in_text;
    size_t start;
};

using SegmentedWords = std::vector<SegmentedWord>;

#define LOWERCASE_ALPHABET "abcdefghijklmnopqrstuvwxyz"
#define UPPERCASE_ALPHABET "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define DIGITS             "0123456789"
#define ALPHANUM           LOWERCASE_ALPHABET UPPERCASE_ALPHABET DIGITS
#define REAL_ALPHANUM      ALPHANUM "'"

class WordSegmenter
{
public:
    struct Options
    {
        bool words_in_lowercase;
        std::string allowed_word_characters;
    };

    explicit WordSegmenter(const Options &options = Options{
            .words_in_lowercase = true,
            .allowed_word_characters = REAL_ALPHANUM,
    });

    SegmentedWords segment(const std::string *text) const;

    virtual ~WordSegmenter();

    static bool is_full_word(const SegmentedWord &segmentedWord, const std::string &allowed_word_characters)
    {
        size_t end = segmentedWord.start + segmentedWord.word.size();

        if (segmentedWord.start == 0 && end == segmentedWord.in_text->size())
        {
            return true;
        }
        if (segmentedWord.start == 0 && end < segmentedWord.in_text->size())
        {
            return allowed_word_characters.find(segmentedWord.in_text->at(end)) == std::string::npos;
        }
        if (segmentedWord.start > 0 && end == segmentedWord.in_text->size())
        {
            return allowed_word_characters.find(segmentedWord.in_text->at(segmentedWord.start - 1)) ==
                   std::string::npos;
        }
        return allowed_word_characters.find(segmentedWord.in_text->at(segmentedWord.start - 1)) == std::string::npos &&
               allowed_word_characters.find(segmentedWord.in_text->at(end)) == std::string::npos;
    }

private:
    Options options;
};

}

#endif //WFINDER_WORDSEGMENTER_H
