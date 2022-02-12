#ifndef MYTPYES_H
#define MYTPYES_H

typedef unsigned char UCHAR;
typedef unsigned int UINT;
typedef UCHAR* PUCHAR;
typedef unsigned long ULONG;

#define TIME_DELAY   990000000L

// this is the same as NUM_PORT_BITS (should be...)
#define NUM_DATA_RECS 40

#define NUM_DAT_NAMES 45
#define DAT_NAME_STR_LEN 25
//#define TDATE_STAMP_STR_LEN 25
#define TDATE_STAMP_STR_LEN 16
#define UPLOAD_BUFF_SIZE 10000
#define NUM_ADC_CHANNELS 11
#define SERIAL_BUFF_SIZE 10
#define RAW_DATA_ARRAY_SIZE 15

// tcp command sent to TS-7200 from laptop
// these have to exactly match what's in cmd_array[] in tasks.c

typedef struct
{
	int cmd;
	char cmd_str[30];
} CMD_STRUCT;

#define OLABELSIZE 30

typedef struct _ip
{
	int port;			// port which is controlled by the input
	int input;			// input port which controls output 
	int function;		// if this is > 0 then execute the function in cmd_array 
						// (CMD_STRUCT) instead of setting output 
	char label[OLABELSIZE];
}IP;

typedef struct
{
	float latitude;
	float longitude;
	char name[30];
}WAYPOINTS;

enum dist_units
{
	METERS,
	FEET,
	MILES,
	KILOMETERS,
	YARDS
}DIST_UNITS;

typedef struct
{
	UCHAR row;
	UCHAR col;
	UCHAR data_col;
} FORMAT_STR;

typedef struct
{
	UCHAR fpga_val;
	UCHAR adc_val;	// the corrisponding values returned by the light sensor
} DIMMER_STR;

enum rt_values_offsets
{
	OIL_PRES,
	AIR_TEMP,
	MAP,
	OIL_TEMP,
	O2,
	ODOM,
	TRIP,
	RPM,
	MPH,
	RUN_TIME,
	ENG_TEMP,
	FUEL_LEVEL,
	OUTDOOR_TEMP,
	IND_TEMP,
	LAT,
	LONG,
	GPS_DIR,
	GPS_SPEED,
	GPS_ALT,
	NEXT,
	PREV,
	ENGINE,
	COOLING_FAN,
	HEAD_LIGHTS,
	BRIGHTS,
	BRAKES,
	RUNNING_LIGHTS
} RT_VALUES_OFFSETS_TYPES;

