#include "client.h"
#include "file_trader.h"
#include <iostream>

Client::Client(boost::asio::io_context& io)
    : resolver_(io),
      socket_(io),
      io_(io),
      t_(io)
{ }
void Client::start(const std::string& host, const std::string& port)
{
    host_ = host;
    port_ = port;
    retry_count = 0;
    do_resolve();
}
void Client::do_resolve()
{
    auto self = shared_from_this();

    resolver_.async_resolve(host_, port_,
        [self] (boost::system::error_code ec, auto results) {
        if (!ec) {
            self->retry_count = 0;
            self->do_connect(results);
        } else {
            ++self->retry_count;
            if (self->retry_count < MAX_RETRY) self->do_resolve();
            else std::cerr << "Fatal[" << self->retry_count << "] async_resolve: " << ec.message() << std::endl;
        }
    });
}
void Client::do_connect(const boost::asio::ip::tcp::resolver::results_type& endpoints) {
    auto self = shared_from_this();

    t_.expires_after(std::chrono::seconds{5});
    t_.async_wait([self](auto ec){ self->on_timeout(ec); });

    boost::asio::async_connect(socket_, endpoints,
        [self, endpoints] (boost::system::error_code ec, boost::asio::ip::tcp::endpoint endpoint) {
            self->t_.cancel();

            if (!ec) {
                std::cout << "Connected to: " << endpoint.address().to_string() << ":" << endpoint.port() << std::endl;
                self->retry_count = 0;

                // govno;
                std::make_shared<file_trader>(std::move(self->socket_), "file.txt")->start();

            } else {
                ++self->retry_count;
                if (self->retry_count < MAX_RETRY) {
                    self->socket_ = boost::asio::ip::tcp::socket(self->io_);
                    self->do_resolve();
                }
                else {
                    std::cerr << "Fatal[" << self->retry_count << "] async_connect: " << ec.message() << std::endl;
                }
            }
    });
}
void Client::on_timeout(const boost::system::error_code& ec) {
    if (ec == boost::asio::error::operation_aborted) {
        return;
    }

    std::cerr << "connect close! " << std::endl;
    return;
}
