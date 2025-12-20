#ifndef FILE_TRADER_H
#define FILE_TRADER_H
#include <boost/asio.hpp>
#include <fstream>
#include "file_header.h"

class file_trader : public std::enable_shared_from_this<file_trader>
{
public:
    file_trader(boost::asio::ip::tcp::socket& socket, const std::string& name, const std::string& host, const std::string& port);
    void start();
private:
    void open_file();
    void send_meta();
    void send_file();

    boost::asio::ip::address addr_;
    int port_;

    boost::asio::ip::tcp::socket socket_;
    std::ifstream file_;
    uint64_t size_file_;
    const std::string name_;
    
    std::array<char, 2048> chunk;
    
    std::size_t count_chunks = 0;
    std::size_t max_chunks;
    int procent = 1;
};

#endif // FILE_TRADER_H
