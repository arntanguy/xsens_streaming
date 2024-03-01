cimport c_xsens_streaming

cdef class UdpServer(object):
	cdef c_xsens_streaming.UdpServer * impl
