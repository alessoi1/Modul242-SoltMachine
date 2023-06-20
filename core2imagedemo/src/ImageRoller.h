#ifndef RANDOM_IMAGE_H_
#define RANDOM_IMAGE_H_
#include "Arduino.h"
#include "lvgl.h"

#define MAX_NUM_OF_IMAGES 10
#define MAX_TIMEOUT 500
#define MIN_TIMEOUT 1

#define IMAGE_ROLLER_ROLLING 1
#define IMAGE_ROLLER_STOPPED 0

class ImageRoller {
public:
	ImageRoller();
    void add_image(lv_obj_t * image);
    lv_obj_t * next();
    void start();
    bool is_stopped();
    unsigned long next_timeout();
private:
    lv_obj_t * image_objs[MAX_NUM_OF_IMAGES];
    uint8_t num_of_images = 0;
    uint8_t state = IMAGE_ROLLER_STOPPED;
    uint8_t current_image_pos = 0;
    uint16_t faktor = 1;
    uint16_t current_timeout = MIN_TIMEOUT;
};

#endif