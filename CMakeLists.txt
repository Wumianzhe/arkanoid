project(arkanoid)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")

include_directories("${PROJECT_SOURCE_DIR}/inc")

add_executable(main main.cpp game.cpp racket.cpp ball.cpp entity.cpp functions.cpp brick.cpp field.cpp bonus.cpp)
# add_subdirectory(src)
target_link_libraries(main sfml-window sfml-graphics sfml-system)
