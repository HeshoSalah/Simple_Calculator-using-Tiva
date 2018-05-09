//This project is made by:Hesham Salah Abdelfattah,Karim Amr,Mina Yousry Halim.

//the code is about making a simple calculator using an lcd and 4x4 keypad.
//the connection is (RS,RW,En)->(PA5,PA6,PA7) respectively and the remnained eight pins of the lcd to PB0->PB7.
//for the keypad the 4 pins of the rows to PE0->PE3 and the 4 pins of the columns to PD0->PD3. 

/*the RGB led should be lightened in blue when a number is pressed and turns off when a sign is pressed and again
turns on in blue when another input is pressed.Finally,if the result is calculated well it blinks the green led and any error
results in red led blinking*/

#include "TM4C123GH6PM.h"
#include <stdint.h>
#include "prototypes.h"
#include "math.h"


// these are general variables common used between all the functions. 
uint8_t sign=0;    //to store the input sign +,-,/,*
uint32_t i=0;      //index for the array of no[4]
uint8_t z=1;      // to check that no signs can come after each other ex; ++,+= and intialized with 1 to prevent begining with any sign.
uint8_t x=0;      // to calculate the operands.
uint8_t no[5];    //array to store the numbers of the operand
uint8_t key;      //to recieve the returned character
uint32_t sum;   // for the result.
uint32_t op=0;   //used in the operand calculation.


