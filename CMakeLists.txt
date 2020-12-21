cmake_minimum_required (VERSION 3.10)
project("nonogram-solver")

include(compiler_flags.cmake)

set(SOURCE_FILES
	${PROJECT_SOURCE_DIR}/src/main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

add_subdirectory(nonogram-solver-lib)

target_link_libraries(${PROJECT_NAME} PRIVATE nonogram-solver-lib)

if (WIN32)
	set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/puzzles")
endif()

