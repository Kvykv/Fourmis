#ifndef RESOURCEHOLDER_H
#define RESOURCEHOLDER_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <string>
#include <memory>
#include <cassert>

// Resource ID for sf::Texture

enum TextureID
{
    TextureAnt,
    TextureEgg,
};


template <typename Resource, typename Identifier>
class ResourceHolder
{
    public:
        void load(Identifier id, const std::string& fileName);

        template <typename Parameter>
		void load(Identifier id, const std::string& filename, const Parameter& parameter);

        Resource& get(Identifier id);

        const Resource& get(Identifier id) const;

    protected:

    private:
        void insertResource(Identifier id, std::unique_ptr<Resource> resource);
        std::map<Identifier, std::unique_ptr<Resource>> m_resourceMap;
};

///************************************************************************************************
///************************************************************************************************
///************************************************************************************************
///************************************************************************************************

template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& filename)
{
	// Create and load resource
	std::unique_ptr<Resource> resource(new Resource());
	if (!resource->loadFromFile(filename))
		throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);

	// If loading successful, insert resource to map
	insertResource(id, std::move(resource));
}

template <typename Resource, typename Identifier>
template <typename Parameter>

void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& filename, const Parameter& parameter)
{
	// Create and load resource
	std::unique_ptr<Resource> resource(new Resource());
	if (!resource->loadFromFile(filename, parameter))
		throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);

	// If loading successful, insert resource to map
	insertResource(id, std::move(resource));
}

template <typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::get(Identifier id)
{
	auto found = m_resourceMap.find(id);
	assert(found != m_resourceMap.end());

	return *found->second;
}

template <typename Resource, typename Identifier>
const Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) const
{
	auto found = m_resourceMap.find(id);
	assert(found != m_resourceMap.end());

	return *found->second;
}

template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::insertResource(Identifier id, std::unique_ptr<Resource> resource)
{
	// Insert and check success
	auto inserted = m_resourceMap.insert(std::make_pair(id, std::move(resource)));
	assert(inserted.second);
}

using TextureHolder = ResourceHolder<sf::Texture, TextureID>;

#endif // RESOURCEHOLDER_H
