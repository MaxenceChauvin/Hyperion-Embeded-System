#include "Arduino.h"
#include "AccGyro.h"
#include <Wire.h>

// ---------------------------------------------------------------------------------
//
//
AccGyro::AccGyro() {
}

// ---------------------------------------------------------------------------------
//
//
void AccGyro::getData() {
  int16_t a;

  Wire.beginTransmission(MPU_addr);

  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers

  a=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcX = (a+32768)*1023/65536;

  a=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcY = (a+32768)*1023/65536;

  a=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  AcZ = (a+32768)*1023/65536;

  Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)

  a=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyX=a / 131;  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)

  a=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  GyY=a / 131;  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)

  a=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  GyZ =a / 131;

#if 0
  Serial.print(AcX); Serial.print(" ");
  Serial.print(AcY); Serial.print(" ");
  Serial.print(AcZ); Serial.print(" | ");
  Serial.print(Tmp/340.00+36.53); Serial.print(" | ");
  Serial.print(GyX); Serial.print(" ");
  Serial.print(GyY); Serial.print(" ");
  Serial.println(GyZ);
#endif
}

// ---------------------------------------------------------------------------------
//
//
void AccGyro::initState() {
  int i;

  Wire.begin();
  // init gyroscope MPU-6050
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);

  getData();

  SpX = 0;
  SpY = 0;
  SpZ = 0;
  PosX = 0;
  PosY = 0;
  PosZ = 0;
  begGyX = 0;
  begGyY = 0;
  begGyZ = 0;
  begAcX = AcX;
  begAcY = AcY;
  begAcZ = AcZ;

  for (i=0;i<500;i++) {
    getData();

    begGyX += GyX;
    begGyY += GyY;
    begGyZ += GyZ;

    begAcX = begAcX * 0.95 + AcX * 0.05;
    begAcY = begAcY * 0.95 + AcY * 0.05;
    begAcZ = begAcZ * 0.95 + AcZ * 0.05;

    delay(2);
  }

  begGyX /= 500;
  begGyY /= 500;
  begGyZ /= 500;

}

void AccGyro::getSpeed(long time1){
    getData();
    double deltatime = millis() - time1;
    //Serial.println(deltatime);
    //Serial.println(deltatime/1000);
    if (begAcX - AcX > 5 || begAcX - AcX < -5 )
        SpX = SpX + (deltatime/1000)*(begAcX - AcX);
    else SpX = 0;
    if (begAcX - AcX > 5 || begAcX - AcX < -5 )
        SpY = SpY + (deltatime/1000)*(begAcY - AcY);
    else SpY = 0;
    if (begAcX - AcX > 5 || begAcX - AcX < -5 )
        SpZ = SpZ + (deltatime/1000)*(begAcZ - AcZ);
    else SpZ = 0;
}

void AccGyro::getPosition(long time2){
    getData();
    double deltatime = millis() - time2;
    //Serial.println(deltatime);
    PosX = PosX + (deltatime/1000)*SpX;
    PosY = PosY + (deltatime/1000)*SpY;
    PosZ = PosZ + (deltatime/1000)*SpZ;
}

long AccGyro::getGyX() { return GyX; }
long AccGyro::getGyY() { return GyY; }
long AccGyro::getGyZ() { return GyZ; }

long AccGyro::getInitGyX() { return begGyX; }
long AccGyro::getInitGyY() { return begGyY; }
long AccGyro::getInitGyZ() { return begGyZ; }

long AccGyro::getAccX() { return AcX; }
long AccGyro::getAccY() { return AcY; }
long AccGyro::getAccZ() { return AcZ; }

long AccGyro::getInitAccX() { return begAcX; }
long AccGyro::getInitAccY() { return begAcY; }
long AccGyro::getInitAccZ() { return begAcZ; }

long AccGyro::getDeltaAccX() { return begAcX - AcX; }
long AccGyro::getDeltaAccY() { return begAcY - AcY; }
long AccGyro::getDeltaAccZ() { return begAcZ - AcZ; }

long AccGyro::getDeltaGyX() { return begGyX - GyX; }
long AccGyro::getDeltaGyY() { return begGyY - GyY; }
long AccGyro::getDeltaGyZ() { return begGyZ - GyZ; }

double AccGyro::getSpeedX() { return SpX; }
double AccGyro::getSpeedY() { return SpY; }
double AccGyro::getSpeedZ() { return SpZ; }

double AccGyro::getPosX() { return PosX; }
double AccGyro::getPosY() { return PosY; }
double AccGyro::getPosZ() { return PosZ; }
