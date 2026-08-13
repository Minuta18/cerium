#ifndef CERIUM_PLATFORM_FILESYSTEM_FILESYSTEM_HPP_
#define CERIUM_PLATFORM_FILESYSTEM_FILESYSTEM_HPP_

#include <string>
#include <vector>

class Filesystem {
	virtual std::string resolve(std::vector<std::string> path) = 0;
	virtual std::vector<std::string> parsePath(const std::string& path) = 0;
};

class LinuxFilesystem : public Filesystem {
public:
	std::string resolve(std::vector<std::string> path) override;
	std::vector<std::string> parsePath(const std::string& path) override;

	void writeFile(const VirtualPath& path);
	std::string readFile(const VirtualPath& path);
};

class WindowsFilesystem : public Filesystem {
public:
	std::string resolve(std::vector<std::string> path) override;
	std::vector<std::string> parsePath(const std::string& path) override;

	void writeFile(const VirtualPath& path);
	std::string readFile(const VirtualPath& path);
};

#endif // CERIUM_PLATFORM_FILESYSTEM_FILESYSTEM_HPP_
