// Mint
template <const int MOD>
struct mint {
	int x;
	mint(): x(0) {}
	mint(int _x): x(_x%MOD<0?_x%MOD+MOD:_x%MOD) {}
	mint& operator+=(mint rhs) { x+=rhs.x; if(x>=MOD) x-=MOD; return *this; }
	mint& operator-=(mint rhs) { x-=rhs.x; if(x<0)x+=MOD; return *this; }
	mint& operator*=(mint rhs) { x*=rhs.x; x%=MOD; return *this; }
	mint& operator/=(mint rhs) { *this *= rhs.inv(); return *this; }
	mint operator+(mint rhs) { mint res=*this; res+=rhs; return res; }
	mint operator-(mint rhs) { mint res=*this; res-=rhs; return res; }
	mint operator*(mint rhs) { mint res=*this; res*=rhs; return res; }
	mint operator/(mint rhs) { mint res=*this; res/=rhs; return res; }
	mint inv() { return this->pow(MOD-2); }
	mint pow(int e) {
		mint res(1);
		for(mint p=*this;e>0;e/=2,p*=p) if(e%2)
			res*=p;
		return res;
	}
	bool operator<(mint rhs) { return x < rhs.x; }
	bool operator!=(mint rhs) { return x != rhs.x; }
	bool operator==(mint rhs) { return x == rhs.x; }
};
using Z = mint<998'244'353>;

struct hash_mint {
	mint<3000000019> x;
	mint<3000000109> y;
	hash_mint(): x(0), y(0) {}
	hash_mint(int _x, int _y): x(_x), y(_y) {}
	hash_mint(mint<3000000019> _x, mint<3000000109> _y): x(_x), y(_y) {}
	hash_mint& operator+=(hash_mint rhs) { return *this += rhs; }
	hash_mint& operator-=(hash_mint rhs) { return *this -= rhs; }
	hash_mint& operator*=(hash_mint rhs) { return *this *= rhs; }
	hash_mint& operator/=(hash_mint rhs) { return *this /= rhs; }
	hash_mint operator+(hash_mint rhs) { return *this += rhs; }
	hash_mint operator-(hash_mint rhs) { return *this -= rhs; }
	hash_mint operator*(hash_mint rhs) { return *this *= rhs; }
	hash_mint operator/(hash_mint rhs) { return *this /= rhs; }
	hash_mint inv() { return hash_mint(1, 1) / *this; }
	hash_mint pow(int e) { return hash_mint(x.pow(e), y.pow(e)); }
	bool operator==(hash_mint rhs) { return x == rhs.x && y == rhs.y; }
	bool operator!=(hash_mint rhs) { return x != rhs.x || y != rhs.y; }
	bool operator<(hash_mint rhs) { return x != rhs.x ? x < rhs.x : y < rhs.y; }
};
using ZZ = hash_mint;
