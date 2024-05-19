#include <iostream>
#include "WordSegmenter.h"
#include "WordsFinder.h"

int main()
{
    std::string text = "Hello, World! This is a test text. "
                       "'s Morgens ga ik naar school. "
                       "NASA is an acronym for National Aeronautics and Space Administration.";


    // Words Segmentation -> breaking sentences into words
    std::cout << "Word Segmentation:" << std::endl;
    wfinder::WordSegmenter segmenter({
            .words_in_lowercase = true,
            .allowed_word_characters = REAL_ALPHANUM,
    });
    wfinder::SegmentedWords segmented_words = segmenter.segment(&text);

    for (const wfinder::SegmentedWord &word: segmented_words)
    {
        std::cout << word.word << " at " << word.start << std::endl;
    }

    // Words Finder -> finding words in text
    std::cout << "\nWords Finder:" << std::endl;
    std::vector<std::string> words = {"nASa", "A"};
    wfinder::WordsFinder words_finder(words, {
            .ignore_case = true,
            .whole_word = true,
            .allowed_word_characters = REAL_ALPHANUM,
    });

    for (const wfinder::SegmentedWord &word: words_finder.find_in_text(text))
    {
        std::cout << "'" << word.word << "'" << " found at " << word.start << " in text: '"
                  << text.substr(word.start, word.word.size()) << "'" << std::endl;
    }

    return 0;
}
