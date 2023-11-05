float getvelocity(float ti){ // Need t0_ti and then final Ti and then need 


if(velflag == 0){ // intialiaze only once every start

  counter_vel = 0;
  velflag = 1;
}

float dt = (time_acceleration - ti)/1000;//should be devided by 1000
//float dt_er= dt_er + dt;//increment by 9 every 9ms
float dv = Anew[0] * (dt) * 0.5; //time in between readings but should atualy be a measurement input we also know the output HZ so should not be a problem

 

//v = v_old + dv - error_v;
float v = v_old + dv ; //time 0.5
v_old = v;

//will only be 50 beind, maybe global

vbuffer[counter_vel] = v; //goes to 100/sample rate and then start repopulating
timbuf[counter_vel] = (time_acceleration - ti)/1000; // 
errorbuff[counter_vel] = error_v;
Anew_50[counter_vel] = Anew[0];//old values;
//
float vf = vbuffer[counter_vel] - errorbuff[counter_vel]; //after 100 vf should be correct for past...thus always sample rate behind

if(counter_vel == 10)//sample rate every 10 samples
{
 a =(v - vstart)/(time_acceleration - ti)/1000; // can reset // Must start at 0
 b = v - a*(time_acceleration - ti)/1000; // can reset

 
vstart = v; //shifting the line
ti = time_acceleration; //shifting the line


counter_vel = 0;
}
//velocitycounter; //counter for velocity buffer should be Sample rate behind vbuff
float tuse = timbuf[counter_vel];
error_v = a*tuse + b; // can reset

//time_acceleration_last = time_acceleration;

counter_vel++;
//Serial.print(",");
//Serial.print(counter_vel);
//Serial.println(",");


//Serial.print(errorbuff[counter_vel]);
////Serial.print(",");
//Serial.print(",");
//Serial.print(vbuffer[counter_vel]);
//Serial.print(",");
////Serial.print(",");
////Serial.print(",");
if(counter_vel == 9){
  Vel_flag_update =1;
//  Serial.print(Vel_flag_update);
//  Serial.print(",");
}


if(counter_vel == 10){
//Serial.print(Anew_50[counter_vel]);
//Serial.print(",");
//Serial.println(vf); //This velocity is okay for now
//Serial.print(Vel_flag_update);
//Serial.print(",");
//Serial.println(vf);
return vf;
}

}

 boolean zeroVelocityUpdate(float acceleration[], float angularVelocity[])
    {
        float accelprevious[3];
      
        if(abs(acceleration[0]) <= STATIC_ACCELERATION_THRESHOLD && //if accel < static_accel(0.08) then ZVU = 1
                abs(acceleration[1]) <= STATIC_ACCELERATION_THRESHOLD &&
                abs(acceleration[2]) <= STATIC_ACCELERATION_THRESHOLD &&   // look at the Z because it does not start at 0
                abs(angularVelocity[0]) <= STATIC_ANGULAR_VELOCITY_THRESHOLD &&
                abs(angularVelocity[1]) <= STATIC_ANGULAR_VELOCITY_THRESHOLD &&
                abs(angularVelocity[2]) <= STATIC_ANGULAR_VELOCITY_THRESHOLD)
                
        {
          //Serial.println("1");
            samplesCount++;
            ZVU = 1;
            timestampflag = 0; //flag resets when 0
            velflag = 0;
            vstart = 0;
        }
          else
        {
          //Serial.println("stop"); // constantly in stop
            samplesCount = 0; 
            
        }

         accelprevious[0] = acceleration[0];
        
        // maybe should put if here
        return (samplesCount >= STATIC_SAMPLES_THRESHOLD); // if greater than 10 then ZerovelocityUpdate = True. Once true then all == 0. It works 
        
    }


float integrate_pos(float vel, float ti){ // Need t0_ti and then final Ti and then need 
   float dt = (time_acceleration - ti)/1000;//should be devided by 1000
   float ds = vel * (dt) * 0.5;
   float s = s_old + ds ; //time 0.5
   s_old = s; //No error calcs for this one

   return s;
}    
