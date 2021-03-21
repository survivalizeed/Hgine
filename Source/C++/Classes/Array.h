

#pragma once

#include "../Functional/includes.h"

extern sur::Vec2 _window_size;


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

		//Set
		inline void operator ()(int x, int y, T what) {
			if (typeid(T) == typeid(DWORD)) {
				y = sizeSep.y - y;
				y--;
			}
			if (x < 0 || y < 0 || x > _window_size.x - 1|| y > _window_size.y - 1) return;
			arr[x + sizeSep.x * y] = what;
		}

		//Get
		inline T operator ()(int x, int y) {
			if (typeid(T) == typeid(DWORD)) {
				y = sizeSep.y - (y);
			}
			if (x < 0 || y < 0 || x > _window_size.x - 1|| y > _window_size.y - 1) return 0;
			return arr[x + sizeSep.x * y];
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
