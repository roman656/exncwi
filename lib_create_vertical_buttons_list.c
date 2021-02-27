#include "exncwi.h"

Button* create_vertical_buttons_list(wchar_t* buttons_text[],
                                     uint32_t buttons_amount,
                                     uint16_t y, uint16_t x,
                                     uint16_t y_size, uint16_t x_size,
                                     int16_t interval)
{
    return create_buttons_list(buttons_text, buttons_amount, y, x,
            y_size, x_size, interval, -x_size);
}