#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#define WIDTH 50
#define HEIGHT 35
#define GENERATIONS 1000

#define VILLAGE_VERSION 0

#define EMPTY 0
#define BACTERIA 1

#if VILLAGE_VERSION
#define VILLAGE 2
#endif

// Data structures
typedef struct
{
    int x;
    int y;
} vec2;

typedef struct field_s
{
    int *occupations;
    int *next_occupations;
    int current_generation;
} field_t;

// Prototypes
void DBG_print_field_content(field_t);
int rnd(int, int);
field_t field_init();
void add_bacteria(field_t *, vec2);
void kill_bacteria(field_t *, vec2);
vec2 get_free_position(field_t);
vec2 i2v2(int, int);
int v22i(vec2, int);
vec2 rnd_vec2(int, int);
int is_bacteria(field_t, vec2);
int is_village(field_t, vec2);
void new_bacteria(field_t *);
void update(field_t *);
int clamp(int, int, int);
int surrounders(int *, vec2);
void field_free(field_t);
void new_bacteria_n(field_t *, int);
void copy_field(field_t *);
int msleep(long);
int get_cell_type(field_t, int);

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
        field.current_generation++;
        msleep(time_interval);
    }

    field_free(field);
    return 0;
}

// Implementations
int clamp(int min, int val, int max)
{
    if (val < min)
        return min;
    if (val > max)
        return max;
    return val;
}

void update(field_t *field)
{
    int i;
    int bacteria_neighboors;
    printf("\n");
    for (i = 0; i < WIDTH * HEIGHT; i++)
    {
#if VILLAGE_VERSION
        if (is_village(*field, i2v2(i, WIDTH)))
        {
            continue;
        }

#endif
        bacteria_neighboors = surrounders(field->occupations, i2v2(i, WIDTH));

        switch (bacteria_neighboors)
        {
        case 0:
        case 1:
            if (is_bacteria(*field, i2v2(i, WIDTH)))
            {
                field->next_occupations[i] = EMPTY;
            }
            break;
        case 2:
        case 3:
            if ((is_bacteria(*field, i2v2(i, WIDTH))) || (!is_bacteria(*field, i2v2(i, WIDTH)) && bacteria_neighboors == 3))
            {
                field->next_occupations[i] = BACTERIA;
            }
            break;
#if VILLAGE_VERSION
        case 7:
        case 8:
            if (!is_bacteria(*field, i2v2(i, WIDTH)))
            {
                field->next_occupations[i] = VILLAGE;
            }
            break;
#endif
        default:
            if (is_bacteria(*field, i2v2(i, WIDTH)))
            {
                field->next_occupations[i] = EMPTY;
            }
            break;
        }
    }
    copy_field(field);
}

void copy_field(field_t *field)
{
    int i;
    for (i = 0; i < HEIGHT * WIDTH; i++)
    {
        field->occupations[i] = field->next_occupations[i];
    }
}

int surrounders(int *occ, vec2 pos)
{
    int surrounders = 0;
    int i, j;
    vec2 _pos = pos;
    for (i = -1; i < 2; i++)
    {
        for (j = -1; j < 2; j++)
        {
            if (i == 0 && j == 0)
            {
                continue;
            }
            _pos.x = pos.x + i;
            _pos.y = pos.y + j;

            if (_pos.x < 0 || _pos.y < 0 || _pos.x >= HEIGHT || _pos.y >= WIDTH)
            {
                continue;
            }

            surrounders += occ[v22i(_pos, WIDTH)] == BACTERIA ? BACTERIA : EMPTY;
        }
    }
    return surrounders;
}

void new_bacteria_n(field_t *field, int num)
{
    for (; num > 0; num--)
    {
        new_bacteria(field);
    }
}

void new_bacteria(field_t *field)
{
    vec2 new_pos = get_free_position(*field);
    add_bacteria(field, new_pos);
}

int rnd(int min, int max)
{
    return (int)rand() % (max - min) + min;
}

field_t field_init()
{
    int i, j = 0;
    field_t f;
    f.occupations = (int *)malloc(WIDTH * HEIGHT * sizeof(int));
    f.next_occupations = (int *)malloc(WIDTH * HEIGHT * sizeof(int));
    f.current_generation = 0;
    if (f.occupations == NULL || f.next_occupations == NULL)
    {
        printf("ERROR: Memory allocation failed");
        exit(1);
    }
    for (i = 0; i < WIDTH * HEIGHT; i++)
    {
        f.occupations[i] = EMPTY;
        f.next_occupations[i] = EMPTY;
    }
    return f;
}

void field_free(field_t field)
{
    free(field.occupations);
    free(field.next_occupations);
}

void add_bacteria(field_t *field, vec2 bac_position)
{
    field->occupations[v22i(bac_position, WIDTH)] = BACTERIA;
}

void kill_bacteria(field_t *field, vec2 bac_position)
{
    field->occupations[v22i(bac_position, WIDTH)] = EMPTY;
}

vec2 get_free_position(field_t field)
{
    while (1)
    {
        vec2 new_position = rnd_vec2(WIDTH, HEIGHT);
        if (is_bacteria(field, new_position))
        {
            continue;
        }
        return new_position;
    }
}

vec2 i2v2(int i, int C)
{
    vec2 v2;
    v2.x = (int)i / C;
    v2.y = i % C;
    return v2;
}

int v22i(vec2 v, int C)
{
    return v.x * C + v.y;
}

vec2 rnd_vec2(int width, int height)
{
    vec2 v;
    v.x = rnd(0, height);
    v.y = rnd(0, width);
    return v;
}

int is_bacteria(field_t field, vec2 pos)
{
    return field.occupations[v22i(pos, WIDTH)] == BACTERIA;
}

#if VILLAGE_VERSION
int is_village(field_t field, vec2 pos)
{
    return field.occupations[v22i(pos, WIDTH)] == VILLAGE;
}
#endif

void DBG_print_field_content(field_t field)
{
    int i;
    vec2 vec2_coord;
    for (i = 0; i < WIDTH * HEIGHT; i++)
    {
        vec2_coord = i2v2(i, WIDTH);
        if (is_bacteria(field, vec2_coord))
        {
            printf("X");
        }
#if VILLAGE_VERSION
        else if (is_village(field, vec2_coord))
        {
            printf("0");
        }
#endif
        else
        {
            printf(" ");
        }
        if (i != 0 && (i + 1) % WIDTH == 0)
        {
            printf("\n");
        }
    }
}

int get_cell_type(field_t field, int i)
{
    return field.occupations[i];
}

int msleep(long msec)
{
    struct timespec ts;
    int res;

    if (msec < 0)
    {
        return -1;
    }

    ts.tv_sec = msec / 1000;
    ts.tv_nsec = (msec % 1000) * 1000000;

    do
    {
        res = nanosleep(&ts, &ts);
    } while (res);

    return res;
}