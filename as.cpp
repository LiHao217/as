///home/yxj/gcc-8.2.0-exe/bin/g++ -O2 as.cpp as.h insn.h register.h   -o lhas
#include <iostream>
#include "insn.h"
#include "register.h"
#include "as.h"
#include <fstream>
#include <bitset>

using namespace std;
const int N = 300;
bool debug = false;
void _Execute_Shell_Command(string _Compiler_Option);
void _Line_In_Input_File_Paser(string _Line_In_Input_File, string _Output_File_Name);
void _Create_Basic_Block_List(string _Line_In_Input_File);
void _Analysis_Opcodeand_Operand(string _Line_In_Input_File);
void _Assembly_Code_2_Binary_Code(string _Opcode_Name, string _First_Operand, string _Seond_Operand);
void _Binary_Code_2_Output_File(
    string _Opcode_Binary_Code,
    string _Opcode_Type,
    string _First_Operand_Binary_Code,
    string _Seond_Operand_Binary_Code);
int main(int argc, char *argv[])
{
    string _Input_File_Name = "";
    _Output_File_Name = "";
    //get input file name
    for (int i = 1; i < argc; i++)
    {
        string _argv = argv[i];
        if (_argv.find(".s") != -1)
        {
            _Input_File_Name = argv[i];
        }
        if (_argv.find("-g") != -1)
        {
            debug = true;
        }
    }
    string _Input_File_Name_tmp = _Input_File_Name;
    _Output_File_Name = _Input_File_Name_tmp.replace(_Input_File_Name.find(".s"), 2, ".bin");
    _Execute_Shell_Command("rm " + _Output_File_Name);
    string _Line_In_Input_File = "";

    //Create basic block list
    ifstream _Input_File_Stream(_Input_File_Name);
    if (!_Input_File_Stream)
    {
        cout << "as open input file fail!" << endl;
        return 1;
    }
    else
    {
        cout << "as open input file success" << endl;
    }

    while (getline(_Input_File_Stream, _Line_In_Input_File))
    {
        _Line_In_Input_File_Paser(_Line_In_Input_File, _Output_File_Name);
    }
    _Basic_Block_List_Completed = true;
    _Input_File_Stream.close();

    //analysis the opcode and operand
    ifstream _Input_File_Stream_For_Opcode(_Input_File_Name);
    if (!_Input_File_Stream_For_Opcode)
    {
        cout << "as open output file fail!" << endl;
        return 1;
    }
    else
    {
        cout << "as open input file success" << endl;
    }
    while (getline(_Input_File_Stream_For_Opcode, _Line_In_Input_File))
    {
        _Line_In_Input_File_Paser(_Line_In_Input_File, _Output_File_Name);
    }
    _Input_File_Stream_For_Opcode.close();
    //Output the final executable code to a binary file
    string _Output_File_Name_Temp = _Output_File_Name;
    string _Binary_Output_File_Name = _Output_File_Name_Temp.erase(_Output_File_Name.find("_as"));
    _Execute_Shell_Command(_Binary_Output_File_Name);
    string _Line_In_Input_File_Stream_For_Debug_Output_File = "";
    ifstream _Input_File_Stream_For_Debug_Output_File(_Output_File_Name);
    while (getline(_Input_File_Stream_For_Debug_Output_File, _Line_In_Input_File_Stream_For_Debug_Output_File))
    {
        string _Output_Binary_File_Option = "echo " + _Line_In_Input_File_Stream_For_Debug_Output_File + " | xxd -r -ps >> " + _Binary_Output_File_Name;
        _Execute_Shell_Command(_Output_Binary_File_Option);
    }
    _Input_File_Stream_For_Debug_Output_File.close();
    cout << "Compilation completed" << endl;
}

void _Line_In_Input_File_Paser(string _Line_In_Input_File, string _Output_File_Name)
{
    //find a basic block
    if (!_Basic_Block_List_Completed)
    {
        if (_Line_In_Input_File[_Basic_Block_Begin_Flag_Site] == _Basic_Block_Begin_Flag)
        {
            _Create_Basic_Block_List(_Line_In_Input_File);
        }
    }
    //find a opcode ,
    /*The list of basic blocks has been established, so when we encounter a basic block, 
    we directly output the binary code.*/
    if (_Basic_Block_List_Completed && _Line_In_Input_File[_Opcode_Address_Begin] == _Opcode_Begin_Flag || _Line_In_Input_File[_Basic_Block_Begin_Flag_Site] == _Basic_Block_Begin_Flag)
    {
        _Analysis_Opcodeand_Operand(_Line_In_Input_File);
    }
}

