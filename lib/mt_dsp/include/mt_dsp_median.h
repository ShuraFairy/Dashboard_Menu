#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>

typedef struct {
    uint16_t* window_buffer;
    uint16_t window_size;
} mt_dsp_median_u16_t;

typedef struct {
    float* window_buffer;
    uint16_t window_size;
} mt_dsp_median_f32_t;

void mt_dsp_median_u16_init(mt_dsp_median_u16_t* filter);
uint16_t mt_dsp_median_u16_calc(mt_dsp_median_u16_t* filter, uint16_t input);
void mt_dsp_median_f32_init(mt_dsp_median_f32_t* filter);
float mt_dsp_median_f32_calc(mt_dsp_median_f32_t* filter, float input);

#ifdef __cplusplus
}
#endif
