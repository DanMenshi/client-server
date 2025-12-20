#include "App.h"
#include "constant.h"

int main() {
    boost::asio::io_context io;
    App app(io);
    app.start();

    io.run();
    return 0;
}
