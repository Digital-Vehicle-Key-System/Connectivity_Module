#include "connectivity_config.h"
#include "connectivity_init.h"
#include "connectivity_private.h" 
 
void setup()
{
 Connectivity_CtrlBoardCommvoidInit();
   //Serial.printf("sizeof: %d\n",sizeof(trunk));
  
 // Connect to Wi-Fi network and Firebase
  connectToWiFi();
  setupFirebase();
  loadUserDataFromFirebase();

}

void loop()
{
 
}
