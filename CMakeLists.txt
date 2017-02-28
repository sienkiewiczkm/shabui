cmake_minimum_required(VERSION 3.0)
project(shabui)

set(PROJECT_NAME_LIB ${PROJECT_NAME}-lib)

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/source)

bison_target(ShabuiParser
    ${PROJECT_SOURCE_DIR}/source/ShabuiParser.y
    ${PROJECT_BINARY_DIR}/source/ShabuiParser.cxx
)

flex_target(ShabuiScanner
    ${PROJECT_SOURCE_DIR}/source/ShabuiScanner.l
    ${PROJECT_BINARY_DIR}/source/ShabuiScanner.cxx
)

add_flex_bison_dependency(ShabuiScanner ShabuiParser)

add_library(${PROJECT_NAME_LIB}
    source/GLSLCodeBuilder.cpp
    source/GLSLLoader.cpp
    source/ParserOutput.cpp
    source/ShabuiAst.cpp
    source/StringUtils.cpp
    ${BISON_ShabuiParser_OUTPUTS}
    ${FLEX_ShabuiScanner_OUTPUTS}
)

target_compile_features(${PROJECT_NAME_LIB}
    PUBLIC cxx_auto_type
    PUBLIC cxx_rvalue_references
)

target_include_directories(${PROJECT_NAME_LIB}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
    PUBLIC ${PROJECT_BINARY_DIR}/source
)

add_executable(${PROJECT_NAME}
    ${PROJECT_SOURCE_DIR}/source/cli/Main.cpp
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE ${PROJECT_NAME_LIB}
)
