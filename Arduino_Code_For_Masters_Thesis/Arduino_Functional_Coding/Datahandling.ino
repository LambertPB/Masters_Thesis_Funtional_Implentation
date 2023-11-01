void datahandling(){

  //only store every 0.2s and on every 10s send data
  //if(senddata_instant == 1({} // only ble

  //if(not instant)
    
  
  time_data = millis();

//  
  if(time_data - time_data_start >= 5)// 200 millisecs //Online live
  {
//  databuf[data_counter][0] = Anew[0];
//  databuf[data_counter][1] = Gyro[0];// norm2;
//  databuf[data_counter][2] = velx;//this is 10 behind and so is filtered
//   databuf[data_counter][3] = pos;//xAcc
//  databuf[data_counter][4] = filtered;
//  databuf[data_counter][5] = peak*5;
////
////  databuf[data_counter][0] = filtered;
////  databuf[data_counter][1] = peak*5;
////  databuf[data_counter][2] = both*10;//this is 10 behind and so is filtered
////   databuf[data_counter][3] = var;//xAcc
////  databuf[data_counter][4] = time_er_peak_c;
//// // databuf[data_counter][5] = peak2*-5;
//  
//  
//
////  Serial.print( "databuf = " );
//  Serial.print( databuf[data_counter][0] );
//   Serial.print( ", " );
//  Serial.print( databuf[data_counter][1] );
//   Serial.print( "," );
////    Serial.print( flag);
////   Serial.print( "," );
//  
//  Serial.print( databuf[data_counter][2] );
//  Serial.print( ", " );
//  Serial.println( databuf[data_counter][3] );
////  Serial.print( ", " );
////  Serial.println( databuf[data_counter][4] );
////  Serial.print( ", " );
////  Serial.println( databuf[data_counter][5] );   
//  time_data_start = time_data;


  if(data_counter == 50){


  //online
  flag = 5; //should be 3 so it can print in ble for online
 // sensorTask()

    data_counter = -1;
  }

  

  data_counter = data_counter + 1;
  }



/////




/////
//flash

//timepopfloat
if(appendData == true){

if((reading_ble_append  == 1) & (reading_append == 0)){ // read once
  
if(time_data - timeold >= 30){ // here the value   every second print //smaller not ideal jsut to fast
  
if(k_Fs <= 300){ // get time with calculation 1000 times

//  messagetest[k_Fs][0] = {Anew[0]};
//  messagetest[k_Fs][1] = {norm2};
//  messagetest[k_Fs][2] = {velx};
//  messagetest[k_Fs][3] = {xAcc};
//  messagetest[k_Fs][4] = {yGyro};
//  messagetest[k_Fs][5] = {zGyro};


  messagetest[k_Fs][0] = {filtered};
  messagetest[k_Fs][1] = {velx};
  messagetest[k_Fs][2] = {pos};
  messagetest[k_Fs][3] = {steps};
  messagetest[k_Fs][4] = {Speed};
  messagetest[k_Fs][5] = {timebetween_peak/1000};
//
//  Serial.print(Anew[0]); //X
//  Serial.print(",");
//  Serial.print(norm2);//Z
//  Serial.print(",");
//  Serial.print(velx);
//  Serial.print(",");
//  Serial.println(Anew[2]);
  
//   Serial.print("Anew");
//  Serial.print(Anew[0]);
//   Serial.print(": n  orm");
//  Serial.print(norm2);
//   Serial.print(": velx :");
//  Serial.print(velx);
//  Serial.print(": messagetest 1 : ");
//  Serial.print(messagetest[k_Fs][0]);
//    Serial.print(": messagetest 2 : ");
//  Serial.print(messagetest[k_Fs][1]);
//   Serial.print(": messagetest 3 : ");
//  Serial.print(messagetest[k_Fs][2]);
//  Serial.print(": messagetest 4 : ");
//   Serial.print(messagetest[k_Fs][3]);
//   Serial.print(": messagetest 5 : ");
  //    Serial.print(messagetest[k_Fs][4]);
  //   Serial.print(": messagetest 6 : ");
//   Serial.println(messagetest[k_Fs][5]);
 // k = k+1; // happeens fast so need to set up
 if(counterflash < 1){//for now only 6 stored values
 if(k2_Fs == 300){  // needs to be global stop
  kstore = 0; //set low here...This does not make sense
  appendFilelarge(fileName , 300); // filenane plus loopsize

  counterflash = counterflash +1;
//Serial.println(k2_Fs);
  k2_Fs = -1; // here the problem lies this was 0 and thus never sent updated the first itereations 
  k_Fs = -1;

//  if(triggered_LED == 0){
//   digitalWrite(BLUE, LOW); //ON
//   triggered_LED = 1;
//  }else{
//   digitalWrite(BLUE, HIGH); //OFF
//   triggered_LED = 0;
//  }
  
}
 }
 else if(counterflash >= 1){
  digitalWrite(LED_BUILTIN, HIGH); 
 }
 k_Fs = k_Fs+1; // happeens fast so need to set up
  k2_Fs = k2_Fs+1;

}


timeold = time_data;
//Serial.println(timeold);
}
//Serial.println("Inreading");
 //reading_ble_append  = 0;
}
}

if(readData == true){
  if(reading_ble == 1){ // read once
//    Serial.println("readdata");
   readFile(fileName); //can use getdata();
    Serial.println("Inreading");
  reading_ble = 0;
  }

}



  

}
