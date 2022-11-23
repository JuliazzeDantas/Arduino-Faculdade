// C++ code
//


#define ledTemp 11
#define l1 10
#define l2 6
#define l3 5

#define buzzer 2

#define tmp A0 //
//Intervalo (-40) - 125
#define pot A1 
//0 - 1023
#define ldr A2

void setup()
{
  pinMode(ledTemp, OUTPUT);
  pinMode(l1, OUTPUT);
  pinMode(l2, OUTPUT);
  pinMode(l3, OUTPUT);
 
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

void mediaTemperatura(float temperatura[]){
  float mediaTemp = 0;
  for(int cont = 0; cont < 10; cont++){
    mediaTemp = mediaTemp + temperatura[cont];
  }
  Serial.print("A temperatura media e' de: ");
  Serial.println(mediaTemp/10);
  limiteTemperatura(mediaTemp/10); // chama a função que compara com o limite de temperatura
  mediaTemp = 0;
  tempoMedia = millis();
}

void medirTemperatura(){
  if(millis() - tempoTemp >= 100){ // Guardando as 10 últimas temperaturas a cada 100 ms
    quantidadeTemp = (quantidadeTemp + 1) % 10;
    temperatura[quantidadeTemp] = ((0.48875855327 *analogRead(tmp)) - 50); // Se for um LM35, multiplicar por  0.1075268817
    tempoTemp = millis();
    if(millis() - tempoMedia >= 1000){ //Mostrando a média da temperatura a cada 1 seg
      Serial.println("---------------");  
        mediaTemperatura(temperatura);
        Serial.println("---------------");
    }
  }
}

void limiteTemperatura(float temp){
  //A Razão é: (pot - 0)/1023 = (tmp - 0)/50
  //tmp = pot * (50/1023) + 0
  float aux = analogRead(pot);
  float potToTemp = aux * 50.0 / 1023.0;
  Serial.print("A Temperatura limite e': ");
  Serial.println(potToTemp);
  if(potToTemp <= temp){
    Serial.println("Temperatura excede o limite estabelecido. CUIDADO!");
    tone(buzzer, 440, 1000);
    digitalWrite(ledTemp, HIGH);
  }
  else{
    float razao = (temp/potToTemp) * 225;
    analogWrite(ledTemp, razao);
  }
}

void iluminar(){
  float lux = map(analogRead(ldr), 969, 500, 225 * 3, 0); //mapeando para PWM
  if(lux <= 225){
    analogWrite(l1, lux);
    analogWrite(l2, 0);
    analogWrite(l3, 0);
  }
  else{
    if(lux <= 225 * 2){
      analogWrite(l1, 225);
      analogWrite(l2, lux - 225);
      analogWrite(l3, 0);
    }
    else{
      analogWrite(l1, 225);
      analogWrite(l2, 225);
      analogWrite(l3, lux - 450);
    }
  }
  
}

void loop()
{
  iluminar();
  medirTemperatura(); // chama a função que vê a média de temperatua
  

  
}
