#ifndef CONNECTIVITY_INIT_H
#define CONNECTIVITY_INIT_H
#include "Error_States.h"
// Function prototypes

//void streamCallback(StreamData data);
//void streamTimeoutCallback(bool timeout);
ES_t connectToWiFi();
ES_t setupFirebase();
ES_t addUser(userData newUser);
ES_t printStoredUserData();
ES_t loadUserDataFromFirebase();
ES_t Connectivity_CtrlBoardCommvoidInit();
ES_t Connectivity_CtrlBoardSendData(const userData *dataArray, int userCount);

#endif
