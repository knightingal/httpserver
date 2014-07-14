__author__ = 'knightingal'

import socket

if __name__ == "__main__":
    HOST = '127.0.0.1'    # The remote host
    PORT = 8081              # The same port as used by the server
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((HOST, PORT))
    s.sendall(
        "POST /index HTTP/1.1\r\n" +
        "Content-Length: 5\r\n" +
        "Accept-Language: zh-CN,zh;q=0.8\r\n" +
        "Accept-Encoding: gzip,deflate,sdch\r\n" +
        "Host: 127.0.0.1:8081\r\n" +
        "Accept: */*\r\n" +
        "User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.31 " +
        "(KHTML, like Gecko) Chrome/26.0.1410.63 Safari/537.31\r\n" +
        "Accept-Charset: GBK,utf-8;q=0.7,*;q=0.3\r\n" +
        "Connection: close\r\n" +
        "Content-Type: application/x-www-form-urlencoded\r\n" +
        "\r\n" +
        "hello\r\n"
    )
    data = s.recv(1024)
    s.close()
    print data
