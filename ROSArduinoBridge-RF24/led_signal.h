/***************************************************************
               Led Signal function definitions
   *************************************************************/

#define LED_PORT A0

bool blinking = false;
int pending_blinks = 0;
int blinks_interval = 0;
long last_blink = 0;
bool led_state = 0;

void BlinkLoop();
