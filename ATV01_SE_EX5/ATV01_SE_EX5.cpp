
int pinoLDR = A0;      
int pinoRele = 2;      
int valorLDR = 0;     
int limite = 500;      

void setup() {
  pinMode(pinoRele, OUTPUT);  
  digitalWrite(pinoRele, LOW); 
  Serial.begin(9600);         
}

void loop() {
  valorLDR = analogRead(pinoLDR); 
  Serial.print("Luminosidade: ");
  Serial.println(valorLDR);

  if (valorLDR < limite) {
    digitalWrite(pinoRele, HIGH);
    Serial.println("Lâmpada LIGADA");
  } else {
    digitalWrite(pinoRele, LOW);
    Serial.println("Lâmpada DESLIGADA");
  }

  delay(500);
}