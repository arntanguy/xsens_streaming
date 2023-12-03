/*! \file
  \section FileCopyright Copyright Notice
  This is free and unencumbered software released into the public domain.

  Anyone is free to copy, modify, publish, use, compile, sell, or
  distribute this software, either in source code form or as a compiled
  binary, for any purpose, commercial or non-commercial, and by any
  means.

  In jurisdictions that recognize copyright laws, the author or authors
  of this software dedicate any and all copyright interest in the
  software to the public domain. We make this dedication for the benefit
  of the public at large and to the detriment of our heirs and
  successors. We intend this dedication to be an overt act of
  relinquishment in perpetuity of all present and future rights to this
  software under copyright law.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
  IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
  OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
  ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
  OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <thread>

#include <xsens_streaming/angularsegmentkinematicsdatagram.h>
#include <xsens_streaming/centerofmassdatagram.h>
#include <xsens_streaming/eulerdatagram.h>
#include <xsens_streaming/jointanglesdatagram.h>
#include <xsens_streaming/linearsegmentkinematicsdatagram.h>
#include <xsens_streaming/parsermanager.h>
#include <xsens_streaming/positiondatagram.h>
#include <xsens_streaming/quaterniondatagram.h>
#include <xsens_streaming/scaledatagram.h>
#include <xsens_streaming/streamer.h>
#include <xsens_streaming/timecodedatagram.h>
#include <xsens_streaming/trackerkinematicsdatagram.h>
#include <xstypes/xssocket.h>
#include <xstypes/xsthread.h>

struct Datagram;

/**
 * @brief Receives data streamed using "Xsens MVN real-time network streaming Protocol Specification"
 *
 * For details, please refer to:
 * https://www.xsens.com/hubfs/Downloads/Manuals/MVN_real-time_network_streaming_protocol_specification.pdf
 */
class UdpServer
{
public:
  /**
   * @brief Construct a new Udp Server object
   *
   * @param address Address of the MVN streamer
   * @param port Port of the MVN streamer
   *
   * @throws std::runtime_error when the connection fails to establish
   */
  UdpServer(XsString address = "localhost", uint16_t port = 9763);
  virtual ~UdpServer();

  std::vector<QuaternionDatagram::Kinematics> quaternions() const
  {
    std::lock_guard<std::mutex> lock(quaternionMutex_);
    isQuaternionAvail_ = false;
    return quaternions_;
  }

  std::vector<JointAnglesDatagram::Joint> jointAngles() const
  {
    std::lock_guard<std::mutex> lock(jointAnglesMutex_);
    isJointAnglesAvail_ = false;
    return jointAngles_;
  }

  std::vector<PositionDatagram::VirtualMarkerSet> virtualMarkerPositions() const
  {
    std::lock_guard<std::mutex> lock(virtualMarkerPositionMutex_);
    isVirtualMarkerPositionAvail_ = false;
    return virtualMarkerPositions_;
  }

  std::vector<LinearSegmentKinematicsDatagram::Kinematics> linearSegmentKinematics() const
  {
    std::lock_guard<std::mutex> lock(linearSegmentKinematicsMutex_);
    isLinearSegmentKinematicAvail_ = false;
    return linearSegmentKinematics_;
  }

  std::vector<EulerDatagram::Kinematics> euler() const
  {
    std::lock_guard<std::mutex> lock(eulerMutex_);
    isEulerAvail_ = false;
    return euler_;
  }

  std::vector<AngularSegmentKinematicsDatagram::Kinematics> angularSegmentKinematics() const
  {
    std::lock_guard<std::mutex> lock(angularSegmentKinematicsMutex_);
    isAngularSegmentKinematicsAvail_ = false;
    return angularSegmentKinematics_;
  }

  std::vector<ScaleDatagram::PointDefinition> pointDefinition() const
  {
    std::lock_guard<std::mutex> lock(dataDefinitionMutex_);
    isPointDefinitionAvail_ = false;
    return pointDefinition_;
  }

  std::vector<ScaleDatagram::NullPoseDefinition> nullPoseDefinition() const
  {
    std::lock_guard<std::mutex> lock(dataDefinitionMutex_);
    isNullPoseDefinitionAvail_ = false;
    return nullPoseDefinition_;
  }

  std::vector<TrackerKinematicsDatagram::Kinematics> trackerData() const
  {
    std::lock_guard<std::mutex> lock(trackerDataMutex_);
    isTrackerDataAvail_ = false;
    return trackerData_;
  }

  TimeCodeDatagram::TimeCode timeCode() const
  {
    std::lock_guard<std::mutex> lock(timeCodeMutex_);
    isTimeCodeAvail_ = false;
    return timeCode_;
  }

  CenterOfMassDatagram::Kinematics comData() const
  {
    std::lock_guard<std::mutex> lock(comDataMutex_);
    isComDataAvail_ = false;
    return comData_;
  }

  void printDatagrams(bool print)
  {
    printDatagrams_ = print;
  }

  void waitQuaternions() const
  {
    std::unique_lock<std::mutex> lock(quaternionMutex_);
    quaternionCV_.wait(lock, [this] { return isQuaternionAvail_; });
  }

