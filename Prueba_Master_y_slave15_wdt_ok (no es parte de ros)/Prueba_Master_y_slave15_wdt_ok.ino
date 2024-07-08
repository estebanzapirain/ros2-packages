//arduino pro mini 8 mhz
#include <avr/wdt.h>
#include "RF24Network.h"
#include "RF24.h"
#include "RF24Mesh.h"
#include <SPI.h>
//Include eeprom.h for AVR (Uno, Nano) etc. except ATTiny
#include <EEPROM.h>
#include <MsTimer2.h>
#include <avr/boot.h>
#include <AESLib.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define DIP1  A2 
#define DIP2  A3
#define DIP3  A4
#define DIP4  A5

#define ONE_WIRE_BUS 4
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
/***** Configure the chosen CE,CS pins *****/
RF24 radio(7,8);
RF24Network network(radio);
RF24Mesh mesh(radio,network);

uint8_t leer_dipswitch(void)
{
  uint8_t DIP1_val, DIP2_val, DIP3_val, DIP4_val;     // Variables donde se guardan los estados del dip switch.
  uint8_t CANTIDAD_ESCLAVOS;
  
  DIP1_val = digitalRead(DIP1);           // Leo el estado del dip switch
  DIP2_val = digitalRead(DIP2);
  DIP3_val = digitalRead(DIP3);
  DIP4_val = digitalRead(DIP4);
  
  CANTIDAD_ESCLAVOS = (DIP4_val << 3) | (DIP3_val << 2) | (DIP2_val << 1) | DIP1_val;   
  return CANTIDAD_ESCLAVOS;
} 

uint8_t nodeID;
uint8_t ID_destino=0;
uint32_t displayTimer = 0;
boolean enviar=false;
char data[128];
String inputString="";
int identif=1;
String mensaje="";
boolean existe_destino= false;
uint8_t num_ser[16];
boolean coincide=true;
char tipo_mensaje;

volatile uint32_t tiempo = 0;
uint32_t periodo=0;
volatile uint8_t int2_flag = 0, int3_flag = 0;
//char nombre_dispositivo[32];
//char direccion_app[32];
char nombre_dispositivo[36];
char direccion_app[36];
//String nombre_dispositivo="Device Name";
//String direccion_app="PlayStore Link";
void setup() {
  wdt_disable();
  pinMode(DIP1,INPUT_PULLUP);
  pinMode(DIP2,INPUT_PULLUP);
  pinMode(DIP3,INPUT_PULLUP);
  pinMode(DIP4,INPUT_PULLUP);
  nodeID = leer_dipswitch();
  Serial.begin(115200);

  MsTimer2::set(10, timer2_isr); // 10ms period
  MsTimer2::stop();
  EEPROM.get(30, nombre_dispositivo);
  EEPROM.get(100, direccion_app);

  
  long leido;
  EEPROM.get(20, leido);
  if ((leido>115200)|| (leido < 0))
  {
    Serial.begin(9600);
  }
  else
  {
    Serial.begin(leido);
  }
  
  // Seteo el ID del nodo. 0 es maestro
  mesh.setNodeID(nodeID);
  Serial.println(mesh.getNodeID());


  //Serial.println("Numero de serie: ");
  char campo[3]={'\0','\0','\0'};
  for (uint8_t i = 14; i < 24; i += 1)  {
    sprintf(campo,"%02X",boot_signature_byte_get(i));
    num_ser[i-14]=boot_signature_byte_get(i);
  }
  // completo con 0      
  for (uint8_t i = 10; i < 16; i += 1)  {
    num_ser[i]=0;
  }
  const uint8_t key[] = {5,7,6,3,4,9,0,7,0,0,15,3,6,8,4,0};
  aes128_enc_single(key, num_ser); //encripto
  
//  Serial.println("encrypted:");
  for (uint8_t i = 0; i < 16; i += 1)  {
    sprintf(campo,"%02X",num_ser[i]);
//    Serial.print(campo);
  }
//  Serial.println();

//  Serial.print("Almacenado en eeprom: ");
  for (int8_t i= 0; i<16;i++)
  {
    uint8_t value = EEPROM.read(i);
    sprintf(campo,"%02X",value);
//    Serial.print(campo);
    if (num_ser[i]!= value)
    {
      coincide=false;
    }
  }
//  Serial.println();
        
  if (coincide==false)
  {
    
    Serial.println("Product:");
    char campo[3]={'\0','\0','\0'};
  
    for (uint8_t i = 14; i < 24; i += 1)  {
      
      sprintf(campo,"%02X",boot_signature_byte_get(i));
      Serial.print(campo);
    }
    Serial.println();
    Serial.println(F("Enter the code"));
    Serial.println(F("format: PASSxx.."));
  }



  if (nodeID==0)
  {
    delay(3000);
  }
  
  // Connect to the mesh
  if (coincide==true)
  {
    mesh.begin();
  }

  int est = EEPROM.read(24);
  if (est==1)
  {
    pinMode(2, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(2), int2_isr, FALLING);
  }
  est = EEPROM.read(25);
  if (est==1)
  {
    pinMode(3, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(3), int3_isr, FALLING);
  }
  periodo=millis();
  wdt_enable(WDTO_4S);
}

