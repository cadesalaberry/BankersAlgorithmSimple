#define NB_TYPES_RES 4

int rdm_nbr_between(const int min, const int max) {

	return min + ( rand() % (max-min+1) );
}

typedef struct {
	
	int total_res[NB_TYPES_RES];
	int stock[NB_TYPES_RES];
	int safe_state[NB_TYPES_RES];

} banker;

typedef struct {
	
	int max_res[NB_TYPES_RES];
	int stock[NB_TYPES_RES];
	int request[NB_TYPES_RES];
	int granted[NB_TYPES_RES];

} customer;

/**
 * Prints what the customers holds and needs
 */
void report_customer(const customer cust) {

int res;
	for (res = 0; res < NB_TYPES_RES; res++) {

		printf("\t%d?%d/%d", cust.request[res], cust.stock[res], cust.max_res[res]);
	}
	printf("\n");
}
/**
 * Prints what the customers holds and needs
 */
void report_customers(const customer * custs, const int nb_custs) {
	
	int id;
	
	printf("Customers\tA\tB\tC\tD\n");
	
	for (id = 0; id < nb_custs; id++)	{
		
		printf("#%d\t", id);
		report_customer(custs[id]);
	}
}

/**
 * Gives random values to the number of ressources
 * for every customers.
 */
void rdm_customer_res(customer * custs, const int nb_custs) {

	int i, j;
	for (i = 0; i < nb_custs; i++) {
		for (j = 0; j < NB_TYPES_RES; j++) { 
			custs[i].max_res[j] = rdm_nbr_between(5,12);
			custs[i].stock[j] = 0;
			custs[i].request[j] = 0;
		}
	}
}

/**
 * Gives random values to the next request of
 * every customers.
 */
void rdm_customer_req(customer * cust) {

	int res_id;

	for (res_id = 0; res_id < NB_TYPES_RES; res_id++) { 
		cust->request[res_id] = rdm_nbr_between(0,5);
	}
}

/**
 * Prints what the banker holds and the max value computed
 */
void report_banker(const banker bkr) {
	
	int res;
	
	printf("Banker\nFree:\t");
	
	for (res = 0; res < NB_TYPES_RES; res++) {
	
		printf("\t%d", bkr.total_res[res]);
	}
	printf("\nTotal:\t");
	
	for (res = 0; res < NB_TYPES_RES; res++) {
	
		printf("\t%d", bkr.stock[res]);
	}
	printf("\n");
}

void find_ideal_res_for_banker(const customer * custs, const int nb_custs, banker * bkr){

	int id, res;

	// Computes the available number of ressources
	for (res = 0; res < NB_TYPES_RES; res++) {
		bkr->total_res[res] = 0;

		// Computes the total number for each ressources
		for (id = 0; id < nb_custs; id++) {
			bkr->total_res[res] += custs[id].max_res[res];
		}
		
		// Multiplies total by 0.6 and round DOWN to find the ideal value.
		bkr->stock[res] = (5*bkr->total_res[res]/ 3);
	}
}

int update_safe_states(const customer * custs, const int nb_custs, banker * bkr) {

	int remaining, id, res;

	bkr->safe_state[0] = custs[0].max_res[0] - custs[0].stock[0];
	
	for (res = 0; res < NB_TYPES_RES; res++) {
		for (id = 0; id < nb_custs; id++) {
			
			remaining = custs[id].max_res[res] - custs[id].stock[res];
			
			if (bkr->safe_state[res] < remaining) {
				bkr->safe_state[0] = remaining;
			}
		}
	}



	return 1;
}

int banker_grant_req(customer cust, const int res_id, banker bkr) {


	return 1;
}

void process_transfer(customer * cust, const res_id, banker * bkr) {

	bkr->stock[res_id] -= cust->request[res_id];
	cust->stock[res_id] += cust->request[res_id];
	cust->request[res_id] = 0;
}