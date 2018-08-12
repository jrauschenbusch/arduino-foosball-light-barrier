/*************************************
 ***  CONFIGURATION AND LIBRARIES  ***
 *************************************/

// Change settings and used libraries in the config file
// Use the example config file as a template
#include "digital_foosball.h"

#include <Bridge.h>
#include <HttpClient.h>
#include <avr/dtostrf.h>

HttpClient client;

// Debugging
#ifdef DEBUG
#define LOG(message) (Serial.println(message))
#else
#define LOG(message) (((0)))
#endif

/***********************************
 *** Linked List Implementation  ***
 ***********************************/
typedef struct goal {
  int id;
  int pin_state;
  int falling_micros;
  int rising_micros;
} goal_t;

typedef struct node {
  struct goal *goal;
  struct node *next;
} node_t;

void push(node_t *head, goal_t *goal);
goal_t * pop(node_t **head);
void logSpeed(goal_t *goal);
boolean handleREST(goal_t *goal);
void blink(int pin, int times, int delay_millis);
void handleRetry(goal_t *goal);
void handleGoal(goal_t *goal);
void handleInterruptState(goal_t *goal);

node_t *head = (node_t *) malloc(sizeof(node_t));
goal_t *current_goal_1 = (goal_t *) malloc(sizeof(goal_t));
goal_t *current_goal_2 = (goal_t *) malloc(sizeof(goal_t));

void push(node_t *head, goal_t *goal) {

  node_t *current = head;

  while (current->next != NULL) {
    current = current->next;
  }

  /* now we can add a new variable */
  current->goal = goal;
  current->next = (node_t *) malloc(sizeof(node_t));
  current->next->goal = NULL;
  current->next->next = NULL;
}

goal_t * pop(node_t **head) {

  if (*head == NULL) {
    return NULL;
  }

  if ((*head)->goal == NULL) {
    return NULL;
  }

  goal_t *retval = (*head)->goal;
  node_t *next_node = (*head)->next;

  free(*head);
  *head = next_node;

  return retval;
}

/*************************
 *** Network Handling  ***
 *************************/

void logSpeed(goal_t *goal) {

  int diff_micros = goal->rising_micros - goal->falling_micros;

  double DIAMETER_BALL = 1.0E-2;
  double seconds = diff_micros * 1E-6;
  double meter_per_second = DIAMETER_BALL / seconds;
  double kmh = meter_per_second * 3.6;

  char speed[10];
  char kmh_temp[10];

  dtostrf(kmh, 2, 1, kmh_temp);
  sprintf(speed, "%s F", kmh_temp);

  LOG(speed);
}

boolean handleREST(goal_t *goal) {

  int diff = goal->rising_micros - goal->falling_micros;

  unsigned long token = random(65535);

  char path[512];
  sprintf(path, "%s/events/goals/%d?token=%lu&micro_seconds=%d", SERVER_URL, goal->id, token, diff);
  LOG(path);

  int timeout_start = millis();

  client.getAsynchronously(path);

  boolean response_ok = false;

  while (!client.ready()) {

    int current = millis() - timeout_start;

    if (current > 1000) {
      LOG("REST call timeout");
      break;
    }

    delay(100);
  }

  if (client.ready()) {
    response_ok = true;
  }

  client.close();

  return response_ok;
}

void blink(int pin, int times, int delay_millis) {
  for (int i = 0; i < times; i++) {
    if (i > 0) {
      delay(delay_millis);
    }
    digitalWrite(pin, HIGH);
    delay(delay_millis);
    digitalWrite(pin, LOW);
  }
}

void signalInit() {
  int led_delay = 250;
  for (int i = 0; i < 6; i++)
  {
    if (i == 3) {
      led_delay = led_delay << 1;
    }
    delay(led_delay);
    digitalWrite(LED_PIN_1, HIGH);
    digitalWrite(LED_PIN_2, HIGH);
    delay(led_delay);
    digitalWrite(LED_PIN_1, LOW);
    digitalWrite(LED_PIN_2, LOW);
  }
}

