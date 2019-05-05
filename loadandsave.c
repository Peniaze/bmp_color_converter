#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <windows.h>
#include "bmp.h"






int load_file(char* path)
{
    FILE *my_bmp;
    my_bmp = fopen(path, "rb");
    if (my_bmp == 0)
	return 1;

    fread((&image_header), sizeof(BMPHeader), 1, my_bmp);


    fseek(my_bmp, 54, 0);
    image_data = malloc(sizeof(*image_data) * image_header.image_size_bytes);
    fread(image_data, image_header.image_size_bytes, 1, my_bmp);
    fclose(my_bmp);
    return 0;
}

void save_file(char* path)
{
    FILE *my_bmp;
    my_bmp = fopen(path, "wb");
    rewind(my_bmp);
    fwrite(&image_header, sizeof(BMPHeader), 1, my_bmp);
    fwrite(image_data, image_header.image_size_bytes, 1, my_bmp);
    fclose(my_bmp);
    saved++;
    name_set = 1;
}
