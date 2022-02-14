#ifndef MYTPYES_H
#define MYTPYES_H

typedef unsigned char UCHAR;
typedef unsigned int UINT;
typedef UCHAR* PUCHAR;
typedef unsigned long ULONG;

#define TRUE 1
#define FALSE 0

#define DATA_SIZE 500

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


#endif
