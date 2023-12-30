//=============================================================================================
// CLASS       : udp_client                                                                    =
// Description : UDP Client module that creates and manages an instance of a udp udp_client       =
//=============================================================================================

#ifndef _UDP_CLIENT_HPP_
#define _UDP_CLIENT_HPP_

#include <sys/socket.h> // Needed for the socket functions
#include <netdb.h>      // Needed for the socket functions
#include <netinet/in.h> // Needed for internet addresses
#include "../net/node.hpp"
#include "../net/utils.hpp"

// library specific headers
// #include <net/node.hpp>
// #include <net/utils.hpp>

using namespace std;

namespace udp{
  class client : public Node
  {

  public:

    // initialize a new udp udp_client instance
    client(string, int);

    // connect to host node
    void Connect(void);

    // send message to currently connected host node
    void Send(string);

    // send typed message to currently connected host node
    void Send(string,string);

    // send message to specific connected socket address
    void Send(struct sockaddr*, string);

    // send typed message to specific connected socket address
    void Send(struct sockaddr*,string,string);

    // listen to the response sent by the server
    string ListenToResponse();

    // Stop connection with host
    void Stop();

  private:

    // child proceess id
    pid_t  _childpid;

  };
}
#endif
