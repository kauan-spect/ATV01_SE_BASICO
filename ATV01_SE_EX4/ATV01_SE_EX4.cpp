// Monitor de temperatura com TMP36
// Contexto: semáforo de temperatura para banho/torneira/aquecedor (uso doméstico)
// Ligações conforme sua foto:
//  - Vermelho -> 5V
//  - Preto   -> GND
//  - Verde   -> A0 (saída analógica do TMP36)

// Pino analógico onde o sensor está conectado
const int PIN_SENSOR = A0;

// Usamos o LED interno para indicar estado (não é componente novo)
const int PIN_LED = 13;

// Intervalo de leitura (ms)
const unsigned long INTERVALO_MS = 1000UL;

// Janela para média móvel simples (suaviza leituras)
const int WINDOW = 8;
int buffer[WINDOW];
int bufPos = 0;
int bufCount = 0;

unsigned long ultimaLeituraTs = 0;

// Limiares (ajuste conforme sua necessidade):
const float LIMIAR_ATENCAO = 35.0; // °C - quando começa a atenção
const float LIMIAR_PERIGO  = 42.0; // °C - quando é perigoso

void setup() {
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, LOW);

  Serial.begin(9600);
  Serial.println("Monitor de temperatura iniciado (TMP36).");

  // Inicializa buffer com zeros
  for (int i = 0; i < WINDOW; ++i) buffer[i] = 0;
}

void loop() {
  unsigned long agora = millis();
  if (agora - ultimaLeituraTs >= INTERVALO_MS) {
    ultimaLeituraTs = agora;

    // Leitura crua do ADC
    int leitura = analogRead(PIN_SENSOR);

    // Alimenta buffer para média
    buffer[bufPos] = leitura;
    bufPos = (bufPos + 1) % WINDOW;
    if (bufCount < WINDOW) bufCount++;

    // Calcula média das leituras do buffer (precaução para leituras ruidosas)
    long soma = 0;
    for (int i = 0; i < bufCount; ++i) soma += buffer[i];
    float media = (float)soma / (float)bufCount;

    // Converte média ADC -> tensão (V). ADC 10-bit: 0..1023
    const float VREF = 5.0; // tensão de referência (5V na sua ligação)
    float tensao = media * (VREF / 1023.0);

    // Conversão TMP36 -> temperatura em Celsius:
    // TMP36: Vout = 0.5V at 0°C, 0.75V at 25°C -> Temp(°C) = (Vout - 0.5) * 100
    float tempC = (tensao - 0.5) * 100.0;

    // Também calcula Fahrenheit (opcional)
    float tempF = tempC * 9.0 / 5.0 + 32.0;

    // Mostra no Serial
    Serial.print("ADC_med: ");
    Serial.print((int)media);
    Serial.print("  V: ");
    Serial.print(tensao, 3);
    Serial.print(" V  |  Temp: ");
    Serial.print(tempC, 2);
    Serial.print(" C  (");
    Serial.print(tempF, 1);
    Serial.println(" F)");

    // Lógica de indicação (sem novos componentes)
    if (tempC >= LIMIAR_PERIGO) {
      // Perigo: LED ligado fixo
      digitalWrite(PIN_LED, HIGH);
      Serial.println("ALERTA: Temperatura em nivel PERIGO!");
    } else if (tempC >= LIMIAR_ATENCAO) {
      // Atenção: LED pisca lentamente (implementado aqui)
      piscarLed(800); // pisca com periodo ~800ms
      Serial.println("ATENCAO: Temperatura elevada.");
    } else {
      // Normal: LED desligado
      digitalWrite(PIN_LED, LOW);
    }
  }

  // aqui loop continua, sem bloquear (piscarLed é não-bloqueante para próximas leituras)
}

// Função não-bloqueante simples para piscar o LED
// período_ms = intervalo entre alternâncias (ms)
void piscarLed(unsigned long periodo_ms) {
  static unsigned long lastToggle = 0;
  static bool estado = false;
  unsigned long now = millis();
  if (now - lastToggle >= periodo_ms) {
    lastToggle = now;
    estado = !estado;
    digitalWrite(PIN_LED, estado ? HIGH : LOW);
  }
}
