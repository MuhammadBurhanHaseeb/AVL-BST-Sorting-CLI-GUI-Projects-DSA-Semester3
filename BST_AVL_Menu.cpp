#include <iostream>
#include <conio.h>
#include <queue>
#include <stack>
#include <string>
#include <fstream>
#include <chrono>
#include "AVL.h"

using namespace std;
using namespace std::chrono;

BST bst;
AVL avl;

int menu1();
int menu2();
int menu3();
int menu4();
void clearScreen();
void load(int op, int tree);//
string parseRecord(string record, int field);
void newInsert(int tree, TreeNode *node);
void retrieve(int tree);
void update(int tree);
int remove(int tree);
void breathFirst(int tree);
void preOrder(int tree);
void postOrder(int tree);
void inOrder(int tree);
void calculateTime(time_t start, time_t end);

int main()
{
    int tree;

Menu1:
    int op = menu1();

    if (op == 0)
        goto EndProgram;

Menu2:
    tree = op;
    op = menu2();

    if (op == 0)
        goto Menu1;

    load(op, tree);

Menu3:
    op = menu3();

    if (op == 0)
        goto Menu2;

    else
    {
        if (op == 1)
        {
            auto start = steady_clock::now();
            TreeNode node;
            newInsert( tree, &node );

            if (tree == 1)
                bst.insert(&node);
            else
                avl.insert(&node);
            auto end = steady_clock::now();

            auto nanosecond = duration_cast<nanoseconds>( end - start );

            cout <<endl << " time = " << nanosecond.count() <<endl;
        }

        else if (op == 2)
        {
            auto start = steady_clock::now();
            retrieve(tree);
            auto end = steady_clock::now();

            auto nanosecond = duration_cast<nanoseconds>( end - start );

            cout <<endl << " time = " << nanosecond.count() <<endl;
        }

        else if (op == 3)
        {
            auto start = steady_clock::now();
            update(tree);
            auto end = steady_clock::now();

            auto nanosecond = duration_cast<nanoseconds>( end - start );

            cout <<endl << " time = " << nanosecond.count() <<endl;
        }

        else if (op == 4)
        {
            auto start = steady_clock::now();
            if (tree == 1)
                bst.remove(remove(tree));
            else
                avl.remove(remove(tree));

            auto end = steady_clock::now();

            auto nanosecond = duration_cast<nanoseconds>( end - start );

            cout <<endl << " time = " << nanosecond.count() <<endl;
        }

        else if (op == 5)
        {
            goto Menu4;
        }

        goto Menu3;
    }

Menu4:
    op = menu4();

    if (op == 0)
        goto Menu3;

    else
    {
        if (op == 1)
        {
            auto start = steady_clock::now();
            breathFirst(tree);
            auto end = steady_clock::now();

            auto nanosecond = duration_cast<nanoseconds>( end - start );

            cout << " time = " << nanosecond.count() <<endl;
        }

        else if (op == 2)
        {
            auto start = steady_clock::now();
            preOrder(tree);
            auto end = steady_clock::now();

            auto nanosecond = duration_cast<nanoseconds>( end - start );

            cout << " time = " << nanosecond.count() <<endl;
        }

        else if (op == 3)
        {
            auto start = steady_clock::now();
            postOrder(tree);
            auto end = steady_clock::now();

            auto nanosecond = duration_cast<nanoseconds>( end - start );

            cout << " time = " << nanosecond.count() <<endl;
        }

        else if (op == 4)
        {
            auto start = steady_clock::now();
            inOrder(tree);
            auto end = steady_clock::now();

            auto nanosecond = duration_cast<nanoseconds>( end - start );

            cout << " time = " << nanosecond.count() <<endl;
        }

        goto Menu4;
    }

EndProgram:
    cout <<endl << " End of Program.";
}

void clearScreen()
{
    cout << endl
         << " Press any key to continue. ";
    getch();
    system("CLS");
}

int menu1()
{
    string op;
    cout << endl
         << "\t Menu 1 \t" << endl;
    cout << "-----------------------" << endl;
    cout << " 1. Binary Search Tree" << endl;
    cout << " 2. AVL Tree" << endl;
    cout << " 0. Exit"
         << endl;

Menu:
    cout << " Your Choice: ";
    cin >> op;
    int num = stoi(op);

    if (num == 1 || num == 2 || num == 0)
        return num;

    else
    {
        cout << "Invalid Choice!" << endl
             << endl;
        goto Menu;
    }
}

