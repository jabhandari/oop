#ifndef  SENECA_COLLECTION_H
#define SENECA_COLLECTION_H

#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <functional>
#include "mediaItem.h"
namespace seneca {


    class Collection {
        std::string m_name;
        std::vector<seneca::MediaItem*> m_items;
        void (*m_observer)(const Collection&, const seneca::MediaItem&) = nullptr;//no seneca

    public:
        Collection(const std::string& name) : m_name(name),m_observer(nullptr) {}

        Collection(const Collection&) = delete;
        Collection& operator=(const Collection&) = delete;
        Collection(Collection&&) = delete;
        Collection& operator=(Collection&&) = delete;
        ~Collection() {
            for (auto item : m_items) {
                delete item;
            }
        }

        const std::string& name() const { return m_name; }
        size_t size() const { return m_items.size(); }

        void setObserver(void (*observer)(const Collection&, const seneca::MediaItem&)) {
            m_observer = observer;
        }

        Collection& operator+=(seneca::MediaItem* item) {
            bool already = std::any_of(m_items.begin(), m_items.end(), [item](const MediaItem* originItem)
                {
                    return originItem->getTitle() == item->getTitle();
                });

            if (already)
            {
                delete item;
            }
            else
            {
                m_items.push_back(item);
                if (m_observer)
                {
                    m_observer(*this, *item);
                }
            }

            return *this;
        }
        seneca::MediaItem* operator[](size_t idx) const {
            if (idx >= m_items.size()) {
                throw std::out_of_range("Bad index [" + std::to_string(idx) +
                    "]. Collection has [" + std::to_string(m_items.size()) + "] items.");
            }
            return m_items[idx];
        }

        seneca::MediaItem* operator[](const std::string& title) const {
       
            MediaItem* result = nullptr;

            auto address = std::find_if(m_items.begin(), m_items.end(), [title](const MediaItem* item)
                {
                    return item->getTitle() == title;
                });

            if (address != m_items.end())
            {
                result = *address;
            }

            return result;
        }

        void removeQuotes() {
         
            std::for_each(m_items.begin(), m_items.end(), [](MediaItem* item)
                {
                    std::string title = item->getTitle();
                    std::string summary = item->getSummary();


                    if (!title.empty() && title.front() == '"')
                    {
                        title.erase(0, 1);
                    }
                    if (!title.empty() && title.back() == '"')
                    {
                        title.erase(title.size() - 1);
                    }

                    if (!summary.empty() && summary.front() == '"')
                    {
                        summary.erase(0, 1);
                    }
                    if (!summary.empty() && summary.back() == '"')
                    {
                        summary.erase(summary.size() - 1);
                    }

                    item->setTitle(title);
                    item->setSummary(title);

                });

        }

        void sort(const std::string& field) {
          
            std::sort(m_items.begin(), m_items.end(), [field](const MediaItem* m1, const MediaItem* m2)
                {
                    bool result = false;
                    if (field == "Title")
                    {
                        result = m1->getTitle() < m2->getTitle();

                    }
                    else if (field == "Year")
                    {
                        result = m1->getYear() < m2->getYear();
                    }
                    return result;
                });
        }

        friend std::ostream& operator<<(std::ostream& out, const Collection& collection) {
            for (const auto& item : collection.m_items) {
                item->display(out);
            }
            return out;
        }
    };
}

#endif 