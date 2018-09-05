/* Copyright (C) 2017 Alexander Downey */
#ifndef _MATRIX_H
#define _MATRIX_H
#include <vector>
#include <iostream>
#include <string>
#include <cstdarg>
#include <memory>
#include <map>
#include "StringUtils.h"
#include "VectorUtils.h"

template <size_t t, typename v>
class Matrix {
    public:
        explicit Matrix(size_t i = 0) : vecOfMatrix(i) {};
        
        Matrix<t - 1, v> &operator [] (size_t i) {
            return vecOfMatrix[i];
        }
		const Matrix<t - 1, v> &operator [] (size_t i) const {
			return vecOfMatrix[i];
		}

		Matrix<t - 1, v> &at(size_t i) {
			return vecOfMatrix.at(i);
		}
		const Matrix<t - 1, v> &at(size_t i) const {
			return vecOfMatrix.at(i);
		}

        Matrix(int n, va_list vl) {
            if (n > 0) {
                int val=va_arg(vl,int); 
                vecOfMatrix.resize(val, Matrix<t - 1, v>(n - 1, vl));
            }
        };
        Matrix(int n, int iSize, ...) {
            if (n > 1) {
                va_list vl;
                va_start(vl,iSize);
                vecOfMatrix.resize(iSize, Matrix<t - 1, v>(n - 1, vl));
                    
                va_end(vl);
            }
        };
		Matrix(const Matrix<t - 1, v> &mat) : vecOfMatrix(1, mat) {}
		Matrix(size_t i, const Matrix<t - 1, v> &mat) : vecOfMatrix(i, mat) {}
		Matrix(const Matrix<t, v> &mat) : vecOfMatrix(mat.vecOfMatrix) {}
		Matrix(const std::vector<size_t> &vec) {
			std::vector<size_t> vec2;
			size_t tMySize = 1;
			if (vec.size() > 0) {
				vec2 = std::vector<size_t>(++vec.begin(), vec.end());
				tMySize = vec[0];
			}
			vecOfMatrix = std::vector<Matrix<t - 1, v> >(tMySize, Matrix<t - 1, v>(vec2));
		}
		Matrix(const Matrix<t, std::complex<v> > &mat, bool bReal) {
			for (size_t i = 0; i < mat.size(); ++i) {
				vecOfMatrix.push_back(Matrix<t - 1, v>(mat[i], bReal));
			}
		}

        std::shared_ptr<std::map<int, std::map<std::string, int> > > spMapLevelToNameMap;
		
		size_t getNDims() const {
			return t;
		}

		size_t numel() const {
			size_t tRet = 0;
			for (auto &iter : vecOfMatrix) {
				tRet += iter.numel();
			}
			return tRet;
		}

		size_t size() const {
			return vecOfMatrix.size();
		}

		std::vector<size_t> sizes() const {
			std::vector<size_t> vecRet = vecOfMatrix[0].sizes();
			vecRet.insert(vecRet.begin(), vecOfMatrix.size());
			return vecRet;
		}

		bool element(size_t &ind, v *&val) {
			val = nullptr;
			bool bRet = false;
			for (size_t i = 0; i < vecOfMatrix.size() && !bRet; ++i) {
				bRet = vecOfMatrix[i].element(ind, val);
			}
			return bRet;
		}

		v &element(size_t ind) {
			v *pv = nullptr;
			element(ind, pv);
			return *pv;
		}
		
		/*Matrix<t + 1, v> operator() {
			return Matrix<t + 1, v>(*this);
		}*/
		size_t elements(std::vector<Matrix<0, v> > &vec) {
			for (size_t i = 0; i < vecOfMatrix.size(); ++i) {
				vecOfMatrix[i].elements(vec);
			}
			return vec.size();
		}

		size_t elements(std::vector<Matrix<0, const v> > &vec) const {
			for (size_t i = 0; i < vecOfMatrix.size(); ++i) {
				vecOfMatrix[i].elements(vec);
			}
			return vec.size();
		}

