#define _CRT_SECURE_NO_WARNINGS
#include "dictionary.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstring>
#include <iomanip>

namespace seneca {

    Dictionary::Dictionary(const Dictionary& other)
        : m_size(other.m_size), m_words(nullptr) {
        if (other.m_words) {
            m_words = new Word[m_size];
            for (size_t i = 0; i < m_size; ++i) {
                m_words[i].m_word = other.m_words[i].m_word;
                m_words[i].m_definition = other.m_words[i].m_definition;
                m_words[i].m_pos = other.m_words[i].m_pos;
            }
        }
    }

    Dictionary& Dictionary::operator=(const Dictionary& other) {
        if (this != &other) {
            delete[] m_words;

            m_size = other.m_size;
            m_words = nullptr;

            if (other.m_words) {
                m_words = new Word[m_size];
                for (size_t i = 0; i < m_size; ++i) {
                    m_words[i].m_word = other.m_words[i].m_word;
                    m_words[i].m_definition = other.m_words[i].m_definition;
                    m_words[i].m_pos = other.m_words[i].m_pos;
                }
            }
        }
        return *this;
    }

    Dictionary::Dictionary(Dictionary&& other) noexcept
        : m_size(other.m_size), m_words(other.m_words) {
        other.m_size = 0;
        other.m_words = nullptr;
    }

    Dictionary& Dictionary::operator=(Dictionary&& other) noexcept {
        if (this != &other) {
            delete[] m_words;
            m_words = other.m_words;
            m_size = other.m_size;

            other.m_words = nullptr;
            other.m_size = 0;
        }
        return *this;
    }

    void Dictionary::loadFromFile(const char* filename) {
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

    PartOfSpeech Dictionary::parsePartOfSpeech(const std::string& pos) {
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

    Dictionary::Dictionary(const char* filename) {
        loadFromFile(filename);
    }

    Dictionary::~Dictionary() {
        delete[] m_words;
    }

    void Dictionary::searchWord(const char* word) {
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
        bool found = false;
        for (size_t i = 0; i < m_size; ++i) {
            if (std::strcmp(m_words[i].m_word.c_str(), word) == 0) {
                if (!found) {
                    std::cout << m_words[i].m_word;
                }
                else {
                    std::cout << std::setw(std::strlen(word)) << " ";
                }
                std::cout << " - ";
                if (seneca::g_settings.m_verbose && m_words[i].m_pos != PartOfSpeech::Unknown) {
                    std::cout << "(" << posStrings[static_cast<int>(m_words[i].m_pos)] << ") ";
                }
                std::cout << m_words[i].m_definition << std::endl;
                found = true;
                if (!seneca::g_settings.m_show_all) {
                    break;
                }
            }
        }

        if (!found) {
            std::cout << "Word '" << word << "' was not found in the dictionary." << std::endl;
        }
    }

} // namespace seneca
