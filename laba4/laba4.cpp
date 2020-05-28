
	// C++ program for expression tree 
   
    #include <stack>
#include <iostream>
	using namespace std;

	// An expression tree node 
	struct et
	{
		char value;
		et* left, * right;
	};

	// A utility function to check if 'c' 
	// is an operator 
	bool isOperator(char c)
	{
		if (c == '+' || c == '-' ||
			c == '*' || c == '/' ||
			c == '^')
			return true;
		return false;
	}

	// Utility function to do inorder traversal 
	void inorder(et * t)
	{
		if (t)
		{
			inorder(t->left);
			cout << "%c " << t->value << endl;
			inorder(t->right);
		}
	}

	// A utility function to create a new node 
	et* newNode(int v)
	{
		et* temp = new et;
		temp->left = temp->right = NULL;
		temp->value = v;
		return temp;
	};

	// Returns root of constructed tree for given 
	// postfix expression 
	et* constructTree(char postfix[])
	{
		stack<et*> st;
		et* t, * t1, * t2;

		// Traverse through every character of 
		// input expression 
		for (int i = 0; i < strlen(postfix); i++)
		{
			// If operand, simply push into stack 
			if (!isOperator(postfix[i]))
			{
				t = newNode(postfix[i]);
				st.push(t);
			}
			else // operator 
			{
				t = newNode(postfix[i]);

				// Pop two top nodes 
				t1 = st.top(); // Store top 
				st.pop();	 // Remove top 
				t2 = st.top();
				st.pop();

				// make them children 
				t->right = t1;
				t->left = t2;

				// Add this subexpression to stack 
				st.push(t);
			}
		}

		// only element will be root of expression 
		// tree 
		t = st.top();
		st.pop();

		return t;
	}

	// Driver program to test above 
	int main()
	{
		char postfix[] = "ab+ef*g*-";
		et* r = constructTree(postfix);
		cout << "infix expression is" << endl;
		inorder(r);
		return 0;
	}


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
