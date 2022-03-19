if(APPLE)
  cmake_minimum_required(VERSION 3.22)
else()
  cmake_minimum_required(VERSION 3.16)
endif()

project(Hum_Game)


if(APPLE)
  set(SDL2_INCLUDE_DIR /opt/homebrew/include/SDL2)
  set(SDL2_LIBRARY /opt/homebrew/lib/libSDL2.dylib)
  set(SDL2_IMAGE_LIBRARY /opt/homebrew/lib/libSDL2_image.dylib)
else()
  set(SDL2_INCLUDE_DIR /usr/include/SDL2)
  set(SDL2_LIBRARY /usr/lib/x86_64-linux-gnu/libSDL2-2.0.so)
  set(SDL2_IMAGE_LIBRARY /usr/lib/x86_64-linux-gnu/libSDL2_image-2.0.so)
endif()

set(HEADER_FILES 
  include/GameEngine.hpp
  include/Sprite.hpp
)

set(SOURCE_FILES 
  src/main.cpp 
  src/GameEngine.cpp
  src/Sprite.cpp
)

include_directories(${SDL2_INCLUDE_DIR})
add_executable(Hum_Game ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(Hum_Game ${SDL2_LIBRARY})
target_link_libraries(Hum_Game ${SDL2_IMAGE_LIBRARY})