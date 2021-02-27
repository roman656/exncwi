#include "exncwi.h"

void buttons_lists_concat(Button* list_1, Button* list_2)
{
    /* При корректных входных параметрах. */
    if (list_1 != list_2 && list_1 != NULL && list_2 != NULL)
    {
        while (list_1 != NULL)
        {
            /* Когда дошли до конца первого списка. */
            if (list_1->next == NULL)
            {
                /* Соединяем его с началом второго списка. */
                list_1->next = list_2;
                break;
            }

            /* Переход к следующей кнопке. */
            list_1 = list_1->next;
        }
    }
}