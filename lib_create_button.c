#include "exncwi.h"

Button* create_button(wchar_t* button_text, uint16_t y, uint16_t x,
                      uint16_t y_size, uint16_t x_size)
{
    wchar_t** temp = &button_text;
    return create_buttons_list(temp, 1, y, x, y_size, x_size, 0, 0);
}