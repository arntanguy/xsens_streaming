#
# Copyright 2015-2019 CNRS-UM LIRMM, CNRS-AIST JRL
#

set(BINDINGS_LIBRARIES
  xsens_streaming
)


add_cython_bindings(xsens_streaming
  TARGETS ${BINDINGS_LIBRARIES}
  VERSION ${PROJECT_VERSION}
  MODULES xsens_streaming.xsens_streaming
  EXPORT_SOURCES
    xsens_streaming/__init__.py
    xsens_streaming/c_xsens_streaming.pxd
    xsens_streaming/xsens_streaming.pxd
  PRIVATE_SOURCES
    xsens_streaming/xsens_streaming.pyx
)
