#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

#define ll long long

int is_prime[1000010];
vector<ll> divisor[1000010];
ll low, high;

ll div_ceil(ll a, ll b)
{
        return (a + b - 1) / b;
}

void segmented_sieve()
{
        for(int i = 2; i <= 1000000; i ++){
                if(!is_prime[i]){
                        for(int j = i + i; j <= 1000000; j += i) is_prime[j] = 1;

                        for(ll j = div_ceil(low, i) * (ll)i ; j <= high; j += i){
                                divisor[j - low].push_back(i);
                        }
                }
        }
}

int main()
{
        cin >> low >> high;
        segmented_sieve();

        return 0;
}
