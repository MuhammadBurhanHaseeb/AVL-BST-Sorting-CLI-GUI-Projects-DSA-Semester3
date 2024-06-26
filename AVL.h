#include <iostream>
#include <stack>
#include "BST.h"

using namespace std;

class AVL
{
public:
    TreeNode *root;
    TreeNode *actionOn;
    stack<TreeNode *> path;
    bool inserting;

    AVL()
    {
        root = NULL;
        actionOn = NULL;
        inserting = false;

        while (!path.empty())
        {
            path.pop();
        }
    }

    int height(TreeNode *node)
    {
        if (node == NULL)
            return 0;

        return node->height;
    }

    int getBalanceFactor(TreeNode *node)
    {
        if (node == NULL)
            return 0;

        return height(node->left) - height(node->right);
    }

    int max(int a, int b)
    {
        if (a > b)
        {
            return a;
        }
        return b;
    }

    TreeNode *rightRotate(TreeNode *x)
    {
        TreeNode *y = x->left;
        TreeNode *T2 = y->right;
        y->right = x;
        x->left = T2;
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;
        return y;
    }

    TreeNode *leftRotate(TreeNode *x)
    {
        TreeNode *y = x->right;
        TreeNode *T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;
        return y;
    }

    stack<TreeNode *> insert(TreeNode *node)
    {
        stack<TreeNode *> s;
        if (root == NULL)
        {
            root = node;
            return s;
        }
        TreeNode *prev = root;
        TreeNode *next = root;
        while (next != NULL)
        {
            prev = next;
            s.push(next);
            if (node->index < prev->index)
                next = prev->left;
            else
                next = prev->right;
        }
        s.push(node);
        if (node->index >= prev->index)
            prev->right = node;
        else
            prev->left = node;
        return s;
    }

    void insertionWithRotaion(TreeNode *node)
    {
        stack<TreeNode *> s = insert(node);
        rotate(s, node);
    }

    void rotate(stack<TreeNode *> s, TreeNode *node)
    {
        TreeNode *temp;
        TreeNode *temp1;
        while (!s.empty())
        {
            temp = s.top();
            bool isBalanceChanged = false;
            temp->height = max(height(temp->left), height(temp->right)) + 1;
            int balanceFactor = getBalanceFactor(temp);
            if (balanceFactor > 1)
            {
                if (node->index < temp->left->index)
                    temp1 = rightRotate(temp);
                else if (node->index > temp->left->index)
                {
                    temp->left = leftRotate(temp->left);
                    temp1 = rightRotate(temp);
                }
                isBalanceChanged = true;
            }
            if (balanceFactor < -1)
            {
                if (node->index > temp->right->index)
                    temp1 = leftRotate(temp);
                else if (node->index < temp->right->index)
                {
                    temp->right = rightRotate(temp->right);
                    temp1 = leftRotate(temp);
                }
                isBalanceChanged = true;
            }
            s.pop();
            if (isBalanceChanged)
            {
                if (s.empty())
                    root = temp1;
                else
                {
                    if (s.top()->left == temp)
                        s.top()->left = temp1;
                    else
                        s.top()->right = temp1;
                }
            }
        }
    }

    TreeNode *retrieve(int index)
    {
        if (root == NULL)
        {
            return NULL;
        }

        TreeNode *temp = root;

        while (true)
        {
            if (temp->index == index)
            {
                return temp;
                break;
            }

            if (temp->index > index)
            {
                if (temp->left != NULL)
                {
                    temp = temp->left;
                }

                else
                    break;
            }

            else
            {
                if (temp->right != NULL)
                {
                    temp = temp->right;
                }

                else
                    break;
            }
        }

        return NULL;
    }

    void update(int index, TreeNode *node)
    {
        TreeNode *temp = retrieve(index);
        temp->id = node->id;
        temp->firstName = node->firstName;
        temp->lastName = node->lastName;
        temp->company = node->company;
        temp->city = node->city;
        temp->country = node->country;
        temp->phone1 = node->phone1;
        temp->phone2 = node->phone2;
        temp->email = node->email;
        temp->subscriptionDate = node->subscriptionDate;
        temp->website = node->website;
    }

    void remove( int index )
    {
        deleteNode( root, index );
    }

    TreeNode *deleteNode(TreeNode *root, int index)
    {
        if (root == NULL)
            return root;

        if (index < root->index)
            root->left = deleteNode(root->left, index);

        else if (index > root->index)
            root->right = deleteNode(root->right, index);

        else
        {
            if ((root->left == NULL) ||
                (root->right == NULL))
            {
                TreeNode *temp = root->left ? root->left : root->right;

                if (temp == NULL)
                {
                    temp = root;
                    root = NULL;
                }
                else
                    *root = *temp;

                free(temp);
            }
            else
            {
                TreeNode *temp = minValueNode(root->right);

                root->index = temp->index;

                root->right = deleteNode(root->right, temp->index);
            }
        }

        if (root == NULL)
            return root;

        root->height = 1 + max(height(root->left),
                               height(root->right));

        int balance = getBalanceFactor(root);

        if (balance > 1 && getBalanceFactor(root->left) >= 0)
            return rightRotate(root);

        if (balance > 1 && getBalanceFactor(root->left) < 0)
        {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        if (balance < -1 && getBalanceFactor(root->right) <= 0)
            return leftRotate(root);

        if (balance < -1 && getBalanceFactor(root->right) > 0)
        {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    TreeNode *minValueNode(TreeNode *node)
    {
        TreeNode *current = node;

        while (current->left != NULL)
            current = current->left;

        return current;
    }
};