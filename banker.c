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
	
	int i, j;
	
	// Randomizes the number of customers
	int nb_customers = rdm_nbr_between(5,10);
	customer customers[nb_customers];
	
	rdm_customer_res(customers, nb_customers);
	
	// Prints a report of the customers
	report_customers(customers, nb_customers);
	
	
	// Computes the available number of ressources 
	for (j = 0; j < NB_TYPES_RES; j++) {
		jerome.total_res[j] = 0;
		for (i = 0; i < nb_customers; i++) {
			jerome.total_res[j] += customers[i].max_res[j];
		}
		
		// Multiplies total by 0.6 and round up.
		jerome.free_res[j] = 1 + (5*jerome.total_res[j]/ 3);
	}

	// Prints a report of the banker
	report_banker(jerome);
	return 0;
}



