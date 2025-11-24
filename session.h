#pragma once
#include <boost/asio.hpp>
#include <array>

class Session : public std::enable_shared_from_this<Session>
{
public:
    Session(boost::asio::ip::tcp::socket _socket);
    ~Session();
    void start();
private:
    void do_write();
    void do_read();
    std::string write_server();
    std::array<char, 1024> buf;
    boost::asio::ip::tcp::socket socket;
    static inline size_t num_conn = 0;
    std::string name;
};

