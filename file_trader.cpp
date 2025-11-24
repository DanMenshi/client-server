#include "file_trader.h"
#include <iostream>

file_trader::file_trader(boost::asio::ip::tcp::socket&& socket, const std::string& name)
    : socket_(std::move(socket)),
      name_(name)
{}
void file_trader::start() {
    open_file();
}
void file_trader::open_file() {
    file_.open(name_, std::ios::binary);
    if (!file_) {
        std::cerr << "File not open" << std::endl;
        return;
    }
    send_file();
}
void file_trader::send_file() {
    if (file_.eof()) {
        std::cout << "File sent" << std::endl;
        return;
    }

    file_.read(buf_.data(), buf_.size());
    std::size_t bytes = file_.gcount();

    auto self = shared_from_this();
    boost::asio::async_write(socket_, boost::asio::buffer(buf_.data(), bytes),
    [self] (boost::system::error_code ec, std::size_t n) {
        if (!ec) {
            std::cout << "Count chunks: " << ++self->count_chunks << std::endl;
            self->send_file();
        }
    });
}

