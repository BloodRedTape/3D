cmake_minimum_required(VERSION 3.10)

project(3D)

set(CMAKE_CXX_STANDARD_REQUIRED 17)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(StraitXPackages/Base)
add_subdirectory(StraitXPackages/ImGui)
add_subdirectory(Thirdparty/tinygltf)

set(3D_SOURCES
    Sources/main.cpp
)

set(3D_INCLUDE
    Sources/
)

add_executable(3D ${3D_SOURCES})
target_link_libraries(3D StraitXBase StraitXImGui)
target_include_directories(3D
    PUBLIC ${3D_INCLUDE}
    PUBLIC Thirdparty/tinygltf
)