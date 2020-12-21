cmake_minimum_required (VERSION 3.10)
project("nonogram-solver-lib")

set(INCLUDE_FILES
    ${PROJECT_SOURCE_DIR}/include/puzzle.h
    ${PROJECT_SOURCE_DIR}/include/puzzle_solver.h
)

set(SOURCE_FILES
	${PROJECT_SOURCE_DIR}/src/puzzle.cpp
    ${PROJECT_SOURCE_DIR}/src/puzzle_solver.cpp
)

add_library(${PROJECT_NAME} ${INCLUDE_FILES} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

