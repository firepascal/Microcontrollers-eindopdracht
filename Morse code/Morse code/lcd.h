/*
* lcd.h
*
* Created: 3-3-2021 14:56:33
*  Author: Pascal
*/

#ifndef LCD_H_
#define LCD_H_
#endif /* LCD_H_ */

void lcd_init(void);
void lcd_display_text(char *str);
void lcd_set_cursor(int position);
void lcd_clear_display(void);