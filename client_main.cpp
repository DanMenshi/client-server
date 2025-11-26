#include "client.h"
#include "constant.h"

int main() {
    boost::asio::io_context io;

    std::make_shared<Client>(io)->start(HOST, PORT);

    io.run();
    return 0;
}
