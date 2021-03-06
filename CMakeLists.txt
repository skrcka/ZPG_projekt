cmake_minimum_required(VERSION 3.8)
project(krc0071_zpg)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCES
    src/main.cpp
	src/Utils/utils.cpp
	src/Engine.cpp
	src/Window.cpp
	src/Factory.cpp
	src/Scene.cpp
	src/Models/Model.cpp
	src/Shaders/Shader.cpp
	src/Camera.cpp
	src/Objects/Object.cpp
	src/Transforms/Transform.cpp
	src/AssetManager.cpp
	src/Textures/Texture.cpp
	src/Objects/Skybox.cpp
	src/Objects/Enemy.cpp
	src/Lights/Light.cpp
	src/Lights/PointLight.cpp
	src/Lights/DirectionalLight.cpp
	src/Lights/SpotLight.cpp
	src/Lights/Flashlight.cpp
	src/Material.cpp
)

include_directories(
	"${CMAKE_SOURCE_DIR}/src"
	"${CMAKE_SOURCE_DIR}/include"
)

add_compile_options(-Wall -Wextra -pedantic)

add_executable(${PROJECT_NAME} ${SOURCES})

find_package(OpenGL REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
find_package(glm REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
find_package(DevIL REQUIRED)
find_package(assimp REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} )

target_link_libraries( ${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${GLFW_LIBRARIES} ${GLM_LIBRARIES} ${GLEW_LIBRARIES} ${IL_LIBRARIES} ${ASSIMP_LIBRARIES} )
