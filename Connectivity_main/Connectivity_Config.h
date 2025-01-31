#ifndef CONNECTIVITY_CONFIG_H
#define CONNECTIVITY_CONFIG_H

// Define WiFi network 
#define WIFI_SSID "samar"
#define WIFI_PASSWORD "cat123456"


// Define user login
#define USER_EMAIL "samaribrahim@std.mans.edu.eg"
#define USER_PASSWORD "213456"

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
  char user_id[50];
  unsigned int speed_limit;
  Door_Access door;
  char user_name[50];
  Engine_Access engine;
  Trunk_Access trunk;
} userData;

#endif
