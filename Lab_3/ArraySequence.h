#pragma once
#include "Dynamic_Array.h"
#include "Sequence.h"

template <class T>
class ArraySequence : public Sequence<T> {
protected:
	DynamicArray<T>* mas = 0;
	int size = 0;

public:
	ArraySequence() : Sequence<T>() {
		mas = new DynamicArray<T>(0);
		this->size = 0;
	}

	ArraySequence(int size) : Sequence<T>() {
		mas = new DynamicArray<T>(size);
		this->size = size;
	}

	ArraySequence(T* values, int size) :Sequence<T>() {
		mas = new DynamicArray<T>(values, size);
		this->size = size;
	}

	virtual T& operator [](int index) const {
		return  mas->operator[](index);
	}

	virtual ~ArraySequence() = default;

	virtual T GetFirst() const override {
		if (this->size == 0)
			throw std::out_of_range(IndexOutOfRange);

		return mas->Get(0);
	}

	virtual T Get(int index) const override {
		if (index < 0 || index >= size)
			throw std::out_of_range(IndexOutOfRange);

		return mas->Get(index);
	}

	virtual T GetLength() const override {
		return size;
	}

	virtual T GetLast() const override {
		return mas->Get(this->size - 1);
	}

	virtual void Prepend(T values) override {
		mas->Resize(size + 1);
		size = size + 1;
		mas->Set(size - 1, values);
	}

	virtual void Append(T values) override {
		mas->Resize(size + 1);
		T data1 = mas->Get(0);
		T data2 = 0;

		for (int i = 0; i < this->size; i++) {
			data2 = data1;
			data1 = mas->Get(i + 1);
			mas->Set(i + 1, data2);
		}

		mas->Set(0, values);
	}

	virtual void InsertAt(T values, int index) override {
		if (index < 0 || index >= size) throw std::out_of_range(IndexOutOfRange);

		mas->Set(index, values);
	}

	virtual Sequence<T>* GetSubSequence(int startIndex, int endIndex) const override {
		if (startIndex < 0 || startIndex >= size || endIndex < 0 || endIndex >= size) throw std::out_of_range(IndexOutOfRange);

		Sequence<T>* GetSubSequence = new ArraySequence();
		for (int i = 0; i < (endIndex - startIndex + 1); i++)
			GetSubSequence->Prepend(mas->Get(startIndex + i));

		return GetSubSequence;
	}

	virtual ArraySequence <T>* Concat(Sequence<T>* mas2) const override {
		ArraySequence <T>* newmas = new ArraySequence();

		for (int i = 0; i < this->size; i++)
			newmas->Prepend(mas->Get(i));

		for (int i = 0; i < mas2->GetLength(); i++)
			newmas->Prepend(mas2->Get(i));

		return newmas;
	}

	virtual void Print() override {
		mas->Print();
	}

	virtual void Enter() override {
		mas->EnterMas();
	}
};

int Test_Array_Sequence() {
	int* pr{ new int[5] {11,12,13,14,15} };
	ArraySequence<int> mas1(pr, 5);

	int* priv{ new int[3] {23,16,4} };
	ArraySequence<int> mas2(priv, 3);

	if (mas1[1] == 12 && mas1[4] == 15)
		std::cout << "Test Operator []: success" << "\n";
	else {
		std::cout << "Test Operator []: fail" << "\n";
	};

	if (mas1.GetFirst() == 11)
		std::cout << "Test GetFirst: success" << "\n";
	else {
		std::cout << "Test GetFirst: fail" << "\n";
	};

	if (mas1.GetLast() == 15)
		std::cout << "Test GetLast: success" << "\n";
	else {
		std::cout << "Test GetLast: fail" << "\n";
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

	mas1.Append(76);
	if (mas1.GetFirst() == 76)
		std::cout << "Test Append: success" << "\n";
	else {
		std::cout << "Test Append: fail" << "\n";
	};

	mas1.Prepend(8);
	if (mas1.GetLast() == 8)
		std::cout << "Test Prepend: success" << "\n";
	else {
		std::cout << "Test Prepend: fail" << "\n";
	};


	mas1.GetSubSequence(2, 5);
	if (mas1[2] == 12 && mas1[3] == 13 && mas1[4] == 14 && mas1[5] == 8)
		std::cout << "Test GetSubSequence: success" << "\n";
	else {
		std::cout << "Test GetSubSequence: fail" << "\n";
	};

	/*mas1.Resize(7);
	if (mas1.GetLength() == 7)
		std::cout << "Test Resize: success" << "\n";
	else {
		std::cout << "Test Resize: fail" << "\n";
	};*/

	int data = 44;
	mas1.InsertAt(data, 4);
	if (mas1[4] == 44)
		std::cout << "Test InsertAt: success" << "\n";
	else {
		std::cout << "Test InsertAt: fail" << "\n";
	};

	ArraySequence<int>* p2 = mas1.Concat(&mas2);
	if (p2->Get(0) == 76 && p2->Get(1) == 11 && p2->Get(2) == 12 && p2->Get(3) == 13
		&& p2->Get(4) == 44 && p2->Get(5) == 8 && p2->Get(6) == 23 && p2->Get(7) == 16
		&& p2->Get(8) == 4)
		std::cout << "Test Concat: success" << "\n";
	else {
		std::cout << "Test Concat: fail" << "\n";
	};


	DynamicArray<int> mas3(2);
	if (mas3[0] == -842150451 && mas3[1] == -842150451)
		std::cout << "Test Creation constructor: success" << "\n";
	else {
		std::cout << "Test Creation constructor: fail" << "\n";
	};
	//-842150451

	delete[7] pr;
	delete[3] priv;

	return 0;
}