// msg's sent from client to TS-7200
enum cmd_types
{
	NON_CMD,
	ENABLE_START,
	STARTER_OFF,
	ON_ACC,
	OFF_ACC,
	ON_FUEL_PUMP,
	OFF_FUEL_PUMP,
	ON_FAN,
	OFF_FAN,
	ON_LIGHTS,
	OFF_LIGHTS,
	ON_BRIGHTS,
	OFF_BRIGHTS,
	BLANK,
	ESTOP_SIGNAL,
	ON_BRAKES,
	OFF_BRAKES,
	ON_RUNNING_LIGHTS,
	OFF_RUNNING_LIGHTS,
	SPECIAL_CMD,
	START_SEQ,
	SHUTDOWN,
	ON_LLIGHTS,
	OFF_LLIGHTS,
	ON_LBRIGHTS,
	OFF_LBRIGHTS,
	ON_RLIGHTS,
	OFF_RLIGHTS,
	ON_RBRIGHTS,
	OFF_RBRIGHTS,
	WIPER1,
	WIPER2,
	WIPER_OFF,
	SHUTDOWN_IOBOX,
	REBOOT_IOBOX,
	SET_TIME,
	GET_TIME,
	TEST_LEFT_BLINKER,
	TEST_RIGHT_BLINKER,
	DISCONNECT,
	BAD_MSG,
	CURRENT_TIME,
	SET_PARAMS,
	EXIT_PROGRAM,
	ENGINE_TEMP,
	INDOOR_TEMP,
	SEND_RT_VALUES1,
	SEND_RT_VALUES2,
	SEND_RT_VALUES3,
	ENGINE_RUNTIME,
	SERVER_UPTIME,
	SEND_CONFIG,
	SEND_MSG,
	SEND_RPM,
	SEND_MPH,
	SEND_ADCS1,
	SEND_ADCS2,
	NAV_UP,
	NAV_DOWN,
	NAV_SIDE,
	NAV_CLICK,
	NAV_CLOSE,
	SEND_STATUS,
	SERVER_UP,
	SERVER_DOWN,
	UPLOAD_NEW,
	UPLOAD_OTHER,
	UPLOAD_NEW_PARAM,
	SET_TEMP_LIMIT,
	SET_FAN_ON,
	SET_FAN_OFF,
	HIGH_REV_LIMIT,
	LOW_REV_LIMIT,
	LIGHTS_ON_DELAY,
	SET_BATT_BOX_TEMP,
	TEMP_TOO_HIGH,
	GET_VERSION,
	UPDATE_CONFIG,
	SEND_CONFIG2,
	GET_CONFIG2,
	CLIENT_CONNECTED,
	SERVER_CONNECTED,
	SET_KEYMODE,
	SHELL_AND_RENAME,
	REFRESH_LCD,
	SEND_GPS_GLL_DATA,
	SEND_GPS_GGA_DATA,
	SEND_GPS_GSA_DATA,
	SEND_GPS_GSV_DATA,
	SEND_GPS_RMC_DATA,
	SEND_GPS_VTG_DATA,
	SEND_GPS_ZDA_DATA,
	SET_GPS_DATA,
	SET_GPS_BAUDRATE,
	ENABLE_GPS_SEND_DATA,
	ENABLE_ADC_SEND_DATA,
	ADC_GATE,
	SET_ADC_RATE,
	SET_RPM_MPH_RATE,
	SET_FPGA_RATE,
	SEND_RT_FPGA_STATUS,
	SEND_REV_LIMIT_OVERRIDE,
	SEND_FP_OVERRIDE,
	LCD_TEST_MODE,
	LCD_SCROLL_UP,
	LCD_SCROLL_DOWN,
	LCD_SHIFT_RIGHT,
	LCD_SHIFT_LEFT,
	LCD_CLEAR,
	TEST_IO_PORT,
	SEND_LCD_PWM,
	SEND_DIMMER_VALUES,
	SEND_DEBUG_MSG,
	SET_RPM_MPH_BRIGHTNESS,
	TEST_ENGINE_TEMPS,
	START_WIPER_OFF
}CMD_TYPES;

enum key_types
{
 	KP_1 = 0xE0, //		- E0
	KP_2, // '2'		- E1
	KP_3, // '3'		- E2
	KP_4, // '4'		- E3
	KP_5, // '5'		- E4
	KP_6, // '6'		- E5
	KP_7, // '7'		- E6
	KP_8, // '8'		- E7
	KP_9, // '9'		- E8
	KP_A, // 'A'		- E9
	KP_B, // 'B'		- EA
	KP_C, // 'C'		- EB
	KP_D, // 'D'		- EC
	KP_POUND,	// '#'	- ED
	KP_AST, // '*'		- EE
	KP_0 	// '0'		- EF
} KEY_TYPES;

// 25 total output_types
// until now the input labels match the outputs
// this is not always the case
// the labels for the I_DATA types
// are the same up to TESTOUTPUT25
// then all the labels for the inputs
// are called TESTINPUTXX

