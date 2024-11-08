#pragma once
void motor_controller_init();
void TC0_enable_interrupt();
void motor_controller_set_sp(int8_t sp);
int32_t PID();