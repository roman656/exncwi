#include "exncwi.h"

void free_buttons(Button* root_button_ptr)
{
    Button* temp = root_button_ptr;

    while (temp != NULL)
    {
        /* Удаление окна кнопки. */
        if (root_button_ptr->button_win != NULL)
        {
            delwin(root_button_ptr->button_win);
        }

        /* Переназначение корня. */
        root_button_ptr = root_button_ptr->next;

        /* Удаление текущей кнопки. */
        free(temp);

        /* Переход к следующей кнопке. */
        temp = root_button_ptr;
    }
}