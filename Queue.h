#include "Elevmodule.h"

/*
typedef struct order {
	int floor;
	int direction;
} order;

order orders[1+3*(N_FLOORS-1)]; 
int nOrders = 0;

/* SKAL INN I FUNKSJON I MAIN
for(int i=0; i<1+3*(N_FLOORS-1); i++){
	orders[i].floor=2+3*(N_FLOORS-1);
	orders[i].direction=2+3*(N_FLOORS-1);	
}
*/

void queue_add_order();

void queue_delete_all_orders();

void queue_delete_order();

//order queue_next_order();