		//template<size_t t, typename v>
		Matrix<t - 1, v> slice(size_t dim, size_t ind) {
			Matrix<t - 1, v> mat;
			slice(mat, dim, ind);
			return mat;
		}

		void set(v val) {
			for (size_t i = 0; i < vecOfMatrix.size(); ++i) {
				vecOfMatrix[i].set(val);
			}
		}

		void set(const Matrix<t,v> &mat) {
			size_t iSize = std::min(vecOfMatrix.size(), mat.vecOfMatrix.size());
			for (size_t i = 0; i < vecOfMatrix.size(); ++i) {
				vecOfMatrix[i].set(mat[i]);
			}
		}

		bool setCopy(bool b) {
			for (size_t i = 0; i < vecOfMatrix.size(); ++i) {
				vecOfMatrix[i].setCopy(b);
			}
			return b;
		}

		Matrix<t, v> operator=(const Matrix<t, v> &mat) { /*vecOfMatrix = mat.vecOfMatrix;*/
			if (this != &mat) {
				vecOfMatrix.clear();
				vecOfMatrix.reserve(mat.vecOfMatrix.size());
				for (size_t i = 0; i < mat.size(); ++i) {
					vecOfMatrix.push_back(mat.vecOfMatrix[i]);
				}
			}
			return *this;
		}

		friend Matrix<t + 1, v>;
protected:
	std::vector<Matrix<t - 1, v> > vecOfMatrix;
	
	void slice(Matrix<t - 1, v> &mat, size_t dim, size_t ind) {
		if (dim == t) {
			mat = vecOfMatrix[ind];
		}
		else if (dim < t) {
			for (size_t i = 0; i < vecOfMatrix.size(); ++i) {
				mat.vecOfMatrix.push_back(vecOfMatrix[i].slice(dim, ind));
			}
		}
	}
};


template <typename v>
class Matrix<1, v> {
    public:
        explicit Matrix(size_t i = 0, v val = v()) : vecOfMatrix(i, Matrix<0, v>(val)) {};
        Matrix(int n, va_list vl) {
            if (n == 1) {
                int val=va_arg(vl,int); 
                vecOfMatrix.resize(val);
            } else if (n == 2) {
                int size=va_arg(vl,int);
                v val=va_arg(vl,v);
                vecOfMatrix.resize(size, Matrix<0, v>(val));
            }
        };
		Matrix(const std::vector<size_t> &vec) : vecOfMatrix(vec.empty() ? (size_t) 1 : vec[0], Matrix<0, v>(v())) {}
		Matrix(const Matrix<1, std::complex<v> > &mat, bool bReal) {
			for (size_t i = 0; i < mat.size(); ++i) {
				vecOfMatrix.push_back(Matrix<0, v>(bReal ? mat[i].real() : mat[i].imag()));
			}
		}

		template<class ForwardIterator>
		Matrix(ForwardIterator first, ForwardIterator last) {
			while (first != last) {
				vecOfMatrix.push_back(Matrix<0, v>(*first));
				++first;
			}
		}
		Matrix(const std::vector<v> &vec) : Matrix(vec.begin(), vec.end()) {}

        v &operator [] (size_t i) {
            return *vecOfMatrix[i];
        }
		const v &operator [] (size_t i) const {
			return *vecOfMatrix[i];
		}
		size_t numel() const {
			return vecOfMatrix.size();
		}
		size_t size() const {
			return vecOfMatrix.size();
		}
		std::vector<size_t> sizes() const {
			return std::vector<size_t>(1, vecOfMatrix.size());
		}
		bool element(size_t &ind, v *&val) {
			val = nullptr;
			bool bRet = ind < vecOfMatrix.size();
			if (bRet) {
				val = vecOfMatrix[ind].get();
			}
			else {
				ind -= vecOfMatrix.size();
			}
			return bRet;
		}

