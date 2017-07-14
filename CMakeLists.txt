cmake_minimum_required(VERSION 3.0)
project(shabui)

set(PROJECT_NAME_CLI ${PROJECT_NAME}-cli)

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/source/shabui)

bison_target(ShabuiParser
    ${PROJECT_SOURCE_DIR}/source/ShabuiParser.y
    ${PROJECT_BINARY_DIR}/source/shabui/ShabuiParser.cxx
)

flex_target(ShabuiScanner
    ${PROJECT_SOURCE_DIR}/source/ShabuiScanner.l
    ${PROJECT_BINARY_DIR}/source/shabui/ShabuiScanner.cxx
)

add_flex_bison_dependency(ShabuiScanner ShabuiParser)

add_library(${PROJECT_NAME}
    source/GLSLCodeBuilder.cpp
    source/GLSLLoader.cpp
    source/ParserOutput.cpp
    source/ShabuiAst.cpp
    source/StringUtils.cpp
    ${BISON_ShabuiParser_OUTPUTS}
    ${FLEX_ShabuiScanner_OUTPUTS}
)

target_compile_features(${PROJECT_NAME}
    PUBLIC cxx_std_17
    PUBLIC cxx_auto_type
    PUBLIC cxx_rvalue_references
)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
    PRIVATE ${PROJECT_BINARY_DIR}/source
)

add_executable(${PROJECT_NAME_CLI}
    ${PROJECT_SOURCE_DIR}/source/cli/Main.cpp
)

target_link_libraries(${PROJECT_NAME_CLI}
    PRIVATE ${PROJECT_NAME}
)

enable_testing()
file(GLOB TEST_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} test/*.cpp)

foreach(testSrc ${TEST_SRCS})
  get_filename_component(testName ${testSrc} NAME_WE)
  add_executable(${testName} ${testSrc})
  target_link_libraries(${testName} ${PROJECT_NAME})
  add_test(
    NAME ${testName}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test
    COMMAND ${testName}
  )
endforeach(testSrc)
