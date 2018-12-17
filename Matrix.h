/* Copyright (C) 2017 Alexander Downey */
#ifndef _MATRIX_H
#define _MATRIX_H
#include <vector>
#include <iostream>
#include <string>
#include <cstdarg>
#include <memory>
#include <map>
#include <list>
#include <iterator>
#include "StringUtils.h"
#include "VectorUtils.h"

class matrix_iterator_base;
class Matlab;

template<size_t t, typename v>
class matrix_iterator;// : public std::iterator<std::random_access_iterator_tag, v>, public matrix_iterator_base;

template<size_t t, typename v>
class const_matrix_iterator;

namespace Mat {
	template <size_t t, typename v>
	class Matrix {
	public:
		explicit Matrix(size_t i = 0) : vecOfMatrix(i) {};

		Matrix<t - 1, v> &operator [] (size_t i) {
			if (i < 0) {
				i = vecOfMatrix.size() - i;
			}
			return vecOfMatrix[i];
		}
		const Matrix<t - 1, v> &operator [] (size_t i) const {
			if (i < 0) {
				i = vecOfMatrix.size() - i;
			}
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
				int val = va_arg(vl, int);
				vecOfMatrix.resize(val, Matrix<t - 1, v>(n - 1, vl));
			}
		};
		Matrix(int n, int iSize, ...) {
			if (n > 1) {
				va_list vl;
				va_start(vl, iSize);
				vecOfMatrix.resize(iSize, Matrix<t - 1, v>(n - 1, vl));

				va_end(vl);
			}
		};
		Matrix(const Matrix<t - 1, v> &mat) : vecOfMatrix(1, mat) {}
		Matrix(size_t i, const Matrix<t - 1, v> &mat) : vecOfMatrix(i, mat) {}
		Matrix(const Matrix<t, v> &mat) : vecOfMatrix(mat.vecOfMatrix) {}
		Matrix(const std::vector<Matrix<t - 1, v> > &vec) : vecOfMatrix(vec) {}
		Matrix(const std::vector<size_t> &vec, v val) {
			std::vector<size_t> vec2;
			size_t tMySize = 1;
			if (vec.size() > 0) {
				vec2 = std::vector<size_t>(++vec.begin(), vec.end());
				tMySize = vec[0];
			}
			vecOfMatrix = std::vector<Matrix<t - 1, v> >(tMySize, Matrix<t - 1, v>(vec2, val));
		}
		Matrix(const Matrix<t, std::complex<v> > &mat, bool bReal) {
			for (size_t i = 0; i < mat.size(); ++i) {
				vecOfMatrix.push_back(Matrix<t - 1, v>(mat[i], bReal));
			}
		}

		//std::shared_ptr<std::map<int, std::map<std::string, int> > > spMapLevelToNameMap;

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

		bool elementMat1(size_t &ind, Matrix<1, v> *&val) {
			val = nullptr;
			bool bRet = false;
			for (size_t i = 0; i < vecOfMatrix.size() && !bRet; ++i) {
				bRet = vecOfMatrix[i].elementMat1(ind, val);
			}
			return bRet;
		}

		bool elementMat1Iter(size_t &ind, typename Matrix<1, v>::iterator &iter) {
			bool bRet = false;
			for (size_t i = 0; i < vecOfMatrix.size() && !bRet; ++i) {
				bRet = vecOfMatrix[i].elementMat1Iter(ind, iter);
			}
			return bRet;
		}

		v &element(size_t ind) {
			v *pv = nullptr;
			element(ind, pv);
			return *pv;
		}

