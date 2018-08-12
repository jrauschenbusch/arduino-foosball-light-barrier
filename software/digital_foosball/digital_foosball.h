/***********************
 ***  CONFIGURATION  ***
 ***********************/
 
// Pin constants, change if you modified  the hardware schematic
#define GOAL_1_OUT_PIN 4
#define GOAL_1_IN_PIN 11

#define GOAL_2_OUT_PIN 2
#define GOAL_2_IN_PIN 8

#define LED_PIN_1 3
#define LED_PIN_2 5

#define MAX_CONNECTION_ATTEMPTS 5;

char CONTEXT[] = "";

char SERVER_URL[] = "http://0.0.0.0:19000";

/***************************
 ***  DEBUGGING OPTIONS  ***
 ***************************/

// Define to enable output messages on Serial
// Use #define to enable, #undef to disable
#define DEBUG
#define LOGGING


