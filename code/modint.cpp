//constexpr int64_t MOD = 1000000007;
struct Z {
	int64_t x;
	Z(const int64_t x=0): x(x%MOD<0?x%MOD+MOD:x%MOD) {}
	Z fexp(uint64_t e) const {
		Z ret{1};
		for(Z copy{x};e>0;e/=2,copy*=copy)if(e&1)ret*=copy;
		return ret;
	}
	Z inv()const{return this->fexp(MOD-2);}
	void operator+=(const Z rhs){x+=rhs.x;if(x>=MOD)x-=MOD;}
	void operator-=(const Z rhs){x-=rhs.x;if(x<0)x+=MOD;}
	void operator*=(const Z rhs){x*=rhs.x;x%=MOD;}
	void operator/=(const Z rhs){x*=rhs.inv().x;x%=MOD;}
	bool operator==(const Z rhs)const{return x==rhs.x;}
	Z operator+(const Z rhs)const{Z ret{x};ret+=rhs;return ret;}
	Z operator-(const Z rhs)const{Z ret{x};ret-=rhs;return ret;}
	Z operator*(const Z rhs)const{Z ret{x};ret*=rhs;return ret;}
	Z operator/(const Z rhs)const{Z ret{x};ret/=rhs;return ret;}
};
