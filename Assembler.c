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
} SymbolTable[20];

struct LiteralTableEntry
{
	char name[20];
	int location;
} LiteralTable[20];

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


int CheckForLabel(char * inst , int n , int stcounter , int lc)
{
	char labelcheck[20];
	int labelflag=0;
	int z=0,i;

	for(i=0;i<n;i++)
		{
			labelcheck[z++]=inst[i];
			if(inst[i]==':')
				{
					labelflag=1;
					break;
				}
		}

	labelcheck[z]='\0';

	if(labelflag==0)
		{
			return -1;
		}
	else
		{
			strcpy(SymbolTable[stcounter].name,labelcheck);
			SymbolTable[stcounter++].location=lc;

			return z;
		}			

}

int InitializeLocationCounter( char * inst , int n )
	{
	    int lc=0,i;
	    int siz = strlen(inst)-1;
	    inst[siz]='\0';
	    int z=0;
	    char startcheck[20];

	    for(i=0;i<strlen(inst)&&inst[i]!=' ';i++)
		{
			startcheck[z++]=inst[i];
		}

	   startcheck[z]='\0';

	   if(strcmp(startcheck , "START")==0)
		{
			z++;
			for(i=z;i<strlen(inst);i++)
				{
					lc*=10;
					lc+=(inst[i]-'0');
				}
			return lc;
	    	}
	   else {
			printf("\n Error : Missing Start Assember Directive ");
			exit(0);
			return -1;
		}
	}


int main()
{

    CreateMotTable();
    CreatePotTable();

    int lc=0 , stcounter=0,j,ltcounter=0;;

    char *inst=NULL;
    int len =20 , i;
    FILE* fp;
    fp = fopen("input.txt" , "r");

    if(fp==NULL)
    {
        printf("\n The required file does not exist");

        return 0;
    }

    // Initializing location counter

    getline(&inst , &len , fp );
    
    lc=InitializeLocationCounter(inst , strlen(inst) );

    

   
   // Iterating through each statement
    while( getline(&inst , &len , fp ) != -1)
    {

        int siz = strlen(inst)-1;
        int isflag=0;
        inst[siz]='\0';	
	int labelflag,z=0;

	// Checking for presence of Label
	labelflag=CheckForLabel(inst , strlen(inst),stcounter,lc);
	
		if(labelflag==-1)
			i=0;
		else
			i=labelflag;
			
	while(inst[i]==' ')
		i++;	


	// Finding OPCODE of Imperative Statement if present
	char is[20];
	for(;i<strlen(inst)&&inst[i]!=' ';i++)
	{
		is[z++]=inst[i];
	}

	is[z]='\0';
        for(j=0;j<11;j++)
        {
            if(strcmp(is , MotTable[j].name)==0)
                {
                    isflag=1;
                    printf("%d ",MotTable[j].opcode);
                    break;
                }


        }

        if(isflag==0)
            {
		// Testing in POT Table		
			for(j=0;j<5;j++)
				{
					if(strcmp(is , PotTable[j].name)==0)
						{
				    			isflag=1;
				   			printf("%d ",PotTable[j].opcode);
				    			break;
						}
				}


			if(

		if(isflag==0)
			{
				printf("\n %s instruction not found in MOT or POT" , is);
				exit(0);
			}

	    }

	
	//Checking for Register

	if(isflag==1)
	{
		char registertype[20];
		int registerflag=0;
		int t=0;
		
		while(inst[i]==' ')
			i++;

		for(;i<strlen(inst)&&inst[i]>='A' && inst[i]<='Z' ;i++)
			{
				registertype[t++]=inst[i];
			}
	
		registertype[t]='\0';

		if(strcmp(registertype,"AREG")==0)
			{ 	registerflag=1;
				printf("1 ");
			}
		else if(strcmp(registertype,"BREG")==0)
			{	registerflag=1;
				printf("2 ");
			}
		else if(strcmp(registertype,"CREG")==0)
			{	registerflag=1;
				printf("3 ");
			}
		else if(strcmp(registertype,"DREG")==0)
			{	registerflag=1;
				printf("4 ");
			}

	}

		
		while(inst[i]==' ' || inst[i]==',')
			i++;

	//Detecting Literal/Symbol

	char LitSym[20];
	int LitSymFlag=0;
	z=0;

	for(;i<strlen(inst)&&inst[i]!=' ';i++)
		{
			LitSym[z++]=inst[i];
		}

	LitSym[z]='\0';

	
	//Checking in Literal Table
	
	if(LitSym[1]=='=')
		{
			for(j=0;j<ltcounter;j++)
				if(strcmp(LiteralTable[j].name,LitSym)==0)
					{
						if(LiteralTable[j].location!=-1)
							{
								printf("%d ",LiteralTable[j].location);
							}
					
						else printf("%s ",LitSym);

						LitSymFlag=1;
					}

			if(LitSymFlag==0)
				{
					strcpy(LiteralTable[ltcounter].name,LitSym);
					LiteralTable[ltcounter].location=-1;
					printf("%s ",LiteralTable[ltcounter++].name);	
				}	
		}
	else
	//Checking in Symbol Table
		{
			for(j=0;j<stcounter;j++)
				if(strcmp(SymbolTable[j].name,LitSym)==0)
					{
						if(SymbolTable[j].location!=-1)
							{
								printf("%d ",LiteralTable[j].location);
							}
					
						else printf("%s ",LitSym);

						LitSymFlag=1;
					}

			if(LitSymFlag==0)
				{
					
					strcpy(SymbolTable[stcounter].name,LitSym);
					SymbolTable[stcounter].location=-1;
					printf("%s ",SymbolTable[stcounter++].name);	
				}
		}

	

//printf("%s",LitSym);
	
		
	
	
	printf("\n");
	lc++;	
    }

    return 0;
}
