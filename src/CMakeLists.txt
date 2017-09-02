set(SOURCE_FILES utils.cpp call.cpp callgen_cdecl.cpp)

if(UNIX)
    list(APPEND SOURCE_FILES callgen_SysV_x86_64.cpp)
elseif(WIN64)
    list(APPEND SOURCE_FILES callgen_Win_x86_64.cpp)
endif()

add_library(callff ${SOURCE_FILES})

if(${CMAKE_CXX_COMPILER_ID} MATCHES "GNU" OR ${CMAKE_CXX_COMPILER_ID} MATCHES "Clang")
    target_compile_options(callff PRIVATE -pedantic -fpic)
    if(${BUILD_M32})
        set_target_properties(callff PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
    endif()
endif()
