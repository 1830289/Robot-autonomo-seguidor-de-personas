/* 
 Conexion Puente H
 ARDUINO   L298n      
 5         in3
 6         in4 
 9         in1 
 10        in2 
           5v--Alimentacion externa 5v (pila)
           GND--Negativo de la pila

 Conexion del Modulo Bluetooth HC-06 y el Arduino
 ARDUINO    Bluetooth HC-06 
 0 (RX)       TX
 1 (TX)       RX
 5V           VCC
 GND          GND
 !!Cuidado!! Las conexiones de TX y RX al modulo Bluetooth deben estar desconectadas
 en el momento que se realiza la carga del codigo (Sketch) al Arduino.
 
 Conexion Sensor Ultrasonido HC-SR04
 ARDUINO    Ultrasonido HC-SR04 
 2            Echo
 3            Trig
 5V           VCC
 GND          Gnd
 */
int enA = 5;
int enB = 10;
int in1 = 6; 
int in2 = 7; 
int in3 = 8; 
int in4 = 9; 
int vel = 255;            // Velocidad de los motores (0-255)
String estado;

int pecho = 2;            // define el pin 2 como (pecho) para el Ultrasonido
int ptrig = 3;            // define el pin 3 como (ptrig) para el Ultrasonido
int duracion, distancia;  // para Calcular distacia

void setup()  { 
  Serial.begin(9600);    // inicia el puerto serial para comunicacion con el Bluetooth
  
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
  pinMode(pecho, INPUT);   // define el pin 2 como entrada (pecho) 
  pinMode(ptrig,OUTPUT);   // define el pin 3 como salida  (ptrig) 
  pinMode(13,OUTPUT);

} 

void loop()  { 

  if(Serial.available()){        // lee el bluetooth y almacena en estado
    estado = Serial.readString();
    Serial.println(estado);
    
  }
  if(estado == 'u'){           // Desplazar al Frente  
      digitalWrite(in2, 0);     
      digitalWrite(in4, 0); 
      digitalWrite(in1, vel);  
      digitalWrite(in3, vel);       
  }else{
    if(estado == 'l'){          // IZQ 
      digitalWrite(in2, 0);     
      digitalWrite(in4, 0); 
      digitalWrite(in1, 0);  
      digitalWrite(in3, vel);      
    }else{
      if(estado == 'r'){          // DER
        digitalWrite(in2, 0);     
        digitalWrite(in4, 0);
        digitalWrite(in1, 0);
        digitalWrite(in3, vel);  
      }else{
        if(estado == 'd'){          // Reversa
          digitalWrite(in1, 0);    
          digitalWrite(in3, 0);
          digitalWrite(in2, vel);  
          digitalWrite(in4, vel);      
        }else{
          digitalWrite(in2, 0);     //Parar
          digitalWrite(in4, 0); 
          digitalWrite(in1, 0);    
          digitalWrite(in3, 0);
        }
      }
    }
  }  
}
