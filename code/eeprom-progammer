
int dataPin = 12;
int latchPin = 11;
int clockPin = 10;

int writeEnablePin= 9;
//int outputEnable=8; 



int IOPins[] = {13,2,3,4,5,6,7,8};


byte numbers[] = {0x3F ,0x06 ,0x5B ,0x4F ,0x66 ,0x6D ,0x7D ,0x07 ,0x7F ,0x6F};
                //!gfe dcba
             



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);

  digitalWrite(writeEnablePin,HIGH);
  pinMode(writeEnablePin,OUTPUT);

  digitalWrite(outputEnable,HIGH);
  pinMode(outputEnable,OUTPUT);

  writeEEPROM();
  delay(3000);
  readEEPROM(0x00);
 

  //writeEEPROMNeg();
  delay(3000);
  //readEEPROM(1024);

  testEEPROM();
}


void loop() {
  // put your main code here, to run repeatedly:



}

void setAddress(int address, bool outputEnable) 
{
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, lowByte(address));
  shiftOut(dataPin, clockPin, LSBFIRST, highByte(address) | (outputEnable ? 0x00 : ( 1 << 5))  );
  digitalWrite(latchPin, HIGH);
  //delay(10);
}

byte readData()
{
  byte inputByte = 0;

  for( int i =0 ; i < sizeof(IOPins) / sizeof(IOPins[0]); i++)
  {
    if( digitalRead( IOPins[i]) == HIGH )
    {
      inputByte |= ( 1 << i);
    }
  }
  //none reading decimal point (msb)

  //delay(10);
  return inputByte;
}

void writeData(byte data)
{
  int num=1;
  for(int i = 0 ; i < sizeof(IOPins) / sizeof(IOPins[0]); i++)
  {
    
    if(( data & num) == 0) digitalWrite(IOPins[i],LOW);
    else digitalWrite(IOPins[i],HIGH);
    num *=2;

  }

  digitalWrite(writeEnablePin,LOW);
  delayMicroseconds(1);
  digitalWrite(writeEnablePin,HIGH);
  delay(5);

}


void readEEPROM(int startingAddress)
{

  //digitalWrite(outputEnable,LOW);
  //digitalWrite(writeEnablePin,HIGH);
  for( int i =0 ; i< sizeof(IOPins) / sizeof(IOPins[0]); i++) pinMode(IOPins[i],INPUT);

  byte data=0;
  int address=startingAddress;
  for(int i = address; i < address + 256 ;i++)
  {
    setAddress(i,true);
    data = readData();
    setReadPrint(i,data);
    //delay(10);
  }

  Serial.println(" ");
  Serial.println("Finish reading 00 section");

  address += 256;
  for(int i = address; i < address + 256 ;i++)
  {
    setAddress(i,true);
    data = readData();
    setReadPrint(i,data);
   //delay(10);
  }

  Serial.println(" ");
  Serial.println("Finish reading 01 section");


  address += 256;
  for(int i = address; i < address + 256 ;i++)
  {
    setAddress(i,true);
    data = readData();
    setReadPrint(i,data);
    //delay(10);
  }

  Serial.println(" ");
  Serial.println("Finish reading 10 section");


  address += 256;
  for(int i = address; i < address + 256 ;i++)
  {
    setAddress(i,true);
    data = readData();
    setReadPrint(i,data);
    //delay(10);
  }

  Serial.println(" ");
  Serial.println("Finish reading 11 section");


}

