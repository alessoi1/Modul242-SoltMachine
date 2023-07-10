#include "ImageRoller.h"

ImageRoller::ImageRoller()
{
}

void ImageRoller::add_image(lv_obj_t *image, String imageName)
{
    if (num_of_images >= MAX_NUM_OF_IMAGES)
        return;
    lv_obj_set_hidden(image, false);
    image_names[num_of_images] = String(imageName);
    image_objs[num_of_images] = image;
    num_of_images++;
}

void ImageRoller::start()
{
    state = IMAGE_ROLLER_ROLLING;
    current_timeout = MIN_TIMEOUT;
    faktor = 1;
    current_image_pos = random(num_of_images);
}

String ImageRoller::get_name_of_image()
{
    return image_names[current_image_pos];
}

bool ImageRoller::is_stopped()
{
    return state == IMAGE_ROLLER_STOPPED;
}

unsigned long ImageRoller::next_timeout()
{
    return millis() + current_timeout;
}

lv_obj_t *ImageRoller::next()
{
    if (state == IMAGE_ROLLER_STOPPED)
        return image_objs[current_image_pos];
    lv_obj_set_hidden(image_objs[current_image_pos], true);
    current_image_pos++;
    if (current_image_pos >= num_of_images)
    {
        current_image_pos = 0;
    }
    current_timeout = current_timeout + faktor;
    faktor = faktor + 10;
    if (current_timeout >= MAX_TIMEOUT)
    {
        state = IMAGE_ROLLER_STOPPED;
    }
    lv_obj_set_hidden(image_objs[current_image_pos], false);
    return image_objs[current_image_pos];
}