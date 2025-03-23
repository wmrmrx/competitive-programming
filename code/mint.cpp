template <const int64_t MOD> struct mint {
	int32_t x;
	mint(): x(0) {}
	mint(int64_t _x): x(_x%MOD<0?_x%MOD+MOD:_x%MOD) {}
	mint& operator+=(mint rhs) { x+=rhs.x; if(x>=MOD) x-=MOD; return *this; }
	mint& operator-=(mint rhs) { x-=rhs.x; if(x<0)x+=MOD; return *this; }
	mint& operator*=(mint rhs) { x=int64_t(x)*int64_t(rhs.x)%MOD; return *this; }
	mint& operator/=(mint rhs) { *this *= rhs.inv(); return *this; }
	mint operator+(mint rhs) { mint res=*this; return res+=rhs; }
	mint operator-(mint rhs) { mint res=*this; return res-=rhs; }
	mint operator*(mint rhs) { mint res=*this; return res*=rhs; }
	mint operator/(mint rhs) { mint res=*this; return res/=rhs; }
	mint inv() { return this->pow(MOD-2); }
	mint pow(int64_t e) {
		mint res(1);
		for(mint p=*this;e>0;e/=2,p*=p) if(e%2)
			res*=p;
		return res;
	}
	bool operator<(mint rhs) { return x < rhs.x; }
	bool operator!=(mint rhs) { return x != rhs.x; }
	bool operator==(mint rhs) { return x == rhs.x; }
	friend ostream& operator<<(ostream& o, mint m) { return o << m.x; }
};
using Z = mint<998'244'353>;

struct Comb {
    int n;
    vector<Z> _fac;
    vector<Z> _invfac;
    vector<Z> _inv;
    
    Comb() : n{0}, _fac{1}, _invfac{1}, _inv{0} {}
    Comb(int n) : Comb() {
        init(n);
    }
    void init(int m) {
        if (m <= n) return;
        _fac.resize(m + 1);
        _invfac.resize(m + 1);
        _inv.resize(m + 1);
        
        for (int i = n + 1; i <= m; i++) {
            _fac[i] = _fac[i - 1] * i;
        }
        _invfac[m] = _fac[m].inv();
        for (int i = m; i > n; i--) {
            _invfac[i - 1] = _invfac[i] * i;
            _inv[i] = _invfac[i] * _fac[i - 1];
        }
        n = m;
    }
    Z fac(int m) {
        if (m > n) init(2 * m);
        return _fac[m];
    }
    Z invfac(int m) {
        if (m > n) init(2 * m);
        return _invfac[m];
    }
    Z inv(int m) {
        if (m > n) init(2 * m);
        return _inv[m];
    }
    Z binom(int n, int m) {
        if (n < m || m < 0) return 0;
        return fac(n) * invfac(m) * invfac(n - m);
    }
} comb;
