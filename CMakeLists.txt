cmake_minimum_required(VERSION 3.0)
project(shabui)

set(PROJECT_NAME_LIB ${PROJECT_NAME}-lib)

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/source)
bison_target(ShabuiParser
    ${PROJECT_SOURCE_DIR}/source/shabui.y
    ${PROJECT_BINARY_DIR}/source/shabuiparser.c
)

flex_target(ShabuiScanner
    ${PROJECT_SOURCE_DIR}/source/shabui.l
    ${PROJECT_BINARY_DIR}/source/shabuiscanner.c
)

add_flex_bison_dependency(ShabuiScanner ShabuiParser)

add_library(${PROJECT_NAME_LIB}
    ${BISON_ShabuiParser_OUTPUTS}
    ${FLEX_ShabuiScanner_OUTPUTS}
)

target_include_directories(${PROJECT_NAME_LIB}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
    PUBLIC ${PROJECT_BINARY_DIR}/source
)

add_executable(${PROJECT_NAME}
    ${PROJECT_SOURCE_DIR}/source/cli/main.c
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE ${PROJECT_NAME_LIB}
)
