

void BLE_main(){

//in main
//BLEDevice central = BLE.central();  // Wait for a BLE central to connect
//if (central) {
//   //Serial.println(counter);
////if(counter == 1000){ 
//if(once == 1){
//Serial.print("Connected to central MAC: ");
//Serial.println(central.address());
//once = 0;
//}
  
  
 counter =0;

//if start timer go into bleTask2 for auto update
//if button add go into bletask other for sending of data

reading = BLE_UUID_FlagChar_ADDDATA.value(); // should be interupt, possible interrupt because the value should be//only read once
reading_ble_append = BLE_UUID_FlagChar_APPEND_Write.value();

if(reading == 1 & prev_red == 0){
  reading_ble = 1;
  prev_red = reading;
}else{
  reading_ble = 0;
  prev_red = reading;
}


if(reading_ble_append == 1 & prev_red_append == 0){ // sets that button has been pressed
  Serial.print("here in red"); 
  prev_red_append = reading_ble_append;
}
else if(reading_ble_append == 0 & prev_red_append == 1){ // and here it stops appending once 0
  reading_append = 1;
  prev_red_append = 1;
}




if(flag == 4){// this is direct
//getdata();
 for (uint16_t  i = 0; i < 10000; i++) { // and connected
  Serial.print("here, i :");
  Serial.println(i);
 //sensorTask(buf[i][1],buf[i][2],buf[i][3]);
 //bleTask();
 

 //setflaglow
 }
 }

//sending the entire time
if(flag == 3 ){//&& otherflag == 1 //just make flag online
  
   for (uint16_t  i = 0; i < 50; i++) {
  Serial.print("Here");
   Serial.print( databuf[i][0] );
   Serial.print( ", " );
  Serial.print( databuf[i][1] );
   Serial.print( "," );
  Serial.println( databuf[1][2] );
//  sensorTask(databuf[i][0] ,databuf[i][1],databuf[i][2]);
//  bleTask();


  flag = 0;
 }
 databuf[1][0] = 21;
 databuf[1][1] = 21;
 databuf[1][2] = 21;
//sensorTask( databuf[1][0],databuf[1][1],databuf[1][2]);
 //bleTask();
  
//  if ( sensorTask() )
//  {
//    printTask();
//  }
//}
//counter = counter+1;
 }
 }
//}




void sensorTask(float val, float val1, float val2, float val4, float val5, float val6)
{

uint32_t previousMillis = 0;

  uint32_t currentMillis = millis();
  if ( currentMillis - previousMillis < SENSOR_UPDATE_INTERVAL )
  {
    sensorData.updated = false;
  }
  previousMillis = currentMillis;
//x_new,y_new,z_new
//  IMU.readAcceleration( x, y, z); 
//sensorData.Accel_X = x*1000000;


sensorData.Accel_X = val; // sneding filtered accel data// will send norm later
sensorData.Accel_Y = val1; // This can change rappidly since variable
sensorData.Accel_Z = val2;
sensorData.customVar_4 = val4 ;
sensorData.customVar_5 = val5;
sensorData.customVar_6 = val6;

//sensorData.Accel_X =10; /// make sure that it is long not float 
//Serial.print(sensorData.Accel_Y);
//Serial.print(",");
//Serial.println(sensorData.customVar_5);
//Serial.print(",");

//
// #ifdef REVERSE_BYTE_ORDER
//    sensorData.Accel_X = __REV( sensorData.Accel_X );
//   // sensorData.Accel_X = sensorData.Accel_X ;
// #endif
  //Serial.println(sensorData.Accel_X,HEX);
  sensorData.updated = true;

  //return sensorData.updated; // can be void with no return
}





