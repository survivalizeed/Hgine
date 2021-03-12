

#pragma once

#include "includes.h"


namespace analyses {
	template <typename T>
	class Array {

	private:
		T* arr = nullptr;
		size_t size = 0;
		sur::Vec2 sizeSep;
	public:
		Array() = default;

		explicit Array(T* arrptr, sur::Vec2 size)
			: arr(arrptr), size(size.x* size.y), sizeSep(size) {}

		T* GetPtr() {
			return arr;
		}

		inline T operator ()(int x, int y) {
			if (typeid(T) == typeid(DWORD)) {
				y = sizeSep.y - (y);
				x--;
			}
			return arr[x + sizeSep.x * y];
		}

		//Set
		inline void operator ()(int x, int y, T what) {
			if (typeid(T) == typeid(DWORD)) {
				y = sizeSep.y - y;
				x--;
			}
			arr[x + sizeSep.x * y] = what;
		}


		void operator ()(T* arrptr, sur::Vec2 size) {
			arr = arrptr;
			sizeSep = size;
			this->size = size.x * size.y;
		}

		void FillWith(T what) {
			T* p = arr;
			for (size_t i = 0; i < size; i++, p++) {
				*p = what;
			}
		}

		void Set(int index, T what) {
			arr[index] = what;
		}

		inline void ST(int x, int y, T what){
			if (typeid(T) == typeid(DWORD)) {
				y = sizeSep.y - (y);
				x--;
			}
			arr[x + sizeSep.x * y] = what;
		}

		T Get(int index) const {
			return arr[index];
		}

		T Get2d(int x, int y) const{
			return arr[x + sizeSep.x * y];
		}

		size_t GetArraySize() const {
			return size;
		}

		size_t GetWrittenCellCount() const {
			size_t counter = 0;
			T* p = arr;
			for (size_t i = 0; i < size; i++, p++) {
				if (*p != 0) {
					counter++;
				}
			}
			return counter;
		}
	};
}
