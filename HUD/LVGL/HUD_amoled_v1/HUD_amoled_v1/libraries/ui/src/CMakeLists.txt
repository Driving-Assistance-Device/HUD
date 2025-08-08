SET(SOURCES ui_Screen0.c
    ui.c
    ui_comp_hook.c
    ui_helpers.c
    ui_events.c
    ui_img_dist_png.c
    ui_img_lanel_png.c
    ui_img_laner_png.c
    ui_img_vehicle_png.c
    fonts/ui_font_MontserratBold32.c)

add_library(ui ${SOURCES})