// also need to insert signals for fuelpump and ignition interrupt relays
// controlled by the FPGA in series with primary fuelpump and ignition relays (1 & 2)
enum input_types
{
	STARTER_INPUT,				// 0 	STARTER & COOLINGFAN don't go to the tray
	COOLINGFAN_INPUT,			// 1 	first card starts @ 280h
	BRAKE_INPUT,				// 2
	SEAT_SWITCH,				// 3
	DOOR_SWITCH,				// 4
	WIPER_HOME,					// 5  	red wire from the wiper motor
	WIPER1_INPUT,				// 6  	switch to turn on slow wipers
	WIPER2_INPUT,				// 7 	switch to turn on fast wipers
	WIPER_OFF_INPUT,			// 8
	BACKUP_INPUT,				// 9
	HEADLAMP_INPUT,				// 10 	this starts the DB-15 under the dash
	RUNNING_LIGHTS_INPUT,		// 11 	HEADLAMP_INPUT -> BRIGHTS_INPUT comes
	MOMENTARY_INPUT,			// 12 	from the AM turn signal switch
	RIGHTBLINKER_INPUT,			// 13 	20 is the start of the 2nd card @ 300h
	LEFTBLINKER_INPUT,			// 14
	BRIGHTS_INPUT,				// 15
	ESTOP_INPUT = 27,			// 27	emergency stop
	ROCKER1_INPUT,				// 28
	ROCKER2_INPUT,				// 29
	ROCKER3_INPUT,				// 30
	ROCKER4_INPUT,				// 31
	ROCKER5_INPUT,				// 32
}INPUT_TYPES;

// * 25 not working only because wire from DB-15 not going to cable on dip on TS-7800

enum output_types
{
	STARTER,			// bank 0
	ACCON,
	FUELPUMP,
	COOLINGFAN,
	LHEADLAMP,
	RHEADLAMP,
	RUNNINGLIGHTS,
	LIGHTBAR,

	LEFTRBLINKER,		// bank 1
	RIGHTRBLINKER,
	LEFTFBLINKER,
	RIGHTFBLINKER,
	LBRAKELIGHT,
	RBRAKELIGHT,
	XLBLINKER,
	XRBLINKER,

	LBRIGHTS,			// bank 2
	RBRIGHTS,
	DOME_LIGHTS,
	WWIPER1,
	WWIPER2,
	WWIPER_OFF,
	ROCKER_SW1,
	ROCKER_SW2,

	ROCKER_SW3,
	ROCKER_SW4,			// bank 3
	ROCKER_SW5,
	BACKUPLIGHTS,
	MOMENTARY,
	TESTOUTPUT29,
	TESTOUTPUT30,
	TESTOUTPUT31,

	TESTOUTPUT32,		// bank 4
	TESTOUTPUT33,
	TESTOUTPUT34,
	TESTOUTPUT35,
	TESTOUTPUT36,
	TESTOUTPUT37,
	TESTOUTPUT38,
	TESTOUTPUT39
}OUTPUT_TYPES;

#define LAST_OUTPUT_WITH_SPECIAL_TYPE XRBLINKER+1		// see list.txt

/*
TRLEFTBLINKER,		// don't really need these as outputs 
TRRIGHTBLINKER,		// can just have extra relays in par to 
					// outputs of current blinker relays
*/

#define LEN 30
#define AVR_BUF_LEN 15
#define NUM_STR 36	// no. of strings in eeprom (AVR_t6963/eeprom/main_burn.c)

#define COLUMN              40      //Set column number to be e.g. 32 for 8x8 fonts, 2 pages
#define ROWS                16
#define SIZE_NUM			20		// size of buffer used by num entry mode
#define PASSWORD_SIZE 		6

// messages sent from STM32 to AVR using the AVR_cmd task
#define AVR_START_BYTE 0xFE
#define AVR_END_BYTE 0xFD

#define CHAR_CMD				2
#define GOTO_CMD				3
#define SET_MODE_CMD	 		4
#define LCD_CLRSCR				5
#define LCD_MSG1				6
#define BURN_EEPROM				7	// these are used by the eeprom/burn_main.c program
#define READ_EEPROM				8
#define EEPROM_STR				9
#define EEPROM_STR2				10
#define SEND_BYTE_RT_VALUES		11
#define SEND_BYTE_HEX_VALUES	12
#define SEND_INT_RT_VALUES		13
#define LCD_CLRSCR2				14
#define SHOW_EEPROM				15
#define PASSWORD_MODE			16
#define SET_NUM_ENTRY_MODE		17
#define DISPLAY_STR				18
#define DISPLAY_RTLABELS		19
#define DISPLAY_STATUSLABELS	20
#define DISPLAY_ELAPSED_TIME	21
#define DISPLAY_TEMP			22
#define RESET					23
#define SET_8X8_FONT			24
#define SET_6X8_FONT			25

