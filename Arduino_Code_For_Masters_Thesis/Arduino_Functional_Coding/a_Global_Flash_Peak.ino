
//-----Libraries-----
#include <Arduino_LSM9DS1.h>
#include "MadgwickAHRS.h"
#include <ArduinoBLE.h>
#include <avr/pgmspace.h> 
#include <PeakDetection.h> // import lib


// initialize a Madgwick filter:
Madgwick filter;

PeakDetection peakDetection; // create PeakDetection object




// lights

int triggered_LED = 0;

 #define RED 22     
 #define BLUE 24     
 #define GREEN 23
 #define LED_PWR 25

// sensor's sample rate is fixed at 104 Hz:

//----------------------------------------------------------------------------------------------------------------------
// Initialize flash
//----------------------------------------------------------------------------------------------------------------------


#include <stdlib.h>
#include <avr/dtostrf.h>

#define FS_NANO33BLE_VERSION_MIN_TARGET      "FS_Nano33BLE v1.2.0"
#define FS_NANO33BLE_VERSION_MIN             1002000

  #define BUF_SIZE                  7  //why 7? Because a float of 6 plus a .
#define _FS_LOGLEVEL_               1

// Min NANO33BLE_FS_SIZE_KB must be  64KB. If defined smalller => auto adjust to  64KB
// Max NANO33BLE_FS_SIZE_KB must be 512KB. If defined larger   => auto adjust to 512KB
#define NANO33BLE_FS_SIZE_KB        256

#define FORCE_REFORMAT              false

// Default USING_LITTLEFS. Uncomment to not USING_LITTLEFS => USING_FATFS.
// It's advisable not to use FATFS, as the NANO33BLE_FS_SIZE_KB must be auto-adjusted to 512KB
//#define USING_LITTLEFS              false

#include <FS_Nano33BLE.h>

#define START_COUNT_OVER            false
#define data_storage                true
#define Sense_Pressure              false

FileSystem_MBED *myFS;

char fileName[] = MBED_FS_FILE_PREFIX "/test.txt"; //global file name


//----------------------------------------------------------------------------------------------------------------------
//flash variables
//----------------------------------------------------------------------------------------------------------------------

#define useFlash         false // not used

float messagetest[600][6];
//float buf[6000][3];

int k_Fs, k2_Fs;
int flag_float;
 char buff[BUF_SIZE];
 int counter_float;
 int kstore;
 int counterflash = 0;
unsigned long timepopfloat;
unsigned long timeold;

//----------------------------------------------------------------------------------------------------------------------
// Global Variables
//----------------------------------------------------------------------------------------------------------------------

                                        //-----Accel-----
  #define useAccel      true
  #define useBLE        true
  #define Readfloat     true
  
  float sensorRate;
  int i,k ,flag, once, updateready;
  float x_new,y_new ,z_new ,GRAVITY , alpha; // this does not have to be global because I am not using iut throughout // will take up to much mem 
  // for now this is global // later on will use it else where
  float xAcc, yAcc, zAcc;
  float xGyro, yGyro, zGyro;
  float xMag, yMag, zmag;
  float q0,q1,q2,q3;
 float x_Low,y_Low,z_Low; 
 float x_norm,y_norm,z_norm , norm, norm2 ,normXZ;

  // values for orientation:
  float roll, pitch, heading;
  float Quat[4];
  float Gyro[4];
  float out[4];
  float Ae[4][1];
  float g[3];
  float Anew[3];
  //float buf[1000][3];
  

  const int ledPin = LED_BUILTIN;

                                       //-----Velocity-----


float vbuffer[100];
float errorbuff[100];
float timbuf[100];
float error_v;
float a;
float b; 
float Anew_50[100];

int ZVU = 1;
int samplesCount;int STATIC_SAMPLES_THRESHOLD = 10;
double STATIC_ACCELERATION_THRESHOLD = 2;
double STATIC_ANGULAR_VELOCITY_THRESHOLD = 60;
double STATIC_ACCELERATION_DIFF = 0.02;

int velflag; // get rid of floats
int counter_vel;
  unsigned long previousMillis = 5000;
  unsigned long myTime;
  unsigned long Test;


  float timestampflag, timestamp, velx , time_acceleration;
float v_old; //holds old value 

float vstart;
int Vel_flag_update;

                                        //-----Position-----
float s_old;
float pos =0;
float pos_step =0;
float Speed;

                                        //-----DataHnadling-----
float databuf[50][6];                                    
float time_data;
float time_data_start;
int data_counter = 0;  
int reading = 0;//start 0 and wait for set to 1 from ble
int reading_ble = 0;
int prev_red = 0;

int reading_append = 0;//start 0 and wait for set to 1 from ble
int reading_ble_append = 0;
int prev_red_append = 0;

  #define appendData     true
  #define readData     true


                                        //------PEAk-------//
int flag_peak2;
int flag_peak;

int peak_time_flag; 

int counter_peak;
int both;
int peak_counter_both; //counting peaks for cadence // the data might be missed
int peak_counter_peak1;
int peak_counter_peak2; 
float norm_mag;
float mag;
                
