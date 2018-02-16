#include "elev.h"
#include "functions.h"
#include <stdio.h>

  
int main() {
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    printf("Press STOP button to stop elevator and exit program.\n");
    int check = 0;
    elev_set_motor_direction(0);
    while (1) {
      if (check == 0){
        printf("setter definert tilstand\n");
        set_defined_state();
        check = 1;
    }

      if(elev_get_floor_sensor_signal()!=-1)
        set_Curr_Floor_Light_Indicator();
      if(elev_get_stop_signal())
        stop_button();
      if((elev_get_floor_sensor_signal() == 3))
        set_direction_down();
      if (elev_get_floor_sensor_signal() == 0)
        set_direction_up();
      for(int i = 0; i<4; i++){
        for(int j = 0; j<3; j++){
            if(elev_get_button_signal(j, i)){
                register_order(i,j);
            }
        }
      } 
      if(elev_get_obstruction_signal())
        set_direction_up();           
    }
    return 0;
}

