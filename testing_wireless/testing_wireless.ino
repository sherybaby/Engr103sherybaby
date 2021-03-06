
// TRANSMITTER CODE

//NOTE :- THIS CODE IS USED WHEN YOU WANT TO CONTROL THE ROBOT VIA THE COMPUTER!!!!

#include <VirtualWire.h>

void setup()
{
    Serial.begin(9600);	  // Debugging only
    Serial.println("setup");

    // Initialise the IO and ISR
     
    vw_setup(2000);	 // Bits per sec
        vw_set_tx_pin(3); //Transmitter Data Pin to Digital Pin 3
}//close setup

void loop()
{
  
  if (Serial.available() > 0)
  {
     int sendByte = Serial.read();//Starts reading data from the serial monitor once condition is met
     Serial.println(sendByte);
 
  switch (sendByte){
 
    case 'f':  //if the controller type f
  {
    
    char *msg2 = "f";
    digitalWrite(13, true); // Flash a light to show transmitting
    vw_send((uint8_t *)msg2, strlen(msg2));//send byte to the receiver
    vw_wait_tx(); // Wait until the whole message is gone
    digitalWrite(13, false);
    break;
     
  }
    case 'b':  //if controller types b
    {
   char *msg2 = "b";
   digitalWrite(13, true); // Flash a light to show transmitting
   vw_send((uint8_t *)msg2, strlen(msg2));//send byte to the receiver
   vw_wait_tx(); // Wait until the whole message is gone
   digitalWrite(13, false);  
   break;
    }
    
    case 's': //if controller types s
    {
   char *msg2 = "s";
   digitalWrite(13, true); // Flash a light to show transmitting
   vw_send((uint8_t *)msg2, strlen(msg2));//send byte to the receiver
   vw_wait_tx(); // Wait until the whole message is gone
   digitalWrite(13, false);  
   break;
    }
    
    case 'l': //if controller types l
  {  
   char *msg2 = "l";
   digitalWrite(13, true); // Flash a light to show transmitting
   vw_send((uint8_t *)msg2, strlen(msg2));//send byte to the receiver
   vw_wait_tx(); // Wait until the whole message is gone
   digitalWrite(13, false);    
   break;
  }     
    case 'r': //if controller types r
    {
   char *msg2 = "r";
   digitalWrite(13, true); // Flash a light to show transmitting
   vw_send((uint8_t *)msg2, strlen(msg2));//send byte to the receiver
   vw_wait_tx(); // Wait until the whole message is gone
   digitalWrite(13, false);   
   break;
    }
    default://if any other value is entered
    {
      
       Serial.println("wrong entry");//print wrong entry in the serial monitor
    }
   }// close switch-case
  }//close if 
 }//close loop
  
 // End Of Code 
