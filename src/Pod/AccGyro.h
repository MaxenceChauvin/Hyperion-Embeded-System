#ifndef AccGyro_h
#define AccGyro_h

#include "Arduino.h"

#define MPU_addr 0x68  // I2C address of the MPU-6050

class AccGyro {
	public:
		AccGyro();
		void getData();
		void initState();
		void getSpeed(long time1);
		void getPosition(long time1);

		long getGyX();
		long getGyY();
		long getGyZ();

		long getInitGyX();
		long getInitGyY();
		long getInitGyZ();

		long getAccX();
		long getAccY();
		long getAccZ();

		long getInitAccX();
		long getInitAccY();
		long getInitAccZ();

		long getDeltaAccX();
		long getDeltaAccY();
		long getDeltaAccZ();

		long getDeltaGyX();
		long getDeltaGyY();
		long getDeltaGyZ();

		double getSpeedX();
		double getSpeedY();
		double getSpeedZ();

		double getPosX();
		double getPosY();
		double getPosZ();

	private:
		long AcX,AcY,AcZ;
		long Tmp;
		long GyX,GyY,GyZ;
		double SpX,SpY,SpZ;
		double PosX,PosY,PosZ;

		// initial state
		long begGyX, begGyY, begGyZ;
		long begAcX, begAcY, begAcZ;
};

#endif
