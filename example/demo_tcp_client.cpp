#include <iostream>
#include "../src/tcp/tcp_client.hpp"
#include <sstream>
#include <string>
#include <chrono>
#include <thread>


using std::string;

int main(int argc, char** argv)
{

  // initialize default port number and max connection cout
  int     port    = 12002;
  string  address = "127.0.0.1";

  // check if there are any passed arguments
  if(argc == 3)
  {
    // initialize string stream from argument
    std::istringstream arg_stream(argv[1]);

    // bind arguments stream to port int variable if valid
    if ( !(arg_stream >> port) )
      std::cerr << "Invalid number " << argv[1] << '\n';
  }

  // create server instance with specified port number
  tcp::client client(address,port);

  // connect to host node
  client.Connect();

  // send message to host
  for(int i=0;i<100;i++){
    client.Send("Hi! - from client");
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }

  return 0;
}
