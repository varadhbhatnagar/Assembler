# Assembler
Assembler for a Simple Instruction Set written in C

The Instruction Set is as follows : </br>
OPCODE     IMPERATIVE STATEMENT :  </br>
                    		 </br>
0           STOP         </br>
1           ADD </br>
2          SUBTRACT </br>
3          MULT </br>
4          MOVER </br>
5          MOVEM </br>
6          COMP </br>
7          BC </br>
8          DIV </br>
9          READ </br>
10         PRINT </br>
 </br>
 </br>
The Assembler Directives to be used are : </br>

START </br>
LTORG </br>
EQU </br>
ORIGIN </br>
END </br>

Sample Code : </br>
 </br>
START 200 </br>
MOVER AREG, '=5' </br>
MOVEM AREG, A </br>
LOOP: MOVER AREG,A </br>
MOVER CREG, B </br>
ADD CREG , '=1' </br>
BC ANY NEXT </br>
LTORG </br>
NEXT: SUB AREG , '=1' </br>
BC LT BACK </br>
LAST: STOP  </br>
ORIGIN LOOP+2 </br>
MULT CREG,B </br>
ORIGIN LAST+1 </br>
BACK: EQU LOOP </br>
END </br>
