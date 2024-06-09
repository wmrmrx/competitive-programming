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