int menu2()
{
    string op;
    cout << endl
         << "\t Menu 2 \t" << endl;
    cout << "-----------------------" << endl;
    cout << " 1. Load 100 records" << endl;
    cout << " 2. Load 1000 records" << endl;
    cout << " 3. Load 10000 records" << endl;
    cout << " 4. Load 100000 records" << endl;
    cout << " 0. Back"
         << endl;

Menu:
    cout << " Your Choice: ";
    cin >> op;
    int num = stoi(op);

    if (num >= 0 && num <= 4)
        return num;

    else
    {
        cout << "Invalid Choice!" << endl
             << endl;
        goto Menu;
    }
}

int menu3()
{
    string op;
    cout << endl
         << "\t Menu 3 \t" << endl;
    cout << "-----------------------" << endl;
    cout << " 1. Insert a New Record" << endl;
    cout << " 2. Retrieve a Record" << endl;
    cout << " 3. Update a Record" << endl;
    cout << " 4. Delete a Record" << endl;
    cout << " 5. Traverse the Tree" << endl;
    cout << " 0. Back"
         << endl;

Menu:
    cout << " Your Choice: ";
    cin >> op;
    int num = stoi(op);

    if (num >= 0 && num <= 5)
        return num;

    else
    {
        cout << "Invalid Choice!" << endl
             << endl;
        goto Menu;
    }
}

int menu4()
{
    string op;
    cout << endl
         << "\t Menu 4 \t" << endl;
    cout << "-----------------------" << endl;
    cout << " 1. Breath first Traversal" << endl;
    cout << " 2. Pre order Traversal" << endl;
    cout << " 3. Post order Traversal" << endl;
    cout << " 4. In order Traversal" << endl;
    cout << " 0. Back"
         << endl;

Menu:
    cout << " Your Choice: ";
    cin >> op;
    int num = stoi(op);

    if (num >= 0 && num <= 4)
        return num;

    else
    {
        cout << "Invalid Choice!" << endl
             << endl;
        goto Menu;
    }
}

void load(int op, int tree)
{
    fstream file;

    if (op == 1)
        file.open("customers-100.csv", ios::in);
    else if (op == 2)
        file.open("customers-1000.csv", ios::in);
    else if (op == 3)
        file.open("customers-10000.csv", ios::in);
    else
        file.open("customers-100000.csv", ios::in);

    string line, word, temp;

    getline(file, line);

    while (getline(file, line))
    {
        TreeNode *node = new TreeNode();
        node->index = stoi(parseRecord(line, 0));
        node->id = parseRecord(line, 1);
        node->firstName = parseRecord(line, 2);
        node->lastName = parseRecord(line, 3);
        node->company = parseRecord(line, 4);
        node->city = parseRecord(line, 5);
        node->country = parseRecord(line, 6);
        node->phone1 = parseRecord(line, 7);
        node->phone2 = parseRecord(line, 8);
        node->email = parseRecord(line, 9);
        node->subscriptionDate = parseRecord(line, 10);
        node->website = parseRecord(line, 11);
        node->left = NULL;
        node->right = NULL;

        if (tree == 1)
            bst.insert(node);

        else
            avl.insertionWithRotaion(node);
    }

    file.close();
}

string parseRecord(string record, int field)
{
    int commaCount = 0;
    string item;

    for (int x = 0; x < record.length(); x++)
    {
        if (record[x] == ',')
        {
            commaCount = commaCount + 1;
        }
        else if (commaCount == field)
        {
            item = item + record[x];
        }
    }
    return item;
}

void newInsert(int tree, TreeNode *node)
{
    cout << " Fill in the following details->" << endl;
    cout << " Index: ";
    cin >> node->index;
    cout << " Customer ID: ";
    cin >> node->id;
    cout << " First Name: ";
    cin >> node->firstName;
    cout << " Last Name: ";
    cin >> node->lastName;
    cout << " Company: ";
    cin >> node->company;
    cout << " Country: ";
    cin >> node->country;
    cout << " City: ";
    cin >> node->city;
    cout << " Phone 1: ";
    cin >> node->phone1;
    cout << " Phone 2: ";
    cin >> node->phone2;
    cout << " Email: ";
    cin >> node->email;
    cout << " Subscription Date: ";
    cin >> node->subscriptionDate;
    cout << " Website: ";
    cin >> node->website;
    node->left = NULL;
    node->right = NULL;
}

