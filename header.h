#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct MotTableEntry
{
    int opcode ;
    char name[30];
    int sizeofinst;

} MotTable[20];


struct PotTableEntry
{
	char name[30];
} PotTable[20];

struct SymbolTableEntry
{
	char name[20];
	int location;
	int value;
} SymbolTable[20];

struct LiteralTableEntry
{
	char name[20];
	int location;
} LiteralTable[20];

struct PoolTableEntry
{
	int batch;
} PoolTable[10];

void CreateMotTable()
{
	    MotTable[0].opcode = 0;
	    strcpy(MotTable[0].name,"STOP");
	    MotTable[0].sizeofinst=1;

	    MotTable[1].opcode = 1;
	    strcpy(MotTable[1].name,"ADD");
	    MotTable[1].sizeofinst=1;

	    MotTable[2].opcode = 2;
	    strcpy(MotTable[2].name,"SUB");
	    MotTable[2].sizeofinst=1;

	    MotTable[3].opcode = 3;
	    strcpy(MotTable[3].name,"MULT");
	    MotTable[3].sizeofinst=1;

	    MotTable[4].opcode = 4;
	    strcpy(MotTable[4].name,"MOVER");
	    MotTable[4].sizeofinst=1;

	    MotTable[5].opcode = 5;
	    strcpy(MotTable[5].name,"MOVEM");
	    MotTable[5].sizeofinst=1;

	    MotTable[6].opcode = 6;
	    strcpy(MotTable[6].name,"COMP");
            MotTable[6].sizeofinst=1;

	    MotTable[7].opcode = 7;
	    strcpy(MotTable[7].name,"BC");
            MotTable[7].sizeofinst=1;

	    MotTable[8].opcode = 8;
	    strcpy(MotTable[8].name,"DIV");
            MotTable[8].sizeofinst=1;

	    MotTable[9].opcode = 9;
	    strcpy(MotTable[9].name,"READ");
            MotTable[9].sizeofinst=1;

	    MotTable[10].opcode = 10;
	    strcpy(MotTable[10].name,"PRINT");
	    MotTable[10].sizeofinst=1;

}

void CreatePotTable()
{
	strcpy(PotTable[0].name,"START");
	strcpy(PotTable[1].name,"ORIGIN");
	strcpy(PotTable[2].name,"END");
	strcpy(PotTable[3].name,"EQU");
	strcpy(PotTable[4].name,"LTORG");

}

