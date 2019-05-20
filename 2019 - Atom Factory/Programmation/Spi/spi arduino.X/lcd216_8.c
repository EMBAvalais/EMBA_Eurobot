////////////////////////////////////////////////////////////////////////////
////                             LCD216_8.C                             ////
////         Driver for common 2x16 LCD modules with data 8 bits        ////
////                                                                    ////
////  lcd_init()   Must be called before any other function.            ////
////                                                                    ////
////  lcd_putc(c)  Will display c on the next position of the LCD.      ////
////                     The following have special meaning:            ////
////                      \f  Clear display                             ////
////                      \n  Go to start of second line                ////
////                      \b  Move back one position                    ////
////                                                                    ////
////  lcd_gotoxy(x,y) Set write position on LCD (upper left is 1,1)     ////
////                                                                    ////
////  lcd_getc(x,y)   Returns character at position x,y on LCD          ////
////                                                                    ////
////////////////////////////////////////////////////////////////////////////
////   EMVS  Ecole des Metiers du Valais                                ////
////   Date:      05/06/2004                                            ////
////   Version:   1.0                                                   ////
////   Auteur:    Daniel Duay                                           ////
////////////////////////////////////////////////////////////////////////////

// As defined in the following structure the pin connection is as follows:
//     E0  rs
//     E1  rw
//     E2  enable
//     D0  D0
//     D1  D1
//     D2  D2
//     D3  D3
//     D4  D4
//     D5  D5
//     D6  D6
//     D7  D7
//

struct lcd_pin_map {                 // This structure is overlayed
           BOOLEAN rs;           // on to an I/O port to gain
           BOOLEAN rw;               // access to the LCD pins.
           BOOLEAN enable;               // The bits are allocated from
        } lcd;


#if defined(__PCH__)
 #byte lcd = 0xF84                // This puts the entire structure
#else
 #byte lcd = 0x09                 // on to port E (at address 9)
#endif

#define lcd_type 2                // 0=5x7, 1=5x10, 2=2 lines

#define set_tris_lcd(x) set_tris_d(x)  // port on Data

byte const LCD_READ = 0xFF;
byte const LCD_WRITE = 0x00;

BYTE const LCD_INIT_STRING[4] = {0x30 | (lcd_type << 2), 0xc, 1, 6};
                                  // These bytes need to be sent to the LCD
                                  // to start it up.
                                  // The following are used for setting
                                  // the I/O port direction register.



BYTE lcdline;

BYTE lcd_read_byte() {
      BYTE data;

      set_tris_lcd(LCD_READ);
      lcd.rw = 1;
      delay_cycles(1);
      lcd.enable = 1;
      delay_cycles(1);
      data = input_d();
      lcd.enable = 0;
      set_tris_lcd(LCD_WRITE);
      return(data);
}


void lcd_send_byte( BYTE address, BYTE n )
{
      lcd.rs = 0;
      while ( bit_test(lcd_read_byte(),7) ) ;
      lcd.rs = address;
      delay_cycles(1);
      lcd.rw = 0;
      delay_cycles(1);
      lcd.enable = 0;
      set_tris_lcd(LCD_WRITE);
      output_d (n);
      delay_cycles(1);
      lcd.enable = 1;
      delay_us(5);
      lcd.enable = 0;
}


void lcd_init() {
    BYTE i;

    lcd.rs = 0;
    lcd.rw = 0;
    lcd.enable = 0;
    delay_ms(15);
    for(i=0;i<=3;++i)
      {
       lcd_send_byte(0, LCD_INIT_STRING[i]);
       delay_us(5);
      }
}


void lcd_gotoxy( BYTE x, BYTE y) {
   BYTE address;

   switch(y) {
     case 1 : address=0x80;break;
     case 2 : address=0xC0;break;
     default: address=0x80;break;
   }
   address+=x-1;
   lcd_send_byte(0,address);
}

void lcd_putc( char c) {
   switch (c) {
     case '\f'   : lcd_send_byte(0,1);
                   lcdline=1;
                   delay_ms(10);
                   break;
     case '\n'   : lcd_gotoxy(1,++lcdline);
                   break;
     case '\b'   : lcd_send_byte(0,0x10);
                   break;
     default     : lcd_send_byte(1,c);
                   break;
   }
}

char lcd_getc( BYTE x, BYTE y) {
   char value;

    lcd_gotoxy(x,y);
    lcd.rs = 0;
    while ( bit_test(lcd_read_byte(),7) ) ;
    lcd.rs=1;
    value = lcd_read_byte();
    lcd.rs=0;
    return(value);
}



