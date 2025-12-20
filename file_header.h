#ifndef FILE_HEADER_H
#define FILE_HEADER_H
#include <boost/asio.hpp>

#pragma pack(push, 1)
struct file_header {
    // 0. accept 
    // 1. send
    bool flagSendtoAccept;
    uint32_t addr;
    uint16_t port;
    char name[225];
    uint64_t size;
};
#pragma pack(pop)

file_header make_header(bool flag_, boost::asio::ip::address& addr_, int port_, const std::string& name_, int size_file_) {
    file_header fh{};
    fh.flagSendtoAccept = flag_;
    fh.addr = addr_.to_v4().to_uint();
    fh.port = port_;
    std::snprintf(fh.name, sizeof(fh.name), "%s", name_.c_str());
    fh.size = size_file_;
    return fh;
}

#endif // FILE_HEADER_H
                                   