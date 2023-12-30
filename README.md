# sockit

A fancy, schmancy, and slightly quirky socket programming library in C++. This library aims to make dealing with sockets in C++ as delightful as a surprise puppy delivery.

### How to use 🚀
**sockit** is here to make your life easier, just like that one friend who always brings snacks. We've drawn inspiration from JavaScript's `socket.io` framework because, let's face it, it's the cool kid on the block.

*TCP Server*
```cpp
// create a TCP server with a side of charm
int port = 4000;
tcp::server server(port);
server.OnMessage(PrintMessage); // because who doesn't love a good message
server.Listen();
```

*TCP Client*
```cpp
// create a TCP client – because why should servers have all the fun
int     port    = 4000;
string  address = "127.0.0.1";

tcp::client client(address, port);
client.Connect();
client.Send("Hi");
```

In a hurry, try our udp server

*UDP Server*
```cpp
// create a UDP server with a side of charm
int port = 4000;
udp::server server(port);
server.OnMessage(PrintMessage); // because who doesn't love a good message
server.Listen();
```

*UDP Client*
```cpp
// create a UDP client – because why should servers have all the fun
int     port    = 4000;
string  address = "127.0.0.1";

udp::client client(address, port);
client.Connect();
client.Send("Hi");
```

### Contribution 🍰
Feel like adding your flavor to this socket extravaganza? Fork it, clone it, and make it your own. It's like a potluck, but with code.

```bash
git clone https://github.com/harsh11101/sockit.git
```

## Building 🏗️
We've tested our construction skills with `GNU Make 3.81` and `g++ 4.9.2`. To build this masterpiece:

```bash
git clone https://github.com/harsh11101/sockit.git
cd ./sockit/build
make
```

Voila! Find the shiny new library `sockit.so` and binaries for examples in the `dist` directory, right under the library's cozy home.