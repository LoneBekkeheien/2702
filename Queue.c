#include "Queue.h"
#include "Elevmodule.h"

/*
void queue_add_order(){ 
	for(int i=0; i<N_FLOORS; i++) {
		if(elev_get_button_signal(BUTTON_COMMAND,i)==1){
			nOrders+=1;
			orders[nOrders].floor=i;
			orders[nOrders].direction=0;
			}
		if(elev_get_button_signal(BUTTON_CALL_UP,i)==1){
			nOrders+=1;
			orders[nOrders].floor=i;
			orders[nOrders].direction=1;	
			}

		if(elev_get_button_signal(BUTTON_CALL_DOWN,i)==1){		
			nOrders+=1;
			orders[nOrders].floor=i;
			orders[nOrders].direction=-1; 
			}
	}
}

void queue_delete_all_orders(){
	for(int i=0; i<nOrders; i++){
		orders[i].floor=2+3*(N_FLOORS-1);
		orders[i].direction=2+3*(N_FLOORS-1);
	}
	nOrders=0;	
}

void queue_delete_order(){
	for(int i=0; i<1+3*(N_FLOORS-1); i++){
		if(elev_get_floor_sensor_signal()==orders[i].floor){
			orders[i].floor=2+3*(N_FLOORS-1);
			orders[i].direction=2+3*(N_FLOORS-1);
			nOrders-=1;	
		}
	}
}

order queue_next_order(){
	return orders[0];	
}

*/