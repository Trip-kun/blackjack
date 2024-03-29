set( _soil_HEADER_SEARCH_DIRS
"C:/Program Files (x86)/SOIL/include/"
)
set( _soil_LIB_SEARCH_DIRS
"C:/Program Files (x86)/SOIL/lib/"
)
set(_soil_ENV_ROOT $ENV{SOIL_ROOT})
if(NOT SOIL_ROOT AND _soil_ENV_ROOT)
    set(SOIL_ROOT ${_soil_ENV_ROOT})
endif()

if(SOIL_ROOT)
    list(INSERT _soil_HEADER_SEARCH_DIRS 0 "${SOIL_ROOT}/include")
    list(INSERT _soil_LIB_SEARCH_DIRS 0 "${SOIL_ROOT}/lib")
endif()
FIND_PATH(SOIL_INCLUDE_DIR "SOIL/SOIL.h"
PATHS ${_soil_HEADER_SEARCH_DIRS})

FIND_LIBRARY(SOIL_LIBRARY NAMES libsoil.a libSOIL.a
PATHS ${_soil_LIB_SEARCH_DIRS})
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(soil DEFAULT_MSG
SOIL_LIBRARY SOIL_INCLUDE_DIR)
target_include_directories(${PROJECT_NAME} PUBLIC ${SOIL_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC ${SOIL_LIBRARY})