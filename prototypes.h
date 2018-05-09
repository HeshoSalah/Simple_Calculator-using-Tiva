#include <stdint.h>

void delayMs(uint32_t n);
void delayUs(uint32_t n);
void LCD_command(unsigned char command);
void lcd_data(unsigned char data);
void LCD_init(void);
void keypad_init(void);
unsigned char keypad_getkey(void);
void store(uint32_t b);
void calculate_operand(uint8_t arr[],uint32_t c);
void error(void);
void intTochar(uint32_t y);
uint32_t charToint(uint8_t k);