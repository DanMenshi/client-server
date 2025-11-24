#include <iostream>
#include <boost/asio.hpp>
#include "session.h"

using boost::asio::ip::tcp;


void do_accept(boost::asio::io_context& io , tcp::acceptor& acceptor) {
    auto socket = std::make_shared<tcp::socket>(io);
    acceptor.async_accept(*socket,
        [socket, &acceptor, &io](boost::system::error_code ec) {
            if (!ec) {
                std::make_shared<Session>(std::move(*socket))->start();
            } else {
                std::cout << "Error: " << ec.what() << std::endl;
            }
            do_accept(io, acceptor);
       });
}

int main() {
    try {
        boost::asio::io_context io;
        tcp::acceptor acceptor(io, {tcp::v4(), 55555});

        do_accept(io, acceptor);
        io.run();
    } catch (std::exception& e) {
        std::cerr << "ex: " << e.what() << std::endl;
    }

    return 0;
}
