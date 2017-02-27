#include <time.h>
#include <stdio.h>
#include "Eventmanager.h"
#include "Elevmodule.h"
#include "Timer.h"
#include "Queue.h"

int ev_emergency_button_pushed(){
    return elev_get_stop_signal();
}

int ev_time_door_out(){
    return timer_3sec();
}


/*
int ev_check_buttons(){ 
    return nOrders;
}


int ev_order_same_floor(){
    for(int i=0; i<nOrders; i++){
        if(orders[i].floor==elev_get_floor_sensor_signal()){
            if(orders[i].direction==0||orders[i].direction==direction()){
                return 1;
            }
        }
    } 

    return 0;
}

int direction(){
    if(queue_next_order().floor>elev_get_floor_sensor_signal()){
        return 1;
    }

    if(queue_next_order().floor<elev_get_floor_sensor_signal()){
        return -1;
    }   
    return 0;
}

*/

