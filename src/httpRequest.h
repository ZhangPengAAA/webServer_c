#pragma once

#include<string>
using std::string;

class httpRequest
{
private:
	string Method;
	string Url;
	string httpType;
public:
    bool isGoodRequest = 1;
public:
    //将http请求报文分解
    httpRequest(){}
	httpRequest(std::string  messageFromSocket);
	string getMethod()
	{
		return Method;
	}
	string getUrl()
	{
		return Url;
	}
	string getHttpType()
	{
		return httpType;
	}
};
