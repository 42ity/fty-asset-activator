cmake_minimum_required(VERSION 3.13)
cmake_policy(VERSION 3.13)


##############################################################################################################
find_package(fty-cmake PATHS ${CMAKE_BINARY_DIR}/fty-cmake)
##############################################################################################################


##############################################################################################################

etn_target(shared ${PROJECT_NAME}
    SOURCES
        src/libfty_asset_activator.cc
    PUBLIC_INCLUDE_DIR
        public_includes
    PUBLIC
        fty_asset_activator.h
        fty_asset_activator_commands.h
        fty_asset_activator_library.h
        libfty_asset_activator.h
    USES_PUBLIC
        fty-asset
    USES_PRIVATE
        cxxtools
        czmq
        fty-asset-accessor
        fty_common
        fty_common_logging
        fty_common_mlm
        fty_proto
        fty-utils
        libzmq
        libsodium
        mlm
)

##############################################################################################################
