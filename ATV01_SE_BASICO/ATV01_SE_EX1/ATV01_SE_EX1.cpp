// C++ code
//
void setup()
{
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(2, OUTPUT);
}

void loop()
{
  digitalWrite(4, HIGH);
  delay(2000); //farol vermelho de pare acende por 2 segundos
  digitalWrite(4, LOW);
  delay(100); //transição vermelho pro amarelo
  digitalWrite(3, HIGH);
  delay(1000); //farol amarelo de atenção acende por 1 segundo
  digitalWrite(3, LOW);
  delay(100); //transição amarelo pro verde
  digitalWrite(2, HIGH);
  delay(3000); //farol verde de passe acende por 3 segundos
  digitalWrite(2, LOW);
  delay(100); //transição do verde para o vermelho
}