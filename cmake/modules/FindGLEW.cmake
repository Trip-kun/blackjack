set( _GLEW_HEADER_SEARCH_DIRS
        "C:/Program Files (x86)/glew/include/"
)
set( _GLEW_LIB_SEARCH_DIRS
        "C:/Program Files (x86)/glew/lib/"
)
set(_GLEW_ENV_ROOT $ENV{GLEW_ROOT})
if(NOT GLEW_ROOT AND _GLEW_ENV_ROOT)
    set(GLEW_ROOT ${_GLEW_ENV_ROOT})
endif()

if(GLEW_ROOT)
    list(INSERT _GLEW_HEADER_SEARCH_DIRS 0 "${GLEW_ROOT}/include")
    list(INSERT _GLEW_LIB_SEARCH_DIRS 0 "${GLEW_ROOT}/lib")
endif()
FIND_PATH(GLEW_INCLUDE_DIR "GL/glew.h"
        PATHS ${_GLEW_HEADER_SEARCH_DIRS})

FIND_LIBRARY(GLEW_LIBRARY NAMES libglew.a libGLEW.a libglew32.a libGLEW32.a
        PATHS ${_GLEW_LIB_SEARCH_DIRS})
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GLEW DEFAULT_MSG
        GLEW_LIBRARY GLEW_INCLUDE_DIR)
target_include_directories(${PROJECT_NAME} PUBLIC ${GLEW_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC ${GLEW_LIBRARY})