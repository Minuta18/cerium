#ifndef CERIUM_PLATFORM_FILESYSTEM_PATH_HPP_
#define CERIUM_PLATFORM_FILESYSTEM_PATH_HPP_

#include <unordered_map>
#include <string>
#include <memory>
#include <optional>

#include "path_resolver.hpp"
#include "virtual_path.hpp"
#include "filesystem.hpp"

enum class Platform {
	Linux,
	Windows,
	MacOS
};

class VirtualFilesystem {
private:
	std::unordered_map<std::string, std::unique_ptr<PathResolver>> resolvers;

	Platform platform;
	std::unique_ptr<Filesystem> fs;

	std::vector<std::string> coreBasePath;
	std::vector<std::string> projectBasePath;

	Platform platformDetection();
public:
	VirtualFilesystem();

	void  registerResolver(std::string name, std::unique_ptr<PathResolver> newResolver);
	PathResolver& getResolver(const std::string& name);
	std::string readFile(const VirtualPath& path, std::optional<int> readLength = std::nullopt);
	void writeFile(const VirtualPath& path, const std::string& data);
};

#endif // CERIUM_PLATFORM_FILESYSTEM_PATH_HPP_