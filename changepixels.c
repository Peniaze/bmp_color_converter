#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <windows.h>
#include "bmp.h"



void add_colors_value(
	int Red,
	int Green,
	int Blue)
/*
 * Add set colors to an array of bitmap data
*/
{
    saved = 0;
// helper var for overflow check
    int hold_value;
    int i,j;
    long int push_to_currentline;
    for (i=0; i<image_header.height_px; i++)
    {
	push_to_currentline = i*image_header.width_px*3+i*padding;
	for (j=0; j<image_header.width_px; j++)
	{
	    hold_value = image_data[3*j+push_to_currentline];
	    hold_value += Blue;
	    if (hold_value>0xFF)
		image_data[3*j+push_to_currentline] = 0xFF;
	    else
		if (hold_value<0)
		    image_data[3*j+push_to_currentline] = 0;
		else
		    image_data[3*j+push_to_currentline] += Blue;
	    hold_value = image_data[3*j+1+push_to_currentline];
	    hold_value += Green;
	    if (hold_value>0xFF)
		image_data[3*j+1+push_to_currentline] = 0xFF;
	    else
		if (hold_value<0)
		    image_data[3*j+1+push_to_currentline] = 0;
		else
		    image_data[3*j+1+push_to_currentline] += Green;
	    hold_value = image_data[3*j+2+push_to_currentline];
	    hold_value += Red;
	    if (hold_value>0xFF)
		image_data[3*j+2+push_to_currentline] = 0xFF;
	    else
		if (hold_value<0)
		    image_data[3*j+2+push_to_currentline] = 0;
		else
		    image_data[3*j+2+push_to_currentline] += Red;
	}
    }
}

void shhi_change(
	char shhi,
	int tolerance,
	int value)
/*
 * Changes the shadows/highlights of a picture based on tolerance
 * shhi = 0 if darkening highlights
 * shhi = 1 if brightening shadows
 * value >> increases each color's value by itself
 * tolerance 0-765 >>
 *	    765 >> most bright
 *	    0	>> most dark
*/
{
    saved = 0;
    int hold_value;
    int i,j;
    long int push_to_currentline;
    if (!shhi)
	tolerance = 765 - tolerance;
    for (i=0; i<image_header.height_px; i++)
    {
	push_to_currentline = i*image_header.width_px*3+i*padding;
	for (j=0; j<image_header.width_px; j++)
	{
	    hold_value = image_data[3*j+push_to_currentline];
	    hold_value += image_data[3*j+1+push_to_currentline];
	    hold_value += image_data[3*j+2+push_to_currentline];
	    if (shhi)
	    {
		if (hold_value+3*value<tolerance)
		{
		    image_data[3*j+push_to_currentline] += value;
		    image_data[3*j+1+push_to_currentline] += value;
		    image_data[3*j+2+push_to_currentline] += value;
		}
	    }
	    else
		if (hold_value-3*value>tolerance)
		{
		    image_data[3*j+push_to_currentline] -= value;
		    image_data[3*j+1+push_to_currentline] -= value;
		    image_data[3*j+2+push_to_currentline] -= value;
		}
	}
    }
}

void invert_colors(void)
/*
 * Inverts colors of a picture
 * (for each color 0xFF - *current color value*)
*/
{
    saved = 0;
    int i,j;
    long int push_to_currentline;
    for (i=0; i<image_header.height_px; i++)
    {
	push_to_currentline = i*image_header.width_px*3+i*padding;
	for (j=0; j<image_header.width_px; j++)
	{
	    image_data[3*j+push_to_currentline] = 0xFF - image_data[3*j+push_to_currentline];
	    image_data[3*j+1+push_to_currentline] = 0xFF - image_data[3*j+1+push_to_currentline];
	    image_data[3*j+2+push_to_currentline] = 0xFF - image_data[3*j+2+push_to_currentline];
	}
    }
}

void greyscale(void)
/*
 * Puts picture in greyscale
 * sum of all colors divided evenly between them
*/
{
    saved = 0;
    int i,j;
    int hold_value;
    long int push_to_currentline;
    for (i=0; i<image_header.height_px; i++)
    {
	push_to_currentline = i*image_header.width_px*3+i*padding;
	for (j=0; j<image_header.width_px; j++)
	{
	    hold_value = image_data[3*j+push_to_currentline];
	    hold_value += image_data[3*j+1+push_to_currentline];
	    hold_value += image_data[3*j+2+push_to_currentline];
	    hold_value /= 3;
	    image_data[3*j+push_to_currentline] = hold_value;
	    image_data[3*j+1+push_to_currentline] = hold_value;
	    image_data[3*j+2+push_to_currentline] = hold_value;
	}
    }
}


