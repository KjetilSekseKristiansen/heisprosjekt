#include <io.h>
#include <elev.h>
#include <functions.h>
void set_Delay_Then_close(int s){
	time_t start,end;
	int t;
	start=clock();//predefined  function in c
	while(t<s){
		end=clock();
		t = (end-start)/CLOCKS_PER_SEC;
	}
	elev_set_door_open_lamp(0);
}

void set_Direction_on_end(){
	if (elev_get_floor_sensor_signal() == 3)
        elev_set_motor_direction(DIRN_DOWN);
    else if (elev_get_floor_sensor_signal() == 0)
        elev_set_motor_direction(DIRN_UP);
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
void set_order_light(){
	int isPressed;
	for(int i = 0; i<4; i++)
		for(int j = 0; j<3; j++){
		 isPressed = elev_get_button_signal(button_channel_matrix[i][j], i); //loops through all buttons
		 if(isPressed = 1)
		 elev_set_button_lamp(button_channel_matrix[i][j], i, 1); 	// if press detected sets the corresponding lamp
		}
}
void set_defined_state(){
	int state = elev_get_floor_sensor_signal(); // checks if in defined state or not
	while(state==-1){ // if not in defined state run until elevator is in defined state
		elev_set_motor_direction(DIRN_UP);
		state = elev_get_floor_sensor_signal(); // constantly checks if elevator has reached a floor
		if(state !=-1){
			elev_set_motor_direction(0); //stops motor when reached defined state
			break;
		}
		}
	}
	elev_set_motor_direction(DIRN_STOP);
}
void clear_order_light(int floor){
		elev_set_button_lamp(button_channel_matrix[floor][0], floor, 0); // clears the uplamp for the current floor 
		elev_set_button_lamp(button_channel_matrix[floor][1], floor, 0)  //clears the downlamp...
}
void stop_button(int status){
		if(status){
			elev_set_motor_direction(0); // stops elevator
			clearOrders(); //removes all orders
			for(int i = 0; i<4; i++)
				clear_order_light(i); //resets all orderlights
			if(elev_get_floor_sensor_signal()!=-1) // opens door if stop on floor
				 elev_set_door_open_lamp(1);
			while(1)
				if(!elev_get_stop_signal())
					goto BEGIN;
				; // if stop released waits for 3 seconds then starts again
		}
		BEGIN: set_Delay_Then_close(3);
}
void set_orders_up(){
	for( int i = 0; i<3; i++){
		if(lamp_channel_matrix[i][1] ==1)
			order_matrix[i][1] = 1; // registers order for up by modifying order_matrix
	}
	return orderUpIndex;
}
void set_orders_down(){
	for( int i = 1; i<4; i++){
		if(lamp_channel_matrix[i][2] ==1)
			order_matrix[i][0] = 1; // Registers order for down by modifying order_matrix
	}
	return orderDownIndex;
}
void clear_orders(){
	for(int i = 0; i<4; i++)
		for(int j = 0; j<2; j++)
		order_matrix[i][j] = 0;
}

