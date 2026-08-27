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

class UnixFilesystem : public Filesystem {
	virtual std::string resolve(std::vector<std::string> path) override = 0;
	VirtualPath parsePath(const std::string& path);

	void writeFile(const VirtualPath& path);
	std::string readFile(const VirtualPath& path, std::optional<int> readLength = std::nullopt);
};

class LinuxFilesystem : public UnixFilesystem {
public:
	std::string resolve(std::vector<std::string> path) override;
	VirtualPath parsePath(const std::string& path) override;

};

class WindowsFilesystem : public Filesystem {
public:
	std::string resolve(std::vector<std::string> path) override;
	VirtualPath parsePath(const std::string& path) override;

	void writeFile(const VirtualPath& path);
	std::string readFile(const VirtualPath& path, std::optional<int> readLength = std::nullopt);
};

class MacOSFilesystem : public UnixFilesystem {
public:
	std::string resolve(std::vector<std::string> path) override;
	VirtualPath parsePath(const std::string& path) override;

};

#endif // CERIUM_PLATFORM_FILESYSTEM_FILESYSTEM_HPP_
