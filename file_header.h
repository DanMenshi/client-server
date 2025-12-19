#ifndef FILE_HEADER_H
#define FILE_HEADER_H
#include <boost/asio.hpp>

#pragma pack(push, 1)
struct file_header {
    bool flagSendtoAccept;
    // 0. accept 
    // 1. send 
    boost::asio::ip::address addr;
    uint16_t port;
    char name[225];
    uint64_t size;
};
#pragma pack(pop)

#endif // FILE_HEADER_H
