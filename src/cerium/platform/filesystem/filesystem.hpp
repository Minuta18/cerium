 #ifndef CERIUM_PLATFORM_FILESYSTEM_FILESYSTEM_HPP_
#define CERIUM_PLATFORM_FILESYSTEM_FILESYSTEM_HPP_

#include <string>
#include <vector>
#include <optional>

#include "virtual_path.hpp"

class Filesystem {
	virtual std::string resolve(std::vector<std::string> path) = 0;
	virtual VirtualPath parsePath(const std::string& path) = 0;

	// Basic file operations exposed by all concrete filesystem implementations
	virtual void writeFile(const VirtualPath& path, const std::string& data) = 0;
	virtual std::string readFile(const VirtualPath& path, std::optional<int> readLength = std::nullopt) = 0;
};

class UnixFilesystem : public Filesystem {
	virtual std::string resolve(std::vector<std::string> path) override = 0;
	VirtualPath parsePath(const std::string& path) override;

	void writeFile(const VirtualPath& path, const std::string& data) override;
	std::string readFile(const VirtualPath& path, std::optional<int> readLength = std::nullopt) override;
};

class LinuxFilesystem : public UnixFilesystem {
public:
	std::string resolve(std::vector<std::string> path) override;
	VirtualPath parsePath(const std::string& path) override;

	void writeFile(const VirtualPath& path, const std::string& data) override;
	std::string readFile(const VirtualPath& path, std::optional<int> readLength = std::nullopt) override;
};

class WindowsFilesystem : public Filesystem {
public:
	std::string resolve(std::vector<std::string> path) override;
	VirtualPath parsePath(const std::string& path) override;

	void writeFile(const VirtualPath& path, const std::string& data) override;
	std::string readFile(const VirtualPath& path, std::optional<int> readLength = std::nullopt) override;

	bool bannedSymbolDetect(std::vector<std::string> path);
};

class MacOSFilesystem : public UnixFilesystem {
public:
	std::string resolve(std::vector<std::string> path) override;
	VirtualPath parsePath(const std::string& path) override;

	void writeFile(const VirtualPath& path, const std::string& data) override;
	std::string readFile(const VirtualPath& path, std::optional<int> readLength = std::nullopt) override;
};

#endif // CERIUM_PLATFORM_FILESYSTEM_FILESYSTEM_HPP_
