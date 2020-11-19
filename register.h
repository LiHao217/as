#pragma once
#include <string>
class _Register
{
public:
	std::string _Register_Name;
	std::string _Register_Machine_Code;
	std::string _Register_type;
};

constexpr auto _Register_Num = 4;

const _Register _Registers[] =
{
	{"r0","00",""},
	{"r1","01",""},
	{"r2","10",""},
	{"r3","11",""},
	
};