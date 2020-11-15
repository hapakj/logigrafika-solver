cmake_minimum_required (VERSION 3.10)
project("logigrafika-solver")

include(compiler_flags.cmake)

set(SOURCE_FILES
	${PROJECT_SOURCE_DIR}/src/main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

