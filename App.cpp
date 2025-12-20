#include "App.h"
#include <iostream>
#include <chrono>
#include "file_trader.h"

App::App(boost::asio::io_context& io) 
	: io_(io), client_(io_), socket_(io_)
{ }

void App::start() {
	client_.start(HOST, PORT);
	io_.run();
	io_.restart();
	choice();
}

void App::choice() {
	std::cout << "What do you have? (1. send/ 2. accept)\n~ ";
	int input = 0;
	std::cin >> input;

	if (input == 1) {
		send();
	}
	else {
		accept();
	}
	choice();
}

void App::send() {
	

	io_.run();
}