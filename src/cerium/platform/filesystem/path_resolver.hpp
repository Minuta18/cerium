#ifndef CERIUM_PLATFORM_FILESYSTEM_PATHRESOLVER_HPP_
#define CERIUM_PLATFORM_FILESYSTEM_PATHRESOLVER_HPP_

#include <vector>
#include <string>
#include <filesystem>

class PathResolver {
public:
	virtual std::vector<std::string> resolvePath(const std::vector<std::string>& path) = 0;
	virtual std::vector<std::string> resolvePath(const std::filesystem::path& path) = 0;
};

class SimplePathResolver : public PathResolver {
public:
	std::vector<std::string> resolvePath(const std::vector<std::string>& path) override;
};

#endif // CERIUM_PLATFORM_FILESYSTEM_PATHRESOLVER_HPP_