#include "session.h"
#include <iostream>


using boost::asio::ip::tcp;

Session::Session(tcp::socket _socket)
    :   socket(std::move(_socket))
{
    name.append(std::to_string(socket.remote_endpoint().port()));
}
Session::~Session() {
    --num_conn;
    std::cout << name << " : close connected!" << std::endl;
}
void Session::start() {
    do_read();
    ++num_conn;
}
void Session::do_read()
{
    auto self = shared_from_this();
    socket.async_read_some(boost::asio::buffer(buf),
       [self] (boost::system::error_code ec, std::size_t bytes) {
            if (!ec) {
                std::cout << self->name << " : " << std::string(self->buf.data(), bytes - 1) << std::endl;
                std::cout << "Number clients: " << num_conn << std::endl;
                self->do_write();
            }
       });
}
void Session::do_write()
{
    auto self = shared_from_this();
    socket.async_write_some(boost::asio::buffer("Hello client!\n"),
        [self] (boost::system::error_code ec, std::size_t len_buf) {
            if (!ec) {
                self->do_read();
            }
        });
}
