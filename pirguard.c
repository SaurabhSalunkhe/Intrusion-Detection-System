#include<W79E2051_4051.h>//251Pin16,17,18,19
sbit RS = P1^3;     //lcd4 -> 15
sbit Enable=P1^2;   //lcd6 -> 14
#define LCD_PORT P1 // lcd11->16 lc12->17...lc14->19
sbit pir    =  P3^5; // Sensor Input from Pir Board
sbit indi   =  P3^4; // Indicator Led
sbit Siren 	=  P3^3; // Siren/Buzzer output
sbit Swch   =  P3^2; // Switch input
bdata char flag;	  // Flags Here vvvvvvvvvvvv
sbit armed	= flag^0;
void send_cmd(unsigned char);
void sndStr(unsigned char*);
void delayms(unsigned int);
void LCD_Init(void);void l1(void);void l2(void);
void delay(int );void shl(int);
void send_byte(unsigned char ch);
void sendString(unsigned char *str);
void initGsm();void action(); void bip(int n);
void send_byte(unsigned char ch);
void SrStr(unsigned char *str);
void InitSerial(void)
{	TMOD = 0x20;CKCON |= 0x10;	PCON |= 0x80; 
    TL1 = TH1 = 0xe8;	TR1 = 1;}				
void initGsm(){SrStr("AT\r\n");delay(700);
 SrStr("AT+CMGF=1\n\r");delay(700);}
void send_byte(unsigned char ch) // Serial Routines
{   TI = 0; SBUF = ch; while(!TI);delay(5);}
void SrStr(unsigned char *str)
{ 	while(*str != '\0')	send_byte(*str++);}

void main()
{ LCD_Init(); P1=0x00; indi=Siren=Swch=armed=0;
 l1();sndStr("PirGuard Project");
 l2();sndStr("By Group of :-  "); shl(2);
 InitSerial();delay(470);SCON = 0x52; bip(34);bip(16);
 l1();sndStr("Sarvesh, Saurabh");
 l2();sndStr("   And Omkar    ");shl(2);initGsm();

rearm: l1();sndStr("Press Arm Switch");
    l2();sndStr("Now to Activate ");shl(2);bip(25);bip(1);

ream:if (Swch){ delay(200); 
        l1();sndStr("Pir Guard Armed "); 
        l2();sndStr("Sensing On Now!");shl(1);armed=1;bip(25);
    SrStr("AT+CMSS=1\,");SrStr("\"9930499095\"\r\n");
    SrStr("AT+CMSS=1\,");SrStr("\"9867624994\"\r\n");
    delay(3000);// Time delay for Closing Shutter.
pir=0;
sss:if(pir) { indi=1; action(); indi=0; armed=0;goto rearm;}
            pir=0; goto sss;
              } 
    delay(20);goto ream;
}
void l1(){send_cmd(0x80);}// cursor to beg of 1st line, 
void l2(){send_cmd(0xC0);} // cursor @ beg of 2nd line
void shl(int n){int i;for(i=0;i<n;i++) send_cmd(0x18);}
void LCD_Init(){ P1 = 0x00;delayms(15);
 send_cmd(0x30);delayms(8);send_cmd(0x30);delayms(2);
 send_cmd(0x30);delayms(2);send_cmd(0x02);delayms(2);
 send_cmd(0x28);delayms(2);send_cmd(0x0C);delayms(2);
 send_cmd(0x01);delayms(2);send_cmd(0x06);delayms(2);}
void send_cmd(unsigned char Command)
{  unsigned char ch=0;
 LCD_PORT &= 0x00; LCD_PORT =(Command);
 RS = 0;  Enable = 1; delayms(2);
 Enable = 0; delayms(2); LCD_PORT &= 0x00;
 LCD_PORT =(Command<<4); RS = 0; Enable = 1; 
 delayms(2); Enable = 0; delayms(2); }
void sndStr(unsigned char *String)
{unsigned char i=0, ch=0, temp=0;
while(String[i]!='\0')
{ temp = String[i++];
 LCD_PORT &= 0x00; LCD_PORT = (temp);
 RS = 1; Enable = 1; delayms(2);
 Enable = 0; delayms(1); LCD_PORT &= 0x00;
 LCD_PORT = ((temp<<4)); RS = 1; Enable = 1;  
 delayms(2); Enable = 0; delayms(1);
if(i>=16) send_cmd(0x1C);delayms(10);}return; }
void delayms(unsigned int value)
{ unsigned int i,j; for(i=0;i<=value;i++)
 {  for(j=0;j<84;j++)  ;  }}

void action(){ l1();sndStr("Intrusion Detctd");
 l2();sndStr("Notifying Master");shl(1);
bip(150);bip(350);bip(150);
SrStr("ATD9930499095;\r\n");
delay(1200);SrStr("ATH\r\n");
SrStr("AT+CMSS=2\,");SrStr("\"9930499095\"\r\n");
SrStr("AT+CMSS=2\,");SrStr("\"8097567824\r\n");
l1();sndStr("SMS Notice is   ");
 l2();sndStr("Sent to Master ");//shl(1);
while(Swch==0)bip(16);delayms(100);}

void bip(int n) {  //Make Noise & Call Thru GSM
Siren = 1;delay(n+100);Siren = 0;delay(n);}
void delay(int count)    //Function to provide delay
{   int i,j;
    for(i=0;i<count;i++)    for(j=0;j<2475;j++);}


