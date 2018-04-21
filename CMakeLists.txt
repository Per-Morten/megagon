project(megagon)
cmake_minimum_required (VERSION 3.5 FATAL_ERROR)

# Set global variables
set(CMAKE_BUILD_TYPE Debug)

# Aliases
set(SRCDIR ${CMAKE_SOURCE_DIR})
set(BINDIR ${CMAKE_BINARY_DIR})




# Find system packages
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
#find_package(GLFW REQUIRED)
#find_package(GLM REQUIRED)

# Configure main executeable
add_executable(megagon "${SRCDIR}/src/main.cpp")

set_target_properties(
    megagon
    PROPERTIES
#    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    RUNTIME_OUTPUT_DIRECTORY "${BINDIR}"
    LIBRARY_OUTPUT_DIRECTORY "${BINDIR}/bin"
)

target_sources(
    megagon
    PRIVATE "${SRCDIR}/src/parser.cpp"
    PRIVATE "${SRCDIR}/src/logger.cpp"  
)


################################
# Apple, linux, others...
################################
target_compile_options(
    megagon
    PRIVATE "-Wall"
    PRIVATE "-Wextra"
    PRIVATE "-std=c++17"
    PRIVATE "-lGLFW"
)

target_include_directories(
    megagon
    PRIVATE ${SRCDIR}/src
)

target_link_libraries(
    megagon
    PRIVATE ${OPENGL_LIBRARIES}
    PRIVATE ${GLEW_LIBRARY}
    PRIVATE glfw
)



message("CMAKE_BINARY_DIR: " ${BINDIR})
message("OPENGL_LIBRARIES"   ${OPENGL_LIBRARIES})
message("GLEW_LIBRARY"       ${GLEW_LIBRARY})
