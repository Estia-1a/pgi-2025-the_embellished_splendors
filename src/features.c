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

void max_pixel(const char *source_path) {
    unsigned char *data = NULL;
    int width, height, channels;

    if (read_image_data(source_path, &data, &width, &height, &channels) == 0) {
        printf("Erreur : lecture image impossible.\n");
        return;
    }

    int max_sum = -1;
    int max_x = 0, max_y = 0;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int i = (y * width + x) * channels;
            int r = data[i];
            int g = data[i + 1];
            int b = data[i + 2];
            int sum = r + g + b;

            if (sum > max_sum) {
                max_sum = sum;
                max_x = x;
                max_y = y;
            }
        }
    }

    int idx = (max_y * width + max_x) * channels;
    printf("max_pixel (%d, %d): %d, %d, %d\n", max_x, max_y, data[idx], data[idx + 1], data[idx + 2]);

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

void color_invert(char *source_path) {
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
        
        data[i] = 255 - r;
        data[i + 1] = 255 - g;
        data[i + 2] = 255 - b;
    }  

    if (write_image_data("image_out.bmp", data, width, height) == 0) {
        printf("Erreur lors de l'écriture de l'image.\n");
    }

    free(data);
}

void color_gray_luminance(char *source_path) {
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
        unsigned char value = 0.21*r + 0.72*g + 0.07*b;
        
        data[i] = value;
        data[i + 1] = value;
        data[i + 2] = value;
    }

    if (write_image_data("image_out.bmp", data, width, height) == 0) {
        printf("Erreur lors de l'écriture de l'image.\n");
    }

    free(data);

}

int max(int n1, int n2, int n3) {
    int max = 0 ;

    if (n3>n2 && n3>n1) {
        max = n3;
    } else if (n2>n1) {
        max = n2 ;
    } else {
        max = n1 ;
    }

    return max ;
}

int min(int n1, int n2, int n3) {
    int min = 0 ;

    if (n3<n2 && n3<n1) {
        min = n3;
    } else if (n2<n1) {
        min = n2 ;
    } else {
        min = n1 ;
    }

    return min ;
}

void color_desaturate(char *source_path) {
    unsigned char *data = NULL;
    int width, height, channels;

    if (read_image_data(source_path, &data, &width, &height, &channels) == 0) {
        printf("Lecture de l'image impossible.\n");
        return;
    }

    for (int i = 0; i < width * height * channels; i += channels) {
        unsigned char R = data[i];
        unsigned char G = data[i + 1];
        unsigned char B = data[i + 2];
        unsigned char new_val = (min(R, G, B) + max(R, G, B)) / 2;
        
        data[i] = new_val;
        data[i + 1] = new_val;
        data[i + 2] = new_val;
    }

    if (write_image_data("image_out.bmp", data, width, height) == 0) {
        printf("Erreur lors de l'écriture de l'image.\n");
    }

    free(data);

}

void scale_crop(char *source_path, int center_x, int center_y, int new_width, int new_height){
    unsigned char *data = NULL;
    int width, height, channels;
 
    read_image_data(source_path, &data, &width, &height, &channels);
 
    unsigned char *crop_data = malloc(new_width * new_height * channels);
 
    memset(crop_data, 0, new_width * new_height * channels);

    int debut_x = center_x - new_width / 2;
    int debut_y = center_y - new_height / 2;
 
    for (int y = 0; y < new_height; ++y) {
        for (int x = 0; x < new_width; ++x) {
            int img_original_x = debut_x + x;
            int img_original_y = debut_y + y;
            
            if (img_original_x >= 0 && img_original_x < width && img_original_y >= 0 && img_original_y < height) {
                for (int c = 0; c < channels; ++c) {
                    crop_data[(y * new_width + x) * channels + c] = data[(img_original_y * width + img_original_x) * channels + c];
                }
            }
        }
    }
 
    write_image_data("image_out.bmp", crop_data, new_width, new_height);
 
    free(data);
    free(crop_data);
}


/* TRANSFORM */

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

void mirror_horizontal(char *source_path){
    unsigned char *data=NULL ;
    int width, height, channels ;

    if(read_image_data(source_path, &data, &width, &height, &channels) ==0){
        printf("Erreur de lecture image.\n");
        return; 
    }

    unsigned char *mirror_data = malloc(width * height * channels);
        if (!mirror_data) {
            printf("Erreur mémoire.\n");
            free(data);
            return;
    }

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x){
            for (int c=0; c < channels; ++c){
                mirror_data[(y * width + (width - 1 - x)) * channels + c] =
                    data[(y * width + x) * channels + c];    
            }
        }
    }

    if (write_image_data("image_out.bmp", mirror_data, width, height)== 0 ) {
        printf("Erreur d'écriture de l'image.\n");
    }

    free(data);
    free(mirror_data);
}

void mirror_vertical(char *source_path){
    unsigned char *data=NULL ;
    int width, height, channels ;

    if(read_image_data(source_path, &data, &width, &height, &channels) ==0){
        printf("Erreur de lecture image.\n");
        return; 
    }

    unsigned char *mirror_data = malloc(width * height * channels);
        if (!mirror_data) {
            printf("Erreur mémoire.\n");
            free(data);
            return;
    }

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x){
            for (int c=0; c < channels; ++c){
                mirror_data[(y * width +  x) * channels + c] =
                    data[((height - 1 - y) * width + x) * channels + c];   
            }
        }
    }

    if (write_image_data("image_out.bmp", mirror_data, width, height )== 0 ) {
        printf("Erreur d'écriture de l'image.\n");
    }

    free(data);
    free(mirror_data);
}

void mirror_total(char *source_path) {
    unsigned char *data = NULL;
    int width, height, channels;

    if (read_image_data(source_path, &data, &width, &height, &channels) == 0) {
        printf("Erreur de lecture image.\n");
        return;
    }

    unsigned char *mirror_data = malloc(width * height * channels);
    if (!mirror_data) {
        printf("Erreur mémoire.\n");
        free(data);
        return;
    }

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            for (int c = 0; c < channels; ++c) {
                int new_x = width - 1 - x;
                int new_y = height - 1 - y;

                mirror_data[(new_y * width + new_x) * channels + c] =
                    data[(y * width + x) * channels + c];
            }
        }
    }

    if (write_image_data("image_out.bmp", mirror_data, width, height) == 0) {
        printf("Erreur d'écriture de l'image.\n");
    }

    free(data);
    free(mirror_data);
}
