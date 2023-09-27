set(STREAMING_PROTOCOL_SRC
angularsegmentkinematicsdatagram.cpp
centerofmassdatagram.cpp
datagram.cpp
eulerdatagram.cpp
jointanglesdatagram.cpp
linearsegmentkinematicsdatagram.cpp
metadatagram.cpp
parsermanager.cpp
positiondatagram.cpp
quaterniondatagram.cpp
scaledatagram.cpp
streamer.cpp
timecodedatagram.cpp
trackerkinematicsdatagram.cpp
udpserver.cpp
)

set(STREAMING_PROTOCOL_HEADERS
${CMAKE_SOURCE_DIR}/include/xsens_streaming/angularsegmentkinematicsdatagram.h
${CMAKE_SOURCE_DIR}/include/xsens_streaming/centerofmassdatagram.h
${CMAKE_SOURCE_DIR}/include/xsens_streaming/datagram.h
${CMAKE_SOURCE_DIR}/include/xsens_streaming/eulerdatagram.h
${CMAKE_SOURCE_DIR}/include/xsens_streaming/jointanglesdatagram.h
${CMAKE_SOURCE_DIR}/include/xsens_streaming/linearsegmentkinematicsdatagram.h
${CMAKE_SOURCE_DIR}/include/xsens_streaming/metadatagram.h
${CMAKE_SOURCE_DIR}/include/xsens_streaming/parsermanager.h
${CMAKE_SOURCE_DIR}/include/xsens_streaming/positiondatagram.h
${CMAKE_SOURCE_DIR}/include/xsens_streaming/quaterniondatagram.h
${CMAKE_SOURCE_DIR}/include/xsens_streaming/scaledatagram.h
${CMAKE_SOURCE_DIR}/include/xsens_streaming/streamer.h
${CMAKE_SOURCE_DIR}/include/xsens_streaming/timecodedatagram.h
${CMAKE_SOURCE_DIR}/include/xsens_streaming/trackerkinematicsdatagram.h
${CMAKE_SOURCE_DIR}/include/xsens_streaming/udpserver.h
)

add_library(xsens_streaming SHARED ${STREAMING_PROTOCOL_SRC} ${STREAMING_PROTOCOL_HEADERS})
target_include_directories(xsens_streaming PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include>)
target_link_libraries(xsens_streaming PUBLIC
    mtsdk::mtsdk # only xstypes needed
)
target_link_libraries(xsens_streaming PRIVATE Threads::Threads)
set_target_properties(xsens_streaming PROPERTIES INSTALL_RPATH "${MTSDK_LIBRARY_DIR}")


install(TARGETS xsens_streaming
    EXPORT ${TARGETS_EXPORT_NAME}
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/xsens_streaming
        DESTINATION include
        FILES_MATCHING
        PATTERN "*.h"
)

add_executable(xsens_streaming_sample main.cpp)
target_link_libraries(xsens_streaming_sample xsens_streaming)
target_link_libraries(xsens_streaming_sample Boost::program_options)
set_target_properties(xsens_streaming_sample PROPERTIES INSTALL_RPATH "${MTSDK_LIBRARY_DIR}")

install(TARGETS xsens_streaming_sample)
