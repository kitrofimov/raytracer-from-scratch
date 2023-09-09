target_include_directories(${EXECUTABLE_NAME} PUBLIC lib/include)

add_library(sdl2 SHARED IMPORTED)
set_property(TARGET sdl2 PROPERTY IMPORTED_LOCATION SDL2.dll)

# find .dll.a
find_library(
  SDL2_LIB
  SDL2.dll
  HINTS ${CMAKE_CURRENT_SOURCE_DIR}
  REQUIRED
)

target_link_libraries(
  ${EXECUTABLE_NAME} PRIVATE
  ${SDL2_LIB}
)

target_include_directories(${EXECUTABLE_NAME} PUBLIC include)
file(COPY SDL2.dll DESTINATION ${CMAKE_BINARY_DIR}/bin/)  # copy dynamic library to bin
