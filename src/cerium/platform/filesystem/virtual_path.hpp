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
	VirtualPath(std::filesystem::path path);

	std::string resolve();

	void operator/(const VirtualPath& subpath);
};

#endif // CERIUM_PLATFORM_FILESYSTEM_PATH_HPP_