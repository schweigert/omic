// *** Hardwarespecific functions ***
void UTFT::LCD_Writ_Bus(char VH,char VL, byte mode)
{   
	switch (mode)
	{
	case 1:
		if (display_serial_mode==SERIAL_4PIN)
		{
			if (VH==1)
				sbi(P_SDA, B_SDA);
			else
				cbi(P_SDA, B_SDA);
			pulse_low(P_SCL, B_SCL);
		}
		else
		{
			if (VH==1)
				sbi(P_RS, B_RS);
			else
				cbi(P_RS, B_RS);
		}

		if (VL & 0x80)
			sbi(P_SDA, B_SDA);
		else
			cbi(P_SDA, B_SDA);
		pulse_low(P_SCL, B_SCL);
		if (VL & 0x40)
			sbi(P_SDA, B_SDA);
		else
			cbi(P_SDA, B_SDA);
		pulse_low(P_SCL, B_SCL);
		if (VL & 0x20)
			sbi(P_SDA, B_SDA);
		else
			cbi(P_SDA, B_SDA);
		pulse_low(P_SCL, B_SCL);
		if (VL & 0x10)
			sbi(P_SDA, B_SDA);
		else
			cbi(P_SDA, B_SDA);
		pulse_low(P_SCL, B_SCL);
		if (VL & 0x08)
			sbi(P_SDA, B_SDA);
		else
			cbi(P_SDA, B_SDA);
		pulse_low(P_SCL, B_SCL);
		if (VL & 0x04)
			sbi(P_SDA, B_SDA);
		else
			cbi(P_SDA, B_SDA);
		pulse_low(P_SCL, B_SCL);
		if (VL & 0x02)
			sbi(P_SDA, B_SDA);
		else
			cbi(P_SDA, B_SDA);
		pulse_low(P_SCL, B_SCL);
		if (VL & 0x01)
			sbi(P_SDA, B_SDA);
		else
			cbi(P_SDA, B_SDA);
		pulse_low(P_SCL, B_SCL);
		break;
	case 8:
		//Clear port registers
		REG_PIOB_CODR=0x4000000; //PB26
		REG_PIOD_CODR=0x64f; //PD0-3,PD6,PD9-10

		//DB08 on PIN22 -> PIO_PB26
		REG_PIOB_SODR=(VH<<26) & 0x4000000;
		//DB09 on PIN23 -> PIO_PA14
		REG_PIOA_SODR=(VH<<13) & 0x4000;
		//DB10 on PIN24 -> PIO_PA15
		REG_PIOA_SODR=(VH<<13) & 0x8000;
		//DB11 on PIN25 -> PIO_PD0
		REG_PIOD_SODR=(VH>>3) & 0x01;
		//DB12 on PIN26 -> PIO_PD1
		REG_PIOD_SODR=(VH>>3) & 0x02;
		//DB13 on PIN27 -> PIO_PD2
		REG_PIOD_SODR=(VH>>3) & 0x04;
		//DB14 on PIN28 -> PIO_PD3
		REG_PIOD_SODR=(VH>>3) & 0x08;
		//DB15 on PIN29 -> PIO_PD6
		REG_PIOD_SODR=(VH>>1) & 0x40;
		pulse_low(P_WR, B_WR);

		//DB08 on PIN22 -> PIO_PB26
		REG_PIOB_SODR=(VL<<26) & 0x4000000;
		//DB09 on PIN23 -> PIO_PA14
		REG_PIOA_SODR=(VL<<13) & 0x4000;
		//DB10 on PIN24 -> PIO_PA15
		REG_PIOA_SODR=(VL<<13) & 0x8000;
		//DB11 on PIN25 -> PIO_PD0
		REG_PIOD_SODR=(VL>>3) & 0x01;
		//DB12 on PIN26 -> PIO_PD1
		REG_PIOD_SODR=(VL>>3) & 0x02;
		//DB13 on PIN27 -> PIO_PD2
		REG_PIOD_SODR=(VL>>3) & 0x04;
		//DB14 on PIN28 -> PIO_PD3
		REG_PIOD_SODR=(VL>>3) & 0x08;
		//DB15 on PIN29 -> PIO_PD6
		REG_PIOD_SODR=(VL>>1) & 0x40;
		pulse_low(P_WR, B_WR);
		break;
	case 16:
		//Clear port registers
		REG_PIOA_CODR=0xc080; //PA7,PA14,PA15
		REG_PIOB_CODR=0x4000000; //PB26
		REG_PIOC_CODR=0x3e; //PC1 - PC5
		REG_PIOD_CODR=0x64f; //PD0-3,PD6,PD9-10
                
		//DB00 on PIN37 -> PIO_PC5
		REG_PIOC_SODR=(VL<<5) & 0x20;
		//DB01 on PIN36 -> PIO_PC4
		REG_PIOC_SODR=(VL<<3) & 0x10;
		//DB02 on PIN35 -> PIO_PC3
		REG_PIOC_SODR=(VL<<1) & 0x08;
		//DB03 on PIN34 -> PIO_PC2
		REG_PIOC_SODR=(VL>>1) & 0x04;
		//DB04 on PIN33 -> PIO_PC1
		REG_PIOC_SODR=(VL>>3) & 0x02;
		//DB05 on PIN32 -> PIO_PD10
		REG_PIOD_SODR=(VL<<5) & 0x400;
		//DB06 on PIN31 -> PIO_PA7
		REG_PIOA_SODR=(VL<<1) & 0x80;
		//DB07 on PIN30 -> PIO_PD9
		REG_PIOD_SODR=(VL<<2) & 0x200;
		//DB08 on PIN22 -> PIO_PB26
		REG_PIOB_SODR=(VH<<26) & 0x4000000;
		//DB09 on PIN23 -> PIO_PA14
		REG_PIOA_SODR=(VH<<13) & 0x4000;
		//DB10 on PIN24 -> PIO_PA15
		REG_PIOA_SODR=(VH<<13) & 0x8000;
		//DB11 on PIN25 -> PIO_PD0
		REG_PIOD_SODR=(VH>>3) & 0x01;
		//DB12 on PIN26 -> PIO_PD1
		REG_PIOD_SODR=(VH>>3) & 0x02;
		//DB13 on PIN27 -> PIO_PD2
		REG_PIOD_SODR=(VH>>3) & 0x04;
		//DB14 on PIN28 -> PIO_PD3
		REG_PIOD_SODR=(VH>>3) & 0x08;
		//DB15 on PIN29 -> PIO_PD6
		REG_PIOD_SODR=(VH>>1) & 0x40;

		pulse_low(P_WR, B_WR);
		break;
	}
}

void UTFT::_set_direction_registers(byte mode)
{
	if (mode==16)
	{
		REG_PIOA_OER=0xc080; //PA7,PA14,PA15 enable
		REG_PIOB_OER=0x4000000; //PB26 enable
		REG_PIOC_OER=0x3e; //PC1 - PC5 enable
		REG_PIOD_OER=0x64f; //PD0-3,PD6,PD9-10 enable
	}
}

