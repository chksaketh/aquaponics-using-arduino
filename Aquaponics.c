#include <Wire.h>
#include <LiquidCrystal.h>
#include <OneWire.h>
#include <SoftwareSerial.h>
#include <Servo.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

const int pingPin = 7; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 6; // Echo Pin of Ultrasonic Sensor
long duration;
int distance;

// SoftwareSerial mySerial(10, 11);
const int bz = A4;
int kk = 0;
Servo feed;
int ts = A0;
int ps = A1;
int is = A3;
int mp1 = 3;
int mp2 = 4;

void setup() {
    Wire.begin();
    Serial.begin(9600);
    pinMode(pingPin, OUTPUT);
    pinMode(echoPin, INPUT);
    // mySerial.begin(115200);
    sensors.begin();
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("AQUA MNTRNG");
    feed.attach(5);
    pinMode(mp1, OUTPUT);
    pinMode(mp2, OUTPUT);
    pinMode(bz, OUTPUT);
    // wifi_init();
    feed.write(0);
    digitalWrite(bz, 0);
    digitalWrite(mp1, 0);
    digitalWrite(mp2, 0);
    pinMode(ts, INPUT);
    pinMode(ps, INPUT);
    pinMode(is, INPUT);
    delay(2000);
}

void loop() {
    digitalWrite(pingPin, LOW);
    delayMicroseconds(2);
    digitalWrite(pingPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(pingPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration / 2) / 29.1;

    int tbval = analogRead(ts) / 20;
    int pval = analogRead(ps) / 105;
    int irval = 1 - digitalRead(is);
    sensors.requestTemperatures();
    int tval = sensors.getTempCByIndex(0);

    digitalWrite(mp1, 1);
    delay(3000);
    digitalWrite(mp1, 0);

    lcd.clear();
    lcd.print("T:" + String(tval) + " TB:" + String(tbval) + " P:" + String(pval));
    lcd.setCursor(0, 1);
    lcd.print("IR:" + String(irval) + " L:" + String(distance));

    if (irval == 1) {
        feed.write(0);
        delay(200);
    } else {
        digitalWrite(bz, 1);
        feed.write(60);
        delay(200);
        digitalWrite(bz, 0);
    }

    if (distance > 7) {
        digitalWrite(mp2, 1);
    } else {
        digitalWrite(mp2, 0);
    }

    delay(300);
}

// void wifi_init() {
//     mySerial.println("AT+RST");
//     delay(4000);
//     mySerial.println("AT+CWMODE=3");
//     delay(4000);
//     mySerial.print("AT+CWJAP=");
//     mySerial.write('"');
//     mySerial.print("prudhvi"); // ssid/user name
//     mySerial.write('"');
//     mySerial.write(',');
//     mySerial.write('"');
//     mySerial.print("12345678"); // password
//     mySerial.write('"');
//     mySerial.println();
//     delay(1000);
// }

// void upload(int x, int y, int z, int p, int q) {
//     String cmd = "AT+CIPSTART=\"TCP\",\"";
//     cmd += "184.106.153.149"; // api.thingspeak.com
//     cmd += "\",80";
//     mySerial.println(cmd);
//     delay(1000);
//     String getStr = "GET /update?api_key=OTCJ2EFTTX3C3S8U&field1=";
//     getStr += String(x);
//     getStr += "&field2=";
//     getStr += String(y);
//     getStr += "&field3=";
//     getStr += String(z);
//     getStr += "&field4=";
//     getStr += String(p);
//     getStr += "&field5=";
//     getStr += String(q);
//     getStr += "\r\n\r\n";
//     cmd = "AT+CIPSEND=";
//     cmd += String(getStr.length());
//     mySerial.println(cmd);
//     delay(1000);
//     mySerial.println(getStr);
// }
