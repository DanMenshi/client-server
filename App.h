#pragma once
#include <boost/asio.hpp>

#include "constant.h"
#include "client.h"

class App {
public:
	App(boost::asio::io_context& io);
	void start();
	void choice();
	void send();
	void accept();
private:
	boost::asio::io_context& io_;
	boost::asio::ip::tcp::socket& socket_;
	Client client_;
};
