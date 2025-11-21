cmake_minimum_required(VERSION 3.0)
cmake_policy(VERSION 3.0)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

# Production build option
option(PRODUCTION_BUILD "Make this a production build" OFF)

# MSVC specific settings
if(MSVC)
    add_compile_options(/arch:AVX2)
endif()

project(Brain)

# Disable unnecessary GLFW components
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)


if (APPLE)
    add_library(raudio_c STATIC "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/raudio/src/raudio.c")
    target_include_directories(raudio_c PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/raudio/include")
    set_target_properties(raudio_c PROPERTIES LINKER_LANGUAGE C)
    target_compile_options(raudio_c PRIVATE -std=c11)
else()
    add_subdirectory(thirdparty/raudio)				#audio
endif()

# Add third-party libraries
add_subdirectory(thirdparty/glfw-3.3.2)			#window oppener
add_subdirectory(thirdparty/stb_image)			#loading immaged
add_subdirectory(thirdparty/stb_truetype)		#loading ttf files
#add_subdirectory(thirdparty/enet-1.3.17)		#networking
add_subdirectory(thirdparty/glm)				#math
add_subdirectory(thirdparty/imgui-docking)		#ui
add_subdirectory(thirdparty/safeSave)			#saving data, designed for gamedev. It also makes backups so the player won't loose saves.
add_subdirectory(thirdparty/profilerLib)		#profiling, just a simpe library for measuring elapsed time
add_subdirectory(thirdparty/gl2d)				#2D rendering library
add_subdirectory(thirdparty/glui)				#ui library, usefull for making game menus

# Add GLAD manually as static library
add_library(glad STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glad/src/glad.c  # Ensure this path is correct
)

# Include directories for GLAD
target_include_directories(glad PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glad/include   # Ensure this path is correct
)

# Collect all source files
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "OpenGL/src/*/*.cpp")

# Create executable
add_executable("${CMAKE_PROJECT_NAME}" ${MY_SOURCES})

# Set C++ standard
set_property(TARGET "${CMAKE_PROJECT_NAME}" PROPERTY CXX_STANDARD 23)

# Define preprocessor macros
target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC GLFW_INCLUDE_NONE=1)

if(PRODUCTION_BUILD)
    target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="OpenGL/Resources/")
    target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC PRODUCTION_BUILD=1)
else()
    target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="OpenGL/Resources/")
    target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC PRODUCTION_BUILD=0)
endif()

# Include directories for other libraries
target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/OpenGL/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/OpenGL/include/Core"
    "${CMAKE_CURRENT_SOURCE_DIR}/OpenGL/include/Renderer"
    "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/gl2d/include/gl2d"
    "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glad/include/glad"
    "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glad/include/KHR"
    "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glfw-3.3.2/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glm/glm"
    "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glui/include/glui"
    "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/imgui-docking/imgui"
    "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/profilerLib/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/raudio/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/raudio/include/external"
    "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/safeSave/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/stb_image/include/stb_image"
    "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/stb_truetype/include/stb_truetype"
)

if (CMAKE_SYSTEM_PROCESSOR MATCHES "arm64|aarch64")
    add_compile_definitions(GL2D_USE_SIMD=0) # Disables SIMD for ARM
    if(APPLE)
        target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE glm glfw
            glad stb_image stb_truetype gl2d raudio_c imgui safeSave profilerLib glui
            "-framework IOKit"
            "-framework Cocoa"
            "-framework OpenGL"
        )
        target_compile_definitions("${CMAKE_PROJECT_NAME}" PRIVATE
            GL2D_USE_SIMD=0
            GL2D_USE_LEGACY=0
            GL2D_FORCE_CORE_PROFILE=1
            GL2D_USE_PACKED_VERTICES=0
        )
    else()
        target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE glm glfw
            glad stb_image stb_truetype gl2d raudio imgui safeSave profilerLib glui
        )
        target_compile_definitions("${CMAKE_PROJECT_NAME}" PRIVATE
            GL2D_USE_SIMD=0
        )
    endif()
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
    "${CMAKE_CURRENT_SOURCE_DIR}/OpenGL/src/Renderer/Shaders/*.frag"
    "${CMAKE_CURRENT_SOURCE_DIR}/OpenGL/src/Renderer/Shaders/*.vert"
)

foreach(GLSL ${GLSL_SOURCE_FILES})
    get_filename_component(FILE_NAME ${GLSL} NAME)
    list(APPEND GLSL_BINARY_FILES ${GLSL})
endforeach()

add_custom_target(Shaders DEPENDS ${GLSL_BINARY_FILES})
