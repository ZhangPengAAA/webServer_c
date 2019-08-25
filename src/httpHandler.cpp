#include"httpHandler.h"
#include"httpRequest.h"
#include"httpResponse.h"
#include<string>
#include<iostream>
#include<unistd.h>
#include<sys/sendfile.h>
#include<fcntl.h>


void requestHandler(char buf[], int ss, int connfd)
{
    std::string message(buf);
    std::cout << "message: " << message << std::endl;
    httpRequest Request(message);
    if(!Request.isGoodRequest)
        return;
    if(Request.getMethod()  == "GET")
    {
        std::string htmlToClient;
        std::cout << "method: " << Request.getMethod() << std::endl;
        std::cout << "url: " << Request.getUrl() << std::endl;
        std::cout << "httpType: " << Request.getHttpType() << std::endl;

        httpResponse Response;
        //char file[] = "test.html";
        std::cout << "response created\n";
        //Response.writeBody(file);
        //std::cout << "body finished\n";
        Response.writeStatusLine("HTTP/1.1","404","NOT FOUND");
        Response.writeHeadLines("Date: Sat, 31 Dec 2006 22:22:22 GMT");
        Response.writeHeadLines("Content-Type: text/html");
        htmlToClient = Response.getResponseHead() + Response.response;
        std::cout << "write begin" << "\n";
        write(connfd, htmlToClient.data(), htmlToClient.size());
        int fd = open("test.html", O_RDONLY);
        sendfile(connfd, fd, nullptr, 20000);
    }
}

