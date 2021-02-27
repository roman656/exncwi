#include "exncwi.h"

int print_buttons(const Button* root_button_ptr, bool show_box,
                  chtype vertical_char, chtype horizontal_char,
                  bool use_attributes, const int* attributes)
{
    /* Проверка входных параметров. */
    if (root_button_ptr == NULL || (use_attributes && attributes == NULL))
    {
        return 1;
    }

    /* Обновление стандартного экрана. */
    if (refresh() == ERR)
    {
        return 2;
    }

    /* Проход по всем кнопкам в списке. */
    for (uint32_t i = 0; root_button_ptr != NULL; i++)
    {
        /* Применение соответсвующих текущей кнопке аттрибутов (если задано). */
        if (use_attributes
                && (wbkgd(root_button_ptr->button_win, attributes[i]) != OK))
        {
            return 3;
        }

        /* Отображение контура кнопки (если задано). */
        if (show_box && (box(root_button_ptr->button_win,
                vertical_char, horizontal_char) == ERR))
        {
            return 4;
        }

        /* Печать текста кнопки с выравниванием по центру. */
        if (ERR == mvwaddwstr(root_button_ptr->button_win,
                root_button_ptr->y_size / 2,
                (root_button_ptr->x_size - wcslen(root_button_ptr->text)) / 2,
                root_button_ptr->text))
        {
            return 5;
        }

        /* Обновление окна кнопки. */
        if (wrefresh(root_button_ptr->button_win) == ERR)
        {
            return 2;
        }

        /* Переход к следующей кнопке. */
        root_button_ptr = root_button_ptr->next;
    }

    return 0;
}