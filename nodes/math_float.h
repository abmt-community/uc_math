/**
 * Author: Hendrik van Arragon, 2023
 * SPDX-License-Identifier: MIT
 */

#ifndef UC_MATH_MATH_FLOAT_H
#define UC_MATH_MATH_FLOAT_H UC_MATH_MATH_FLOAT_H

#include <abmt/time.h>

namespace uc_math{
    
//@node: auto
struct counter_float{
    float param_start = 0;
    float param_end   = 1;
    float param_step  = 0.01;
    bool   param_auto_restart = true;
    
    float out;
    
    unsigned int num_steps = 0;
    unsigned int steps = 0;

    void init();
    void tick();
};
    
//@node: auto
struct integrate_float{
    float out;
    float in = 0;
    bool   in_reset = false;
    float param_initial_value = 0;
    float param_min = -1000000000000;
    float param_max =  1000000000000;
    abmt::time raster_interval;
    float interval_sec;
    
    void init();
    void tick();
};

//@node: auto
struct derive_float{
    float out;
    float in;
    float last_in;
    abmt::time raster_interval;
    float samples_per_sec;
    
    void init();
    void tick();
};

//@node: auto
struct pt1_float{
    float out;
    float in = 0;
    float param_t = 1;
    bool   param_init_with_first_input = true;
    float param_initial_value = 0;
    abmt::time raster_interval;
    float factor;
    
    void init();
    void tick();
};

//@node: auto
struct pt2_float{
    float out;
    float out_derivative;
    float in = 0;
    float param_t  = 1;
    float param_d  = 1;
    bool   param_init_with_first_input = true;
    float param_initial_value = 0;
    float param_initial_value_derivative = 0;
    float T_inv;
    float TT_inv;
    abmt::time raster_interval;
    float interval_sec;
    
    void init();
    void tick();
};

//@node: auto
struct limit_float{
    float out;
    float in = 0;

    float param_min = 0;
    float param_max = 1;
    
    void tick();
};


//@node: auto
struct ma_filter_float{
    float out;
    float in = 0;
    size_t param_size = 10;
    bool   param_init_with_first_input = true;
    float param_initial_value = 0;
    
    size_t pos = 0;
    
    float* data;
    
    void init();
    void tick();
    void final();
};

//@node: auto
struct dt_float{
    float out_dt;
    float param_first_dt = 0.01;
    abmt::time last_call; 
    
    void init();
    void tick();
};


//@node: auto
struct min_float{
    float out;
    float in = 0;
    bool   in_reset = false;
    void init();
    void tick();
};

//@node: auto
struct max_float{
    float out;
    float in = 0;
    bool in_reset = false;
    void init();
    void tick();
};

//@node: auto
struct interpolate_float{
    float out;
    float in = 0;
    float param_in_min = 0;
    float param_in_max = 1;
    float param_out_min = 0;
    float param_out_max = 1;
    void tick();
};

} // namespace uc_math

#endif // UC_MATH_MATH_FLOAT_H
