#ifndef __FIELD_H__
#define __FIELD_H__
#include <stdlib.h>
#include <stdio.h>
#include "../vec2/vec2.h"
#include "../constants.h"
#include "../shlib/shlib.h"

typedef struct field_s
{
    int *occupations;
    int *next_occupations;
    int current_generation;
} field_t;

void DBG_print_field_content(field_t);
field_t field_init();
void add_bacteria(field_t *, vec2);
void kill_bacteria(field_t *, vec2);
vec2 get_free_position(field_t);
int is_bacteria(field_t, vec2);
int is_village(field_t, vec2);
void new_bacteria(field_t *);
void update(field_t *);
int surrounders(field_t, vec2);
void field_free(field_t);
void new_bacteria_n(field_t *, int);
void copy_field(field_t *);
int get_cell_type(field_t, int);

#endif
