#include "client.h"

std::string host = "25.53.195.106";
std::string port = "55555";

int main() {
    boost::asio::io_context io;

    std::make_shared<Client>(io)->start(host, port);

    io.run();
    return 0;
}
