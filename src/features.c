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

/* Milestone 1 */

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

