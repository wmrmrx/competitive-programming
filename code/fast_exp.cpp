int fast_exp(int num, int exponent, int mod) {
	int ret = 1;
	while(exponent) {
		if(exponent&1) {
			ret = (ret*num)%mod;
		}
		exponent >>= 1;
		num = (num*num)%mod;
	}
}
