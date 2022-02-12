#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <stdio.h>
#include <fcntl.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include "../mytypes.h"
#include "lcd_func78.h"
#include "serial_io.h"
/*
The DIO and LCD headers are controlled by 32 bit registers at 0xe8000004 and 0xe8000008. 
Bits 15-0 control the DIO header and bits 29-16 control the LCD header. The register at 
0xe8000008 is the output register. Writing a 0 drives the pin low but writing a 1 only 
tristates. To use these pins for input, write a 1 to the output register and read the 
register at 0xe8000004.

*/
/*********************************************************************************************************/
#ifdef TS_7800

#define MIRROR_PINS

#define PADR    0							// address offset of LCD
#define PADDR   (0x10 / sizeof(UINT))		// address offset of DDR LCD
#define PHDR    (0x40 / sizeof(UINT))		// bits 3-5: EN, RS, WR
#define PHDDR   (0x44 / sizeof(UINT))		// DDR for above
#define DIODDR	(0x14 / sizeof(UINT))
#define DIOADR	(0x04 / sizeof(UINT))
#define PORTFB  (0x30 / sizeof(UINT))
#define PORTFD	(0x34 / sizeof(UINT))

/**********************************************************************************************************/
void test_lcdbit(int level)
{
	// DIO9 - bit 0		when these are written to SPI_RW
	// DIO11 - bit 2
	// SPI_MOSI - bit 3
	// DIO13 - bit 4
	// SPI_CLK - bit 5
	// DIO 15 - bit 6
	int ii;
	SPI_RW |= SCOPE_TRIGGER;
	for (ii=0;ii<20000;ii++);
	for (ii=0;ii<20000;ii++);
	for (ii=0;ii<20000;ii++);
	SPI_RW &= ~SCOPE_TRIGGER;

	//printf("%02x ",temp);
//	for (ii=0;ii<20000;ii++);
/*
	for (ii=0;ii<20000;ii++);
	putLCDbit(4,level);
	for (ii=0;ii<20000;ii++);
	putLCDbit(5,level);
	for (ii=0;ii<20000;ii++);
	putLCDbit(6,level);
	for (ii=0;ii<20000;ii++);
	putLCDbit(7,level);
	for (ii=0;ii<20000;ii++);
	putLCDbit(8,level);
	for (ii=0;ii<20000;ii++);
	putLCDbit(9,level);
	for (ii=0;ii<20000;ii++);
	putLCDbit(10,level);
*/
}
/**********************************************************************************************************/
int init_spi(void)
{
	printf("init_spi\r\n");
	spi_fd = open("/dev/mem", O_RDWR|O_SYNC);
	if(spi_fd < 0)
	{
		printf("failed to open /dev/mem\n");
		return -1;
	}
	else
	{
		spi_dioptr = (UCHAR *)mmap(0, getpagesize(),
			PROT_READ|PROT_WRITE, MAP_SHARED, spi_fd, LCDBASEADD);

		RW_REG(spi_dioptr) &= ~BASELINE_MASK; /* baseline should always be zero */
		SPI_RW |= SPI_CLK;

		printf("opened spi_fd: %d %d %4x \n",spi_fd,getpagesize(),spi_dioptr);
		vulcd = (UINT *)spi_dioptr + 1;
/*
		phdr = &spi_dioptr[PHDR];
		padr = &spi_dioptr[PADR];
		paddr = &spi_dioptr[PADDR];

		phddr = &spi_dioptr[PHDDR];
		dio_addr = &spi_dioptr[DIOADR];
		dio_ddr = &spi_dioptr[DIODDR];

		printf("phdr:     %4x %4x\n",phdr,*phdr);	  // 40
		printf("padr:     %4x %4x\n",padr,*padr);	  // 0
		printf("paddr:    %4x %4x\n",paddr,*paddr);	  // 10
		printf("phddr:    %4x %4x\n",phddr,*phddr);	  // 44
		printf("dio_addr: %4x %4x\n",dio_addr,*dio_addr);
		printf("dio_ddr:  %4x %4x\n",dio_ddr,*dio_ddr);
		printf("portfb:   %4x %4x\n",portfb,*portfb);  // 30
		printf("portfd:   %4x %4x\n",portfd,*portfd);  // 34
		*paddr = 0xff;	  // set port A to outputs
*/
		return 0;
	}
}

