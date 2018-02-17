#include "io.h"
#include "elev.h"
#include "functions.h"
#include "channels.h"
#include <stdio.h>
#include <time.h>
void set_delay_Then_close(int s){
	time_t start,end;
	int t = 0;
	start=clock();//predefined  function in c
	while(t<s){
		end=clock();
		t = (end-start)/CLOCKS_PER_SEC;
	}
	elev_set_door_open_lamp(0);
	set_defined_state();
}
void set_Curr_Floor_Light_Indicator(){
	switch(elev_get_floor_sensor_signal()){ //logic for which floorlamp should be set
		case 0: elev_set_floor_indicator(0); 
		break;
		case 1: elev_set_floor_indicator(1); 
		break;
		case 2: elev_set_floor_indicator(2); 
		break;
		case 3: elev_set_floor_indicator(3); 
		break;
	}
}
void set_defined_state(){
	int state = elev_get_floor_sensor_signal(); // checks if in defined state or not
	while(state==-1){ // if not in defined state run until elevator is in defined state
		elev_set_motor_direction(DIRN_UP);
		state = elev_get_floor_sensor_signal(); // constantly checks if elevator has reached a floor
		if(state !=-1){
			printf("stopp\n");
			elev_set_motor_direction(0); //stops motor when reached defined state
			break;
		}
	}
	elev_set_motor_direction(DIRN_STOP);
}
void stop_button(){
			reset_orders();
			elev_set_motor_direction(0);// stops elevator //resets all orderlights
			if(elev_get_floor_sensor_signal()!=-1) // opens door if stop on floor
			if(elev_get_floor_sensor_signal()!=-1) // opens door if stop on floor
				 elev_set_door_open_lamp(1);
			while(1)
				if(!elev_get_stop_signal()){
					printf("%d\n", *check);
					set_delay_Then_close(3);
					break;
				} // if stop released waits for 3 seconds then starts again
}
void delete_orders_on_current_floor(){
	if(elev_get_floor_sensor_signal()!=-1)
	for(int i = 0; i<3; i++)
		elev_set_button_lamp(i, elev_get_floor_sensor_signal(), 0);
}