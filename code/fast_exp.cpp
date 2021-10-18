int fast_exp(int num, int exponent, int mod) {
	if(exponent == 0) {
		return 1;
	}
	int half = fast_exp(num,exponent/2,mod);
	half = (half*half)%mod;
	if(exponent%2) {
		half = (half*num)%mod;
	}
	return half;
}
