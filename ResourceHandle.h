#pragma once
#include "pch.h"
#include <string>
#include <map>
#include <memory>
#include <cassert>
template <typename Resource, typename Indentifier>
class ResourceHandle
{
public:
	void Load(Indentifier ID,const std::string& filename);
	template <typename Parameter>
	void Load(Indentifier ID, const std::string& filename, const Parameter& secondParam);

	Resource& Get(Indentifier ID);
	const Resource& Get(Indentifier ID)const;
	
private:
	void Insert(Indentifier ID,std::unique_ptr<Resource> res);
private:
	std::map<Indentifier, std::unique_ptr<Resource>> m_Resources;
};

template<typename Resource, typename Indentifier>
inline void ResourceHandle<Resource, Indentifier>::Load(Indentifier ID, const std::string & filename)
{
	std::unique_ptr<Resource> resource(new Resource());
	
	if (!resource->loadFromFile(filename))
		throw std::runtime_error("ResourceHandle::load - Failed to load" + filename);

	Insert(ID, std::move(resource));
}

template<typename Resource, typename Indentifier>
inline Resource& ResourceHandle<Resource, Indentifier>::Get(Indentifier ID)
{
	auto res = m_Resources.find(ID);
	assert(res != m_Resources.end());
	return *res->second;
}

template<typename Resource, typename Indentifier>
inline const Resource & ResourceHandle<Resource, Indentifier>::Get(Indentifier ID) const
{
	auto res = m_Resources.find(ID);
	assert(res != m_Resources.end());
	return *res->second;
}

template<typename Resource, typename Indentifier>
inline void ResourceHandle<Resource, Indentifier>::Insert(Indentifier ID, std::unique_ptr<Resource> res)
{
	auto result = m_Resources.insert(std::make_pair(ID, std::move(res)));
	assert(result.second);
}

template<typename Resource, typename Indentifier>
template<typename Parameter>
inline void ResourceHandle<Resource, Indentifier>::Load(Indentifier ID, const std::string & filename, const Parameter & secondParam)
{
	std::unique_ptr<Resource> resource(new Resource());

	if (!resource->loadFromFile(filename, secondParam))
		throw std::runtime_error("ResourceHandle::load - Failed to load" + filename);

	Insert(ID, resource);
}
