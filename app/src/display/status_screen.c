/*
 * Copyright (c) 2020 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#include <zmk/display/widgets/output_status.h>
#include <zmk/display/widgets/peripheral_status.h>
#include <zmk/display/widgets/battery_status.h>
#include <zmk/display/widgets/layer_status.h>
#include <zmk/display/widgets/wpm_status.h>
#include <zmk/display/status_screen.h>

#include <zephyr/logging/log.h>
LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

#if IS_ENABLED(CONFIG_ZMK_WIDGET_BATTERY_STATUS)
static struct zmk_widget_battery_status battery_status_widget;
#endif

#if IS_ENABLED(CONFIG_ZMK_WIDGET_OUTPUT_STATUS)
static struct zmk_widget_output_status output_status_widget;
#endif

#if IS_ENABLED(CONFIG_ZMK_WIDGET_PERIPHERAL_STATUS)
static struct zmk_widget_peripheral_status peripheral_status_widget;
#endif

#if IS_ENABLED(CONFIG_ZMK_WIDGET_LAYER_STATUS)
static struct zmk_widget_layer_status layer_status_widget;
#endif

#if IS_ENABLED(CONFIG_ZMK_WIDGET_WPM_STATUS)
static struct zmk_widget_wpm_status wpm_status_widget;
#endif

lv_obj_t *zmk_display_status_screen() {
    lv_obj_t *screen;
    screen = lv_obj_create(NULL);

    // Create a style object for padding
    static lv_style_t style;
    lv_style_init(&style);

    // Set padding values using configuration options
    lv_style_set_pad_top(&style, LV_STATE_DEFAULT, CONFIG_ZMK_DISPLAY_PADDING_TOP);
    lv_style_set_pad_bottom(&style, LV_STATE_DEFAULT, CONFIG_ZMK_DISPLAY_PADDING_BOTTOM);
    lv_style_set_pad_left(&style, LV_STATE_DEFAULT, CONFIG_ZMK_DISPLAY_PADDING_LEFT);
    lv_style_set_pad_right(&style, LV_STATE_DEFAULT, CONFIG_ZMK_DISPLAY_PADDING_RIGHT);

#if IS_ENABLED(CONFIG_ZMK_WIDGET_BATTERY_STATUS)
    zmk_widget_battery_status_init(&battery_status_widget, screen);
    lv_obj_add_style(zmk_widget_battery_status_obj(&battery_status_widget), LV_PART_MAIN, &style);
    lv_obj_align(zmk_widget_battery_status_obj(&battery_status_widget), LV_ALIGN_TOP_RIGHT,
                 -CONFIG_ZMK_DISPLAY_PADDING_RIGHT, CONFIG_ZMK_DISPLAY_PADDING_TOP);
#endif

#if IS_ENABLED(CONFIG_ZMK_WIDGET_OUTPUT_STATUS)
    zmk_widget_output_status_init(&output_status_widget, screen);
    lv_obj_add_style(zmk_widget_output_status_obj(&output_status_widget), LV_PART_MAIN, &style);
    lv_obj_align(zmk_widget_output_status_obj(&output_status_widget), LV_ALIGN_TOP_LEFT,
                 CONFIG_ZMK_DISPLAY_PADDING_LEFT, CONFIG_ZMK_DISPLAY_PADDING_TOP);
#endif

#if IS_ENABLED(CONFIG_ZMK_WIDGET_PERIPHERAL_STATUS)
    zmk_widget_peripheral_status_init(&peripheral_status_widget, screen);
    lv_obj_add_style(zmk_widget_peripheral_status_obj(&peripheral_status_widget), LV_PART_MAIN,
                     &style);
    lv_obj_align(zmk_widget_peripheral_status_obj(&peripheral_status_widget), LV_ALIGN_TOP_LEFT,
                 CONFIG_ZMK_DISPLAY_PADDING_LEFT, CONFIG_ZMK_DISPLAY_PADDING_TOP);
#endif

#if IS_ENABLED(CONFIG_ZMK_WIDGET_LAYER_STATUS)
    zmk_widget_layer_status_init(&layer_status_widget, screen);
    lv_obj_add_style(zmk_widget_layer_status_obj(&layer_status_widget), LV_PART_MAIN, &style);
    lv_obj_set_style_text_font(zmk_widget_layer_status_obj(&layer_status_widget),
                               lv_theme_get_font_small(screen), LV_PART_MAIN);
    lv_obj_align(zmk_widget_layer_status_obj(&layer_status_widget), LV_ALIGN_BOTTOM_LEFT,
                 CONFIG_ZMK_DISPLAY_PADDING_LEFT, -CONFIG_ZMK_DISPLAY_PADDING_BOTTOM);
#endif

#if IS_ENABLED(CONFIG_ZMK_WIDGET_WPM_STATUS)
    zmk_widget_wpm_status_init(&wpm_status_widget, screen);
    lv_obj_add_style(zmk_widget_wpm_status_obj(&wpm_status_widget), LV_PART_MAIN, &style);
    lv_obj_align(zmk_widget_wpm_status_obj(&wpm_status_widget), LV_ALIGN_BOTTOM_RIGHT,
                 -CONFIG_ZMK_DISPLAY_PADDING_RIGHT, -CONFIG_ZMK_DISPLAY_PADDING_BOTTOM);
#endif
    return screen;
}