bool setupBleMode()
{
  if ( !BLE.begin() )
  {
    return false;
  }

  // set advertised local name and service UUID
  BLE.setDeviceName( BLE_DEVICE_NAME );
  BLE.setLocalName( BLE_LOCAL_NAME );
  BLE.setAdvertisedService( footsensorService );

  // BLE add characteristics
  footsensorService.addCharacteristic( customAccelX );
  footsensorService.addCharacteristic( customAccelY );
  footsensorService.addCharacteristic( customAccelZ );
  footsensorService.addCharacteristic( customVar4 ); //extra here
  footsensorService.addCharacteristic( customVar5 );
  footsensorService.addCharacteristic( customVar6 );
  footsensorService.addCharacteristic(BLE_UUID_FlagChar_ADDDATA);
  footsensorService.addCharacteristic(BLE_floatflag);
  
  footsensorService.addCharacteristic(BLE_UUID_FlagChar_APPEND_Write);
  //footsensorService.addCharacteristic( norm ); // adding more charteristics

  // add service
  BLE.addService( footsensorService );

  // set the initial value for the characeristic

  // customAccelX.writeValue( sensorData.Accel_X );  
  customAccelX.writeValue( sensorData.Accel_X );  
  customAccelX.writeValue( sensorData.Accel_X );  
  customAccelX.writeValue( sensorData.Accel_X );  
  customAccelX.writeValue( sensorData.Accel_X );  
  customAccelX.writeValue( sensorData.Accel_X );  
  customAccelX.writeValue( sensorData.Accel_X );  
  
  customAccelX.writeValue(sensorData.Accel_X); // change here in order to 
  customAccelY.writeValue(sensorData.Accel_Y);
  customAccelZ.writeValue(sensorData.Accel_Z);
  customVar4.writeValue(sensorData.customVar_4);
  customVar5.writeValue(sensorData.customVar_5);
  customVar6.writeValue(sensorData.customVar_6);
  BLE_UUID_FlagChar_ADDDATA.writeValue(0); 
  BLE_floatflag.writeValue(0);

  BLE_UUID_FlagChar_APPEND_Write.writeValue(0);
  // set BLE event handlers
  BLE.setEventHandler( BLEConnected, blePeripheralConnectHandler );
  BLE.setEventHandler( BLEDisconnected, blePeripheralDisconnectHandler );

  // start advertising
  BLE.advertise();

  return true;
}


void bleTask()
{
  const uint32_t BLE_UPDATE_INTERVAL = 10;
  static uint32_t previousMillis = 0;

  uint32_t currentMillis = millis();
  if ( currentMillis - previousMillis >= BLE_UPDATE_INTERVAL )
  {
    previousMillis = currentMillis;
    BLE.poll();
  }



    //BLE_floatflag.writeValue(1);
//    Serial.print("flag: "); 
//    updateready = BLE_floatflag.value(); // should be interupt
//    Serial.print(updateready);

    
  if ( sensorData.updated) // updating data here && updateready == 1
  {
    // BLE defines Temperature UUID 2A6E Type sint16 ( see XML links )
    // Unit is in degrees Celsius with a resolution of 0.01 degrees Celsius
   // int16_t Accel_X = sensorData.Accel_X ;// maybe round because of work

    
//    BLE_floatflag.writeValue(0);//just test one
//    delay(500);
//
//    customAccelY.writeValue( sensorData.Accel_Y ); 
//    customAccelZ.writeValue( sensorData.Accel_Z );
//    Serial.print("flag_value: ");
//    Serial.println(BLE_floatflag.value());
//    sensorData.updated = false;
//    
//    delay(500); //delay in order to function
//    BLE_floatflag.writeValue(1);
//    
//    Serial.print("flag_value: ");
//    Serial.print(BLE_floatflag.value());
    
    customAccelX.writeValue( sensorData.Accel_X );  
    customAccelY.writeValue( sensorData.Accel_Y ); // replace this with the norm and then will have x,z, and norm
//    int test =1;
//    int test0 =0;
//    BLE_floatflag.writeValue(test0); // set update here
//    Serial.print("flag_value: ");
//    Serial.print(BLE_floatflag.value());
      customAccelZ.writeValue( sensorData.Accel_Z );
      customVar4.writeValue(sensorData.customVar_4);
      customVar5.writeValue(sensorData.customVar_5);
      customVar6.writeValue(sensorData.customVar_6);
//    sensorData.updated = false;
    delay(100); //delay in order to function
//    BLE_floatflag.writeValue(test);
//    
//    Serial.print("flag_value: ");
//    Serial.print(BLE_floatflag.value());
 
  }
}

void blePeripheralConnectHandler( BLEDevice central )
{
 // digitalWrite( BLE_LED_PIN, HIGH );
  Serial.print( F ( "Connected to central: " ) );
  Serial.println( central.address() );
}


void blePeripheralDisconnectHandler( BLEDevice central )
{
 // digitalWrite( BLE_LED_PIN, LOW );
  Serial.print( F( "Disconnected from central: " ) );
  Serial.println( central.address() );
  once = 1;
}
