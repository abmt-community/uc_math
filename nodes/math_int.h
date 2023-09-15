/**
 * Author: Hendrik van Arragon, 2023
 * SPDX-License-Identifier: MIT
 */

#ifndef UC_MATH_MATH_INT_H
#define UC_MATH_MATH_INT_H UC_MATH_MATH_INT_H

#include <cstdint>
#include <abmt/time.h>

namespace uc_math{

//@node: auto
struct counter_int{
    int32_t param_start = 0;
    int32_t param_end   = 1;
    int32_t param_step  = 1;
    bool   param_auto_restart = true;
    
    int32_t out;
    
    int32_t num_steps = 0;
    int32_t steps = 0;

    void init();
    void tick();
};

//@node: auto
struct integrate_int{
    int32_t out;
    int32_t in = 0;
    bool   in_reset = false;
    int32_t param_initial_value = 0;
    int32_t param_min = -727379967;
    int32_t param_max =  727379967;
    abmt::time raster_interval;
    int32_t interval_sec;
    
    void init();
    void tick();
};

//@node: auto
struct derive_int{
    int32_t out;
    int32_t in;
    int32_t last_in;
    abmt::time raster_interval;
    int32_t samples_per_sec;
    
    void init();
    void tick();
};

// you may want to use two pt1 behind each other
//@node:auto
class pt2_int{
public:
	int32_t out;
	int64_t mem1;
	int64_t mem2;
	int32_t in = 0;
	int32_t d_1k;
	int64_t T_inv;
	int64_t TT_inv;
	int32_t ticks_per_sec = 100;
	float param_t = 0.1;
    float param_d = 1.0;
    abmt::time raster_interval;

    void init();
    void tick();
};

//@node:auto
class pt1_int{
public:
	int32_t out;
	int32_t in;
	int32_t param_Tms = 1000;
	int32_t param_initial_value;
	
	int64_t mem;
	int32_t dt_divT;
	abmt::time raster_interval;

    void init();
    void tick();
};

//@node: auto
struct limit_int{
    int32_t out;
    int32_t in = 0;

    int32_t param_min = 0;
    int32_t param_max = 1;
    
    void tick();
};

//@node: auto
struct ma_filter_int{
    int32_t out;
    int32_t in = 0;
    size_t param_size = 16;
    bool   param_init_with_first_input = true;
    int32_t param_initial_value = 0;
    
    int32_t sum = 0;
    size_t pos = 0;
    
    int32_t* data;
    
    void init();
    void tick();
    void final();
};

//@node: auto
struct min_int{
    int32_t out;
    int32_t in = 0;
    bool   in_reset = false;
    void init();
    void tick();
};

//@node: auto
struct max_int{
    int32_t out;
    int32_t in = 0;
    bool in_reset = false;
    void init();
    void tick();
};


} // namespace uc_math

#endif // UC_MATH_MATH_INT_H