		size_t elements(std::vector<Matrix<0, v> > &vec) {
			for (size_t i = 0; i < vecOfMatrix.size(); ++i) {
				bool bCopy = vecOfMatrix[i].getCopy();
				vecOfMatrix[i].setCopy(false);
				vec.push_back(vecOfMatrix[i]);
				vecOfMatrix[i].setCopy(bCopy);
			}
			return vec.size();
		}

		size_t elements(std::vector<Matrix<0, const v> > &vec) const {
			for (size_t i = 0; i < vecOfMatrix.size(); ++i) {
				bool bCopy = vecOfMatrix[i].getCopy();
				vecOfMatrix[i].setCopy(false);
				vec.push_back(Matrix<0, const v>(vecOfMatrix[i]));
				vecOfMatrix[i].setCopy(bCopy);
			}
			return vec.size();
		}

		Matrix<0, v> &at(size_t i) {
			return vecOfMatrix[i];
		}
		/*Matrix<2, v> operator() {
			return Matrix<t + 1, v>(*this);
		}*/
		void set(v val) {
			for (size_t i = 0; i < vecOfMatrix.size(); ++i) {
				vecOfMatrix[i].set(val);
			}
		}

		void set(const Matrix<1, v> &mat) {
			size_t iSize = std::min(vecOfMatrix.size(), mat.vecOfMatrix.size());
			for (size_t i = 0; i < vecOfMatrix.size(); ++i) {
				vecOfMatrix[i].set(mat[i]);
			}
		}

		bool setCopy(bool b) {
			for (size_t i = 0; i < vecOfMatrix.size(); ++i) {
				vecOfMatrix[i].setCopy(b);
			}
			return b;
		}

		Matrix<0, v> slice(size_t dim, size_t ind) {
			return at(ind);
		}

		Matrix<1, v> operator=(const Matrix<1, v> &mat) { vecOfMatrix = mat.vecOfMatrix;  return *this; }

		template <typename v>
		friend std::ostream &printMatrix(std::ostream &os, const Matrix<1, v> &mat, const std::string &sTab);
		friend Matrix<2, v>;
protected:
	std::vector< Matrix<0, v> > vecOfMatrix;
};

template <typename v>
class Matrix<0, v> : public std::shared_ptr<v> {
public:
	explicit Matrix(const v &val) : bCopy(true), std::shared_ptr<v>(new v(val)) {}
	Matrix() : bCopy(true), std::shared_ptr<v>(new v()) {}
	//Matrix(const Matrix<0, v> &mat) : std::shared_ptr<v>(mat ? new v(*mat) : nullptr) {}
	//Matrix(const std::shared_ptr<v> sp) : std::shared_ptr<v>(sp) {}
	Matrix(const Matrix<0, v> &mat) : bCopy(mat.bCopy), std::shared_ptr<v>(mat.bCopy ? std::shared_ptr<v>(mat ? new v(*mat) : nullptr) : std::shared_ptr<v>(mat)) {}
	template<typename U>
	Matrix(const Matrix<0, U> &mat) : bCopy(mat.getCopy()), std::shared_ptr<v>(mat.getCopy() ? std::shared_ptr<U>(mat ? new U(*mat) : nullptr) : std::shared_ptr<U>(mat)) {}
	size_t numel() const {
		return this->get() ? 1 : 0;
	}
	size_t size() const {
		return numel();
	}
	v &operator [] (size_t i) {
		return *(*this);
	}
	const v &operator [] (size_t i) const {
		return *(*this);
	}
	bool setCopy(bool b) const {
		return bCopy = b;
	}
	bool getCopy() const {
		return bCopy;
	}

	Matrix<0, v> makeReference() {
		bool b = bCopy;
		bCopy = false;
		Matrix<0, v> mat = *this;
		bCopy = b;
		return mat;
	}
	void set(const v &val) {
		*(*this) = val;
	}
	void set(const Matrix<0, v> &mat) {
		*(*this) = *mat;
	}


