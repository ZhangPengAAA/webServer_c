#pragma once

#include<string>
#include<vector>
using std::string;


class httpResponse
{
private:
	string httpType;
	string status;
	string statusDescription;


	bool isGoodRequest = 1;

	std::vector<string> headLines;
	char* body;
	//unsigned char body[];
public:
    string response;
public:
	void writeBody(char * filename);
	void writeStatusLine(string hType, string stat, string statDescription);
	void writeHeadLines(string contentType);

	string getResponseHead();
	char* getBody();
};