// offsets into eeprom
#define RT_VALUES_OFFSET 1
#define STATUS_VALUES_OFFSET 14

#define START_ROW_STATUS 0
#define STATUS_ENGINE START_ROW_STATUS
#define STATUS_COOLING_FAN STATUS_ENGINE+1
#define STATUS_HEAD_LIGHTS STATUS_ENGINE+2
#define STATUS_BRIGHTS STATUS_ENGINE+3
#define STATUS_BRAKES STATUS_ENGINE+4
#define STATUS_RUNNING_LIGHTS STATUS_ENGINE+5
#define STATUS_BLOWER STATUS_ENGINE+6
#define STATUS_WIPERS STATUS_ENGINE+7

#define VARIOUS_MSG_OFFSET 21
#define STATUS_ON VARIOUS_MSG_OFFSET+4
#define STATUS_OFF VARIOUS_MSG_OFFSET+5
#define NO_MENUS 2

// start positions on screen
#define NUM_RT_LABELS 27
#define START_RT_VALUE_ROW 1
#define START_RT_VALUE_COL 0
#define ENDING_RT_VALUE_ROW 7
#define RT_VALUE_COL_WIDTH 19

#define NUM_STATUS_LABELS 7
#define START_STATUS_VALUE_ROW 1
#define START_STATUS_VALUE_COL 2

typedef struct params
{
	int rpm_mph_update_rate;	// update rates for LED displays
	int fpga_xmit_rate;
	int high_rev_limit;
	int low_rev_limit;
	int cooling_fan_on;
	int cooling_fan_off;
	int lights_on_value; // light sensor value to turn lights on 
	int lights_off_value; // light sensor value to turn lights off (should be > above)
	int adc_rate;
	int rt_value_select;	// 
	int lights_on_delay;
	int engine_temp_limit;
	int batt_box_temp;
	int test_bank;
	int password_timeout;
	int password_retries;
	int baudrate3;
}PARAM_STRUCT;

// FPGA commands
#define SET_FPGA_SEND_UPDATE_RATE 	0x01
#define SET_RPM_MPH_UPDATE_RATE		0x02
#define DTMF_TONE_ON 				0x03
#define DTMF_TONE_OFF 				0x04
#define SPECIAL_TONE_ON 			0x05
#define LCD_PWM 					0x06
#define TUNE_ON						0x07
#define TUNE_OFF					0x08
#define LOAD_TUNE					0x09
#define SHOW_DOWNLOAD				0x0A
#define ADC_CTL						0x0B
#define SET_ADC_RATE2				0x0C
#define SET_HIGH_REV_LIMIT 			0x0D
#define SET_LOW_REV_LIMIT 			0x0E
#define REV_LIMIT_OVERRIDE			0x0F
#define FUEL_PUMP_OVERRIDE			0x10
#define LCD_TEST_MODE2				0x11
#define MPH_RPM_SET_LED_BRIGHT		0x12
#define MPH_RPM_LED_BRIGHT			0x13
#define MPH_RPM_LED_DIM				0x14
#define MPH_RPM_LED_SET_RATIO		0x15
#define MPH_RPM_LED_SPEC_CMD		0x16

// params for lcd_pwm (screen dimmer)
#define PWM_OFF_PARAM					0x01 // off
#define PWM_ON_PARAM					0x1F // on
#define PWM_80DC_PARAM					0x1A // duty_cycle = 80%
#define PWM_75DC_PARAM					0x16 // duty_cycle = 75%
#define PWM_60DC_PARAM					0x12 // duty_cycle = 60%
#define PWM_50DC_PARAM					0x0E // duty_cycle = square wave
#define PWM_30DC_PARAM					0x0A // duty_cycle = 30%
#define PWM_25DC_PARAM					0x06 // duty_cycle = 25%
#define PWM_12DC_PARAM					0x02 // duty_cycle = 12%

#endif
