MOV SI, 2000H    ; Set the Source Index (SI) to 2000H (starting address for the source data)
MOV DI, 3000H    ; Set the Destination Index (DI) to 3000H (starting address for the destination)
MOV CX, 0064H    ; Set the Count (CX) to 0064H (100 in decimal), indicating the number of bytes to copy

REPE MOVSB       ; Repeat the MOVSB (move byte) instruction CX times (100 times),
                 ; transferring one byte at a time from the address in SI to the address in DI,
                 ; and automatically incrementing SI and DI after each byte move

HLT              ; Halt the program after the copy operation is complete
