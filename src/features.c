#include <estia-image.h>
#include <stdio.h>
#include <stdlib.h>


#include "features.h"
#include "utils.h"

/**
 * @brief Here, you have to code features of the project.
 * Do not forget to commit regurlarly your changes.
 * Your commit messages must contain "#n" with: n = number of the corresponding feature issue.
 * When the feature is totally implemented, your commit message must contain "close #n".
 */

void helloWorld() {
    printf("Hello World !");
}

/* Tutoriel */

void dimension(char *source_path) {
    unsigned char *data = NULL;
    int width = 10, height = 10, channels = 0;

    int result = read_image_data(source_path, &data, &width, &height, &channels);

    if (result == 0) {
        fprintf(stderr, "impossible de lire l'image \"%s\" \n", source_path);
        return;
    }

    printf("dimension: %d, %d\n", width, height);

    free(data);
}

void first_pixel(char *source_path) {
    unsigned char *data;
    int width, height, channels;

    if (read_image_data(source_path, &data, &width, &height, &channels) != 0) {
        printf("first_pixel: %d, %d, %d\n", data[0], data[1], data[2]);
    } else {
        printf("Erreur lors de la lecture de l'image\n");
    }
}

void tenth_pixel(char *source_path) {
    unsigned char *data = NULL;
    int width, height, channels;

    read_image_data(source_path, &data, &width, &height, &channels);

    if (width < 10) {
        printf("largeur < 10 \n");
        free(data);
        return;
    }

    int index = (9 * channels); // 9e pixel (x=9,y=0), channels par pixel
    unsigned char R = data[index];
    unsigned char G = data[index + 1];
    unsigned char B = data[index + 2];

    printf("tenth_pixel: %d, %d, %d\n", R, G, B);

    free(data);
}

void second_line(char *source_path) {
    unsigned char *data = NULL;
    int width, height, channels;
    read_image_data(source_path, &data, &width, &height, &channels);
    if (height < 2) {
        printf("Image too small\n");
        return;
    }
    int index = width * channels; // Premier pixel de la deuxième ligne (ligne 1)
    printf("second_line: %d, %d, %d\n", data[index], data[index + 1], data[index + 2]);
}

void print_pixel(char *filename, int x, int y) {
    unsigned char *data = NULL;
    int width, height, channels;
    read_image_data(filename, &data, &width, &height, &channels);
  
    pixelRGB *p = get_pixel(data, width, height, channels, x, y);
    if (p == NULL) {
        printf("Coordinates out of range\n");
        return;
    }
    printf("print_pixel (%d, %d): %d, %d, %d\n", x, y, p->R, p->G, p->B);
}

/* Statistics */

void max_pixel(const char* filename) {
    unsigned char* data = NULL;
    int width, height, channels;

    if (read_image_data(filename, &data, &width, &height, &channels)==0) {
        fprintf(stderr, "impossible de lire l'image %s\n", filename);
        return;
    }

    int best_index = 0;
    int max_sum = 0;

    for (int i = 0; i < width * height; i++) {
        int r = data[i * channels];
        int g = data[i * channels + 1];
        int b = data[i * channels + 2];
        int sum = r + g + b;

        if (i == 0 || sum > max_sum) {
            max_sum = sum;
            best_index = i;
        }
    }

    int x = best_index % width;
    int y = best_index / width;
    int r = data[best_index * channels];
    int g = data[best_index * channels + 1];
    int b = data[best_index * channels + 2];

    printf("max_pixel (%d, %d): %d, %d, %d\n", x, y, r, g, b);
    free(data);
}

void min_pixel(const char *filename) {
    unsigned char *data;
    int width, height, channels;

    if (read_image_data(filename, &data, &width, &height, &channels)==0) {
        printf("Erreur lecture image\n");
        return;
    }

    int min_sum = 1000;
    int min_x = 0, min_y = 0;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int i = (y * width + x) * channels;
            int r = data[i], g = data[i + 1], b = data[i + 2];
            int sum = r + g + b;

            if (sum < min_sum) {
                min_sum = sum;
                min_x = x;
                min_y = y;
            }
        }
    }

    int i = (min_y * width + min_x) * channels;
    printf("min_pixel (%d, %d): %d, %d, %d\n", min_x, min_y, data[i], data[i+1], data[i+2]);

    free(data);
}

void max_component(const char *filename, const char *component) {
    unsigned char *data = NULL;
    int width, height, channels;

    if (read_image_data(filename, &data, &width, &height, &channels)==0) {
        printf("erreur lecture image\n");
        return;
    }

    int max_value = -1, max_x = 0, max_y = 0;
    int index = 0;
    if (component[0] == 'R') {
        index = 0;
    } else if (component[0] == 'G') {
        index = 1;
    } else {
        index = 2; 
    }

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int i = (y * width + x) * channels;
            int value = data[i + index];
            if (value > max_value) {
                max_value = value;
                max_x = x;
                max_y = y;
            }
        }
    }

    printf("max_component %s (%d, %d): %d\n", component, max_x, max_y, max_value);
    free(data);
}

