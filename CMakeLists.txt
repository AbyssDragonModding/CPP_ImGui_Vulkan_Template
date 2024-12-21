# ImGui with GLFW/Vulkan example

cmake_minimum_required(VERSION 3.15)
include(FetchContent)
project("ImGui_Vulkan")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(PROJ_DEPS_DIR ${CMAKE_SOURCE_DIR}/deps)

# Get the path to the Vulkan SDK
if(WIN32)
    if(NOT DEFINED ENV{VULKAN_SDK})
        message(FATAL_ERROR "VULKAN_SDK environment variable is not set, or VulkanS SDK is not installed.")
    else()
        set(VULKAN_SDK $ENV{VULKAN_SDK})
        message(STATUS "VULKAN_SDK ENV: $ENV{VULKAN_SDK}")
    endif()
elseif(UNIX)
    set(VULKAN_SDK /usr/)
endif()
##############
# Vulkan SDK #
##############
file(GLOB VULKAN_SDK_HEADERS
${VULKAN_SDK}/Include/vulkan/*.h
${VULKAN_SDK}/Include/vulkan/*.hpp
${VULKAN_SDK}/Include/vk_video/*.h
${VULKAN_SDK}/Include/vk_video/*.hpp
)

add_library(vulkan INTERFACE)
target_include_directories(vulkan INTERFACE
${VULKAN_SDK}/Include/vulkan
${VULKAN_SDK}/Include/vk_video
)

##############################
# Download the IMGUI Library #
##############################
set(IMGUI_LIB_DIR ${PROJ_DEPS_DIR}/imgui)
if(NOT EXISTS ${IMGUI_LIB_DIR})
    message(STATUS "Downloading IMGUI Library")
    FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui.git
        GIT_TAG docking
        SOURCE_DIR ${IMGUI_LIB_DIR}
    )
    FetchContent_MakeAvailable(imgui)
endif()

# Build the imgui library
message(STATUS "Building IMGUI Library")
# Collect all the .cpp files in the imgui directory
file(GLOB IMGUI_SOURCES 
${IMGUI_LIB_DIR}/*.cpp
${IMGUI_LIB_DIR}/backends/imgui_impl_glfw.cpp
${IMGUI_LIB_DIR}/backends/imgui_impl_vulkan.cpp
) 
add_library(imgui STATIC ${IMGUI_SOURCES})

target_include_directories(imgui PUBLIC 
${IMGUI_LIB_DIR}/
${IMGUI_LIB_DIR}/backends
)

#############################
# Download the GLFW Library #
#############################
set(GLFW_LIB_DIR${PROJ_DEPS_DIR}/glfw)
if(NOT EXISTS ${GLFW_LIB_DIR})
    message(STATUS "Downloading GLFW Library")
    FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG master
        SOURCE_DIR ${GLFW_LIB_DIR}
    )
    FetchContent_MakeAvailable(glfw)
endif()

# Build the GLFW library
message(STATUS "Building GLFW Library")
add_subdirectory(${GLFW_LIB_DIR})

#############################################
# add the executable and link the libraries #
#############################################
file(GLOB PROJ_SRC_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB PROJ_HEADER_FILES ${CMAKE_SOURCE_DIR}/include/*.h)
add_executable(${PROJECT_NAME} ${PROJ_SRC_FILES} ${PROJ_HEADER_FILES})
target_link_libraries(${PROJECT_NAME}
PRIVATE
imgui
vulkan
glfw
)
