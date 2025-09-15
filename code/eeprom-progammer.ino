
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

  delay(1000);

  // Write EEPROM
  for( int i =0 ; i< sizeof(IOPins) / sizeof(IOPins[0]); i++) pinMode(IOPins[i],OUTPUT);
  for(int i = 0; i < 8; i++)
    {
      setAddress(i,false);
      writeData(numbers[i]);
      setWritePrint(i,numbers[i]);
    }

  // Read EEPROM
  for( int i =0 ; i< sizeof(IOPins) / sizeof(IOPins[0]); i++) pinMode(IOPins[i],INPUT);
  byte data=0;
  for(int i = 0; i < 8; i++)
    {
        setAddress(i,true);
        data = readData();
        setReadPrint(i,data);
    }


  
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