	Matrix<0, v> makeCopy() const {
		return (*this) ? Matrix<0, v>(this->[0]) : Matrix<0, v>();
	}

private:
	mutable bool bCopy;
};

template<typename v>
std::ostream &printMatrix(std::ostream &os, const Matrix<1, v> &mat, const std::string &sTab) {
	os << sTab << "Dim " << 1 << ":\n" << sTab;
	os << mat.vecOfMatrix << "\n";
	return os;
}

template<size_t t, typename v>
std::ostream &printMatrix(std::ostream &os, const Matrix<t, v> &mat, const std::string &sTab) {
	os << sTab << "Dim " << t << ":\n";
	for (size_t i = 0; i < mat.size(); ++i) {
		os << sTab << "Index " << i << ":\n";
		printMatrix(os, mat[i], sTab + "    ");
	}
	os << "\n";
	return os;
}

template<size_t t, typename v>
std::ostream &operator<<(std::ostream &os, const Matrix<t, v> &mat) {
	return printMatrix(os, mat, std::string());
}

template<typename v>
std::ostream &operator<<(std::ostream &os, const Matrix<0, v> &mat) {
	if (mat) {
		os << *mat;
	}
	else {
		os << mat.get();
	}
	return os;
}



/*template <size_t t, typename v>
Matrix<t, v> operator+=(Matrix<t, v> &mat, v val) {

}*/
#define MATRIX_ASSIGN_OP(op) \
template <size_t t, typename v> \
Matrix<t, v> &operator##op(Matrix<t, v> &mat, v val) { \
	size_t iSize = mat.size(); \
	for (size_t i = 0; i < iSize; ++i) { \
		mat[i] op val; \
	} \
	return mat; \
} \
template <size_t t, typename v> \
Matrix<t, v> &operator##op(Matrix<t, v> &matL, const Matrix<t, v> &matR) { \
	if (matR.size() == 1) { \
		for (size_t i = 0; i < matL.size(); ++i) { \
			matL[i] op matR[0]; \
		} \
	} \
	else { \
		size_t iSize = std::min(matL.size(), matR.size()); \
		for (size_t i = 0; i < iSize; ++i) { \
			matL[i] op matR[i]; \
		} \
	} \
	return matL; \
} \
template <size_t t, typename v> \
Matrix<t, v> &operator##op(Matrix<t, v> &matL, const Matrix<t - 1, v> &matR) { \
	for (size_t i = 0; i < matL.size(); ++i) { \
		matL[i] op matR; \
	} \
	return matL; \
} \

MATRIX_ASSIGN_OP(+=);
MATRIX_ASSIGN_OP(-=);
MATRIX_ASSIGN_OP(*=);
MATRIX_ASSIGN_OP(/=);
MATRIX_ASSIGN_OP(&=);
MATRIX_ASSIGN_OP(|=);
MATRIX_ASSIGN_OP(^=);
MATRIX_ASSIGN_OP(%=);

