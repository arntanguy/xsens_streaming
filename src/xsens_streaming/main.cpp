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

#include <boost/program_options.hpp>
#include <xsens_streaming/streamer.h>
#include <xsens_streaming/udpserver.h>
#include <xstypes/xstime.h>
namespace po = boost::program_options;

int main(int argc, char * argv[])
{
  auto host = std::string{};
  auto port = 0u;
  po::options_description desc("xsens_streaming_sample options");
  // clang-format off
  desc.add_options()
    ("help", "Produce this message")
  	("host,h", po::value<std::string>(&host)->default_value("localhost"), "connection host")
  	("port,p", po::value<unsigned int>(&port)->default_value(9763), "connection port");
  // clang-format on
  /* Parse command line arguments */
  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);
  if(vm.count("help"))
  {
    std::cout << desc << std::endl;
    return 1;
  }

  UdpServer udpServer(host, (uint16_t)port);
  udpServer.printDatagrams(true);

  while(true) XsTime::msleep(10);

  return 0;
}
