#ifndef FILE_HEADER_H
#define FILE_HEADER_H
#include <boost/asio.hpp>

#pragma pack(push, 1)
struct file_header {
    char name[225];
    uint64_t size;
};
#pragma pack(pop)

#endif // FILE_HEADER_H