/**********************************************************************************************************/
void test_spi(void)
{
	int i;
	printf("test_spi\r\n");
	for(i = 0;i < 32;i++)
		printf("%X : %2x\n",spi_dioptr + i,*(spi_dioptr + i));
}

/**********************************************************************************************************/
void test_spi2(void)
{
	int i;
	printf("test_spi2\r\n");
	printf("%2x %2x %2x %2x %2x\n",SPI_RO,SPI_RW,SPI_CLK,SPI_MOSI,SPI_MISO);
	// this returns "1 21 20 8 2"
}

/**********************************************************************************************************/
unsigned char spi8(unsigned char c)
{
	int i;
	unsigned char m0c0, m1c0, m0c1, m1c1;
	unsigned char ret = 0;

	m1c1 = SPI_RW | SPI_MOSI | SPI_CLK;
	m1c0 = m1c1 & ~SPI_CLK;
	m0c0 = m1c0 & ~SPI_MOSI;
	m0c1 = m1c1 & ~SPI_MOSI;

	DELAY1();
	for(i=0; i < 8; i++)
	{
		if (c & 0x80)
		{
			DELAY1();
			SPI_RW = m1c1;
			ret <<= 1;
			DELAY1();
			SPI_RW = m1c0;
			c <<= 1;
			DELAY1();
			if (~SPI_RO & SPI_MISO) ret |= 1;	  // SPI MISO comes out inverted on the 7800.
			DELAY1();
		}
		else
		{
			DELAY1();
			SPI_RW = m0c1;
			ret <<= 1;
			DELAY1();
			SPI_RW = m0c0;
			c <<= 1;
			DELAY1();
			if (~SPI_RO & SPI_MISO) ret |= 1;	  // SPI MISO comes out inverted on the 7800.
			DELAY1();
		}
	}
	SPI_RW = m0c1;
	return ret;
}

/**********************************************************************************************************/
unsigned int spi32(unsigned int c)
{
	int i;
	unsigned char m0c0, m1c0, m0c1, m1c1;
	unsigned int ret = 0;

	m1c1 = SPI_RW | SPI_MOSI | SPI_CLK;
	m1c0 = m1c1 & ~SPI_CLK;
	m0c0 = m1c0 & ~SPI_MOSI;
	m0c1 = m1c1 & ~SPI_MOSI;
	for(i=0; i < 32; i++)
	{
		if (c & 0x80000000)
		{
			SPI_RW = m1c1;
			ret <<= 1;
			SPI_RW = m1c0;
			if (~SPI_RO & SPI_MISO) ret |= 1;	  // SPI MISO comes out inverted on the 7800.
			c <<= 1;
		}
		else
		{
			SPI_RW = m0c1;
			ret <<= 1;
			SPI_RW = m0c0;
			if (~SPI_RO & SPI_MISO) ret |= 1;	  // SPI MISO comes out inverted on the 7800.
			c <<= 1;
		}
	}
	SPI_RW = m0c1;
	return ret;
}

/**********************************************************************************************************/
void spi_write8(unsigned char c)
{
	int i;
	unsigned char m0c0, m1c0, m0c1, m1c1;
	m1c1 = SPI_RW | SPI_MOSI | ~SPI_CLK;
	m1c0 = m1c1 & SPI_CLK;
	m0c0 = m1c0 & ~SPI_MOSI;
	m0c1 = m1c1 & ~SPI_MOSI;

	usleep(10);
	for(i=0; i < 8; i++)
	{
		if (c & 0x80)
		{
			SPI_RW = m1c1;
			usleep(10);
			SPI_RW = m1c0;
		}
		else
		{
			SPI_RW = m0c1;
			usleep(10);
			SPI_RW = m0c0;
		}
		c <<= 1;
		usleep(10);
	}
	SPI_RW = m0c1;
	usleep(10);
}

