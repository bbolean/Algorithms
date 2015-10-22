// problem link: http://codeforces.com/contest/584/problem/D

/* 
    
                                                D. Dima and Lisa
                                            time limit per test1 second
                                            memory limit per test256 megabytes
                                            inputstandard input
                                            outputstandard output
    Dima loves representing an odd number as the sum of multiple primes, and Lisa loves it when there are at most three primes. Help 
    them to represent the given number as the sum of at most than three primes.

    More formally, you are given an odd numer n. Find a set of numbers pi (1 ≤ i ≤ k), such that  1 ≤ k ≤ 3 pi is a prime

    The numbers pi do not necessarily have to be distinct. It is guaranteed that at least one possible solution exists.

    Input
    The single line contains an odd number n (3 ≤ n < 1000 000 000).

    Output
    In the first line print k (1 ≤ k ≤ 3), showing how many numbers are in the representation you found.

    In the second line print numbers pi in any order. If there are multiple possible solutions, you can print any of them.

    Sample test(s)
    input
    27

    output
    3
    5 11 11

    Note
    A prime is an integer strictly larger than one that is divisible only by one and by itself.
    
*/

// Solution

/* 
    To begin with, from Goldbach's conjecture we know that every even number can be represented as a sum of two prime numbers. Actually 
    this is not proven yet, (but there was some very significant progress achieved by Lev Schnirelmann in 1930 and then by russian
    mathematician Vinogradov) but for even numbers in range from 1 to 10^9, we can assume this conjecture works fine.

        So lets get back to our problem. We have number n, and its odd. We know that every even number less than n, can be represented as
    sum of two prime numbers, so if we take largest prime number p, which is less then or equal to n (p <= n), then p >= 3 and hence 
    p is odd, so if we subtract it from n, we will get even number which we already know can be represented as a sum of two prime numbers.
    So every odd number n can be represented as a sum of three prime numbers. The problem here is to find p because p <= n and hence 
    p is in range 3 <= p <= 10^9, so if we iterate through every number from 3 to n, we will need to check hudge number of p-s and it will
    be much time consuming. But here is the key trick. We need to remind theory about maximal length of gaps between consecutive primes, 
    which promisses that maximum gap between n and p will be roughly speaking not greater than 300. This means if we take n, then n-1, and
    so on, after at most 300 iteration we will have p. So once we have p, we subtract it from n and get n = n - p, and here n is less then
    300. Now all that remains is, to find two primes a and b such that a + b = n. As far as n is very small number at this moment, we can 
    iterate through numbers from 2 to n / 2 by a, and check whether a and (n - a) are both primes, if they are both primes, then we have
    the solution.

        There is some corner cases when n is itself prime or when we subtract p from n we will get 2, we will handle both cases in our code
    bellow.
    
    Wikipedia:
        https://en.wikipedia.org/wiki/Goldbach%27s_conjecture
        https://en.wikipedia.org/wiki/Lev_Schnirelmann
        https://en.wikipedia.org/wiki/Vinogradov%27s_theorem
        https://en.wikipedia.org/wiki/Prime_gap
*/

// Implementation

/* 
    At first we need some precalculation to make it easy and fast to detect whether number p is prime or not. For this reason we will
    use Sieve of Eratosthenes to keep all prime numbers from 2 to sqr(n). As n can be 10^9 we will need to keep boolean for 
    sqrt(1000000000) which is approximately 32 000 numbers. 

    Wikipedia:
        https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
    http://www.algolist.net/Algorithms/Number_theoretic/Sieve_of_Eratosthenes
*/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


// for each index indx, we keep false if indx is prime, and true
// if indx is not prime
vector<bool> isprime(32000);
vector<int> primes;     // list of prime numbers in range from 2 to 32 000

// checks if number k is prime by iterating all prime numbers in
// vector primes, and checking if one of them divides k
bool checkprime(int k){
    for(int i = 0; primes[i] * primes[i] <= k; i++){
        if(k % primes[i] == 0) return false;
    }
    return true;
}


int main() {

    // algorithm according to sieve of Eratosthenes for finding
    // prime numbers
    for(int i = 2; i < 32000; i++){
        if(!isprime[i]){
            for(int k = 2; i * k < 32000; k++){
                isprime[i*k] = true;
            }
            primes.push_back(i);
        }
    }

    // here we start executing our program, we read input data
    int n;
    cin >> n;

    // corner case: 1
    // if n is prime then it can be represented as a sum of one
    // prime number, itself
    if(checkprime(n)){
        cout << 1 << endl << n;
        return 0;
    }

    // corner case: 2
    // if n - 2 is prime then n can be represented as a sum of two
    // prime number, n - 2 and 2
    if(checkprime(n-2)){
        cout << 2 << endl;
        cout << 2 << " " << n - 2;
        return 0;
    }

    // here we definitely know n should be represented as a sum
    // of three prime numbers
	cout << 3 << endl;

    // find p, print it and subtract it from n
    for(int i = n; i >= 2; i--){
        if(checkprime(i)){
            cout << i << " ";
			n -= i;
			break;
        }
    }
	
    // find a and b, and print it
	for(int i = 2; i <= n / 2; i++){
		if(checkprime(i) && checkprime(n-i)){
			cout << i << " " << n - i;
			break;
		}
	}

    return 0;
}