#include "elev.h"
#include "functions.h"
#include <stdio.h>

  
int main() {
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    set_defined_state();
    int order_control= 0;
    while (1) {
	  if(elev_get_floor_sensor_signal()!=-1)
        elev_set_floor_indicator(elev_get_floor_sensor_signal());
      if(elev_get_stop_signal())
        stop_sequence();
      if((elev_get_floor_sensor_signal() == 3)){
        set_direction(-1);
        order_control = 1;
      }
      if (elev_get_floor_sensor_signal() == 0){
          set_direction(1);
          order_control = 0;
	  }
      for(int i = 0; i<4; i++){
        for(int j = 0; j<3; j++){
            if(elev_get_button_signal(j, i)){
                register_order(i,j);
            }
        }
      }  
     handle_orders_inside();
      }
    return 0;
}

//        io_write_analog(MOTOR,2800);