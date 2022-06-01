template <typename T> 
struct Matrix {
	int lin, col;
	unique_ptr<unique_ptr<T[]>[]> m;

	Matrix(int lin, int col): lin(lin), col(col), m(new unique_ptr<T[]>[lin]) {
		for(int i=0;i<lin;i++) m[i].reset(new T[col]);
		for(int i=0;i<lin;i++) fill_n(m[i].get(), col, 0);
	}

	Matrix operator*(Matrix& rhs) const {
		assert(col == rhs.lin);
		Matrix res(lin, rhs.col);
		for(int i=0;i<lin;i++) 
			for(int k=0;k<col;k++)
				for(int j=0;j<rhs.col;j++)
					res.m[i][j] += m[i][k]*rhs.m[k][j];
		return res;
	}

	Matrix exp(uint64_t num) const {
		assert(lin == col);
		int n = lin;
		Matrix res(n,n);
		for(int i=0;i<n;i++) res.m[i][i] = 1;
		for(Matrix copy=*this;num;num/=2,copy=copy*copy)
			if(num&1) res = res*copy;
		return res;
	}
};
