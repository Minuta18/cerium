#ifndef TESTS_TESTMIDDLEWARE_HPP_
#define TESTS_TESTMIDDLEWARE_HPP_

#include "../../../src/cerium/debug/logging/LoggerMiddleware.hpp"

class TestMiddleware : public LoggerMiddleware {
public:
    int calledCount = 0;
    Log lastLog;

    void log(const Log& log) override {
        calledCount++;
        lastLog = log;
    }
};

#endif // TESTS_TESTMIDDLEWARE_HPP_
