#pragma once
#include "Sequence.h"
//#include "Dynamic_Array.h"
//#include "Linked_List.h"
//#include "ArraySequence.h"
#include "List_Sequence.h"
#include <string>

#define TN TreeNode<T>*

template<class T>
class TreeNode {
public:
	T values;
	TreeNode* left;
	TreeNode* right;

	//создание звена
	TreeNode(T value) {
		this->values = value;
		this->left = nullptr;
		this->right = nullptr;
	}

	//получение элемента
	T Get() {
		return this->values;
	}
};

template<class T>
class BinaryTree {
public:
	TN root;

	BinaryTree() {
		this->root = nullptr;
	}

	BinaryTree(TN root) {
		this->root = root;
	}

	TN GetRoot() {
		return root;
	}

	//вставить элемент
	void Insert(T value) {
		TN ptr = root;
		TN end = nullptr;
		TN InsertNode = new TreeNode<T>(value);

		while (ptr != nullptr){
			end = ptr;
			if (value <= ptr->Get()) { ptr = ptr->left; }
			else ptr = ptr->right;
		}

		if (end == nullptr) root = InsertNode;
		else {
			if (value <= end->Get()) { end->left = InsertNode; }
			else end->right = InsertNode;
		}
	}

	//поиск элемента
	TN FindNode(TN Node, T value) {
		if (root == nullptr) throw std::exception("Empty");
		if (Node == nullptr) throw std::exception("Not Found");
		if (Node->values == value) { return Node; }
		else if (value <= Node->values) { return FindNode(Node->left, value); }
		else if (value > Node->values) {return FindNode(Node->right, value);}
	}

	TN FindNode(T value) {
		return FindNode(this->root, value);
	}

	//удаление элемента (удалять можно только листья)
	bool DeleteNode(T value) {
		return DeleteNode(this->root, value);
	}

	bool DeleteNode(TN Node, T value) {
		if (Node == nullptr) return false;

		TN tmp = Node;
		TN end = nullptr;
		bool check;


		if (tmp->left == nullptr && tmp->right == nullptr) {
			if (tmp->values == value) {
				delete tmp;
				return true;
			}
			else return false;
		}

		while (tmp != nullptr && tmp->values != value) {
			if (value <= tmp->values) {
				check = false;
				end = tmp;
				tmp = tmp->left;
			}
			else {
				if (value > tmp->values) {
					check = true;
					end = tmp;
					tmp = tmp->right;
				}
			}
		}

		if (tmp == nullptr) {
			throw std::exception("Empty");
			return false;
		}
		else {
			if (tmp->right == nullptr && tmp->left == nullptr) {
				if (!check) {
					end->left = nullptr;
				}
				else end->right = nullptr;

				delete tmp;
				return true;
			}
			else {
				if (tmp->right == nullptr && tmp->left == nullptr) {
					if (end->left == tmp) {
						end->left = tmp->right;
					}
					else end->right = tmp->right;

					delete tmp;
					return true;
				}
				else {
					if (tmp->left != nullptr && tmp->right != nullptr) {
						TN tmp2 = nullptr;
						end = tmp;
						tmp2 = tmp;
						check = true;
						tmp = tmp->right;
						while (tmp->left != nullptr) {
							tmp2 = tmp;
							check = false;
							tmp = tmp->left;
						}
						end->values = tmp->values;

						if (tmp->right != nullptr) {
							if (check) {
								tmp2->right = tmp->right;
							}
							else tmp2->left = tmp->right;

							delete tmp;
							return true;
						}
						else {
							if (check) {
								tmp2->right = nullptr;
							}
							else tmp2->left = nullptr;

							delete tmp;
							return true;
						}
					}
				}
			}
		}

	}

	//ввод дерева
	void EnterTree() {
		std::cout << "Enter size of the Tree: ";
		int count;
		std::cin >> count;

		for (int i = 0; i < count; i++) {
			T data;
			std::cout << "Element " << i << " : ";
			std::cin >> data;
			Insert(data);
		}	
	}

	//вывод дерева
	void printTree(TN Node, int lvl) {
		if (Node != nullptr) {
			//throw std::exception("Empty");
		
			printTree(Node->right, lvl + 1);
			for (int i = 0; i < lvl - this->height(); i++) std::cout << "    ";
				std::cout << "[" << lvl - this->height() << "]";
				std::cout << Node->Get() << "\n";
			printTree(Node->left, lvl + 1);
		}
	}

