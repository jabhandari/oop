#define _CRT_SECURE_NO_WARNINGS
#include "dictionary.h"
#include <fstream>
#include <iostream>
#include <sstream>
namespace seneca {
	void Dictionary::loadFromFile(const char* filename)
	{
        std::ifstream file(filename);
        if (!file.is_open()) return;

        Word* words = nullptr;
        size_t capacity = 0;
        size_t size = 0;

        std::string line;
        while (std::getline(file, line)) {
            if (size >= capacity) {
                capacity = capacity == 0 ? 1 : capacity * 2;
                Word* newWords = new Word[capacity];
                if (words) {
                    std::copy(words, words + size, newWords);
                    delete[] words;
                }
                words = newWords;
            }
            std::istringstream iss(line);
            std::string word, pos, definition;

            if (std::getline(iss, word, ',') && std::getline(iss, pos, ',') && std::getline(iss, definition)) {
                words[size++] = { word, definition, parsePartOfSpeech(pos) };
            }
        }

        m_words = words;
        m_size = size;
	}

    PartOfSpeech Dictionary::parsePartOfSpeech(const std::string& pos)
    {
        if (pos == "n." || pos == "n. pl.") {
            return PartOfSpeech::Noun;
        }
        if (pos == "adv.") {
            return PartOfSpeech::Adverb;
        }
        if (pos == "a.") {
            return PartOfSpeech::Adjective;
        }
        if (pos.find("v.") == 0) {
            return PartOfSpeech::Verb;
        }
        if (pos == "prep.") {
            return PartOfSpeech::Preposition;
        }
        if (pos == "pron.") {
            return PartOfSpeech::Pronoun;
        }
        if (pos == "conj.") {
            return PartOfSpeech::Conjunction;
        }
        if (pos == "interj.") {
            return PartOfSpeech::Interjection;
        }
        return PartOfSpeech::Unknown;
    }

    Dictionary::Dictionary(const char* filename)
    {
        loadFromFile(filename);
    }

    Dictionary::~Dictionary()
    {
        delete[] m_words;
    }

    void Dictionary::searchWord(const char* word)
    {
        static const char* posStrings[] = {
        "unknown",
        "noun",
        "pronoun",
        "adjective",
        "adverb",
        "verb",
        "preposition",
        "conjunction",
        "interjection"
        };

        for (size_t i = 0; i < m_size; ++i) {
            if (m_words[i].m_word == word) {
                std::cout << m_words[i].m_word << " - ";
                if (seneca::g_settings.m_verbose && m_words[i].m_pos != PartOfSpeech::Unknown) {
                    std::cout << "(" << posStrings[static_cast<int>(m_words[i].m_pos)] << ") ";
                }
                std::cout << m_words[i].m_definition << std::endl;
                return;
            }
        }

        std::cout << "Word '" << word << "' was not found in the dictionary." << std::endl;
    }
 }
