task DriveForward(){

	resetMotorEncoder(Left_Drive);
  resetMotorEncoder(Right_Drive);

  while(abs(getMotorEncoder(Left_Drive)) < 200 && getMotorEncoder(Right_Drive) < 200){

  	motor[Left_Drive] = 70;
 	 	motor[Right_Drive] = 70;

 	}

  motor[Left_Drive] = 0;
  motor[Right_Drive] = 0;

}
