#pragma once
#include <stdexcept>
#include <exception>

constexpr auto IndexOutOfRange = "Index out of range";

template <class T>
class LinkedList {

private:
	struct Node
	{
		T values = 0;
		Node* next = nullptr;
	};

	Node* head = nullptr;
	int size = 0;

public:
	//конструкторы
	LinkedList() : size(0), head(nullptr)
	{};

	LinkedList(const T* values, const int size) : LinkedList()
	{
		if (size < 0) throw std::length_error("Index is negative");
		if (size == 0) throw std::length_error("Node is empty");

		Node* tail = new Node{ *values,nullptr };
		head = tail;

		for (size_t i = 1; i < size; i++) {
			Node* body = new Node{ *(values + i),nullptr };
			tail->next = body;
			tail = body;
		}

		this->size = size;
	}

	//копирующий конструктор
	LinkedList(LinkedList <T> const& list) {
		Node* body{ head };
		Node* List{ body };

		for (size_t i = 1; i < size; i++, body = body->next) {
			List = new Node{ body->values,List };
		}

		this->size = size;
	}

	//деструктор
	~LinkedList() {
		while (this->head != nullptr) {
			Node* body{ head->next };
			delete[] head;
			this->head = body;
		}

		delete[] this->head;
	}

	//вывод первого элемента списка
	T GetFirst() {
		if (size == 0) throw std::length_error(IndexOutOfRange);
		//std::cout << head->values;

		return head->values;
	}

	//вывод последнего элемента списка
	T GetLast() {
		if (size == 0) throw std::length_error(IndexOutOfRange);
		Node* body{ head };

		for (size_t i = 0; i < size - 1; i++) body = body->next;
		//std::cout << body->values;

		return body->values;
	}

	//получение элемента по индексу
	T Get(int index) {
		if (index < 0 || index >= size) throw std::length_error(IndexOutOfRange);
		Node* body{ head };

		for (size_t i = 0; i < index; i++) body = body->next;
		return body->values;
	}

	T& operator [] (int index) {
		if (index < 0 || index >= size) throw std::length_error(IndexOutOfRange);
		Node* body{ head };

		for (size_t i = 0; i < index; i++) body = body->next;

		return body->values;
	}

	//Получить список всех элементов
	LinkedList<T>* GetSubList(int startIndex, int endIndex) {
		if (startIndex < 0 || endIndex < 0 || startIndex >= size || endIndex >= size || startIndex > endIndex)
			throw std::length_error(IndexOutOfRange);
		Node* body{ head };

		for (size_t i = 0; i < startIndex; i++) body = body->next;

		LinkedList<T>* newNode = new LinkedList<T>;

		for (size_t i = startIndex; i < endIndex + 1; i++) {
			newNode->Prepend(body->values);
			body = body->next;
		}

		newNode->size = endIndex - startIndex + 1;

		return newNode;
	}

	//длина списка
	int GetLength() {
		return size;
	}

	//добавление элемента в начало списка
	void Append(T data) {
		head = new Node{ data,head };

		++size;
	}

	//добавление элемента в конец списка
	void Prepend(T data) {
		if (head == nullptr)  head = new Node{ data,head };
		else {
			Node* body{ head };
			for (size_t i = 1; i < size; i++) body = body->next;
			body->next = new Node{ data,nullptr };
		}

		++size;
	}

	//Вставляет элемент в заданную позицию
	void InsertAt(T data, int index) {
		if (index < 0 || index >= size) throw std::length_error(IndexOutOfRange);
		Node* body{ head };

		for (size_t i = 0; i < index - 1; i++) body = body->next;

		Node* newNode = new Node{ data,body->next };
		body->next = newNode;

		this->size += 1;
	}

	//Соединене двух списков
	LinkedList<T>* Concat(LinkedList<T>* list) {
		Node* body{ this->head };
		LinkedList<T>* newList = new LinkedList<T>();

		for (int i = 0; i < this->size; i++) {
			newList->Prepend(body->values);
			body = body->next;
		}

		Node* body2{ list->head };
		for (int i = this->size; i < (list->size + this->size); i++) {
			newList->Prepend(body2->values);
			body2 = body2->next;
		}

		newList->size = this->size + list->size;

		return newList;
	}

	//Вывод списка
	void Print() {
		for (int i = 0; i < size; i++) {
			std::cout << Get(i) << " ";
		};
		std::cout << "\n";
	}

	//Ввод списка
	void EnterList() {
		std::cout << "Enter size of the List: ";
		int count;
		std::cin >> count;

		for (int i = 0; i < count; i++) {
			T data;
			std::cout << "Element " << i << " : ";
			std::cin >> data;
			Prepend(data);
		}

	}
};

int Test_Linked_list() {
	int* a{ new int[6] {1,4,5,7,4,17} };
	int* b{ new int[5] {5,11,8,9,2} };

	LinkedList<int> list1{ a,6 };
	LinkedList<int> list2{ b,5 };

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
	if (list1[0] == 5)
		std::cout << "Test Append: success" << "\n";
	else {
		std::cout << "Test Append: fail" << "\n";
	};

	list2.Prepend(9);
	if (list2[5] == 9)
		std::cout << "Test Prepend: success" << "\n";
	else {
		std::cout << "Test Prepend: fail" << "\n";
	};

	LinkedList<int>* p = list2.GetSubList(1, 4);
	if (p->Get(0) == 11 && p->Get(1) == 8 && p->Get(2) == 9 && p->Get(3) == 2)
		std::cout << "Test GetSubList: success" << "\n";
	else {
		std::cout << "Test GetSubList: fail" << "\n";
	};

	list2.InsertAt(3, 2);
	if (list2[2] == 3)
		std::cout << "Test InsertAt: success" << "\n";
	else {
		std::cout << "Test InsertAt: fail" << "\n";
	};

	LinkedList<int>* p2 = list1.Concat(&list2);
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