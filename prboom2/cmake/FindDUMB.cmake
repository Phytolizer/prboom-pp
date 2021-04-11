set(DUMB_SEARCH_PATHS /usr/local/ /usr /opt)

find_path(
  DUMB_INCLUDE_DIR dumb.h
  HINTS ${DUMB_ROOT}
  PATH_SUFFIXES include include/dumb
  PATHS ${DUMB_SEARCH_PATHS})
find_library(
  DUMB_LIBRARY dumb
  HINTS ${DUMB_ROOT}
  PATH_SUFFIXES lib64 lib
  PATHS ${DUMB_SEARCH_PATHS})

if(DUMB_INCLUDE_DIR AND DUMB_LIBRARY)
  set(DUMB_FOUND TRUE)
endif(DUMB_INCLUDE_DIR AND DUMB_LIBRARY)

if(DUMB_FOUND)
  message(STATUS "Found Dumb: ${DUMB_LIBRARY}")
else(DUMB_FOUND)
  message(STATUS "Could NOT find Dumb")
endif(DUMB_FOUND)
