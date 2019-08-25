#include"httpResponse.h"
#include<fstream>
#include<fcntl.h>
#include<unistd.h>
#include<cstring>
/*
#include<unistd.h>
#include<iostream>
*/
void httpResponse::writeBody(char * filename){
    int n;
	body = filename;
	char buf[12];
	int openfd = open(body, O_RDONLY);
    while((n = read(openfd, buf, 12)) > 0)
    {
        response = response + std::string(buf);
        memset(buf, '\0', strlen(buf));
    }
}

void httpResponse::writeStatusLine(string hType, string stat, string statDescription)
{
	this->httpType = hType;
	this->status = stat;
	this->statusDescription = statDescription;
}

void httpResponse::writeHeadLines(string contentType)
{
	headLines.push_back(contentType);
}

string httpResponse::getResponseHead()
{
	std::string response;

	response = httpType + " " + status + " " + statusDescription + "\r\n";
	for(auto& x : headLines)
        response = response + x + "\r\n";
    response = response + "\r\n" + "\r\n";// + body;

	return response;
}

char*  httpResponse::getBody()
{
    return body;
}

/*
int main()
{
    httpResponse Response;
    Response.writeStatusLine("HTTP/1.1","200","OK");
    Response.writeHeadLines("a;sdlkfa;wkf");
    Response.writeHeadLines("a;sdjkfaj;sdklfj;adkf;aklf");
    Response.writeHeadLines("aaa");
    Response.writeBody("requestFile");

    std::cout << Response.getResponseHead();
    write(1, Response.getBody(), 1000);

}
*/
