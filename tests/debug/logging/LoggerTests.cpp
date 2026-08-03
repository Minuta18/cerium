#include <gtest/gtest.h>

#include "../../../src/cerium/debug/logging/Logging.hpp"
#include "TestMiddleware.hpp"

TEST(Logger, IgnoresDebugMessages) {
    auto middleware = std::make_shared<TestMiddleware>();

    LoggerConfig config;
    config.middlewares.push_back(middleware);

    Logging::setDefaultConfig(config);

    auto logger = Logging::createLogger("test.logger");

    logger.info("Hello");
    logger.debug("Test");

    EXPECT_EQ(middleware->calledCount, 1);
    EXPECT_EQ(middleware->lastLog.message, "Hello");
}

TEST(Logger, FormattedMessage) {
    auto middleware = std::make_shared<TestMiddleware>();

    LoggerConfig config;
    config.middlewares.push_back(middleware);

    Logging::setDefaultConfig(config);

    auto logger = Logging::createLogger("test.logger");

    logger.info("test {}", 57);

    EXPECT_EQ(middleware->calledCount, 1);
    EXPECT_EQ(middleware->lastLog.message, "test 57");
}

TEST(Logger, LoggerName) {
    auto middleware = std::make_shared<TestMiddleware>();

    LoggerConfig config;
    config.middlewares.push_back(middleware);

    Logging::setDefaultConfig(config);

    auto logger = Logging::createLogger("test.logger");

    logger.warn("Hello");

    EXPECT_EQ(middleware->lastLog.name, "test.logger");
}
