// problem
// link : http://codeforces.com/gym/100739/problem/F

/*								 F. What were those numbers?
								time limit per test0.25 seconds
								memory limit per test64 megabytes
								inputstandard input
								outputstandard output
 Informikas likes to play a simple game with his friends. First he takes a list of numbers from 1 to N. Later he takes some of 
 those numbers and calculates the average of them. When done, Informikas writes down number N and the average value as a fraction 
 P / Q on a piece of paper.

	The next part of the game is easy one. Informikas puts the piece of paper with values N and P / Q in a drawer and doesn't look at 
 it for a couple of days. During this time he usually eats three times a day, solves couple or more programming problems and does 
 other things.

Then there comes the tricky part. After some time, when Informikas is completely sure that he has no memory of the first step of 
the game, he takes out the piece of paper, looks at the values of N and P / Q and tries to come up with numbers from interval [1;N] 
so that the average of those numbers would be equal to P / Q. However, he many times fails figuring out those numbers and he ends up 
wondering if he might have made a mistake in the first step and there are no solutions at all.

Informikas would like to have a program which would find the solution in case he is not able to do that himself. Could you help him?

Input
The first line of input consist of three integer values N, P and Q (1 ≤ N ≤ 105, 1 ≤ P ≤ 1010, 1 ≤ Q ≤ 105). It is guaranteed that 
the fraction can't be simplified (i.e. the greatest common divisor GCD(P, Q) = 1).

Output
Output either a set of integers from the range [1;N] having an average value of P / Q or write "IMPOSSIBLE" if there is no way to 
make this kind of set. If there are multiple solutions, output any of them.

Sample test(s)
input
1 1 1
output
1 
input
2 3 2
output
1 2 
input
3 7 3
output
IMPOSSIBLE
 
*/

/* 
 * to have average P / Q, we should at least select Q numbers from 1 to n. These numbers at least will be 1,2,3,...,Q. so P is not less
 * than Q*(Q+1)/2, and also, numbers at most will be n-Q+1,n-Q+2,...,n-1,n (Q of them in the whole). then P is not greater then
 * (n - Q + 1) * Q + Q*(Q-1) / 2. If any of these two constraint is violated, then answer will be impossible. If not, then we can take
 * first Q numbers: 1,2,3,...Q and increase each of them one-by-one untill we get P as their sum. This procedure always will reach
 * sum to P
 * */
#include <iostream>
#include <stdio.h>
#include <vector>
#include <set>
#include <math.h>
#include <algorithm>

using namespace std;

typedef long long ll;

// comparation functions for 64 bit integers
ll MIN(ll a, ll b){
	if(a < b) return a;
	return b;
}

ll MAX(ll a, ll b){
	if(a > b) return a;
	return b;
}
  
int main(){
  
	ll n,p,q;
	cin >> n >> p >> q;
	
	// check two constraints
	if(p < q*(q+1) / 2 || p > q*(n-q + 1) + q*(q-1)/2) {
		cout << "IMPOSSIBLE";
		return 0;
	}
	
	// put first least Q numbers in vector
	vector<ll> rest;	
	for(int i = 0; i < q; i++){
		rest.push_back(n - i);
	}
	
	reverse(rest.begin(),rest.end());
	
	ll sum = (n - q + 1) * q + q * (q - 1) / 2;
	// increase them one-by-one
	for(ll i = 0; i < q; i++){
		ll diff = sum - p;
		if(diff == 0) break;	// if we reached sum to P, we end our calculation
		ll newval = MAX(i+1,rest[i]-diff);
		sum -= rest[i] - newval;
		rest[i] = newval;
	}
    
    // print the result
    for(int i = 0; i < q; i++)
    cout << rest[i] << " " ;
     
    return 0;
}

