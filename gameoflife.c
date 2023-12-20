#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "lib/constants.h"
#include "lib/field/field.h"
#include "lib/shlib/shlib.h"
#include "lib/vec2/vec2.h"

// Main
int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: ./main [time_interval (ms)] [amount_of_bacteria (<=%d)]", WIDTH * HEIGHT);
        return -1;
    }
    int time_interval = atoi(argv[1]);
    int amount_of_bacteria = atoi(argv[2]);

    field_t field = field_init();
    new_bacteria_n(&field, amount_of_bacteria);

    while (field.current_generation < GENERATIONS)
    {
        system("clear");
        printf("Generation: %d\n\n", field.current_generation);
        DBG_print_field_content(field);
        update(&field);
        msleep(time_interval);
    }

    field_free(field);
    return 0;
}
