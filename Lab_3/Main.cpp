#include <iostream>
#include <string>
//#include "List_Sequence.h"
//#include "ArraySequence.h"
#include "BinaryTree.h"

int interface() {
	std::cout << "What type of data do you want to work with? \n";
	std::cout << "Choose type of the list:\n1. int\n2. double\n";
	int type;
	do {
		std::cin >> type; std::cout <<"\n";
		if ((type != 1) && (type != 2))
		{
			std::cout << ("You must choose 1 or 2\n");
		}
	} while ((type != 1) && (type != 2));

	BinaryTree<int>* Tree1;
	Tree1 = new BinaryTree<int>();
	BinaryTree<double>* Tree2;
	Tree2 = new BinaryTree<double>();

	BinaryTree<int>* Tree_sub1;
	Tree_sub1 = new BinaryTree<int>();
	BinaryTree<double>* Tree_sub2;
	Tree_sub2 = new BinaryTree<double>();
	int choice = 0;
	int ch;

	BinaryTree<int>* Tree_find1;
	Tree_find1 = new BinaryTree<int>();
	BinaryTree<double>* Tree_find2;
	Tree_find2 = new BinaryTree<double>();

	if (type == 1) { Tree1->EnterTree(); 
	}else Tree2->EnterTree();

	do {
		std::cout << "\n" << " Choose the operation:\n"
			"1. Print Tree \n"
			"2. Get Height\n"
			"3. Map\n"
			"4. Search\n"
			"5. Delete Sheet\n"
			"6. Get SubTree\n"
			"7. Check SubTree\n"
			"8. Check Element\n"
			"9. exit\n";

		std::cout << "\nYour choice: ";
		std::cin >> choice; std::cout << "\n";
		int k1;
		double k2;
		

		switch (choice) {
		case 1:
			if (type == 1) Tree1->printTree(Tree1->GetRoot(), Tree1->height());
			if (type == 2) Tree2->printTree(Tree2->GetRoot(), Tree2->height());
			break;
		case 2:
			if (type == 1) std::cout << Tree1->height();
			if (type == 2) std::cout << Tree2->height();
			break;
		case 3:
			std::cout << " Choose the function:\n"
				"1. zero \n"
				"2. difference\n"
				"3. half\n";
			std::cin >> ch;

			if (type == 1 && ch == 1) Tree1->Map(zero);
			if (type == 1 && ch == 2) Tree1->Map(difference);
			if (type == 1 && ch == 3) Tree1->Map(half);

			if (type == 2 && ch == 1) Tree2->Map(zero2);
			if (type == 2 && ch == 2) Tree2->Map(difference2);
			if (type == 2 && ch == 3) Tree2->Map(half2);
			break;
		case 4:
			std::cout << "Enter element: ";
			if (type == 1) {
				std::cin >> k1;
			}else std::cin >> k2;

			if (type == 1) std::cout << Tree1->FindNode(k1);
			if (type == 2) std::cout << Tree2->FindNode(k2);
			break;
		case 5:
			std::cout << "Enter element: ";
			if (type == 1) {
				std::cin >> k1;
			}else std::cin >> k2;

			if (type == 1) Tree1->DeleteNode(k1);
			if (type == 2) Tree2->DeleteNode(k2);
			break;
		case 6:
			std::cout << "Enter element: ";
			if (type == 1) {
				std::cin >> k1;
			}
			else std::cin >> k2;

			if (type == 1) {
				Tree_sub1 = Tree1->SubTree(k1);
				Tree_sub1->printTree(Tree_sub1->GetRoot(), Tree_sub1->height());
			}
			if (type == 2) {
				Tree_sub2 = Tree2->SubTree(k2);
				Tree_sub2->printTree(Tree_sub2->GetRoot(), Tree_sub2->height());
			}
			break;
		case 7:
			if (type == 1) {
				Tree_find1->EnterTree();
				if (Tree1->FindSubTree(Tree_find1) == true){
					std::cout << "True";
				}
				else std::cout << "False";
			}
			if (type == 2) {
				Tree_find2->EnterTree();
				if (Tree2->FindSubTree(Tree_find2) == true) {
					std::cout << "True";
				}
				else std::cout << "False";
			}
			break;
		case 8:
			std::cout << "Enter element: ";
			if (type == 1) {
				std::cin >> k1;
			}
			else std::cin >> k2;

			if (type == 1 && Tree1->CheckElement(k1) == true) std::cout << "True"; 
			if (type == 1 && Tree1->CheckElement(k1) != true) std::cout << "False";

			if (type == 2 && Tree2->CheckElement(k2) == true) std::cout << "True"; 
			if (type == 2 && Tree2->CheckElement(k2) != true) std::cout << "False";
			break;
		case 9:
			std::cout << "Good job";
			break;
		default: std::cout << "ERROR. You need choose an action.";
		}
		std::cout << "\n";
	} while (choice != 9);




	//Tree1->EnterTree();
	//Tree1->printTree(Tree1->GetRoot(), Tree1->height());

	delete Tree1;
	delete Tree2;
	delete Tree_sub1;
	delete Tree_sub2;

	return 0;
}




int main() {
	/*Test_List_Sequence();
	Test_Array_Sequence();
	Test_MyClass();*/

	//Test_BinaryTree();
	interface();


	return 0;
}