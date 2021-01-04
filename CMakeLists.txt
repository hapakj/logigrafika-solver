cmake_minimum_required (VERSION 3.10)
project("nonogram-solver")

include(compiler_flags.cmake)

function(setup_build_type src dst)
    string(TOUPPER ${src} src)
    string(TOUPPER ${dst} dst)

    set(CMAKE_EXE_LINKER_FLAGS_${dst} "${CMAKE_EXE_LINKER_FLAGS_${src}}" CACHE STRING "Flags used by the linker during ${dst} builds." FORCE)
    set(CMAKE_SHARED_LINKER_FLAGS_${dst} "${CMAKE_SHARED_LINKER_FLAGS_${src}}" CACHE STRING "Flags used by the linker during ${dst} builds." FORCE)
    set(CMAKE_MODULE_LINKER_FLAGS_${dst} "${CMAKE_MODULE_LINKER_FLAGS_${src}}" CACHE STRING "Flags used by the linker during ${dst} builds." FORCE)
    set(CMAKE_C_FLAGS_${dst} "${CMAKE_C_FLAGS_${src}}" CACHE STRING "Flags used by the compiler during ${dst} builds." FORCE)
    set(CMAKE_CXX_FLAGS_${dst} "${CMAKE_CXX_FLAGS_${src}}" CACHE STRING "Flags used by the compiler during ${dst} builds." FORCE)
endfunction()

setup_build_type("Debug" "UBSan")

include(sanitizers.cmake)

set(SOURCE_FILES
    ${PROJECT_SOURCE_DIR}/src/main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

add_subdirectory(nonogram-solver-lib)

target_link_libraries(${PROJECT_NAME} PRIVATE nonogram-solver-lib)

if (WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/puzzles")
endif()

