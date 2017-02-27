#include "Elevmodule.h"
#include "Timer.h"
#include "Eventmanager.h"
#include "Queue.h"
#include "Statemachine.h"
#include <stdio.h>

enum state{
    IDLE=0,
    RUN = 1,
    EMERGENCY_STOP = 2,
    DOOR_OPEN = 3,
} state, nextstate;

static void elevator_initialize() {
    while(elev_get_floor_sensor_signal() == -1) {
        elev_set_motor_direction(DIRN_UP);
    }
    elev_set_motor_direction(DIRN_STOP);
}

void fsm_EMERGENCY_STOP() {
    elev_set_stop_lamp(1); 
    elev_set_motor_direction(DIRN_STOP); 
}

void fsm_IDLE() {
    elev_set_motor_direction(DIRN_STOP); 
    if(elev_get_floor_sensor_signal() != -1){ //stopp i etasje
        //elev_set_button_lamp(knappesignal, elev_get_floor_sensor_signal(), 0); //HVORDAN VET VI HVILKEN KNAPP
        elev_set_floor_indicator(elev_get_floor_sensor_signal());
    }
}

void fsm_RUN() {
    //queue_add_order();
    //queue_next_order(); //henter neste ordre som skal utf�res 
    elev_set_button_lamp(BUTTON_CALL_DOWN, 3, 1); //HVORDAN VET VI HVILKEN KNAPP - HAR MED KØSYSTEMET Å GJØRE, STRUCT 
    //elev_set_motor_direction(direction()); 
}

void fsm_DOOR_OPEN() {
    elev_set_door_open_lamp(1);
    timer_start(); 
    //queue_delete_order(); 
    if (ev_time_door_out()) {
        elev_set_door_open_lamp(0);
    }
}


int main() {
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    printf("Press STOP button to stop elevator and exit program.\n");

    elevator_initialize(); //Initialiserer heisen (kjører opp til nærmeste etasje hvis den ikke allerede står i etasje)
    elev_set_motor_direction(DIRN_UP);

    state=IDLE;
    nextstate=0;
    
   
    while (1) {
        // Change direction when we reach top/bottom floor
        if (elev_get_floor_sensor_signal() == N_FLOORS - 1) {
            elev_set_motor_direction(DIRN_DOWN);
        } else if (elev_get_floor_sensor_signal() == 0) {
            elev_set_motor_direction(DIRN_UP);
        }
        
        /*  ødelegger emergency_stop, knappen lyser ikke
        // Stop elevator and exit program if the stop button is pressed
        if (elev_get_stop_signal()) {
            elev_set_motor_direction(DIRN_STOP);
            break;
        }
        */ 
       
        switch(state){
                    case IDLE:
                        if(ev_emergency_button_pushed()==1){
                            nextstate = EMERGENCY_STOP;
                        }
                        /*
                        if(ev_order_same_floor() == 1){
                            nextstate = DOOR_OPEN;
                        }
                        if(ev_check_button()==1){
                            nextstate = RUN;
                        }
                        */
                        break;
                    case EMERGENCY_STOP:
                        if(ev_emergency_button_pushed()==1){
                            nextstate = EMERGENCY_STOP;
                        }
                        if(ev_emergency_button_pushed()==0){
                            if(elev_get_floor_sensor_signal() != -1){ //er i en etasje
                                //queue_delete_all_orders();
                                elev_set_stop_lamp(0);
                                elev_set_floor_indicator(elev_get_floor_sensor_signal()); //kanskje denne må inn i ev_door_open()
                                nextstate = DOOR_OPEN;
                            }
                            else{
                                //queue_delete_all_orders();
                                elev_set_stop_lamp(0);
                                nextstate = IDLE; 
                            }
                        }
                        break;
                    case RUN:
                        /*
                        if(ev_order_same_floor() == 0){
                            nextstate = RUN;
                        }
                        if(ev_order_same_floor() == 1){
                            nextstate = IDLE;
                        }
                        */
                        if(ev_emergency_button_pushed() == 1){
                            nextstate = EMERGENCY_STOP;
                        }
                        break;
                    case DOOR_OPEN:
                        if(ev_time_door_out()==0){
                            nextstate = DOOR_OPEN;
                        }
                        else{
                            nextstate = IDLE;
                        }
                        break;
                    default:
                        break;
        }

        if(state != nextstate){
            switch(nextstate){
                case IDLE:
                    fsm_IDLE();
                    break;
                case EMERGENCY_STOP:
                    fsm_EMERGENCY_STOP();
                    break;
                case RUN:
                    fsm_RUN();
                    break;
                case DOOR_OPEN:
                    fsm_DOOR_OPEN();
                    break;
                default:
                    break;
            }
        }
        
        state = nextstate;
        
    }

    return 0;
}
