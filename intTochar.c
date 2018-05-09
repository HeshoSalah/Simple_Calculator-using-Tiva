/* This function is used to convert the result from an integer type to character type in order to enable the printing
on the lcd using 'lcd_Data()'*/

#include <stdint.h>

void intTochar(uint32_t y)
{
	int tenthousands;
	int thousands;
	int cents;
	int tens;
	int ones;
	
if(y<=9){
	switch(y)
	{
		case 0:
	        lcd_data('0');
		      break;
		case 1:
	        lcd_data('1');
		      break;
		case 2:
	        lcd_data('2');
		      break;
		case 3:
	        lcd_data('3');
		      break;
		case 4:
	        lcd_data('4');
		      break;
		case 5:
	        lcd_data('5');
		      break;
		case 6:
	        lcd_data('6');
		      break;
		case 7:
	        lcd_data('7');
		      break;
		case 8:
	        lcd_data('8');
		      break;
		case 9:
	        lcd_data('9');
		      break;
	
	}
}
if(y<100 && y>=10)
{
   tens=y/10;
	intTochar(tens);     // Recursive Function
	 ones=y-(tens*10);
	intTochar(ones);
}
if(y<1000 && y>=100)
{
 cents=y/100;
	intTochar(cents);
 tens=(y-(cents*100))/10;
	intTochar(tens);
 ones=y-(cents*100)-(tens*10);
	intTochar(ones);
}
if(y<10000 && y>=1000)
{
 thousands=y/1000;
	intTochar(thousands);
	cents=(y-(thousands*1000))/100;
	intTochar(cents);
 tens=(y-(thousands*1000)-(cents*100))/10;
	intTochar(tens);
 ones=y-(thousands*1000)-(cents*100)-(tens*10);
	intTochar(ones);
}
if(y<100000 && y>=10000)
{
  tenthousands=y/10000;
	intTochar(tenthousands);
	thousands=(y-(tenthousands*10000))/1000;
	intTochar(thousands);
	cents=(y-(tenthousands*10000)-(thousands*1000))/100;
	intTochar(cents);
 tens=(y-(tenthousands*10000)-(thousands*1000)-(cents*100))/10;
	intTochar(tens);
 ones=y-(tenthousands*10000)-(thousands*1000)-(cents*100)-(tens*10);
	intTochar(ones);
}
}
