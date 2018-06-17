#ifndef __FUNCTION_H
#define __FUNCTION_H
#include "sys.h"



void Display(void) ;

double   Through_distance( int pulseamount_Left, int pulseamount_Right) ;



double gain_speed( int second,double distance );

void  sound_light_alarm(int coin)  ;

void  search_path1(int sign_left1,int sign_left2,int sign_right1,int sign_right2);

void  search_path2(int sign_left1,int sign_left2,int sign_right1,int sign_right2);

void gain_sign();


#endif