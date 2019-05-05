#ifndef BMP
#define BMP
#include <stdint.h>
#include <stdlib.h>

#pragma pack(push)
#pragma pack(1)
typedef struct {             // Total: 54 bytes
  uint16_t  type;             // Magic identifier: 0x4d42
  //uint16_t  _padding;
  uint32_t  sizee;             // File size in bytes
  uint16_t  reserved1;        // Not used
  uint16_t  reserved2;        // Not used
  uint32_t  offset;           // Offset to image data in bytes from beginning of file (54 bytes)
  uint32_t  dib_header_size;  // DIB Header size in bytes (40 bytes)
  int32_t   width_px;         // Width of the image
  int32_t   height_px;        // Height of image
  uint16_t  num_planes;       // Number of color planes
  uint16_t  bits_per_pixel;   // Bits per pixel
  uint32_t  compression;      // Compression type
  uint32_t  image_size_bytes; // Image size in bytes
  int32_t   x_resolution_ppm; // Pixels per meter
  int32_t   y_resolution_ppm; // Pixels per meter
  uint32_t  num_colors;       // Number of colors
  uint32_t  important_colors; // Important colors
} BMPHeader;
#pragma pack(pop)



BMPHeader image_header;
unsigned char* image_data;
int padding;
char saved;
char name_set;
char filename[35];



void add_colors_value(int Red, int Green, int Blue);
void shhi_change(char shhi, int tolerance, int value);
void invert_colors(void);
void greyscale(void);

int get_user_value(int from, int to);
int select_action(void);

int load_file(char* path);
void save_file(char* path);





#endif