void signalError() {
  while (true) {
    digitalWrite(LED_PIN_2, HIGH);
    delay(100);
    digitalWrite(LED_PIN_2, LOW);
    delay(100);
  }
}

void handleRetry(goal_t *goal) {

  int retry = 0;
  int maxConnections = MAX_CONNECTION_ATTEMPTS;
  boolean success = false;

  for (; !success && retry < maxConnections; retry++) {

    delay(1000);

    char retry_tmp[8];
    sprintf(retry_tmp, "Retry #%d", retry);
    LOG(retry_tmp);

    success = handleREST(goal);
  }

  if (retry == 5) {
    LOG("Give up!");
    signalError();
  }
}

void handleGoal(goal_t *goal) {

  LOG("Sending request...");
  boolean success = handleREST(goal);

  if (!success) {
    handleRetry(goal);
  }

}

void handleInterruptState(goal_t *goal)
{
  char temp[30];
  
  goal->pin_state = !goal->pin_state;
  
  switch (goal->pin_state) {
    case 0:

      sprintf(temp, "IRQ edge goal %d falling", goal->id);
      LOG(temp);

      goal->falling_micros = micros();

      break;
    case 1:

      int id = goal->id;

      sprintf(temp, "IRQ edge goal %d rising", id);
      LOG(temp);

      if (goal->id == 1) {
        blink(LED_PIN_1, 2, 10000);
      } else if (goal->id == 2) {
        blink(LED_PIN_2, 2, 10000);
      }

      goal->rising_micros = micros();
      push(head, goal);

      goal = (goal_t *) malloc(sizeof(goal_t));
      goal->id = id;

      // TODO: Disable current pin irq for a specific time of ~3000ms
      // PCintPort::detachInterrupt(PCintPort::arduinoPin);

      break;
  }
}

void registerGoal_1()
{
  handleInterruptState(current_goal_1);
}

void registerGoal_2()
{
  handleInterruptState(current_goal_2);
}

/*****************************
 ***  Setup and main loop  ***
 *****************************/

void setup()
{

  pinMode(LED_PIN_1, OUTPUT);
  pinMode(LED_PIN_2, OUTPUT);

  pinMode(GOAL_1_OUT_PIN, OUTPUT);
  pinMode(GOAL_2_OUT_PIN, OUTPUT);

  digitalWrite(GOAL_1_OUT_PIN, HIGH);
  digitalWrite(GOAL_2_OUT_PIN, HIGH);

  signalInit();

  LOG("Init Arduino Yun Bridge ...");
  Bridge.begin();
  LOG("Bridge is initialized.");

  blink(LED_PIN_1, 2, 500);

  LOG("Connecting to server ...");
  
  int status = client.get(SERVER_URL);
  
  if (status != 0) {
     LOG("Can't establish connection to server!");
     signalError();
  }

  LOG("Connected to server");
  
  head->goal = NULL;
  head->next = NULL;

  current_goal_1->id = 1;
  current_goal_2->id = 2;
  
  current_goal_1->pin_state = LOW;
  current_goal_2->pin_state = LOW;

  attachInterrupt(digitalPinToInterrupt(GOAL_1_IN_PIN), registerGoal_1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(GOAL_2_IN_PIN), registerGoal_2, CHANGE);

  LOG("Light barriers are ready for use!\n");
}

void loop()
{
  goal_t *goal = pop(&head);

  // TODO: Re-Enable current disabled pin after a timeout
  // PCintPort::attachInterrupt(GOAL_1_IN_PIN, registerGoal_1, CHANGE);
  // PCintPort::attachInterrupt(GOAL_2_IN_PIN, registerGoal_2, CHANGE);
  
  if (goal != NULL) {
    handleGoal(goal);
  }
}


