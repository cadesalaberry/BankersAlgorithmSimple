#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "banker.h"

int main(int argc, char **argv)
{
	// Initiates random seed
	srand(time(NULL));
	
	// Gives our banker a badass name
	// (http://en.wikipedia.org/wiki/Jerome_Kerviel)
	banker jerome;

	// Randomizes the number of customers
	int nb_customers = rdm_nbr_between(5,10);
	customer customers[nb_customers];
	
	rdm_customer_res(customers, nb_customers);
	
	// Prints a report of the customers
	report_customers(customers, nb_customers);

	// Determines how much the banker should have available
	find_ideal_res_for_banker(customers, nb_customers, &jerome);


	report_banker(jerome);

	int safe_state = 1;
	while(safe_state) {
		
		int id;
		for (id = 0; id < nb_customers; id++) {
			rdm_customer_req(&customers[id]);
			
			if (banker_grant_req(customers[id], nb_customers, jerome)) {
				//customers[id].stock[]
			}
		}

		
		if (safe_state > 3){
			printf("Simulation ran %d times ", safe_state-1);
			printf("before reaching an unsafe state.\n");
			safe_state = 0;
			break;
		}
		safe_state++;
	}
	report_customers(customers, nb_customers);


	return 0;
}