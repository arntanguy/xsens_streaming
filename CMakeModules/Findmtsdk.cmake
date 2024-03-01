#
# Copyright 2021 CNRS-UM LIRMM
#

# Try to find the MT Software Suite SDK for XSens
#
# This can use MTSDK_PREFIX as an hint
#
# Defines the mtsdk::mtsdk target

set(MTSDK mtsdk::mtsdk)
if(NOT TARGET ${MTSDK})
  if(NOT DEFINED MTSDK_PREFIX)
    set(MTSDK_PREFIX ${CMAKE_INSTALL_PREFIX})
  endif()

  find_path(MTSDK_INCLUDE_DIR
    NAMES xstypes.h
    HINTS ${MTSDK_PREFIX}
    PATHS /usr/local
    PATH_SUFFIXES xsens/include
    )

  find_path(MTSDK_LIBRARY_DIR
    NAMES libxstypes.so
    HINTS ${MTSDK_PREFIX}
    PATHS /usr/local
    PATH_SUFFIXES xsens/lib
    )

  find_library(MTSDK_LIBRARY
    NAMES "xstypes"
    PATHS ${MTSDK_PREFIX}
    PATHS /usr/local
    PATH_SUFFIXES xsens/lib
    )

  include(FindPackageHandleStandardArgs)
  find_package_handle_standard_args(mtsdk DEFAULT_MSG MTSDK_LIBRARY MTSDK_INCLUDE_DIR)
  mark_as_advanced(MTSDK_INCLUDE_DIR MTSDK_LIBRARY)
  if(MTSDK_FOUND)
    add_library(${MTSDK} INTERFACE IMPORTED GLOBAL)
    set_target_properties(${MTSDK} PROPERTIES
      INTERFACE_INCLUDE_DIRECTORIES "${MTSDK_INCLUDE_DIR}"
      INTERFACE_LINK_LIBRARIES ${MTSDK_LIBRARY}
      )
  endif()
endif()
