#include <avr/io.h>
#include <util/delay.h>

void twi_init(){
  TWBR = 72;
  TWSR = ~((1 << TWPS0) | (1 << TWPS1));
  TWCR |= (1 << TWEN);
}

void twi_start(){
  
  TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
  
  while(!(TWCR & (1 << TWINT)));
}

void twi_write(uint8_t data){
  TWDR = data;

  TWCR = (1 << TWEN) | (1 << TWINT);

  while(!(TWCR & (1 << TWINT)));
}

void twi_stop(){

  TWCR = (1 << TWEN) | (1 << TWSTO) | (1 << TWINT);
}

void oled_command(uint8_t cmd){
  twi_start();
  twi_write(0x78);
  twi_write(0x00);
  twi_write(cmd);
  twi_stop();
}

void oled_data(uint8_t data){
  twi_start();
  twi_write(0x78);
  twi_write(0x40);
  twi_write(data);
  twi_stop();
}

void oled_init(void) {
    _delay_ms(100); 

    oled_command(0xAE); 

    oled_command(0x8D); 
    oled_command(0x14); 

    oled_command(0xAF); 
}

void oled_clear(){
  
  for(uint16_t i = 0 ; i < 1024 ; i++){
    oled_data(0x00);
  }
}



int main(void) {
    twi_init();
    oled_init();
    oled_clear();

    const uint8_t char_I[3] = {0x0, 0x7F, 0x0};
    const uint8_t* font_ptr = 0;
    font_ptr = char_I;
    for(uint8_t i = 0 ; i < 3 ; i++){
      oled_data(font_ptr[i]);
    }

    while(1) {
        
    }

   
    return 0;
}

  


  



