cmake_minimum_required(VERSION 3.20)
project(PP5 C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_EXE_LINKER_FLAGS -pthread)

include_directories(src)

add_executable(PP5
        src/main.c
        src/libraries.h
        src/structures/structures.c
        src/pictureOperations/picture_manipulation.c
        src/rle/rle.c
        src/helpers/helper.c
        )
add_executable(test_rle
        test/rle/test_rle.c
        src/rle/rle.c
        src/libraries.h
        src/structures/structures.c
        )

add_executable(test_picture_manipulation
        test/pictureOperations/test_picture_manipulation.c
        src/pictureOperations/picture_manipulation.c
        src/libraries.h
        src/structures/structures.c
        )

target_link_libraries(PP5 m)
target_link_libraries(test_rle m)