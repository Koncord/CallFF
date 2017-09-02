set(SOURCE_FILES utils.cpp call.cpp)

if(UNIX)
    list(APPEND SOURCE_FILES callgen_SysV_x86_64.cpp)
elseif(WIN64)
    list(APPEND SOURCE_FILES callgen_Win_x86_64.cpp)
endif()

add_library(callff ${SOURCE_FILES})

if(${CMAKE_CXX_COMPILER_ID} MATCHES "GNU" OR ${CMAKE_CXX_COMPILER_ID} MATCHES "Clang")
    target_compile_options(callff PRIVATE -pedantic -fpic)
endif()
