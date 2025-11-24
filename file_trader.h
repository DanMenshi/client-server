#ifndef FILE_TRADER_H
#define FILE_TRADER_H
#include<boost/asio.hpp>
#include <fstream>

class file_trader : public std::enable_shared_from_this<file_trader>
{
public:
    file_trader(boost::asio::ip::tcp::socket&& socket, const std::string& name);
    void start();
private:
    void open_file();
    void send_file();
    boost::asio::ip::tcp::socket socket_;
    std::ifstream file_;
    const std::string name_;
    std::array<char, 4096> buf_;
    std::size_t count_chunks = 0;
};

#endif // FILE_TRADER_H
