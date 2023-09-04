cmake_minimum_required(VERSION 3.18.4)
project(renderer)

set(
  SOURCES

  src/main.cpp

  # Main classes
  src/Window/Window.cpp
  src/Camera/Camera.cpp
  src/Scene/Scene.cpp

  # Object classes
  src/Sphere/Sphere.cpp

  # Light classes
  src/Light/LightSource.cpp
  src/Light/AmbientLight/AmbientLight.cpp
  src/Light/PointLight/PointLight.cpp
  src/Light/DirectionalLight/DirectionalLight.cpp

  # Utility classes/structs
  src/utils/color/color.cpp
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")  # force .exe to build/bin

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC lib/include)
target_include_directories(${PROJECT_NAME} PUBLIC src)

add_library(sdl2 SHARED IMPORTED)
set_property(TARGET sdl2 PROPERTY IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/lib/SDL2.dll")

# find .dll.a
find_library(
  SDL2_LIB
  SDL2.dll
  HINTS "${CMAKE_SOURCE_DIR}/lib/"
  REQUIRED
)

target_link_libraries(
  ${PROJECT_NAME} PRIVATE
  "${SDL2_LIB}"
)

file(COPY res/ DESTINATION bin/)  # copy resources to bin
file(COPY lib/SDL2.dll DESTINATION bin/)  # copy dynamic library to bin
