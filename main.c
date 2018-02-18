#include "elev.h"
#include "functions.h"
#include <stdio.h>

  
int main() {
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    int check = 0;
    elev_set_motor_direction(0);
    while (1) {
      if (check == 0){
        set_defined_state();
        check = 1;
    }
	  if(elev_get_floor_sensor_signal()!=-1)
        set_Curr_Floor_Light_Indicator();
      if(elev_get_stop_signal())
        stop_button();
      if((elev_get_floor_sensor_signal() == 3))
        elev_set_motor_direction(DIRN_DOWN);
      if (elev_get_floor_sensor_signal() == 0){
         elev_set_motor_direction(DIRN_UP);
	  }
      for(int i = 0; i<4; i++){
        for(int j = 0; j<3; j++){
            if(elev_get_button_signal(j, i)){
                register_order(i,j);
            }
        }
      }        
    }
    return 0;
}

io_write_analog(MOTOR, 2800);