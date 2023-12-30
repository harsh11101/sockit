//==============================================================================================
//= CLASS       : udp_server                                                                     =
//= Description : UDP Server module that creates and manages an instance of a udp udp_server     =
//==============================================================================================

#include "udp_server.hpp"
#include "../net/utils.hpp"
#include "../net/node.hpp"
#include <stdexcept>
#include <iostream>
#include <string>
#include <cstring> // for bzero

using namespace std;

namespace udp {

    // Constructor: Create new udp udp_server instance
    server :: server (int portNumber) {
        //initialize port number and stop udp_server flag
        _port = portNumber;
        _stop_udp_server_flag = 0;

        // initialize the udp_server address struct with zero byte stream
        bzero(&_udp_server_address, sizeof(_udp_server_address));

        _udp_server_address.sin_family = AF_INET;           // IP version not specified. Can be both.
        _udp_server_address.sin_addr.s_addr = htonl(INADDR_ANY); // make udp_server accept all addresses
        _udp_server_address.sin_port = htons(_port);      // Set port number in type [network byte order]

        // initialize socket with [internet addresses, socket stream sequences with default protocol]
        _udp_server_socket_fd = socket( __type_internet_domain_sockets__, __type_datagram_socket__, 0);
    }

    // Start listening at specified port
    int server :: Listen () {
        int accepted_num_of_connections = 100000;

        // bind the address name and port number to the scoket address struct
        int bind_result = bind(_udp_server_socket_fd, (struct sockaddr *)&_udp_server_address, sizeof(_udp_server_address));
        std::cout << "Bind: " << bind_result << std::endl;

        // start listening to the port
        if (bind_result != 0) {
            return -1;
        } else {
            cout << "Start listening at port " << _port << std::endl; // For testing purposes
        }
        int i=0;
        // forever loop for accepting messages
        while (1) {
            if (_stop_udp_server_flag) {
                cout << "Server is stopped !";
                _stop_udp_server_flag = 0;
                break;
            }

            // initialize client address struct
            _client_address_length = sizeof(_client_address);

            // Directly receiving messages from any client
            _message_length = recvfrom(_udp_server_socket_fd, _message, _MSG_BUFFER_SIZE_, 0, (struct sockaddr *)&_client_address, &_client_address_length);

            // skip iteration if no incoming messages
            if (_message_length <= 0) continue;

            // put trailing characters
            _message[_message_length] = 0;
            string msg_str(_message);
            // for(int i=0;i<100;i++){
              respond("200", "Got your message!!"+ std::to_string(i), "Hi - from udp_server");
          i++;
            // }

            // execute OnMessage function if available
            if (_on_msg_fn_ptr != NULL) {
                try {
                    std::string client_ip = inet_ntoa(_client_address.sin_addr);
                    Node* nd = new Node("", client_ip, "");
                    this->_on_msg_fn_ptr(nd, msg_str);
                } catch (std::exception exp) {
                    std::cerr << "failed to execute [OnMessage] function";
                }
            }
        }

        return bind_result;
    }

    // Respond to a client message
    void server :: respond(const std::string& statusCode, const std::string& message, const std::string& response) {
        string fullResponse = "{Status: " + statusCode + "," + "\nMessage: " + message + "," +  "\nResponse: " + response + "}";
        sendto(_udp_server_socket_fd, fullResponse.c_str(), fullResponse.length(), 0, (struct sockaddr*)&_client_address, _client_address_length);
    }

    // Stop udp_server from listening
    void server :: Stop() {
        _stop_udp_server_flag = 1;
    }

    // Assign on message received behavior
    void server :: OnMessage(void (*fptr)(Node*, string)) {
        _on_msg_fn_ptr = fptr;
    }

}
