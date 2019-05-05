#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <windows.h>
#include "bmp.h"








int main()
{
// **Contents of the printf below:**
/*
* Welcome to bmp image converter!
* You should always backup your bmp before opening it in this program.
*
* Write path to source file:
*/
    printf("Welcome to bmp image converter!\nYou should always backup your bmp before opening it in this program.\n\nWrite path to source file:\n");


    char bmp_path[1000];
    scanf("%1000[^\n]", &bmp_path);
    system("cls");

    if (load_file(&bmp_path))
	goto error;
    saved = 0;
    name_set = 0;
    strcpy(filename, "default.bmp");


    padding = (image_header.width_px % 4);

// select from options





    while (!select_action());




// here starts writing of the bmp

    printf("Hello world!\n");
    free(image_data);
    return 0;


error:
    printf("Reading bmp file failed.");
    return 1;
}
