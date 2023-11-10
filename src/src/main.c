#include <stdio.h>
#include <string.h>

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <lvgl.h>
#include <zephyr/drivers/display.h>

#define SLEEP_TIME_MS	50

LOG_MODULE_REGISTER(MAIN, LOG_LEVEL_DBG);


int main(void)
{

    // Display test stuff
    const struct device *display_dev;
    lv_obj_t *hello_world_label;
    lv_obj_t *top_text_label;
    lv_obj_t *bottom_text_label;
    lv_obj_t *counter_label;
    static lv_style_t style1;

    char count_str[11] = {0};
    uint32_t count = 0;

    display_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_display));
    if (!device_is_ready(display_dev))
    {
        LOG_ERR("Display not ready");
    }

    LOG_INF("Application starting");

    hello_world_label = lv_label_create(lv_scr_act());
    top_text_label = lv_label_create(lv_scr_act());
    bottom_text_label = lv_label_create(lv_scr_act());
    counter_label = lv_label_create(lv_scr_act());

    lv_style_init(&style1);
    lv_style_set_bg_color(&style1, lv_color_black());
    lv_style_set_bg_opa(&style1, LV_OPA_100);
    lv_style_set_text_color(&style1, lv_color_white());

    lv_obj_set_style_bg_color(lv_scr_act(), lv_color_white(), 0);

    lv_label_set_text(hello_world_label, "Hello world!");
    lv_label_set_text(top_text_label, "Top text");
    lv_label_set_text(bottom_text_label, "Bottom text");
    lv_label_set_text(counter_label, "");

    lv_obj_add_style(hello_world_label, &style1, 0);
    lv_obj_add_style(top_text_label, &style1, 0);
    lv_obj_add_style(bottom_text_label, &style1, 0);
    lv_obj_add_style(counter_label, &style1, 0);


    lv_obj_align(hello_world_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_align(top_text_label, LV_ALIGN_TOP_MID, 0, 0);
    lv_obj_align(bottom_text_label, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_obj_align(counter_label, LV_ALIGN_CENTER, 0, 16);

    lv_task_handler();
    display_blanking_off(display_dev); 

    /* Main loop*/
    while(true)
    {
        sprintf(count_str, "%d", count);
        // lv_label_set_text(counter_label, count_str);
        lv_task_handler();
        count++;

        k_msleep(SLEEP_TIME_MS);

    }

    return 0;
}