void writeEEPROM()
{
  
  ///digitalWrite(outputEnable,HIGH); 
  for( int i =0 ; i< sizeof(IOPins) / sizeof(IOPins[0]); i++) pinMode(IOPins[i],OUTPUT);

  int address=0;
  for(int i = 0; i < 256 ; i++)
  {
    setAddress(address + i,false);
    writeData( numbers[i % 10]);
    setWritePrint(address+i,numbers[i % 10]);
  
  }

  Serial.println();
  Serial.println("finish writing 00 section");



  address += 256;
  for(int i = 0; i < 256 ; i++)
  {
    setAddress(address + i,false);
    writeData( numbers[ (i/10) % 10]);
    setWritePrint(address+i,numbers[(i/10) % 10]);    
    
  }

  Serial.println();
  Serial.println("finish writing 01 section");

  

  address += 256;
  for(int i = 0; i < 256 ; i++)
  {
    setAddress(address + i,false);
    writeData(numbers[(i/100) % 10]);
    setWritePrint(address+i,numbers[(i/100) % 10]);       
    
  }

  Serial.println();
  Serial.println("finish writing 10 section");

  
  address += 256;
  for(int i = 0; i < 256 ; i++)
  {
    setAddress(address + i,false);
    writeData(0x00);
    setWritePrint(address+i,0x00);       
    
  }

  Serial.println();
  Serial.println("finish writing 11 section");


  Serial.println();
  Serial.println("finish writing");

}

void setWritePrint(int address,byte data)
{

  if ( address % 10 == 0) 
  {
    Serial.println();
    if(address < 16) Serial.print("0");
    Serial.print(address,HEX);
    Serial.print(": ");
  } 

  if(data < 16) Serial.print("0");
  Serial.print(data,HEX);
  Serial.print(" ");

}

void setReadPrint(int address ,byte data)
{
   if ( address % 10 == 0) 
    {
      Serial.println();
      if(address < 16) Serial.print("0");
      Serial.print(address,HEX);
      Serial.print(": ");
    } 

    if(data<16) Serial.print("0");
    Serial.print(data,HEX);
    Serial.print(" ");

}

void writeEEPROMNeg()
{
  delay(1000);
  int address=1024;
  

  for(int i = 0 ; i < 128 ; i++)
  {
    setAddress(address + i,false);
    writeData( numbers[i % 10]);
    setWritePrint(address+i,numbers[i % 10]);    
    delay(10);
  }

  address += 128;

  for(int i = 0 ; i < 128 ; i++)
  {
    setAddress(address + i,false);
    writeData( numbers[ (128-i) % 10]);
    setWritePrint(address+i,numbers[(128-i) % 10]);    
    delay(10);
  }

  Serial.println();
  Serial.println("finish writing 00 section");



  address += 128;
  for(int i = 0; i < 128 ; i++)
  {
    setAddress(address + i,false);
    writeData( numbers[ (i/10) % 10]);
    setWritePrint(address+i,numbers[(i/10) % 10]);    
    delay(10);
  }


  address += 128;
  for(int i = 0; i < 128 ; i++)
  {
    setAddress(address + i,false);
    writeData( numbers[ ( (128-i) /10) % 10]);
    setWritePrint(address+i,numbers[( (128-i) /10) % 10]);    
    delay(10);
  }

  Serial.println();
  Serial.println("finish writing 01 section");


  
  address += 128;
  for(int i = 0; i < 128 ; i++)
  {
    setAddress(address + i,false);
    writeData(numbers[(i/100) % 10]);
    setWritePrint(address+i,numbers[(i/100) % 10]);       
    delay(10);
  }


  address += 128;
  for(int i = 0; i < 128 ; i++)
  {
    setAddress(address + i,false);
    writeData(numbers[((128-i)/100) % 10]);
    setWritePrint(address+i,numbers[((128-i)/100) % 10]);       
    delay(10);
  }

  Serial.println();
  Serial.println("finish writing 10 section");



  address += 128;
  for(int i = 0; i < 128 ; i++)
  {
    setAddress(address + i,false);
    writeData(0x00);
    setWritePrint(0x00,address+i);       
    delay(10);
  }


  address += 128;
  for(int i = 0; i < 128 ; i++)
  {
    setAddress(address + i,false);
    writeData(0x40);
    setWritePrint(0x40,address+i);       
    delay(10);
  }


  Serial.println();
  Serial.println("finish writing 11 section");


  Serial.println();
  Serial.println("finish writing");

}

void testEEPROM()
{
  for(int i =0 ; i < 256; i++)
  {
    setAddress(address + i,false);
    Serial.println(i);
    delay(300);
  }

}
