#ifndef CERIUM_PLATFORM_FILESYSTEM_PATH_HPP_
#define CERIUM_PLATFORM_FILESYSTEM_PATH_HPP_

#include <string>

class File {
public:
	std::string read(uint32_t size);
	std::string readAll();

	void write(const std::string& data);

	void close();
};

#endif // CERIUM_PLATFORM_FILESYSTEM_PATH_HPP_