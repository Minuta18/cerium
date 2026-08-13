#include "virtual_path.hpp"

VirtualPath::VirtualPath(std::string path_) : path(std::move(path_)) {}

std::string VirtualPath::resolve() {
    PathResolver& pathResolver = resolver->getResolver(path.front());
}

void VirtualPath::operator/(const VirtualPath& subpath) {
    path.push_back(subpath);
}
};