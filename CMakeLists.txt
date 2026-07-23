cmake_minimum_required(VERSION 3.15)
project(sokoban_engine)

# 1. Silences CMP0135 timestamp warning
if(POLICY CMP0135)
  cmake_policy(SET CMP0135 NEW)
endif()

# 2. Fixes the "Compatibility with CMake < 3.5 has been removed" error for raylib
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 3. Fetch and build raylib
include(FetchContent)
FetchContent_Declare(
    raylib
    URL "https://github.com/raysan5/raylib/archive/refs/tags/5.0.tar.gz"
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(BUILD_EXAMPLES OFF CACHE INTERNAL "")
FetchContent_MakeAvailable(raylib)

# 4. Your executable definition
add_executable(my_game src/main.cpp src/game.cpp)

# 5. Link raylib
target_link_libraries(my_game PRIVATE raylib)
