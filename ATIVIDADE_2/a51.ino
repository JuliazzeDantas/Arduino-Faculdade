// C++ code
//


#define ledTemp 11
#define ledLuz2 10
#define ledLuz3 6
#define ledLuz4 5

#define buzzer 2

#define tmp A0 //
//Intervalo (-40) - 125
#define pot A1 
//0 - 1023
#define ldr A2

void setup()
{
  pinMode(ledTemp, OUTPUT);
  pinMode(ledLuz2, OUTPUT);
  pinMode(ledLuz3, OUTPUT);
  pinMode(ledLuz4, OUTPUT);
 
  pinMode(buzzer, OUTPUT);
  
  pinMode(tmp, INPUT);
  pinMode(pot, INPUT);
  pinMode(ldr, INPUT);
  Serial.begin(9600);
  
}

unsigned long tempoTemp = 0;
unsigned long tempoMedia = 0;
int quantidadeTemp = 0;
float temperatura[10];

float mediaTemperatura(float temperatura[]){
  float mediaTemp = 0;
  for(int cont = 0; cont < 10; cont++){
    mediaTemp = mediaTemp + temperatura[cont];
  }
  Serial.print("A temperatura media e' de: ");
  Serial.println(mediaTemp/10);
  mediaTemp = 0;
  tempoMedia = millis();
}

float medirTemperatura(){
  if(millis() - tempoTemp >= 100){ // Guardando as 10 últimas temperaturas a cada 100 ms
    quantidadeTemp = (quantidadeTemp + 1) % 10;
    temperatura[quantidadeTemp] = ((0.48875855321*analogRead(tmp))-50);
    tempoTemp = millis();
    if(millis() - tempoMedia >= 1000){ //Mostrando a média da temperatura a cada 1 seg
      mediaTemperatura(temperatura);
  	}
    return temperatura[quantidadeTemp];
  }
}

void limiteTemperatura(float temp){
  //A Razão é: (pot - 0)/1023 = (tmp - 0)/50
  //tmp = pot * (50/1023) + 0
  float aux = analogRead(pot);
  float potToTemp = aux * 50.0 / 1023.0;
  //Serial.print("A Temperatura limite e': ");
  //Serial.println(potToTemp);
  //Serial.print("A Temperatura atual e': ");
  //Serial.println(temp);
  //Serial.println();
  //Serial.println("---------------");
  //Serial.println();
  if(potToTemp <= temp){
    Serial.println("Temperatura excede o limite estabelecido. CUIDADO!");
    analogWrite(buzzer, HIGH);
  }
      
}

void loop()
{
  
  float temp = medirTemperatura();
  
  limiteTemperatura(temp);
  //limiteTemperatura(temp);
  //pot: 0 - 1023
  //tmp: 20 - 358
  //tempReal: -40 - 125
  //Serial.println(analogRead(tmp));
  
}