#ifndef CERIUM_PROJECT_APPLICATION_HPP_
#define CERIUM_PROJECT_APPLICATION_HPP_

#include "project.hpp"

class Application {
private:
    Project project;
public:
    Application(Project proj);
    void run();
};

#endif //CERIUM_PROJECT_APPLICATION_HPP_