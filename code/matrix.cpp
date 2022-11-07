template <typename T> 
struct Matrix {
	int n, m;
	vector<T> v;

	Matrix(int _n, int _m): n(_n), m(_m), v(n*m) {}

	T* operator[](int i) {
		return &v[i*n];
	}

	Matrix operator*(Matrix& rhs) const {
		//assert(m == rhs.n);
		Matrix res(n, rhs.m);
		for(int i=0;i<n;i++) 
			for(int k=0;k<m;k++)
				for(int j=0;j<rhs.m;j++)
					res[i][j] += (*this)[i][k]*rhs[k][j];
		return res;
	}

	Matrix exp(int num) {
		//assert(n == m);
		Matrix res(n,n);
		for(int i=0;i<n;i++) res[i][i] = 1;
		for(Matrix copy=*this;num;num/=2,copy=copy*copy)
			if(num&1) res = res*copy;
		return res;
	}
};
