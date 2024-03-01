from libcpp.string cimport string
from libcpp cimport bool as cppbool
from libcpp.vector cimport vector


cdef extern from "<xsens_streaming/jointanglesdatagram.h>":
    cdef struct JointAngles "JointAnglesDatagram::Joint":
        unsigned int parent
        unsigned int child
        float rotation[3]

cdef extern from "<xsens_streaming/quaterniondatagram.h>":
    cdef struct QuatKinematics "QuaternionDatagram::Kinematics":
        int segmentId
        float position[3]
        float orientation[4]

cdef extern from "<xsens_streaming/eulerdatagram.h>":
    cdef struct EulerKinematics "EulerDatagram::Kinematics":
        unsigned int segmentId
        float pos[3]
        float rotation[3]

cdef extern from "<xsens_streaming/positiondatagram.h>":
    cdef struct VirtualMarkerSet "PositionDatagram::VirtualMarkerSet":
        unsigned int segmentId
        float pointPos[3]

cdef extern from "<xsens_streaming/linearsegmentkinematicsdatagram.h>":
    cdef struct LinearSegmentKinematics "LinearSegmentKinematicsDatagram::Kinematics":
        int segmentId
        float pos[3]
        float velocity[3]
        float acceleration[3]

cdef extern from "<xsens_streaming/angularsegmentkinematicsdatagram.h>":
    cdef struct AngularSegmentKinematics "AngularSegmentKinematicsDatagram::Kinematics":
        int segmentId
        float segmentOrien[4]
        float angularVeloc[3]
        float angularAccel[3]


cdef extern from "<xsens_streaming/trackerkinematicsdatagram.h>":
    cdef struct TrackerKinematics "TrackerKinematicsDatagram::Kinematics":
        int segmentId
        float sens_rot[4]
        float sen_freeAcc[3]
        float sen_acc[3]
        float sen_gyr[3]
        float sen_mag[3]

cdef extern from "<xsens_streaming/scaledatagram.h>" namespace "ScaleDatagram":
    cdef struct PointDefinition:
        unsigned int segmentId
        unsigned int pointId
        string segmentName
        int characteristicOfPoint
        float pos[3]

    cdef struct NullPoseDefinition:
        string segmentName
        float pos[3]

cdef extern from "<xsens_streaming/timecodedatagram.h>" namespace "TimeCodeDatagram":
    cdef struct TimeCode:
        long int nano
        signed char hour
        signed char minute
        signed char second

cdef extern from "<xsens_streaming/centerofmassdatagram.h>":
    cdef struct CoMKinematics "CenterOfMassDatagram::Kinematics":
        float pos[3]
        float vel[3]
        float acc[3]


cdef extern from "<xsens_streaming/udpserver.h>":
    cdef cppclass UdpServer:
        UdpServer(const string&, unsigned int port)
        UdpServer(const string&)
        UdpServer(unsigned int port)
        UdpServer()

        void printDatagrams(cppbool enable_print)

        vector[JointAngles] jointAngles()
        vector[QuatKinematics] quaternions()
        vector[VirtualMarkerSet] virtualMarkerPositions()
        vector[LinearSegmentKinematics] linearSegmentKinematics()
        vector[AngularSegmentKinematics] angularSegmentKinematics()
        vector[EulerKinematics] euler()
        vector[PointDefinition] pointDefinition()
        vector[NullPoseDefinition] nullPoseDefinition()
        vector[TrackerKinematics] trackerData()
        TimeCode timeCode()
        CoMKinematics comData()

        void waitQuaternions()
        void waitJointAngles()
        void waitVirtualMarkerPositions()
        void waitLinearSegmentKinematics()
        void waitAngularSegmentKinematics()
        void waitEuler()
        void waitPointDefinition()
        void waitNullPoseDefinition()
        void waitTrackerData()
        void waitTimeCode()
        void waitComData()
