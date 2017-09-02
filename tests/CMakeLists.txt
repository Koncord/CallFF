set(SOURCE_FILES main.cpp)

add_executable(simpleTest ${SOURCE_FILES})
target_link_libraries(simpleTest callff)

if(${BUILD_M32})
    set_target_properties(simpleTest PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif()
