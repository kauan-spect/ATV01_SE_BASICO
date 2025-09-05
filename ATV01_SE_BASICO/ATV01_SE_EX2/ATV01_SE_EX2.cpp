int verde = 2;    
int vermelho = 3;  
int botao = 4;        

void setup() {
  pinMode(verde, OUTPUT);
  pinMode(vermelho, OUTPUT);
  pinMode(botao, INPUT);
  digitalWrite(vermelho, HIGH); 
  digitalWrite(verde, LOW);
}

void loop() {
  if (digitalRead(botao) == LOW) { 
    digitalWrite(vermelho, LOW);  
    digitalWrite(verde, HIGH);    

    delay(5000); 

    digitalWrite(verde, LOW);    
    digitalWrite(vermelho, HIGH); 
  }
}
