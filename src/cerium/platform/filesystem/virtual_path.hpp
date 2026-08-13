#ifndef CERIUM_PLATFORM_FILESYSTEM_PATH_HPP_
#define CERIUM_PLATFORM_FILESYSTEM_PATH_HPP_

#include <vector>
#include <string>
#include <filesystem>

#include "filesystem.hpp"
#include "path_resolver.hpp"

class VirtualPath {
private:
	std::vector<std::string> path;
	
	static Filesystem* resolver;
public:
	VirtualPath(std::string path);
	VirtualPath(std::string path, std::string from);
	VirtualPath(std::filesystem::path path);

	std::string resolve();
	std::string getVirtual();

	void append(const VirtualPath& subpath);

	VirtualPath operator/(const VirtualPath& subpath);
	void operator/=(const VirtualPath& subpath);
	VirtualPath operator+(const VirtualPath& subpath);
	void operator+=(const VirtualPath& subpath);

	std::string operator[](const size_t index);

	bool operator==(const VirtualPath& other);
};

#endif // CERIUM_PLATFORM_FILESYSTEM_PATH_HPP_