void loop() {
wdt_reset();    
if (coincide==true) //clave
 {
  // Esta funcion actualiza la red
  mesh.update();
  
  if (nodeID==0)
  {
    mesh.DHCP();
  }
  else
  {
    
    if (millis() - periodo >= 2000)    // Espero 2 segundos...
    {
      if ( ! mesh.checkConnection() ) {
            mesh.renewAddress();
          } 
          periodo=millis();
     }
  }
  
  // Leo datos recibidos
  if(network.available()){
    RF24NetworkHeader header;
    network.peek(header);
    tipo_mensaje=header.type;
    network.read(header,&data,sizeof(data));

    //if (nodeID!=0) // si es esclavo y recibo datos por radio
    //{
        convertir_a_string();
        mensaje=mensaje.substring(0,mensaje.length());
        boolean a = decodificar_comandos_radio();
          //Serial.println(a);
          
        if (a==false) //si no es comando conocido, sacar el dato por puerto serie
        {
          if (nodeID!=0)
          {
            Serial.println(mensaje); // era Serial.print(mensaje);
          }
          else
          {
            Serial.println(data);
          }
        }
        //-------------fin de agregado
        mensaje="";
  
    //}
    //else  //si es maestro
    //{
    //  Serial.println(data);
    //}
    
    
    for (uint8_t i=0;i<128;i++)
    {
      data[i]='\0';
    }
  }

  if (enviar==true)
   {
    if (nodeID==0)
    {
      //identif=1;
      analizar_comandos_master();
      inputString="";
      
      existe_destino= false;
      //mesh.update();
      
      for(int j=0; j<mesh.addrListTop; j++)
              {
                //Serial.print(mesh.addrList[j].nodeID);
                //Serial.print(" identif:");
                //Serial.println(identif);
                if (mesh.addrList[j].nodeID == identif) // si existe el destino
                {
                    //Serial.println("existe");
                    existe_destino= true;
                }
                
              }
        
    }
    else
    {
      inputString="";
      identif=0;
      existe_destino= true;
    }
    

    if (existe_destino == true)
    {
      if (nodeID == 0)  // Si es maestro...
      {
        mesh.write(&data, 'M', sizeof(data),identif);
        existe_destino = false;
      }
      else // Si es esclavo...
      {
        if (ID_destino != 0)
        {
          identif=ID_destino;
        }
        if (!mesh.write(&data, 'M', sizeof(data),identif)) {
          // Si falla el envio, chequeo la conexion a la red
          if ( ! mesh.checkConnection() ) {
            // Renuevo la direccion
            //Serial.println("Renewing Address");
            mesh.renewAddress();
          } /*else {
            Serial.println("Send fail, Test OK");
          }*/
        }// else Serial.println("OK");
        existe_destino=false;
      }
    }
    enviar=false;
   }

    if (nodeID!=0) // si es esclavo
    {
        if (int2_flag == 1)   // Si se disparo la interrupcion 2...
        {
          if (millis() - tiempo >= 70)    // Espero 70 milisegundos...
          {
             if (digitalRead(2) == 0)     // Si despues de ese tiempo, el pin sigue en bajo...
             {
                int2_flag = 0;            // Limpio la bandera de interrupcion 2
                //Serial.println("Interrupcion 2");
                //envio mesaje
                char int2_str[11] = {'I','D','0','1','i','n','t','2','\n','\r','\0'};
                char idslave[3]={'\0','\0','\0'};
                sprintf(idslave,"%02d",nodeID);
                int2_str[2]=idslave[0];
                int2_str[3]=idslave[1];
                if (!mesh.write(&int2_str, '1', sizeof(int2_str))) {
           
                    if ( ! mesh.checkConnection() ) {
                      //radio.powerDown();
                      //radio.powerUp();
                      mesh.renewAddress();
                    } 
                    
                  }
             }
          }
        
      }
    
      if (int3_flag == 1)   // Si se disparo la interrupcion 3...
      {
        if (millis() - tiempo >= 70)    // Espero 70 milisegundos...
        {
           if (digitalRead(3) == 0)     // Si despues de ese tiempo, el pin sigue en bajo...
           {
              int3_flag = 0;            // Limpio la bandera de interrupcion 2
              //Serial.println("Interrupcion 3");
              //envio mesaje
    
              char int3_str[11] = {'I','D','0','1','i','n','t','3','\n','\r','\0'};
              char idslave[3]={'\0','\0','\0'};
              sprintf(idslave,"%02d",nodeID);
              int3_str[2]=idslave[0];
              int3_str[3]=idslave[1];
              if (!mesh.write(&int3_str, '1', sizeof(int3_str))) {
         
                  if ( ! mesh.checkConnection() ) {
     
                    mesh.renewAddress();
                  } 
                  
                }
              
           }
        }
      }

    }
    else // si es maestro
    {
      if (int2_flag == 1)   // Si se disparo la interrupcion 2...
        {
          if (millis() - tiempo >= 70)    // Espero 70 milisegundos...
          {
             if (digitalRead(2) == 0)     // Si despues de ese tiempo, el pin sigue en bajo...
             {
                int2_flag = 0;            // Limpio la bandera de interrupcion 2
                //Serial.println("Interrupcion 2");
                Serial.println(F("ID00Int2"));
             }
          }
        }

        
        if (int3_flag == 1)   // Si se disparo la interrupcion 3...
        {
          if (millis() - tiempo >= 70)    // Espero 70 milisegundos...
          {
             if (digitalRead(3) == 0)     // Si despues de ese tiempo, el pin sigue en bajo...
             {
                int3_flag = 0;            // Limpio la bandera de interrupcion 2
                //Serial.println("Interrupcion 2");
                Serial.println(F("ID00Int3"));
             }
          }
        }
    }
   
  }
  
}

