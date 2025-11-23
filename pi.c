#include <math.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <getopt.h>
#define PI 3.14159

int main(int argc, char *argv[])
{
    static struct option long_options[] = {
        {"width", required_argument, 0, 'x'},
        {"height", required_argument, 0, 'y'},
        {"help", no_argument, 0, 'h'},
        {0, 0, 0, 0} // Sentinel for the end of the array
    };
    int opt_idx = 0;
    FILE *f = fopen("test.ppm", "wb");
    int w = 512, h = 512, c;
    char magic[64];

    while ((c = getopt_long(argc, argv, "x:y:h", long_options, &opt_idx)) != -1)
    {
        switch (c)
        {
        case 'x':
            w = atoi(optarg);
            break;
        case 'y':
            h = atoi(optarg);
            break;
        case 'h':
            printf("help:\nx --width set the PPM output width\ny --height set the PPM output height\n");
            return 0;
        case '?':
            break;
        default:
            abort();
        }
    }

    snprintf(magic, 64, "P6\n%d\n%d\n255\n", w, h);

    fwrite(magic, strlen(magic), sizeof(char), f);
    for (int i = 0; i < h; ++i)
    {
        for (int j = 0; j < w; ++j)
        {
            double si1 = (2 * PI / w) * j;
            double si2 = (8 * PI / w) * j;
            double si3 = (32 * PI / w) * j;
            double sin1 = (h / 3 / 2) * sin(si1) + (h / 6 );
            double sin2 = (h / 3 / 2) * sin(si2) + (h / 6 * 3);
            double sin3 = (h / 3 / 2) * sin(si3) + (h / 6 * 5);
            // printf("sin(%f) * %d + %d = %d\n", si, h / 2, h / 2, (int)s );s
            char buf[3];
            char on1 = (int)sin1 == h - 1 - i ? 255 : 0;
            char on2 = (int)sin2 == h - 1 - i ? 255 : 0;
            char on3 = (int)sin3 == h - 1 - i ? 255 : 0;
            buf[0] = on1;
            buf[1] = on2;
            buf[2] = on3;

            fwrite(&buf, sizeof(buf), sizeof(char), f);
        }
    }
    fclose(f);
    printf("wrote test.ppm\n");
}