void retrieve(int tree)
{
    int idx;
    TreeNode *node;

    cout << " Enter the index: ";
    cin >> idx;

    if (tree == 1)
        node = bst.retrieve(idx);

    else
        node = avl.retrieve(idx);

    cout << node->index << endl;
    cout << node->id << endl;
    cout << node->firstName << endl;
    cout << node->lastName << endl;
    cout << node->company << endl;
    cout << node->country << endl;
    cout << node->city << endl;
    cout << node->phone1 << endl;
    cout << node->phone2 << endl;
    cout << node->email << endl;
    cout << node->subscriptionDate << endl;
    cout << node->website << endl;
}

void update(int tree)
{
    int idx;
    TreeNode node;

    cout << " Enter the index you wish to update: ";
    cin >> idx;

    cout << " Fill in the following details->" << endl;
    node.index = idx;
    cout << " Customer ID: ";
    cin >> node.id;
    cout << " First Name: ";
    cin >> node.firstName;
    cout << " Last Name: ";
    cin >> node.lastName;
    cout << " Company: ";
    cin >> node.company;
    cout << " Country: ";
    cin >> node.country;
    cout << " City: ";
    cin >> node.city;
    cout << " Phone 1: ";
    cin >> node.phone1;
    cout << " Phone 2: ";
    cin >> node.phone2;
    cout << " Email: ";
    cin >> node.email;
    cout << " Subscription Date: ";
    cin >> node.subscriptionDate;
    cout << " Website: ";
    cin >> node.website;

    if (tree == 1)
        bst.update(idx, &node);

    else
        avl.update(idx, &node);
}

int remove(int tree)
{
    int idx;

    cout << " Enter the index you wish to remove: ";
    cin >> idx;

    return idx;
}

void breathFirst(int tree)
{
    TreeNode *temp;
    queue<TreeNode *> family;

    if (tree == 1)
        family.push(bst.root);

    else
        family.push(avl.root);

    temp = family.front();

    while (!family.empty())
    {
        if (temp->left != NULL)
        {
            family.push(temp->left);
        }

        if (temp->right != NULL)
        {
            family.push(temp->right);
        }

        cout << endl
             << temp->index;

        family.pop();
        temp = family.front();
    }
}

void preOrder(int tree)
{
    TreeNode *temp;
    stack<TreeNode *> family;

    if (tree == 1)
        family.push(bst.root);

    else
        family.push(avl.root);

    temp = family.top();

    while (!family.empty())
    {
        if (temp->right != NULL)
        {
            family.push(temp->right);
        }

        if (temp->left != NULL)
        {
            family.push(temp->left);
        }

        cout << family.top()->index <<endl;

        temp = family.top();
        family.pop();
    }
}

void postOrder(int tree)
{
    TreeNode *temp;
    stack<TreeNode *> family;
    stack<TreeNode *> next;

    if (tree == 1)
        family.push(bst.root);

    else
        family.push(avl.root);

    temp = family.top();

    while (!family.empty())
    {
        if (temp->left != NULL)
        {
            family.push(temp->left);
        }

        if (temp->right != NULL)
        {
            family.push(temp->right);
        }

        next.push(family.top());
        temp = family.top();
        family.pop();
    }

    while (!next.empty())
    {
        cout << next.top()->index <<endl;

        next.pop();
    }
}

void inOrder(int tree)
{
    TreeNode *cur;
    stack<TreeNode *> sk;

    if (tree == 1)
        cur = bst.root;

    else
        cur = avl.root;

    while (!sk.empty() || cur != NULL)
    {
        if (cur != NULL)
        {
            sk.push(cur);
            cur = cur->left;
        }

        else
        {
            cur = sk.top();
            sk.pop();
            cout << cur->index <<endl;
            cur = cur->right;
        }
    }
}

void calculateTime(time_t start, time_t end)
{
    double diff;

    diff = end - start;

    cout << endl << "time = " <<diff << endl;
}