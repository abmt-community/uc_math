/**
 * Author: Hendrik van Arragon, 2023
 * SPDX-License-Identifier: MIT
 */

#include "math_int.h"

using namespace std;
using namespace uc_math;

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

void counter_int::init(){
	num_steps = (param_end - param_start )/param_step;
	steps = 0;
}

void counter_int::tick(){
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


void integrate_int::init(){
    out = param_initial_value;
    interval_sec = (raster_interval.ms()/1000.0);
}

void integrate_int::tick(){
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


void derive_int::init(){
    last_in = in;
    samples_per_sec = 1.0/(raster_interval.ms()/1000.0);
}

void derive_int::tick(){
    out = samples_per_sec * (in - last_in);
    last_in = in;
}

void pt2_int::init(){
    ticks_per_sec = 1000/raster_interval.ms();
	d_1k = param_d*1024;
    float T  = 1.0/2.0/M_PI*param_t;
    T_inv    = 1.0/T + 0.5;
    TT_inv   = 1.0/(T*T) + 0.5;
    mem2 = 0;
    mem1 = in*16*ticks_per_sec;
}

void pt2_int::tick(){
    mem2 += (in*16*TT_inv - mem1*TT_inv/ticks_per_sec - mem2*2*d_1k*T_inv/1024)/ticks_per_sec;
    mem1 += mem2;
    out = mem1/16/ticks_per_sec;
}

void pt1_int::init(){
    out = param_initial_value;
    mem = out * 1024;
    dt_divT = raster_interval.ms()*1024/param_Tms;
}

void pt1_int::tick(){
    mem = mem + (dt_divT * (in - out));
    out = mem / 1024;
}

void limit_int::tick(){
    out = in;
    if(out > param_max){
        out = param_max;
    }
    if(out < param_min){
        out = param_min;
    }
}


void ma_filter_int::init(){
    data = new int32_t[param_size];
    int32_t init_val = param_initial_value;
    if(param_init_with_first_input){
        init_val = in;
    }
    for(int i = 0; i < param_size; ++i){
        data[i] = init_val/param_size;
    }
    pos = 0;
    sum = init_val*param_size;
    out = sum/param_size;
}

void ma_filter_int::tick(){
    sum -= data[pos];
    data[pos] = in;
    sum += data[pos];
    out = sum/param_size;
    ++pos;
    if(pos >= param_size){
        pos = 0;
    }
}

void ma_filter_int::final(){
    delete[] data;
}

void min_int::init(){
    out =std::numeric_limits<int32_t>::max();
}

void min_int::tick(){
    if(in < out){
        out = in;
    }
    if(in_reset){
        out = in;
    }
}

void max_int::init(){
    out = std::numeric_limits<int32_t>::lowest();
}

void max_int::tick(){
    if(in > out){
        out = in;
    }
    if(in_reset){
        out = in;
    }
}
