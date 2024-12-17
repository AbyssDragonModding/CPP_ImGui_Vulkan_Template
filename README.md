# C++ ImGui Vulkan Template
ImGui template project to use with C++ GLFW and Vulkan.

You probably will have to modify the CMakeLists.txt file if you are on linux, I have not tested it on linux


## Requirements
- CMake 3.15+
- Vulkan SDK

## Installation
NOTE: Make sure the vulkan SDK is installed first, if your on windows it should automatically set the path according to what vulkan set in the environment variable
1. Clone the repository
2. Change the project name in the CMakeLists.txt
3. open directory in terminal
4. mkdir build
5. cd build
6. cmake ..
- It will then download the ImGui (Docking branch) and GLFW Repository, build the lib files and setup the project

## Using the template
- Once you open up the project in Visual Studio set the "ProjectName" project as the default project.
- Open Up the MainWindow.h and MainWindow.cpp class files
- All your menu code goes in theose two files
