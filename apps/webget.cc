#include "socket.hh"
#include "util.hh"

#include <cstdlib>
#include <iostream>

using namespace std;

void get_URL(const string &host, const string &path) {
    // Your code here.

    // You will need to connect to the "http" service on
    // the computer whose name is in the "host" string,
    // then request the URL path given in the "path" string.

    // Then you'll need to print out everything the server sends back,
    // (not just one call to read() -- everything) until you reach
    // the "eof" (end of file).
    TCPSocket http_socket;  // 创建套接字
    auto addr_server = Address(host, "http");  // 服务器地址
    http_socket.connect(addr_server);  // 本地套接字连接服务器
    // 通过套接字写入http请求
    http_socket.write("GET " + path + " HTTP/1.1\r\n");
    http_socket.write("Host: " + host + "\r\n");
    http_socket.write("Connection: close\r\n");
    http_socket.write("\r\n");  // 别忘了最后还有一行回车
    // 从socket的文件中读取服务器的返回信息
    while (!http_socket.eof()) {
        cout << http_socket.read();
    }
    http_socket.close();  // 关闭文件
}

int main(int argc, char *argv[]) {
    try {
        if (argc <= 0) {
            abort();  // For sticklers: don't try to access argv[0] if argc <= 0.
        }

        // The program takes two command-line arguments: the hostname and "path" part of the URL.
        // Print the usage message unless there are these two arguments (plus the program name
        // itself, so arg count = 3 in total).
        if (argc != 3) {
            cerr << "Usage: " << argv[0] << " HOST PATH\n";
            cerr << "\tExample: " << argv[0] << " stanford.edu /class/cs144\n";
            return EXIT_FAILURE;
        }

        // Get the command-line arguments.
        const string host = argv[1];
        const string path = argv[2];

        // Call the student-written function.
        get_URL(host, path);
    } catch (const exception &e) {
        cerr << e.what() << "\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
