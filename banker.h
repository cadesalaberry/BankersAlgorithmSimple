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

void report_customers(customer * custs, int nb_custs) {
	
	int id, res;
	
	printf("Customers\tA\tB\tC\tD\n");
	
	for (id = 0; id < nb_custs; id++)	{
		
		printf("#%d\t", id);
		for (res = 0; res < NB_TYPES_RES; res++)	{
		
			printf("\t%d", custs[id].max_res[res]);
		}
		printf("\n");
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
