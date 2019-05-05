#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <windows.h>
#include "bmp.h"



int get_user_value(int from, int to)
{
    fflush(stdin);
    int temp;
    printf("Range %d-%d: ", from, to);
    scanf("%d", &temp);
    return temp;
}

void user_save(void)
{
    strcpy(filename, "");
    system("cls");
    printf("Save this file as: [max 30 characters, '.bmp' is added automatically]\n");
    fflush(stdin);
    scanf("%30[^\n]", filename);
    strcat(filename, ".bmp");
    save_file(filename);
}



// Returns 1 to escape loop
int select_action(void)
{
// temporary variable (must be bigger than 8bit)
	int temp;
	char option;
	int R = 0;
	int G = 0;
	int B = 0;
// **Contents of the printf below:**
/*
* Select action:
* [0] -- make image brighter
* [1] -- make image darker
* [2] -- brighten shadows
* [3] -- darken highlights
* [4] -- adjust colors manually
* [5] -- invert colors
* [6] -- greyscale
*
* [s] -- save
* [S] -- save as
* [q] -- save and quit program
* [Q] -- exit program w/o saving
*
*  Input:
*/
	system("cls");
	printf("Select action:\n\n[0] -- make image brighter\n[1] -- make image darker\n[2] -- brighten shadows\n[3] -- darken highlights\n[4] -- adjust colors manually\n[5] -- invert colors\n[6] -- greyscale\n\n[s] -- save \n[S] -- save as\n[q] -- save and quit program\n[Q] -- exit program w/o saving\n\n Input: ");
	fflush(stdin);
	scanf("%c", &option);
	system("cls");
	switch (option)
	{
	    case '0':
		printf("Make image brighter by\n");
		temp = get_user_value(0,255);
		R = temp; G = temp; B = temp;
		add_colors_value(R,G,B);
		return 0;
	    case '1':
		printf("Make image darker by\n");
		temp = get_user_value(0,255);
		R = -temp; G = -temp; B = -temp;
		add_colors_value(R,G,B);
		return 0;
	    case '2':
		printf("Make shadows brighter by\n");
		temp = get_user_value(0,255);
		printf("\nInsert shadow tolerance [lower values mean less tolerance]\n");
		R = get_user_value(0,765);
		shhi_change(0,R,temp);
		return 0;
	    case '3':
		printf("Make highlights darker by\n");
		temp = get_user_value(0,255);
		printf("\nInsert shadow tolerance [lower values mean less tolerance]\n");
		R = get_user_value(0,765);
		shhi_change(1,R,temp);
		return 0;
	    case '4':
		printf("Increase color values\n");
		printf("Red : ");
		R = get_user_value(-255,255);
		printf("\n");
		printf("Green : ");
		G = get_user_value(-255,255);
		printf("\n");
		printf("Blue : ");
		B = get_user_value(-255,255);
		add_colors_value(R,G,B);
		printf("\n");
		return 0;
	    case '5':
		invert_colors();
		return 0;
	    case '6':
		greyscale();
		return 0;
	    case 's':
		if (name_set == 0)
		    user_save();
		else
		    save_file(filename);
		return 0;
	    case 'S':
		user_save();
		return 0;
	    case 'q':
		if (name_set == 0)
		    user_save();
		else
		    save_file(filename);
		return 1;
	    case 'Q':
		if (saved == 0)
		{
		    system("cls");
		    printf("Do you want to exit program without saving?\n[y]: ");
		    char c;
		    fflush(stdin);
		    scanf(" %c", &c);
		    if (c == 'y')
			return 1;
		    else
			return 0;
		}
		return 1;
	    default:
		system("cls");
		printf("Wrong input.");
		Sleep(1000);
		return 0;
	}
}
