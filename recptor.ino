#include <RH_ASK.h>
#include <SPI.h>
#include <ServoTimer2.h>

RH_ASK driver;
ServoTimer2 servo;

String str = "";
#define pinoServo 7
int statusServo = 0;
int pos = 0;

void setup()
{
    Serial.begin(9600);
    Serial.println("setup");
    servo.attach(7);

    if (!driver.init())
    {
        Serial.println("falhou");
    }

    driver.init();
}

void loop()
{

    uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
    uint8_t buflen = sizeof(buf);

    if (driver.recv(buf, &buflen))
    {
        Serial.println("recebe...");
        str = "";
        int i;

        for (int i = 0; i < buflen; i++)
        {
            str += (char)buf[i];
        }

        if ((str.equals("abre")) && statusServo == 0)
        {
            statusServo = 1;
            servo.write(2700);
            Serial.println("roda pro 360");
        }
        else
        {
            if ((str.equals("fecha")) && statusServo == 1)
            {
                statusServo = 0;
                servo.write(0);
                Serial.println("roda pro 0");
            }
        }
    }
}