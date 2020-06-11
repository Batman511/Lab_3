#pragma once
#include "Linked_List.h"
#include "Sequence.h"

template <class T>
class LinkedListSequence : public Sequence<T> {
protected:
	LinkedList<T>* linked_list;

public:

	LinkedListSequence() : Sequence<T>() {
		linked_list = new LinkedList<T>();
	}

	LinkedListSequence(T* values, int size) : Sequence<T>() {
		linked_list = new LinkedList<T>(values, size);
	}

	virtual ~LinkedListSequence() = default;

	virtual T GetFirst() const override {
		if (linked_list->GetLength() == 0) throw std::out_of_range(IndexOutOfRange);

		return linked_list->GetFirst();
	}

	virtual T GetLast() const override {
		if (linked_list->GetLength() == 0) throw std::out_of_range(IndexOutOfRange);

		return linked_list->GetLast();
	}

	virtual int GetLength()const {
		return linked_list->GetLength();
	}

	virtual T Get(int index) const override {
		if (index < 0 || index >= linked_list->GetLength()) throw std::out_of_range(IndexOutOfRange);

		return linked_list->Get(index);
	}

	virtual T& operator [](int index) const {
		return  linked_list->operator[](index);
	}

	virtual Sequence<T>* GetSubSequence(int startIndex, int endIndex) const override {
		if (startIndex < 0 || endIndex < 0 || startIndex >= linked_list->GetLength() || endIndex >= linked_list->GetLength())
			throw std::out_of_range(IndexOutOfRange);

		LinkedList<T>* subList = linked_list->GetSubList(startIndex, endIndex);
		Sequence<T>* subSequence = new LinkedListSequence<T>();

		for (int i = 0; i < subList->GetLength(); i++)
			subSequence->Prepend(subList->Get(i));

		return subSequence;
	}

	virtual LinkedListSequence<T>* Concat(Sequence<T>* linked_list2) const  override {
		LinkedListSequence<T>* ConcatSequence = new LinkedListSequence<T>();

		for (int i = 0; i < linked_list->GetLength(); i++)
			ConcatSequence->Prepend(linked_list->Get(i));

		for (int i = 0; i < linked_list2->GetLength(); i++)
			ConcatSequence->Prepend(linked_list2->Get(i));

		/*for (int i=0; i < ConcatSequence->GetLength(); i++) {
			std::cout << ConcatSequence->Get(i) << " ";
		};*/


		return ConcatSequence;
	}

	virtual void Append(T values) override {
		return linked_list->Append(values);
	}

	virtual void Prepend(T values) override {
		return linked_list->Prepend(values);
	}

	virtual void InsertAt(T values, int index) {
		if (index < 0 || index >= linked_list->GetLength()) throw std::out_of_range(IndexOutOfRange);

		return linked_list->InsertAt(values, index);
	}

	virtual void Print() override {
		return linked_list->Print();
	}

	virtual void Enter() override {
		return linked_list->EnterList();
	}

};

int Test_List_Sequence() {
	int* a{ new int[6] {1,4,5,7,4,17} };
	LinkedListSequence<int> list1{ a,6 };

	int* b{ new int[5] {5,11,8,9,2} };
	LinkedListSequence<int> list2{ b,5 };

	if (list1.GetFirst() == 1)
		std::cout << "Test GetFirst: success" << "\n";
	else {
		std::cout << "Test GetFirst: fail" << "\n";
	};

	if (list1.GetLast() == 17)
		std::cout << "Test GetLast: success" << "\n";
	else {
		std::cout << "Test GetLast: fail" << "\n";
	};

	if (list1[2] == 5 && list1[5] == 17)
		std::cout << "Test Operator []: success" << "\n";
	else {
		std::cout << "Test Operator []: fail" << "\n";
	};

	if (list1.GetLength() == 6)
		std::cout << "Test GetLenght: success" << "\n";
	else {
		std::cout << "Test GetLenght: fail" << "\n";
	};

	if (list1.Get(3) == 7)
		std::cout << "Test Get: success" << "\n";
	else {
		std::cout << "Test Get: fail" << "\n";
	};

	list1.Append(5);
	if (list1.Get(0) == 5)
		std::cout << "Test Append: success" << "\n";
	else {
		std::cout << "Test Append: fail" << "\n";
	};

	list2.Prepend(9);
	if (list2.Get(5) == 9)
		std::cout << "Test Prepend: success" << "\n";
	else {
		std::cout << "Test Prepend: fail" << "\n";
	};

	Sequence<int>* p = list2.GetSubSequence(1, 4);
	if (p->Get(0) == 11 && p->Get(1) == 8 && p->Get(2) == 9 && p->Get(3) == 2)
		std::cout << "Test GetSubList: success" << "\n";
	else {
		std::cout << "Test GetSubList: fail" << "\n";
	};

	list2.InsertAt(3, 2);
	if (list2.Get(2) == 3)
		std::cout << "Test InsertAt: success" << "\n";
	else {
		std::cout << "Test InsertAt: fail" << "\n";
	};

	LinkedListSequence<int>* p2 = list1.Concat(&list2);
	if (p2->Get(0) == 5 && p2->Get(1) == 1 && p2->Get(2) == 4 && p2->Get(3) == 5
		&& p2->Get(4) == 7 && p2->Get(5) == 4 && p2->Get(6) == 17 && p2->Get(7) == 5
		&& p2->Get(8) == 11 && p2->Get(9) == 3 && p2->Get(10) == 8 && p2->Get(11) == 9
		&& p2->Get(12) == 2 && p2->Get(13) == 9)
		std::cout << "Test Concat: success" << "\n";
	else {
		std::cout << "Test Concat: fail" << "\n";
	};

	delete[7] a;
	delete[6] b;

	return 0;
}