/**
 * You can play around with the following values.
 * 
 * RES_TYPE represents the number of type of ressources.
 *
 * NB_MAX_OF_SIMULATIONS is self explainatory.
 * 
 * MIN_NB_CUST - MAX_NB_CUST are the minimum and maximum
 * number of customers to create for the simulation.
 *
 * MIN_RES_LIM - MAX_RES_LIM are the minimum and maximum
 * number of ressources that a customer can ask to be available
 * at the bank initially.
 * 
 * The requests made by the customers will be chosen between 
 * MIN_REQUEST and MAX_REQUEST.
 */
#define RES_TYPE 4

#define NB_MAX_OF_SIMULATIONS 202

#define MAX_NB_CUST 12
#define MIN_NB_CUST 5

#define MAX_RES_LIM 12
#define MIN_RES_LIM 5

#define MAX_REQUEST 5
#define MIN_REQUEST 0

int id;
int res;
int res_id;

int rdm_nbr_between(const int min, const int max) {

	return min + ( rand() % (max-min+1) );
}

typedef struct {
	
	int total_res[RES_TYPE];
	int stock[RES_TYPE];
	int safe_state[RES_TYPE];
	int deny_count[RES_TYPE];

} banker;

typedef struct {
	
	int max_res[RES_TYPE];
	int stock[RES_TYPE];
	int request[RES_TYPE];

} customer;

/**
 * Prints what the customers holds and needs
 */
void report_customer(const customer cust) {

	for (res = 0; res < RES_TYPE; res++) {

		printf("\t%d?%d/%d", cust.request[res], cust.stock[res], cust.max_res[res]);
	}
	printf("\n");
}
/**
 * Prints what the customers holds and needs
 */
void report_customers(const customer * custs, const int nb_custs) {
	
	printf("Customers");
	
	for (res_id = 0; res_id < RES_TYPE; res_id++)	{
		
		printf("\tres%d", res_id);
	}
	printf("\n");

	for (id = 0; id < nb_custs; id++)	{
		
		printf("#%d\t", id);
		report_customer(custs[id]);
	}
}

/**
 * Gives random values to the number of ressources
 * for every customers and sets their stocks,
 * and requests to zero.
 */
void rdm_customer_res(customer * custs, const int nb_custs) {

	for (id = 0; id < nb_custs; id++) {
		for (res_id = 0; res_id < RES_TYPE; res_id++) { 
			custs[id].max_res[res_id] = rdm_nbr_between(MIN_NB_CUST,MAX_NB_CUST);
			custs[id].stock[res_id] = 0;
			custs[id].request[res_id] = 0;
		}
	}
}

/**
 * Gives random values to the next request of
 * every customers.
 */
void rdm_customer_req(customer * cust) {

	for (res_id = 0; res_id < RES_TYPE; res_id++) { 

		cust->request[res_id] = rdm_nbr_between(MIN_REQUEST,MAX_REQUEST);
	}
	
}
/**
 * Gives random values to the next request of
 * every customers.
 */
void rdm_customers_req(customer * custs, const int nb_custs) {

	for (id = 0; id < nb_custs; id++) {

		rdm_customer_req(&custs[id]);
	}
}

/**
 * Prints what the banker holds and the max value computed
 */
void report_banker(const banker bkr) {
	
	printf("Banker\nStock:\t");
	
		for (res = 0; res < RES_TYPE; res++) {
	
		printf("\t%d", bkr.stock[res]);
	}

	printf("\nTotal:\t");
	
	for (res = 0; res < RES_TYPE; res++) {
	
		printf("\t%d", bkr.total_res[res]);
	}

	printf("\nSafe:\t");
	
	for (res = 0; res < RES_TYPE; res++) {
	
		printf("\t%d", bkr.safe_state[res]);
	}

	printf("\nDeny:\t");
	
	for (res = 0; res < RES_TYPE; res++) {
	
		printf("\t%d", bkr.deny_count[res]);
	}
	printf("\n");
}

void find_ideal_res_for_banker(const customer * custs, const int nb_custs, banker * bkr){

	// Computes the available number of ressources
	for (res = 0; res < RES_TYPE; res++) {
		bkr->total_res[res] = 0;

		// Computes the total number for each ressources
		for (id = 0; id < nb_custs; id++) {
			bkr->total_res[res] += custs[id].max_res[res];
		}
		
		// Multiplies total by 0.6 and round DOWN to find the ideal value.
		bkr->stock[res] = (3*bkr->total_res[res]/ 5);
		bkr->safe_state[res] = -1;
	}
}

/**
 * Find the minimum number of ressources needed for one of the customer
 * to complete his project (and thus give back his ressources)
 */
void update_safe_states(const customer * custs, const int nb_custs, banker * bkr) {

	int remaining;
	
	// Iterates over all ressources
	for (res = 0; res < RES_TYPE; res++) {

		bkr->safe_state[res] = bkr->total_res[res];

		// Looks for the min needed to finish a project
		for (id = 0; id < nb_custs; id++) {
			
			remaining = custs[id].max_res[res] - custs[id].stock[res];
			
			// Checks that the stock can still be useful to somebody else
			if (bkr->safe_state[res] > remaining) {
				
				// Checks that the customer does not go past limit
				if (remaining < 0) {
				
					remaining = 0;	
				}

				bkr->safe_state[res] = remaining;
			}
		}
	}
}

int banker_grant_req(customer cust, const int res_id, banker bkr) {

	// Computes what would be the value of the stocks after
	int bank_aftr = bkr.stock[res_id] - cust.request[res_id];
	int cust_aftr = cust.stock[res_id] + cust.request[res_id];

	// Checks that the customer does not ask past limit
	if (cust_aftr <= cust.max_res[res_id]) {

		// Checks that the request is consistent with the stock
		if (bank_aftr >=0) {
		
			if (bank_aftr >= bkr.safe_state[res_id]) {
				
				return 1;
			}//else {printf("Banks becomes lower than safe_state.\n");}
		}//else {printf("Bank becomes negative.\n");}
	}//else {printf("Customer asked over limit.\n");}
	return 0;
}

void process_transfer(customer * cust, const int res_id, banker * bkr) {

	//printf("res #%d: [init=%d] ", res_id, bkr->stock[res_id]);
	//printf("- %d = ", cust->request[res_id]);
	
	bkr->stock[res_id] -= cust->request[res_id];
	cust->stock[res_id] += cust->request[res_id];
	cust->request[res_id] = 0;

	//printf("%d\n", bkr->stock[res_id]);

	if (cust->stock[res_id] >= cust->max_res[res_id]) {
		bkr->stock[res_id] += cust->stock[res_id];
		cust->stock[res_id] = 0;
	}
}

void reset_deny_count(banker * bkr) {

	for (res_id = 0; res_id < RES_TYPE; res_id++) {
		bkr->deny_count[res_id] = 0;
	}
}