#define MATRIX_OP(op) \
template <size_t t, typename v> \
Matrix<t, v> operator##op(Matrix<t, v> mat, v val) { \
	mat op##= val; \
	return std::move(mat); \
} \
template <size_t t, typename v> \
Matrix<t, v> operator##op(v val, Matrix<t, v> mat) { \
	size_t iSize = mat.size(); \
	for (size_t i = 0; i < iSize; ++i) { \
		mat.at(i).set(val op mat[i]); \
	} \
	return std::move(mat); \
} \
template <size_t t, typename v> \
Matrix<t, std::complex<v> > operator##op(const Matrix<t, v> &mat, std::complex<v> val) { \
	Matrix<t, std::complex<v> > matRet(mat.sizes()); \
	for (size_t i = 0; i < iSize; ++i) { \
		matRet.at(i).set(mat[i] op val); \
	} \
	return std::move(matRet); \
} \
template <size_t t, typename v> \
Matrix<t, std::complex<v> > operator##op(std::complex<v> val, const Matrix<t, v> &mat) { \
	Matrix<t, std::complex<v> > matRet(mat.sizes()); \
	size_t iSize = mat.size(); \
	for (size_t i = 0; i < iSize; ++i) { \
		matRet.at(i).set(val op mat[i]); \
	} \
	return std::move(matRet); \
} \
template <size_t t, typename v> \
Matrix<t, v> operator##op(Matrix<t, v> matL, const Matrix<t, v> &matR) { \
	if (matR.size() == 1) { \
		for (size_t i = 0; i < matL.size(); ++i) { \
			matL[i] op##= matR[0]; \
		} \
	} \
	else if (matL.size() == 1) { \
		Matrix<t, v> mat(matR.size(), matL[0]); \
		size_t iSize = std::min(mat.size(), matR.size()); \
		for (size_t i = 0; i < iSize; ++i) { \
			mat[i] op##= matR[i]; \
		} \
		return mat; \
	} else { \
		size_t iSize = std::min(matL.size(), matR.size()); \
		for (size_t i = 0; i < iSize; ++i) { \
			matL[i] op##= matR[i]; \
		} \
	} \
	return std::move(matL); \
} \
template <size_t t, typename v> \
Matrix<t, v> operator##op(Matrix<t, v> matL, const Matrix<t - 1, v> &matR) { \
	for (size_t i = 0; i < matL.size(); ++i) { \
		matL[i] op##= matR; \
	} \
	return std::move(matL); \
} \
template <size_t t, typename v> \
Matrix<t, v> operator##op(const Matrix<t - 1, v> &matL, const Matrix<t, v> &matR) { \
	Matrix<t, v> mat(matR.size(), matL); \
	size_t iSize = matR.size(); \
	for (size_t i = 0; i < iSize; ++i) { \
		mat[i].set(mat[i] op matR[i]); \
	} \
	return std::move(mat); \
} \


MATRIX_OP(+);
MATRIX_OP(-);
MATRIX_OP(*);
MATRIX_OP(/);
MATRIX_OP(&);
MATRIX_OP(|);
MATRIX_OP(^);
MATRIX_OP(%);

template<size_t t, typename v>
Matrix<t, v> operator-(const Matrix<t, v> &mat) {
	return 0 - mat;
}

//Prefix
template<size_t t, typename v>
Matrix<t, v> operator--(Matrix<t, v> &mat) {
	return mat -= 1;
}

//Postfix
template<size_t t, typename v>
Matrix<t, v> operator--(Matrix<t, v> &mat, int unused) {
	Matrix<t, v> matRet = mat;
	mat -= 1;
	return matRet;
}

//Prefix
template<size_t t, typename v>
Matrix<t, v> operator++(Matrix<t, v> &mat) {
	return mat += 1;
}

//Postfix
template<size_t t, typename v>
Matrix<t, v> operator++(Matrix<t, v> &mat, int unused) {
	Matrix<t, v> matRet = mat;
	mat += 1;
	return matRet;
}


#define MATRIX_FUNC1(mat_func) \
template <size_t t, typename v> \
Matrix<t, v> mat_func(Matrix<t, v> mat) { \
	return std::move(mat_func##i(mat)); \
} \
template <size_t t, typename v> \
Matrix<t, v> &mat_func##i(Matrix<t, v> &mat) { \
	for (size_t i = 0; i < mat.size(); ++i) { \
		mat_func##i(mat[i]); \
	} \
	return mat; \
} \
template <typename v> \
Matrix<1, v> &mat_func##i(Matrix<1, v> &mat) { \
	for (size_t i = 0; i < mat.size(); ++i) { \
		mat[i] = mat_func(mat[i]); \
	} \
	return mat; \
} \

