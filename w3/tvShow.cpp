#include "tvShow.h"
#include <iomanip>
#include <algorithm>
#include <numeric>
#include "settings.h"
namespace seneca {

    ///TvShow::TvShow(unsigned int id, const std::string& title, const std::string& summary, unsigned short year)
    //    : MediaItem(title, summary, year), m_id(id) {}
   
    TvShow::TvShow(const std::string& id, const std::string& title, unsigned short year, const std::string& summary) :
        MediaItem(title, summary, year), m_id(id) {}


    void TvShow::display(std::ostream& out) const
    {
        if (g_settings.m_tableView)
        {
            out << "S | ";
            out << std::left << std::setfill('.') << std::setw(50) << getTitle() << " | ";
            out << std::right << std::setfill(' ') << std::setw(2) << m_episodes.size() << " | ";
            out << std::setw(4) << getYear() << " | ";
            if (g_settings.m_maxSummaryWidth > -1)
            {
                if (static_cast<short>(getSummary().size()) <= g_settings.m_maxSummaryWidth)
                    out << getSummary();
                else
                    out << getSummary().substr(0, g_settings.m_maxSummaryWidth - 3) << "...";
            }
            else
                out << getSummary();
            out << std::endl;
        }
        else
        {
            out << getTitle() << " [" << getYear() << "]\n";
            out << std::string(getTitle().size() + 7, '-') << '\n';
            size_t pos = 0;
            while (pos < getSummary().size())
            {
                out << "    " << getSummary().substr(pos, g_settings.m_maxSummaryWidth) << '\n';
                pos += g_settings.m_maxSummaryWidth;
            }
            for (const auto& episode : m_episodes)
            {
                out << std::setfill('0') << std::right;
                out << "    S" << std::setw(2) << episode.m_season
                    << "E" << std::setw(2) << episode.m_numberInSeason << " ";
                if (!episode.m_title.empty())
                    out << episode.m_title << '\n';
                else
                    out << "Episode " << episode.m_numberOverall << '\n';

                pos = 0;
                while (pos < episode.m_summary.size())
                {
                    out << "            " << episode.m_summary.substr(pos, g_settings.m_maxSummaryWidth - 8) << '\n';
                    pos += g_settings.m_maxSummaryWidth - 8;
                }
            }
            out << std::string(getTitle().size() + 7, '-') << std::setfill(' ') << '\n';
        }
    }

    TvShow* TvShow::createItem(const std::string& strShow)
    {
       /* if (strShow.empty() || strShow[0] == '#')
            throw std::invalid_argument("Not a valid show.");

        std::istringstream ss(strShow);
        std::string token;
        std::vector<std::string> tokens;

        while (std::getline(ss, token, ','))
        {
            MediaItem::trim(token);
            tokens.push_back(token);
        }

        if (tokens.size() != 4)
            throw std::invalid_argument("Invalid format for show data.");

        unsigned int id = std::stoi(tokens[0]);
        unsigned short year = static_cast<unsigned short>(std::stoi(tokens[2]));

        return new TvShow(id, tokens[1], tokens[3], year);*/

        // Check for comment line or empty string
        if (strShow[0] == '#' || strShow.empty())
            throw "Not a valid show.";

        std::string tokens[4]{};
        std::stringstream ss(strShow);
        std::string token;
        size_t idx{ 0 };

        // Read tokens from the string
        while (std::getline(ss, token, ',') && idx < 4)
        {
            MediaItem::trim(token); // Remove spaces from token
            tokens[idx++] = token;
        }

        TvShow* temp = new TvShow(tokens[0], tokens[1], static_cast<unsigned short>(std::stoi(tokens[2])), tokens[3]);

        // Create and return TvShow object
        return temp;
    }


    double TvShow::getEpisodeAverageLength() const
    {
       /* auto totalLength = std::accumulate(m_episodes.begin(), m_episodes.end(), 0, [](int sum, const TvEpisode& ep) {
            return sum + ep.m_length;
            });
        return m_episodes.empty() ? 0 : static_cast<double>(totalLength) / m_episodes.size();*/
        return std::accumulate(m_episodes.begin(), m_episodes.end(), (double)0,
            [&](double total, const TvEpisode& ep)
            {
                return total + ep.m_length;
            }) / m_episodes.size();
    }

    std::list<std::string> TvShow::getLongEpisodes() const
    {
        //std::list<std::string> longEpisodes;
        //std::copy_if(m_episodes.begin(), m_episodes.end(), std::back_inserter(longEpisodes), [](const TvEpisode& ep) {
        //    return ep.m_length >= 3600; ///////////////////
        //    });
        //return longEpisodes;
        std::list<std::string> longEpisode;

        std::for_each(m_episodes.begin(), m_episodes.end(), [&](const TvEpisode& episode)
            {
                if (episode.m_length >= 3600)
                {
                    longEpisode.push_back(episode.m_title);
                }
            });
        return longEpisode;
    }
}