float filtered;
int peak;
float filtered2 ;

int peak2;                                 
float var;   


float time_er_peak;//time that has to pass 
//for a new peak to be valid
float time_peak; //time between two phasing peaks
float time_peak_dec;
float time_er_peak_c; 
float peak_first;
int steps;  

float timebetween_peak_start;
float timebetween_peak;

float time_test;


//step
int flag_peak_time;
int step_flag;
                                        //-----BLE-----


//BLE UUIDS_UPDATE later
#define BLE_UUID_FootsensorService                  "0000480f-0000-1000-8000-00805f9b34fb"
#define BLE_UUID_ACCEL_X                            "00002a11-0000-1000-8000-00805f9b34fb"
#define BLE_UUID_ACCEL_Y                            "00002a12-0000-1000-8000-00805f9b34fb"
#define BLE_UUID_ACCEL_Z                            "00002a13-0000-1000-8000-00805f9b34fb"
#define BLE_UUID_VAR_4                              "00002a16-0000-1000-8000-00805f9b34fb"
#define BLE_UUID_VAR_5                              "00002a17-0000-1000-8000-00805f9b34fb"
#define BLE_UUID_VAR_6                              "00002a18-0000-1000-8000-00805f9b34fb"


#define BLE_UUID_Flag_ADDDATA                        "00002a14-0000-1000-8000-00805f9b34fb" // one on MIT // ADD data button
#define BLE_UUID_Flag_Float                         "00002a15-0000-1000-8000-00805f9b34fb"

#define BLE_UUID_Flag_APPEND                         "00002a19-0000-1000-8000-00805f9b34fb" // one on MIT // ADD data button




#define BLE_DEVICE_NAME                           "Arduino Nano 33 BLE"
#define BLE_LOCAL_NAME                            "Arduino Nano 33 BLE"

#define SENSOR_UPDATE_INTERVAL                    (10000)





                  //____Pressure
#include <Wire.h>

//#include "BARO.h"

#define LPS225HB_ADDRESS  0x5C

#define LPS225HB_WHO_AM_I_REG        0x0f
#define LPS225HB_CTRL2_REG           0x11
#define LPS225HB_STATUS_REG          0x27
#define LPS225HB_PRESS_OUT_XL_REG    0x28
#define LPS225HB_PRESS_OUT_L_REG     0x29
#define LPS225HB_PRESS_OUT_H_REG     0x2a
#define LPS225HB_TEMP_OUT_L_REG      0x2b
#define LPS225HB_TEMP_OUT_H_REG      0x2c


bool press_check;
float presstest;

//#define REVERSE_BYTE_ORDER


BLEService footsensorService( BLE_UUID_FootsensorService );
//BLEUnsignedLongCharacteristic  customAccelX( BLE_UUID_ACCEL_X, BLERead | BLENotify );
BLEFloatCharacteristic customAccelX( BLE_UUID_ACCEL_X, BLERead | BLENotify); //float to send floats
BLEFloatCharacteristic customAccelY( BLE_UUID_ACCEL_Y, BLERead | BLENotify);
BLEFloatCharacteristic customAccelZ( BLE_UUID_ACCEL_Z, BLERead | BLENotify );
BLEFloatCharacteristic customVar4( BLE_UUID_VAR_4, BLERead | BLENotify); //float to send floats
BLEFloatCharacteristic customVar5( BLE_UUID_VAR_5, BLERead | BLENotify); //float to send floats
BLEFloatCharacteristic customVar6( BLE_UUID_VAR_6, BLERead | BLENotify); //float to send floats

BLEIntCharacteristic BLE_UUID_FlagChar_ADDDATA(BLE_UUID_Flag_ADDDATA, BLERead | BLEWrite);//need notify only for updating
BLEIntCharacteristic BLE_floatflag( BLE_UUID_Flag_Float, BLERead | BLENotify ); // rather write so you can double change


BLEIntCharacteristic BLE_UUID_FlagChar_APPEND_Write(BLE_UUID_Flag_APPEND, BLERead | BLEWrite);//need notify only for updating

typedef struct __attribute__( ( packed ) )  ///sent data that will be used for the BLE data
{
  float Accel_X; //uint32_t switch between float and other one and int32_t for singed
  float Accel_Y; 
  float Accel_Z; 
  float customVar_4;
  float customVar_5;
  float customVar_6;
  //float normAccel;   ///this is for norm data
  bool updated = false;
} sensor_data_t;

sensor_data_t sensorData = { .Accel_X = 0,.Accel_Y = 0,.Accel_Z = 0,.customVar_4 = 0,.customVar_5 = 0,.customVar_6 = 0, .updated = false }; // add norm here

int counter;

                                        
//----------------------------------------------------------------------------------------------------------------------
// Setup
//----------------------------------------------------------------------------------------------------------------------



