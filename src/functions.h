#pragma once

#include<string>
#include<vector>
#include<regex>

#include<iostream>


std::vector<std::string> regexSplit(std::string& input, std::string sig, size_t sigRealLen)
{
	std::vector<std::string> svec;
	std::string temp, frontSig, backSig;

	frontSig = ".*" + sig;
	backSig = sig + ".*";

	std::regex rf(frontSig);
	std::regex rb(backSig);
	std::smatch tail;

	size_t tempSize = 0;
	//std::cout << "input: \n" << input << std::endl;
	//std::cout << "sig: \n" << sig << std::endl;
	for(std::sregex_iterator it(input.begin(), input.end(), rf), end_it;
			it != end_it; ++it)
    {
        temp = it->str();
        tempSize = temp.size();
        if(tempSize > sigRealLen)
        {
            temp.resize(tempSize - sigRealLen);
            svec.emplace_back(temp);
            //std::cout << temp;
        }
	}
	/*
	//需要获取最后一次匹配的函数
	std::regex_search(input, tail, rb);
	temp = tail.str();
	tempSize = temp.size();
	if(tempSize > sigRealLen)
	{
        std::string stail = temp.substr(sigRealLen);
        svec.emplace_back(stail);
        std::cout << stail;
	}
	*/

    //std::cout << svec.size() << std::endl;

	return svec;
}

