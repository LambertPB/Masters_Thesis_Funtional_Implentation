void printTask()
{
  Serial.print( "Accel_X = " );
  Serial.print( sensorData.Accel_X );
  Serial.print(",");
  Serial.print( "Accel_Y = " );
  Serial.print( sensorData.Accel_Y );
  Serial.print(",");
  Serial.print( "Accel_Z = " );
  Serial.print( sensorData.Accel_Z );
  //Serial.print(",");
  //Serial.print(x);
  Serial.println( "," );
  
}

void printdata(){


// Serial.print(Ae[1][1]);
//  Serial.print(",");
//  Serial.print(Ae[2][1]);
//  Serial.print(",");
//  Serial.print(Ae[3][1]);
//  Serial.print(",");
//  Serial.print(Quat[0]);
//  Serial.print(",");
//  Serial.print(Quat[1]);
//  Serial.print(",");
//  Serial.print(Quat[2]);
//  Serial.print(",");
//  Serial.print(Quat[3]);
//  Serial.print(","); 
//    
//  Serial.print(Gyro[0]);
//  Serial.print(",");
//  Serial.print(Gyro[1]);
//  Serial.print(",");
//  Serial.print(Gyro[2]);
//  Serial.print(",");
//  

  Serial.print(x_new);
  Serial.print(",");
  Serial.print(y_new);
  Serial.print(",");
  Serial.print(z_new);
  Serial.print(",");
  Serial.println(norm);

//  Serial.print(Anew[0]);
//  Serial.print(",");
//  Serial.print(Anew[1]);
//  Serial.print(",");
//  Serial.println(Anew[2]);
//   
////  Serial.print("Orientation: ");
//  Serial.print(",");
//  Serial.print(heading);
//  Serial.print(",");
//  Serial.print(pitch);
//  Serial.print(",");
//  Serial.println(roll);
  
}


void print_to_sheet(){
   // Serial.println("LABEL,Ax,Ay,Az,Gx,Gy,Gz,Mx,My,Mz");
  Serial.println("LABEL,Ae1,Ae2,Ae3,Ae4,Q1,Q2,Q3,Q4,Out1");
}

void printsingle(float single){
Serial.print("The word");
Serial.println(single);
}

void getdata(){
//if called and data 0 then send data else dont send easy


if(k_Fs>300 && flag_float == 1 ){ //when k 300 // only read once
 Serial.println("Here");
   readFile(fileName);
   flag_float = 0;
}

  
}
  