void analizar_comandos_master(void)
{
  //Serial.println(inputString);
  if (inputString.substring(0,2)=="ID")
      {
            String ID_str = inputString.substring(2,4);
            identif = ID_str.toInt();
                     
            //String total = mensaje.substring(4,mensaje.length()+1);
            int8_t largo = inputString.length();
            for (int i=4;i<largo;i++)
            {
              data[i-4]=inputString.charAt(i);
            }
            data[largo-4]='\0';
            //Serial.println(data);
            
      }
}

void convertir_a_string(void) //devuelve String mensaje
{
    mensaje="";
    int tam = sizeof(data);
  
    for (int i=0;i<tam-1;i++)
      {
        char theChar = data[i];
        mensaje.concat(theChar);
      }
 // Serial.println(mensaje);
}


void serialEvent() {
  while (Serial.available()) {
    MsTimer2::start();
    char inChar = (char)Serial.read(); 
    inputString += inChar;

  }
}

void timer2_isr(void)
{
    //if (inChar == '\n') {
      //Serial.println("int");
      //Serial.println(inputString);
      MsTimer2::stop();
      //Serial.println(inputString);
      decodificar_comandos();
      //inputString = "";
      
    //} 

}

void convertir_a_vector(void)
{
  if (nodeID!=0) // si es esclavo
  {
    data[0]='I';
    data[1]='D';
    char idslave[3]={'\0','\0','\0'};
    sprintf(idslave,"%02d",nodeID);
    data[2]=idslave[0];
    data[3]=idslave[1];
    int8_t largo = inputString.length();
  
    
    for (int i=4;i<largo+4;i++)
    {
      data[i]=inputString.charAt(i-4);
    }
    data[largo+4]='\0';
  }
  else
  {
    int8_t largo = inputString.length();
    for (int i=0;i<largo;i++)
    {
      data[i]=inputString.charAt(i);
    }
    data[largo]='\0';
  }
}

void decodificar_comandos(void)
{
  Serial.println(inputString.substring(0,4));
  if (inputString.substring(0,4)=="BAUD")
  {
    int largo = inputString.length();
    String baud = inputString.substring(4,largo);
    //int velo = baud.toInt();
    long velo = baud.toInt();
    Serial.print("BAUD");
    Serial.println(velo);
    
    EEPROM.put(20, velo);
    //long leido;
    //EEPROM.get(20, leido);
    Serial.println("Restart");
    inputString="";
    //Serial.print("Leido de eeprom: ");
    //Serial.println(leido);
    //Serial.begin(velo);
    
  } else if (inputString.substring(0,4)=="PASS")
  {
    Serial.println("PASS");  
    char campo[3]={'\0','\0','\0'};
    Serial.print("clave leida: ");
    for (uint8_t i = 4; i < 36; i += 2)  {
      
      campo[0]=inputString.charAt(i);
      campo[1]=inputString.charAt(i+1);
      Serial.print(campo);

      int d = StrToHex(campo);
      
      EEPROM.write((i-4)/2, d);

      
      //Serial.print(campo);
      //Serial.print(" StrToHex: ");
      //Serial.println(d,HEX);
      
    }
    inputString="";
    Serial.print("OK");
    //Serial.println();
  }
  else if (inputString.substring(0,6)=="WRDESC") // escribe descriptor 
  {
    String desc = inputString.substring(6);
    uint8_t largo = desc.length();
    uint8_t i;
    for (i= 30; i<30+largo;i++)
    {
      EEPROM.write(i,desc.charAt(i-30));
    }
    EEPROM.write(i,'\0');
    //EEPROM.put(30, desc);
    Serial.println("OK");
    inputString="";
  }
  else if (inputString.substring(0,6)=="RDDESC") // escribe descriptor 
  {
    //String desc = inputString.substring(6);
    for (uint8_t i= 30; i<62;i++)
    {
      nombre_dispositivo[i-30]=EEPROM.read(i);
    }
    inputString="";
    Serial.println(nombre_dispositivo);
  }
  else if (inputString.substring(0,6)=="WRAPPL") // escribe link a app de playstore  
  {
    String appl = inputString.substring(6);
    uint8_t largo = appl.length();
    uint8_t i;
    for (i= 100; i<100+largo;i++)
    {
      EEPROM.write(i,appl.charAt(i-100));
    }
    EEPROM.write(i,'\0');
    Serial.println("OK");
    inputString="";
  }
  else if (inputString.substring(0,6)=="RDAPPL") // lee link a app de playstore  
  {
    //Serial.println("entra");
    for (uint8_t i= 100; i<132;i++)
    {
      direccion_app[i-100]=EEPROM.read(i);
    }
    inputString="";
    Serial.println(direccion_app);
    
  }
      
    else if (nodeID!=0) // si es esclavo
    {
      if (inputString.substring(0,4)=="IDEN")   // Comando de identificacion
      {
        char idslave[3]={'\0','\0','\0'};
        sprintf(idslave,"%02d",nodeID);
        Serial.print("Slave_#");
        Serial.println(idslave);
        inputString="";
        //Serial.println("NRF24L01_Slave"); 
      } else if (inputString.substring(0,2)=="ID")
            {
              //Serial.println(inputString);
              String ID_str = inputString.substring(2,4);
              ID_destino = ID_str.toInt(); // destino

              if (ID_destino!=nodeID)
              {
                  char idslave[3]={'\0','\0','\0'};
                  sprintf(idslave,"%02d",nodeID);
                  //inputString.setCharAt(2,idslave[0]);
                  //inputString.setCharAt(3,idslave[1]);
                  int8_t largo = inputString.length();
        
                  data[0]='I';
                  data[1]='D';
                  data[2]=idslave[0];
                  data[3]=idslave[1];
                  //Serial.println(idslave);
                  for (int i=4;i<largo;i++)
                  {
                    data[i]=inputString.charAt(i);
                  }
                  
                  data[largo]='\0';
                  enviar=true;
                  //Serial.println(data);
              }
              else
              {
                decodificar_comandos_locales('S');
              }
              
            }
            else
            {
              convertir_a_vector();  //devuelve data
              ID_destino=0;
              enviar=true;
            }
    }
    else //si es maestro
    {
      if (inputString.substring(0,4)=="IDEN")   // Comando de identificacion
      {
        Serial.println("Master");
        inputString="";
      }
      else if (inputString.substring(0,4)=="LIST")   // Comando para lista de esclavos conectados
      {
        char list_str[5] = {'I','D','0','1','\0'};
    
        for(int i=0; i<mesh.addrListTop; i++){
          char conv1_str[3]={'\0','\0','\0'};
          sprintf(conv1_str,"%02d",mesh.addrList[i].nodeID);
           list_str[2]=conv1_str[0];
           list_str[3]=conv1_str[1];
           Serial.println(list_str);
        }  
        inputString="";
      }
      else if (inputString.substring(0,4)=="ID00")
      {
        decodificar_comandos_locales('M');
      }

      
      else
      {
        
        convertir_a_vector();  //devuelve data
        ID_destino=0;
        enviar=true;
      }
    }

}

