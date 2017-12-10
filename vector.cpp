#pragma once
#include "stdafx.h"

namespace sort {
	template <typename T>
	class vector {
	private:
		int n_;
		T *arr_;
	public:	
		vector() {
			n_ = 0;
			arr_ = NULL;
		}

		vector(int n) {
			n_ = n;
			arr_ = new T[n];
		}

		void resize(int n) {
			n_ = n;
			delete[] arr_;
			arr_ = new T[n];
		}

		const int size() {
			return n_;
		}

		/*const T& operator[](int n) {
			return arr[n];
		}*/

		T& operator[](int n) {
			if (n < 0 || n >= n_)
				return arr_[n_ - 1];
			return arr_[n];
		}

		vector& operator=(vector &from) {
			//int n = from.size() > n_ ? from.size() : n_;

			for (int i = 0; i < n_; i++) {
				arr_[i] = from[i];
			}
			return *this;
		}

		bool operator!=(vector &arr) {
			for (int i = 0; i < this->size(); i++) {
				if (arr_[i] != arr[i])
					return true;
			}
			return false;
		}

		void clear() {
			delete[] arr_;
			arr_ = NULL;
			n_ = 0;
		}
	
		~vector() {
			delete[] arr_;
		}
	};
}