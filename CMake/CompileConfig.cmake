function(add_strict_compilation_flags TARGET)
set(COMPILATION_FLAGS
    -Wunused -Wall -Wpedantic -Wextra -Werror=return-type -Werror=alloca -Werror=init-self -Werror=sequence-point
    -Werror=dangling-else -Werror=parentheses -Werror=sign-compare -Werror=pointer-compare -Werror=bool-compare
    -Werror=bool-operation -Werror=logical-not-parentheses -Werror=float-conversion -Werror=missing-braces
    -Werror=shift-count-negative -Werror=shift-count-overflow -Werror=shift-negative-value -Werror=switch-default
    -Werror=switch-unreachable
    -Wstrict-aliasing -Wstrict-overflow -Wduplicated-cond -Wduplicated-branches
    -Wlogical-op -Wrestrict -Wuninitialized -Wignored-qualifiers -Wattributes -Wignored-attributes -Wdate-time
    -Wmissing-declarations -Wnull-dereference -Wshadow -Wformat-overflow=2 -Wformat-signedness
    -Wformat-truncation=2 -Wformat -Wformat-security -Wformat-y2k -Wpacked -Wunused-parameter -Wfloat-equal
    -Wmissing-include-dirs -Wsuggest-attribute=pure -Wsuggest-attribute=const -Wsuggest-attribute=noreturn
    -Wsuggest-final-types -Wcast-qual -Wsign-promo -Woverloaded-virtual
    )

    target_compile_options(${TARGET} PRIVATE ${COMPILATION_FLAGS})

# TODO: add new flags: -Weffc++
endfunction()

