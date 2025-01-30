#include "Error_States.h"
#include "stdTypes.h"
#include "connectivity_config.h"
#include "connectivity_init.h"
#include "connectivity_private.h"
#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include <ArduinoJson.h>

// Firebase object definition
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;



userData *users = NULL;
int userCount = 0;

ES_t connectToWiFi()
{
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(300);
    }
    Serial.println();
    Serial.print("Connected to Wi-Fi with IP: ");
    Serial.println(WiFi.localIP());
    return ES_OK;
}

ES_t setupFirebase()
{
    config.api_key = API_KEY;
    auth.user.email = USER_EMAIL;
    auth.user.password = USER_PASSWORD;
    config.database_url = DATABASE_URL;
    config.max_token_generation_retry = 3;
    Firebase.begin(&config, &auth);
    return ES_OK;
}

// Function to add a new user
ES_t addUser(userData newUser)
{
    userData *temp = (userData *)realloc(users, (userCount + 1) * sizeof(userData));
    if (temp == NULL)
    {
        Serial.println("Memory allocation failed!");
        return ES_ERROR;
    }
    users = temp;
    users[userCount] = newUser;
    userCount++;
    return ES_OK;
}

// Function to print all stored user data
ES_t printStoredUserData()
{
    for (int i = 0; i < userCount; i++)
    {
        Serial.println("========== User " + String(i + 1) + " ==========");
        Serial.printf("User Name: %s\n", users[i].user_name);
        Serial.printf("User ID: %s\n", users[i].user_id);
        Serial.printf("Speed Limit: %d\n", users[i].speed_limit);
        Serial.printf("Door Access: %s\n", users[i].door == Door_On ? "On" : "Off");
        Serial.printf("Engine Access: %s\n", users[i].engine == Engine_On ? "On" : "Off");
        Serial.printf("Trunk Access: %s\n", users[i].trunk == Trunk_On ? "On" : "Off");
        Serial.println("------------------------------");
    }
    return ES_OK;
}

ES_t Connectivity_CtrlBoardCommvoidInit()
{
    // Initialize Serial communication for debugging (USB to Serial)
    Serial.begin(115200);
    while (!Serial)
    {
        ; // Wait for the serial monitor to open
    }

    // Initialize Serial2 (for UART communication with Nucleo)
    Serial2.begin(115200, SERIAL_8N1, 16, 17); // Use the correct pins for TX (16) and RX (17)
    Serial.println("UART initialized for communication with Nucleo.");
    return ES_OK;
}

// Function to send user data over UART
ES_t Connectivity_CtrlBoardSendData(const userData *dataArray, int userCount)
{
    // Check if the data array is valid
    if (dataArray == NULL || userCount == 0)
    {
        Serial.println("No user data to send.");
        return ES_ERROR;
    }

    // Send the entire userData array over UART
    Serial2.write((const char *)dataArray, userCount * sizeof(userData));
    Serial.println("User data sent successfully.");
    return ES_OK;
}

// Function to load data from Firebase
ES_t loadUserDataFromFirebase()
{
    if (Firebase.RTDB.getJSON(&fbdo, "/users"))
    {
        if (fbdo.dataType() == "json")
        {
            StaticJsonDocument<2048> doc; // Increased buffer size
            DeserializationError error = deserializeJson(doc, fbdo.jsonString());
            if (error)
            {
                Serial.print("JSON parsing failed: ");
                Serial.println(error.f_str());
                return ES_ERROR;
            }

            JsonObject root = doc.as<JsonObject>();
            for (JsonPair keyValue : root)
            {
                const char *userKey = keyValue.key().c_str();
                JsonObject user = keyValue.value().as<JsonObject>();

                // Validate the presence of required fields
                if (user.containsKey("user_id") && user.containsKey("user_name") &&
                    user.containsKey("speed_limit") && user.containsKey("door") &&
                    user.containsKey("engine") && user.containsKey("trunk"))
                {
                    userData newUser;
                    strncpy(newUser.user_id, user["user_id"], sizeof(newUser.user_id) - 1);
                    newUser.user_id[sizeof(newUser.user_id) - 1] = '\0'; // Null-terminate
                    strncpy(newUser.user_name, user["user_name"], sizeof(newUser.user_name) - 1);
                    newUser.user_name[sizeof(newUser.user_name) - 1] = '\0'; // Null-terminate
                    newUser.speed_limit = user["speed_limit"];
                    newUser.door = (Door_Access)user["door"];
                    newUser.engine = (Engine_Access)user["engine"];
                    newUser.trunk = (Trunk_Access)user["trunk"];

                    addUser(newUser);
                }
                else
                {
                    Serial.println("Missing fields in Firebase data.");
                    continue;
                }
            }
        }
    }
    else
    {
        Serial.print("Firebase error: ");
        Serial.println(fbdo.errorReason());
        return ES_ERROR;
    }

    printStoredUserData();
    // Send the user data after loading from Firebase
    Connectivity_CtrlBoardSendData(users, userCount);

    fbdo.setBSSLBufferSize(4096, 1024);
    fbdo.setResponseSize(2048);
    return ES_OK;
}