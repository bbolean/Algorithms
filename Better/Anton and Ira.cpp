// Problem link :  http://codeforces.com/contest/584/problem/E

/* 
													E. Anton and Ira
												time limit per test1 second
												memory limit per test256 megabytes
												inputstandard input
												outputstandard output
	Anton loves transforming one permutation into another one by swapping elements for money, and Ira doesn't like paying for stupid games. 
Help them obtain the required permutation by paying as little money as possible.

More formally, we have two permutations, p and s of numbers from 1 to n. We can swap pi and pj, by paying |i - j| coins for it. Find and 
print the smallest number of coins required to obtain permutation s from permutation p. Also print the sequence of swap operations at 
which we obtain a solution.

Input
	The first line contains a single number n (1 ≤ n ≤ 2000) — the length of the permutations.

	The second line contains a sequence of n numbers from 1 to n — permutation p. Each number from 1 to n occurs exactly once in this line.

	The third line contains a sequence of n numbers from 1 to n — permutation s. Each number from 1 to n occurs once in this line.

Output
	In the first line print the minimum number of coins that you need to spend to transform permutation p into permutation s.

	In the second line print number k (0 ≤ k ≤ 2·106) — the number of operations needed to get the solution.

	In the next k lines print the operations. Each line must contain two numbers i and j (1 ≤ i, j ≤ n, i ≠ j), which means that you 
	need to swap pi and pj.

	It is guaranteed that the solution exists.

Sample test(s)
	input
	4
	4 2 1 3
	3 2 4 1
	output
	3
	2
	4 3
	3 1
Note
	In the first sample test we swap numbers on positions 3 and 4 and permutation p becomes 4 2 3 1. We pay |3 - 4| = 1 coins for that. 
On second turn we swap numbers on positions 1 and 3 and get permutation 3241 equal to s. We pay |3 - 1| = 2 coins for that. In total we 
pay three coins.

*/

//	solution


/* 
	
	First, let'c count least number of coin's we will definitely need to get permutation s from permutation p. Suppose we pay doubled number
	of coins for each swap. Then let's look what we will get if we want to swap two numbrs which are on the indexes i1 and i2 (i1 < i2). We
	need to take number on i1 and move it to the right by (i2 - i1) steps. Also we need to move number on index i2 by the same number of
	steps to the left. And we know according to our assumptions that we need to pay 2*(i2-i1) coins for this. Now lets say we need to pay
	(i2-i1) coins to move number from index i1 to index i2, and also the same number of coins is needed to move number from i2 to i1. Then
	This makes our problem simple, since we know that if we want to move any number from index a to index b, we need |a-b| coins to do it.
		
		Now lets say some some number n pi is the index of n in p permutation, and si is index in s permutation. Then we definitely know that
	we need to at least to move number n from pi to si(there may be some other moves needed also, we dont know yet.), and wee need 
	|pi-si| coins for that. Then if we sum up such values for each number from p, we will get least number of coins we will need to move
	each number to its final position. Suppose that value is V. Now lets get back to our swap. When we do swap, we change positions of two
	numbers simultaneously, so instead of spending V coins, we will need V / 2 coins in total at least.
		
		Now we will show, that V / 2 is enough coins to make this movement. We make this proof by showing that we can choose swap operations
	in such a way, that each number moves in the direction of its final destination and when it reaches, it says there forever. Suppose we
	are in a process of making swaps and reached to some permutation p' which is different from s. Suppose ind(a) is final index of a in s.
	Then we can find two indexes i and j in p' (i < j) such that ind(p'[i]) >= j and ind(p'[j]) <= i, that means number p'[i] should be
	to the right of, or euqual to j in s, and number p'[j] should be to the left of, or equal to i. So if we swap these two numbers, what we 
	actually do is to movethose two numbers according to their direction by some steps. So it's then clear that we do nothing that that's 
	needed. The main fact is that, if we are not done yet, we can always find such i and j, and if we are done, then thats clear, that there 
	is no such i and j.

		Now let's prove what we said above. Suppose we have p' which is different from s. Then iterate from left to right in p' and find 
	first number which needs to move left, suppose its ai( i is the index). Then let's start from i and move to the right. Since ai needs
	to move to the left, there is some number to the left of i, which is not on its final index, so which needs to move right(it can move only to
	the right, since ai is the first number which needs to move left). When iterating from i to left, take first such number which needs to
	move, suppose this is bj( j is index). If bj needs to move right, but left to the ai, then there is some number between them which
	also needs to move, but bj is the first number left to the ai, which needs to move. So bj should need to move to ai-s position of right
	to ai. The same goes for ai, and we will get i and j.

		
*/
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <stack>


using namespace std;

typedef long long ll;

int main() {
	

	
	int n;
	cin >> n;

	vector<int> p(n+1);
	vector<int> ind(n+1);

	// keep p
	for(int i = 1; i <= n; i++){
		int a;
		scanf("%d",&a);
		p[i] = a;
	}

	// keep final indexes for each number in ind
	for(int i = 1; i <= n; i++){
		int a;
		scanf("%d",&a);
		ind[a] = i;
	}

	// calculate V, which is doubled total
	// number of coins we need
	int sum = 0;
	for(int i = 1; i <= n; i++){
		sum += abs(i - ind[p[i]]);
	}

	// print V / 2
	cout << sum / 2 << endl;

	 
	// keep result pairs
	vector<pair<int,int> > rest;

	// iterate from left to right in p
	for(int i = 1; i <= n; i++){

		// find such number, which should move left
		if(ind[p[i]] < i){
			// move number to left by swapping.
			// this number may be swapped several times
			int index = i;								// index where number, going to the left will be in p
			for(int j = i - 1; j >= ind[p[index]]; j--){
				if(ind[p[j]] != j){						// find number left to index, which needs to move
					int tmp = p[index];					// swapp numbers
					p[index] = p[j];
					p[j] = tmp;
					rest.push_back(make_pair(index,j));	// keep pairs
					index = j;							// keep new position for left moving number
				}
			}
		}
	}

	// print result
	cout << rest.size() << endl;
	for(int i = 0; i < rest.size(); i++)
		printf("%d %d\n",rest[i].first,rest[i].second);

	return 0;
}