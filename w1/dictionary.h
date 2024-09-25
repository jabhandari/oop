#ifndef SENECA_DICTIONARY_H
#define SENECA_DICTIONARY_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "settings.h"

namespace seneca {

    enum class PartOfSpeech {
        Unknown,
        Noun,
        Pronoun,
        Adjective,
        Adverb,
        Verb,
        Preposition,
        Conjunction,
        Interjection
    };

    struct Word {
        std::string m_word{};
        std::string m_definition{};
        PartOfSpeech m_pos = PartOfSpeech::Unknown;
    };

    class Dictionary {
    private:
        Word* m_words = nullptr;
        size_t m_size = 0;

    public:
        Dictionary() {};
        void loadFromFile(const char* filename);
        PartOfSpeech parsePartOfSpeech(const std::string& pos);
        Dictionary(const char* filename);
        ~Dictionary();
        void searchWord(const char* word);
    
    };

} // namespace seneca

#endif