/**********************************************************************************************************/
void spi_write32(unsigned int c)
{
	int i;
	unsigned char m0c0, m1c0, m0c1, m1c1;

	m1c1 = SPI_RW | SPI_MOSI | SPI_CLK;
	m1c0 = m1c1 & ~SPI_CLK;
	m0c0 = m1c0 & ~SPI_MOSI;
	m0c1 = m1c1 & ~SPI_MOSI;
	for(i=0; i < 32; i++)
	{
		if (c & 0x80000000)
		{
			SPI_RW = m1c1;
			c <<= 1;
			printf("%2x ",c);
			SPI_RW = m1c0;
		}
		else
		{
			SPI_RW = m0c1;
			c <<= 1;
			printf("%2x ",c);
			SPI_RW = m0c0;
		}
	}
	SPI_RW = m0c1;
}
#ifndef MAKE_TARGET
/*********************************************************************************************************/
static void mydelay(unsigned long i)
{
	unsigned long j;

	do
	{
		for(j = 0;j < 10000;j++);
		i--;
	}while(i > 0);
}

/**********************************************************************************************************/
int main(void)
{
	int i,j,key, ii;
	int level = 0;
	UCHAR temp, temp2;
	char errmsg[20];

	i = j = 0;

	init_spi();
	init_serial3(4);
	printf("version 0.1\n");
	do
	{
		key = getc(stdin);
		switch(key)
		{
			case 'a':
				// to test this hook GND to pin 10 (MISO) 
				// to show '00' or leave open to show '02'
				printf("MISO input: %02x\n", ~SPI_RO & SPI_MISO);
				printf("MOSI input: %02x\n", ~SPI_RO & SPI_MOSI);
				printf("CLK input: %02x\n", ~SPI_RO & SPI_CLK);
				printf("SS input: %02x\n", ~SPI_RO & SPI_SS);						// pin 13
				printf("SCOPE_TRIGGER input: %02x\n", ~SPI_RO & SCOPE_TRIGGER);		// pin 15
				printf("%X : %2x\n",spi_dioptr + 5,*(spi_dioptr + 5));
				printf("done\n");
				break;

			case 'b':
/*
				for(i = 0;i < 500;i++)
				{
					SPI_RW |= SCOPE_TRIGGER;
					mydelay(1);
					SPI_RW &= ~SCOPE_TRIGGER;
					mydelay(1);
					SPI_RW |= SPI_SS;
					mydelay(20);
					SPI_RW &= ~SPI_SS;
					mydelay(10);
				}

				// so tie MOSI TO MISO and try this...
				temp &= SPI_CLK;
				printf("SPI_CLK: %02x\n",SPI_CLK);
				printf("SPI_MOSI: %02x\n",SPI_MOSI);
				printf("SPI_MISO: %02x\n",SPI_MISO);
				printf("SPI_SS: %02x\n",SPI_SS);
				SPI_RW = 0;
				SPI_RW |= SPI_MOSI;
				printf("%02x\n",SPI_RW);	// 08
				SPI_RW = 0;
				SPI_RW |= SPI_MISO;
				printf("%02x\n",SPI_RW);	// 02
				SPI_RW = 0;
				SPI_RW |= SPI_CLK;
				printf("%02x\n",SPI_RW);	// 20
				SPI_RW = 0;
				SPI_RW |= SPI_SS;
				printf("%02x\n",SPI_RW);	// 10
				SPI_RW = 0;
				printf("done\n");
*/
				SPI_RW = 0;
				printf("%02x\n",SPI_RW);
				SPI_RW |= SPI_MOSI;
				DELAY5();
				printf("%02x %02x\n",SPI_RW, SPI_RO);
				break;

			case 'c':
				test_spi();
				printf("done\n");
				break;

			case 'd':
				test_spi2();
				printf("done\n");
				break;

			case 'e':
				temp = 0x21;
				printf("starting master SPI\n");
				for(i = 0;i < 200;i++)
				{

					SPI_RW |= SCOPE_TRIGGER;
					DELAY1();
					SPI_RW &= ~SCOPE_TRIGGER;
					DELAY1();
					SPI_RW &= ~SPI_SS;

					DELAY1();
					printf("%02x => ",temp);

					temp++;
					if(temp > 0x7f)
						temp = 0x21;
					temp2 = spi8(temp);
//					spi_write8(temp++);
					printf("%02x %02x\r\n",temp2,temp2-temp);

					DELAY1();
					SPI_RW |= SPI_SS;
					DELAY1();

				}
				printf("done\n");
				break;

			case 'f':
				temp = 0;
				for(i = 0;i < 100;i++)
				{
					DELAY1();
					printf("%02x => ",temp);
					temp2 = spi8(temp++);
					printf("%02x %02x\r\n",temp2,temp2-temp);
				}
				printf("done\n");
				break;

			case 'g':
				temp = 0xAA;
				for(i = 0;i < 100;i++)
				{
					SPI_RW |= SCOPE_TRIGGER;
					mydelay(10);
					SPI_RW &= ~SCOPE_TRIGGER;
					mydelay(10);
					SPI_RW &= ~SPI_SS;
					spi_write8(temp);
					SPI_RW |= SPI_SS;
					mydelay(100);
				}
				printf("done\n");
				break;

			case 'h':
				temp = 0x21;
				for(i = 0;i < 500;i++)
				{
					if(temp > 0x7e)
						temp = 0x21;
					printf("%c\n",temp++);
					usleep(1);
				}
				break;
			case 'i':
				temp = 0x21;
				for(i = 0;i < 500;i++)
				{
					if(temp > 0x7e)
						temp = 0x21;
					printf("%c\n",temp++);
					mydelay(1);
				}
				break;

			case 'm':
				printf("c - clear screen\n");
				printf("l - left shift\n");
				printf("r - right shift\n");
				printf("h - home cursor\n");
				printf("u - scroll_up\n");
				printf("d - scroll_down\n");
				printf("p - print new string to buffer\n");
				printf("q - quit\n");
				break;
			case 'p':
				temp = 0x21;
				printf("testing w/r\n");
				while(1)
				{
					for(i = 0;i < 500;i++)
					{
						write_serial3(temp);
						if(++temp > 0x7f)
							temp = 0x21;
						DELAY1();
					}
					for(i = 0;i < 500;i++)
					{
						temp = read_serial3(errmsg);
						printf("%c",temp);
					}
					printf("\n");
				}
				break;
			case 'u':
				printf("reading comm3\n");
//				for(i = 0;i < 5000;i++)
				while(1)
				{
					temp = read_serial3(errmsg);
					printf("%c",temp);
				}
				break;
			case 't':
				write_serial3(0xFE);
				for(i = 0;i < 500;i++)
				{
					temp = read_serial3(errmsg);
					printf("%c",temp);
				}
				break;
			case 'v':
				write_serial3(0xFD);
				for(i = 0;i < 500;i++)
				{
					temp = read_serial3(errmsg);
					printf("%c",temp);
				}
				break;
			case 'w':
				write_serial3(0xFC);
				for(i = 0;i < 500;i++)
				{
					temp = read_serial3(errmsg);
					printf("%c",temp);
				}
				break;
			case '1':
				break;
			case '2':
				break;
			case '3':
				break;
			case '4':
				break;
			case '5':
				break;
			case '6':
				break;
			case '7':
				break;
			case '8':
				break;
			case '9':
				break;
			default:
				break;
		}
	}while(key != 'q');
}
#endif
#endif
