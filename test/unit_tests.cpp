#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "HelloWorld.h"
#include "doctest.h"

TEST_CASE("HelloWorld Test") {
    HelloWorld hello;

    CHECK(hello.sayHello() == "Hello, World!");
}