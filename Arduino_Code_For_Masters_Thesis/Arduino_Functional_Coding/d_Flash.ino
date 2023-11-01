
void appendFilelarge(const char * path, int loopsize) 
{
   digitalWrite(BLUE, LOW); //ON
  
  Serial.print("Appending file: "); Serial.print(path);

  FILE *file = fopen(path, "a");
  
  if (file) 
  {
    Serial.println(" => Open OK");
  }
  else
  {
    Serial.println(" => Open Failed");
    return;
  }

   for(int scounter = 0;scounter <=loopsize; scounter ++){
    
   dtostrf(messagetest[scounter][0], BUF_SIZE , 4 , buff);  //4 is decimals after //think it is jsut goign to overwrite
   //writeFile(buff, sizeof(buff), file);
   if (fwrite((uint8_t *) buff, 1, BUF_SIZE, file)) 
  {
    Serial.println("* Appending OK");
  } 
  else 
  {
    Serial.println("* Appending failed");
  }
   dtostrf(messagetest[scounter][1], BUF_SIZE , 4 , buff);  //4 is decimals after
   //writeFile(buff, sizeof(buff), file);
  if (fwrite((uint8_t *) buff, 1, BUF_SIZE, file)) 
  {
    Serial.println("* Appending OK");
     
  } 
  else 
  {
    Serial.println("* Appending failed");
  }
   
   dtostrf(messagetest[scounter][2], BUF_SIZE , 4 , buff);  //4 is decimals after
   //writeFile(buff, sizeof(buff), file);
  if (fwrite((uint8_t *) buff, 1, BUF_SIZE, file)) 
  {
    Serial.println("* Appending OK");
  } 
  else 
  {
    Serial.println("* Appending failed");
  }
   dtostrf(messagetest[scounter][3], BUF_SIZE , 4 , buff);  //4 is decimals after //think it is jsut goign to overwrite
   //writeFile(buff, sizeof(buff), file);
   if (fwrite((uint8_t *) buff, 1, BUF_SIZE, file)) 
  {
    Serial.println("* Appending OK");
  } 
  else 
  {
    Serial.println("* Appending failed");
  }
   dtostrf(messagetest[scounter][4], BUF_SIZE , 4 , buff);  //4 is decimals after //think it is jsut goign to overwrite
   //writeFile(buff, sizeof(buff), file);
   if (fwrite((uint8_t *) buff, 1, BUF_SIZE, file)) 
  {
    Serial.println("* Appending OK");
  } 
  else 
  {
    Serial.println("* Appending failed");
  }
   dtostrf(messagetest[scounter][5], BUF_SIZE , 4 , buff);  //4 is decimals after //think it is jsut goign to overwrite
   //writeFile(buff, sizeof(buff), file);
   if (fwrite((uint8_t *) buff, 1, BUF_SIZE, file)) 
  {
    Serial.println("* Appending OK");
  } 
  else 
  {
    Serial.println("* Appending failed");
  }
 
  
 }
     
  fclose(file);
}

//void writeFile(const char * message, size_t messageSize, const char * path){
// 
// if (fwrite((uint8_t *) message, 1, messageSize, file)) 
//  {
//    Serial.println("* Appending OK");
//  } 
//  else 
//  {
//    Serial.println("* Appending failed");
//  }
//}

void appendFile(const char * path, const char * message, size_t messageSize) 
{
  Serial.print("Appending file: "); Serial.print(path);

  FILE *file = fopen(path, "a");
  
  if (file) 
  {
    Serial.println(" => Open OK");
  }
  else
  {
    Serial.println(" => Open Failed");
    return;
  }

  if (fwrite((uint8_t *) message, 1, messageSize, file)) 
  {
    Serial.println("* Appending OK");
  } 
  else 
  {
    Serial.println("* Appending failed");
  }
   
  fclose(file);
}



