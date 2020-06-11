#pragma once
template <class T>
class Sequence {
private:
	int size = 0;

public:
	Sequence() = default;
	virtual ~Sequence() {};

	virtual T GetFirst() const = 0;
	virtual T GetLast() const = 0;
	virtual T Get(int index) const = 0;
	virtual int GetLength() const = 0;

	virtual T& operator [] (int index) const = 0;

	virtual void Append(T values) = 0;
	virtual void Prepend(T values) = 0;
	virtual void InsertAt(T values, int index) = 0;
	virtual void Print() = 0;
	virtual void Enter() = 0;
	virtual Sequence<T>* Concat(Sequence<T>* list) const = 0;
	virtual Sequence<T>* GetSubSequence(int startIndex, int endIndex) const = 0;

};
