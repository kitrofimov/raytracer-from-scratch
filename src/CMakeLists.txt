set(
  SOURCES

  main.cpp

  # Main
  Window/Window.cpp
  Camera/Camera.cpp
  Scene/Scene.cpp

  # Objects
  Sphere/Sphere.cpp

  # Light sources
  Light/LightSource.cpp
  Light/AmbientLight/AmbientLight.cpp
  Light/PointLight/PointLight.cpp
  Light/DirectionalLight/DirectionalLight.cpp

  # Utility classes/functions
  utils/color/color.cpp
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")

add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})
if(MSVC)
  target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE /W4 /WX)
else()
  target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE
                         -Wall -Wextra -Wpedantic -Wno-unused)
endif()
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
