#ifndef CLIENT_H
#define CLIENT_H
#include <boost/asio.hpp>


#define MAX_RETRY 5

class Client : public std::enable_shared_from_this<Client>
{
public:
    Client(boost::asio::io_context& io);
    void start(const std::string& host, const std::string& port);
private:
    void do_resolve();
    void do_connect(const boost::asio::ip::tcp::resolver::results_type& endpoints);
    void on_timeout(const boost::system::error_code& ec);
    boost::asio::io_context& io_;
    boost::asio::ip::tcp::resolver resolver_;
    boost::asio::ip::tcp::socket socket_;
    std::string host_;
    std::string port_;
    boost::asio::steady_timer t_;

    int retry_count = 0;
};

#endif // CLIENT_H