//analysis the opcode and operand
void _Analysis_Opcodeand_Operand(string _Line_In_Input_File)
{
    string _Opcode_Name = "";
    string _First_Operand = "";
    string _Seond_Operand = "";
    _Opcode_Finish = false;
    _First_Operand_Finish = false;
    _Second_Operand_Finish = false;
    if (_Line_In_Input_File[_Opcode_Address_Begin] == _Opcode_Begin_Flag)
    {
        for (int i = 1; i < _Line_In_Input_File.size(); ++i)
        {
            //get opcode
            if (!_Opcode_Finish && _Line_In_Input_File[i] == '\t')
            {
                _Opcode_Finish = true;
                continue;
            }
            else if (!_Opcode_Finish && _Line_In_Input_File[i] != '\t')
            {
                _Opcode_Name += _Line_In_Input_File[i];
                continue;
            }
            //get first operand
            if (!_First_Operand_Finish && _Line_In_Input_File[i] == ',')
            {
                _First_Operand_Finish = true;
                continue;
            }
            else if (!_First_Operand_Finish && _Line_In_Input_File[i] != '\t')
            {
                _First_Operand += _Line_In_Input_File[i];
                continue;
            }
            //get second operand
            if (!_Second_Operand_Finish && _Line_In_Input_File[i] != '\t')
            {
                _Seond_Operand += _Line_In_Input_File[i];
            }
        }
    }
    else if (_Line_In_Input_File[_Basic_Block_Begin_Flag_Site] == _Basic_Block_Begin_Flag)
    {
        ofstream _Output_File_Stream_For__Basic_Block(_Output_File_Name, ios::app);
        string _Basic_Block_Name = _Line_In_Input_File.erase(_Basic_Block_Begin_Flag_Site, _Basic_Block_Begin_Flag_Length);
        int _Basic_Block_End_Flag_Site = _Line_In_Input_File.find(_Basic_Block_End_Flag);
        _Basic_Block_Name = _Line_In_Input_File.erase(_Basic_Block_End_Flag_Site - 1, _Basic_Block_End_Flag_Length);
        map<string, string>::iterator iter;
        iter = _Basic_Block.find(_Basic_Block_Name);
        if (iter != _Basic_Block.end())
        {
            _Output_File_Stream_For__Basic_Block << iter->second;
        }

        _Output_File_Stream_For__Basic_Block.close();
    }
    /* Start converting assembly code to binary code*/
    _Assembly_Code_2_Binary_Code(
        _Opcode_Name,
        _First_Operand,
        _Seond_Operand);
    ofstream _Output_File_Stream_For_Debug(_Output_File_Name, ios::app);
    if (debug)
    {
        _Output_File_Stream_For_Debug << _Line_In_Input_File << "\n";
    }
    _Output_File_Stream_For_Debug.close();
}
/* converting assembly code to binary code*/
void _Assembly_Code_2_Binary_Code(
    string _Opcode_Name,
    string _First_Operand,
    string _Seond_Operand)
{
    string _Opcode_Binary_Code = "";
    string _Opcode_Type = "";
    string _First_Operand_Binary_Code = "";
    string _Seond_Operand_Binary_Code = "";
    for (int i = 0; i < _Insn_Num; ++i)
    {
        if (_Opcodes[i]._Insn_Name == _Opcode_Name)
        {
            _Opcode_Binary_Code = _Opcodes[i]._Insn_Machine_Code;
            _Opcode_Type = _Opcodes[i]._Insn_type;
        }
    }
    for (int i = 0; i < _Register_Num; ++i)
    {
        if (_Registers[i]._Register_Name == _First_Operand)
        {
            _First_Operand_Binary_Code = _Registers[i]._Register_Machine_Code;
        }
        if (_Registers[i]._Register_Name == _Seond_Operand)
        {
            _Seond_Operand_Binary_Code = _Registers[i]._Register_Machine_Code;
        }
    }
    /*Start with the binary code and output to a file*/
    if (_Opcode_Type == _Insn_Jump)
    {
        map<string, string>::iterator iter;
        iter = _Basic_Block.find(_First_Operand);
        if (iter != _Basic_Block.end())
        {
            _First_Operand_Binary_Code = iter->second;
        }

        _Binary_Code_2_Output_File(
            _Opcode_Binary_Code,
            _Opcode_Type,
            _First_Operand_Binary_Code,
            _Seond_Operand_Binary_Code);
    }
    else if (_Opcode_Type == _Insn_Immediate_Count)
    {
        _Seond_Operand_Binary_Code = bitset<2>(_Seond_Operand[0]).to_string();
        _Binary_Code_2_Output_File(
            _Opcode_Binary_Code,
            _Opcode_Type,
            _First_Operand_Binary_Code,
            _Seond_Operand_Binary_Code);
    }
    else
    {
        _Binary_Code_2_Output_File(
            _Opcode_Binary_Code,
            _Opcode_Type,
            _First_Operand_Binary_Code,
            _Seond_Operand_Binary_Code);
    }
}

