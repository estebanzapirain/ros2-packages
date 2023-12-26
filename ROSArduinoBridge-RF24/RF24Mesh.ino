/* Include Radio Communications code*/
#ifdef USE_RF24
  /*RF definitions*/
  #include "RF24Mesh.h"
  #include <avr/wdt.h>
  #include "RF24Network.h"
  #include "RF24.h"
  #include <SPI.h>
  //Include eeprom.h for AVR (Uno, Nano) etc. except ATTiny
  #include <EEPROM.h>
//  #include <MsTimer2.h>
  #include <avr/boot.h>
  //#include <AESLib.h>
  //#include <OneWire.h>
  //#include <DallasTemperature.h> 
#endif

#define DIP1  A2 
#define DIP2  A3
#define DIP3  A4
#define DIP4  A5

//#define ONE_WIRE_BUS 4
//OneWire oneWire(ONE_WIRE_BUS);
//DallasTemperature sensors(&oneWire);
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

void RF24setup() {
  wdt_disable();
  pinMode(DIP1,INPUT_PULLUP);
  pinMode(DIP2,INPUT_PULLUP);
  pinMode(DIP3,INPUT_PULLUP);
  pinMode(DIP4,INPUT_PULLUP);
  nodeID = leer_dipswitch();
 // Serial.begin(115200);

 // MsTimer2::set(10, timer2_isr); // 10ms period
 // MsTimer2::stop();
  EEPROM.get(30, nombre_dispositivo);
  EEPROM.get(100, direccion_app);

  
  // Seteo el ID del nodo. 0 es maestro
  mesh.setNodeID(nodeID);
  Serial.println(mesh.getNodeID());


  if (nodeID==0)
  {
    delay(3000);
  }
  
  // Connect to the mesh
  if (coincide==true)
  {
    mesh.begin();
  }

   periodo=millis();
  wdt_enable(WDTO_4S);
}

void RF24loop() {
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


        convertir_a_string();
        mensaje=mensaje.substring(0,mensaje.length());
        
        //Formato del mensaje: 
        //comando arg1 arg2
        //separo por espacios, quedándome con el resto

        //Comando
        cmd = mensaje[0];

        //Argumento 1
        mensaje = mensaje.substring(2,mensaje.length());
        String argv1_str = mensaje.substring(0,mensaje.indexOf(' '));

        //Argumento 2
        String argv2_str = mensaje.substring(mensaje.indexOf(' ') + 1,mensaje.length());
       
        argv1_str.toCharArray(argv1, 16);
        argv2_str.toCharArray(argv2, 16);
        
        Serial.print("cmd= ");
        Serial.println(cmd);
        Serial.print("arg1= ");
        Serial.println(argv1);
        Serial.print("arg2= ");
        Serial.println(argv2);
        
        mensaje="";
        runCommand();
        resetCommand();
   
    
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
//    MsTimer2::start();
    char inChar = (char)Serial.read(); 
    inputString += inChar;

  }
}

void timer2_isr(void)
{
    //if (inChar == '\n') {
      //Serial.println("int");
      //Serial.println(inputString);
//      MsTimer2::stop();
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
         if (inputString.substring(4,9)=="DIO5H")    // Pin 5 en alto
        {
          pinMode(13, OUTPUT);
          digitalWrite(13, HIGH);
          Serial.println(inputString.substring(0,9));
          //Serial.println(F("ID00DIO5H"));
        }
        if (inputString.substring(4,9)=="DIO5L")    // Pin 5 en bajo
        {
          pinMode(13, OUTPUT);
          digitalWrite(13, LOW);
          Serial.println(inputString.substring(0,9));
          //Serial.println(F("ID00DIO5L"));
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
 if (mensaje.substring(0,5)=="DIO5H" || mensaje.substring(4,9)=="DIO5H")    // Pin 5 en alto
  {
    char dio5_str[10] = {'I','D','0','1','D','I','O','5','H','\0'};
    dio5_str[2]=idslave[0];
    dio5_str[3]=idslave[1];
    if (!mesh.write(&dio5_str, 'R', sizeof(dio5_str),id_destino_num)) {
        if ( ! mesh.checkConnection() ) {
          mesh.renewAddress();
        } 
    }
    pinMode(13, OUTPUT);
    digitalWrite(13, HIGH);
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
    pinMode(13, OUTPUT);
    digitalWrite(13, LOW);
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

  
  
  
  return(b);
}
