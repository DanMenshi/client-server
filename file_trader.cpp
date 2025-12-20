#include "file_trader.h"
#include "file_header.h"
#include <iostream>

file_trader::file_trader(boost::asio::ip::tcp::socket& socket, const std::string& name, const std::string& host, const std::string& port)
    : socket_(std::move(socket)),
      name_(name),
      addr_(boost::asio::ip::make_address(host)),
      port_(std::stoi(port))
{}
void file_trader::start() {
    open_file();
}
void file_trader::open_file() {
    file_.open(name_, std::ios::binary | std::ios::ate);
    if (!file_) {
        std::cerr << "File not open" << std::endl;
        return;
    }
    size_file_ = file_.tellg();
    max_chunks = size_file_ / chunk.size();
    file_.seekg(0);
    send_meta();
}
void file_trader::send_meta() {
    file_header fh = make_header(0, addr_, port_, name_, size_file_);

    auto self = shared_from_this();

    boost::asio::async_write(socket_, boost::asio::buffer(&fh, sizeof(fh)),
        [self] (boost::system::error_code ec, std::size_t) {
            if (!ec) {
                std::cout << "Filename: " << self->name_ << "\nSize(byte): " << self->size_file_ << "\n === sending === " << std::endl;
                self->send_file();
            } else {
                std::cerr << "Fatal send_meta: " << ec.message() << std::endl;
            }
    });
}
void file_trader::send_file() {
    if (count_chunks >= max_chunks / 100 * procent) {
        std::cout << procent << "%" << std::endl;
        procent += 1;
    }

    if (file_.eof()) {
        std::cout << "File sent" << std::endl;
        return;
    }

    file_.read(chunk.data(), chunk.size());
    std::size_t bytes = file_.gcount();

    auto self = shared_from_this();
    boost::asio::async_write(socket_, boost::asio::buffer(chunk.data(), bytes),
    [self] (boost::system::error_code ec, std::size_t) {
        if (!ec) {
            ++self->count_chunks;
            self->send_file();
        }
    });
}