  void waitJointAngles() const
  {
    std::unique_lock<std::mutex> lock(jointAnglesMutex_);
    jointAnglesCV_.wait(lock, [this] { return isJointAnglesAvail_; });
  }

  void waitVirtualMarkerPositions() const
  {
    std::unique_lock<std::mutex> lock(virtualMarkerPositionMutex_);
    virtualMarkerPositionCV_.wait(lock, [this] { return isVirtualMarkerPositionAvail_; });
  }

  void waitLinearSegmentKinematics() const
  {
    std::unique_lock<std::mutex> lock(linearSegmentKinematicsMutex_);
    linearSegmentKinematicsCV_.wait(lock, [this] { return isLinearSegmentKinematicAvail_; });
  }

  void waitEuler() const
  {
    std::unique_lock<std::mutex> lock(eulerMutex_);
    eulerCV_.wait(lock, [this] { return isEulerAvail_; });
  }

  void waitAngularSegmentKinematics() const
  {
    std::unique_lock<std::mutex> lock(angularSegmentKinematicsMutex_);
    angularSegmentKinematicsCV_.wait(lock, [this] { return isAngularSegmentKinematicsAvail_; });
  }

  void waitPointDefinition() const
  {
    std::unique_lock<std::mutex> lock(dataDefinitionMutex_);
    dataDefinitionCV_.wait(lock, [this] { return isPointDefinitionAvail_; });
  }

  void waitNullPoseDefinition() const
  {
    std::unique_lock<std::mutex> lock(dataDefinitionMutex_);
    dataDefinitionCV_.wait(lock, [this] { return isNullPoseDefinitionAvail_; });
  }

  void waitTrackerData() const
  {
    std::unique_lock<std::mutex> lock(trackerDataMutex_);
    trackerDataCV_.wait(lock, [this] { return isTrackerDataAvail_; });
  }

  void waitTimeCode() const
  {
    std::unique_lock<std::mutex> lock(timeCodeMutex_);
    timeCodeCV_.wait(lock, [this] { return isTimeCodeAvail_; });
  }

  void waitComData() const
  {
    std::unique_lock<std::mutex> lock(comDataMutex_);
    comDataCV_.wait(lock, [this] { return isComDataAvail_; });
  }

protected:
  void readMessages();
  void startThread();
  void stopThread();

protected:
  std::thread th_;

  std::vector<QuaternionDatagram::Kinematics> quaternions_;
  mutable std::mutex quaternionMutex_;
  mutable std::condition_variable quaternionCV_;
  mutable bool isQuaternionAvail_{false};

  std::vector<JointAnglesDatagram::Joint> jointAngles_;
  mutable std::mutex jointAnglesMutex_;
  mutable std::condition_variable jointAnglesCV_;
  mutable bool isJointAnglesAvail_{false};

  std::vector<PositionDatagram::VirtualMarkerSet> virtualMarkerPositions_;
  mutable std::mutex virtualMarkerPositionMutex_;
  mutable std::condition_variable virtualMarkerPositionCV_;
  mutable bool isVirtualMarkerPositionAvail_{false};

  std::vector<LinearSegmentKinematicsDatagram::Kinematics> linearSegmentKinematics_;
  mutable std::mutex linearSegmentKinematicsMutex_;
  mutable std::condition_variable linearSegmentKinematicsCV_;
  mutable bool isLinearSegmentKinematicAvail_{false};

  std::vector<EulerDatagram::Kinematics> euler_;
  mutable std::mutex eulerMutex_;
  mutable std::condition_variable eulerCV_;
  mutable bool isEulerAvail_{false};

  std::vector<AngularSegmentKinematicsDatagram::Kinematics> angularSegmentKinematics_;
  mutable std::mutex angularSegmentKinematicsMutex_;
  mutable std::condition_variable angularSegmentKinematicsCV_;
  mutable bool isAngularSegmentKinematicsAvail_{false};

  std::vector<ScaleDatagram::PointDefinition> pointDefinition_;
  std::vector<ScaleDatagram::NullPoseDefinition> nullPoseDefinition_;
  mutable std::mutex dataDefinitionMutex_;
  mutable std::condition_variable dataDefinitionCV_;
  mutable bool isPointDefinitionAvail_;
  mutable bool isNullPoseDefinitionAvail_{false};

  std::vector<TrackerKinematicsDatagram::Kinematics> trackerData_;
  mutable std::mutex trackerDataMutex_;
  mutable std::condition_variable trackerDataCV_;
  mutable bool isTrackerDataAvail_{false};

  TimeCodeDatagram::TimeCode timeCode_;
  mutable std::mutex timeCodeMutex_;
  mutable std::condition_variable timeCodeCV_;
  mutable bool isTimeCodeAvail_{false};

  CenterOfMassDatagram::Kinematics comData_;
  mutable std::mutex comDataMutex_;
  mutable std::condition_variable comDataCV_;
  mutable bool isComDataAvail_{false};

  std::unique_ptr<XsSocket> socket_;
  uint16_t port_;
  XsString hostName_;

  std::unique_ptr<ParserManager> parserManager_;
  bool printDatagrams_ = false;

  volatile std::atomic_bool started_{false}, stopping_{false};
};

#endif
