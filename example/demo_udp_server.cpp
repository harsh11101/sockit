#include <iostream>
#include "../src/udp/udp_server.hpp"
#include <sstream>

using std::string;
using std::cout;

void print(Node *nd, string msg)
{
  cout<<"printing"<<std::endl;
  cout<< nd->ip <<" : " << msg << std::endl;
}

int main(int argc, char** argv)
{
  //initialize default port number and max connection cout
  int port = 8080;

  // check if there are any passed arguments
  if(argc > 1)
  {
    // initialize string stream from argument
    std::istringstream arg_stream(argv[1]);

    // bind arguments stream to port int variable if valid
    if ( !(arg_stream >> port) )
      std::cerr << "Invalid number " << argv[1] << '\n';
  }

  // create server instance with specified port number
  udp::server server(port);

  // set async fn to handle incoming messages
  server.OnMessage(print);
  // server.respond("200","harry","Hi from server");

  //start listening to connections
  int result = server.Listen();

  if(result != 0)
    cout << "Faild to start server !" << std::endl;

  return 0;
}
