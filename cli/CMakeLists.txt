cmake_minimum_required(VERSION 3.13)
cmake_policy(VERSION 3.13)

project(fty-asset-activator-cli
    VERSION 1.0.0
)

##############################################################################################################
find_package(fty-cmake PATHS ${CMAKE_BINARY_DIR}/fty-cmake)
##############################################################################################################


##############################################################################################################

etn_target(exe ${PROJECT_NAME}
    SOURCES
        src/fty-asset-activator-cli.cpp
    USES_PRIVATE
        fty_asset_activator
        fty_common
        fty_common_mlm
        fty_common_logging
        fty-utils
        fty_proto
        czmq
)
