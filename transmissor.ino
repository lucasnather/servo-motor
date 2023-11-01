#include <RH_ASK.h>
#include <SPI.h>

RH_ASK driver;
#define botaoAbrir 2
#define botaoFechar 4

void setup()
{
    Serial.begin(9600);
    pinMode(botaoAbrir, INPUT_PULLUP);
    pinMode(botaoFechar, INPUT_PULLUP);

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
        driver.send((uint8_t *)abre, strlen(abre));
        driver.waitPacketSent();
        delay(200);
    }

    if (digitalRead(botaoFechar) == LOW)
    {
        driver.send((uint8_t *)fecha, strlen(fecha));
        driver.waitPacketSent();
        delay(200);
    }
}