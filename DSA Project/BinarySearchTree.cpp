#include "BinarySearchTree.h"
#include <iostream>
#include"student.h"
#include <string>
#include <stack>
#include <queue>
#include <fstream>
BinarySearchTree::BinarySearchTree()
{
	this->root = nullptr;
}

bool BinarySearchTree::isEmpty()
{
	return (this->root == nullptr) ? true : false;
}

Node * BinarySearchTree::SearchForNode(Node * current, std::string name)
{
	if (current != nullptr)
	{
		if (current->data.getNameOfStudent() == name)
			return current;
		SearchForNode(current->left, name);
		SearchForNode(current->right, name);
	}
}

void BinarySearchTree::InsertStudent(student newStudent)
{
	
	Node* newNode = new Node();
	newNode->data = newStudent;
	newNode->left = nullptr;
	newNode->right = nullptr;
	if (isEmpty())
	{
		this->root = newNode;
		return;
	}
	else
	{
		Node*temp = this->root;
		Node* parent = nullptr;
		while (temp != nullptr)
		{
			parent = temp;
			if (newStudent.getNameOfStudent() >= parent->data.getNameOfStudent())
			{
				temp = temp->right;
			}
			else
			{
				temp = temp->left;
			}
		}
		if (newStudent.getNameOfStudent() < parent->data.getNameOfStudent())
		{
			parent->left = newNode;
		}
		else
		{
			parent->right = newNode;
		}
		
	}
}

void BinarySearchTree::PreOrderTraversal(Node * currentRoot)
{
	if (currentRoot != nullptr)
	{
		std::cout << currentRoot->data << " ";
		PreOrderTraversal(currentRoot->left);
		PreOrderTraversal(currentRoot->right);
	}
}

void BinarySearchTree::PreOrderTraversal()
{
	Node*currentRoot = this->root;
	if (currentRoot != nullptr)
	{
		currentRoot->data.displayStudentInfo();
		PreOrderTraversal(currentRoot->left);
		PreOrderTraversal(currentRoot->right);
	}
}

void BinarySearchTree::InOrderTraveral(Node* currentRoot)
{
	if (currentRoot != nullptr)
	{
		InOrderTraveral(currentRoot->left);
		currentRoot->data.displayStudentInfo();
		InOrderTraveral(currentRoot->right);
	}
}

void BinarySearchTree::InOrderTraveral()
{
	Node* currentRoot = this->root;
	if (currentRoot != nullptr)
	{
		InOrderTraveral(currentRoot->left);
		currentRoot->data.displayStudentInfo();
		InOrderTraveral(currentRoot->right);
	}
}

void BinarySearchTree::PostOrderTraversal()
{
	Node*currentNode = this->root;
	if (currentNode != nullptr)
	{
		PostOrderTraversal(currentNode->left);
		PostOrderTraversal(currentNode->right);
		currentNode->data.displayStudentInfo();
	}
}

void BinarySearchTree::PostOrderTraversal(Node*currentNode)
{
	if (currentNode != nullptr)
	{
		PostOrderTraversal(currentNode->left);
		PostOrderTraversal(currentNode->right);
		currentNode->data.displayStudentInfo();
	}
}
Node* BinarySearchTree::SearchTree(Node*currentRoot, std::string key)
{
	
		if (currentRoot != nullptr && (currentRoot->data.getNameOfStudent() == key))
		{
			currentRoot->data.displayStudentInfo();
			return currentRoot;
		}

		if (currentRoot->data.getNameOfStudent() < key)
		{
			return SearchTree(currentRoot->right, key);
		}
		else
		{
			return SearchTree(currentRoot->left, key);
		}
}

Node* BinarySearchTree::get_root()
{
	return this->root;
}

void BinarySearchTree::setRoot(Node * root)
{
	this->root = root;
}

std::stack <student> students;
void DeleteNode(Node * current, std::string studentToDelete, bool & del)
{
	if (current != nullptr)
	{
		if (current->data.getNameOfStudent() == studentToDelete)
		{
			del = true;
		}
		else
		{
			DeleteNode(current->left, studentToDelete, del);
			DeleteNode(current->right, studentToDelete, del);
			students.push(current->data);
			return;
		}
	}
}

void BinarySearchTree::deleteStudent(Node * currentNode, std::string studentToDelete)
{
	BinarySearchTree BST;

	bool del = false;

	DeleteNode(currentNode, studentToDelete,del);

	while (!students.empty())
	{
		BST.InsertStudent(students.top());
		students.pop();
	}
	if (!del)
		std::cout << "Student Not deleted" << std::endl;

	this->root = BST.root;
}


Node* BinarySearchTree::FindFirstStudent(Node* currentRoot)
{
	if (currentRoot == nullptr)
	{
		return nullptr;
	}
	else if (currentRoot->left == nullptr)
	{
		currentRoot->data.displayStudentInfo();
		return currentRoot;
	}
	else
	{
		return FindFirstStudent(currentRoot->left);
	}
}

