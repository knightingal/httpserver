__author__ = 'knightingal'

import urllib2

if __name__ == "__main__":
    request = urllib2.Request("http://127.0.0.1:8081/index")
    request.add_header(
        "User-Agent",
        "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.31 "
        "(KHTML, like Gecko) Chrome/26.0.1410.63 Safari/537.31"
    )
    request.add_header("Connection", "keep-alive")
    request.add_header("Accept", "*/*")
    request.add_header("Accept-Encoding", "gzip,deflate,sdch")
    request.add_header("Accept-Language", "zh-CN,zh;q=0.8")
    request.add_header("Accept-Charset", "GBK,utf-8;q=0.7,*;q=0.3")

    request.add_data("hello, my name is Knightingal")
    fd = urllib2.urlopen(request)
    net_string = fd.read()
    fd.close()
    print net_string
