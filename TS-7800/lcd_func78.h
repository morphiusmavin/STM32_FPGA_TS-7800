#ifndef __LCD_FUNC_H
#define __LCD_FUNC_H

#ifndef TS_7800
#warning "TS_7800 not defined in lcd_func"
#else

#define LCD_BUF_LINES 30
#define LCD_BUF_COLS 32
static char buffer[LCD_BUF_LINES][LCD_BUF_COLS];
static char *buf_ptr;
static int cur_buf_line;
static int cur_disp_line;
static int cur_buf_size;

volatile UINT *vulcd;

#define	LCDBASEADD	  0xE8000000
#define RW_MASK       0x00200000
#define ENABLE_MASK   0x00100000
#define BASELINE_MASK 0x00080000
#define RS_MASK       0x00040000
#define BUSY_MASK     0x20000000

#define DELAY1() mydelay(1)
#define DELAY2() mydelay(2)
#define DELAY3() mydelay(5)
#define DELAY4() mydelay(10)
#define DELAY5() mydelay(20)

#define RW_REG(ptr) *(ptr + 0x08/sizeof(unsigned int))

#define SPI_CLK (1 << 5)		// pin 14
#define SPI_MOSI (1 << 3)		// pin 12
#define SPI_MISO (1 << 1)		// pin 10
#define SPI_SS (1 << 4)			// pin 13 (DIO_13)
#define SCOPE_TRIGGER (1 << 6)	// pin 15 (DIO_15)

#define SPI_RO *(spi_dioptr + 0x05/sizeof(unsigned char))
#define SPI_RW *(spi_dioptr + 0x09/sizeof(unsigned char))

volatile UCHAR *spi_dioptr;
volatile  int spi_fd;

#if 0
#define PADR    0							// address offset of LCD
#define PADDR   (0x10 / sizeof(UINT))		// address offset of DDR LCD
#define PHDR    (0x40 / sizeof(UINT))		// bits 3-5: EN, RS, WR
#define PHDDR   (0x44 / sizeof(UINT))		// DDR for above
#define DIODDR	(0x14 / sizeof(UINT))
#define DIOADR	(0x04 / sizeof(UINT))
#define PORTFB  (0x30 / sizeof(UINT))
#define PORTFD	(0x34 / sizeof(UINT))
#define PORTLED	(0x20 / sizeof(UINT))
#endif
//The RED and Green LEDs can be controlled at physical address location 0x8084_0020.
//Bit 1 is the RED LED and bit 0 is the Green LED. A Logic “1” turns the LED on.

#define HOME 0x80
#define ROW2 0xA8
#define CLEAR 0x01
#define SHIFTLEFT 0x18
#define SHIFTRIGHT 0x1c

// These delay values are calibrated for the EP9301
// CPU running at 166 Mhz, but should work also at 200 Mhz
#define SETUP   15
#define PULSE   36
#define HOLD    22

static void lcdinit(void);
static void lcd_cursor(int row, int col, int page);
static void add_col(void);
static void inc_bufptrs(void);
inline void lcd_wait_not_busy(void);
inline void lcd_cmd_cls(void);

static void display_current(int special_case);
void scroll_up(void);
void scroll_down(void);
int myprintf1(char *str);
int myprintf2(char *str, int i);
int myprintf3(char *str, int i, int j);
void shift_left(void);
void shift_right(void);
void lcd_home(void);
void lcd_cls(void);
void red_led(int onoff);
void green_led(int onoff);
int lcd_enabled;
void test_spi2(void);
void test_spi(void);
void test_lcdbit(int level);
int init_spi(void);
static void mydelay(unsigned long i);

volatile UINT *gpio;
volatile UINT *phdr;
volatile UINT *phddr;
volatile UINT *padr;
volatile UINT *paddr;
volatile UINT *dio_addr;
volatile UINT *dio_ddr;
volatile UINT *portfb;
volatile UINT *portfd;

#endif
#endif

