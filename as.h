#pragma once

#include <iostream>
#include"insn.h"
#include"register.h"
#include"as.h"
#include<fstream>
#include<map>
#include<string>
using namespace std;

string _Output_File_Name = "";

constexpr auto _Basic_Block_Begin_Flag = '.';

constexpr auto _Basic_Block_End_Flag = ":";

int _Basic_Block_Address_Begin = 0;

int _Basic_Block_Begin_Flag_Site = 0;

int _Basic_Block_Begin_Flag_Length = 1;

int _Basic_Block_End_Flag_Length = 2;

std::map<std::string , std::string > _Basic_Block;

bool _Basic_Block_List_Completed = false;

constexpr auto _Opcode_Begin_Flag = '\t';

int _Opcode_Address_Begin = 0;

bool _Opcode_Finish = false;

bool _First_Operand_Finish = false;

bool _Second_Operand_Finish = false;