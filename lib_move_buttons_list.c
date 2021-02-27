#include "exncwi.h"

static bool is_moving_correct(Button* root_button_ptr, int16_t y, int16_t x)
{
    bool result = TRUE;
    int y_max, x_max;

    /* Получение значений максимальных допустимых координат на экране. */
    getmaxyx(stdscr, y_max, x_max);
    y_max--;
    x_max--;

    /* Проход по всему списку кнопок. */
    while (root_button_ptr != NULL)
    {
        /* Если будет выход кнопки за границы экрана. */
        if ((root_button_ptr->button_win->_begy + y) < 0
                || (root_button_ptr->button_win->_begx + x) < 0
                || (root_button_ptr->button_win->_begy +
                root_button_ptr->y_size - 1 + y) > y_max
                || (root_button_ptr->button_win->_begx +
                root_button_ptr->x_size - 1 + x) > x_max)
        {
            result = FALSE;
            break;
        }

        /* Переход к следующей кнопке. */
        root_button_ptr = root_button_ptr->next;
    }

    return result;
}

static int restore_moved_buttons(Button* root_button_ptr, int16_t y, int16_t x,
                                 uint32_t moved_buttons_amount)
{
    /* Восстановление ранее сдвинутых кнопок. */
    for (uint32_t i = 0; i < moved_buttons_amount; i++)
    {
        /* Перемещение окна кнопки на прежние координаты. */
        if (mvwin(root_button_ptr->button_win,
                  root_button_ptr->button_win->_begy - y,
                  root_button_ptr->button_win->_begx - x) == ERR)
        {
            return 3;
        }

        /* Переход к следующей кнопке. */
        root_button_ptr = root_button_ptr->next;
    }

    return 2;
}

int move_buttons_list(Button* root_button_ptr, int16_t y, int16_t x)
{
    /* Проверка входных параметров. */
    if (root_button_ptr == NULL || (y == 0 && x == 0))
    {
        return 1;
    }

    /* Проверка, не будет ли выхода кнопок за границы экрана. */
    if (!is_moving_correct(root_button_ptr, y, x))
    {
        return 2;
    }

    Button* temp = root_button_ptr;
    uint32_t moved_buttons_amount = 0;

    /* Проход по всему списку кнопок. */
    while (temp != NULL)
    {
        /* Перемещение окна кнопки на новые координаты. */
        if (mvwin(temp->button_win,
                  temp->button_win->_begy + y,
                  temp->button_win->_begx + x) == ERR)
        {
            /* Восстановление ранее сдвинутых кнопок. */
            return restore_moved_buttons(root_button_ptr, y, x,
                    moved_buttons_amount);
        }

        moved_buttons_amount++;

        /* Переход к следующей кнопке. */
        temp = temp->next;
    }

    return 0;
}