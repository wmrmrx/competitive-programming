template <typename T> struct Matrix {
	const size_t lin, col;
	vector<vector<T>> m;
	Matrix(size_t lin, size_t col): lin(lin), col(col) {
		m.assign(lin,vector<T>(col));
	}
	Matrix operator*(Matrix& B) const {
		assert(col == B.lin);
		size_t ret_lin = lin, ret_col = B.col;
		Matrix ret(ret_lin, ret_col);
		for(size_t i=0;i<ret_lin;i++) {
			for(size_t k=0;k<col;k++) {
				for(size_t j=0;j<ret_col;j++) {
					ret.m[i][j] += m[i][k]*B.m[k][j];
				}
			}
		}
		return ret;
	}
	void operator*=(Matrix& B) {
		assert(col == B.lin);
		size_t ret_lin = lin, ret_col = B.col;
		Matrix ret(ret_lin, ret_col);
		for(size_t i=0;i<ret_lin;i++) {
			for(size_t k=0;k<col;k++) {
				for(size_t j=0;j<ret_col;j++) {
					ret.m[i][j] += m[i][k]*B.m[k][j];
				}
			}
		}
		lin = ret.lin;
		col = ret.col;
		m = ret.m;
	}
	Matrix exp(uint64_t num) const {
		assert(lin == col);
		size_t N = lin;
		Matrix I(N,N);
		Matrix copy = *this;
		for(size_t i=0;i<N;i++) {
			I.m[i][i] = 1;
		}
		while(num) {
			if(num&1) {
				I *= copy;
			}
			num >>= 1;
			copy *= copy;
		}
		return I;
	}
	//Matrix operator__OPERATOR__(const Matrix& B) {
	//	assert(lin == B.lin && col == B.col);
	//	Matrix ret(lin, col);
	//	for(size_t i=0;i<lin;i++) {
	//		for(size_t j=0;j<col;j++) {
	//			ret.m[i][j] = m[i][j] __OPERATOR__ B.m[i][j]; 
	//		}
	//	}
	//	return ret;
	//}
	//void operator__OPERATOR__=(const Matrix& B) {
	//	assert(lin == B.lin && col == B.col);
	//	Matrix ret(lin, col);
	//	for(size_t i=0;i<lin;i++) {
	//		for(size_t j=0;j<col;j++) {
	//			ret.m[i][j] = m[i][j] __OPERATOR__ B.m[i][j]; 
	//		}
	//	}
	//	lin = ret.lin;
	//	col = ret.col;
	//	m = ret.m;
	//}
	void display() {
		for(size_t i=0;i<lin;i++) {
			for(size_t j=0;j<col;j++) {
				cout << m[i][j] << ' ';
			}
			if(i == lin-1) {
				cout << endl;
			} else {
				cout << '\n';
			}
		}
	}
};
