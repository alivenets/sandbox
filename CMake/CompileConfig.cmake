include(CheckCXXCompilerFlag)

function(target_activate_pedantic_compilation TARGET)
    # Basic compilation flags that are supported by GCC
    set(BASE_COMPILATION_FLAGS
     -pedantic-errors
     -Wunused -Wall -Wextra
     -Werror=return-type -Werror=init-self -Werror=sequence-point -Werror=parentheses
     -Werror=sign-compare -Werror=bool-compare -Werror=logical-not-parentheses
     -Werror=float-conversion -Werror=missing-braces -Werror=shift-count-negative -Werror=shift-count-overflow
     -Werror=switch-default
     -Wstrict-aliasing -Wstrict-overflow -Wlogical-op
     -Wuninitialized -Wignored-qualifiers -Wattributes -Wdate-time -Wmissing-declarations
     -Wshadow
     -Wformat-signedness -Wformat -Wformat-security -Wformat-y2k
     -Wpacked -Wunused-parameter -Wfloat-equal -Wmissing-include-dirs
     -Wsuggest-attribute=pure -Wsuggest-attribute=const -Wsuggest-attribute=noreturn -Wsuggest-final-types
     -Wcast-qual -Wsign-promo -Woverloaded-virtual
    )

    # Additional compilation flags depending on GCC version
    check_cxx_compiler_flag(-Werror=shift-negative-value HAS_NEGATIVE_VALUE)
    if(HAS_NEGATIVE_VALUE)
        list(APPEND EXT_COMPILATION_FLAGS -Werror=shift-negative-value)
    endif()

    check_cxx_compiler_flag(-Wduplicated-cond HAS_DUPLICATED_COND)
    if(HAS_DUPLICATED_COND)
        list(APPEND EXT_COMPILATION_FLAGS -Wduplicated-cond)
    endif()

    check_cxx_compiler_flag(-Wignored-attributes HAS_IGNORED_ATTRIBUTES)
    if(HAS_IGNORED_ATTRIBUTES)
        list(APPEND EXT_COMPILATION_FLAGS -Wignored-attributes)
    endif()

    check_cxx_compiler_flag(-Wnull-dereference HAS_NULL_DEREFERENCE)
    if(HAS_NULL_DEREFERENCE)
        list(APPEND EXT_COMPILATION_FLAGS -Wnull-dereference)
    endif()

    check_cxx_compiler_flag(-Wduplicated-branches HAS_DUPLICATED_BRANCHES)
    if(HAS_DUPLICATED_BRANCHES)
        list(APPEND EXT_COMPILATION_FLAGS -Wduplicated-branches)
    endif()

    check_cxx_compiler_flag(-Wrestrict HAS_RESTRICT)
    if(HAS_RESTRICT)
        list(APPEND EXT_COMPILATION_FLAGS -Wrestrict)
    endif()

    check_cxx_compiler_flag(-Wformat-overflow=2 HAS_FORMAT_OVERFLOW)
    if(HAS_FORMAT_OVERFLOW)
        list(APPEND EXT_COMPILATION_FLAGS -Wformat-overflow=2)
    endif()

    check_cxx_compiler_flag(-Wformat-truncation=2 HAS_FORMAT_TRUNCATION)
    if(HAS_FORMAT_TRUNCATION)
        list(APPEND EXT_COMPILATION_FLAGS -Wformat-truncation=2)
    endif()

    check_cxx_compiler_flag(-Werror=alloca HAS_ALLOCA)
    if(HAS_ALLOCA)
        list(APPEND EXT_COMPILATION_FLAGS -Werror=alloca)
    endif()

    check_cxx_compiler_flag(-Werror=dangling-else HAS_DANGLING_ELSE)
    if(HAS_DANGLING_ELSE)
        list(APPEND EXT_COMPILATION_FLAGS -Werror=dangling-else)
    endif()

    check_cxx_compiler_flag(-Werror=pointer-compare HAS_POINTER_COMPARE)
    if(HAS_POINTER_COMPARE)
        list(APPEND EXT_COMPILATION_FLAGS -Werror=pointer-compare)
    endif()

    check_cxx_compiler_flag(-Werror=bool-operation HAS_BOOL_OPERATION)
    if(HAS_BOOL_OPERATION)
        list(APPEND EXT_COMPILATION_FLAGS -Werror=bool-operation)
    endif()

    check_cxx_compiler_flag(-Werror=switch-unreachable HAS_SWITCH_UNREACHABLE)
    if(HAS_SWITCH_UNREACHABLE)
        list(APPEND EXT_COMPILATION_FLAGS -Werror=switch-unreachable)
    endif()

    target_compile_options(${TARGET} PRIVATE ${BASE_COMPILATION_FLAGS} ${EXT_COMPILATION_FLAGS})

    # TODO: add flags: -Weffc++
endfunction()
