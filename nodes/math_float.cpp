/**
 * Author: Hendrik van Arragon, 2023
 * SPDX-License-Identifier: MIT
 */
 
#include "math_float.h"
#include <abmt/os.h>
#include <math.h>

using namespace std;
using namespace uc_math;

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

void counter_float::init(){
	float n_steps = (param_end - param_start )/param_step;
	if(n_steps > 0){
		num_steps = floorf(n_steps);
	}else{
		num_steps = 0;
	}
	steps = 0;
}

void counter_float::tick(){
	out = param_start + steps * param_step;
	steps++;
	if(steps > num_steps){
		if(param_auto_restart){
			steps = 0;
		}else{
			steps = num_steps;
		}
	}
}


void integrate_float::init(){
    out = param_initial_value;
    interval_sec = (raster_interval.ms()/1000.0);
}

void integrate_float::tick(){
    out += interval_sec * in;
    if(out > param_max){
        out = param_max;
    }
    if(out < param_min){
        out = param_min;
    }
    if(in_reset){
        init();
    }
}


void derive_float::init(){
    last_in = in;
    samples_per_sec = 1.0/(raster_interval.ms()/1000.0);
}

void derive_float::tick(){
    out = samples_per_sec * (in - last_in);
    last_in = in;
}


void pt1_float::init(){
    if(param_init_with_first_input){
        out = in;
    }else{
        out = param_initial_value;
    }
    factor = (raster_interval.ms()/1000.0)/param_t;
}

void pt1_float::tick(){
    out = out + factor * (in - out);
}


void pt2_float::init(){
    float T = 1.0/2.0/M_PI*param_t;
    T_inv    = 1.0/T;
    TT_inv   = 1.0/(T*T);
    if(param_init_with_first_input){
        out = in;
    }else{
        out = param_initial_value;
    }
    out_derivative = param_initial_value_derivative;
    interval_sec = (raster_interval.ms()/1000.0);
}

void pt2_float::tick(){
    out_derivative = out_derivative + interval_sec * (in*TT_inv - out*TT_inv - out_derivative*2*param_d*T_inv);
    out += interval_sec * out_derivative;
}


void limit_float::tick(){
    out = in;
    if(out > param_max){
        out = param_max;
    }
    if(out < param_min){
        out = param_min;
    }
}


void ma_filter_float::init(){
    data = new float[param_size];
    float init_val = param_initial_value;
    if(param_init_with_first_input){
        init_val = in;
    }
    for(int i = 0; i < param_size; ++i){
        data[i] = init_val/param_size;
    }
    pos = 0;
    out = init_val;
}

void ma_filter_float::tick(){
    out -= data[pos];
    data[pos] = in/param_size;
    out += data[pos];
    ++pos;
    if(pos >= param_size){
        pos = 0;
    }
}

void ma_filter_float::final(){
    delete[] data;
}


void dt_float::init(){
    last_call = abmt::time::now() - abmt::time::ns(param_first_dt * 1000.0*1000.0*1000.0);
}

void dt_float::tick(){
    auto now   = abmt::time::now();
    auto delta = now - last_call;
    out_dt     = delta.sec2();
    last_call  = now;
}

void min_float::init(){
    out =std::numeric_limits<float>::max();
}

void min_float::tick(){
    if(in < out){
        out = in;
    }
    if(in_reset){
        out = in;
    }
}

void max_float::init(){
    out = std::numeric_limits<float>::lowest();
}

void max_float::tick(){
    if(in > out){
        out = in;
    }
    if(in_reset){
        out = in;
    }
}

void interpolate_float::tick(){
    if(in > param_in_max){
        in = param_in_max;
    }
    if(in < param_in_min){
        in = param_in_min;
    }
    float out_delta = param_out_max - param_out_min;
    float in_delta = param_in_max - param_in_min;
    out = param_out_min + (in-param_in_min)/(in_delta) * out_delta;
}