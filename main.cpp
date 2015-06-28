#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <algorithm>
double stack[256];
double memory[65000];
typedef bool flag;
std::vector<std::string> program;
std::vector<std::string> ppc;
enum {A,B,C,D,NumberOfRegisters};
double registers[NumberOfRegisters];
int IP = 0;
int MEMPTR = 0;
int ppcPTR = 0;
flag compare = false;
bool dataEnd = false;
bool noStatementHit = true;
void eval(std::string ins);
void evalPPC(std::string ins);
void printRegisters();
void printFlags();
void syntaxCheck();
std::vector<std::string> statements
{
	".DATAEND",
	".dd"
};


bool in_quote(const std::string& s)
{
	for (auto it : statements)
	{
		
		if(s == it)
			return true;
	}
	return false;
}

int main()
{



	std::filebuf pfb;


	if (pfb.open("I:\\dev\\visual studio\\virtual-machine\\prog.txt", std::ios::in))
	{
		std::istream mem(&pfb);

		std::string help = "";
		while (1)
		{
			mem >> help;
			ppc.push_back(help);

			if (help == ".DATAEND")
				break;
		}
		pfb.close();
	}




	if (pfb.open("I:\\dev\\visual studio\\virtual-machine\\prog.txt", std::ios::in))
	{
		std::istream prog(&pfb);

		std::string help = "";
		while (1)
		{
			prog >> help;
			
			if (dataEnd == true)
			{
				program.push_back(help);
			}
			if (help == ".DATAEND")
				dataEnd = true;
			if (help == ".END")
				break;
		}


		pfb.close();

	}
	else
	{
		std::cout << "DATEI NICHT GEFUNDEN" << std::endl;
	}

	//Syntaxcheck
	syntaxCheck();
	while (1)
	{
 		evalPPC(ppc[ppcPTR]);
		++ppcPTR;
		if (ppc[ppcPTR-1] == ".DATAEND")
		{
			break;
		}
	}
	while (program[IP] != ".END")
	{

		eval(program[IP]);

		++IP;
	}

	system("PAUSE");
	return 0;
}

void eval(std::string ins)
{
	if (ins == "LDA")
	{
		registers[A] = std::stoi(program[++IP]);
	}
	if (ins == "LDB")
	{
		registers[B] = std::stoi(program[++IP]);
	}
	if (ins == "LDC")
	{
		registers[C] = std::stoi(program[++IP]);
	}
	if (ins == "LDD")
	{
		registers[D] = std::stoi(program[++IP]);
	}
	else if (ins == "ADD")
	{
		registers[A] += std::stoi(program[++IP]);
	}
	else if (ins == "SUB")
	{
		registers[A] -= std::stoi(program[++IP]);
	}
	else if(ins == "CMP")
	{
		if (registers[A] == std::stoi(program[++IP]))
			compare = true;
		else
			compare = false;
	}
	else if(ins == "HLT")
	{
		getchar();
		exit(1);
		
	}
	else if(ins == "JMP")
	{
		std::string label = program[++IP];
		int jumpAddres = 0;
		for (size_t i = 0; i < program.size(); i++)
		{

			if (program[i] == label && program[i - 1] != "JMP" && program[i - 1] != "JNQ " && program[i - 1] != "JEQ" )
			{
				
				
				IP = i;

				break;
			}
		}
	}
	else if(ins == "JEQ")
	{
		std::string label = program[++IP];
		int jumpAddres = 0;
		for (size_t i = 0; i < program.size(); i++)
		{

			if ((program[i] == label && program[i - 1] != "JMP"  && program[i - 1] != "JNQ " && program[i - 1] != "JEQ") && compare == 1)
			{
				

				IP = i;

				break;
			}
		}
	}
	else if(ins == "JNQ")
	{
		std::string label = program[++IP];
		int jumpAddres = 0;
		for (size_t i = 0; i < program.size(); i++)
		{

			if ((program[i] == label && program[i - 1] != "JMP"  && program[i - 1] != "JNQ " && program[i - 1] != "JEQ" ) && compare != 1)
			{


				IP = i;

				break;
			}
		}
	}
	printRegisters();
	printFlags();
}


void evalPPC(std::string ins)
{

	if (ins == ".data")
	{
		MEMPTR = std::stoi(ppc[++ppcPTR]);

	}
	if (ins == ".dd")
	{
		/*
		std::cout << "CALL" << ppcPTR << std::endl;
		while (noStatementHit)
		{

			++ppcPTR;
			if (in_quote(ppc[ppcPTR]))
			{
				noStatementHit = false;
				memory[MEMPTR++] = std::stoi(ppc[++ppcPTR]);
				break;

			}
			memory[MEMPTR++] = std::stoi(ppc[ppcPTR]);
		
		}
	
		8*/
	}
	if (ins == ".DATAEND")
	{
		return;
	}
	
}


void printRegisters()
{
	char help = 'A';
	std::cout << "IP " << IP << std::endl;
	std::cout << "---------REGS---------" << std::endl;
	for (size_t i = 0; i < NumberOfRegisters; i++)
	{
		
		std::cout << help <<" "<< registers[i] << std::endl;
		help++;
	}
	std::cout << "------------------" << std::endl;
	
}
void printFlags()
{
	std::cout << "---------FLAGS----" << std::endl;
	std::cout << "CMP " << compare << std::endl;
	std::cout << "------------------" << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
}



void syntaxCheck()
{
	int ctr = 0;
	int ctr2 = 0;
	while (1)
	{

		
		++ctr;
		if (ppc[ctr - 1] == ".DATAEND")
		{
			break;
		}
	}
	while (program[ctr2] != ".END")
	{

		

		++ctr2;
	}
	
}