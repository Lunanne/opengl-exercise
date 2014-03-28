    include(FindPackageHandleStandardArgs)
    find_path( SOIL_INCLUDE_DIR "SOIL.h" PATH_SUFFIXES SOIL )
    find_library( SOIL_LIBRARIES SOIL )
    find_package_handle_standard_args(SOIL DEFAULT_MSG SOIL_LIBRARIES SOIL_INCLUDE_DIR )