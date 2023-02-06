cmake_minimum_required(VERSION 3.21)
project(proi_zad2_wojciechsekulaczw16)

set(CMAKE_CXX_STANDARD 14)

include_directories(ScalesApp)
include_directories(ScalesLib)
include_directories(ScalesUnitTest)

add_library(ScalesLib ScalesLib/Scale.cpp ScalesLib/Scale.h)

add_executable(proi_zad2_wojciechsekulaczw16 ScalesApp/ScalesApp.cpp)
target_link_libraries(proi_zad2_wojciechsekulaczw16 ScalesLib)

#testy
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
if(WIN32)
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif(WIN32)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(ScalesUnitTest ScalesUnitTest/ScalesUnitTest.cpp)
target_link_libraries(ScalesUnitTest PUBLIC gtest_main ScalesLib)

include(GoogleTest)
gtest_discover_tests(ScalesUnitTest)
