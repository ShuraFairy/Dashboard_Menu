#include "mt_dsp_mavg.h"
#include <string.h>

void mt_dsp_mavg_u16_init(mt_dsp_mavg_u16_t* filter)
{
    if (filter) {
        memset(filter->window_buffer, 0, sizeof(uint16_t) * filter->window_size);
    }
}

uint16_t mt_dsp_mavg_u16_calc(mt_dsp_mavg_u16_t* filter, uint16_t input)
{
    uint32_t sum = 0;

    if (filter) {
        uint16_t temp_window[filter->window_size];

        memcpy(temp_window, filter->window_buffer + 1, (filter->window_size - 1) * sizeof(uint16_t));
        temp_window[filter->window_size - 1] = input;
        memcpy(filter->window_buffer, temp_window, filter->window_size * sizeof(uint16_t));

        for (uint16_t i = 0; i < filter->window_size; i++) {
            sum += (uint32_t)filter->window_buffer[i];
        }
    }

    return (uint16_t)(sum / filter->window_size);
}

void mt_dsp_mavg_f32_init(mt_dsp_mavg_f32_t* filter)
{
    if (filter) {
        memset(filter->window_buffer, 0, sizeof(uint16_t) * filter->window_size);
    }
}

float mt_dsp_mavg_f32_calc(mt_dsp_mavg_f32_t* filter, float input)
{
    float sum = 0;

    if (filter) {
        float temp_window[filter->window_size];

        memcpy(temp_window, filter->window_buffer + 1, (filter->window_size - 1) * sizeof(float));
        temp_window[filter->window_size - 1] = input;
        memcpy(filter->window_buffer, temp_window, filter->window_size * sizeof(float));

        for (uint16_t i = 0; i < filter->window_size; i++) {
            sum += filter->window_buffer[i];
        }
    }

    return (float)(sum / filter->window_size);
}
