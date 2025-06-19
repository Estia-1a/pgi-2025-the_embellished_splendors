#ifndef FEATURES_H
#define FEATURES_H

/* Tutoriel */
void helloWorld();
void dimension (char *source_path);
void first_pixel(char *source_path);
void tenth_pixel(char *source_path);
void second_line(char *source_path);
void print_pixel(char *filename, int x, int y);

/* Statistics */
void min_pixel(const char* filename);
void max_pixel(const char* filename);
void max_component(const char *filename, const char *component);
void min_component(const char *filename, const char *component);
void stat_report(const char* filename);

/* Colors */
void color_red(char *source_path);
void color_green(char *source_path);
void color_blue(char *source_path);
void color_gray(char *source_path);

/*Transform*/
void rotate_cw(char *source_path);
void rotate_acw(char *source_path);


#endif
