MOV CH,05H
L2: 
MOV CL,05H
MOV SI,2000H
L1:
MOV AL,[SI]
MOV BL,[SI+1]
CMP AL,BL
JC L3
MOV DL,[SI+1]
XCHG [SI],DL
MOV [SI+1],DL
L3:
INC SI
DEC CL
JNZ L1
DEC CH
JNZ L2
HLT
