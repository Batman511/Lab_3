#pragma once
#include <stdexcept>
#include <exception>

constexpr auto IndexOutOfRange = "Index out of range";


template <class T>
class DynamicArray {
private:
	T* mas = nullptr;
	int size = 0;

public:
	//конструкторы
	DynamicArray(const int size) {
		this->size = size;
		this->mas = new T[size];
	}

	DynamicArray(const T* mas, const int size) {
		this->size = size;
		this->mas = new T[size];

		if (size < 0) throw std::length_error("Index is negative");

		for (int i = 0; i < size; i++) this->mas[i] = mas[i];
	}

	//копирующий конструктор
	DynamicArray(DynamicArray<T> const& dynamic_array) :DynamicArray(T* dynamic_array->mas, dynamic_array->size)
	{}

	DynamicArray<T>& operator = (DynamicArray<T>& dynamic_array) {
		T* new_mas = new T[dynamic_array.GetSize()];
		for (int i = 0; i < dynamic_array.size; i++) new_mas[i] = dynamic_array.mas[i];

		this->size = dynamic_array.size;
		this->mas = new_mas;

		return (*this);
	}

	//деструктор
	~DynamicArray() {
		delete[] mas;
		size = 0;
	}

	//получить элемент массива
	T& operator[] (int index) {
		if (index < 0 || index >= this->size) throw std::out_of_range(IndexOutOfRange);

		return mas[index];
	}

	T Get(int index) {
		if (index < 0 || index >= size)
			throw std::out_of_range(IndexOutOfRange);

		return mas[index];
	}

	//получить длину массива
	int GetLength() const {
		return size;
	}

	//задать элемент по индексу
	void Set(int index, T value) {
		if (index < 0 || index >= size) throw std::out_of_range(IndexOutOfRange);

		mas[index] = value;
	}

	//изменить размер массива
	void Resize(int new_size) {
		if (new_size < 0) throw std::length_error("Index is negative");

		int size2 = new_size < size ? new_size : size;
		T* new_mas = new T[new_size];

		size = new_size;
		for (int i = 0; i < size2; i++) new_mas[i] = mas[i];
		delete[] mas;
		mas = new_mas;
	}

	//вывод массива
	void Print() {
		for (int i = 0; i < size; i++)
			std::cout << mas[i] << " ";
		std::cout << "\n";
	}

	//ввод массива
	void EnterMas() {
		std::cout << "Enter size of the Array: ";
		int count;
		std::cin >> count;
		Resize(count);

		for (int i = 0; i < count; i++) {
			int data;
			std::cout << "Element " << i << " : ";
			std::cin >> data;
			Set(i, data);
		}
	}
};

int Test_Dynamic_Array() {
	int* pr{ new int[5] {11,12,13,14,15} };
	DynamicArray<int> mas1(pr, 5);

	if (mas1[1] == 12 && mas1[4] == 15)
		std::cout << "Test Operator []: success" << "\n";
	else {
		std::cout << "Test Operator []: fail" << "\n";
	};

	if (mas1.GetLength() == 5)
		std::cout << "Test GetSize: success" << "\n";
	else {
		std::cout << "Test GetSize: fail" << "\n";
	};

	if (mas1.Get(3) == 14)
		std::cout << "Test Get: success" << "\n";
	else {
		std::cout << "Test Get: fail" << "\n";
	};

	mas1.Resize(7);
	if (mas1.GetLength() == 7)
		std::cout << "Test Resize: success" << "\n";
	else {
		std::cout << "Test Resize: fail" << "\n";
	};

	int data = 44;
	mas1.Set(5, data);
	if (mas1[5] == 44)
		std::cout << "Test Set: success" << "\n";
	else {
		std::cout << "Test Set: fail" << "\n";
	};

	DynamicArray<int> mas2(2);
	if (mas2[0] == -842150451 && mas2[1] == -842150451)
		std::cout << "Test Creation constructor: success" << "\n";
	else {
		std::cout << "Test Creation constructor: fail" << "\n";
	};
	//-842150451

	delete[5] pr;

	return 0;
}