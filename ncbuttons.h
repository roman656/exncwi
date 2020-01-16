#ifndef NCBUTTONS_H_INCLUDED
#define NCBUTTONS_H_INCLUDED

/*------------------------------*/
/*      Библиотека "кнопок"     */
/*     Необходимо проверить     */
/*    подключение отмеченных    */
/*      библиотек из списка     */
/*       version: 0.1.0.3       */
/*   Диапазон значений exit():  */
/*        [-18000;-18001]       */
/*------------------------------*/

/*----------Библиотеки----------*/
#include <ncurses.h>             //<- !!!
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mystrch.h"             //<- !!!
/*------------------------------*/

/*-----------Структуры----------*/
/*Кнопка (здесь и далее: графическое представление кнопки)*/
typedef struct buttn
{
    int number;                  //Номер кнопки.
    int y_size;                  //Размер кнопки по оси Y.
    int x_size;                  //Размер кнопки по оси X.
    char* message;               //Текст кнопки.
    WINDOW* but_win;             //Указатель на окно кнопки.
    struct buttn* next;          //Указатель на следующую кнопку.
} BUTTON;

typedef struct progress_bar 
{
	int y_size;
    int x_size;
	int number_of_steps;
	int number_of_completed_steps;
	int max_value;
	int min_value;
	char* message;
	BUTTON* background_button;
	BUTTON* steps_buttns;
} PROGRESS_BAR;
/*------------------------------*/

/*------------Функции-----------*/
///Инициальзация ncurses.
///\param int if_cur - управление курсором. (1 - есть; 0 - нет);
///\param int if_keypad - подключение функциональных клавиш. (1 - есть; 0 - нет);
///\param int if_echo - отображаются ли нажатые клавиши на экране. (1 - отображаются; 0 - нет);
///\param int if_color - включить ли режим с поддержкой цветов. Если нет, то остальные параметры не важно, как назначить. (1 - да; 0 - нет);
///\param int pair_num - количество цветовых пар (текст & фон). Больше 0;
///\param int* colors_arr - массив, заполненный цветовыми парами. Например: int array[] = {1,3,4,6}. Четное количество элементов массива. Сначала 2 цвета для первой пары: цвет текста, цвет фона... И так для всех цветовых пар. Значений должно быть в 2 раза больше, чем число пар.
///В случае ошибки инициализации: exit(-18000); Если терминал не поддерживает цвета, но поступил запрос на подключение: exit(-18001).
void ncurses_start(int if_cur, int if_keypad, int if_echo, int if_color, int pair_num, int* colors_arr);

///Создает список кнопок (вертикальных).
///\param char** butt_mess - массив строк с текстом для каждой кнопки;
///\param int num_of_mess - количество сообщений для кнопок (равно количеству кнопок);
///\param int y_size - размер каждой кнопки по оси Y (>=0, но результат нормальный только в разумных пределах: >2);
///\param int x_size - размер каждой кнопки по оси X (>=0);
///\param int y - отступ по оси Y до первой кнопки;
///\param int poz - положение кнопок по оси X (0 - выравнивание по левому краю; 1 - по центру; 2 - по правому краю; иначе - по центру);
///\param int interval - расстояние по оси Y между кнопками;
///\param int local_x_poz - дополнительное смещение по оси X (добавляется к текущему смещению).
///\return Возвращает указатель на корневую кнопку (первую).
BUTTON* Create_vertical_buttons(char** butt_mess, int num_of_mess, int y_size, int x_size, int y, int poz, int interval, int local_x_poz);

///Создает список кнопок (горизонтальных).
///\param char** butt_mess - массив строк с текстом для каждой кнопки;
///\param int num_of_mess - количество сообщений для кнопок (равно количеству кнопок);
///\param int y_size - размер каждой кнопки по оси Y (>=0, но результат нормальный только в разумных пределах: >2);
///\param int x_size - размер каждой кнопки по оси X (>=0);
///\param int y - отступ по оси Y до первой кнопки;
///\param int poz - положение кнопок по оси X (0 - выравнивание по левому краю; 1 - по центру; 2 - по правому краю; иначе - по центру);
///\param int interval - расстояние по оси X между кнопками;
///\param int local_x_poz - дополнительное смещение по оси X (добавляется к текущему смещению).
///\return Возвращает указатель на корневую кнопку (первую).
BUTTON* Create_horizontal_buttons(char** butt_mess, int num_of_mess, int y_size, int x_size, int y, int poz, int interval, int local_x_poz);

///Создает полосу загрузки (горизонтальную).
PROGRESS_BAR* Create_horizontal_progressbar(char* bar_message, int max_value, int min_value, int number_of_steps, int y_size, int x_size, int y, int poz, int local_x_poz, int interval_for_steps);

///Отображает кнопки на экране (один аттрибут на все кнопки).
///\param BUTTON* root - указатель на корневую (первую) кнопку;
///\param int show_box - отображать ли контуры кнопок (1 - да, 0 - нет);
///\param int use_attr - использовать ли аттрибуты (1 - да, 0 - нет);
///\param int attr - сами аттрибуты (1 - да, 0 - нет).
void Print_buttons_mono(BUTTON* root, int show_box, int use_attr, int attr);

///Отображает кнопки на экране (для каждой кнопки свой аттрибут).
///\param BUTTON* root - указатель на корневую (первую) кнопку;
///\param int show_box - отображать ли контуры кнопок (1 - да, 0 - нет);
///\param int use_attr - использовать ли аттрибуты (1 - да, 0 - нет);
///\param int* attr - массив аттрибутов. Для каждой кнопки свой элемент (За соответствием количества кнопок количеству элементов массива следить вручную).
void Print_buttons(BUTTON* root, int show_box, int use_attr, int* attr);

void Print_progressbar_mono(PROGRESS_BAR* prog_bar, int show_box, int use_attr, int attr);

///Освобождает память, выделенную под кнопки.
///\param BUTTON* root - указатель на корневую (первую) кнопку.
void Free_buttons(BUTTON* root);
/*------------------------------*/

#endif // NCBUTTONS_H_INCLUDED
