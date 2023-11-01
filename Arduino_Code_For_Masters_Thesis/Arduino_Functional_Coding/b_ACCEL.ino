
//float accelfilter(){
//
//float x_Low,y_Low,z_Low; // just funtion variable
//float x_out,y_out,z_out;
//
////pretty sure x_low resets or x_out resets
//Serial.print(x_Low);
//Serial.print(",");
//Serial.println(x_out);
//
//// jip
//
//  x_Low = ((alpha * xAcc) + (1.0 - alpha) * x_out); //filtering data here....The time frame does not compare to the correct gyro and mag data
//  y_Low = ((alpha * yAcc) + (1.0 - alpha) * y_out);
//  z_Low = ((alpha * zAcc) + (1.0 - alpha) * z_out);  
//  x_out = x_Low;
//  y_out = y_Low;
//  z_out = z_Low;
//  
//
//  return x_out,y_out,z_out;
//}




void acceldata_order(){

//if(useaccel == true){
//  
//}

// filter can be its own, then just have Alpha and xAcc coming in and X_new going out
//  low passfilter?? APlha = ?
  x_Low = ((alpha * xAcc) + (1.0 - alpha) * x_new); //filtering data here....The time frame does not compare to the correct gyro and mag data
  y_Low = ((alpha * yAcc) + (1.0 - alpha) * y_new);
  z_Low = ((alpha * zAcc) + (1.0 - alpha) * z_new);  
  x_new = x_Low;
  y_new = y_Low;
  z_new = z_Low;
  
//filtered accel values to send to BLE
//printdata();

x_norm = pow(x_new, 2);
y_norm = pow(y_new, 2);
z_norm = pow(z_new, 2);




norm = (x_norm) + (y_norm) + (z_norm);//magniture 
normXZ = sqrt(x_norm +z_norm);
norm2 = (sqrt(norm)-0.98); //Gravity avg
mag =  pow(zGyro, 2) + pow(yGyro, 2);
norm_mag = sqrt(mag);

 double data = (double)norm2; // this will be 10 behind, same as velocity
 double data2 = (double)norm_mag;
 peakDetection.add(data); // adds a new data point
 peakDetection.add2(data2); 

  filtered = (float)peakDetection.getFilt(); // moving average
  peak = peakDetection.getPeak();
  filtered2 = (float) peakDetection.getFilt2(); // moving average
  peak2 = peakDetection.getPeak2();
  var = (float) peakDetection.getVar();

  time_er_peak = time_er_peak +1 ;//timeing off ...try counter //time that has to pass for a new peak to be valid
  
  time_test = time_er_peak - time_er_peak_c; //time_test so that I can check var
  
  //time_test = time_er_peak - time_er_peak_c; //time_test so that I can check var



     if(time_test >= 40){ //it works but for some reasoon when it goes to 2 it does not drop at the right time, 
        //cant go to 0 if in peak 
          peak_first = 0;
//         peak_time_flag = 1;
     }
  
 if(peak == 1 || peak2 == 1){ // for counter start 
      //count here this gives a wait of 3 

       
       if(peak == 1){
         flag_peak = 1;
         peak_counter_peak1++; //counts peaks
         time_er_peak_c = time_er_peak;
         peak_first++; // first peak, can only be reset in count 
        // time_peak_dec = millis(); //time between two phasing peaks
          time_peak = millis();
         time_test = time_er_peak - time_er_peak_c; //pushes it to 0         
      }
      


      
      if(peak2 == 1){
         flag_peak2 = 1;
         peak_counter_peak2++;//counts peaks because catching the peak might be hard
      }
     
      counter_peak++;
      if(counter_peak== 5){// rep of 4 before it fails
        flag_peak = 0;
        flag_peak2 = 0;
        counter_peak = 0;
      }
      if(flag_peak == 1 && flag_peak2 ==1 && peak_first == 1) { //5ms delay so that it does nto get picked up && data =>0.5 might have to use filtered, because it is delayed by 10 //  && (time_er_peak - time_er_peak_c) >= 5)
       both = 3; // 3 to easily identify the peaks
       flag_peak2 = 0;
       flag_peak = 0;
       counter_peak = 0;
       peak_counter_both++;  
       step_flag++;
              
    }
      
    }else{
       both = 0; 
    }
if(step_flag == 2){//when step detected 
  if(flag_peak_time == 0){
    time_peak =  0; //time_peak_dec
    flag_peak_time = 1;
  }
  steps++; // counting steps here
  if(steps == 0){//when step is 0
    timebetween_peak_start = time_peak;
    //pos= pos - pos 
  }
  timebetween_peak = time_peak - timebetween_peak_start;  // this works wow except for the first one 
  timebetween_peak_start = time_peak;
  step_flag = 0;
  Speed = (pos - pos_step)/(timebetween_peak/1000);
  pos_step = pos;
}

    
//Serial.print(filtered);
//Serial.print(",");
//Serial.print(peak);
//Serial.print(",");
//Serial.print("Data2>>");
//Serial.print(",");
//Serial.print(filtered2);
//Serial.print(",");
//Serial.print(peak2);
//Serial.print(",");
//Serial.print(peak_counter_peak1);
//Serial.print(",");
//Serial.print(peak_counter_peak2);
//Serial.print(",");
//Serial.print(peak_counter_both);
//Serial.print(",");
//Serial.println(both);

 
filter.update(xGyro, yGyro, zGyro, x_new, y_new, z_new ,xMag, yMag, zmag);


    roll = filter.getRoll();
    pitch = filter.getPitch(); 
    heading = filter.getYaw();
    q0 = filter.getq0();
    q1 = filter.getq1();
    q2 = filter.getq2();  
    q3 = filter.getq3();


 
   Quat[0]= q0;//printing quaternion
    Quat[1] = q1;
    Quat[2] = q2;
    Quat[3] = q3;
    
    //Gyro
    Gyro[0]= xGyro;//printing quaternion
    Gyro[1] = yGyro;
    Gyro[2] = zGyro;
    
  g[0] = 2 * (Quat[1] * Quat[3] - Quat[0] * Quat[2]) * GRAVITY;
  g[1] = 2 * (Quat[0] * Quat[1] + Quat[2] * Quat[3]) * GRAVITY;
  g[2] = (Quat[0] * Quat[0] - Quat[1] * Quat[1] - Quat[2] * Quat[2] + Quat[3] * Quat[3]) * GRAVITY;
    
   Ae[0][1] = 0;
   Ae[1][1] = {x_new};
   Ae[2][1] = {y_new};
   Ae[3][1] = {z_new};

// used for velocity but wont use for gait
Anew[0] = (Ae[1][1] - g[0]); // should be plus when there is side movements -  works fine now
Anew[1] = (Ae[2][1] + g[1]); // buffer, just holds one float value 
Anew[2] = (Ae[3][1] - g[2])
;

//cant be ever be true if I keep reseting thus always 1 until move

if(zeroVelocityUpdate(Anew,Gyro)!= true) // not true because it must zero right after velx only every 10. Then also the zvu because 
  {ZVU = 0;}
  else {
    velx = 0;
  }

  
 time_acceleration = millis(); // accel time



 if(ZVU == 0){

     if(timestampflag == 0){ //setting timestamp, will go back to 0 when zvu goes to 1 again
        timestamp  = time_acceleration; //ti
        timestampflag = 1; // only run once
     }
     
    if(Vel_flag_update == 1){
      velx = getvelocity(timestamp);
      velx = velx*0.38;//lower the veloctity //if this is to high then the the error is to big 0.35 works well ..will try 0.4 next
      Vel_flag_update = 0;
      pos = integrate_pos(velx,timestamp);
    
     }   
     if(Vel_flag_update == 0){
       getvelocity(timestamp); //send ti, time acceleration is global //think this is just to keep the counter active and processing.
     }
//           Serial.print("Velix :");
//    Serial.println(velx);
//    if(Vel_flag_update == 1 && Vel_flag_update)
 }


 //storage of data in flash
 
//timepopfloat = millis();
//if(timepopfloat - timeold >= 1000){ // here the value   every second print
//if(k_Fs <= 300){ // get time with calculation 1000 times
//
//  messagetest[k_Fs][0] = {x_norm};
//  messagetest[k_Fs][1] = {y_norm};
//  messagetest[k_Fs][2] = {z_norm};
//  
//  Serial.print("in, k:");
//  Serial.println(k);
//   Serial.print("messagetest 2 : ");
//  Serial.println(messagetest[k_Fs][1]);
//  k = k+1; // happeens fast so need to set up
//
// if(k2_Fs == 299){  // needs to be global stop
//
//  //appendFilelarge(fileName , 299); // filenane plus loopsize
//
//Serial.println(k2_Fs);
//  k2_Fs = 0;
//}
// k_Fs = k_Fs+1; // happeens fast so need to set up
//  k2_Fs = k2_Fs+1;
//
//}
//
//timeold = timepopfloat;
//Serial.println(timeold);
//}
//getdata();
}
