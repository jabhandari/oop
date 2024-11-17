#ifndef SENECA_COLLECTION_H
#define SENECA_COLLECTION_H

#include "mediaItem.h"
#include <string>
#include <vector>

namespace seneca {

	class Collection {
		std::string m_name;
		std::vector<MediaItem*> m_items;
		void (*m_observer)(const Collection&, const MediaItem&);

	public:
		Collection(const std::string& name);
		Collection(const Collection& other) = delete;
		Collection& operator=(const Collection& other) = delete;
		Collection(Collection&& other) noexcept = delete;
		Collection& operator=(Collection&& other) noexcept = delete;

		~Collection();

		const std::string& name() const;

		size_t size() const;

		void setObserver(void (*observer)(const Collection&, const MediaItem&));

		Collection& operator+=(MediaItem* item);

		MediaItem* operator[](size_t idx) const;

		MediaItem* operator[](const std::string& title) const;

		void removeQuotes();

		void sort(const std::string& field);
	};

	std::ostream& operator<<(std::ostream& os, const Collection& collection);

} 

#endif