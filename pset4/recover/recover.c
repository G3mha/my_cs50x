#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    // Checking if there are only 2 parameters passed
    if (argc != 2)
    {
        printf("Usage: ./recover image\n"); // Showing the correct format for the input
        return 1; // Ending the program with great style
    }

    // Checking if the file opens
    FILE *raw = fopen(argv[1], "r");
    if (raw == NULL)
    {
        printf("File could not be opened.\n"); // Printing the error
        return 1; // Ending the program with great style
    }

    // Allocating the memory needed for the initialized var
    uint8_t buffer[512];

    // Getting the name of the file
    char name[8];
    FILE *img;
    int n = 0; // setting the counting var

    // Determining the 1st JPEG and, then, all the adjacent
    while (fread(buffer, 512, 1, raw) == 1)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // Closing the previous image, except the 1st JPEG.
            if (n > 0)
            {
                fclose(img);
            }
            sprintf(name, "%03i.jpg", n++);
            img = fopen(name, "w");
            fwrite(buffer, 512, 1, img);
        }
        else if (n > 0)
        {
            fwrite(buffer, 512, 1, img);
        }
    }
}