void decodificar_comandos_locales(char tipo)
{
    if (tipo=='M')
    {
        if (inputString.substring(4,8)=="INT2")    // Activo interrupcion 2
        {
          pinMode(2, INPUT_PULLUP);
          attachInterrupt(digitalPinToInterrupt(2), int2_isr, FALLING);
          EEPROM.write(24,1);
          Serial.println(F("ID00INT2"));
        }
        if (inputString.substring(4,10)=="NOINT2")    // Desactivo interrupcion 2
        {
          detachInterrupt(digitalPinToInterrupt(2));
          int2_flag = 0;
          EEPROM.write(24,0);
          Serial.println(F("ID00NOINT2")); 
        }
        if (inputString.substring(4,8)=="INT3")      // Activo interrupcion 3
        {
          pinMode(3, INPUT_PULLUP);
          attachInterrupt(digitalPinToInterrupt(3), int3_isr, FALLING);
          EEPROM.write(25,1);
          Serial.println(F("ID00INT3"));
          //Serial.println("Int 3 activada");
        }
        if (inputString.substring(4,10)=="NOINT3")    // Desactivo interrupcion 3
        {
          int3_flag = 0;
          detachInterrupt(digitalPinToInterrupt(3));
          EEPROM.write(25,0);
          Serial.println(F("ID00NOINT3"));             
        }
    }
        if (inputString.substring(4,8)=="DIN2")    // LEER Pin 2
        {
          pinMode(2, INPUT_PULLUP);
          int pin=digitalRead(2);
          //Serial.println("aca");
          if (pin==0)
          {
            Serial.print(inputString.substring(0,8));
            Serial.println("0");
            //Serial.println(F("ID00DIN20"));
            
          }
          else
          {
            Serial.print(inputString.substring(0,8));
            Serial.println("1");
            //Serial.println(F("ID00DIN21"));
          }
        }
        if (inputString.substring(4,8)=="DIN3")    // LEER Pin 3
        {
          pinMode(3, INPUT_PULLUP);
          int pin=digitalRead(3);
          if (pin==0)
          {
            //Serial.println(F("ID00DIN30"));
            Serial.print(inputString.substring(0,8));
            Serial.println("0");
          }
          else
          {
            //Serial.println(F("ID00DIN31"));
            Serial.print(inputString.substring(0,8));
            Serial.println("1");
          }
        }
        if (inputString.substring(4,9)=="DIO5H")    // Pin 5 en alto
        {
          pinMode(5, OUTPUT);
          digitalWrite(5, HIGH);
          Serial.println(inputString.substring(0,9));
          //Serial.println(F("ID00DIO5H"));
        }
        if (inputString.substring(4,9)=="DIO5L")    // Pin 5 en bajo
        {
          pinMode(5, OUTPUT);
          digitalWrite(5, LOW);
          Serial.println(inputString.substring(0,9));
          //Serial.println(F("ID00DIO5L"));
        }
        if (inputString.substring(4,9)=="DIO6H")    // Pin 6 en alto
        {
          pinMode(6, OUTPUT);
          digitalWrite(6, HIGH);
          //Serial.println(F("ID00DIO6H"));
          Serial.println(inputString.substring(0,9));
        }
        if (inputString.substring(4,9)=="DIO6L")    // Pin 6 en bajo
        {
          pinMode(6, OUTPUT);
          digitalWrite(6, LOW);
          //Serial.println(ID00DIO6L); 
          //Serial.println(F("ID00DIO6L"));
          Serial.println(inputString.substring(0,9));
        }
        if (inputString.substring(4,9)=="PWM09")    // PWM 9
        {
          char pwm9_str[15] = {'I','D','0','0','P','W','M','0','9','0','0','0','\r','\n','\0'};
          pwm9_str[9] = inputString.charAt(9);
          pwm9_str[10] = inputString.charAt(10);
          pwm9_str[11] = inputString.charAt(11);
      
          char pwm9_val[4] = {pwm9_str[9],pwm9_str[10],pwm9_str[11],'\0'};
          int val = atoi(pwm9_val);
          analogWrite(9,val);
          //Serial.print(pwm9_str);
          Serial.println(inputString.substring(0,9));
        }
        if (inputString.substring(4,9)=="PWM10")    // PWM 10
        {
          char pwm10_str[15] = {'I','D','0','0','P','W','M','1','0','0','0','0','\r','\n','\0'};
          pwm10_str[9] = inputString.charAt(9);
          pwm10_str[10] = inputString.charAt(10);
          pwm10_str[11] = inputString.charAt(11);
      
          char pwm10_val[4] = {pwm10_str[9],pwm10_str[10],pwm10_str[11],'\0'};
          int val = atoi(pwm10_val);
          analogWrite(10,val);
          //Serial.print(pwm10_str);
          Serial.println(inputString.substring(0,9));
        }
        if (inputString.substring(4,7)=="AN0")
        {
          //char an0_str[14] = {'I','D','0','0','A','N','0','1','0','2','3','\r','\n','\0'};
          //char an0_str[14] = {'I','D','0','0','A','N','6','1','0','2','3','\n','\r','\0'};
          int conv = analogRead(A0);
          //int conv = analogRead(A6);
          char conv_str[5]={'\0','\0','\0','\0','\0'};
          sprintf(conv_str,"%04d",conv);
          //an0_str[7] = conv_str[0];
          //an0_str[8] = conv_str[1];
          //an0_str[9] =  conv_str[2];
          //an0_str[10] = conv_str[3];
          //Serial.print(an0_str);
          Serial.print(inputString.substring(0,7));
          Serial.println(conv_str);
        }
        if (inputString.substring(4,7)=="AN1")
        {
          //char an0_str[14] = {'I','D','0','0','A','N','1','1','0','2','3','\r','\n','\0'};
          int conv = analogRead(A1);
          //char an0_str[14] = {'I','D','0','0','A','N','7','1','0','2','3','\n','\r','\0'};
          //int conv = analogRead(A7);
          char conv_str[5]={'\0','\0','\0','\0','\0'};
          sprintf(conv_str,"%04d",conv);
          //an0_str[7] = conv_str[0];
          //an0_str[8] = conv_str[1];
          //an0_str[9] =  conv_str[2];
          //an0_str[10] = conv_str[3];
          //Serial.print(an0_str);
          Serial.print(inputString.substring(0,7));
          Serial.println(conv_str);
        }
        if (inputString.substring(4,8)=="TEMP")    // Temp
        {
          //char temp_str[14] = {'I','D','0','0','T','E','M','P','0','0','0','\r','\n','\0'};
          sensors.begin();
          sensors.requestTemperatures(); // Send the command to get temperatures
          int temperatura = sensors.getTempCByIndex(0);
      
          char conv1_str[4]={'\0','\0','\0','\0'};
          sprintf(conv1_str,"%03d",temperatura);
          //temp_str[8] = conv1_str[0];
          //temp_str[9] = conv1_str[1];
          //temp_str[10] = conv1_str[2];
          //Serial.print(temp_str);
          Serial.print(inputString.substring(0,8));
          Serial.println(conv1_str);
        }
        
        inputString="";
}

