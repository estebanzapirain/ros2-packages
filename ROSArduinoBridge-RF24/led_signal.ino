/***************************************************************
  Signalling LED functions
   
   *************************************************************/


void BlinkLoop(){
  if ((millis() - last_blink) >= blinks_interval){
    led_toggle();
    pending_blinks--;
    last_blink = millis();
    Serial.println(last_blink);
    }
  if (pending_blinks <= 0){
    blinking = false;
    Serial.println(pending_blinks);
    }
  }
  
void led_toggle(){
  led_state = !led_state;
  digitalWrite(LED_PORT,led_state);
  }
