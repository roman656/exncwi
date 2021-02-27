#include "exncwi.h"

/*
 * TODO: проверку, что создаваемые кнопки не находятся частично/полностью
 * за пределами экрана.
 */
Button* create_buttons_list(wchar_t* buttons_text[],
                            uint32_t buttons_amount, uint16_t y, uint16_t x,
                            uint16_t y_size, uint16_t x_size,
                            int16_t y_interval, int16_t x_interval)
{
    /* Проверка входных параметров. */
    if ((buttons_text == NULL) || (buttons_amount < 1)
            || (y_size < 1) || (x_size < 1))
    {
        return NULL;
    }

    Button* temp = NULL;
    Button* root_button_ptr = NULL;

    /* Координаты верхнего левого угла текущей кнопки. */
    uint16_t y_temp = y;
    uint16_t x_temp = x;

    for (uint32_t i = 0; i < buttons_amount; i++) 
    {
        /* Создание новой кнопки. */
        if (i != 0)
        {
            temp->next = (Button*) malloc(sizeof(Button));
            temp = temp->next;
        }
        else
        {
            temp = (Button*) malloc(sizeof(Button));

            /* Сохранение указателя на корень списка. */
            root_button_ptr = temp;
        }

        /* Если возникла ошибка при выделении памяти. */
        if (temp == NULL)
        {
            /* Очистка памяти от созданных ранее кнопок. */
            free_buttons(root_button_ptr);

            return NULL;
        }

        /* Инициализация текущей кнопки. */
        temp->next = NULL;
        temp->id = i + 1;
        temp->y_size = y_size;
        temp->x_size = x_size;
        temp->text = buttons_text[i];
        temp->button_win = newwin(y_size, x_size, y_temp, x_temp);

        /* Если возникла ошибка при создании окна кнопки. */
        if (temp->button_win == NULL)
        {
            /* Очистка памяти от созданных ранее кнопок. */
            free_buttons(root_button_ptr);

            return NULL;
        }

        /* Перезапись координат следующей кнопки. */
        y_temp += y_size + y_interval;
        x_temp += x_size + x_interval;
    }

    return root_button_ptr;
}