#include "exncwi.h"

#define TEXT_COLOR COLOR_WHITE
#define LIGHT_COLOR COLOR_GREEN
#define ERROR_COLOR COLOR_RED
#define BACKGROUND_COLOR COLOR_BLACK

int main(int argc, char* argv[])
{
    uint16_t colors[] = {TEXT_COLOR,  BACKGROUND_COLOR,
                         LIGHT_COLOR, BACKGROUND_COLOR,
                         ERROR_COLOR, BACKGROUND_COLOR};
    wchar_t* main_menu_options[] = {L"Старт", L"Настройки", L"Выход"};
    wchar_t* main_menu_text = L"Главное меню";
    int options_amount = 3;
    int current_option = 0;
    bool has_finished = FALSE;

    /* Инициализация библиотеки exncwi. */
    int code = init_exncwi(FALSE, FALSE, TRUE, TRUE, options_amount, colors);

    if (code != OK)
    {
        fprintf(stderr, "init_exncwi() error. Code: %d\n", code);
        exit(EXIT_FAILURE);
    }

    /* Создание главного меню. */
    int main_menu_attributes[] = {COLOR_PAIR(2), COLOR_PAIR(1), COLOR_PAIR(1)};
    int button_x_size = 25;
    int button_y_size = 3;
    Button* main_menu_root_button = create_vertical_buttons_list(
            main_menu_options, options_amount, getmaxy(stdscr) / 3,
            (getmaxx(stdscr) - button_x_size) / 2, button_y_size,
            button_x_size, 0);

    while (!has_finished)
    {
        clear();
        mvaddwstr(getmaxy(stdscr) / 4,
                (getmaxx(stdscr) - wcslen(main_menu_text)) / 2, main_menu_text);
        box(stdscr, 0, 0);
        print_buttons(main_menu_root_button, TRUE,
                0, 0, TRUE, main_menu_attributes);

        switch(getch())
        {
            case KEY_UP:
            {
                if (current_option > 0)
                {
                    int temp = main_menu_attributes[current_option];
                    main_menu_attributes[current_option] = 
                            main_menu_attributes[current_option - 1];
                    main_menu_attributes[current_option - 1] = temp;
                    current_option--;
                }
                break;
            }
            case KEY_DOWN:
            {
                if (current_option < options_amount - 1)
                {
                    int temp = main_menu_attributes[current_option];
                    main_menu_attributes[current_option] = 
                            main_menu_attributes[current_option + 1];
                    main_menu_attributes[current_option + 1] = temp;
                    current_option++;
                }
                break;
            }
            case '\n':
            {
                has_finished = TRUE;
                break;
            }
            default: {}
        }
    }

    free_buttons(main_menu_root_button);
    close_exncwi();
    return 0;
}
