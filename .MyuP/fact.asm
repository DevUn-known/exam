MOV CX, [00200H]
MOV AX, 00001H
MOV DX, 00000H

L1: 
    MUL CX
    LOOP L1

MOV [00202H], AX
MOV [00203H], DX

HLT
