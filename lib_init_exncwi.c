#include "exncwi.h"

int init_exncwi(bool use_cursor, bool use_echo, bool use_keypad,
                bool use_colors, uint16_t color_pairs_amount,
                const uint16_t* color_pairs_array)
{
    /* Проверка корректности входных параметров. */
    if ((color_pairs_amount < 1 || color_pairs_array == NULL) && use_colors)
    {
        return 1;
    }

    /* Установка используемой в системе локали. */
    setlocale(LC_ALL, "");

    /* Инициализация ncurses. */
    if (!initscr())
    {
        return 2;
    }

    /* Установка режима отображения курсора. */
    if (curs_set(use_cursor) == ERR)
    {
        return (close_exncwi() == ERR) ? 4 : 3;
    }

    /* Установка режима отображения символов, набираемых на клавиатуре. */
    if (use_echo)
    {
        if (echo() == ERR)
        {
            return (close_exncwi() == ERR) ? 6 : 5;
        }
    }
    else
    {
        if (noecho() == ERR)
        {
            return (close_exncwi() == ERR) ? 6 : 5;
        }
    }

    /* Включение/выключение режима поддержки функциональных клавиш. */
    if (keypad(stdscr, use_keypad) == ERR)
    {
        return (close_exncwi() == ERR) ? 8 : 7;
    }

    /*
     * Установка режима ввода cbreak. Символы становятся
     * доступными программе сразу после их набора на клавиатуре.
     */
    if (cbreak() == ERR)
    {
        return (close_exncwi() == ERR) ? 10 : 9;
    }

    if (use_colors)
    {
        /* Проверка, поддерживает ли вообще терминал цвета. */
        if (!has_colors())
        {
            return (close_exncwi() == ERR) ? 12 : 11;
        }

        /* Включение поддержки цветов. */
        if (start_color() == ERR)
        {
            return (close_exncwi() == ERR) ? 14 : 13;
        }

        /* 
         * Количество создаваемых цветовых пар
         * не может превышать максимальное.
         */
        if (color_pairs_amount > COLOR_PAIRS)
        {
            return (close_exncwi() == ERR) ? 16 : 15;
        }

        /* Создание цветовых пар. */
        uint16_t current_pair_id = 1;
        uint32_t colors_amount = color_pairs_amount * 2;

        for (uint32_t i = 0; i < colors_amount; i += 2)
        {
            if (ERR == init_pair(current_pair_id, color_pairs_array[i],
                    color_pairs_array[i + 1]))
            {
                return (close_exncwi() == ERR) ? 18 : 17;
            }

            current_pair_id++;
        }

        /* Установка текущей цветовой пары (первая). */
        if (wattrset(stdscr, COLOR_PAIR(1)) == ERR)
        {
            return (close_exncwi() == ERR) ? 20 : 19;
        }
    }

    return 0;
}