set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	set(COMPILER_FLAG_WARNINGS "/W3")
	set(COMPILER_FLAG_TREAT_WARNING_AS_ERROR "/WX")
	set(COMPILER_FLAG_MULTIPLE_PROCESSES "/MP")
endif()
	
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	set(COMPILER_FLAG_WARNINGS "-Wall" "-Wextra" "-Wformat=2" "-Wconversion" "-Wsign-compare")
	
	## disable too strict warnings
	set(COMPILER_FLAG_WARNINGS ${COMPILER_FLAG_WARNINGS} "-Wno-double-promotion" "-Wno-switch-enum")
	
	set(COMPILER_FLAG_TREAT_WARNING_AS_ERROR "-Werror")
	set(COMPILER_FLAG_PEDANTIC "-Wpedantic")
	
	if (NOT WIN32)
		set(COMPILER_FLAG_OLD_STYLE_CAST "$<$<COMPILE_LANGUAGE:CXX>:-Wold-style-cast>")
	else()
		set(COMPILER_FLAG_OLD_STYLE_CAST "-Wold-style-cast")
	endif()
endif()

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	## disable too strict warnings
    set(COMPILER_FLAG_WARNINGS)
	list(APPEND COMPILER_FLAG_WARNINGS "-Wno-nonportable-system-include-path" "-Wno-shadow-field-in-constructor")
	list(APPEND COMPILER_FLAG_WARNINGS "-Wno-global-constructors" "-Wno-exit-time-destructors")
	list(APPEND COMPILER_FLAG_WARNINGS "-Wno-c++98-compat-pedantic")
    list(APPEND COMPILER_FLAG_WARNINGS "-Wno-zero-as-null-pointer-constant")

    if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL "10.0.0")
        list(APPEND COMPILER_FLAG_WARNINGS "-Wno-return-std-move-in-c++11" )
    endif()
endif()

set(COMPILER_FLAGS ${COMPILER_FLAG_WARNINGS}
                   ${COMPILER_FLAG_TREAT_WARNING_AS_ERROR}
				   ${COMPILER_FLAG_MULTIPLE_PROCESSES}
				   ${COMPILER_FLAG_PEDANTIC}
				   ${COMPILER_FLAG_OLD_STYLE_CAST})
add_compile_options(${COMPILER_FLAGS})

## workaround for Visual Studio build with Clang
if (WIN32 AND "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	add_compile_options("-Wno-unused-command-line-argument")
endif()
