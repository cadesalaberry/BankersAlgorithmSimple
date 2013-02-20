#define NB_TYPES_RES 4

int rdm_nbr_between(const int min, const int max) {

	return min + ( rand() % (max-min+1) );
}

typedef struct {
	
	int total_res[NB_TYPES_RES];
	int free_res[NB_TYPES_RES];

} banker;

typedef struct {
	
	int max_res[NB_TYPES_RES];
	int cur_res[NB_TYPES_RES];

} customer;
/**
 * Gives random values to the number of ressources
 * for every customers.
 */
void rdm_customer_res(customer * custs, int nb_custs) {

	int i, j;
	for (i = 0; i < nb_custs; i++) {
		for (j = 0; j < NB_TYPES_RES; j++) { 
			custs[i].max_res[j] = rdm_nbr_between(5,12);
			custs[i].cur_res[j] = 0;
		}
	}
}

/**
 * Prints what the customers holds and needs
 */
void report_customers(customer * custs, int nb_custs) {
	
	int id, res;
	
	printf("Customers\tA\tB\tC\tD\n");
	
	for (id = 0; id < nb_custs; id++)	{
		
		printf("#%d\t", id);
		for (res = 0; res < NB_TYPES_RES; res++)	{
		
			printf("\t%d/%d", custs[id].cur_res[res], custs[id].max_res[res]);
		}
		printf("\n");
	}
}

void find_ideal_res_for_banker(customer * custs, int nb_custs, banker bkr){

	int id, res;

	// Computes the available number of ressources
	for (res = 0; res < NB_TYPES_RES; res++) {
		bkr.total_res[res] = 0;

		// Computes the total number for each ressources
		for (id = 0; id < nb_custs; id++) {
			bkr.total_res[res] += custs[id].max_res[res];
		}
		
		// Multiplies total by 0.6 and round DOWN to find the ideal value.
		bkr.free_res[res] = 1 + (5*bkr.total_res[res]/ 3);
	}
}

void report_banker(banker the_banker) {
	
	int res;
	
	printf("Banker\nFree:\t");
	
	for (res = 0; res < NB_TYPES_RES; res++)	{
	
		printf("\t%d", the_banker.total_res[res]);
	}
	printf("\nTotal:\t");
	
	for (res = 0; res < NB_TYPES_RES; res++)	{
	
		printf("\t%d", the_banker.free_res[res]);
	}
	printf("\n");
}