		const v &element(size_t ind) const {
			v *pv = nullptr;
			const_cast<Mat::Matrix<t, v> *>(this)->element(ind, pv);
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
		Matrix<t - 1, v> slice(size_t dim, long long int ind) {
			Matrix<t - 1, v> mat;
			slice(mat, dim, ind);
			return mat;
		}

		Matrix<t, v> slice(size_t dim, size_t indBeg, long long int indEnd) {
			Matrix<t, v> mat;
			slice(mat, dim, indBeg, indEnd);
			return mat;
		}

		void set(v val) {
			for (size_t i = 0; i < vecOfMatrix.size(); ++i) {
				vecOfMatrix[i].set(val);
			}
		}

		void set(const Matrix<t, v> &mat) {
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
		friend Matlab;

		typedef typename matrix_iterator<t, v> iterator;
		typedef typename const_matrix_iterator<t, v> const_iterator;
		iterator begin() {
			return iterator(*this, 0);
		}

		iterator end() {
			return iterator(*this);
		}

		const_iterator begin() const {
			return const_iterator(*this, 0);
		}

		const_iterator end() const {
			return const_iterator(*this);
		}

		Matrix<t, v> &append(Matrix<t - 1, v> &val) {
			vecOfMatrix.insert(vecOfMatrix.end(), Mat::Matrix<t - 1, v>(val));
			return *this;
		}

		Matrix<t, v> &resize(std::list<size_t> lsize, v val = v()) {
			if (lsize.size() == t) {
				size_t tOld = size();
				if (tOld < lsize.front()) {
					std::vector<size_t> vecSize(++lsize.begin(), lsize.end());
					Matrix<t - 1, v> mat(vecSize, val);
					vecOfMatrix.resize(lsize.front(), mat);
				}
				else if (tOld > lsize.front()) {
					vecOfMatrix.resize(lsize.front());
				}
				lsize.pop_front();
				tOld = std::min(tOld, vecOfMatrix.size());
				for (size_t i = 0; i < tOld; ++i) {
					vecOfMatrix[i].resize(lsize, val);
				}
			}
			return *this;
		}

		Matrix<t,v> &pop_back() {
			if (vecOfMatrix.size() > 0) {
				vecOfMatrix.pop_back();
			}
			return *this;
		}

		explicit operator bool() {
			return all(*this);
		}

	protected:
		std::vector<Matrix<t - 1, v> > vecOfMatrix;

		void slice(Matrix<t - 1, v> &mat, size_t dim, long long int ind) {
			if (dim == t) {
				if (ind < 0) ind += vecOfMatrix.size();
				mat = vecOfMatrix[ind];
			}
			else if (dim < t) {
				for (size_t i = 0; i < vecOfMatrix.size(); ++i) {
					mat.vecOfMatrix.push_back(vecOfMatrix[i].slice(dim, ind));
				}
			}
		}
		void slice(Matrix<t, v> &mat, size_t dim, size_t indBeg, long long int indEnd) {
			if (dim == t) {
				if (indEnd < 0) indEnd += vecOfMatrix.size();
				indEnd = std::min((long long int) size() - 1, indEnd);
				for (size_t i = indBeg; i <= indEnd; ++i) {
					mat.vecOfMatrix.push_back(vecOfMatrix[i]);
				}
			}
			else if (dim < t) {
				for (size_t i = 0; i < vecOfMatrix.size(); ++i) {
					mat.vecOfMatrix.push_back(vecOfMatrix[i].slice(dim, indBeg, indEnd));
				}
			}
		}
	};


	template <typename v>
	class Matrix<1, v> {
	public:
		Matrix() { /*std::cerr << "Matrix default\n"; */}
		explicit Matrix(size_t i, v val = v()) : vecOfMatrix(i, Matrix<0, v>(val)) { /*std::cerr << "Matrix " << i << " " << val << std::endl;*/ };
		//Matrix(v val) : Matrix((size_t) 1, val) {}
		Matrix(int n, va_list vl) {
			if (n == 1) {
				int val = va_arg(vl, int);
				vecOfMatrix.resize(val);
			}
			else if (n == 2) {
				int size = va_arg(vl, int);
				v val = va_arg(vl, v);
				vecOfMatrix.resize(size, Matrix<0, v>(val));
			}
		};
		Matrix(const std::vector<size_t> &vec, v val) : vecOfMatrix(vec.empty() ? (size_t)1 : vec[0], Matrix<0, v>(val)) {}
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
		//Matrix(const Matrix<1, v> &mat) : vecOfMatrix(mat.vecOfMatrix) {}

		v &operator [] (long long int i) {
			if (i < 0) i += vecOfMatrix.size();
			return *vecOfMatrix[i];
		}
		const v &operator [] (long long int i) const {
			if (i < 0) i += vecOfMatrix.size();
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

		v &element(size_t ind) {
			return *vecOfMatrix[ind];
		}

		const v &element(size_t ind) const {
			return *vecOfMatrix[ind];
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

		Matrix<0, v> &at(long long int i) {
			if (i < 0) i += vecOfMatrix.size();
			return vecOfMatrix[i];
		}
		const v &at(long long int i) const {
			if (i < 0) i += vecOfMatrix.size();
			return *vecOfMatrix[i];
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

		Matrix<0, v> slice(size_t dim, long long int ind) {
			return at(ind);
		}

		Matrix<1, v> slice(size_t dim, size_t tBeg, long long int tEnd) {
			Matrix<1, v> mat;
			if (tEnd < 0) tEnd += vecOfMatrix.size();
			size_t tMin = std::min(tEnd, (long long int) vecOfMatrix.size());
			for (size_t i = tBeg; i <= tMin; ++i) {
				mat.vecOfMatrix.push_back(at(i));
			}

			return mat;
		}

		std::vector<v> toVector() const {
			std::vector<v> vec;
			vec.reserve(vecOfMatrix.size());
			for (size_t i = 0; i < vecOfMatrix.size(); ++i) {
				vec.push_back(*vecOfMatrix[i]);
			}
			return vec;
		}

		Matrix<1, v> operator=(const Matrix<1, v> &mat) { vecOfMatrix = mat.vecOfMatrix;  return *this; }

		template <typename v>
		friend std::ostream &printMatrix(std::ostream &os, const Mat::Matrix<1, v> &mat, const std::string &sTab);
		friend Matrix<2, v>;
		//typedef typename std::vector< Matrix<0, v> >::iterator iterator;
		friend matrix_iterator_base;
		friend Matlab;

		typedef typename matrix_iterator<1, v> iterator;
		typedef typename const_matrix_iterator<1, v> const_iterator;
		iterator begin() {
			return iterator(*this, 0);
		}

		iterator end() {
			return iterator(*this);
		}

		const_iterator begin() const {
			return const_iterator(*this, 0);
		}

		const_iterator end() const {
			return const_iterator(*this);
		}

		bool elementMat1Iter(size_t &ind, typename Matrix<1, v>::iterator &iter) {
			bool bRet = ind < vecOfMatrix.size();
			if (bRet) {
				iter = vecOfMatrix.begin() + ind;
			}
			else {
				ind -= vecOfMatrix.size();
			}
			return bRet;
		}

		bool elementMat1(size_t &ind, Matrix<1, v> *&val) {
			bool bRet = ind < vecOfMatrix.size();
			if (bRet) {
				val = this;
			}
			else {
				ind -= vecOfMatrix.size();
			}
			return bRet;
		}

		static Matrix<1, v> range(v begin, v inc, v end) {
			if (end < begin || inc == (v) 0) {
				return Matrix<1, v>();
			}
			Matrix<1, v> mat(1 + (end - begin) / inc);
			for (size_t i = 0; i < mat.size(); ++i) {
				mat[i] = begin;
				begin += inc;
			}
			return mat;
		}

		Matrix<1, v> &append(const Matrix<1, v> &mat) {
			vecOfMatrix.insert(vecOfMatrix.end(), mat.vecOfMatrix.begin(), mat.vecOfMatrix.end());
			return *this;
		}

		Matrix<1, v> &append(const v &val) {
			vecOfMatrix.insert(vecOfMatrix.end(), Mat::Matrix<0, v>(val));
			return *this;
		}

		Matrix<1, v> &prepend(const Matrix<1, v> &mat) {
			vecOfMatrix.insert(vecOfMatrix.begin(), mat.vecOfMatrix.begin(), mat.vecOfMatrix.end());
			return *this;
		}

		Matrix<1, v> &prepend(const v &val) {
			vecOfMatrix.insert(vecOfMatrix.begin(), Mat::Matrix<0, v>(val));
			return *this;
		}
		/* Creats a one dimensional matrix with values in the range [start, finish] */
		static void range(Matrix<1, v> &mat, const v &start, const v &inc, const v &finish) {
			//mat.vecOfMatrix.clear();
			v vMax = std::max(start, finish);
			v vMin = std::min(start, finish);
			if (inc != 0) {
				for (v vCur = start; vCur <= vMax && vCur >= vMin; vCur += inc) {
					mat.vecOfMatrix.push_back(Matrix<0, v>(vCur));
				}
			}
		}

		Mat::Matrix<1, v> getRange(size_t start, size_t inc, long long int finish) const {
			Mat::Matrix<1, v> matRet;
			if (static_cast<int>(inc) > 0) {
				if (finish < 0) finish += vecOfMatrix.size();
				if (finish > start) {
					for (size_t i = start; i <= finish; i += inc) {
						matRet.vecOfMatrix.push_back(vecOfMatrix[i]);
					}
				}
				else {
					for (size_t i = start; i >= finish; i -= inc) {
						matRet.vecOfMatrix.push_back(vecOfMatrix[i]);
					}
				}
			}
			return matRet;
		}

		Matrix<1, v> &resize(std::list<size_t> lsize, v val = v()) {
			vecOfMatrix.resize(lsize.front(), Matrix<0, v>(val));
			return *this;
		}

		Matrix<1, v> pop_back() {
			if (vecOfMatrix.size() > 0) {
				vecOfMatrix.pop_back();
			}
			return *this;
		}

		//explicit operator bool() { return all(*this); }
		/*
		bool operator<=(const Mat::Matrix<1, v> &mat) {
			return compare(*this, mat) <= 0;
		}

		bool operator>=(const Mat::Matrix<1, v> &mat) {
			return compare(*this, mat) >= 0;
		}

		bool operator<(const Mat::Matrix<1, v> &mat) const {
			return compare(*this, mat) < 0;
		}

		bool operator>(const Mat::Matrix<1, v> &mat) {
			return compare(*this, mat) > 0;
		}

		bool operator==(const Mat::Matrix<1, v> &mat) {
			return compare(*this, mat) == 0;
		}

		bool operator!=(const Mat::Matrix<1, v> &mat) {
			return compare(*this, mat) != 0;
		}*/


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
	std::ostream &printMatrix(std::ostream &os, const Mat::Matrix<1, v> &mat, const std::string &sTab) {
		os << sTab << "Dim " << 1 << ":\n" << sTab;
		os << mat.vecOfMatrix << "\n";
		return os;
	}

	template<size_t t, typename v>
	std::ostream &printMatrix(std::ostream &os, const Mat::Matrix<t, v> &mat, const std::string &sTab) {
		os << sTab << "Dim " << t << ":\n";
		for (size_t i = 0; i < mat.size(); ++i) {
			os << sTab << "Index " << i << ":\n";
			printMatrix(os, mat[i], sTab + "    ");
		}
		os << "\n";
		return os;
	}
}
template<size_t t, typename v>
std::ostream &operator<<(std::ostream &os, const Mat::Matrix<t, v> &mat) {
	return Mat::printMatrix(os, mat, std::string());
}

template<typename v>
std::ostream &operator<<(std::ostream &os, const Mat::Matrix<0, v> &mat) {
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
Mat::Matrix<t, v> &operator##op(Mat::Matrix<t, v> &mat, v val) { \
	size_t iSize = mat.size(); \
	for (size_t i = 0; i < iSize; ++i) { \
		mat[i] op val; \
	} \
	return mat; \
} \
template <size_t t, typename v> \
Mat::Matrix<t, v> &operator##op(Mat::Matrix<t, v> &matL, const Mat::Matrix<t, v> &matR) { \
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
Mat::Matrix<t, v> &operator##op(Mat::Matrix<t, v> &matL, const Mat::Matrix<t - 1, v> &matR) { \
	for (size_t i = 0; i < matL.size(); ++i) { \
		matL[i] op matR; \
	} \
	return matL; \
} \
template <size_t t, typename v> \
Mat::Matrix<t, std::complex<v> > &operator##op(Mat::Matrix<t, std::complex<v> > &matL, const Mat::Matrix<t, v> &matR) { \
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



MATRIX_ASSIGN_OP(+=);
MATRIX_ASSIGN_OP(-=);
MATRIX_ASSIGN_OP(*=);
MATRIX_ASSIGN_OP(/=);
MATRIX_ASSIGN_OP(&=);
MATRIX_ASSIGN_OP(|=);
MATRIX_ASSIGN_OP(^=);
MATRIX_ASSIGN_OP(%=);

#define MATRIX_OP(op, func) \
/* Matrix op val */ \
template <typename v> \
Mat::Matrix<0, v> &func##iLeft(Mat::Matrix<0, v> &mat, v val) { \
	mat[0] = mat[0] op val; \
	return mat; \
} \
template <size_t t, typename v> \
Mat::Matrix<t, v> &func##iLeft(Mat::Matrix<t, v> &mat, v val) { \
	for (size_t i = 0; i < mat.size(); ++i) { \
		func##iLeft(mat.at(i), val); \
	} \
	return mat; \
} \
template <size_t t, typename v> \
Mat::Matrix<t, v> func##(Mat::Matrix<t, v> mat, v val) { \
	return func##iLeft(mat, val); \
} \
template <size_t t, typename v> \
Mat::Matrix<t, v> operator##op(Mat::Matrix<t, v> mat, v val) { \
	return func##iLeft(mat, val); \
} \
/* val op Matrix */ \
template <typename v> \
Mat::Matrix<0, v> &func##iRight(v val, Mat::Matrix<0, v> &mat) { \
	mat[0] = val op mat[0]; \
	return mat; \
} \
template <size_t t, typename v> \
Mat::Matrix<t, v> &func##iRight(v val, Mat::Matrix<t, v> &mat) { \
	for (size_t i = 0; i < mat.size(); ++i) { \
		func##iRight(val, mat.at(i)); \
	} \
	return mat; \
} \
template <size_t t, typename v> \
Mat::Matrix<t, v> func##(v val, Mat::Matrix<t, v> mat) { \
	return func##iRight(val, mat); \
} \
template <size_t t, typename v> \
Mat::Matrix<t, v> operator##op(v val, Mat::Matrix<t, v> mat) { \
	return func##iRight(val, mat); \
} \
/* Matrix op Matrix */ \
template <size_t t, typename v> \
 Mat::Matrix<t, v> &func##iLeft(Mat::Matrix<t, v> &matL, const Mat::Matrix<t, v> &matR) { \
	if (matR.size() == 1) { \
		for (size_t i = 0; i < matL.size(); ++i) { \
			func##iLeft(matL.at(i), matR.at(0)); \
		} \
	} else { \
		size_t tMin = std::min(matL.size(), matR.size()); \
		for (size_t i = 0; i < tMin; ++i) { \
			func##iLeft(matL.at(i), matR.at(i)); \
		} \
	} \
	return matL; \
} \
template <typename v> \
 Mat::Matrix<0, v> &func##iLeft(Mat::Matrix<0, v> &matL, const Mat::Matrix<0, v> &matR) { \
	matL[0] = matL[0] op matR[0]; \
	return matL; \
} \
template <size_t t, typename v> \
 Mat::Matrix<t, v> &func##iRight(const Mat::Matrix<t, v> &matL, Mat::Matrix<t, v> &matR) { \
	if (matL.size() == 1) { \
		for (size_t i = 0; i < matR.size(); ++i) { \
			func##iRight(matL.at(0), matR.at(i)); \
		} \
	} else { \
		size_t tMin = std::min(matL.size(), matR.size()); \
		for (size_t i = 0; i < tMin; ++i) { \
			func##iRight(matL.at(i), matR.at(i)); \
		} \
	} \
	return matR; \
} \
template <typename v> \
 Mat::Matrix<0, v> &func##iRight(const Mat::Matrix<0, v> &matL, Mat::Matrix<0, v> &matR) { \
	matR[0] = matL[0] op matR[0]; \
	return matR; \
} \
template <size_t t, typename v> \
 Mat::Matrix<t, v> operator##op(Mat::Matrix<t, v> matL, const Mat::Matrix<t, v> &matR) { \
	if (matL.numel() == 1) return func##iRight(matL.element(0), Mat::Matrix<t,v>(matR)); \
	return func##iLeft(matL, matR); \
} \
/* complex Matrix op Matrix */ \
template <size_t t, typename v> \
Mat::Matrix<t, std::complex<v> > &func##iLeft(Mat::Matrix<t, std::complex<v> > &matL, const Mat::Matrix<t, v> &matR) { \
	if (matR.size() == 1) { \
		for (size_t i = 0; i < matR.size(); ++i) { \
			func##iLeft(matL.at(i), matR.at(0)); \
		} \
	} else { \
		size_t tMin = std::min(matL.size(), matR.size()); \
		for (size_t i = 0; i < tMin; ++i) { \
			func##iLeft(matL.at(i), matR.at(i)); \
		} \
	} \
	return matL; \
} \
template <typename v> \
 Mat::Matrix<0, std::complex<v> > &func##iLeft(Mat::Matrix<0, std::complex<v> > &matL, const Mat::Matrix<0, v> &matR) { \
	matL[0] = matL[0] op matR[0]; \
	return matL; \
} \
template <size_t t, typename v> \
Mat::Matrix<t, std::complex<v> > operator##op(Mat::Matrix<t, std::complex<v> > matL, const Mat::Matrix<t, v> &matR) { \
	if (matL.numel() == 1) {\
		matL.resize(VectorUtils::toList(matR.sizes()), matL.element(0));\
	}\
	return func##iLeft(matL, matR); \
} \
/* Matrix op complex Matrix */ \
template <size_t t, typename v> \
Mat::Matrix<t, std::complex<v> > &func##iRight(const Mat::Matrix<t, v> &matL, Mat::Matrix<t, std::complex<v> > &matR) { \
	if (matL.size() == 1) { \
		for (size_t i = 0; i < matR.size(); ++i) { \
			func##iRight(matL.at(0), matR.at(i)); \
		} \
	} else { \
		size_t tMin = std::min(matL.size(), matR.size()); \
		for (size_t i = 0; i < tMin; ++i) { \
			func##iRight(matL.at(i), matR.at(i)); \
		} \
	} \
	return matR; \
} \
template <typename v> \
 Mat::Matrix<0, std::complex<v> > &func##iRight(const Mat::Matrix<0, v> &matL, Mat::Matrix<0, std::complex<v> > &matR) { \
	matR[0] = matL[0] op matR[0]; \
	return matR; \
} \
template <size_t t, typename v> \
Mat::Matrix<t, std::complex<v> > operator##op(const Mat::Matrix<t, v> &matL, Mat::Matrix<t, std::complex<v> > matR) { \
	return func##iRight(matL, matR); \
} \
/* Matrix op complex val */ \
template <size_t t, typename v> \
Mat::Matrix<t, std::complex<v> > operator##op(const Mat::Matrix<t, v> &mat, std::complex<v> val) { \
	Mat::Matrix<t, std::complex<v> > matRet = convert<t, v, std::complex<v> >(mat); \
	return func##iLeft(matRet, val); \
} \
template <size_t t, typename v> \
Mat::Matrix<t, std::complex<v> > operator##op(std::complex<v> val, const Mat::Matrix<t, v> &mat) { \
	Mat::Matrix<t, std::complex<v> > matRet = convert<t, v, std::complex<v> >(mat); \
	return func##iRight(val, matRet); \
} \
template <size_t t, typename v> \
Mat::Matrix<t, std::complex<v> > func##iLeft(Mat::Matrix<t, std::complex<v> > &mat, v val) { \
	return func##iLeft(mat, std::complex<v>(val)); \
} \
template <size_t t, typename v> \
Mat::Matrix<t, std::complex<v> > func##iRight(v val, Mat::Matrix<t, std::complex<v> > &mat) { \
	return func##iRight(std::complex<v>(val), mat); \
} \
/* Matrix<t> op Matrix<t-1> */ \
template <size_t t, typename v> \
Mat::Matrix<t, v> &func##iLeft(Mat::Matrix<t, v> &matL, const Mat::Matrix<t - 1, v> &matR) { \
	for (size_t i = 0; i < matL.size(); ++i) { \
		func##iLeft(matL.at(i), matR); \
	} \
	return matL; \
} \
template <size_t t, typename v> \
Mat::Matrix<t, v> &func##iRight(const Mat::Matrix<t - 1, v> &matL, Mat::Matrix<t, v> &matR) { \
	for (size_t i = 0; i < matR.size(); ++i) { \
		func##iRight(matL, matR.at(i)); \
	} \
	return matR; \
} \
template <size_t t, typename v> \
Mat::Matrix<t, v> operator##op(Mat::Matrix<t, v> matL, const Mat::Matrix<t - 1, v> &matR) { \
	return func##iLeft(matL, matR); \
} \
template <size_t t, typename v> \
Mat::Matrix<t, v> operator##op(const Mat::Matrix<t - 1, v> &matL, Mat::Matrix<t, v> matR) { \
	return func##iRight(matL, matR); \
} \


