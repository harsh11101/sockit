//==============================================================================================
//= CLASS       : udp_server                                                                   =
//= Description : UDP Server module that creates and manages an instance of a udp udp_server       =
//==============================================================================================

#ifndef _UDP_SERVER_
#define _UDP_SERVER_

#include <vector>
#include <iostream>
#include <string>
#include <unistd.h>
#include <cstring>      // Needed for memset
#include <sys/socket.h> // Needed for the socket functions
#include <netdb.h>      // Needed for the socket functions
#include <netinet/in.h> // Needed for internet addresses

#include "../net/node.hpp"
#include "../net/utils.hpp"

using std::string;
using std::cout;

namespace udp {
class server{

public:

  // initialize an new udp udp_server instance
  server(int);

  // start listening at specified port
  int Listen();

  // servre On message behavior
  void OnMessage(void (*fptr)(udp::server*,Node*,std::string));

  void respond(const std::string& statusCode, const std::string& message, const std::string& response);


  // stop udp udp_server
  void Stop();

private:

  void (*_on_msg_fn_ptr)(udp::server*, Node*, string) = NULL;

  // address structure for both udp_server and client
  struct sockaddr_in _udp_server_address,_client_address;

  // sockets file discriptors and message length variable
  int    _udp_server_socket_fd , _client_socket_fd, _message_length, _port;

  // socket address length variable
  socklen_t _client_address_length;

  // child proceess id
  pid_t  _childpid;

  // array of characters that represents a message
  char _message[ _MSG_BUFFER_SIZE_ ];

  // ingeter represents a flag of stop udp_server required
  int _stop_udp_server_flag;
};

}
#endif