void BinarySearchTree::addStudentToTree()
{
	std::ifstream studentsFile;
	std::queue <student> newQueue;
	studentsFile.open("Students.dat", std::ios::in | std::ios::binary);
	if (!studentsFile)
	{
		std::cout << "CANNOT OPEN STUDENT FILE TO READ THE RECORDS" << std::endl;
	}
	else
	{
		studentsFile.seekg(0,std::ios::end);
		int noOFStudents = studentsFile.tellg() / sizeof(student);
		studentsFile.seekg(0, std::ios::beg);
		student* newStudents = new student[noOFStudents];
		student* temp= new student;
		for(int i=0;i<noOFStudents;i++)
		{
			studentsFile.read(reinterpret_cast<char*>(temp), sizeof(student));
			newStudents[i] = *temp;/*
			newStudents->displayStudentInfo();
			InsertStudent(newStudents[i]);*/
		}

		studentsFile.close();
	}
}

void BinarySearchTree::AlphabeticOrder(Node* currentRoot,std::queue<student> &Students)
{

	if (currentRoot != nullptr)
	{
		AlphabeticOrder(currentRoot->left,Students);
		Students.push(currentRoot->data);
		AlphabeticOrder(currentRoot->right,Students);
	}
}

void BinarySearchTree::writeToFiles()
{
	std::queue<student> Students;
	std::string fileName;
	AlphabeticOrder(this->root, Students);

	while (!Students.empty())
	{
		student* temp = new student;
		*temp = Students.front();
		std::string newName;
		newName = Students.front().getNameOfStudent();

		fileName = newName[0];
		Students.pop();
		std::ofstream file;
		file.open(fileName + ".dat", std::ios::out|std::ios::binary | std::ios::app);
		if (!file)
		{
			std::cout << "CANNOT OPEN STUDENT FILE TO SAVE THE RECORDS" << std::endl; system("pause");
		}
		else
		{
			file.write(reinterpret_cast<char*>(temp), sizeof(*temp));
		}
		file.close();
	}
}

student BinarySearchTree::readFromFiles(std::string studentToFind)
{
	std::string filename = hashVal(studentToFind);

	std::ifstream fileToRead;
	fileToRead.open(filename, std::ios::in | std::ios::binary/* | std::ios::app*/);

	if (fileToRead)
	{
		student StudentRead;
		while (!fileToRead.eof())
		{
			fileToRead.read(reinterpret_cast<char *>(&StudentRead), sizeof(student));
			if (studentToFind == StudentRead.getNameOfStudent())
			{
				fileToRead.close();
				return StudentRead;
			}
		}
	}
	else
	{
		fileToRead.close();
		std::cout << "Record doesn't exist" << std::endl;
		return student();
	}
}

std::string BinarySearchTree::hashVal(std::string Name)
{
	if (!(Name[0] >= ('A' || 'a') && Name[0] <= ('Z' || 'z')))
	{
		std::string hash = Name.substr(0, 1);
		hash.append(".dat");
		return hash;
	}
	else
	{
		return "Error.dat";
	}
}

student BinarySearchTree::deleteNode(std::string NameOfStudent)
{
	Node *current = nullptr;
	Node*trailCurrent = nullptr;

	bool found = false;

	if (this->root == nullptr)
	{
		std::cout << "CAN NOT DELETE FROM EMPTY TREE!" << std::endl;
	}
	else
	{
		current = this->root;
		trailCurrent = this->root;
		while (current!=nullptr&&!found)
		{
			if (current->data.getNameOfStudent() == NameOfStudent)
			{
				found = true;
			}
			else
			{
				trailCurrent = current;
				if (current->data.getNameOfStudent() >= NameOfStudent)
				{
					current = current->left;
				}
				else
				{
					current = current->right;
				}
			}
		}
		if (current == nullptr)
		{
			std::cout << "The Item to delete is not in the tree" << std::endl;
		}
		else if (found)
		{
			if (current == this->root)
			{
				return deleteFromTree(this->root);
			}
			else if (trailCurrent->data.getNameOfStudent() >= NameOfStudent)
			{
				return deleteFromTree(trailCurrent->left);
			}
			else
			{
				return deleteFromTree(trailCurrent->right);
			}
		}
	}
}

student BinarySearchTree::deleteFromTree(Node* &currentRoot)
{
	student deletedStudent;
	Node* current = nullptr;
	Node*trailCurrent = nullptr;

	Node* temp = nullptr;

	if (currentRoot == nullptr)
	{
		std::cerr << "Error:THE NODE TO BE DELETED IS NULL !" << std::endl;
	}
	else if(currentRoot->left==nullptr&&currentRoot->right==nullptr)
	{
		temp = currentRoot;
		currentRoot = nullptr;
		deletedStudent = temp->data;
		delete temp;
		return deletedStudent;
		
	}
	else if (currentRoot->left == nullptr&&currentRoot->right!=nullptr)
	{
		temp = currentRoot;
		currentRoot = temp->right;
		deletedStudent = temp->data;
		delete temp;
		return deletedStudent;
		

	}
	else if(currentRoot->right==nullptr&&currentRoot->left!=nullptr)
	{
		temp = currentRoot;
		currentRoot = temp->left;
		deletedStudent = temp->data;
		delete temp;
		return deletedStudent;

	}
	else
	{
		current = currentRoot->left;
		trailCurrent = nullptr;
		while (current->right != nullptr)
		{
			trailCurrent = current;
			current = current->right;
		}
		currentRoot->data = current->data;
		if (trailCurrent == nullptr)
		{
			currentRoot->left = current->left;
		}
		else
		{
			trailCurrent->right = current;
		}
		deletedStudent = current->data;
		delete current;
		return deletedStudent;
	}
}
BinarySearchTree::~BinarySearchTree()
{
}
