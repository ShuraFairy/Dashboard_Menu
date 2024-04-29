#include "mt_dsp_median.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int compare_u16(const void* a, const void* b);
static int compare_f32(const void* a, const void* b);

void mt_dsp_median_u16_init(mt_dsp_median_u16_t* filter)
{
    if (filter) {
        memset(filter->window_buffer, 0, sizeof(uint16_t) * filter->window_size);
    }
}

uint16_t mt_dsp_median_u16_calc(mt_dsp_median_u16_t* filter, uint16_t input)
{
    uint16_t result = 0;
    if (filter) {
        if (filter->window_buffer) {
            uint16_t filtered_value = 0;
            uint16_t temp_window[filter->window_size];

            memcpy(temp_window, filter->window_buffer + 1, (filter->window_size - 1) * sizeof(uint16_t));
            temp_window[filter->window_size - 1] = input;
            memcpy(filter->window_buffer, temp_window, filter->window_size * sizeof(uint16_t));

            qsort(temp_window, filter->window_size, sizeof(uint16_t), compare_u16);
            filtered_value = temp_window[filter->window_size / 2];

            result = filtered_value;
        }
    }
    return result;
}

void mt_dsp_median_f32_init(mt_dsp_median_f32_t* filter)
{
    if (filter) {
        memset(filter->window_buffer, 0, sizeof(float) * filter->window_size);
    }
}

float mt_dsp_median_f32_calc(mt_dsp_median_f32_t* filter, float input)
{
    float result = 0;
    if (filter) {
        if (filter->window_buffer) {
            float filtered_value = 0;
            float temp_window[filter->window_size];

            memcpy(temp_window, filter->window_buffer + 1, (filter->window_size - 1) * sizeof(float));
            temp_window[filter->window_size - 1] = input;
            memcpy(filter->window_buffer, temp_window, filter->window_size * sizeof(float));

            qsort(temp_window, filter->window_size, sizeof(float), compare_f32);
            filtered_value = temp_window[filter->window_size / 2];

            result = filtered_value;
        }
    }
    return result;
}

static int compare_u16(const void* a, const void* b)
{
    uint16_t fA = *((uint16_t*)a);
    uint16_t fB = *((uint16_t*)b);

    if (fA == fB)
        return 0;
    else if (fA < fB)
        return -1;
    else
        return 1;
}

static int compare_f32(const void* a, const void* b)
{
    uint16_t fA = *((uint16_t*)a);
    uint16_t fB = *((uint16_t*)b);

    if (fA == fB)
        return 0;
    else if (fA < fB)
        return -1;
    else
        return 1;
}