#if 0

template <size_t t, typename v> \
Mat::Matrix<t, v> operator##op(v val, Mat::Matrix<t, v> mat) { \
	size_t iSize = mat.size(); \
	for (size_t i = 0; i < iSize; ++i) { \
		mat.at(i).set(val op mat[i]); \
	} \
	return std::move(mat); \
} \
template <size_t t, typename v> \
Mat::Matrix<t, std::complex<v> > operator##op(const Mat::Matrix<t, v> &mat, std::complex<v> val) { \
	Mat::Matrix<t, std::complex<v> > matRet(mat.sizes(), std::complex<v>()); \
	for (size_t i = 0; i < iSize; ++i) { \
		matRet.at(i).set(mat[i] op val); \
	} \
	return std::move(matRet); \
} \
template <size_t t, typename v> \
Mat::Matrix<t, std::complex<v> > operator##op(std::complex<v> val, const Mat::Matrix<t, v> &mat) { \
	Mat::Matrix<t, std::complex<v> > matRet(mat.sizes(), std::complex<v>()); \
	size_t iSize = mat.size(); \
	for (size_t i = 0; i < iSize; ++i) { \
		matRet.at(i).set(val op mat[i]); \
	} \
	return std::move(matRet); \
} \
template <size_t t, typename v> \
Mat::Matrix<t, v> operator##op(Mat::Matrix<t, v> matL, const Mat::Matrix<t, v> &matR) { \
	if (matR.size() == 1) { \
		for (size_t i = 0; i < matL.size(); ++i) { \
			matL[i] op##= matR[0]; \
		} \
	} \
	else if (matL.size() == 1) { \
		Mat::Matrix<t, v> mat(matR.size(), matL[0]); \
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
Mat::Matrix<t, v> operator##op(Mat::Matrix<t, v> matL, const Mat::Matrix<t - 1, v> &matR) { \
	for (size_t i = 0; i < matL.size(); ++i) { \
		matL[i] op##= matR; \
	} \
	return std::move(matL); \
} \
template <size_t t, typename v> \
Mat::Matrix<t, v> operator##op(const Mat::Matrix<t - 1, v> &matL, const Mat::Matrix<t, v> &matR) { \
	Mat::Matrix<t, v> mat(matR.size(), matL); \
	size_t iSize = matR.size(); \
	for (size_t i = 0; i < iSize; ++i) { \
		mat[i].set(mat[i] op matR[i]); \
	} \
	return std::move(mat); \
} \

