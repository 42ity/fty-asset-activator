cmake_minimum_required(VERSION 3.13)

########################################################################################################################

project(fty-asset-activator
    VERSION 1.0.0
)

########################################################################################################################
find_package(fty-cmake PATHS ${CMAKE_BINARY_DIR}/fty-cmake)
########################################################################################################################

add_subdirectory(lib)
add_subdirectory(cli)

##############################################################################################################

# if(BUILD_TESTING)
#     enable_testing()

#     # Create a target for the tests
#     etn_test(${PROJECT_NAME}-test
#         SOURCES
#             test/fty_asset_activator_private_selftest.cc
#             test/fty_asset_activator_selftest.cc
#         USES
#             ${PROJECT_NAME}
#             cxxtools
#     )

    
# endif()

etn_test_target(${PROJECT_NAME}-cli
    SOURCES
        test/main.cpp
    USES
        cxxtools
)

##############################################################################################################
