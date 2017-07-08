#include<avr/io.h>
#include<util/delay.h>
#include<string.h>
// Initialising LCD
void cmd()
{ 
 PORTC = 0x04;
 _delay_ms(5);
 PORTC =  0;
}

void dat()
{
 PORTC = 0x05;
 _delay_ms(5);
 PORTC = 0x01;
}
 
void splfn()
{ 
 int a[] = {0x01,0x06,0x38,0x0e,0x80};
 for(int i=0;i<strlen(a);i++)
 {
  PORTD = a[i];
  cmd();
 }
}
// Fn to print a integer on LCD
void disp_int(int x)
{
  int y=1;
  int a=x;
  while(a>9)
  {
   y = y*10;
   a = a/10;
  }
  while(y>0)
  {
   PORTD = ((x/y)+48);
   dat();
   x = x%y;
   y = y/10;
  }
}

 
int main()
{ 
 DDRC = DDRD = 0xff;
 DDRB = 0xff;
 PORTA = 255;
 splfn();
 char ch[] = "Total number is ";
 int c1=0,c2=0,c=0;
 while(1)
 {
 for(int i=0;i<strlen(ch);i++)
 { 
  PORTD = ch[i];
  dat();
 }
  if((PINA&1)==0)
  {
   while((PINA&2) != 0);
   if((PINA&2)==0)
   { 
    c++;
	c1=c;
	PORTB = c1;
	_delay_ms(500);
   }
   if(c1==3)
   {PORTB = 0xaa;
   _delay_ms(300);}
  }
  else if((PINA&2)==0)
  {
   while((PINA&1) != 0);
   if((PINA&1)==0)
   {
    c--;
	c2=c;
	PORTB = c2;
	_delay_ms(500);
   }
  }
 }
return 0;
}

