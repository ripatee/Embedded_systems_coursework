#include <stdio.h>
#include <string.h>

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <lvgl.h>
#include <zephyr/drivers/display.h>

#define SLEEP_TIME_MS	1000

LOG_MODULE_REGISTER(MAIN, LOG_LEVEL_DBG);

int main(void)
{
    int err;
    char count_str[11] = {0};
    uint32_t count = 0;

    // Display test stuff
    const struct device *display_dev;
    lv_obj_t *hello_world_label;
    lv_obj_t *count_label;
    lv_obj_t *top_label;
    lv_obj_t *bottom_label;

    display_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_display));
    if (!device_is_ready(display_dev))
    {
        LOG_ERR("Display not ready");
    }

    LOG_INF("Application starting");

    hello_world_label = lv_label_create(lv_scr_act());
    count_label = lv_label_create(lv_scr_act());
    top_label = lv_label_create(lv_scr_act());
    bottom_label = lv_label_create(lv_scr_act());

    lv_label_set_text(hello_world_label, "Hello world!");
    lv_label_set_text(count_label, "");
    lv_label_set_text(top_label, "Top text");
    lv_label_set_text(bottom_label, "Bottom text");
        
    lv_obj_align(hello_world_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_align(count_label, LV_ALIGN_CENTER, 0, 20);
    lv_obj_align(top_label, LV_ALIGN_TOP_MID, 0, 0);
    lv_obj_align(bottom_label, LV_ALIGN_BOTTOM_MID, 0, 0);

    lv_task_handler();
    display_blanking_off(display_dev); 

    LOG_INF("First write");
    k_msleep(SLEEP_TIME_MS);

    /* Main loop*/
    while(true)
    {
        LOG_INF("Main loop start");

        sprintf(count_str, "%d", count);
        lv_label_set_text(count_label, count_str);

        lv_task_handler();
        count++;

        k_msleep(SLEEP_TIME_MS);
    }
}