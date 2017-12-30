# Assembler
Assembler for a Simple Instruction Set written in C

The Instruction Set is as follows :

0          STOP
1          ADD
2          SUBTRACT
3          MULT
4          MOVER
5          MOVEM
6          COMP
7          BC
8          DIV
9          READ
10         PRINT


The Assembler Directives to be used are :

START
LTORG
EQU
ORIGIN
END

Sample Code :
START 200
MOVER AREG, '=5'
MOVEM AREG, A
LOOP: MOVER AREG,A
MOVER CREG, B
ADD CREG , '=1'
BC ANY NEXT
LTORG
NEXT: SUB AREG , '=1'
BC LT BACK
LAST: STOP 
ORIGIN LOOP+2
MULT CREG,B
ORIGIN LAST+1
BACK: EQU LOOP
END
