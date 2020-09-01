#include <Arduino.h>

int ledArray[] = { 2, 3, 4 };
int ledIndicador = 5;
bool calibrado = false;
int espera = 5000;
bool inicio = false;

int red = 0;
int green = 0;
int blue = 0;

float colorMatriz[]  = { 0, 0, 0 };
float blancoMatriz[] = { 1, 1, 1 };
float negroMatriz[]  = { 0, 0, 0 };
float grisMatriz[]   = { 0, 0, 0 };

void setup() {
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);   //Inicia las 4 salidas
  pinMode(5,OUTPUT);
  
  Serial.begin(9600);  //Inicia el serial en el canal 9600
}

void calibracion(){                   //Función de calibrado
  
  for(int i = 0; i<=2;i++){           
  digitalWrite(ledArray[i],HIGH);}    //Apaga los LED
  digitalWrite(ledIndicador,HIGH);    //Enciende el LED indicador
  delay(espera);                      //Da 5 segundos para colocar el color blanco
  digitalWrite(ledIndicador,LOW);     //Apaga el LED indicador

  //blanco
  for(int i = 0; i<=2;i++){           //Realiza el código para cada color
    digitalWrite(ledArray[i],LOW);     //Enciende el LED del color
    delay(200);                       //Espera 100 milisegundos para dejarlo prender
    blancoMatriz[i] = (analogRead(0)*2.5);  //Registra el color de la lectura
    digitalWrite(ledArray[i],HIGH);   //Apaga el LED
    delay(200);
  }
  
  digitalWrite(ledIndicador,HIGH);    //Enciende el LED indicador
  delay(espera);                      //Da 3 segundos para colocar el color negro
  digitalWrite(ledIndicador,LOW);     //Apaga el LED indicador

  //negro
  for(int i = 0; i<=2;i++){           //Realiza el código para cada color
    digitalWrite(ledArray[i],LOW);    //Enciende el LED del color
    delay(200);                       //Espera 100 milisegundos para dejarlo prender
    negroMatriz[i] = (analogRead(0)*2.5);   //Registra el color de la lectura
    digitalWrite(ledArray[i],HIGH);   //Apaga el LED
    delay(200);
  }
  
  //Gris
  for(int i = 0; i<=2;i++){                               //Realiza el código para cada color
    grisMatriz[i] = (blancoMatriz[i])-(negroMatriz[i]);   //Registra el color de la lectura
  }
  digitalWrite(ledIndicador,HIGH);    //Enciende el LED indicador
  calibrado = true;                   //Marca que está calibrado
  delay(espera);                      //3 segundos antes de empezar
}

void revisaCalibre(){     //Revisa si el programa esta calibrado, si no lo está inicia el calibrado
  if(calibrado == false){
    calibracion();
  }
}

void revisarColor(){                                    //Función de escaneo
  
  for(int i = 0; i<=2; i++){
    digitalWrite(ledArray[i],LOW);                      //Enciende el LED de cada color
    delay(200);                                         //Espera 100 milisegundos para dejarlo prender

    if ((analogRead(0)*2.5) > blancoMatriz[i]){               //Si la lectura es mayor al blanco guardado
      colorMatriz[i]= grisMatriz[i];                    //Registra la lectura como blanca
      delay(200);                                       //Espera 100 milisegundos
      digitalWrite(ledArray[i],HIGH);                   //Apaga el LED
    }
    else if ((analogRead(0)*2.5) < negroMatriz[i]){           //Si la lectura es menor al negro guardado
    colorMatriz[i] = 0;                                 //Registra la lectura como negra
    delay(200);                                         //Espera 100 milisegundos
    digitalWrite(ledArray[i],HIGH);                     //Apaga el LED
    }
    else{                                               //En cualquier otro caso
    colorMatriz[i] = ((analogRead(0)*2.5)-negroMatriz[i]);    //Registra el color de la lectura
    delay(200);                                         //Espera 100 milisegundos
    digitalWrite(ledArray[i],HIGH);                     //Apaga el LED
    }       
  }
}

void imprimirColor(){                //Este es para el monitor o processing
 
  Serial.print(grisMatriz[0],0);     //Inserta el blanco para rojo
  Serial.print(",");
  Serial.print(colorMatriz[0],0);      //Inserta lectura roja
  Serial.print(",");
  Serial.print(grisMatriz[1],0);     //Inserta el blanco para verde
  Serial.print(",");
  Serial.print(colorMatriz[1],0);      //Inserta lectura verde
  Serial.print(",");
  Serial.print(grisMatriz[2],0);     //Inserta el blanco para azul
  Serial.print(",");
  Serial.print(colorMatriz[2],0);      //Inserta lectura azul
  Serial.print(",");
  
  Serial.println();                  //Salta de línea
}


void loop(){          //Funcion que el Arduino ejecuta constantemente
  revisaCalibre();
  revisarColor();
  imprimirColor();
  delay(1000);
}


