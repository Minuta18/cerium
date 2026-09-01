#include "virtual_filesystem.hpp"

#include <stdexcept>
#include "filesystem.hpp"

Platform VirtualFilesystem::platformDetection() {
#ifdef _WIN32
	return Platform::Windows;
#elif __APPLE__
	return Platform::MacOS;
#elif __linux__
	return Platform::Linux;
#else
	throw std::runtime_error("Unsupported platform");
#endif
}

VirtualFilesystem::VirtualFilesystem()
{
	platform = platformDetection();
	if (platform == Platform::Windows) {
		fs = std::make_unique<WindowsFilesystem>();
	}
	else if (platform == Platform::MacOS) {
		fs = std::make_unique<MacOSFilesystem>();
	}
	else if (platform == Platform::Linux) {
		fs = std::make_unique<LinuxFilesystem>();
	}
	else {
		throw std::runtime_error("Unsupported platform");
	}
}

void VirtualFilesystem::registerResolver(std::string name, std::unique_ptr<PathResolver> newResolver) {
	resolvers[name] = std::move(newResolver);
}

PathResolver& VirtualFilesystem::getResolver(const std::string& name) {
	return *resolvers.at(name);
}

std::string VirtualFilesystem::readFile(const VirtualPath& path, std::optional<int> readLength) {
	if (!fs) throw runtime_error("Filesystem not initialized");
	return fs->readFile(path, readLength);
}

void VirtualFilesystem::writeFile(const VirtualPath& path, const std::string& data) {
	if (!fs) throw runtime_error("Filesystem not initialized");
	fs->writeFile(path, data);
}
