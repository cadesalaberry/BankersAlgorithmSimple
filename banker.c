#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "banker.h"

int id, res_id;

int main(int argc, char **argv)
{
	// Initiates random seed
	srand(time(NULL));
	
	// Gives our banker a badass name
	// (http://en.wikipedia.org/wiki/Jerome_Kerviel)
	banker jerome;

	// Randomizes the number of customers
	int nb_customers = rdm_nbr_between(MIN_NB_CUST,MAX_NB_CUST);
	customer customers[nb_customers];
	
	rdm_customer_res(customers, nb_customers);
	
	// Determines how much the banker should have available
	find_ideal_res_for_banker(customers, nb_customers, &jerome);
	
	// Resets the number of times the banker has refused a ressource
	reset_deny_count(&jerome);

	/**USE THIS LINE TO SEE FIRST STATE**/
	// Prints a report of the customers, and the banker
	//report_customers(customers, nb_customers);
	//report_banker(jerome);

	// Notice that it is also used as a counter
	int safe_state = 1;

	while(safe_state) {
		
		int id, res_id;

		// Generates a request matrix
		rdm_customers_req(customers, nb_customers);

		// Resets the number of times the banker has refused a ressource
		reset_deny_count(&jerome);
	
		// Treats the customers requests one by one
		for (id = 0; id < nb_customers && safe_state; id++) {

			// After every customer deal, the safe state changes
			update_safe_states(customers, nb_customers, &jerome);

			// Iterates over all ressources
			for (res_id = 0; res_id < RES_TYPE; res_id++) {
				
				// Checks if a request is valid
				if (!banker_grant_req(customers[id], res_id, jerome)){

					// Records that the ressource has been denied
					jerome.deny_count[res_id]++;

					// Checks that the ressource has not been refused to
					// all the customers
					if (jerome.deny_count[res_id] >= nb_customers) {

						printf("Simulation did %d transactions", safe_state-1);
						printf(" before reaching an unsafe state.\n\n");
						safe_state = 0;
						break;
					}
					

				} else {

					// Transfer the ressource to the customer
					process_transfer(&customers[id], res_id, &jerome);
					
					// Increments the number of successfull transfers
					safe_state++;
				}

				if (safe_state > NB_MAX_OF_SIMULATIONS) {

					printf("\nSimulation did %d transactions", safe_state-1);
					printf(" without encountering any unsafe state.\n");
					safe_state = 0;
					break;
				}
			}
		}
	}

	// Prints a final report of the customers, and the banker
	report_customers(customers, nb_customers);
	report_banker(jerome);

	return 0;
}