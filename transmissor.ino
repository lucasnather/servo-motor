#include <RH_ASK.h>
#include <SPI.h>

RH_ASK driver;

#define botaoAbrir 2
#define ledAbrir 3

#define botaoFechar 4
#define ledFechar 5

#define som 9
#define frequenciaAberto 400
#define frequenciaFechado 800
#define tempoEmitindoOSom 500

void setup()
{
    Serial.begin(9600);
    Serial.println("setup");

    pinMode(botaoAbrir, INPUT_PULLUP);
    pinMode(botaoFechar, INPUT_PULLUP);

    pinMode(ledAbrir, OUTPUT);
    pinMode(ledFechar, OUTPUT);
    pinMode(som, OUTPUT);

    if (!driver.init())
    {
        Serial.println("falhou");
    }

    driver.init();
}
void loop()
{
    const char *abre = "abre";
    const char *fecha = "fecha";

    if (digitalRead(botaoAbrir) == LOW)
    {
        emitirSom(som, frequenciaAberto, tempoEmitindoOSom);
        acendeLed(ledAbrir, ledFechar);
        driver.send((uint8_t *)abre, strlen(abre));
        driver.waitPacketSent();
        delay(200);
    }

    if (digitalRead(botaoFechar) == LOW)
    {
        emitirSom(som, frequenciaFechado, tempoEmitindoOSom);
        acendeLed(ledFechar, ledAbrir);
        driver.send((uint8_t *)fecha, strlen(fecha));
        driver.waitPacketSent();
        delay(200);
    }
}

void emitirSom(int porta, int frequencia, int tempo)
{
    tone(porta, frequencia, tempo);
    delay(600);
    noTone(porta);
}

void acendeLed(int portaLigar, int portaDesligar)
{
    digitalWrite(portaLigar, HIGH);
    digitalWrite(portaDesligar, LOW);
}