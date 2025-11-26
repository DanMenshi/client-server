#include "file_trader.h"
#include "file_header.h"
#include <iostream>

file_trader::file_trader(boost::asio::ip::tcp::socket&& socket, const std::string& name)
    : socket_(std::move(socket)),
      name_(name)
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
    max_chunks = size_file_ / buf_.size();
    file_.seekg(0);
    send_meta();
}
file_header file_trader::make_header() {
    file_header fh{};
    std::snprintf(fh.name, sizeof(fh.name), "%s", name_.c_str());
    fh.size = size_file_;
    return fh;
}
void file_trader::send_meta() {
    file_header fh = make_header();

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
    if (count_chunks >= max_chunks / 100 * test) {
        std::cout << test << "%" << std::endl;
        test += 1;
    }

    if (file_.eof()) {
        std::cout << "File sent" << std::endl;
        return;
    }

    file_.read(buf_.data(), buf_.size());
    std::size_t bytes = file_.gcount();

    auto self = shared_from_this();
    boost::asio::async_write(socket_, boost::asio::buffer(buf_.data(), bytes),
    [self] (boost::system::error_code ec, std::size_t) {
        if (!ec) {
            ++self->count_chunks;
            self->send_file();
        }
    });
}

