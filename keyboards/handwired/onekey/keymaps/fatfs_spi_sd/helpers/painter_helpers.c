#include "helpers.h"

void draw_text_buffer(painter_device_t device, painter_font_handle_t font, char *text_buffer, uint16_t text_buffer_index) {
    uint16_t y = 0;
    uint8_t  h = font->line_height;

    char temp_buff[TEMP_BUFF_LEN];
    uint8_t temp_buff_index = 0;

    uint16_t len = strlen(text_buffer);

    for (uint16_t i = 0; i < len + 1; ++i) {
        // current position marker
        if (i == text_buffer_index) {
            temp_buff[temp_buff_index++] = '|';
        }

        char c = text_buffer[i];

        if (c == '\n') {
            temp_buff[temp_buff_index++] = 0; // null terminate the string before drawing
            qp_drawtext(device, 0, y, font, temp_buff);
            memset(temp_buff, 0, TEMP_BUFF_LEN);
            temp_buff_index = 0;
            y += h;
        }

        temp_buff[temp_buff_index++] = c;

        i++;
    }

    // leftover text
    if (temp_buff_index) {
        qp_drawtext(device, 0, y, font, temp_buff);
    }

}
