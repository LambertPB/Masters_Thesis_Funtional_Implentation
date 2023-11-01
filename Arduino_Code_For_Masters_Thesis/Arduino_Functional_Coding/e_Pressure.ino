

int setupPress(){
//  int test = i2cRead(LPS225HB_WHO_AM_I_REG);
//   Serial.println(test);

if (i2cRead(LPS225HB_WHO_AM_I_REG) != 0xB1) { //B1 is who am I, can test individualy
    return 0;
  }

  press_check = true;
  return 1;
}

int i2cWrite(uint8_t reg, uint8_t val)
{
  Wire.beginTransmission(LPS225HB_ADDRESS);
  Wire.write(reg);
  Wire.write(val);
  if (Wire.endTransmission() != 0) {
    return 0;
  }

  return 1;
}

int i2cRead(uint8_t reg)
{
  Wire.beginTransmission(LPS225HB_ADDRESS);
  Wire.write(reg);
  if (Wire.endTransmission(false) != 0) {
    return -1;
  }

  if (Wire.requestFrom(LPS225HB_ADDRESS, 1) != 1) {
    return -1;
  }
  
  return Wire.read();
}


float readPressureOwn()
{
  if (press_check == true) { //change this 
    // trigger one shot
    i2cWrite(LPS225HB_CTRL2_REG, 0x01);

    // wait for ONE_SHOT bit to be cleared by the hardware
    while ((i2cRead(LPS225HB_CTRL2_REG) & 0x01) != 0) {
      yield();
    }

    float reading = (i2cRead(LPS225HB_PRESS_OUT_XL_REG) |
            (i2cRead(LPS225HB_PRESS_OUT_L_REG) << 8) |
            (i2cRead(LPS225HB_PRESS_OUT_H_REG) << 16)) / 40960.0; //why 40960.0

//    if (units == MILLIBAR) { // 1 kPa = 10 millibar
//      return reading * 10;
//    } else if (units == PSI) {  // 1 kPa = 0.145038 PSI
//      return reading * 0.145038;
//    } else {
      return reading;
  //  }
  }
  return 0;
}
