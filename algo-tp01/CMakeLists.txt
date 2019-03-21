cmake_minimum_required (VERSION 3.11)
project (Algo_01)

include(FetchContent)


 FetchContent_Declare(
   GoogleBenchmark
   URL https://github.com/google/benchmark/archive/v1.4.1.tar.gz
   )

# FetchContent_Declare(
#   CLI11
#   URL https://github.com/CLIUtils/CLI11/archive/v1.7.1.tar.gz
#   )

# FetchContent_Declare(
#   spdlog
#   URL https://github.com/gabime/spdlog/archive/v1.3.1.tar.gz
#   )


if (NOT GoogleBenchmark_POPULATED)
  FetchContent_Populate(GoogleBenchmark)
  set(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE BOOL "From Gtest")
  set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "From Gtest")
  add_subdirectory(${googlebenchmark_SOURCE_DIR} ${googlebenchmark_BINARY_DIR})
endif()

# if (NOT spdlog_POPULATED)
#   FetchContent_Populate(spdlog)
#   add_subdirectory(${spdlog_SOURCE_DIR} ${spdlog_BINARY_DIR})
# endif()

# if (NOT CLI11_POPULATED)
#   FetchContent_Populate(CLI11)
#   add_subdirectory(${cli11_SOURCE_DIR} ${cli11_BINARY_DIR})
# endif()


find_package(PNG REQUIRED)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-W -Wall")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3 -march=native -s")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-W -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -march=native -s")



include_directories(lib/include)


add_library(common src/image.c src/image.h src/closing.c src/closing.h)
target_link_libraries(common PRIVATE PNG::PNG)

add_executable(process src/main.c)
target_link_libraries(process common)

add_executable(bench src/bench.cpp)
target_link_libraries(bench PRIVATE common benchmark)
target_compile_definitions(bench PRIVATE IMAGE_PATH=${CMAKE_SOURCE_DIR}/input.png)

