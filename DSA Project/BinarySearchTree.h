#pragma once
#include"Node.h"
#include<queue>
#include "student.h"
class BinarySearchTree
{
private:
	Node* root;
public:
	BinarySearchTree();
	bool isEmpty();
	void InsertStudent(student newStudent);
	void InOrderTraveral(Node * currentRoot);
	void PostOrderTraversal(Node * currentRoot);
	void PreOrderTraversal(Node * currentRoot);
	void PreOrderTraversal();
	void PostOrderTraversal();
	void InOrderTraveral();
	Node* SearchTree(Node*currentRoot,std::string key);
	Node* get_root();
	void setRoot(Node *);
	
	Node* FindFirstStudent(Node* currentRoot);
	void addStudentToTree();

	// Get Parent of the Current Node
	//Node * GetParent(Node *, std::string);


	Node * SearchForNode(Node * root, std::string);

	student deleteNode(std::string NameOfStudent);
	student deleteFromTree(Node* &currentRoot);
	void deleteStudent(Node * currentNode, std::string studentToDelete);


	
	std::string hashVal(std::string Name);
	void AlphabeticOrder(Node*currentRoot, std::queue<student> &Students);
	void writeToFiles();
	student readFromFiles(std::string);

	~BinarySearchTree();
};