	//высота дерева
	static int height(TN Node) {
		int L,R;

		if (Node->left == nullptr && Node->right == nullptr) { return 0; 
		}
		else {
			if (Node->left != nullptr) {
				L = height(Node->left) + 1;
			}
			else L = 0;

			if (Node->right != nullptr) {
				R = height(Node->right) + 1;
			}
			else R = 0;
		}
		if (L > R) {
			return L;
		}
		else return R;

	}

	int height() {
		return height(this->root);
	}

	//Map
	void Map(T(*foo)(T), TN Node) {
		Node->values = foo(Node->values);
		if (Node->left != nullptr) Map(foo, Node->left);
		if (Node->right != nullptr) Map(foo, Node->right);
	}

	void Map(T(*foo)(T)) {
		if (this->root == nullptr) { std::cout << "Empty" << "\n";
		}
		else this->Map(foo, this->root);
	}

	//получение поддерева
	BinaryTree<T>* SubTree(T value) {
		TN newNode = this->FindNode(value);
		BinaryTree<T>* newTree = new BinaryTree<T>(newNode);

		return newTree;
	}

	//проверка на вхождение элемента
	bool CheckElement(T value) {
		TN tmp = this->root;

		while (tmp != nullptr) {
			if (value < tmp->Get()) {
				tmp = tmp->left;
			}
			else {
				if (value > tmp->Get()) {
					tmp = tmp->right;
				}
				else return true;
			}
		}

		if (tmp == nullptr) return false;
	}

	//проверка на вхождение поддерева
	bool FindSubTree(BinaryTree<T>* subtree) {
		if (subtree->GetRoot() == nullptr && this->GetRoot() != nullptr)
			return false;
		if (subtree->GetRoot() == this->GetRoot())
			return true;
		if (this->CheckElement(subtree->GetRoot()->values)) {
			BinaryTree<T>* checktree = this->SubTree(subtree->GetRoot()->values);
			return checktree->Equality(subtree);
		}
		else return false;
	}

	//проверка на экввалентность деревьев
	bool Equality(BinaryTree<T>* tree)
	{
		if ((this->root != nullptr && tree->GetRoot() == nullptr) || (this->root == nullptr && tree->GetRoot() != nullptr)){
			return false;
		}
		if (this->root == nullptr && tree->GetRoot() == nullptr){
			return true;
		}

		bool res = true;
		TN ThisRight = this->root->right;
		TN ThisLeft = this->root->left;
		TN TreeRight = tree->GetRoot()->right;
		TN TreeLeft = tree->GetRoot()->left;

		if (ThisLeft != nullptr && TreeLeft != nullptr) {
			res = res && this->SubTree(ThisLeft->values)->Equality(tree->SubTree(TreeLeft->values));
		}
		else if (TreeLeft == nullptr && TreeRight == nullptr) {}
		else return false;

		if (ThisRight != nullptr && TreeRight != nullptr) {
			res = res && this->SubTree(ThisRight->values)->Equality(tree->SubTree(TreeRight->values));
		}
		else if (ThisLeft == nullptr && ThisRight == nullptr) {}
		else return false;

		return res;
	}

	//запись обхода в последовательность
	static Sequence<TN>* Firmware(TN Node, std::string str)
	{
		Sequence<TN>* list = nullptr;
		TN* array;
		for (size_t i = 0; i < str.length(); i++){
			switch (str[i]){
			case 'N':
				if (list == nullptr){
					list = new LinkedListSequence<TN>();
					list->Prepend(Node);
				}
				else{
					Sequence<TN>* list2 = nullptr;
					list2 = new LinkedListSequence<TN>();
					list2->Prepend(Node);

					list = list->Concat(list2);
				}
				break;

			case 'R':
				if (Node->right != nullptr){
					if (list == nullptr){
						list = Firmware(Node->right, str);
					}
					else{
						list = list->Concat(Firmware(Node->right, str));
					}
				}
				break;

			case 'L':
				if (Node->left != nullptr){
					if (list == nullptr){
						list = Firmware(Node->left, str);
					}
					else{
						list = list->Concat(Firmware(Node->left, str));
					}
				}

				break;
			}
		}
		return list;
		//delete list;
		//delete list2;
	}

	Sequence<TN>* Firmware(std::string str) {
		return Firmware(this->root, str);
	}

