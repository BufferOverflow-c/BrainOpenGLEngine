cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 23)

# Production build option
option(PRODUCTION_BUILD "Make this a production build" OFF)

# MSVC specific settings
if(MSVC)
    add_compile_options(/arch:AVX2)
endif()

project(BrainCards)

# Disable unnecessary GLFW components
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

# Add third-party libraries
add_subdirectory(thirdparty/glfw-3.3.2)
add_subdirectory(thirdparty/stb_image)
add_subdirectory(thirdparty/stb_truetype)
add_subdirectory(thirdparty/glm)
add_subdirectory(thirdparty/imgui-docking)
#add_subdirectory(thirdparty/gl2d)

# Add GLAD manually as static library
add_library(glad STATIC
    thirdparty/glad/src/glad.c  # Ensure this path is correct
)

# Include directories for GLAD
target_include_directories(glad PUBLIC
    thirdparty/glad/include   # Ensure this path is correct
)

# Collect all source files
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# Create executable
add_executable("${CMAKE_PROJECT_NAME}" ${MY_SOURCES})

# Set C++ standard
set_property(TARGET "${CMAKE_PROJECT_NAME}" PROPERTY CXX_STANDARD 23)

# Define preprocessor macros
target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC GLFW_INCLUDE_NONE=1)

if(PRODUCTION_BUILD)
    target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="./resources/")
    target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC PRODUCTION_BUILD=1)
else()
    target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/")
    target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC PRODUCTION_BUILD=0)
endif()

# Include directories for other libraries
target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")
target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glfw-3.3.2/include")
target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/imgui-docking")
target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/gl2d/include")
target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/stb_image/include/stb_image")

# Link libraries, including GLAD
target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE
    glm
    glfw
    glad
    stb_image
    stb_truetype
    imgui
)

# macOS specific frameworks
if(APPLE)
    target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE
        "-framework IOKit"
        "-framework Cocoa"
        "-framework OpenGL"
    )
endif()

# MSVC specific options
if(MSVC)
    target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC _CRT_SECURE_NO_WARNINGS)
endif()

# Shader Compilation
find_program(GLSL_VALIDATOR glslangValidator HINTS
  ${Vulkan_GLSLANG_VALIDATOR_EXECUTABLE}
  /usr/bin
  /usr/local/bin
  ${VULKAN_SDK_PATH}/Bin
  ${VULKAN_SDK_PATH}/Bin32
  $ENV{VULKAN_SDK}/Bin/
  $ENV{VULKAN_SDK}/Bin32/
)

file(GLOB_RECURSE GLSL_SOURCE_FILES
  "${PROJECT_SOURCE_DIR}/shaders/*.frag"
  "${PROJECT_SOURCE_DIR}/shaders/*.vert"
)

foreach(GLSL ${GLSL_SOURCE_FILES})
    get_filename_component(FILE_NAME ${GLSL} NAME)
    list(APPEND GLSL_BINARY_FILES ${GLSL})
endforeach()

add_custom_target(Shaders DEPENDS ${GLSL_BINARY_FILES})

#foreach(GLSL ${GLSL_SOURCE_FILES})
#  get_filename_component(FILE_NAME ${GLSL} NAME)
#  set(SPIRV "${PROJECT_SOURCE_DIR}/shaders/${FILE_NAME}.spv")
#  add_custom_command(
#    OUTPUT ${SPIRV}
#    COMMAND ${GLSL_VALIDATOR} -V ${GLSL} -o ${SPIRV}
#    DEPENDS ${GLSL})
#  list(APPEND SPIRV_BINARY_FILES ${SPIRV})
#endforeach()

#add_custom_target(Shaders DEPENDS ${SPIRV_BINARY_FILES})
