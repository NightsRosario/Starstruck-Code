//Code that we need for PID
int driveEnc = getMotorEncoder(Left_Back_Drive);
float Kp = 0.5;
float Ki = 0.2;
float Kd = 0.1;
float driveTarget;
float liftTarget;
float clawTarget;
float error;
float integral;
float derivative;
float prevError;

#include "Claw_Alignment.h"

task MoveForward(){

	resetMotorEncoder(Left_Back_Drive);
	resetMotorEncoder(Left_Claw);
	resetMotorEncoder(Right_Claw);
	resetMotorEncoder(Right_Back_Drive);


	integral = 0;
	driveTarget = 1800;

	while (getMotorEncoder(Left_Back_Drive) <= driveTarget || getMotorEncoder(Right_Back_Drive) <= driveTarget){

		error = (driveTarget) - (driveEnc);
		integral = integral + error;

		if(error == 0 || abs(error) > 40){
			integral = 0;
		}

		derivative = error - prevError;
		prevError = error;

		motor[Left_Front_Drive] = motor[Left_Back_Drive] = motor[Right_Back_Drive] = motor[Right_Front_Drive] = Kp*error + Ki*integral + Kd*derivative;

		if(getMotorEncoder(Left_Back_Drive) == error){

			clearTimer(T1);

		}

		if(time1[T1] == 500){

			startTask(Claw_Close);
			stopTask(MoveForward);

		}

	}

}






task Dump(){

	resetMotorEncoder(Left_Back_Drive);
	resetMotorEncoder(Left_Claw);
	resetMotorEncoder(Right_Claw);
	resetMotorEncoder(Right_Back_Drive);
	SensorValue[leftLiftPot] = 0;
	SensorValue[rightLiftPot] = 0;


	integral = 0;
	driveTarget = 2500;

	//Section for drive
	while (getMotorEncoder(Left_Back_Drive) <= driveTarget || getMotorEncoder(Right_Back_Drive) <= driveTarget){

		error = (driveTarget) - (driveEnc);
		integral = integral + error;

		if(error == 0 || abs(error) > 40){
			integral = 0;
		}

		derivative = error - prevError;
		prevError = error;

		motor[Left_Front_Drive] = motor[Left_Back_Drive] = motor[Right_Back_Drive] = motor[Right_Front_Drive] = Kp*error + Ki*integral + Kd*derivative;


		//Section for lift
		while (SensorValue[leftLiftPot] <= liftTarget || SensorValue[rightLiftPot] <= liftTarget){

			error = (liftTarget) - (driveEnc);
			integral = integral + error;

			if(error == 0 || abs(error) > 40){
				integral = 0;
			}

			derivative = error - prevError;
			prevError = error;

		}

		if(SensorValue[leftLiftPot] == error){

			clearTimer(T2);

		}

		if(time1[T2] == 500){

			startTask(Claw_Open);
			stopTask(Dump);

		}

	}

}





//Code to make a 45 degree turn hopefully...
task Turn45(){


	resetMotorEncoder(Left_Back_Drive);
	resetMotorEncoder(Left_Claw);
	resetMotorEncoder(Right_Claw);
	resetMotorEncoder(Right_Back_Drive);


	integral = 0;
	driveTarget = 2500;

	while (getMotorEncoder(Left_Back_Drive) <= driveTarget || getMotorEncoder(Right_Back_Drive) <= driveTarget){

		error = (driveTarget) - (driveEnc);
		integral = integral + error;

		if(error == 0 || abs(error) > 40){
			integral = 0;
		}

		derivative = error - prevError;
		prevError = error;

		motor[Left_Front_Drive] = motor[Left_Back_Drive] = -1*(Kp*error + Ki*integral + Kd*derivative);
		motor[Right_Front_Drive] = motor[Right_Back_Drive] = Kp*error + Ki*integral + Kd*derivative;

		if(getMotorEncoder(Left_Back_Drive) == error){

			clearTimer(T1);

		}

		if(time1[T1] == 500){

			startTask(Dump);
			stopTask(Turn45);

		}

	}

}



//Whole 1st auton
task Auton1(){

	startTask(MoveForward);

}