void min_component(const char *filename, const char *component) {
    unsigned char *data = NULL;
    int width = 0, height = 0, channel_count = 0;

    if (read_image_data(filename, &data, &width, &height, &channel_count) == 0) {
        printf("lecture image impossible.\n");
        return;
    }

    int comp_index;
    if (component[0] == 'R')
        comp_index = 0;
    else if (component[0] == 'G')
        comp_index = 1;
    else if (component[0] == 'B')
        comp_index = 2;
    else {
        printf("composant invalide. Utilisez R, G ou B.\n");
        free(data);
        return;
    }

    int min_value = 256; 
    int min_x = 0, min_y = 0;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int idx = (y * width + x) * channel_count + comp_index;
            if (data[idx] < min_value) {
                min_value = data[idx];
                min_x = x;
                min_y = y;
            }
        }
    }

    printf("min_component %c (%d, %d): %d\n", component[0], min_x, min_y, min_value);

    free(data);
}

void stat_report(const char* filename) {
    FILE* file = fopen("stat_report.txt", "w");

    max_pixel(filename);
    fprintf(file, "\n");

    min_pixel(filename);
    fprintf(file, "\n");

    max_component(filename, "R");
    fprintf(file, "\n");

    max_component(filename, "G");
    fprintf(file, "\n");

    max_component(filename, "B");
    fprintf(file, "\n");

    min_component(filename, "R");
    fprintf(file, "\n");

    min_component(filename, "G");
    fprintf(file, "\n");

    min_component(filename, "B");

    fclose(file);

    printf("Enregistré dans stat_report.txt\n");
}

/* Colors */

void color_red(char *source_path) {
    unsigned char *data = NULL;
    int width, height, channels;

    if (read_image_data(source_path, &data, &width, &height, &channels) == 0) {
        printf("lecture image impossible.\n");
        return;
    }

    for (int i = 0; i < width * height * channels; i += channels) {
        data[i + 1] = 0; // G
        data[i + 2] = 0; // B
    }

    write_image_data("image_out.bmp", data, width, height);
    free(data);
}

void color_green(char *source_path) {
    unsigned char *data = NULL;
    int width, height, channels;

    if (read_image_data(source_path, &data, &width, &height, &channels) == 0) {
        printf("Impossible de lire l'image.\n");
        return;
    }

    for (int i = 0; i < width * height * channels; i += channels) {
        data[i + 0] = 0; 
        data[i + 2] = 0; 
    }

    if (write_image_data("image_out.bmp", data, width, height) == 0) {
        printf("Erreur lors de l'écriture de l'image.\n");
    }

    free(data);
}

void color_blue(char *source_path) {
    unsigned char *data = NULL;
    int width, height, channels;

    if (read_image_data(source_path, &data, &width, &height, &channels) == 0) {
        printf("Impossible de lire l'image.\n");
        return;
    }

    for (int i = 0; i < width * height * channels; i += channels) {
        data[i + 0] = 0; 
        data[i + 1] = 0; 
    }

    if (write_image_data("image_out.bmp", data, width, height) == 0) {
        printf("Erreur lors de l'écriture de l'image.\n");
    }

    free(data);
}

void color_gray(char *source_path) {
    unsigned char *data = NULL;
    int width, height, channels;

    if (read_image_data(source_path, &data, &width, &height, &channels) == 0) {
        printf("Lecture de l'image impossible.\n");
        return;
    }

    for (int i = 0; i < width * height * channels; i += channels) {
        unsigned char r = data[i];
        unsigned char g = data[i + 1];
        unsigned char b = data[i + 2];

        unsigned char gray = (r + g + b) / 3;

        data[i] = gray;
        data[i + 1] = gray;
        data[i + 2] = gray;
    }

    if (write_image_data("image_out.bmp", data, width, height) == 0) {
        printf("Erreur lors de l'écriture de l'image.\n");
    }

    free(data);
}

void rotate_cw(char *source_path) {
    unsigned char *data = NULL;
    int width, height, channels;

    if (read_image_data(source_path, &data, &width, &height, &channels) == 0) {
        printf("Erreur de lecture image.\n");
        return;
    }

    int new_width = height;
    int new_height = width;
    unsigned char *rotated_data = malloc(new_width * new_height * channels);

    if (!rotated_data) {
        printf("Erreur d'allocation mémoire.\n");
        free(data);
        return;
    }

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            for (int c = 0; c < channels; ++c) {
                rotated_data[(x * new_width + (new_width - 1 - y)) * channels + c] =
                    data[(y * width + x) * channels + c];
            }
        }
    }

    if (write_image_data("image_out.bmp", rotated_data, new_width, new_height)== 0 ) {
        printf("Erreur d'écriture de l'image.\n");
    }

    free(data);
    free(rotated_data);
}

void rotate_acw(char *source_path) {
    unsigned char *data =NULL ;
    int width, height,channels ;

    if(read_image_data(source_path, &data, &width, &height, &channels) ==0) {
        printf("Erreur de lecture image.\n");
        return;
    }
    int new_width = height;
    int new_height = width;
    unsigned char *rotated_data = malloc(new_width * new_height * channels);

    if (!rotated_data) {
        printf("Erreur d'allocation mémoire.\n");
        free(data);
        return;
    }

    for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
        for (int c = 0; c < channels; ++c) {
            int new_x = y;
            int new_y = width - 1 - x;
            rotated_data[(new_y * new_width + new_x) * channels + c] =
                data[(y * width + x) * channels + c];
        }
    }
}


    if (write_image_data("image_out.bmp", rotated_data, new_width, new_height)== 0 ) {
        printf("Erreur d'écriture de l'image.\n");
    }

    free(data);
    free(rotated_data);
}