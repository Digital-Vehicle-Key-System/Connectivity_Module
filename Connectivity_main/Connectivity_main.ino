#include "connectivity_config.h"
#include "connectivity_init.h"
#include "connectivity_private.h" 
 Trunk_Access trunk;
void setup()
{
 Connectivity_CtrlBoardCommvoidInit();
   Serial.printf("sizeof: %d\n",sizeof(trunk));
  
 // Connect to Wi-Fi network and Firebase
  connectToWiFi();
  setupFirebase();
  loadUserDataFromFirebase();

  /*fbdo.setBSSLBufferSize(4096, 1024);
  fbdo.setResponseSize(2048);*/
}

void loop()
{
  // العمليات الرئيسية
}
