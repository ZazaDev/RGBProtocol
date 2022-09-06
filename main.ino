#define S_ESPERA_COMANDO 1
#define S_RECEBE_COMANDO 2
#define END '1'

const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;

char Str[16];
unsigned char indice = 0;
unsigned char pwm = 0;
// Programa 2: Serial, LEDs PWM x Computador
void setup() {
  Serial.begin(9600); //Configura a velocidade de comunicação da porta serial.
  pinMode(redPin, OUTPUT); // Configura o Pino 3 como saída.
  pinMode(greenPin, OUTPUT); // Configura o Pino 5 como saída.
  pinMode(bluePin, OUTPUT); // Configura o Pino 6 como saída.
}
void loop() // Cria um loop infinito.
{
  static unsigned char estado = S_ESPERA_COMANDO;
  int x = Serial.available();
  if(x > 0){
    char c = Serial.read();
    switch(estado){
      case S_ESPERA_COMANDO:
      if(c==':'){
        estado = S_RECEBE_COMANDO;
        Serial.println("estado = S_RECEBE_COMANDO");
        indice = 0;
        Str[indice] = c;
      }
      break;
      case S_RECEBE_COMANDO:
      if(c==';'){
        if(Str[1]=='1'){
          Str[indice+1] = 0;
        }
        if(Str[1]==END){
          if(Str[2]=='R'){
            Serial.println("Red");
            pwm = 10000*(Str[3]-48)+1000*(Str[4]-48)+100*(Str[5]-48);
            analogWrite(redPin,pwm);
          }
          if(Str[2]=='G'){
            Serial.println("Green");
            pwm = 10000*(Str[3]-48)+1000*(Str[4]-48)+100*(Str[5]-48);
            analogWrite(greenPin,pwm);
          }
          if(Str[2]=='B'){
            Serial.println("Blue");
            pwm = 10000*(Str[3]-48)+1000*(Str[4]-48)+100*(Str[5]-48);
            analogWrite(bluePin,pwm);
          }
        }
        estado = S_ESPERA_COMANDO;
      }
      indice=indice+1;
      Str[indice] = c;
      break;
    }
  }
}
