#include "virtual_path.hpp"

VirtualPath::VirtualPath(std::string path_) : path(std::move(path_)) {}

std::string VirtualPath::resolve() {
    PathResolver& pathResolver = resolver->getResolver(path.front());
}

void VirtualPath::append(const VirtualPath& subpath) {
	for (size_t i = 0; i < subpath.size(); ++i) {
		path.push_back(subpath[i]);
	}
}

VirtualPath VirtualPath::operator/(const VirtualPath& oldPath, const VirtualPath& newPath) {
    resultPath = oldPath;
    for (size_t i = 0; i < newPath.size(); ++i) {
        resultPath.push_back(newPath[i]);
    }
    return resultPath;
}

void VirtualPath::operator/=(const VirtualPath& subpath) {
	for (size_t i = 0; i < subpath.size(); ++i) {
		path.push_back(subpath[i]);
	}
}

VirtualPath VirtualPath::operator+(const VirtualPath& oldPath, const VirtualPath& newPath) {
	resultPath = oldPath;
	for (size_t i = 0; i < newPath.size(); ++i) {
		resultPath.push_back(newPath[i]);
	}
	return resultPath;
}

VirtualPath VirtualPath::operator+=(const VirtualPath& subpath) {
	for (size_t i = 0; i < subpath.size(); ++i) {
		path.push_back(subpath[i]);
	}
}

std::string VirtualPath::operator[](const size_t index) {
	return path[index];
}

bool VirtualPath::operator==(const VirtualPath& other) {
	if (path.size() != other.path.size()) {
		return false;
	}
	for (size_t i = 0; i < path.size(); ++i) {
		if (path[i] != other.path[i]) {
			return false;
		}
	}
	return true;
}