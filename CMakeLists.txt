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

if(BUILD_TESTING)
    enable_testing()

    # Create a target for the tests
    etn_test(${PROJECT_NAME}-test
        SOURCES
            test/fty_asset_activator_private_selftest.cc
            test/fty_asset_activator_selftest.cc
            lib/public_includes/fty_asset_activator.h
        INCLUDE_DIRS
            lib
        USES
            ${PROJECT_NAME}-static
            czmq
            cxxtools  # cxxtools cannot be use as public because we do not have the cmake package yet
            fty_common
            fty_common_logging
            fty_proto
            fty_common_mlm
            fty_common_translation
            mlm
            magic
            fty-utils
    )

    
endif()

##############################################################################################################
