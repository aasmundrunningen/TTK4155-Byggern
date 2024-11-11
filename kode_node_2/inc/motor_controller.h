#pragma once
void motor_controller_init();
void TC0_enable_interrupt();
void motor_controller_set_sp(int8_t sp);
void solenoid_controll();
void activate_solenoid();
int32_t PID();