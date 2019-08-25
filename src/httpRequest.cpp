#include"httpRequest.h"
#include"functions.h"
#include<stdlib.h>
#include<regex>


/*
#include<iostream>
#include<fstream>
#include<unistd.h>
#include<fcntl.h>
*/

httpRequest::httpRequest(std::string  messageFromSocket)
{
    //std::cout<< 1<< std::endl;
    std::vector<std::string> total, MeUrTy;
    //std::string CRLF("\r\n"),SPACE(".* ");
    std::string requestLine;

    messageFromSocket += "\r\n";
    total = regexSplit(messageFromSocket, "\\r\\n", 2);
    //std::cout << total.size() << std::endl;
    //std::cout << total[0] << std::endl;

    //std::cout << "vector.size = " << total.size() << std::endl;
    total[0] += " ";
    //std::cout << total[0] << "s";
    //requestLine = total[0];
    //std::cout << 3 << std::endl;
    //std::string sss = " ";
    std::regex rrr(" ");
    requestLine = std::regex_replace(total[0], rrr, "\n");
    //std::cout << requestLine;
    MeUrTy = regexSplit(requestLine, "\\n", 1);
    //std::cout << MeUrTy.size() << std::endl;

    if(total.size() < 3)
        isGoodRequest = 0;
    else{
        Method = MeUrTy[0];
        Url = MeUrTy[1];
        httpType = MeUrTy[2];
    }
    //std::cout << Method << "\n" << Url << "\n"
     //           << httpType << std::endl;
}

/*
int main()
{
    std::string s("abcdefg\r\n");
    std::cout << s;
    char buf[200];
    int fd = open("requestFile",O_RDONLY);
    read(fd, buf, 200);
    std::string str("POST /user HTTP/1.1\r\nHost: www.user.com\r\nContent-Type: application/x-www-form-urlencoded\r\nConnection: Keep-Alive\r\nUser-agent: Mozilla/5.0.\r\n\r\nname=world");
    //std::cout << str << std::endl;
    httpRequest Request(str);
    std::cout << Request.getMethod() << "\n" << Request.getUrl() << "\n"
                << Request.getHttpType() << std::endl;

    return 0;
}
*/
