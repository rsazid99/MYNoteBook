string s;
int n;
int SA[maxn], tmpSA[maxn], RA[maxn], tmpRA[maxn], mp[maxn], cnt[maxn];


void counting_sort(int k)
{
        memset(cnt, 0, sizeof cnt);
        int mx = max(n, 300);

        for(int i = 0; i < n; i ++){
                cnt[i + k < n ? RA[i + k] : 0] ++;
        }

        int sum = 0;
        for(int i = 0; i < mx; i ++){
                int tmp = cnt[i];
                cnt[i] = sum;
                sum += tmp;
        }


        for(int i = 0; i < n; i ++){
                tmpSA[cnt[SA[i] + k < n ? RA[SA[i] + k] : 0] ++ ] = SA[i];
        }

        for(int i = 0; i < n; i ++) SA[i] = tmpSA[i];

}

void suffix_array()
{
        for(int i = 0; i < n; i ++) RA[i] = s[i], SA[i] = i;

        for(int k = 1; k < n; k <<= 1){
                counting_sort(k);
                counting_sort(0);

                tmpRA[SA[0]] = 0;
                int r = 0;

                for(int i = 1; i < n;i ++){
                        tmpRA[SA[i]] = (RA[SA[i]] == RA[SA[i - 1]] && (SA[i] + k < n ? RA[SA[i] + k] : 0) == (SA[i - 1] + k ? RA[SA[i - 1] + k] : 0)) ? r : ++ r;
                }

                for(int i = 0; i < n; i ++) RA[i] = tmpRA[i];
                if(RA[SA[n - 1]] == n - 1) break;
        }
}