void deleteFile(const char * path) 
{
  Serial.print("Deleting file: "); Serial.print(path);
  
  if (remove(path) == 0) 
  {
    Serial.println(" => OK");
  }
  else
  {
    Serial.println(" => Failed");
    return;
  }
}
void readFile(const char * path) 
{
  Serial.print("Reading file: "); Serial.print(path);

  FILE *file = fopen(path, "r");
  
  if (file) 
  {
    Serial.println(" => Open OK");
  }
  else
  {
    Serial.println(" => Open Failed");
    return;
  }

  char c;
  uint32_t numRead = 1;
  
  while (numRead) 
  {
    numRead = fread((uint8_t *) &c, sizeof(c), 1, file);

    if (numRead)
      //Serial.print(c);
      storedata(c); // only at end with read data
  }
 
  fclose(file);
}

void storedata(char c){



//Serial.println(counter_float);
if(counter_float <= BUF_SIZE-1){
  //messagetest[k][1]
  buff[counter_float] = c;
  //Serial.print("BuFF");
 // Serial.println(buff[counter_float]); // reuse buffer
 // bzero(buff, BUF_SIZE);
  
}
  //char array to float here
 if(counter_float >= BUF_SIZE-1){//loop same amount as data thus use kstore
  //now store buffer as float into a messagetest buffer that will be sent
  float test = atof(buff); //into messagetest[k][1]. Then send that perfect
  
  //bzero(buff, BUF_SIZE);
  counter_float = -1; //-1 because it needs to start at 0 after counter ++;
//  Serial.print("Test :");
//  Serial.println(test);
//  Serial.print("left = i = :");
//  Serial.println((((kstore-1) / 3)+1));
//  Serial.print("right = j =  :");
//  Serial.println(((kstore+2) % 3));
//  messagetest[(((kstore-1) / 3)+1)][((kstore+2) % 3)] = test; // for 3//populate messagetest to send out 
  messagetest[(((kstore-1) / 6))][((kstore +5) % 6)] = test; 
//  Serial.print("Message test :");
//  Serial.println(messagetest[(((kstore-1) / 6))][((kstore +5) % 6)]); //store return
//    Serial.print("MOD:");
//  Serial.println(((kstore+5)% 6)); 
//  Serial.print("Kstore:");
//  Serial.println(((kstore-1) / 6)); //has to start at 1 for modulo

//   Serial.print("kstore"); 
//    Serial.print(kstore);  
//       Serial.print("_K:"); 
// Serial.print(((kstore-1) / 6));
//  Serial.print("K_oth:"); 
// Serial.println(((kstore+5)% 6));
 
if((kstore % 6) == 0 && kstore!= 0){
//  Serial.print("K1");

//  Serial.print("messagetest:"); //store return
//  Serial.print(messagetest[(((kstore-1) / 6))][((kstore+5)% 6)]); //store return, +5 so that it start with MOD - 0
//  Serial.print("hardMessage:"); //store return
//  Serial.println(messagetest[(((kstore-1) / 6))][0]); //store return, +5 so that it start with MOD - 0
  
//  Serial.print("kstore___:"); 
// Serial.println((((kstore+5)% 6)));

  Serial.print(kstore); //store return
  Serial.print(","); //store return
  Serial.print(messagetest[((kstore-1) / 6)][0]);
   Serial.print(","); //store return
  Serial.print(messagetest[((kstore-1) / 6)][1]);
   Serial.print(","); //store return
  Serial.print(messagetest[((kstore-1) / 6)][2]);
   Serial.print(","); //store return
  Serial.print(messagetest[((kstore-1) / 6)][3]);
   Serial.print(","); //store return
  Serial.print(messagetest[((kstore-1) / 6)][4]);
   Serial.print(","); //store return
  Serial.println(messagetest[((kstore-1) / 6)][5]);
  


 
 sensorTask(messagetest[((kstore-1) / 6)][0] ,messagetest[((kstore-1) / 6)][1],messagetest[((kstore-1) / 6)][2],messagetest[((kstore-1) / 6)][3],messagetest[((kstore-1) / 6)][4],messagetest[((kstore-1) / 6)][5]);
 bleTask();

}

//problem here should have ended at 300
      
 if(kstore == 300){ // take this out and reset kstore when calling data again//this is the problem
  kstore = 0;//somtimes -1 if has to start at 0
 }
 //Serial.println(kstore);
 kstore++; // must be global has to start at 1 for modulo
}
  
  counter_float++;
}
