#ifndef CERIUM_PROJECT_APPLICATION_HPP_
#define CERIUM_PROJECT_APPLICATION_HPP_

#include "project.hpp"
#include <memory>

class Application {
private:
    std::unique_ptr<Project> project;
public:
    Application();
    void run();
};

#endif //CERIUM_PROJECT_APPLICATION_HPP_
