int write_serial2(UCHAR byte);
void printString2(char *myString);
UCHAR read_serial2(char *errmsg);
UCHAR read_serial3(char *errmsg);
void close_serial2(void);
int global_handle2;
int global_handle3;

int init_serial(void);
int init_serial2(void);
int init_serial3(int baudrate);
int write_serial(UCHAR byte);
int write_serial2(UCHAR byte);
int write_serial3(UCHAR byte);
void printString(const char myString[]);
UCHAR read_serial(char *errmsg);
//int read_serial_buff(UCHAR *buff, char *errmsg);
//int write_serial_buff(UCHAR *buff, char *errmsg);
void close_serial(void);
int global_handle;
void printHexByte(UCHAR byte);
char nibbleToHexCharacter(UCHAR nibble);

