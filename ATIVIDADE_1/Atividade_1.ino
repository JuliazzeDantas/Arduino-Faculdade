#define led1 3
#define led2 4
#define led3 5
#define led4 6

#define bUp 7
#define bReset 8

int contador = 0;
int escolheAndar = 0;
int flagAndar = 0;
int andar = 0;

// Variables will change:
int ledState = HIGH;         // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin
int flagReset = 0;
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // ssthe debounce time; increase if the output flickers
unsigned long tempoSubida = 0;

// Variables will change:
int ledStateReset = HIGH;         // the current state of the output pin
int buttonStateReset;             // the current reading from the input pin
int lastButtonStateReset = LOW;   // the previous reading from the input pin

unsigned long lastDebounceTimeReset = 0;  // the last time the output pin was toggled
unsigned long debounceDelayReset = 50;    // ssthe debounce time; increase if the output flickers

unsigned long tempoEscolha = 0;

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);

  pinMode(bUp, INPUT);
  pinMode(bReset, INPUT);
  Serial.begin(9600);

  digitalWrite(led1, HIGH);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  Serial.println("Andar T");
}

void loop() {
    int reading = 0;
  // read the state of the switch into a local variable:
    int reset = digitalRead(bReset);

    // check to see if you just pressed the button
    // (i.e. the input went from LOW to HIGH), and you've waited long enough
    // since the last press to ignore any noise:
 
    // If the switch changed, due to noise or pressing:
    if (reset != lastButtonStateReset) {
      // reset the debouncing timer
      lastDebounceTimeReset = millis();
    }
 
    if ((millis() - lastDebounceTimeReset) > debounceDelayReset) {
      // whatever the reading is at, it's been there for longer than the debounce
      // delay, so take it as the actual current state:
 
      // if the button state has changed:
      if (reset != buttonStateReset) {
        buttonStateReset = reset;
 
        // only toggle the LED if the new button state is HIGH
        if (buttonStateReset == HIGH) {
          flagReset = 1;
          Serial.println("________________________");

        }
      }
    }
 
  if(flagReset){
    unsigned long tempoReset;
    unsigned long tempoTrava;
    int quantidadeReset = 0;
    tempoReset = millis();
    Serial.println("/////////////////");
    while(millis() - tempoReset < 5000 && quantidadeReset < 3){
      Serial.println("********");
      quantidadeReset++;
      tempoTrava = millis();
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, HIGH);
      digitalWrite(led4, HIGH);
      while(millis() - tempoTrava < 1000){
       
      }
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);
      tempoTrava = millis();
      while(millis() - tempoTrava < 1000){
      	
      }	
    }
    quantidadeReset = 0;
    flagReset = 0;
    
    while(flagAndar >= 0){
      
    	if(flagAndar % 4 == 0){
          digitalWrite(led1, HIGH);
          digitalWrite(led2, LOW);
          digitalWrite(led3, LOW);
          digitalWrite(led4, LOW);
          Serial.println("Andar T");   
          tempoTrava = millis();
        }
        if(flagAndar % 4 == 1){
          digitalWrite(led1, HIGH);
          digitalWrite(led2, HIGH);
          digitalWrite(led3, LOW);
          digitalWrite(led4, LOW);
          Serial.println("Andar 1");
          tempoTrava = millis();
        }
        if(flagAndar % 4 == 2){
          digitalWrite(led1, HIGH);
          digitalWrite(led2, HIGH);
          digitalWrite(led3, HIGH);
          digitalWrite(led4, LOW);
          Serial.println("Andar 2");
          tempoTrava = millis();
        }
        if(flagAndar % 4 == 3){
          digitalWrite(led1, HIGH);
          digitalWrite(led2, HIGH);
          digitalWrite(led3, HIGH);
          digitalWrite(led4, HIGH);
          Serial.println("Andar 3");
          tempoTrava = millis();
        }
      Serial.println("Descida de Emergencia!");
      while(millis() - tempoTrava < 4000){
      	
      }	
      flagAndar--;
    }
    flagAndar = 0;
    contador = 0;
    escolheAndar = 0;
  }
  else{
    if(flagAndar%4 == contador%4){
      // read the state of the switch into a local variable:
      reading = digitalRead(bUp);
 
      // check to see if you just pressed the button
      // (i.e. the input went from LOW to HIGH), and you've waited long enough
      // since the last press to ignore any noise:
   
      // If the switch changed, due to noise or pressing:
      if (reading != lastButtonState) {
        // reset the debouncing timer
        lastDebounceTime = millis();
      }
   
      if ((millis() - lastDebounceTime) > debounceDelay) {
        // whatever the reading is at, it's been there for longer than the debounce
        // delay, so take it as the actual current state:
   
        // if the button state has changed:
        if (reading != buttonState) {
          buttonState = reading;
   
          // only toggle the LED if the new button state is HIGH
          if (buttonState == HIGH) {
            escolheAndar++;
            escolheAndar = escolheAndar %4;
            Serial.print("O andar escolhido e': ");
            Serial.println(escolheAndar);
            tempoEscolha = millis();
          }
        }
      }
 
      // save the reading. Next time through the loop, it'll be the lastButtonState:
      lastButtonState = reading;
     
      //-------------------------------------------------------------------------------
 
     
      // save the reading. Next time through the loop, it'll be the lastButtonState:
      lastButtonStateReset = reset;
      if(millis() - tempoEscolha >= 5000){
      if(escolheAndar > contador){
        contador = contador + escolheAndar;
      }
      else{
        if(escolheAndar < contador){
          contador = escolheAndar;
        }
      }
     contador = contador%4;
     // escolheAndar = 0;      
      tempoEscolha = millis();
      }
    }
    else{
      if(millis() > tempoSubida + 4000){
        if(contador >= flagAndar){
          flagAndar++;
        }
        else{
          flagAndar--;
        }
       
        flagAndar = flagAndar%4;
       // Serial.print("O valor do andar e' ");
       //  Serial.print(andar);
        //  Serial.print(" e o valor da flag e' ");
         // Serial.println(flagAndar);
      if(flagAndar % 4 == 0){
          digitalWrite(led1, HIGH);
          digitalWrite(led2, LOW);
          digitalWrite(led3, LOW);
          digitalWrite(led4, LOW);
          Serial.println("Andar T");
          tempoSubida = millis();
         
        }
        if(flagAndar % 4 == 1){
          digitalWrite(led1, HIGH);
          digitalWrite(led2, HIGH);
          digitalWrite(led3, LOW);
          digitalWrite(led4, LOW);
          Serial.println("Andar 1");
          tempoSubida = millis();
        }
        if(flagAndar % 4 == 2){
          digitalWrite(led1, HIGH);
          digitalWrite(led2, HIGH);
          digitalWrite(led3, HIGH);
          digitalWrite(led4, LOW);
          Serial.println("Andar 2");
          tempoSubida = millis();
        }
        if(flagAndar % 4 == 3){
          digitalWrite(led1, HIGH);
          digitalWrite(led2, HIGH);
          digitalWrite(led3, HIGH);
          digitalWrite(led4, HIGH);
          Serial.println("Andar 3");
          tempoSubida = millis();
        }
      }
    }
  }
 
}
