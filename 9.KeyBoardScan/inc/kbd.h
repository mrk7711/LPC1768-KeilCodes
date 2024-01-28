#ifndef kbd_H_
#define kbd_H_

#include <stdint.h>

#define  KBD_PIN_Part         0
#define  KBD_Port             2

void    kbd_init(void);
uint8_t kbd_read(void);


#endif
