#ifndef CONNECTIVITY_CONFIG_H
#define CONNECTIVITY_CONFIG_H

// Define WiFi network 
#define WIFI_SSID "samar"
#define WIFI_PASSWORD "cat123456"

// Define API key
#define API_KEY "AIzaSyBP5vJIqoQP7TIf_MeVPu1gVoGkudfkmf4"

// Define URL for Realtime Firebase Database
#define DATABASE_URL "https://test-4900b-default-rtdb.firebaseio.com/"

// Define user login
#define USER_EMAIL "samaribrahhim2@gmail.com"
#define USER_PASSWORD "123456"

// Define the user structure

typedef enum __attribute__((packed))
{
  Door_Off,
  Door_On
} Door_Access;

typedef enum __attribute__((packed))
{
  Engine_Off,
  Engine_On
} Engine_Access;

typedef enum __attribute__((packed))
{
  Trunk_Off,
  Trunk_On
} Trunk_Access;

typedef struct __attribute__((__packed__))
{
  int user_id;
  char user_name[20];
  unsigned int speed_limit;
  Door_Access door;
  Engine_Access engine;
  Trunk_Access trunk;
} userData;

#endif