void _Binary_Code_2_Output_File(
    string _Opcode_Binary_Code,
    string _Opcode_Type,
    string _First_Operand_Binary_Code,
    string _Seond_Operand_Binary_Code)
{
    //Output the final executable code to a text file
    string _Debug_Output_File_Name = _Output_File_Name;
    ofstream _Debug_Output_File_Stream_For_Opcode(_Debug_Output_File_Name, ios::app);
    if (_Opcode_Type == _Insn_General)
    {
        _Debug_Output_File_Stream_For_Opcode << _Seond_Operand_Binary_Code;
        _Debug_Output_File_Stream_For_Opcode << _First_Operand_Binary_Code;
        _Debug_Output_File_Stream_For_Opcode << _Opcode_Binary_Code;
        _Debug_Output_File_Stream_For_Opcode << "\n";
    }
    if (_Opcode_Type == _Insn_Immediate_Count)
    {
        _Debug_Output_File_Stream_For_Opcode << _Opcode_Binary_Code;
        _Debug_Output_File_Stream_For_Opcode << _Seond_Operand_Binary_Code;
        _Debug_Output_File_Stream_For_Opcode << _Special_Insn;
        _Debug_Output_File_Stream_For_Opcode << "\n";
    }
    if (_Opcode_Type == _Insn_Nop)
    {
        _Debug_Output_File_Stream_For_Opcode << _Opcode_Binary_Code;
        _Debug_Output_File_Stream_For_Opcode << "\n";
    }
    if (_Opcode_Type == _Insn_Shift)
    {
        _Debug_Output_File_Stream_For_Opcode << _Opcode_Binary_Code;
        _Debug_Output_File_Stream_For_Opcode << _First_Operand_Binary_Code;
        _Debug_Output_File_Stream_For_Opcode << _Special_Insn;
        _Debug_Output_File_Stream_For_Opcode << "\n";
    }
    if (_Opcode_Type == _Insn_Jump)
    {
        _Debug_Output_File_Stream_For_Opcode << _First_Operand_Binary_Code;
        _Debug_Output_File_Stream_For_Opcode << _Opcode_Binary_Code;
        _Debug_Output_File_Stream_For_Opcode << "\n";
    }
    _Debug_Output_File_Stream_For_Opcode.close();
}
//Analysis and Create basic block list
void _Create_Basic_Block_List(string _Line_In_Input_File)
{
    string _Basic_Block_Address = bitset<7>(++_Basic_Block_Address_Begin).to_string();

    string _Basic_Block_Name = _Line_In_Input_File.erase(_Basic_Block_Begin_Flag_Site, _Basic_Block_Begin_Flag_Length);

    int _Basic_Block_End_Flag_Site = _Line_In_Input_File.find(_Basic_Block_End_Flag);

    _Basic_Block_Name = _Line_In_Input_File.erase(_Basic_Block_End_Flag_Site - 1, _Basic_Block_End_Flag_Length);

    _Basic_Block.insert(pair<string, string>(_Basic_Block_Name, _Basic_Block_Address));
}

void _Execute_Shell_Command(string _Compiler_Option)
{
    char line[N];
    FILE *fp;
    string cmd = _Compiler_Option;
    //cout << cmd << endl;
    const char *sysCommand = cmd.data();
    if ((fp = popen(sysCommand, "r")) == NULL)
    {
        cout << "error" << endl;
        return;
    }
    while (fgets(line, sizeof(line) - 1, fp) != NULL)
    {
        cout << line;
    }
    pclose(fp);
}