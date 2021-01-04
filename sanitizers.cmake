if (CMAKE_BUILD_TYPE STREQUAL UBSan)
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")

        add_compile_options(
            -fsanitize=undefined

            -fsanitize=alignment
            -fsanitize=bool
            -fsanitize=bounds
            -fsanitize=bounds-strict
            -fsanitize=builtin

            -fsanitize=enum
            -fsanitize=float-divide-by-zero
            -fsanitize=float-cast-overflow
            -fsanitize=integer-divide-by-zero
            -fsanitize=nonnull-attribute

            -fsanitize=null
            -fsanitize=object-size
            -fsanitize=pointer-overflow
            -fsanitize=return
            -fsanitize=returns-nonnull-attribute

            -fsanitize=shift
            -fsanitize=shift-base
            -fsanitize=shift-exponent

            -fsanitize=signed-integer-overflow
            -fsanitize=unreachable
            -fsanitize=vla-bound
            -fsanitize=vptr

            -fno-sanitize-recover=all
        )

        add_link_options(-fsanitize=undefined)

    elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")

        add_compile_options(
            -fsanitize=undefined
            -fsanitize=integer

            -fsanitize=alignment
            -fsanitize=bool
            -fsanitize=builtin
            -fsanitize=bounds
            -fsanitize=enum

            -fsanitize=float-cast-overflow
            -fsanitize=float-divide-by-zero
            -fsanitize=function

            -fsanitize=implicit-unsigned-integer-truncation
            -fsanitize=implicit-signed-integer-truncation
            -fsanitize=implicit-integer-sign-change
            -fsanitize=integer-divide-by-zero

            -fsanitize=nonnull-attribute
            -fsanitize=null
            -fsanitize=nullability-arg
            -fsanitize=nullability-assign
            -fsanitize=nullability-return

            -fsanitize=object-size
            -fsanitize=pointer-overflow
            -fsanitize=return
            -fsanitize=returns-nonnull-attribute

            -fsanitize=shift
            -fsanitize=signed-integer-overflow
            -fsanitize=unreachable
            -fsanitize=unsigned-integer-overflow

            -fsanitize=vla-bound
            -fsanitize=vptr

            -fno-sanitize-recover=all
        )

        add_link_options(-fsanitize=undefined)
        add_link_options(-fuse-ld=lld)
    endif() 
endif()

