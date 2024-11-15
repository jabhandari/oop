#pragma once
#ifndef  SENECA_SPELLCHECKER_H
#define SENECA_SPELLCHECKER_H

#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdexcept>
namespace seneca {


    class SpellChecker {
        std::string m_badWord[6];
        std::string m_goodWord[6];
       // size_t m_replacement[6] = { 0 }; 
        int m_count[6] = { 0 };

    public:
        SpellChecker(const char* filename); /*{
            std::ifstream file(filename);
            if (!file) {
                throw "Bad file name!";
            }

            for (int i = 0; i < 6 && file; ++i) {
                std::string bad, good;
                file >> bad >> good;
                m_badWords[i] = bad;
                m_goodWords[i] = good;
            }
        }*/

        void operator()(std::string& text); /*{
            for (size_t i = 0; i < 6; ++i) {
                size_t pos = text.find(m_badWords[i]);
                while (pos != std::string::npos) {
                    text.replace(pos, m_badWords[i].length(), m_goodWords[i]);
                    m_replacements[i]++;
                    pos = text.find(m_badWords[i], pos + m_goodWords[i].length());
                }
            }
        }*/

        void showStatistics(std::ostream& out) const;/* {
            for (size_t i = 0; i < 6; ++i) {
                out << std::setw(15) << m_badWords[i] << ": " << m_replacements[i] << " replacements\n";
            }
        }*/
    };
}
#endif