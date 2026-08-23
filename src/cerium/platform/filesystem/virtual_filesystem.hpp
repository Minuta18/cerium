#ifndef CERIUM_PLATFORM_FILESYSTEM_PATH_HPP_
#define CERIUM_PLATFORM_FILESYSTEM_PATH_HPP_

#include <unordered_map>
#include <string>
#include <memory>

#include "path_resolver.hpp"
#include "virtual_path.hpp"

enum class Platform {
	Linux,
	Windows,
	MacOS
};

class VirtualFileSystem {
private:
	std::unordered_map<std::string, std::unique_ptr<PathResolver>> resolvers;

	Platform platformDetection();
public:
	VirtualFileSystem();

	void  registerResolver(std::unique_ptr<PathResolver> newResolver);
	PathResolver& getResolver(const std::string& name);

	void readFile(const VirtualPath& path);
	void writeFile(const VirtualPath& path, const std::string& data);
};

#endif // CERIUM_PLATFORM_FILESYSTEM_PATH_HPP_