void setup() { 

  
  delay(1000); // before eveything begins

   pinMode(D2, OUTPUT);
  digitalWrite(D2, LOW); // this always needs to be low at start unless battery will be implemented

   pinMode(D7, OUTPUT); //SCL/SDA high
  digitalWrite(D7, HIGH); 
  
 
 pinMode(BLUE, OUTPUT);
 digitalWrite(BLUE, HIGH); //This is off
 // pinMode(RED, OUTPUT);
 // pinMode(GREEN, OUTPUT);
 // pinMode(LED_PWR, OUTPUT);

  
  Serial.begin(9600);
                                          //------PEAk-------//
peakDetection.begin(10, 3, 0.5); // sets the lag, threshold and influence
peak_counter_peak1 = 0;
peak_counter_peak2 = 0;
peak_counter_both = 0;
  Wire.begin();

  time_er_peak = 0;//time that has to pass for a new peak to be valid
 time_peak = 0;
 time_peak_dec = 0;
  time_er_peak_c = 0;
///////////////////////////////////////////////////////
  //initializing variables 
  sensorRate = 50; // changing sensor value // why 50 and not lower?
    press_check = true;
  flag = 0;
  i = 0;
  k = 0;
  pinMode(ledPin, OUTPUT);
  
    float dt = (1.0 / 50.0);
    float RC = 0.35;
    alpha = dt / (RC + dt);
    GRAVITY = 1;
    x_new = 0;
    y_new = 0;
    z_new = 0;
     ///BLE
    counter = 0;

    k2_Fs = 0;
    k_Fs = 0;
    flag_float = 1;
    counter_float = 0;
    kstore = 1;


/////////////////////

float vbuffer[10];
float errorbuff[10];
float timbuf[10];
float error_v;
float a = 0;
float b = 0;;
float Anew_50[10] ;
   counter_vel = 0;
Vel_flag_update = 0;

//////

int peak_counter_both = 0; //counting peaks for cadence // the data might be missed
int peak_counter_peak1 = 0;
int peak_counter_peak2 = 0; 
peak_time_flag = 0;
peak_first = 0;
steps = 0;
timebetween_peak = 0;
timebetween_peak_start = 0;
time_test = 0;
/////
step_flag = 0;    
 /////////////////////////////////////////

timeold = 0;
 flag_peak_time = 0; //seting time to 0 only on first step. 

  
 // attempt to start the IMU:    
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU");
    // stop here if you can't access the IMU:
    while (true);
  }

//setup storage // can be seperate function
#if  data_storage
  Serial.print("\nStart FS_Counting on "); Serial.println(BOARD_NAME);
  Serial.println(FS_NANO33BLE_VERSION);


  #if defined(FS_NANO33BLE_VERSION_MIN)
  if (FS_NANO33BLE_VERSION_INT < FS_NANO33BLE_VERSION_MIN)
  {
    Serial.print("Warning. Must use this example on Version equal or later than : ");
    Serial.println(FS_NANO33BLE_VERSION_MIN_TARGET);
  }
#endif

  Serial.print("FS_size (KB) = "); Serial.println(NANO33BLE_FS_SIZE_KB);
  Serial.print("FS_ Start Address = 0x"); Serial.println(NANO33BLE_FS_START, HEX);
/////

//add to func
  myFS = new FileSystem_MBED();

   if (!myFS->init()) 
  {
    Serial.println("FS Mount Failed");
    
    return;
  }


  #if  START_COUNT_OVER
  Serial.print("Deleting file: "); Serial.print(fileName);
  
  if (remove(fileName) == 0) 
  {
    Serial.println(" => OK");
  }
  else
  {
    Serial.println(" => Failed");
  }
  #endif
#endif

  
 #if  Sense_Pressure  
     if ( !setupPress() )
  {
    Serial.println("Failed to initialize pressure sensor!");
    while ( 1 );
  }
 #endif 

   if ( !setupBleMode() )
  {
    Serial.println( "Failed to initialize BLE!" );
    while ( 1 );
  }


   //print_to_sheet();
  // start the filter to run at the sample rate:

  
  filter.begin(sensorRate); // using madwick
}



//----------------------------------------------------------------------------------------------------------------------
// Loop
//----------------------------------------------------------------------------------------------------------------------


void loop() {
  // values for acceleration and rotation:

  // check if the IMU is ready to read:
  if (IMU.accelerationAvailable() && //uses wire 1 
      IMU.gyroscopeAvailable()) {
    // read accelerometer &and gyrometer:
    IMU.readAcceleration(xAcc, yAcc, zAcc);
    IMU.readGyroscope(xGyro, yGyro, zGyro);
    IMU.readMagneticField(xMag, yMag, zmag);


//x_new,y_new,z_new  = accelfilter();
//printsingle(xAcc);

BLEDevice central = BLE.central();  // Wait for a BLE central to connect
if (central) {
   //Serial.println(counter);
//if(counter == 1000){ 
if(once == 1){
Serial.print("Connected to central MAC: ");
Serial.println(central.address());
once = 0;
}
acceldata_order();



//printdata();
datahandling();


// maybe send data that is needed to BLE, but wont be needed if it is global var
BLE_main(); // need to fix this for later // works but change interval and also it did not add file 1//interval will change a lot//look at timee(millis) by print line
//read here

}
  }


// presstest = readPressureOwn();
// Serial.print(presstest);
// delay(1000); //has to be delay
}