#endif

MATRIX_OP(+, Add);
MATRIX_OP(-, Subtract);
MATRIX_OP(*, Multiply);
MATRIX_OP(/, Divide);
MATRIX_OP(&, BitAnd);
MATRIX_OP(|, BitOr);
MATRIX_OP(^, BitXor);
MATRIX_OP(%, Mod);

template<size_t t, typename v>
Mat::Matrix<t, v> operator-(const Mat::Matrix<t, v> &mat) {
	return v() - mat;
}

//Prefix
template<size_t t, typename v>
Mat::Matrix<t, v> operator--(Mat::Matrix<t, v> &mat) {
	return mat -= (v) 1;
}

//Postfix
template<size_t t, typename v>
Mat::Matrix<t, v> operator--(Mat::Matrix<t, v> &mat, int unused) {
	Mat::Matrix<t, v> matRet = mat;
	mat -= (v) 1;
	return matRet;
}

//Prefix
template<size_t t, typename v>
Mat::Matrix<t, v> operator++(Mat::Matrix<t, v> &mat) {
	return mat += (v) 1;
}

//Postfix
template<size_t t, typename v>
Mat::Matrix<t, v> operator++(Mat::Matrix<t, v> &mat, int unused) {
	Mat::Matrix<t, v> matRet = mat;
	mat += (v) 1;
	return matRet;
}


