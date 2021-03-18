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

int in1 = 9; 
int in2 = 10; 
int in3 = 5; 
int in4 = 6; 
int vel = 255;            // Velocidad de los motores (0-255)
String coordenadas;
String estado1, estado2;         // inicia detenido
int estado, e1, e2;

int pecho = 2;            // define el pin 2 como (pecho) para el Ultrasonido
int ptrig = 3;            // define el pin 3 como (ptrig) para el Ultrasonido
int duracion, distancia;  // para Calcular distacia

void setup()  { 
  Serial.begin(9600);    // inicia el puerto serial para comunicacion con el Bluetooth
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
    coordenadas = Serial.readString();
    Serial.println(estado);
    estado = coordenadas.indexOf(',');
    estado1 = coordenadas.substring(0,estado);
    estado2 = coordenadas.substring(estado+1);

    e1 = estado1.toInt();
    e2 = estado2.toInt();

    Serial.println(e1);
    Serial.println(e2);
    
  }
  if(e2 < -150){           // Desplazar al Frente  
      analogWrite(in2, 0);     
      analogWrite(in4, 0); 
      analogWrite(in1, vel);  
      analogWrite(in3, vel);       
  }
  if(e1 < -150){          // IZQ 
    analogWrite(in2, 0);     
    analogWrite(in4, 0); 
    analogWrite(in1, 0);  
    analogWrite(in3, vel);      
  }
  if(e1 > -100 && e1 < -50){         // Parar
    if(e2 > -100 && e2 < -50){
      analogWrite(in2, 0);     
      analogWrite(in4, 0); 
      analogWrite(in1, 0);    
      analogWrite(in3, 0); 
    }
  }
  if(e1 > -35){          // DER
    analogWrite(in2, 0);     
    analogWrite(in4, 0);
    analogWrite(in1, 0);
    analogWrite(in3, vel);  
  } 

  if(e2 > -35){          // Reversa
    analogWrite(in1, 0);    
    analogWrite(in3, 0);
    analogWrite(in2, vel);  
    analogWrite(in4, vel);      
  }
  
  if (estado =='f'){               // Boton ON,  se mueve sensando distancia 
  
     digitalWrite(ptrig, HIGH);   // genera el pulso de trigger por 10us
     delay(0.01);
     digitalWrite(ptrig, LOW);
     
     duracion = pulseIn(pecho, HIGH);          // Lee el tiempo del Echo
     distancia = (duracion/2) / 29;            // calcula la distancia en centimetros
     delay(10); 
     
     if (distancia <= 15 && distancia >=2){    // si la distancia es menor de 15cm
        digitalWrite(13,HIGH);                 // Enciende LED
        
        analogWrite(in2, 0);             // Parar los motores por 200 mili segundos
        analogWrite(in4, 0); 
        analogWrite(in1, 0);    
        analogWrite(in3, 0); 
        delay (200);
        
        analogWrite(in2, vel);          // Reversa durante 500 mili segundos
        analogWrite(in4, vel); 
        delay(500);           
        
        analogWrite(in2, 0);            // Girar durante 600 milisegundos   
        analogWrite(in4, 0); 
        analogWrite(in1, 0);  
        analogWrite(in3, vel);  
        delay(600);
        
        digitalWrite(13,LOW);
     }
     else{                             // Si no hay obstaculos se desplaza al frente  
         analogWrite(in2, 0);     
         analogWrite(in4, 0); 
         analogWrite(in1, vel);  
         analogWrite(in3, vel); 
     }
  }

    if(estado=='h'){                 //Programacion de los botones 13-10-9-6-5
    digitalWrite(13,1);        
  }
      if(estado=='m'){           
    digitalWrite(13,0);        
  }
    if(estado=='i'){           
    digitalWrite(in2,1);        
  }
    if(estado=='n'){           
    digitalWrite(in2,0);        
  }
    if(estado=='j'){           
    digitalWrite(in1,1);        
  }
    if(estado=='o'){           
    digitalWrite(in1,0);        
  }
    if(estado=='k'){           
    digitalWrite(in4,1);        
  }
    if(estado=='p'){           
    digitalWrite(in4,0);        
  }
    if(estado=='l'){           
    digitalWrite(in3,1);        
  }
    if(estado=='q'){           
    digitalWrite(in3,0);        
  }
  
}