int main(void)
{

/* enable clock to GPIOF at clock gating control register */
SYSCTL->RCGCGPIO |= 0x20;
/* enable the GPIO pins for the LED (PF3, 2 1) as output */
GPIOF->DIR = 0x0E;
/* enable the GPIO pins for digital function */
GPIOF->DEN = 0x0E;
        
	      LCD_init();
        keypad_init();
      
	start:       LCD_command(1);    //clear the lcd.
               LCD_command(0x80); /* lcd cursor location */

        lcd_data('J');
        lcd_data('u');
        lcd_data('s');
        lcd_data('t');
        lcd_data(' ');
	      lcd_data('2');
	      lcd_data(' ');
        lcd_data('O');
        lcd_data('p');
        lcd_data('e');
        lcd_data('r');
				lcd_data('a');
        lcd_data('n');
        lcd_data('d');
        lcd_data('s');
        delayMs(3000);
        LCD_command(1);    //clear the lcd.

  while(1){
	     do{                          //to be sure that the user really entered a key.
           key= keypad_getkey();
           delayMs(200);   //wait for the debounce
				}while(key==0);
        
		switch(key){
                case '0':
                     lcd_data(key);        //firstly show the number.
        //secondly, store the number in an array to use it later in the calculation of the input operand      
                     no[i]=key;								
        //thirdly,increase the index of the array and zeroing the z again to enable entering a sign or the =    
                     i++; z=0;            
		                 GPIOF->DATA = 0x04;   //it turns on the blue led to inicate that an operand is input. 
                     break;
                case '1':
                     lcd_data(key);
                     no[i]=key;
                     i++; z=0;
								     GPIOF->DATA = 0x04;
                //key='-';     
								break;
                case '2':
                     lcd_data(key);
                     no[i]=key;
                     i++; z=0;
		                 GPIOF->DATA = 0x04;
                //key='=';     
								break;
                case '3':
                     lcd_data(key);
                     no[i]=key;
                     i++; z=0;
		                 GPIOF->DATA = 0x04;
                     break;
                case '4':                
                     lcd_data(key);
                     no[i]=key;
                     i++; z=0;
		                 GPIOF->DATA = 0x04;
                     break;
                case '5':        
                     lcd_data(key);
                     no[i]=key;
                     i++; z=0;
		                 GPIOF->DATA = 0x04;
								// key='-'; 
                     break;
                case '6':
                     lcd_data(key);
                     no[i]=key;
                     i++; z=0;
		                 GPIOF->DATA = 0x04;
                     break;
                case '7':
                     lcd_data(key);
                     no[i]=key;
                     i++; z=0;
		                 GPIOF->DATA = 0x04;
                     break;
                case '8':
                     lcd_data(key);
                     no[i]=key;
                     i++; z=0;
                     //store(op);
		                 GPIOF->DATA = 0x04;
                     break;
                case '9':
                     lcd_data(key);
                     no[i]=key;
                     i++; z=0;
		                 GPIOF->DATA = 0x04;
                     break;
                case '+':
                 //***** if z=1 that means that the previous pressed key was also a sign resulting in error********* 
                 if(z==0)     
                  {
                    calculate_operand(no,i-1);			//firstly calculate the operand stored in no[]
										store(op);
										lcd_data(key);              //show the new sign.
                     z++;                        //to prevent two signs from coming after each other
										 i=0;                        //Zeroing the index of the no[] again
                     sign=key;
                     GPIOF->DATA = 0x00;         //turns the blue led off when any sign is pressed
                     break;
                  }
                  else
                  {
                     error();    //void function to preview an "error" on the lcd
										goto start;  // go to the label start that erase the lcd again and preview hello starting the code again.
                    
                  }
                        
                case '-':
                  if(z==0)
                  {
                     calculate_operand(no,i-1);
										store(op);
                     lcd_data(key);
                     z++;
																				 i=0;                        //Zeroing the index of the no[] again

                     sign=key;
                     GPIOF->DATA = 0x00;
										//key='2'; 
                     break;
                  }
                  else
                  {
                     error();
										goto start;
                     
                  }
               case '*':
                  if(z==0)
                  {
                     calculate_operand(no,i-1);
										store(op);
                     lcd_data(key);
                     z++;
																				 i=0;                        //Zeroing the index of the no[] again

                     sign=key;
                     GPIOF->DATA = 0x00;
                     break;
                  }
                  else
                  {
                     error();
										goto start;
                     
                  }
               case '/':
                  if(z==0)
                  {
                     calculate_operand(no,i-1);
										store(op);
                     lcd_data(key);
                     z++;
										i=0;                        //Zeroing the index of the no[] again

										
                     sign=key;
                     GPIOF->DATA = 0x00;
                     break;
                  }
                  else
                  {
                     error();
										goto start;
                     
                  }
              case '=':
                 if(z==0)
                  {
                     calculate_operand(no,i-1);
                     switch(sign)
                     {
                     case '+':
                       sum=sum+op;
                       lcd_data('=');
										   intTochar(sum);
                       break;
                     case '-':
                       sum=sum-op;
                       lcd_data('=');
                       intTochar(sum);
                       break;
                     case '*':
                       sum=sum*op;
                       lcd_data('=');
                       intTochar(sum);
                       break;
                     case '/':
											 if(op==0)
											 {error();
											 goto start;}
                       sum=sum/op;
                       lcd_data('=');
                       intTochar(sum);
                       break;
                     }
                     GPIOF->DATA = 0x08;    //it turns on the green led when the result is calculated well.
										 delayMs(500);
                     GPIOF->DATA = 0x00;    //it turns off the green led. 
                     delayMs(500);
                     sign=0;
                     i=0; z++;
                     op=0;										 //zeroing the operand variable again
										 goto start;
                     
                   }
                   else
                   {
                     error();
                     op=0;      //zeroing the operand variable again
										 goto start;
                     
                   }
        }    
  }
}
//this function is used to show an error message on the lcd and turns the red led on and then off.
void error(void)
{

	     LCD_command(1);     //clear the screen
	     LCD_command(0x80); /* lcd cursor location:first location in the first row */
             delayMs(500);
	     GPIOF->DATA = 0x02;    //it turns on the red led. 
             delayMs(500);             
             GPIOF->DATA = 0x00;    //it turns off the red led. 
             delayMs(500);
             lcd_data('e');
             lcd_data('r');
             lcd_data('r');
             lcd_data('o');
             lcd_data('r');
             delayMs(1000);
             LCD_command(1);
        
}
//this function is used to calculate the operands.
void calculate_operand(uint8_t arr[],uint32_t c)
{ int t=c;
	int r;
  int g;
	for(x=0;x<=t;x++)
  {   
		 r=c;
		 g=1;      
	   while(r>0)
     {
        g=g*10;
	      if(r==0)
			     break;
        r--;
     }					
          op=op+charToint(arr[x])*g;
          if(c==0)
						break;
					c--;
				
   }
}
//this function to store the first operand then it zeroes the op variable again in order to use the calculate_operand again properly.
void store(uint32_t number)
{
      sum=number;    //storing the operand in variable named sum
      op=0;

}


/* delay n milliseconds (16 MHz CPU clock) */
void delayMs(uint32_t n)
{
int i, j;
for(i = 0 ; i < n; i++)
for(j = 0; j < 3180; j++)
{} /* do nothing for 1 ms */
}
/* delay n microseconds (16 MHz CPU clock) */
void delayUs(uint32_t n)
{
int i, j;
for(i = 0 ; i < n; i++)
for(j = 0; j < 3; j++)
{} /* do nothing for 1 us */
}
/* This function is called by the startup assembly code to perform system specific
initialization tasks. */
void SystemInit(void)
{
/* Grant coprocessor access */
/* This is required since TM4C123G has a floating point coprocessor */
SCB->CPACR |= 0x00F00000;
}
