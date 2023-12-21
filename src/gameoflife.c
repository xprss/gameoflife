#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "include/constants.h"
#include "include/field.h"
#include "include/shlib.h"
#include "include/vec2.h"

// Main
int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: ./main [time_interval (ms)] [amount_of_bacteria (<=%d)]\n", MAX_BACTERIAS);
        return -1;
    }

    int time_interval = atoi(argv[1]);
    int amount_of_bacteria = atoi(argv[2]);
    field_t field = field_init();
    new_bacteria_n(&field, amount_of_bacteria);

    if(time_interval < 0) {
        printf("The time interval must be a positive number.\n");
        return -2;
    }

    if(amount_of_bacteria > MAX_BACTERIAS) {
        printf("The amout of bacterias must be less or equal than %d.\n", MAX_BACTERIAS);
        return -3;
    }

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
