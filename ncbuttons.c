#include "ncbuttons.h"

void ncurses_start(int if_cur, int if_keypad, int if_echo, int if_color, int pair_num, int* colors_arr)
{
    if (!initscr()) 
	{
		fprintf(stderr,"ncurses initialization error!\n");
		exit(-18000);
    }
    if (if_cur) 
	{
        curs_set(1);
    }
    else 
	{
        curs_set(0);
    }
    if (if_keypad)
	{
        keypad(stdscr, 1);
    }
    else 
	{
        keypad(stdscr, 0);
    }
    if (if_echo) 
	{
        echo();
    }
    else 
	{
        noecho();
    }
    cbreak();    //частичный контроль клавиатуры (Ctrl+С - закроет программу)
    if (if_color) 
	{
        start_color();
        if (!has_colors()) 
		{
            fprintf(stderr,"This terminal does not support colors!\n");
			endwin();
            exit(-18001);
        }
        int i = 0, n = 1, check = pair_num;
        while (pair_num)
		{
            init_pair(n,colors_arr[i],colors_arr[i+1]);
            i += 2;
            n++;
            pair_num--;
        }
        if (check != 0) 
		{
            wattrset(stdscr,COLOR_PAIR(1));
        }
    }
}

BUTTON* Create_vertical_buttons(char** butt_mess, int num_of_mess, int y_size, int x_size, int y, int poz, int interval, int local_x_poz) 
{
    int px,x;
    px = getmaxx(stdscr);
    switch (poz)
	{
        case 0: 
		{
            x = 1 + local_x_poz;
            break;
        }
        case 1: 
		{
            x = (px - x_size)/2 + local_x_poz;
            break;
        }
        case 2: 
		{
            x = px - x_size - 1 + local_x_poz;
            break;
        }
        default: 
		{
            x = (px - x_size)/2;
        }
    }
    BUTTON* root = (BUTTON*)malloc_s(sizeof(BUTTON));
    root->message = butt_mess[0];
    root->number = 1;
    root->y_size = y_size;
    root->x_size = x_size;
    root->next = NULL;
    root->but_win = newwin(y_size,x_size,y,x);
    y = y + y_size + interval;
    BUTTON* temp = root;
    for (int i = 1; i < num_of_mess; i++)
	{
        temp->next = (BUTTON*)malloc_s(sizeof(BUTTON));
        temp = temp->next;
        temp->next = NULL;
        temp->number = i + 1;
        temp->y_size = y_size;
        temp->x_size = x_size;
        temp->message = butt_mess[i];
        temp->but_win = newwin(y_size,x_size,y,x);
        y = y + y_size + interval;
    }
    return root;
}

BUTTON* Create_horizontal_buttons(char** butt_mess, int num_of_mess, int y_size, int x_size, int y, int poz, int interval, int local_x_poz) 
{
    int px,x;
    px = getmaxx(stdscr);
    switch (poz)
	{
        case 0:
		{
            x = 1 + local_x_poz;
            break;
        }
        case 1: 
		{
            x = (px - x_size)/2 + local_x_poz;
            break;
        }
        case 2: 
		{
            x = px - x_size - 1 + local_x_poz;
            break;
        }
        default: 
		{
            x = (px - x_size)/2;
        }
    }
    BUTTON* root = (BUTTON*)malloc_s(sizeof(BUTTON));
    root->message = butt_mess[0];
    root->number = 1;
    root->y_size = y_size;
    root->x_size = x_size;
    root->next = NULL;
    root->but_win = newwin(y_size,x_size,y,x);
    x = x + x_size + interval;
    BUTTON* temp = root;
    for (int i = 1; i < num_of_mess; i++)
	{
        temp->next = (BUTTON*)malloc_s(sizeof(BUTTON));
        temp = temp->next;
        temp->next = NULL;
        temp->number = i + 1;
        temp->y_size = y_size;
        temp->x_size = x_size;
        temp->message = butt_mess[i];
        temp->but_win = newwin(y_size,x_size,y,x);
        x = x + x_size + interval;
    }
    return root;
}

PROGRESS_BAR* Create_horizontal_progressbar(char* bar_message, int max_value, int min_value, int number_of_steps, int y_size, int x_size, int y, int poz, int local_x_poz, int interval_for_steps)
{
	char* empty_message[] = {""};
	PROGRESS_BAR* result = (PROGRESS_BAR*)malloc_s(sizeof(PROGRESS_BAR));
	result->background_button = Create_horizontal_buttons(empty_message,1,y_size,x_size,y,poz,0,local_x_poz);
	result->x_size = x_size;
	result->y_size = y_size;
	result->number_of_steps = number_of_steps;
	result->number_of_completed_steps = 0;
	result->max_value = max_value;
	result->min_value = min_value;
	result->message = bar_message;
	int y_size_step = y_size - 2;
	int x_size_step = (x_size - 2) / (max_value / (max_value / number_of_steps));
	int poz_step = 0;
	int y_step = y_size + 1;
	int curr_x_step;
	int l_px;
	char* step_mess[] = {""};
    l_px = getmaxx(stdscr);
	switch (poz)
	{
        case 0:
		{
            curr_x_step = 1 + local_x_poz;
            break;
        }
        case 1: 
		{
            curr_x_step = (l_px - x_size)/2 + local_x_poz;
            break;
        }
        case 2: 
		{
            curr_x_step = l_px - x_size + local_x_poz - 1;
            break;
        }
        default: 
		{
            curr_x_step = (l_px - x_size)/2;
        }
    }
	result->steps_buttns = Create_horizontal_buttons(step_mess,number_of_steps,y_size_step,x_size_step,y_step,poz_step,interval_for_steps,curr_x_step);
	return result;
}


void Print_buttons_mono(BUTTON* root, int show_box, int use_attr, int attr) 
{
    refresh();
    while (root != NULL) 
	{
        if (use_attr) 
		{
            wattron(root->but_win,attr);
        }
        if (show_box) 
		{
            box(root->but_win,0,0);
        }
        mvwprintw(root->but_win,root->y_size/2,(root->x_size-strlen(root->message))/2,"%s",root->message);
        wrefresh(root->but_win);
        root = root->next;
    }
}

void Print_buttons(BUTTON* root, int show_box, int use_attr, int* attr)
{
    refresh();
    int i = 0;
    while (root != NULL) 
	{
        if (use_attr)
		{
            wattron(root->but_win,attr[i]);
        }
        if (show_box)
		{
            box(root->but_win,0,0);
        }
        mvwprintw(root->but_win,root->y_size/2,(root->x_size-strlen(root->message))/2,"%s",root->message);
        wrefresh(root->but_win);
        root = root->next;
        i++;
    }
}

void Free_buttons(BUTTON* root)
{
    BUTTON* temp = root;
    while (root != NULL)
	{
        delwin(root->but_win);
        root = root->next;
        free(temp);
        temp = root;
    }
}
