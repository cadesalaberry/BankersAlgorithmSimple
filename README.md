
#Resource Manager with Banker’s Algorithm
-----------------------------------------


Banker’s algorithm was invented by Dijkstra in 1965. It is based on a money lending problem faced by small-town bankers. Suppose a small-town banker has three customers Paul, Martin, and Cathy.

Paul, Martin, and Cathy have declared that they would need a maximum of 10K, 8K, and 9K dollars, respectively. The banker knows that they are not likely require the maximums at the same time. So, instead of reserving 27K he reserves 18K (an estimated number so he can minimize his borrowing costs). The banker’s customers request loans in small amounts (1K or 2K).

However, the banker is obliged to satisfy requests up to the agreed maximum. That is, Paul can borrow a sum up to 10K. If his requests (sum of all requests or a single request) exceeds 10K, the un-conforming requests will be rejected by the banker.

Consider a situation where Paul, Martin, and Cathy have already borrowed 5K, 3K, and 7K, respectively. The banker has 3K left in the reserve. The banker is in safe state because he can satisfy the requests
at this point. One way of satisfying the customers is to give 2K to Cathy and let her complete her project. We assume that once the maximum funding is given the customers are going to complete their activities and release the resource (money in the case of the banker).

When Cathy releases the funding, the banker will have 10K and he can the other customers’ requests in any given order. So the state is indeed safe.
Now, suppose Martin asks for 2K. The banker would make some tentative calculations to determine whether it is safe to lend the money or not. Suppose he lends the money his reserve would reduce to 1K. After lending, Paul, Martin, and Cathy would hold 5K, 5K, and 7K, respectively. He needs at least 2K
to completely satisfy Cathy (he needs more to satisfy other’s requirements).
Therefore, the banker is in a unsafe state if he lends the 2K requested by Martin. He could lend 1K instead and still remain safe. The above description uses a single type of resource.

We can trivially generalize this algorithm to a computer resource allocation problem with different types of resources. The class notes and the textbook give a general version of the algorithm.


##What Do You Need To Do?

Learn the Banker’s algorithm.

Consider a resource allocation problem with N processes and 4 resource types, where N is randomly picked between 5 and 10. At the beginning, each process declares the number of each resource types it needs. That is, each process declares its maximum resource requirement, which is a number generated between 5 and 12. Once you have all the maximum resource requirements, the available number of resources for each type is generated by summing the requirements and multiplying the sum by 0.6. Any fractions are rounded up to create the initial reserves for each resource type.


Now, the processes issue requests and the resource manager evaluates them. A request could be rejected because it invalid (that is the process is requesting more than the max) or it is unsafe to allocate the request. A simulation run stops when the resource manager has rejected requests from all the processes. That is the resource manager has reached the maximum safe state allocation and is unable to accommodate any more requests without going into unsafe state.


At this point, the resource manager will printout the allocation matrix and terminate the simulation.