#define MATRIX_FUNC1(name, mat_func) \
template <size_t t, typename v> \
Mat::Matrix<t, v> mat_func(Mat::Matrix<t, v> mat) { \
	return std::move(mat_func##i(mat)); \
} \
template <size_t t, typename v> \
Mat::Matrix<t, v> &mat_func##i(Mat::Matrix<t, v> &mat) { \
	for (size_t i = 0; i < mat.size(); ++i) { \
		mat_func##i(mat[i]); \
	} \
	return mat; \
} \
template <typename v> \
Mat::Matrix<1, v> &mat_func##i(Mat::Matrix<1, v> &mat) { \
	for (size_t i = 0; i < mat.size(); ++i) { \
		mat[i] = name::mat_func(mat[i]); \
	} \
	return mat; \
} \

#define MATRIX_FUNC2(name, mat_func) \
/* Matrix - Scalar */ \
template <size_t t, typename v> \
Mat::Matrix<t, v> mat_func(Mat::Matrix<t, v> mat, const v &val) { \
	return std::move(mat_func##i(mat, val)); \
} \
template <size_t t, typename v> \
Mat::Matrix<t, v> &mat_func##i(Mat::Matrix<t, v> &mat, const v &val) { \
	for (size_t i = 0; i < mat.size(); ++i) { \
		mat_func##i(mat[i], val); \
	} \
	return mat; \
} \
template <typename v> \
Mat::Matrix<1, v> &mat_func##i(Mat::Matrix<1, v> &mat, const v &val) { \
	for (size_t i = 0; i < mat.size(); ++i) { \
		mat[i] = name::mat_func(mat[i], val); \
	} \
	return mat; \
} \
/* Scalar - Matrix */ \
template <size_t t, typename v> \
Mat::Matrix<t, v> mat_func(const v &val, Mat::Matrix<t, v> mat) { \
	return std::move(mat_func##i(val, mat)); \
} \
template <size_t t, typename v> \
Mat::Matrix<t, v> &mat_func##i(const v &val, Mat::Matrix<t, v> &mat) { \
	for (size_t i = 0; i < mat.size(); ++i) { \
		mat_func##i(val, mat[i]); \
	} \
	return mat; \
} \
template <typename v> \
Mat::Matrix<1, v> &mat_func##i(const v &val, Mat::Matrix<1, v> &mat) { \
	for (size_t i = 0; i < mat.size(); ++i) { \
		mat[i] = name::mat_func(val, mat[i]); \
	} \
	return mat; \
} \
/* Matrix - Matrix*/ \
template <size_t t, typename v> \
Mat::Matrix<t, v> &mat_func##i(Mat::Matrix<t, v> &mat, const Mat::Matrix<t, v> &val) { \
	size_t iSize = std::min(mat.size(), val.size()); \
	for (size_t i = 0; i < iSize; ++i) { \
		mat_func##i(mat[i], val[i]); \
	} \
	return mat; \
} \
template <typename v> \
Mat::Matrix<1, v> &mat_func##i(Mat::Matrix<1, v> &mat, const Mat::Matrix<1, v> &val) { \
	size_t iSize = std::min(mat.size(), val.size()); \
	for (size_t i = 0; i < iSize; ++i) { \
		mat[i] = name::mat_func(mat[i], val[i]); \
	} \
	return mat; \
} \
template <size_t t, typename v> \
Mat::Matrix<t, v> mat_func(Mat::Matrix<t, v> mat, const Mat::Matrix<t, v> &val) { \
	return std::move(mat_func##i(mat, val)); \
} \

namespace Mat {
	//using std::sqrt;
	MATRIX_FUNC1(std, sqrt);
	//using std::exp;
	MATRIX_FUNC1(std, exp);
	//using std::isnan;
	MATRIX_FUNC1(std, isnan);
	//using std::isinf;
	MATRIX_FUNC1(std, isinf);
	//using std::real;
	MATRIX_FUNC1(std, real);
	//using std::imag;
	MATRIX_FUNC1(std, imag);
	//using std::abs;
	MATRIX_FUNC1(std, abs);
	//using std::conj;
	MATRIX_FUNC1(std, conj);
	//using std::asin;
	MATRIX_FUNC1(std, asin);
	//using std::sin;
	MATRIX_FUNC1(std, sin);
	//using std::cos;
	MATRIX_FUNC1(std, cos);
	MATRIX_OP(||, Or);
	MATRIX_OP(&&, And);
	namespace cmpr_parts {
		MATRIX_OP(> , GreaterThan);
		MATRIX_OP(< , LessThan);
		MATRIX_OP(>= , GreaterThanEQ);
		MATRIX_OP(<= , LessThanEQ);
		MATRIX_OP(== , Equal);
		MATRIX_OP(!= , NotEqual);
	};
	//using std::pow;
	MATRIX_FUNC2(std, pow);
	const long long int end = -1;
	namespace cmpr_whole {
		template<size_t t, typename TypeFrom, typename TypeTo>
		bool operator<(const Mat::Matrix<t, TypeFrom> &matFrom, const Mat::Matrix<t, TypeTo> &matTo) {
			return compare(matFrom, matTo) < 0;
		}
		template<size_t t, typename TypeFrom, typename TypeTo>
		bool operator<=(const Mat::Matrix<t, TypeFrom> &matFrom, const Mat::Matrix<t, TypeTo> &matTo) {
			return &matFrom == &matTo || compare(matFrom, matTo) <= 0;
		}
		template<size_t t, typename TypeFrom, typename TypeTo>
		bool operator>(const Mat::Matrix<t, TypeFrom> &matFrom, const Mat::Matrix<t, TypeTo> &matTo) {
			return compare(matFrom, matTo) > 0;
		}
		template<size_t t, typename TypeFrom, typename TypeTo>
		bool operator>=(const Mat::Matrix<t, TypeFrom> &matFrom, const Mat::Matrix<t, TypeTo> &matTo) {
			return &matFrom == &matTo || compare(matFrom, matTo) >= 0;
		}
		template<size_t t, typename TypeFrom, typename TypeTo>
		bool operator==(const Mat::Matrix<t, TypeFrom> &matFrom, const Mat::Matrix<t, TypeTo> &matTo) {
			return &matFrom == &matTo || compare(matFrom, matTo) == 0;
		}
		template<size_t t, typename TypeFrom, typename TypeTo>
		bool operator!=(const Mat::Matrix<t, TypeFrom> &matFrom, const Mat::Matrix<t, TypeTo> &matTo) {
			return !(matFrom == matTo);
		}
	};
};

template<typename TypeFrom, typename TypeTo>
int compare(const Mat::Matrix<0, TypeFrom> &matFrom, const Mat::Matrix<0, TypeTo> &matTo) {
	int iRet = 0;
	if (matFrom[0] < matTo[0]) {
		iRet = -1;
	}
	else if (matFrom[0] > matTo[0]) {
		iRet = 1;
	}
	return iRet;
}

template<size_t t, typename TypeFrom, typename TypeTo> 
int compare(const Mat::Matrix<t, TypeFrom> &matFrom, const Mat::Matrix<t, TypeTo> &matTo) {
	if (&matFrom == &matTo) return 0;
	std::vector<Mat::Matrix<0, const TypeFrom> > vecFrom;
	std::vector<Mat::Matrix<0, const TypeTo> > vecTo;
	matFrom.elements(vecFrom);
	matTo.elements(vecTo);
	int iRet = 0;
	size_t tMin = std::min(vecFrom.size(), vecTo.size());
	for (size_t i = 0; i < tMin && iRet == 0; ++i) {
		iRet = compare(vecFrom[i], vecTo[i]);
	}
	if (iRet == 0) {
		if (vecFrom.size() < vecTo.size()) {
			iRet = -1;
		}
		else if (vecFrom.size() > vecTo.size()) {
			iRet = 1;
		}
	}
	return iRet;
}

template<size_t t, typename v>
bool any(const Mat::Matrix<t, v> &mat) {
	for (auto &iter : mat) {
		if (static_cast<bool>(iter)) return true;
	}
	return false;
}

template<size_t t, typename v>
bool all(const Mat::Matrix<t, v> &mat) {
	for (auto &iter : mat) {
		if (!static_cast<bool>(iter)) return false;
	}
	return true;
}

template<size_t t, typename v>
size_t some(const Mat::Matrix<t, v> &mat) {
	size_t tRet = 0;
	for (size_t i = 0; i < mat.size(); ++i) {
		tRet += some(mat[i]);
	}
	return tRet;
}

template<typename v>
size_t some(const Mat::Matrix<1, v> &mat) {
	size_t tRet = 0;
	for (size_t i = 0; i < mat.size(); ++i) {
		if (static_cast<bool>(mat[i])) ++tRet;
	}
	return tRet;
}

template<size_t t, typename TypeFrom, typename TypeTo>
Mat::Matrix<t, TypeTo> convert(const Mat::Matrix<t, TypeFrom> &mat) {
	Mat::Matrix<t, TypeTo> matRet(mat.sizes(), TypeTo());
	std::vector<Mat::Matrix<0, TypeTo> > vecTo;
	matRet.elements(vecTo);
	std::vector<Mat::Matrix<0, const TypeFrom> > vecFrom;
	mat.elements(vecFrom);
	for (size_t i = 0; i < vecTo.size(); ++i) {
		vecTo[i][0] = vecFrom[i][0];
	}

	return matRet;
}

template<size_t t, typename v>
Mat::Matrix<t, v> sum(const Mat::Matrix<t, v> &mat, size_t i) {
	if (i >= t) {
		return mat;
	}
	else if (i == t - 1) {
		std::vector<size_t> vecSize = mat.sizes();
		vecSize[0] = 1;
		Mat::Matrix<t, v> matRet(vecSize, v());
		for (size_t j = 0; j < mat.size(); ++j) {
			matRet[0] += mat[j];
		}
		return matRet;
	}
	else {
		std::vector<size_t> vecSize = mat.sizes();
		vecSize[vecSize.size() - i - 1] = 1;
		Mat::Matrix<t, v> matRet(vecSize, v());
		for (size_t j = 0; j < mat.size(); ++j) {
			matRet[j] += sum(mat[j], i);
		}
		return matRet;
	}
	return mat;
}
template<typename v>
Mat::Matrix<1, v> sum(const Mat::Matrix<1, v> &mat, size_t i) {
	if (i > 0) {
		return mat;
	}
	else {
		Mat::Matrix<1, v> matRet(1, 0.0);
		for (size_t j = 0; j < mat.size(); ++j) {
			matRet[0] += mat[j];
		}
		return matRet;
	}
	return mat;
}


template<size_t t, typename v>
Mat::Matrix<t, v> standardDev(const Mat::Matrix<t, v> &mat, size_t i) {
	if (i >= t) {
		return mat;
	}
	else if (i == t - 1) {
		std::vector<size_t> vecSize = mat.sizes();
		vecSize[0] = 1;
		auto vMean = mean(mat, i);
		Mat::Matrix<t, v> matRet(vecSize, v());
		for (size_t j = 0; j < mat.size(); ++j) {
			matRet[0] += Mat::pow(mat[j] - vMean[j], (v) 2);
		}
		matRet[0] /= (v) mat.size();
		sqrti(matRet);
		return matRet;
	}
	else {
		std::vector<size_t> vecSize = mat.sizes();
		vecSize[vecSize.size() - i - 1] = 1;
		Mat::Matrix<t, v> matRet(vecSize, v());
		for (size_t j = 0; j < mat.size(); ++j) {
			matRet[j] += standardDev(mat[j], i);
		}
		return matRet;
	}
	return mat;
}
template<typename v>
Mat::Matrix<1, v> standardDev(const Mat::Matrix<1, v> &mat, size_t i) {
	if (i > 0) {
		return mat;
	}
	else {
		Mat::Matrix<1, v> matRet(1, 0.0);
		v vMean = mean(mat, i)[0];
		for (size_t j = 0; j < mat.size(); ++j) {
			matRet[0] += pow(mat[j] - vMean, 2);
		}
		matRet[0] /= (v) mat.size();
		sqrti(matRet);
		return matRet;
	}
	return mat;
}


template<size_t t, typename v>
Mat::Matrix<t, v> mean(const Mat::Matrix<t, v> &mat, size_t i) {
	if (i >= t) {
		return mat;
	}
	else if (i == t - 1) {
		std::vector<size_t> vecSize = mat.sizes();
		vecSize[0] = 1;
		Mat::Matrix<t, v> matRet(vecSize, v());
		for (size_t j = 0; j < mat.size(); ++j) {
			matRet[0] += mat[j];
		}
		matRet[0] /= (v)mat.size();
		return matRet;
	}
	else {
		std::vector<size_t> vecSize = mat.sizes();
		vecSize[vecSize.size() - i - 1] = 1;
		Mat::Matrix<t, v> matRet(vecSize, v());
		for (size_t j = 0; j < mat.size(); ++j) {
			matRet[j] += mean(mat[j], i);
		}
		return matRet;
	}
	return mat;
}
template<typename v>
Mat::Matrix<1, v> mean(const Mat::Matrix<1, v> &mat, size_t i) {
	if (i > 0) {
		return mat;
	}
	else {
		Mat::Matrix<1, v> matRet(1, 0.0);
		for (size_t j = 0; j < mat.size(); ++j) {
			matRet[0] += mat[j];
		}
		matRet[0] /= (v)mat.size();
		return matRet;
	}
	return mat;
}


template<size_t t, typename v>
void setElementsToIndex(Mat::Matrix<t, v> &mat) {
	std::vector<Mat::Matrix<0, v> > vec;
	mat.elements(vec);
	for (size_t i = 0; i < vec.size(); ++i) {
		vec[i][0] = i;
	}
}

inline bool canSqueeze(const std::vector<size_t> &vec) {
	bool bRet = false;
	for (const size_t &i : vec) {
		if (i == 1) {
			bRet = true;
			break;
		}
	}
	return bRet;
}

template<size_t t, typename v>
bool squeeze(Mat::Matrix<t - 1, v> &matOut, const Mat::Matrix<t, v> &matIn) {
	std::vector<size_t> vecSizes = matIn.sizes();
	bool bOK = false;
	for (auto iter = vecSizes.begin(); iter != vecSizes.end(); ++iter) {
		if (*iter == 1) {
			bOK = true;
			vecSizes.erase(iter++);
			break;
		}
	}
	if (bOK) {
		matOut = Mat::Matrix<t - 1, v>(vecSizes, v());
		std::vector<Mat::Matrix<0, v> > vecOut;
		matOut.elements(vecOut);
		std::vector<Mat::Matrix<0, const v> > vecIn;
		matIn.elements(vecIn);
		bOK = vecIn.size() == vecOut.size();
		if (bOK) {
			for (size_t i = 0; i < vecIn.size(); ++i) {
				vecOut[i][0] = vecIn[i][0];
				std::cerr << "Setting indx " << i << " to " << vecIn[i][0] << std::endl;
				std::cerr << matOut.element(i) << " " << matIn.element(i) << std::endl;
			}
		}
	}
	return bOK;
}

/* complex to normal matrix */

template<size_t t, typename v>
Mat::Matrix<t, v> convertToReal(const Mat::Matrix<t, std::complex<v> > &matcx) {
	Mat::Matrix<t, v> matReal(matcx.sizes(), v());
	std::vector<Mat::Matrix<0, v> > vecReal;
	std::vector<Mat::Matrix<0, const std::complex<v> > > vecCX;
	matReal.elements(vecReal);
	matcx.elements(vecCX);
	for (size_t i = 0; i < vecCX.size(); ++i) {
		vecReal[i][0] = vecCX[i][0].real();
	}
	return matReal;
}

template<size_t t, typename v>
Mat::Matrix<t, v> convertToImag(const Mat::Matrix<t, std::complex<v> > &matcx) {
	Mat::Matrix<t, v> matImag(matcx.sizes(), v());
	std::vector<Mat::Matrix<0, v> > vecImag;
	std::vector<Mat::Matrix<0, const std::complex<v> > > vecCX;
	matImag.elements(vecImag);
	matcx.elements(vecCX);
	for (size_t i = 0; i < vecCX.size(); ++i) {
		vecImag[i][0] = vecCX[i][0].imag();
	}
	return matImag;
}

template<size_t t, typename v>
Mat::Matrix<t, v> convertToAbs(const Mat::Matrix<t, std::complex<v> > &matcx) {
	Mat::Matrix<t, v> matAbs(matcx.sizes(), v());
	std::vector<Mat::Matrix<0, v> > vecAbs;
	std::vector<Mat::Matrix<0, const std::complex<v> > > vecCX;
	matAbs.elements(vecAbs);
	matcx.elements(vecCX);
	for (size_t i = 0; i < vecCX.size(); ++i) {
		vecAbs[i][0] = std::abs(vecCX[i][0]);
	}
	return matAbs;
}


template<size_t t, typename v>
Mat::Matrix<t - 1, v> max(const Mat::Matrix<t, v> &mat, size_t dim, size_t *pos = nullptr) {
	Mat::Matrix<t - 1, v> matRet;
	if (dim == t) {
		if (mat.size() > 0) {
			matRet = mat[0];
			for (size_t i = 1; i < mat.size(); ++i) {
				maxi(matRet, mat[i]);
			}
		}
	}
	else if (dim < t) {
		matRet = Mat::Matrix<t - 1, v>(mat.size());
		for (size_t i = 0; i < mat.size(); ++i) {
			matRet.at(i) = max(mat[i], dim);
		}
	}
	return matRet;
}

template<typename v>
Mat::Matrix<0, v> max(const Mat::Matrix<1, v> &mat, size_t dim, size_t *pos = nullptr) {
	if (mat.size() > 0) {
		size_t tpos = 0;
		v val = mat[0];
		for (size_t i = 1; i < mat.size(); ++i) {
			if (mat[i] > val) {
				val = mat[i];
				tpos = i;
			}
		}
		if (pos) {
			*pos = tpos;
		}
		return Mat::Matrix<0, v>(val);
	}
	else {
		return Mat::Matrix<0, v>();
	}
}

template<typename v>
void maxi(Mat::Matrix<0, v> &matL, const v &valR) {
	if (*matL < valR) {
		*matL = valR;
	}
}


template<typename v>
void maxi(Mat::Matrix<0, v> &matL, const Mat::Matrix<0, v> &matR) {
	if (*matL < *matR) {
		*matL = *matR;
	}
}

template<size_t t, typename v>
void maxi(Mat::Matrix<t, v> &matL, const Mat::Matrix<t, v> &matR) {
	size_t tMin = std::min(matL.size(), matR.size());
	for (size_t i = 0; i < tMin; ++i) {
		maxi(matL.at(i), matR.at(i));
	}
}



class matrix_iterator_base {
protected:
	template<size_t t, typename v>
	static typename std::vector<Mat::Matrix<t - 1, v> >::iterator begin(Mat::Matrix<t, v> &mat) {
		return mat.vecOfMatrix.begin();
	}
	template<size_t t, typename v>
	static typename std::vector<Mat::Matrix<t - 1, v> >::iterator end(Mat::Matrix<t, v> &mat) {
		return mat.vecOfMatrix.end();
	}
	template<size_t t, typename v>
	static typename std::vector<Mat::Matrix<t - 1, v> > &getVector(Mat::Matrix<t, v> &mat) {
		return mat.vecOfMatrix;
	}
//public:
	template<size_t t, typename v>
	static Mat::Matrix<t, v> *unconst(const Mat::Matrix<t, v> *mat) {
		return const_cast<Mat::Matrix<t, v> *>(mat);
	}
};

/* Iterator classes */
template<size_t t, typename v>
class matrix_iterator : public std::iterator<std::random_access_iterator_tag, v>, public matrix_iterator_base {
public:
	matrix_iterator() {
		pmat = nullptr;
		pmat1 = nullptr;
		indx = -1;
	}

	matrix_iterator(Mat::Matrix<t, v> &mat, int i) : pmat(&mat), indx(i), pmat1(nullptr) {
		updateCache();
	}

	matrix_iterator(Mat::Matrix<t, v> &mat) : pmat(&mat), indx(-1), pmat1(nullptr) {}

	bool updateCache() {
		bool bOK = pmat && indx >= 0;
		if (bOK) {
			size_t i = indx;
			bOK = pmat->elementMat1(i, pmat1);
			if (bOK) {
				iter = begin(*pmat1) + i;
			}
		}
		return bOK;
	}

	void next() {
		if (pmat1) {
			++indx;
			++iter;
			if (iter == end(*pmat1)) {
				if (!updateCache()) {
					pmat1 = nullptr;
				}
			}
		}
	}

	void prev() {
		if (indx > 0) {
			--indx;
			if (pmat1 == nullptr || iter == begin(*pmat1)) {
				updateCache();
			}
			else {
				--iter;
			}
		}
	}

	v &operator*() {
		return *(*iter);
	}

	v *operator->() {
		return iter->get();
	}

	bool operator==(const matrix_iterator &mi) const {
		return this == &mi || (pmat == mi.pmat && pmat1 == mi.pmat1 &&
			(pmat1 == nullptr || indx == mi.indx));
	}

	bool operator!=(const matrix_iterator &mi) {
		return !(*this == mi);
	}

	matrix_iterator &operator++() {
		next();
		return *this;
	}

	matrix_iterator operator++(int unused) {
		auto ret = *this;
		next();
		return ret;
	}

	matrix_iterator &operator--() {
		prev();
		return *this;
	}

	matrix_iterator operator--(int unused) {
		auto ret = *this;
		prev();
		return ret;
	}


protected:
	Mat::Matrix<t, v> *pmat;
	int indx;
	typename std::vector<Mat::Matrix<0, v> >::iterator iter;
	Mat::Matrix<1, v> *pmat1;
};

template<size_t t, typename v>
class const_matrix_iterator : protected matrix_iterator<t,v> {
public:
	const_matrix_iterator() : matrix_iterator() {}

	const_matrix_iterator(const Mat::Matrix<t, v> &mat, int i) : matrix_iterator(*matrix_iterator_base::unconst(&mat), i) {}

	const_matrix_iterator(const Mat::Matrix<t, v> &mat) : matrix_iterator(*matrix_iterator_base::unconst(&mat)) {}
	const v &operator*() {
		return *(*iter);
	}

	const v *operator->() {
		return iter->get();
	}
	using matrix_iterator::operator++;
	using matrix_iterator::operator--;
	using matrix_iterator::operator==;
	using matrix_iterator::operator!=;
	bool operator==(const const_matrix_iterator &cmi) {
		return matrix_iterator::operator==(cmi);
	}
	bool operator!=(const const_matrix_iterator &cmi) {
		return !operator==(cmi);
	}
};

namespace std {
	template <size_t t, typename v> class numeric_limits<Mat::Matrix<t, v> > : public numeric_limits<v> {
	public:
		static Mat::Matrix<t, v> min() noexcept { return Mat::Matrix<t, v>(std::vector<size_t>(t, 1), std::numeric_limits<v>::min()); }
		static Mat::Matrix<t, v> max() noexcept { return Mat::Matrix<t, v>(std::vector<size_t>(t, 1), std::numeric_limits<v>::max()); }
		static Mat::Matrix<t, v> quiet_NaN() noexcept { return Mat::Matrix<t, v>(std::vector<size_t>(t, 1), std::numeric_limits<v>::quiet_NaN()); }
	};
};




#endif