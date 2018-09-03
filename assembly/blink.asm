-----------------------------------
AVR DISASSEMBLER LISTING
Address Opcode  Instruction
-----------------------------------
000000  940C    L5:	JMP L1
000001  0034
000002  940C    	JMP L2
000003  003E
000004  940C    	JMP L2
000005  003E
000006  940C    	JMP L2
000007  003E
000008  940C    	JMP L2
000009  003E
00000A  940C    	JMP L2
00000B  003E
00000C  940C    	JMP L2
00000D  003E
00000E  940C    	JMP L2
00000F  003E
000010  940C    	JMP L2
000011  003E
000012  940C    	JMP L2
000013  003E
000014  940C    	JMP L2
000015  003E
000016  940C    	JMP L2
000017  003E
000018  940C    	JMP L2
000019  003E
00001A  940C    	JMP L2
00001B  003E
00001C  940C    	JMP L2
00001D  003E
00001E  940C    	JMP L2
00001F  003E
000020  940C    	JMP L2
000021  003E
000022  940C    	JMP L2
000023  003E
000024  940C    	JMP L2
000025  003E
000026  940C    	JMP L2
000027  003E
000028  940C    	JMP L2
000029  003E
00002A  940C    	JMP L2
00002B  003E
00002C  940C    	JMP L2
00002D  003E
00002E  940C    	JMP L2
00002F  003E
000030  940C    	JMP L2
000031  003E
000032  940C    	JMP L2
000033  003E
000034  2411    L1:	CLR R1               // Limpa o Registrador 1
000035  BE1F    	OUT SREG,R1            // Armazena Registrador Status com R1
000036  EFCF    	LDI YL,$FF             // Carrega imediatamente em YL com endereço $FF
000037  E0D8    	LDI YH,$08             // Carrega imediatamente em YH com endereço $08
000038  BFDE    	OUT SPH,YH             // Armazena SPH com YH
000039  BFCD    	OUT SPL,YL             // Armazena SPL com YL
00003A  940E    	CALL L3                // Chama a Label L3
00003B  0040
00003C  940C    	JMP L4                 // Pula para a L4
00003D  0054
00003E  940C    L2:	JMP L5               // Pula para L5
00003F  0000
000040  9A56    L3:	SBI DDRD,6           // Coloca bit 1 DDR6 na posição 6
000041  E920    	LDI R18,$90            // Carrega imediatamente
000042  E031    	LDI R19,$01            // Carrega imediatamente
000043  9A5E    L10:	SBI PORTD,6        // Coloca bit 1 na PORTD, na posição 6
000044  ED80    	LDI R24,$D0            // Carrega imediatamente
000045  E097    	LDI R25,$07            // Carrega imadiatamente
000046  01F9    L7:	MOVW R31:R30,R19:R18 // Copia o par de registradores
000047  9731    L6:	SBIW ZH:ZL,1         // Subtrai imediatamente os valores em 1
000048  F7F1    	BRNE L6                // Se não for igual, vá a L6
000049  9701    	SBIW R25:R24,1         // Subtrai imediatamente os valores em 1
00004A  F7D9    	BRNE L7                // Se não for igual, vá a L7
00004B  985E    	CBI PORTD,6            // Limpa bit da PORTD, na posição 6
00004C  ED80    	LDI R24,$D0            // Carrega imediatamente em R24, variável $D0
00004D  E097    	LDI R25,$07            // ...
00004E  01F9    L9:	MOVW R31:R30,R19:R18 //  Copia o par de registradores
00004F  9731    L8:	SBIW ZH:ZL,1         // Subtrai imediatamente os valores em 1
000050  F7F1    	BRNE L8                // Se não for igual, vá a L8
000051  9701    	SBIW R25:R24,1         // Subtrai imediatamente os valores em 1
000052  F7D9    	BRNE L9                // Se não for igual, vá a L9
000053  CFEF    	RJMP L10               // Jump Relativo a L10
000054  94F8    L4:	BCLR 7               // Limpa a flag 7 em SREG
000055  CFFF    L11:	RJMP L11           // Loop infinito
