typedef complex<long double> base;
const long double PI = acos(- 1);
const int mod = 13313;

int cnt[2 * maxn];
set<int> se;
vector<int> v;

void fft (vector<base>& a, bool invert) {
	int n = a.size();

	for(int i = 1, j = 0; i < n ; i ++) {
		int bit = n >> 1;
		for (; j >= bit; bit >>= 1)
			j -= bit;
		j += bit;
		if(i < j)
			swap (a[i], a[j]);
	}

	for(int len = 2; len <= n; len <<= 1) {
		long double ang = 2 * PI / len * (invert ? -1 : 1);
		base wlen (cos(ang), sin(ang));
		for(int i = 0; i < n; i += len) {
			base w (1);
			for(int j = 0; j < len / 2; j ++) {
				base u = a[i + j],  v = a[i + j + len / 2] * w;
				a[i + j] = u + v;
				a[i + j + len / 2] = u - v;
				w *= wlen;
			}
		}
	}
	if(invert)
		for(int i = 0; i < n; i ++)
			a[i] /= n;
}

void multiply(const vector<int>& a, const vector<int>& b, vector<int>& res)
{
        int n = 1;
        while(n <= 2 * max(a.size(), b.size())) n <<= 1;

        vector<base> fa(ALL(a)), fb(ALL(b));
        fa.resize(n);
        fb.resize(n);

        fft(fa, false);
        fft(fb, false);

        FORR(i, 0, n) fa[i] *= fb[i];

        fft(fa, true);

        res.resize(n);
        FORR(i, 0, n){
                res[i] = (ll)(fa[i].real() + 0.5) % mod;
                if(res[i] < 0) res[i] += mod;
        }
}

vector<int> go(int l, int r)
{
        if(l == r){
                vector<int> res;
                res.resize(v[l] + 1);
                FOR(i, 0, v[l]){
                        res[i] = 1;
                }
                return res;
        }
        int mid = (l + r) / 2;
        vector<int> x = go(l, mid), y = go(mid + 1, r), res;
        multiply(x, y, res);
        res.resize(x.size() + y.size() - 1);
        return res;
}


int main() {

        //read();
        //ios_base::sync_with_stdio(false); cin.tie(NULL);cout.tie(NULL);
        //write();
        int n, k, x;

        scanf("%d %d", &n, &k);

        FORR(i, 0, n){
                scanf("%d", &x);
                se.insert(x);
                cnt[x] ++;
        }

        set<int> :: iterator it = se.begin();

        for(; it != se.end(); it ++){
                v.pb(cnt[*it]);
        }

        vector<int> ans = go(0, v.size() - 1);

        printf("%d\n", ans[k]);



	return 0;
}


// another Implementation


int arr[1024], x;
vector<int> v;

void fft (vector<base>& a, bool invert) {
	int n = a.size();

	for(int i = 1, j = 0; i < n ; i ++) {
		int bit = n >> 1;
		for (; j >= bit; bit >>= 1)
			j -= bit;
		j += bit;
		if(i < j)
			swap (a[i], a[j]);
	}

	for(int len = 2; len <= n; len <<= 1) {
		double ang = 2 * PI / len * (invert ? -1 : 1);
		base wlen (cos(ang), sin(ang));
		for(int i = 0; i < n; i += len) {
			base w (1);
			for(int j = 0; j < len / 2; j ++) {
				base u = a[i + j],  v = a[i + j + len / 2] * w;
				a[i + j] = u + v;
				a[i + j + len / 2] = u - v;
				w *= wlen;
			}
		}
	}
	if(invert)
		for(int i = 0; i < n; i ++)
			a[i] /= n;
}

vector<int> multiply(const vector<int>& a, const vector<int>& b)
{
        int n = 1;
        while(n <  a.size() + b.size()) n <<= 1;

        vector<base> fa(ALL(a)), fb(ALL(b));
        fa.resize(n);
        fb.resize(n);

        fft(fa, false);
        fft(fb, false);

        FORR(i, 0, n) fa[i] *= fb[i];

        fft(fa, true);
        vector<int> res(n);
        FORR(i, 0, n){
                res[i] = (int)(fa[i].real() + 0.5);
                res[i] = min(res[i], 1);
        }
        while(res.back() == 0 && res.size() > 1) res.pop_back();
        return res;
}



vector<int> go(vector<int> a, int m)
{
        vector<int> z(1, 1);
        while(m){

                if(m & 1) z = multiply(z, a);
                a = multiply(a, a);
                m >>= 1;
        }

        return z;
}

int main() {

        //read();
        //ios_base::sync_with_stdio(false); cin.tie(NULL);cout.tie(NULL);
        //write();
        int n, k;
        scanf("%d %d", &n, &k);

        FOR(i, 1, n) scanf("%d", &x), arr[x] = 1;
        FOR(i, 0, 1000){
                v.pb(arr[i]);
        }

        vector<int> ans = go(v, k);
        FORR(i, 1, ans.size()){
                if(ans[i]) printf("%d ", i);
        }
        printf("\n");

        return 0;
}
