#include "tvShow.h"
#include <iomanip>
#include <algorithm>
#include <numeric>
#include "settings.h"
namespace seneca {

     
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
      
        if (strShow[0] == '#' || strShow.empty())
            throw "Not a valid show.";

        std::string tokens[4]{};
        std::stringstream ss(strShow);
        std::string token;
        size_t idx{ 0 };

        
        while (std::getline(ss, token, ',') && idx < 4)
        {
            MediaItem::trim(token); 
            tokens[idx++] = token;
        }

        TvShow* temp = new TvShow(tokens[0], tokens[1], static_cast<unsigned short>(std::stoi(tokens[2])), tokens[3]);
        return temp;
    }


    double TvShow::getEpisodeAverageLength() const
    {
      
        return std::accumulate(m_episodes.begin(), m_episodes.end(), (double)0,
            [&](double total, const TvEpisode& ep)
            {
                return total + ep.m_length;
            }) / m_episodes.size();
    }

    std::list<std::string> TvShow::getLongEpisodes() const
    {
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
