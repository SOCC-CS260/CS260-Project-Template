#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_COLORS_NONE
#include "HelloWorld.h"
#include "doctest.h"

TEST_CASE("HelloWorld Test") {
    HelloWorld hello;

    CHECK(hello.sayHello() == "Hello, World!");
}