#pragma once
#include <string>

constexpr auto _Insn_Jump = "jump";
constexpr auto _Insn_General = "general";
constexpr auto _Insn_Immediate_Count = "immediate_count";
constexpr auto _Insn_Shift = "shift";
constexpr auto _Insn_Nop = "nop";
constexpr auto _Special_Insn = "1110";
class _Opcode
{
public:
	std::string _Insn_Name;
	std::string _Insn_Machine_Code;
	std::string _Insn_type;
};

constexpr auto _Insn_Num = 14;

const _Opcode _Opcodes[] =
{
	{"bne","1","jump"},
	{"lb","0000","general"},
	{"sb","0010","general"},
	{"add","0100","general"},
	{"sub","0110","general"},
	{"xor","1000","general"},
	{"and","1010","general"},
	{"or","1100","general"},
	{"addi","00","immediate_count"},
	{"subi","01","immediate_count"},
	{"srl","10","shift"},
	{"sll","11","shift"},
	{"nop","00000000","nop"},
	{"special_insn","1110","special_insn"},
};