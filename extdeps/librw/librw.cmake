extdeps_add_cmake_project(librw
    GIT_REPOSITORY "https://github.com/kaalkuul/librw.git"
    GIT_TAG "681d137cd97be1ae3c945f03e98fc5e088589997"
    CMAKE_ARGS
        -DLIBRW_PLATFORM=GL3
        -DLIBRW_GL3_GFXLIB=EXTGL3
        -DLIBRW_EXAMPLES=OFF
)

if (MSVC)
    add_debug_dep(dep_librw)
endif ()
