We want to construct some function for calculation th probability by which we ask the employee to make an evaluation. 
The first basic idea is to use time decay factor which means evaluations made 10 days ago should be less significant than evaluations made
two days ago.So suppose we have time decay factor f, where f is some real number and f is in the boundaries [0, 1] inclusively.
So suppose for an employee we have number of evaluations he made, suppose these numbers are a1, a2, a3, ... , ak. Then one way to calculate the probability can be something like this: p = a1*f + a2*f^2 + a3*f^3 + ... + ak*f^k. But this value can easily be more than 1, 
so f sont be in the range [0,1]. So this try has failed. 
Another way can be something like this: f/a1 + f^2/a2 + f^3/a3 + ... + f^k/ak. But this method won't work also, because there will be some case where for each i, 1 <= i <= k, ai = 1 and then there can be the case where this sum is more than 1. 
The third way is 1 / (a1*f + a2*f^2 + a3*f^3 + ... + ak*f^k). But even this can be more than 1. But lets do some trick here, namely, add 1 
to the denominator. In this way we will have 1 / (1 + a1*f + a2*f^2 + a3*f^3 + ... + ak*f^k) 
In this method we can get any number as close to zero as we want, and the same goes for 1 too. 
So we calculate this value, and take it as a probability, by which we send him an email or not. But how to decide what should f be. We have some cases to consider here. Let's consider cases were we only have two users, this pair cases will cover the whole behavior for many many users. So let's say one of them has evaluations for 4 days as [1 0 2] and the second _ [0 3 0]. Now we may decide that first should
receive an email by a higher probability, so 1 / (1 + f + 2*f^3) > 1 / (1 + 3*f^2) and hence 2*f^2 - 3*f + 1 < 0 which is true when 
0.5 < f < 1. If we say, that the second should receive an email by a higher probability, then we'll get 0 < f < 0.5. So that's why we need to specify some base cases.
