#include<header.h>
#include<stdlib.h>

void FillSymbolTable()
{
	int i=0;
	char string[20],loc[20];
	FILE * fp;
	fp = fopen("symboltab.txt","r");

	while(!feof(fp))
		{
			fscanf(fp,"%s",string);
			fscanf(fp,"%s",loc);
			strcpy(SymbolTable[i].name,string);
			SymbolTable[i].location = atoi(loc);
			i++;
		}
	fclose(fp);
}

void FillLiteralTable()
{
	int i=0;
	char string[20],loc[20];
	FILE * fp;
	fp = fopen("literaltab.txt","r");

	while(!feof(fp))
		{
			fscanf(fp,"%s",string);
			fscanf(fp,"%s",loc);
			strcpy(LiteralTable[i].name,string);
			LiteralTable[i].location = atoi(loc);
			i++;
		}
	fclose(fp);
}

void FillPoolTable()
{
	int i=0;
	char string[20],loc[20];
	FILE * fp;
	//printf("here");
	fp = fopen("symboltab.txt","r");

	while(!feof(fp))
		{
			fscanf(fp,"%s",string);
			PoolTable[i].batch = atoi(loc);
			i++;
		}
	fclose(fp);
}

int main()
	{
		CreateMotTable();
    		CreatePotTable();
	       
		FillSymbolTable();
		FillLiteralTable();
		FillPoolTable();

		FILE *f2,*f3;
		f2= fopen("outputic.txt","r");
		f3= fopen("twopassout.txt","w");
		int len = 20;
		char * inst = NULL;


		if( f2==NULL)

		    {
			printf("\n The required file does not exist");

			return 0;
		    }
		getline(&inst , &len , f2 );
		while( getline(&inst , &len , f2 ) != -1)
    			{
				int i=0;	
				

				if(inst[0]=='(' && inst[1]=='A' && inst[2]=='D' && inst[3]==',')
					{

						continue;
						
					}
				else 
					{
						int line=0;
						while(inst[i]>='0' && inst[i]<='9')
							{
								line*=10;
								line+=(inst[i]-'0');
								i++;
							}

						
						
						while(inst[i]==' ' || inst[i]=='(')
							i++;
					
						if(inst[i]=='I' && inst[i+1]=='S')
							{
								fprintf(f3,"%d " , line);
								i+=3;
								
								int num =0;

								while(inst[i]>='0' && inst[i]<='9')
									{
										num*=10;
										num+=(inst[i]-'0');
										i++;
									}
								fprintf(f3,"%d " , num);
									if(num==0)
										{fprintf(f3,"\n");
											continue;
										}
								i++;
								while(inst[i]==' ' || inst[i]=='(' )
									i++;
								
								while(inst[i]!=')')
									{
										if(inst[i]>='0'&& inst[i]<='9')
											fprintf(f3,"%d ",inst[i]-'0');
										i++;
									}
								i++;
								while(inst[i]==' ' || inst[i]=='(' )
									i++;

								while((inst[i]=='L' && inst[i+1]=='T') || (inst[i]=='S' && inst[i+1]=='T'))
									{
										
										if(inst[i]=='L' && inst[i+1]=='T')
											{
												i+=3;
												char value[20];
												int z=0;
												
												while(inst[i]!=')')
													{
														value[z++]=inst[i++];
														
													}
												fprintf(f3,"%d\n",LiteralTable[atoi(value)].location);
											}

										else if(inst[i]=='S' && inst[i+1]=='T')
											{
												i+=3;
												char value[20];
												int z=0;
												
												while(inst[i]!=')')
													{
														value[z++]=inst[i++];
														
													}
												fprintf(f3,"%d\n",SymbolTable[atoi(value)].location);
											}
									}
									
						
								
							}
								

					
	
					}
				
			}

	
	}
