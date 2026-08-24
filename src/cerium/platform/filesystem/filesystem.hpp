 #ifndef CERIUM_PLATFORM_FILESYSTEM_FILESYSTEM_HPP_
#define CERIUM_PLATFORM_FILESYSTEM_FILESYSTEM_HPP_

#include <string>
#include <vector>
#include <optional>

#include "virtual_path.hpp"

class Filesystem {
	virtual std::string resolve(std::vector<std::string> path) = 0;
	virtual VirtualPath parsePath(const std::string& path) = 0;
};

class LinuxFilesystem : public Filesystem {
public:
	std::string resolve(std::vector<std::string> path) override;
	VirtualPath parsePath(const std::string& path) override;

	void writeFile(const VirtualPath& path);
	std::string readFile(const VirtualPath& path, std::optional<int> readLength = std::nullopt);
};

class WindowsFilesystem : public Filesystem {
public:
	std::string resolve(std::vector<std::string> path) override;
	VirtualPath parsePath(const std::string& path) override;

	void writeFile(const VirtualPath& path);
	std::string readFile(const VirtualPath& path, std::optional<int> readLength = std::nullopt);
};

class MacOSFilesystem : public Filesystem {
public:
	std::string resolve(std::vector<std::string> path) override;
	VirtualPath parsePath(const std::string& path) override;

	void writeFile(const VirtualPath& path);
	std::string readFile(const VirtualPath& path, std::optional<int> readLength = std::nullopt);
};

#endif // CERIUM_PLATFORM_FILESYSTEM_FILESYSTEM_HPP_