#define MATRIX_FUNC2(mat_func) \
template <size_t t, typename v> \
Matrix<t, v> mat_func(Matrix<t, v> mat, const v &val) { \
	return std::move(mat_func##i(mat, val)); \
} \
template <size_t t, typename v> \
Matrix<t, v> &mat_func##i(Matrix<t, v> &mat, const v &val) { \
	for (size_t i = 0; i < mat.size(); ++i) { \
		mat_func##i(mat[i], val); \
	} \
	return mat; \
} \
template <typename v> \
Matrix<1, v> &mat_func##i(Matrix<1, v> &mat, const v &val) { \
	for (size_t i = 0; i < mat.size(); ++i) { \
		mat[i] = mat_func(mat[i], val); \
	} \
	return mat; \
} \
template <size_t t, typename v> \
Matrix<t, v> mat_func(Matrix<t, v> mat, const Matrix<t, v> &val) { \
	return std::move(mat_func##i(mat, val)); \
} \
template <size_t t, typename v> \
Matrix<t, v> &mat_func##i(Matrix<t, v> &mat, const Matrix<t, v> &val) { \
	size_t iSize = std::min(mat.size(), val.size()); \
	for (size_t i = 0; i < iSize; ++i) { \
		mat_func##i(mat[i], val[i]); \
	} \
	return mat; \
} \
template <typename v> \
Matrix<1, v> &mat_func##i(Matrix<1, v> &mat, const Matrix<1, v> &val) { \
	size_t iSize = std::min(mat.size(), val.size()); \
	for (size_t i = 0; i < iSize; ++i) { \
		mat[i] = mat_func(mat[i], val[i]); \
	} \
	return mat; \
} \


//namespace Mat {
	using std::sqrt;
	MATRIX_FUNC1(sqrt);
	using std::exp;
	MATRIX_FUNC1(exp);
	using std::isnan;
	MATRIX_FUNC1(isnan);
	using std::isinf;
	MATRIX_FUNC1(isinf);
	using std::real;
	MATRIX_FUNC1(real);
	using std::imag;
	MATRIX_FUNC1(imag);
	using std::abs;
	MATRIX_FUNC1(abs);
	MATRIX_OP(||);
	MATRIX_OP(&&);
	MATRIX_OP(> );
	MATRIX_OP(< );
	using std::pow;
	MATRIX_FUNC2(pow);
//};





template<size_t t, typename TypeFrom, typename TypeTo>
Matrix<t, TypeTo> convert(const Matrix<t, TypeFrom> &mat) {
	Matrix<t, TypeTo> matRet(mat.sizes());
	std::vector<Matrix<0, TypeTo> > vecTo;
	matRet.elements(vecTo);
	std::vector<Matrix<0, const TypeFrom> > vecFrom;
	mat.elements(vecFrom);
	for (size_t i = 0; i < vecTo.size(); ++i) {
		vecTo[i][0] = vecFrom[i][0];
	}

	return matRet;
}

template<size_t t, typename v>
Matrix<t, v> sum(const Matrix<t, v> &mat, size_t i) {
	if (i >= t) {
		return mat;
	}
	else if (i == t - 1) {
		std::vector<size_t> vecSize = mat.sizes();
		vecSize[0] = 1;
		Matrix<t, v> matRet(vecSize);
		for (size_t j = 0; j < mat.size(); ++j) {
			matRet[0] += mat[j];
		}
		return matRet;
	}
	else {
		std::vector<size_t> vecSize = mat.sizes();
		vecSize[vecSize.size() - i - 1] = 1;
		Matrix<t, v> matRet(vecSize);
		for (size_t j = 0; j < mat.size(); ++j) {
			matRet[j] += sum(mat[j], i);
		}
		return matRet;
	}
	return mat;
}
template<typename v>
Matrix<1, v> sum(const Matrix<1, v> &mat, size_t i) {
	if (i > 0) {
		return mat;
	}
	else {
		Matrix<1, v> matRet(1, 0.0);
		for (size_t j = 0; j < mat.size(); ++j) {
			matRet[0] += mat[j];
		}
		return matRet;
	}
	return mat;
}
#endif