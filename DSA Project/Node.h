#pragma once
#include "student.h"
typedef student dataType;

class Node
{
public:
	dataType data;
	Node* left;
	Node* right;
	Node();
};