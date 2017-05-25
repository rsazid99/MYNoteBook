#include <iostream>
#include <cmath>
using namespace std;

int prime[300000], nprime = 0, mark[1000010];

void sieve(int n)
{
        int limit = sqrt(n * 1.00) + 2;


        mark[1] = 1;
        for(int i = 4; i <= n; i += 2) mark[i] = 1;

        prime[nprime ++] = 2;

        for(int i = 3; i <= n; i += 2){
                if(!mark[i]){
                        prime[nprime ++] = i;

                        if(i <= limit){
                                for(int j = i * i; j <= n; j += i * 2) mark[j] = 1;
                        }
                }
        }
}

int main()
{
        sieve(1000000);

        return 0;
}
