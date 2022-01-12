#include <PS4BT.h>
#include <usbhub.h>


#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

USB Usb;
BTD Btd(&Usb); 

//PS4BT PS4(&Btd, PAIR);
PS4BT PS4(&Btd);

bool printAngle, printTouch;
uint8_t oldL2Value, oldR2Value;
uint8_t LX,LY,RX,RY;
uint8_t value;
void setup() {
  Serial.begin(115200);
#if !defined(__MIPSEL__)
  while (!Serial); 
#endif

  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (Usb.Init() == -1); 
  }
  Serial.print(F("\r\nPS4 Bluetooth Library Started"));
}
String oldCommand = "";
void loop() {
  Usb.Task();
  if (PS4.connected())
  {
    char str[3];
    String command = "PS4: ";
    
    if (PS4.getAnalogHat(LeftHatX) > 137 || PS4.getAnalogHat(LeftHatX) < 117  || PS4.getAnalogHat(LeftHatY) > 137 || PS4.getAnalogHat(LeftHatY) < 117)
    {
      command+= " LeftHatX: ";  
      value = PS4.getAnalogHat(LeftHatX);
      if(value > 137) {  LX = map(value,137, 255, 128, 255); }
      else if(value< 117){ LX = map(value,0, 117, 0, 127); }
      sprintf(str,"%03d",LX);
      command+= str;
      
      command+= " LeftHatY: ";
      value = PS4.getAnalogHat(LeftHatY);
      if(value > 137) {  LY = map(value,137, 255, 128, 255); }
      else if(value <117) { LY = map(value,0, 117, 0, 127); }
      sprintf(str,"%03d",LY);
      command+= str;
    }
    
    if(PS4.getAnalogHat(RightHatX) > 137 || PS4.getAnalogHat(RightHatX) < 117  || PS4.getAnalogHat(RightHatY) > 137 || PS4.getAnalogHat(RightHatY) < 117) 
    {    
      command+=" RightHatX: ";
      value=PS4.getAnalogHat(RightHatX);
      if(value > 137) {  RX = map(value,137, 255, 128, 255); }
      else if(value < 117){ RX = map(value,0, 117, 0, 127); }
      sprintf(str,"%03d",RX);
      command+= str;
      
      command+=" RightHatY: ";    
      value=PS4.getAnalogHat(RightHatY);
      if(value > 137) {  RY = map(value,137, 255, 128, 255); }
      else if(value < 117){ RY = map(value,0, 117, 0, 127); }
      sprintf(str,"%03d",RY);
      command+= str;
    }

    if (PS4.getAnalogButton(L2))
    {
      command+=" L2: ";     value=PS4.getAnalogButton(L2);   
      sprintf(str,"%03d",value);
      command+= str;
    }
    if (PS4.getAnalogButton(R2))
    {
      command+=" R2: ";     value=PS4.getAnalogButton(R2);
      sprintf(str,"%03d",value);
      command+= str;
    }
    
    if (PS4.getButtonPress(PS)) {
      command+=" PS: PS4.disconnect";
      PS4.disconnect();
    }
    if (PS4.getButtonPress(TRIANGLE)) {
      command+=" TRI ";
    }
    if (PS4.getButtonPress(CIRCLE)) {
      command+=" CIR ";
    }
    if (PS4.getButtonPress(CROSS)) {
      command+=" CRO ";
    }
    if (PS4.getButtonPress(SQUARE)) {
      command+=" SQU ";
    }

    if (PS4.getButtonPress(UP)) {
      command+=" UP ";
      PS4.setLed(Red);
    } 
    if (PS4.getButtonPress(RIGHT)) {
      command+=" RIGHT ";
      PS4.setLed(Blue);
    } 
    if (PS4.getButtonPress(DOWN)) {
      command+=" DOWN ";
      PS4.setLed(Yellow);
    } 
    if (PS4.getButtonPress(LEFT)) {
      command+=" LEFT ";
      PS4.setLed(Green);
    }

    if (PS4.getButtonPress(L1))
      command+=" L1 ";
    if (PS4.getButtonPress(L3))
      command+=" L3 ";
    if (PS4.getButtonPress(R1))
      command+=" R1 ";
    if (PS4.getButtonPress(R3))
      command+=" R3 ";

    if (PS4.getButtonPress(SHARE))
      command+=" SHARE ";
    if (PS4.getButtonPress(OPTIONS)) {
      command+=" OPTIONS ";
      command+=String(PS4.getBatteryLevel());
    }
    command += " END";
    
    if(oldCommand != command)
      Serial.print(command);
      
      oldCommand = command;

    delay(1);
  }
}
