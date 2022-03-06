//constexpr int64_t MOD = 1000000007;
struct Z {
	int64_t x;
	Z(const int64_t _x=0, const bool unchecked=false) {
		if(unchecked) x = _x;
		else{int64_t m=_x%MOD;if(m<0)x=m+MOD;else x=m;}
	}
	Z fexp(uint64_t e) const {
		Z ret(1,true);
		for(Z copy(x,true);e>0;e/=2,copy*=copy)if(e&1)ret*=copy;
		return ret;
	}
	Z inv()const{return this->fexp(MOD-2);}
	void operator+=(const Z rhs){x+=rhs.x;if(x>=MOD)x-=MOD;}
	void operator-=(const Z rhs){x-=rhs.x;if(x<0)x+=MOD;}
	void operator*=(const Z rhs){x*=rhs.x;x%=MOD;}
	void operator/=(const Z rhs){x*=rhs.inv().x;x%=MOD;}
	Z operator+(const Z rhs)const{Z ret(x,true);ret+=rhs;return ret;}
	Z operator-(const Z rhs)const{Z ret(x,true);ret-=rhs;return ret;}
	Z operator*(const Z rhs)const{Z ret(x,true);ret*=rhs;return ret;}
	Z operator/(const Z rhs)const{Z ret(x,true);ret/=rhs;return ret;}
};
