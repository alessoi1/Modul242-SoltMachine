#include <Arduino.h>
#include "view.h"
#include "networking.h"
#include "sideled.h"
#include "images/image_cherry.h"
#include "images/image_lemon.h"
#include "images/image_grapes.h"
#include "images/image_watermelon.h"
#include "images/image_luckyseven.h"
#include "ImageRoller.h"
#include "DFRobot_PAJ7620U2.h"

void event_handler_checkbox(struct _lv_obj_t *obj, lv_event_t event);
void event_handler_button(struct _lv_obj_t *obj, lv_event_t event);
void event_handler_gesture(struct _lv_obj_t *obj, lv_event_t event);
void init_image_roller();
void mqtt_callback(char *topic, byte *payload, unsigned int length);
void mqtt_subscribe(const char *topic);

unsigned long next_lv_task = 0;

ImageRoller *rip = new ImageRoller();

DFRobot_PAJ7620U2 gestureSensor;

void event_handler_button(struct _lv_obj_t *obj, lv_event_t event)
{
  if (event == LV_EVENT_PRESSED && rip->is_stopped())
  {
    rip->start();
    mqtt_publish("imageroller/action", "roll");
    
  }
}

void init_image_roller()
{
  rip->add_image(add_image(&image_cherry, 0, 0, event_handler_button), "lemon");
  rip->add_image(add_image(&image_lemon, 0, 0, event_handler_button), "grapes");
  rip->add_image(add_image(&image_grapes, 0, 0, event_handler_button), "watermelon");
  rip->add_image(add_image(&image_watermelon, 0, 0, event_handler_button), "luckyseven");
  rip->add_image(add_image(&image_luckyseven, 0, 0, event_handler_button), "cherry");
}

// ----------------------------------------------------------------------------
// MQTT callback
// ----------------------------------------------------------------------------
void mqtt_callback(char *topic, byte *payload, unsigned int length)
{
  // Parse Payload into String
  char *buf = (char *)malloc((sizeof(char) * (length + 1)));
  memcpy(buf, payload, length);
  buf[length] = '\0';
  String payloadS = String(buf);
  payloadS.trim();

  Serial.println(topic);
  Serial.println(payloadS);

  if (String(topic) == "imageroller/action")
  {
    if (payloadS == "roll")
    {
      if (rip->is_stopped())
      {
        rip->start();
      }
    }
  }
}

// ----------------------------------------------------------------------------
// UI event handlers
// ----------------------------------------------------------------------------

String buffer = "";
lv_obj_t *mbox;

// ----------------------------------------------------------------------------
// MAIN LOOP
// ----------------------------------------------------------------------------
unsigned long next_image_task = 0;

void loop()
{
  mqtt_subscribe("imageroller/action");
  if (next_lv_task < millis())
  {
    lv_task_handler();
    next_lv_task = millis() + 5;
  }
  if (next_image_task < millis())
  {
    rip->next();
    next_image_task = rip->next_timeout();
  }
  DFRobot_PAJ7620U2::eGesture_t gesture = gestureSensor.getGesture();
  if (gesture != gestureSensor.eGestureNone)
  {
    rip->start();
    mqtt_publish("imageroller/action", "roll");
     mqtt_publish("imageroller/image", rip->get_name_of_image().c_str());
  }
  mqtt_loop();
}

// ----------------------------------------------------------------------------
// MAIN SETUP
// ----------------------------------------------------------------------------

void init_networking()
{
  lv_obj_t *wifiConnectingBox = show_message_box_no_buttons("Connecting to WiFi...");
  lv_task_handler();
  delay(5);
  setup_wifi();
  mqtt_init(mqtt_callback);
  close_message_box(wifiConnectingBox);
}

void setup()
{
  init_m5();
  init_display();
  Serial.begin(115200);
  init_networking();
  gestureSensor.begin();
  init_image_roller();
  init_sideled();
  rip->start();
}