cmake_minimum_required(VERSION 3.10)

#set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
#set(PROJECT_VESRION 0.0.${PATCH_VERSION})

set(HOMEWORK_NAME "homework_3")
set(HOMEWORK_NAME_APP "dummy_allocator")
set(PACKAGE_NAME "dummy_allocator")


set(MAJOR_VERSION "0" CACHE INTERNAL "Major version")
set(MINOR_VERSION "0" CACHE INTERNAL "Minor version")
set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION ${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_VERSION})

project(${PACKAGE_NAME} VERSION ${PROJECT_VESRION})

find_package(GTest REQUIRED)

set(APP_SOURCES
    main.cpp
)

set(LIB_SOURCES
    custom_allocator.h
    custom_allocator.cpp
        Container.cpp
        Container.h

)

set(TEST_SOURCES
        test_cases.cpp
)

add_executable(${HOMEWORK_NAME_APP} ${APP_SOURCES})
add_library(${HOMEWORK_NAME}_lib ${LIB_SOURCES})
add_executable(${HOMEWORK_NAME}_test ${TEST_SOURCES})

set_target_properties(${HOMEWORK_NAME_APP} ${HOMEWORK_NAME}_lib ${HOMEWORK_NAME}_test PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(${HOMEWORK_NAME}_lib
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(${HOMEWORK_NAME_APP} PRIVATE
    ${HOMEWORK_NAME}_lib
)
target_link_libraries(${HOMEWORK_NAME}_test
    GTest::gtest_main
    ${HOMEWORK_NAME}_lib
)

if (MSVC)
    target_compile_options(${HOMEWORK_NAME_APP} PRIVATE
        /W4
    )
    target_compile_options(${HOMEWORK_NAME}_lib PRIVATE
        /W4
    )
    target_compile_options(${HOMEWORK_NAME}_test PRIVATE
        /W4
    )
else ()
    target_compile_options(${HOMEWORK_NAME_APP} PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(${HOMEWORK_NAME}_lib PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(${HOMEWORK_NAME}_test PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()


#Тут стоило бы подробнее описать что за путь bin, то есть, что сюда упадёт прога при установке...
install(TARGETS ${HOMEWORK_NAME_APP} RUNTIME DESTINATION /bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

enable_testing()

add_test(${HOMEWORK_NAME}_test ${HOMEWORK_NAME}_test )
#did it work?