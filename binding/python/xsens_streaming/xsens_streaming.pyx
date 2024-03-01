# distutils: language = c++

cimport xsens_streaming.c_xsens_streaming as c_xsens_streaming

cdef class UdpServer(object):
    def __cinit__(self, address: str = "localhost", port: int = 9763):
        self.impl = new c_xsens_streaming.UdpServer(address.encode(), port)

    def __dealloc__(self):
        del self.impl

    def printDatagrams(self, enable_print: bool):
        self.impl.printDatagrams(enable_print)

    def quaternions(self):
        return self.impl.quaternions()

    def jointAngles(self):
        return self.impl.jointAngles()

    def virtualMarkerPositions(self):
        return self.impl.virtualMarkerPositions()

    def linearSegmentKinematics(self):
        return self.impl.linearSegmentKinematics()

    def angularSegmentKinematics(self):
        return self.impl.angularSegmentKinematics()

    def euler(self):
        return self.impl.euler()

    def pointDefinition(self):
        return self.impl.pointDefinition()

    def nullPoseDefinition(self):
        return self.impl.nullPoseDefinition()

    def trackerData(self):
        return self.impl.trackerData()

    def timeCode(self):
        return self.impl.timeCode()

    def comData(self):
        return self.impl.comData()

    def waitQuaternions(self):
        return self.impl.waitQuaternions()

    def waitJointAngles(self):
        return self.impl.waitJointAngles()

    def waitVirtualMarkerPositions(self):
        return self.impl.waitVirtualMarkerPositions()

    def waitLinearSegmentKinematics(self):
        return self.impl.waitLinearSegmentKinematics()

    def waitAngularSegmentKinematics(self):
        return self.impl.waitAngularSegmentKinematics()

    def waitEuler(self):
        return self.impl.waitEuler()

    def waitPointDefinition(self):
        return self.impl.waitPointDefinition()

    def waitNullPoseDefinition(self):
        return self.impl.waitNullPoseDefinition()

    def waitTrackerData(self):
        return self.impl.waitTrackerData()

    def waitTimeCode(self):
        return self.impl.waitTimeCode()

    def waitComData(self):
        return self.impl.waitComData()