int StrToHex(char str[])
{
  return (int) strtol(str, 0, 16);
}

bool decodificar_comandos_radio(void)
{
  boolean b = false;
  char idslave[3]={'\0','\0','\0'};
  char id_destino[3]={'\0','\0','\0'};
  uint8_t id_destino_num=0;
  sprintf(idslave,"%02d",nodeID);
  if (mensaje.substring(0,2)== "ID")
  {
    //Serial.print("mensaje: ");
    //Serial.println(mensaje);
    id_destino[0]=mensaje.charAt(2);
    id_destino[1]=mensaje.charAt(3);
    id_destino_num=atoi(id_destino);
    //Serial.println(mensaje.substring(4,8));
    //mensaje=mensaje.substring(4);
    
  }
  //Serial.println(tipo_mensaje);
  if (tipo_mensaje=='M')
  {
  //Serial.println(tipo_mensaje);
  //Serial.println(mensaje.substring(5,10));
  if (mensaje.substring(0,4)=="INT2")    // Activo interrupcion 2
  {
    pinMode(2, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(2), int2_isr, FALLING);
    EEPROM.write(24,1);
    //Serial.println("Int 2 activada");
    char int2_str[9] = {'I','D','0','1','I','N','T','2','\0'};
    int2_str[2]=idslave[0];
    int2_str[3]=idslave[1];
    if (!mesh.write(&int2_str, '1', sizeof(int2_str),id_destino_num)) {
  
        if ( ! mesh.checkConnection() ) {

          mesh.renewAddress();
        } 
    }
    b=true;
  }
  else if (mensaje.substring(0,6)=="NOINT2")    // Desactivo interrupcion 2
  {
    detachInterrupt(digitalPinToInterrupt(2));
    EEPROM.write(24,0);
    int2_flag = 0;
    char noint2_str[11] = {'I','D','0','1','N','O','I','N','T','2','\0'};
    noint2_str[2]=idslave[0];
    noint2_str[3]=idslave[1];
    if (!mesh.write(&noint2_str, 'R', sizeof(noint2_str),id_destino_num)) {
        if ( ! mesh.checkConnection() ) {
          mesh.renewAddress();
        } 
    }
    b=true;
  }
    else if (mensaje.substring(0,4)=="INT3")    // Activo interrupcion 3
  {
    pinMode(3, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(3), int3_isr, FALLING);
    EEPROM.write(25,1);
    //Serial.println("Int 2 activada");
    char int3_str[9] = {'I','D','0','1','I','N','T','3','\0'};
    int3_str[2]=idslave[0];
    int3_str[3]=idslave[1];
    if (!mesh.write(&int3_str, 'R', sizeof(int3_str),id_destino_num)) {
  
        if ( ! mesh.checkConnection() ) {

          mesh.renewAddress();
        } 
    }
    b=true;
  }
  else if (mensaje.substring(0,6)=="NOINT3")    // Desactivo interrupcion 3
  {
    detachInterrupt(digitalPinToInterrupt(3));
    EEPROM.write(25,0);
    int3_flag = 0;
    char noint3_str[11] = {'I','D','0','1','N','O','I','N','T','3','\0'};
    noint3_str[2]=idslave[0];
    noint3_str[3]=idslave[1];
    if (!mesh.write(&noint3_str, 'R', sizeof(noint3_str),id_destino_num)) {
        if ( ! mesh.checkConnection() ) {
          mesh.renewAddress();
        } 
    }
    
    b=true;
  }


  else if (mensaje.substring(0,4)=="DIN2" || mensaje.substring(4,8)=="DIN2")    // LEER Pin 2
  {
    //Serial.print("entro, destino: ");
    //Serial.println(id_destino_num);
    pinMode(2, INPUT_PULLUP);
    
    char din2_str[10] = {'I','D','0','1','D','I','N','2','0','\0'};
    din2_str[2]=idslave[0];
    din2_str[3]=idslave[1];
    bool d=digitalRead(2);
    if (d==true)
    {
      din2_str[8]= '1';
    }
    else
    {
      din2_str[8]= '0';
    }
    if (!mesh.write(&din2_str, 'R', sizeof(din2_str),id_destino_num)) {
        if ( ! mesh.checkConnection() ) {
          mesh.renewAddress();
        } 
    }
   
    b=true;
  }


  else if (mensaje.substring(0,4)=="DIN3" || mensaje.substring(4,8)=="DIN3")    // LEER Pin 3
  {
    pinMode(3, INPUT_PULLUP);
    
    char din3_str[10] = {'I','D','0','1','D','I','N','3','0','\0'};
    din3_str[2]=idslave[0];
    din3_str[3]=idslave[1];
    bool d=digitalRead(3);
    if (d==true)
    {
      din3_str[8]= '1';
    }
    else
    {
      din3_str[8]= '0';
    }
    if (!mesh.write(&din3_str, 'R', sizeof(din3_str),id_destino_num)) {
        if ( ! mesh.checkConnection() ) {
          mesh.renewAddress();
        } 
    }
   
    b=true;
  }


  
  else if (mensaje.substring(0,5)=="DIO5H" || mensaje.substring(4,9)=="DIO5H")    // Pin 5 en alto
  {
    char dio5_str[10] = {'I','D','0','1','D','I','O','5','H','\0'};
    dio5_str[2]=idslave[0];
    dio5_str[3]=idslave[1];
    if (!mesh.write(&dio5_str, 'R', sizeof(dio5_str),id_destino_num)) {
        if ( ! mesh.checkConnection() ) {
          mesh.renewAddress();
        } 
    }
    pinMode(5, OUTPUT);
    digitalWrite(5, HIGH);
    b=true;
  }
  else if (mensaje.substring(0,5)=="DIO5L" || mensaje.substring(4,9)=="DIO5L")    // Pin 5 en bajo
  {
    char dio5_str[10] = {'I','D','0','1','D','I','O','5','L','\0'};
    dio5_str[2]=idslave[0];
    dio5_str[3]=idslave[1];
    if (!mesh.write(&dio5_str, 'R', sizeof(dio5_str),id_destino_num)) {
        if ( ! mesh.checkConnection() ) {
          mesh.renewAddress();
        } 
    }
    pinMode(5, OUTPUT);
    digitalWrite(5, LOW);
    b=true;
  }
    else if (mensaje.substring(0,5)=="DIO6H" || mensaje.substring(4,9)=="DIO6H")    // Pin 6 en alto
  {
    char dio6_str[10] = {'I','D','0','1','D','I','O','6','H','\0'};
    dio6_str[2]=idslave[0];
    dio6_str[3]=idslave[1];
    if (!mesh.write(&dio6_str, 'R', sizeof(dio6_str),id_destino_num)) {
        if ( ! mesh.checkConnection() ) {
          mesh.renewAddress();
        } 
    }
    pinMode(6, OUTPUT);
    digitalWrite(6, HIGH);
    b=true;
  }
  else if (mensaje.substring(0,5)=="DIO6L" || mensaje.substring(4,9)=="DIO6L")    // Pin 6 en bajo
  {
    char dio6_str[10] = {'I','D','0','1','D','I','O','6','L','\0'};
    dio6_str[2]=idslave[0];
    dio6_str[3]=idslave[1];
    if (!mesh.write(&dio6_str, 'R', sizeof(dio6_str),id_destino_num)) {
        if ( ! mesh.checkConnection() ) {
          mesh.renewAddress();
        } 
    }
    pinMode(6, OUTPUT);
    digitalWrite(6, LOW);
    b=true;
  }
  else if (mensaje.substring(0,5)=="PWM09" || mensaje.substring(4,9)=="PWM09")    // PWM 9
  {
    //Serial.println("Entra");
    char pwm9_str[13] = {'I','D','0','1','P','W','M','0','9','0','0','0','\0'};
    pwm9_str[2]=idslave[0];
    pwm9_str[3]=idslave[1];
    if(mensaje.substring(0,5)=="PWM09")
    {
      pwm9_str[9] = mensaje.charAt(5);
      pwm9_str[10] = mensaje.charAt(6);
      pwm9_str[11] = mensaje.charAt(7);
    }
    else
    {
      pwm9_str[9] = mensaje.charAt(9);
      pwm9_str[10] = mensaje.charAt(10);
      pwm9_str[11] = mensaje.charAt(11);
    }
    if (!mesh.write(&pwm9_str, 'R', sizeof(pwm9_str),id_destino_num)) {
        if ( ! mesh.checkConnection() ) {
          mesh.renewAddress();
        } 
    }
    char pwm9_val[4] = {pwm9_str[9],pwm9_str[10],pwm9_str[11],'\0'};
    int val = atoi(pwm9_val);
    analogWrite(9,val);
    b=true;
  }
  else if (mensaje.substring(0,5)=="PWM10" || mensaje.substring(4,9)=="PWM10")    // PWM 10
  {
    char pwm10_str[13] = {'I','D','0','1','P','W','M','1','0','0','0','0','\0'};
    pwm10_str[2]=idslave[0];
    pwm10_str[3]=idslave[1];
    if (mensaje.substring(0,5)=="PWM10")
    {
      pwm10_str[9] = mensaje.charAt(5);
      pwm10_str[10] = mensaje.charAt(6);
      pwm10_str[11] = mensaje.charAt(7);
    }
    else
    {
      pwm10_str[9] = mensaje.charAt(9);
      pwm10_str[10] = mensaje.charAt(10);
      pwm10_str[11] = mensaje.charAt(11);
    }
    if (!mesh.write(&pwm10_str, 'R', sizeof(pwm10_str),id_destino_num)) {
        if ( ! mesh.checkConnection() ) {
          mesh.renewAddress();
        } 
    }
    char pwm10_val[4] = {pwm10_str[9],pwm10_str[10],pwm10_str[11],'\0'};
    int val = atoi(pwm10_val);
    analogWrite(10,val);
    b=true;
  }

  
  else if (mensaje.substring(0,3)=="AN0" || mensaje.substring(4,7)=="AN0")    // AN0
  //else if (mensaje.substring(0,3)=="AN6")    // AN6
  
  //else if (mensaje.substring(0,3)=="AN0"||mensaje.substring(0,3)=="AN6" )
  {
    char an0_str[12] = {'I','D','0','1','A','N','0','1','0','2','3','\0'};
    //char an0_str[12] = {'I','D','0','1','A','N','6','1','0','2','3','\0'};
    int conv=0;
 

    //conv = analogRead(A6);
    conv = analogRead(A0);
    an0_str[2]=idslave[0];
    an0_str[3]=idslave[1];
    //int conv = analogRead(A0);
    //int conv = analogRead(A6);
    char conv_str[5]={'\0','\0','\0','\0','\0'};
    sprintf(conv_str,"%04d",conv);
    an0_str[7] = conv_str[0];
    an0_str[8] = conv_str[1];
    an0_str[9] =conv_str[2];
    an0_str[10] = conv_str[3];
    if (!mesh.write(&an0_str, 'R', sizeof(an0_str),id_destino_num)) {
        if ( ! mesh.checkConnection() ) {
          mesh.renewAddress();
        } 
    }
   
    b=true;
  }
  else if (mensaje.substring(0,3)=="AN1" || mensaje.substring(4,7)=="AN1")    // AN0
  //else if (mensaje.substring(0,3)=="AN7")    // AN7
  //else if (mensaje.substring(0,3)=="AN1"||mensaje.substring(0,3)=="AN7")
  {
    char an1_str[12] = {'I','D','0','1','A','N','1','1','0','2','3','\0'};
    //char an1_str[14] = {'I','D','0','1','A','N','7','1','0','2','3','\n','\r','\0'};
    int conv1=0;
    
    //conv1 = analogRead(A7);
    conv1 = analogRead(A1);
    an1_str[2]=idslave[0];
    an1_str[3]=idslave[1];
    //int conv1 = analogRead(A1);
    //int conv1 = analogRead(A7);
    char conv1_str[5]={'\0','\0','\0','\0','\0'};
    sprintf(conv1_str,"%04d",conv1);
    an1_str[7] = conv1_str[0];
    an1_str[8] = conv1_str[1];
    an1_str[9] =conv1_str[2];
    an1_str[10] = conv1_str[3];
    if (!mesh.write(&an1_str, 'R', sizeof(an1_str),id_destino_num)) {
        if ( ! mesh.checkConnection() ) {
          mesh.renewAddress();
        } 
    }
   
    b=true;
  }
  
   else if (mensaje.substring(0,4)=="TEMP" || mensaje.substring(4,8)=="TEMP")    // Temp
  {
    //char temp_str[14] = {'I','D','0','1','T','E','M','P','0','0','0','\n','\r','\0'};
    char temp_str[12] = {'I','D','0','1','T','E','M','P','0','0','0','\0'};
    temp_str[2]=idslave[0];
    temp_str[3]=idslave[1];


    // Start up the library
    sensors.begin();
    sensors.requestTemperatures(); // Send the command to get temperatures
    int temperatura = sensors.getTempCByIndex(0);

    char conv1_str[4]={'\0','\0','\0','\0'};
    sprintf(conv1_str,"%03d",temperatura);
    temp_str[8] = conv1_str[0];
    temp_str[9] = conv1_str[1];
    temp_str[10] = conv1_str[2];
    if (!mesh.write(&temp_str, 'R', sizeof(temp_str),id_destino_num)) {
        if ( ! mesh.checkConnection() ) {
          mesh.renewAddress();
        } 
    }
   
    b=true;
  }
  else if (mensaje.substring(0,6)=="RDDESC"|| mensaje.substring(4,10)=="RDDESC") 
  {
     nombre_dispositivo[0]= 'I';
     nombre_dispositivo[1]= 'D';
     nombre_dispositivo[2]=idslave[0];
     nombre_dispositivo[3]=idslave[1];
     for (uint8_t i= 30; i<62;i++)
    {
      nombre_dispositivo[i-26]=EEPROM.read(i);
    }
    /*
    for (uint8_t i= 30; i<62;i++)
    {
      nombre_dispositivo[i-30]=EEPROM.read(i);
    }
    */
    if (!mesh.write(&nombre_dispositivo, 'R', sizeof(nombre_dispositivo),id_destino_num)) {
        if ( ! mesh.checkConnection() ) {
          mesh.renewAddress();
        } 
    }
    b=true;
  }
  else if (mensaje.substring(0,6)=="RDAPPL"|| mensaje.substring(4,10)=="RDAPPL") 
  {
     direccion_app[0]= 'I';
     direccion_app[1]= 'D';
     direccion_app[2]=idslave[0];
     direccion_app[3]=idslave[1];
     for (uint8_t i= 100; i<132;i++)
    {
      direccion_app[i-96]=EEPROM.read(i);
    }
    /*
    for (uint8_t i= 100; i<132;i++)
    {
      direccion_app[i-100]=EEPROM.read(i);
    }*/
    if (!mesh.write(&direccion_app, 'R', sizeof(direccion_app),id_destino_num)) {
        if ( ! mesh.checkConnection() ) {
          mesh.renewAddress();
        } 
    }
    b=true;
  }

  else if (mensaje.substring(0,4)=="LIST" || mensaje.substring(4,8)=="LIST")    // LEER Pin 3
  {
   
    
    char list_str[7] = {'I','D','0','1','\r','\n','\0'};
    
    for(int i=0; i<mesh.addrListTop; i++){
      char conv1_str[3]={'\0','\0','\0'};
      sprintf(conv1_str,"%02d",mesh.addrList[i].nodeID);
       list_str[2]=conv1_str[0];
       list_str[3]=conv1_str[1];
       if (!mesh.write(&list_str, 'R', sizeof(list_str),id_destino_num)) {
        if ( ! mesh.checkConnection() ) {
          mesh.renewAddress();
        } 
       }
     }
    
    
   
    b=true;
  }

  
  
  }
  return(b);
}

void int2_isr(void)
{

    int2_flag = 1;
    tiempo = millis();
 
}

void int3_isr(void)
{
  int3_flag = 1;
  tiempo = millis();
}
