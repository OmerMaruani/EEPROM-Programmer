


int dataPin = 12;
int latchPin = 11;
int clockPin = 10;

int writeEnablePin= 9;
//int outputEnable=8;



int IOPins[] = {13,2,3,4,5,6,7,8};
//none decimal point

byte numbers[] = {0x3F ,0x06 ,0x5B ,0x4F ,0x66 ,0x6D ,0x7D ,0x07 ,0x7F ,0x6F};
                //!gfe dcba
             





int hours1= 0;
int hours2= 0;

int minutes1=0;
int minutes2=0;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);

  digitalWrite(writeEnablePin,HIGH);
  pinMode(writeEnablePin,OUTPUT);

  //digitalWrite(outputEnable,HIGH);
  //pinMode(outputEnable,OUTPUT);
  digitalWrite(latchPin, LOW);



  writeEEPROM();
  delay(3000);
  readEEPROM();


}



void loop() {
  // put your main code here, to run repeatedly:

}



void setAddress(int address, bool outputEnable) 
{
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, lowByte(address));
  shiftOut(dataPin, clockPin, LSBFIRST, highByte(address) | (outputEnable ? 0x00 : ( 1 << 3))  );
  digitalWrite(latchPin, HIGH);
  //delay(10);

 
}


byte readData()
{
  byte inputByte = 0;

  for( int i =0 ; i <sizeof(IOPins) / sizeof(IOPins[0]); i++)
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





void readEEPROM()
{

  //digitalWrite(outputEnable,LOW);
  //digitalWrite(writeEnablePin,HIGH);
  for( int i =0 ; i< sizeof(IOPins) / sizeof(IOPins[0]); i++) pinMode(IOPins[i],INPUT);

  int readincorrectly = 0;
  byte data=0;
  int address =0;
  for(int i = address; i < address + 256 ;i++)
  {
    setAddress(i,true);
    data = readData();
    setReadPrint(data,i);
    if(data != numbers[i % 10])  readincorrectly++;
    //delay(10);
  }

  Serial.println(" ");
  Serial.println("Finish reading 00 section");

  address += 256;
  for(int i = address; i < address + 256 ;i++)
  {
    setAddress(i,true);
    data = readData();
    setReadPrint(data,i);
    if(data != numbers[ (i/10) % 10]) readincorrectly++;
    

   //delay(10);
  }

  Serial.println(" ");
  Serial.println("Finish reading 01 section");


  address += 256;
  for(int i = address; i < address + 256 ;i++)
  {
    setAddress(i,true);
    data = readData();
    setReadPrint(data,i);
    if(data !=numbers[(i/100) % 10]) readincorrectly++;

    //delay(10);
  }

  Serial.println(" ");
  Serial.println("Finish reading 10 section");


  address += 256;
  for(int i = address; i < address + 256 ;i++)
  {
    setAddress(i,true);
    data = readData();
    setReadPrint(data,i);
    if(data != 0x00) readincorrectly++;

    //delay(10);
  }

  Serial.println(" ");
  Serial.println("Finish reading 11 section");

  Serial.print("Number of incorrectly data: ");
  Serial.println(readincorrectly);

}

void writeEEPROM()
{
  
  //digitalWrite(outputEnable,HIGH); 
  for( int i =0 ; i< sizeof(IOPins) / sizeof(IOPins[0]); i++) pinMode(IOPins[i],OUTPUT);

  int address=0;
  for(int i = 0; i < 256 ; i++)
  {
    setAddress(address + i,false);
    writeData( numbers[i % 10]);
    setWritePrint(numbers[i % 10],address+i);
  
  }

  Serial.println();
  Serial.println("finish writing 00 section");



  address += 256;
  for(int i = 0; i < 256 ; i++)
  {
    setAddress(address + i,false);
    writeData( numbers[ (i/10) % 10]);
    setWritePrint(numbers[(i/10) % 10],address+i);    
    
  }

  Serial.println();
  Serial.println("finish writing 01 section");

  

  address += 256;
  for(int i = 0; i < 256 ; i++)
  {
    setAddress(address + i,false);
    writeData(numbers[(i/100) % 10]);
    setWritePrint(numbers[(i/100) % 10],address+i);       
    
  }

  Serial.println();
  Serial.println("finish writing 10 section");

  
  address += 256;
  for(int i = 0; i < 256 ; i++)
  {
    setAddress(address + i,false);
    writeData(0x00);
    setWritePrint(0x00,address+i);       
    
  }

  Serial.println();
  Serial.println("finish writing 11 section");


  Serial.println();
  Serial.println("finish writing");

}


void setWritePrint(byte data, int i)
{

  if( i % 16 == 0)
  {
    Serial.println();
    char buffer[10];
    sprintf(buffer,"%02X",i);
    Serial.print(buffer);
    Serial.print(": ");
  }
  if(i % 8 ==0) Serial.print("  ");
 

  if(data < 16) Serial.print("0");
  Serial.print(data,HEX);
  Serial.print(" ");

}

void setReadPrint(byte data, int i )
{

  if( i % 16 == 0)
  {
    Serial.println();
    char buffer[10];
    sprintf(buffer,"%02x",i);
    Serial.print(buffer);
    Serial.print(": ");
  } 
  if(i % 8 ==0) Serial.print("  ");

  if(data<16) Serial.print("0");
  Serial.print(data,HEX);
  Serial.print(" ");

}







