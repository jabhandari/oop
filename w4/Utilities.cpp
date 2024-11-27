//#include "Utilities.h"
//#include <string>
//#include <stdexcept>
//#include <algorithm>
//#include <cctype>
//namespace seneca {
//    char Utilities::m_delimiter = '|';
//void Utilities::setFieldWidth(size_t newWidth)
//{
//	m_widthField = newWidth;
//}
//size_t Utilities::getFieldWidth() const
//{
//	return m_widthField;
//}
//std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
//{
//    if (next_pos >= str.size()) {
//        more = false;
//        return "";
//    }
//
//    size_t end_pos = str.find(m_delimiter, next_pos);
//    if (end_pos == next_pos) {
//        throw std::invalid_argument("Delimiter found at next_pos.");
//    }
//
//    std::string token = str.substr(next_pos, end_pos - next_pos);
//    token.erase(0, token.find_first_not_of(' ')); // Trim leading spaces
//    token.erase(token.find_last_not_of(' ') + 1); // Trim trailing spaces
//
//    next_pos = (end_pos == std::string::npos) ? std::string::npos : end_pos + 1;
//    more = next_pos != std::string::npos;
//
//    if (token.size() > m_widthField) {
//        m_widthField = token.size();
//    }
//
//    return token;
//}
//void Utilities::setDelimiter(char newDelimiter)
//{
//    m_delimiter = newDelimiter;
//    
//}
//char Utilities::getDelimiter()
//{
//	return m_delimiter;
//}
//}
#include"Utilities.h"
#include <string>
#include <stdexcept>
#include <algorithm>
#include <cctype>
namespace seneca {
        char Utilities::m_delimiter = '|';

        void Utilities::setFieldWidth(size_t newWidth)
        {
            m_widthField = newWidth;
        }

        size_t Utilities::getFieldWidth() const
        {
            return m_widthField;
        }

        std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
        {
            if (next_pos >= str.size()) {
                // No more tokens to extract
                more = false;
                return "";
            }

            // Find the next delimiter
            size_t end_pos = str.find(m_delimiter, next_pos);

            if (end_pos == next_pos) {
                // If the delimiter is at the current position, it means an empty token
                more = false;
                throw std::invalid_argument("Delimiter found at next_pos without a token.");
            }

            // Extract the token
            std::string token = (end_pos == std::string::npos)
                ? str.substr(next_pos)  // Extract till the end of the string
                : str.substr(next_pos, end_pos - next_pos);

            // Trim leading and trailing spaces
            token.erase(0, token.find_first_not_of(' '));
            token.erase(token.find_last_not_of(' ') + 1);

            // Update next_pos for the next token
            next_pos = (end_pos == std::string::npos) ? std::string::npos : end_pos + 1;

            // Set 'more' to true if there are more tokens to extract
            more = (next_pos != std::string::npos);

            // Update field width if the current token's size is greater
            if (token.size() > m_widthField) {
                m_widthField = token.size();
            }

            return token;
        }

        void Utilities::setDelimiter(char newDelimiter)
        {
            m_delimiter = newDelimiter;
        }

        char Utilities::getDelimiter()
        {
            return m_delimiter;
        }
    
}
