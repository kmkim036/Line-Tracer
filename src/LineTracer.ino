#include <Servo.h>

Servo servoRight; // 우측 서보모터 선언
Servo servoLeft; // 좌측 서보모터 선언

// 3개의 IR센서를 각각 0, 1, 2번 핀에 연결
int IR_output0 = 0;
int IR_output1 = 1;
int IR_output2 = 2;

void setup()
{
    Serial.begin(9600);

    // IR센서가 연결된 핀을 각각 INPUT으로 설정
    pinMode(IR_output0, INPUT);
    pinMode(IR_output1, INPUT);
    pinMode(IR_output2, INPUT);

    servoRight.attach(12); // 우측 서보모터를 12번 핀에 연결
    servoLeft.attach(13); // 좌측 서보모터를 13번 핀에 연결
}

void loop()
{
    // 트랙 인식 여부 판단을 위한 문턱값 설정
    int threshold = 650;

    // IR센서가 연결된 각 핀에서의 값을 IR_Value의 각 값으로 설정
    int IR_Value0 = analogRead(IR_output0);
    int IR_Value1 = analogRead(IR_output1);
    int IR_Value2 = analogRead(IR_output2);

    if ((IR_Value0 < threshold) && (IR_Value1 < threshold) && (IR_Value2 < threshold)) {
        // 3개의 센서가 □□□을 인식하면 stop
        Serial.println("0 0 0 => stop");
        servoLeft.writeMicroseconds(1500);
        delay(30);
        servoRight.writeMicroseconds(1500);
        delay(30);
    } else if ((IR_Value0 < threshold) && (IR_Value1 < threshold) && (IR_Value2 >= threshold)) {
        // 3개의 센서가 □□■을 인식하면 우회전
        Serial.println("0 0 1 => right");
        servoLeft.writeMicroseconds(1700);
        delay(30);
        servoRight.writeMicroseconds(1700);
        delay(30);
    } else if ((IR_Value0 < threshold) && (IR_Value1 >= threshold) && (IR_Value2 >= threshold)) {
        // 3개의 센서가 □■■을 인식하면 우회전
        Serial.println("0 1 1 => right");
        servoLeft.writeMicroseconds(1700);
        delay(30);
        servoRight.writeMicroseconds(1700);
        delay(30);
    } else if ((IR_Value0 >= threshold) && (IR_Value1 < threshold) && (IR_Value2 >= threshold)) {
        // 3개의 센서가 ■□■을 인식하면 후진
        Serial.println("1 0 1 => backward");
        servoLeft.writeMicroseconds(1300);
        delay(30);
        servoRight.writeMicroseconds(1700);
        delay(30);
    } else if ((IR_Value0 >= threshold) && (IR_Value1 >= threshold) && (IR_Value2 >= threshold)) {
        // 3개의 센서가 ■■■을 인식하면 전진
        Serial.println("1 1 1 => forward");
        servoLeft.writeMicroseconds(1700);
        delay(30);
        servoRight.writeMicroseconds(1300);
        delay(30);
    } else if ((IR_Value0 < threshold) && (IR_Value1 >= threshold) && (IR_Value2 < threshold)) {
        // 3개의 센서가 □■□을 인식하면 전진
        Serial.println("0 1 0 => forward");
        servoLeft.writeMicroseconds(1700);
        delay(30);
        servoRight.writeMicroseconds(1300);
        delay(30);
    } else if ((IR_Value0 >= threshold) && (IR_Value1 < threshold) && (IR_Value2 < threshold)) {
        // 3개의 센서가 ■□□을 인식하면 좌회전
        Serial.println("1 0 0 => left");
        servoLeft.writeMicroseconds(1300);
        delay(30);
        servoRight.writeMicroseconds(1300);
        delay(30);
    } else {
        // 3개의 센서가 ■■□을 인식하면 좌회전
        Serial.println("1 1 0 => left");
        servoLeft.writeMicroseconds(1300);
        delay(30);
        servoRight.writeMicroseconds(1300);
        delay(30);
    }
}