	std::string ToString(std::string str) {
		std::string res;

		Sequence<TN>* FirmwareTree = this->Firmware(str);
		if (this->root == nullptr) throw std::exception("Empty");

		for (int i = 0; i < FirmwareTree->GetLength(); i++) {
			if (i == 0) {res += std::to_string(FirmwareTree->Get(i)->values) + " ";
			}
			else res += " " + std::to_string(FirmwareTree->Get(i)->values) + " ";
		}

		return res;
	}
};


/////////////////////////////////////Test//////////////////////////////
int difference(int x){
	return x - 1;
}
int zero(int x) {
	return 0;
}
int half(int x) {
	return (x/2);
}

double difference2(double x) {
	return x - 1;
}
double zero2(double x) {
	return 0;
}
double half2(double x) {
	return (x / 2);
}

int Test_BinaryTree() {
	BinaryTree<int>* Test_tree;
	Test_tree = new BinaryTree<int>();
	
	Test_tree->Insert(5);
	Test_tree->Insert(4);
	Test_tree->Insert(6);
	Test_tree->Insert(2);
	Test_tree->Insert(3);
	Test_tree->Insert(8);
	Test_tree->Insert(7);

	//test height
	if (Test_tree->height()==3)
		std::cout << "Test Height: success" << "\n";
	else {
		std::cout << "Test Height: fail" << "\n";
	};

	//test search
	if (Test_tree->FindNode(4) != nullptr)
		std::cout << "Test FindNode: success" << "\n";
	else {
		std::cout << "Test FindNode: fail" << "\n";
	};

	//test CheckElement
	if (Test_tree->CheckElement(8) == true && Test_tree->CheckElement(11) == false)
		std::cout << "Test CheckElement: success" << "\n";
	else {
		std::cout << "Test CheckElement: fail" << "\n";
	};

	//test delete
	Test_tree->DeleteNode(3);
	if (Test_tree->CheckElement(3) == false)
		std::cout << "Test DeleteNode: success" << "\n";
	else {
		std::cout << "Test DeleteNode: fail" << "\n";
	};
	Test_tree->Insert(3);

	//test FindSubTree не работает
	BinaryTree<int>* Test_tree5;
	Test_tree5 = new BinaryTree<int>();

	Test_tree5->Insert(5);
	Test_tree5->Insert(6);
	Test_tree5->Insert(4);

	if (Test_tree->FindSubTree(Test_tree5) == true)
		std::cout << "Test FindSubTree: success" << "\n";
	else {
		std::cout << "Test FindSubTree: fail" << "\n";
	}; 

	//test map
	BinaryTree<int>* Test_tree2;
	Test_tree2 = new BinaryTree<int>();

	Test_tree2->Insert(5);
	Test_tree2->Insert(6);
	Test_tree2->Insert(8);

	Test_tree2->Map(difference);
	if (Test_tree2->CheckElement(4) == true && Test_tree2->CheckElement(7) == true && Test_tree2->CheckElement(5) == true )
		std::cout << "Test Map: success" << "\n";
	else {
		std::cout << "Test Map: fail" << "\n";
	};

	//test Equality (не работает)
	BinaryTree<int>* Test_tree3;
	Test_tree3 = new BinaryTree<int>();

	Test_tree3->Insert(5);
	Test_tree3->Insert(4);
	Test_tree3->Insert(6);
	Test_tree3->Insert(2);
	Test_tree3->Insert(3);
	Test_tree3->Insert(8);
	Test_tree3->Insert(7);

	if (Test_tree->Equality(Test_tree3) == true)
		std::cout << "Test Equality: success" << "\n";
	else {
		std::cout << "Test Equality: fail" << "\n";
	};

	//test Subtree
	BinaryTree<int>* Test_tree4;
	Test_tree4 = new BinaryTree<int>();

	Test_tree4 = Test_tree->SubTree(6);

	if (Test_tree4->CheckElement(6) == true && Test_tree4->CheckElement(7) == true && Test_tree4->CheckElement(8) == true)
		std::cout << "Test SubTree: success" << "\n";
	else {
		std::cout << "Test SubTree: fail" << "\n";
	};

	//test ToString и Firmware не работает компилятор не показывает корректно где ошибка:(
	 //std::cout << Test_tree->ToString("NLR");
	

	//Test_tree2->printTree(Test_tree2->GetRoot(), Test_tree2->height());
	//Test_tree->printTree(Test_tree->GetRoot(), Test_tree->height());
	//Test_tree3->printTree(Test_tree3->GetRoot(), Test_tree3->height());

	delete Test_tree;
	delete Test_tree2;
	delete Test_tree3;
	delete Test_tree4;

	return 0;
}
