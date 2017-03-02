//Auto Align for user control
task Claw(){

	integral = 0;

	while(true){

		if(vexRT[Btn6D] == true){

			//Gets the present error
			error = getMotorEncoder(Left_Claw) - getMotorEncoder(Right_Claw);

			//Takes into account the past values for error to change speed if needed.
			integral = integral + error;

			if(error == 0 || abs(error) > 40){
				integral = 0;
			}

			//Takes into acount the change in errors to predict future values, making the movement stable
			derivative = error - prevError;
			prevError = error;

			motor[Left_Claw] = motor[Right_Claw] = error*Kp + integral*Ki + derivative*Kd;




			}else if(vexRT[Btn6U] == true){

			error = getMotorEncoder(Left_Claw) - getMotorEncoder(Right_Claw);
			integral = integral + error;

			if(error == 0 || abs(error) > 40){
				integral = 0;
			}

			derivative = error - prevError;
			prevError = error;

			motor[Left_Claw] = motor[Right_Claw] = -1*(error*Kp + integral*Ki + derivative*Kd);

			}else{

			motor[Left_Claw] = 0;
			motor[Right_Claw] = 0;

		}

	}

}
