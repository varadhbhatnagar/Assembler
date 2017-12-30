//Made by Varad Bhatnagar

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


int CheckForLabel(char * inst , int n , int *stcounter , int lc)
{
	char labelcheck[20];
	int labelflag=0;
	int z=0,i;

	for(i=0;i<n;i++)
		{
			labelcheck[z++]=inst[i];
			if(inst[i+1]==':')
				{
					labelflag=1;
					break;
				}
		}

	labelcheck[z]='\0';

	for(i=0;i<*stcounter;i++)
		{
			if(strcmp(SymbolTable[i].name,labelcheck)==0)
				{	
					SymbolTable[i].location=lc;
					return z;
				}
		}

	if(labelflag==0)
		{
			return -1;
		}
	else
		{
			strcpy(SymbolTable[*stcounter].name,labelcheck);
			SymbolTable[*stcounter].location=lc;
			(*stcounter)++;
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

    PoolTable[0].batch=0;

    int lc=0 , stcounter=0,j,ltcounter=0,ptcounter=0;

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
	labelflag=CheckForLabel(inst , strlen(inst),&stcounter,lc);
	
		if(labelflag==-1)
			i=0;
		else
			i=labelflag;
			
	while(inst[i]==' ' || inst[i]==':')
		i++;	



	// Finding OPCODE of Imperative Statement if present
	char is[20];
	for(;i<strlen(inst)&&inst[i]!=' ';i++)
	{
		is[z++]=inst[i];
	}

	is[z]='\0';
	//printf("%s",is);
        for(j=0;j<11;j++)
        {
            if(strcmp(is , MotTable[j].name)==0)
                {
                    isflag=1;
                    printf("%d ",MotTable[j].opcode);
                    break;
                }


        }
	
	// STOP Statement
	if(j==0)
		{
			printf("End of Code Section\n");
			lc++;
			
			continue;

		}
	//Branching Statement
	if(j==7)
		{
			
			char bckeyword[20];
			z=0;
			while(inst[i]==' ')
				i++;


			for(;i<strlen(inst)&&inst[i]!=' ';i++)
				bckeyword[z++]=inst[i];

			bckeyword[z]='\0';

			if(strcmp(bckeyword,"LT")==0)
				{
					printf("1 ");
				}
			else if(strcmp(bckeyword,"LE")==0)
				{
					printf("2 ");
				}
			else if(strcmp(bckeyword,"EQ")==0)
				{
					printf("3 ");
				}
			else if(strcmp(bckeyword,"GT")==0)
				{
					printf("4 ");
				}
			else if(strcmp(bckeyword,"GE")==0)
				{
					printf("5 ");
				}
			else if(strcmp(bckeyword,"ANY")==0)
				{
					printf("6 ");
				}



			while(inst[i]==' ')
				i++;
			
			//Jumping to Label
		
			char label[20];
			z=0;
			
			for(;i<strlen(inst)&&inst[i]>='A' && inst[i]<='Z';i++)
				label[z++]=inst[i];

			label[z]='\0';
			int labelflag=0;
			
			for(j=0;j<stcounter;j++)
				if(strcmp(SymbolTable[j].name,label)==0)
					{
						printf("%d ",SymbolTable[j].location);
						labelflag=1;
						printf("  %d\n",lc);
						lc++;
						
						continue;
					}

			if(labelflag==0)
					{
						strcpy(SymbolTable[stcounter].name,label);
						SymbolTable[stcounter].location=-1;
						printf("<%s> ",SymbolTable[stcounter++].name);
						
						printf("  %d \n",lc);
						lc++;
						continue;
					}
			
		}

        if(isflag==0)
            {
		// Testing in POT Table	
		//printf("AD Found");	
			for(j=0;j<5;j++)
				{
					if(strcmp(is , PotTable[j].name)==0)
						{
				    			isflag=1;
				   			//printf("%s",is);
				    			break;
						}
				}


			if(isflag==1)
				{
				  if(j==0)
					{
						// Found START
						printf("\n Error : START Assembler Directive found twice");
					}
				  else if(j==1)
					{
						// Found ORIGIN
						
						while(inst[i]==' ')
							i++;

						int templc=0,templcflag=0,op2=0,op3=-1;
						 
						char loc[20],op;
						

						for(;i<strlen(inst) && (inst[i]>='A' && inst[i]<='Z');i++)
							{
								loc[templc++]=inst[i];
								templcflag=1;
							}
				
						op=inst[i]; 
						i++;
		
						for(;i<strlen(inst) && (inst[i]!=' ');i++)
							{
								op2*=10;
								op2+=(inst[i]-'0');
							}
						//printf("%c %d" , op , op2);
		
						if(templcflag==0)
							{
								printf("\n Error in ORGIN statement syntax");
							}
						else
							{
								for(j=0;j<stcounter;j++)
									if( strcmp(loc , SymbolTable[j].name)==0)
										{
											op3 = SymbolTable[j].location;
											break;
										}

								if(op3==-1)
									{
										printf("\n Invalid location Specified by ORIGIN");
									}

								if(op=='+')
									lc = op3 + op2;
								else if(op=='-')
									lc = op3 - op2;
							}	

						//printf("\n");
						continue;
					}

				else if(j==2)
					{
						//Found END	
						int k;					
						for(k=0;k<ltcounter;k++)
							{
								int ptflag=0;
								if( LiteralTable[k].location==-1)
									{
										if(k<PoolTable[ptcounter].batch)
											PoolTable[ptcounter].batch=k;
					
										int pte=0,l=0;
										ptflag=1;									
										while(LiteralTable[k].name[l]<'0' || LiteralTable[k].name[l]>'9')
												l++;
	
										for(;l<strlen(LiteralTable[k].name) && LiteralTable[k].name[l]>='0' && LiteralTable[k].name[l]<='9';l++)
					
										{
											pte*=10;
											pte+=(LiteralTable[k].name[l]-'0');
										}

										LiteralTable[k].location = lc++;
										
										//printf("\n %d",pte);
									}

								if(ptflag==1)
									{
										++ptcounter;
										
									}
							}

					/*
						//Printing Symbol Table to check
					
						for(j=0;j<stcounter;j++)
							printf("%s %d\n", SymbolTable[j].name , SymbolTable[j].location);
			
						//Printing Literal Table to check			
						
						for(j=0;j<ltcounter;j++)
							printf("%s %d\n" , LiteralTable[j].name , LiteralTable[j].location);
		
						//Printing Pool Table to check

						for(j=0;j<ptcounter;j++)
							printf("%d \n" , PoolTable[j].batch);
					*/

						exit(0);
					}	
			
				else if(j==3)
					{
						// Found EQU
						
						while(inst[i]==' ')
							++i;

						char eq[20];
							z=0;
				
						for(;i<strlen(inst)&&inst[i]!=' ';i++)
							eq[z++]=inst[i];														
					
						eq[z]='\0';

						//printf("%s",eq);

						int k;
						for(k=0;k<stcounter;k++)
							if(strcmp(SymbolTable[k].name,eq)==0)
								{							
									SymbolTable[stcounter++].location=SymbolTable[k].location;
								}
						lc++;
						continue;
					}
				
				else if(j==4)
					{
						//Found LTORG
						
						int lflag=0;
						int k;
						for(k=0;k<ltcounter;k++)
							{
									
							
								if(LiteralTable[k].location==-1)
									{
										if(k<PoolTable[ptcounter].batch)
											PoolTable[ptcounter].batch=k;			
							
										LiteralTable[k].location = lc;
										lflag=1;
										printf(" %d \n",lc);
										lc++;
									}
							}
						if(lflag==1)
							{
								++ptcounter;
								PoolTable[ptcounter].batch=ltcounter;
							}
						continue;
					}
		
				}
		if(isflag==0)
			{
				printf("\n %s instruction not found in MOT or POT" , is);
				exit(0);
			}

	    }

	
	//Checking for Register

	if(isflag==1 )
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
			for(j=PoolTable[ltcounter-1].batch;j<ltcounter;j++)
				if(strcmp(LiteralTable[j].name,LitSym)==0)
					{
						if(LiteralTable[j].location!=-1)
							{
								printf("%d ",LiteralTable[j].location);
							}
					
						else printf("<%s> ",LitSym);

						LitSymFlag=1;
					}

			if(LitSymFlag==0)
				{
					
					strcpy(LiteralTable[ltcounter].name,LitSym);
					LiteralTable[ltcounter].location=-1;
					printf("<%s> ",LiteralTable[ltcounter++].name);	
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
					
						else printf("<%s> ",LitSym);

						LitSymFlag=1;
					}

			if(LitSymFlag==0)
				{
					
					strcpy(SymbolTable[stcounter].name,LitSym);
					SymbolTable[stcounter].location=-1;
					printf("<%s> ",SymbolTable[stcounter++].name);	
				}
		}

	

//printf("%s",LitSym);
	
		
	
	
	printf("%d \n",lc);
	lc++;	
    }

    return 0;
}
