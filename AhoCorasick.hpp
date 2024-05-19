//
// Created by nilerrors on 5/18/24.
//

#ifndef WFINDER_AHOCORASICK_H
#define WFINDER_AHOCORASICK_H

#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <memory>
#include "WordSegmenter.h"

namespace wfinder
{

class AhoCorasick
{
public:
    struct ACTreeNode
    {
        typedef std::shared_ptr<ACTreeNode> Ptr;
        typedef std::pair<const char, Ptr> Child;
        typedef std::unordered_map<char, Ptr> Children;
        Children children;
        std::string const *word = nullptr;
        ACTreeNode::Ptr fail;
    };

    explicit AhoCorasick(const std::vector<std::string> &words, const WordsOptions &opts = WordsOptions{
            .ignore_case = true,
            .whole_word = true,
            .allowed_word_characters = REAL_ALPHANUM})
    {
        top = build_tree(words, opts);
        options = opts;
    }

    std::vector<SegmentedWord> find_in_text(const std::string *text)
    {
        return find_in_text(text, top, options);
    }

    static ACTreeNode::Ptr build_tree(const std::vector<std::string> &words, const WordsOptions &opts = {})
    {
        ACTreeNode::Ptr root = std::make_shared<ACTreeNode>();
        for (const std::string &word: words)
        {
            ACTreeNode::Ptr node = root;
            for (char c: word)
            {
                if (opts.ignore_case)
                {
                    c = static_cast<char>(std::tolower(c));
                }
                if (node->children.count(c) == 0)
                {
                    node->children[c] = std::make_unique<ACTreeNode>();
                }
                node = node->children[c];
            }
            node->word = &word;
        }

        std::queue<ACTreeNode::Ptr> q;
        q.push(root);
        while (!q.empty())
        {
            ACTreeNode::Ptr node = q.front();
            q.pop();
            for (const auto &[c, child]: node->children)
            {
                ACTreeNode::Ptr fail = node->fail;
                while (fail != nullptr && fail->children.count(c) == 0)
                {
                    fail = fail->fail;
                }
                if (fail == nullptr)
                {
                    child->fail = root;
                }
                else
                {
                    child->fail = fail->children[c];
                }
                if (child->word != nullptr)
                {
                    q.push(child);
                }
            }
        }
        return root;
    }

    static std::vector<SegmentedWord>
    find_in_text(const std::string *text, const ACTreeNode::Ptr &root, const WordsOptions &options)
    {
        std::vector<SegmentedWord> results;
        ACTreeNode::Ptr node = root;
        for (size_t i = 0; i < text->size(); i++)
        {
            char c = text->at(i);
            if (options.ignore_case)
            {
                c = static_cast<char>(std::tolower(c));
            }
            while (node != nullptr && node->children.count(c) == 0)
            {
                node = node->fail;
            }
            if (node == nullptr)
            {
                node = root;
            }
            else
            {
                node = node->children[c];
                if (node->word != nullptr)
                {
                    SegmentedWord segmentedWord = SegmentedWord{*node->word, text, i - node->word->size() + 1};
                    if (options.whole_word &&
                        !WordSegmenter::is_full_word(segmentedWord, options.allowed_word_characters))
                    {
                        continue;
                    }
                    results.push_back(segmentedWord);
                }
            }
        }
        return results;
    }

private:
    ACTreeNode::Ptr top;
    WordsOptions options;
};

}

#endif //WFINDER_AHOCORASICK_H
