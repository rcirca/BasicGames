#pragma once
#include <unordered_map>
#include "Utilities.h"
#include <fstream>

template<typename Derived, typename T>
class ResourceManager
{
public:
	ResourceManager(const std::string& pPathsFile) { loadPaths(pPathsFile); }
	virtual ~ResourceManager() { purgeResources(); }

	T* getResource(const std::string& pId)
	{
		auto res = find(pId);
		return (res ? res->first : nullptr);
	}

	std::string getPath(const std::string& pId)
	{
		auto path = _paths.find(pId);
		return (path != _paths.end() ? path->second : "");
	}

	bool requireResource(const std::string& pId)
	{
		auto res = find(pId);
		if(res)
		{
			++res->second;
			return true;
		}

		auto path = _paths.find(pId);
		if (path == _paths.end())
			return false;

		T* resource = load(path->second);
		if (!resource)
			return false;

		_resources.emplace(pid, std::make_pair(resource, 1));
		return true;
	}

	bool releaseResource(const std::string& pId)
	{
		auto res = find(pId);
		if (!res)
			return false;
		--res->second;
		if (!res->second)
			unload(pId);
		return true;
	}

	void purgeResource()
	{
		while(_resources.begin() != _resources.end())
		{
			delete _resources.begin()->second.first;
			_resources.erase(_resources.begin());
		}
	}

	T* load(const std::string& pPath)
	{
		return static_cast<Derived*>(this)->load(pPath);
	}

	std::pair<T*, unsigned int>* find(const std::string& pId)
	{
		auto itr = _resources.find(pId);

		return (itr != _resources.end() ? &itr->second : nullptr);
	}

	bool unload(const std::string& pId)
	{
		auto itr = _resources.find(pId);

		if (itr == _resources.end())
			return false;

		delete itr->second.first;
		_resources.erase(itr);

		return true;
	}

	void loadPaths(const std::string& pPathFile)
	{
		std::ifstream paths;
		paths.open(Utils::getWorkingDirectory() + pPathFile);
		if (paths.is_open())
		{
			std::string line;
			while(std::getline(paths, line))
			{
				std::stringstream keystream(line);
				std::string pathName;
				std::string path;
				keystream >> pathName;
				keystream >> path;
				_paths.emplace(pathName, path);
			}
			paths.close();
			return;
		}
		std::cerr << "FAILED TO LOAD PATH FILE: " << pPathFile << std::endl;
	}

private:
	std::unordered_map< std::string, std::pair<T*, unsigned int >> _resources;
	std::unordered_map<std::string, std::string> _paths;
};
