#include <iostream>
#include "TreeNode.h"

using namespace std;

class BST
{
public:
    TreeNode *root;

    BST()
    {
        root = NULL;
    }

    void insert(TreeNode *node)
    {
        if( root == NULL )
        {
            root = node;
            return;
        }

        else
        {
            TreeNode *temp = root;

            while ( true )
            {
                if ( node->index < temp->index )
                {
                    if (temp->left == NULL)
                    {
                        temp->left = node;
                        return;
                    }

                    else
                    {
                        temp = temp->left;
                    }
                }

                else
                {
                    if (temp->right == NULL)
                    {
                        temp->right = node;
                        return;
                    }

                    else
                    {
                        temp = temp->right;
                    }
                }
            }
        }

        cout << "here" <<endl;
    }

    void remove(int index)
    {
        if (root == NULL)
        {
            return;
        }

        TreeNode *temp = root;
        TreeNode *previous;

        while (true)
        {
            if (index == temp->index)
            {
                if (temp->right == NULL && temp->left == NULL)
                {
                    if( previous->index > temp->index )
                    {
                        previous->left = NULL;
                        //delete temp;
                    }

                    else
                    {
                        previous->right = NULL;
                        //delete temp;
                    }

                    break;
                }

                else if( temp->left == NULL )
                {
                    if( previous->index > temp->index )
                    {
                        previous->left = temp->right;
                        //delete temp;
                    }

                    else
                    {
                        previous->right = temp->right;
                        //delete temp;
                    }

                    break;
                }

                else if( temp->right == NULL )
                {
                    if( previous->index > temp->index )
                    {
                        previous->left = temp->left;
                        //delete temp;
                    }

                    else
                    {
                        previous->right = temp->left;
                        //delete temp;
                    }

                    break;
                }

                TreeNode* prev;
                previous = temp->right;

                while (true)
                {
                    if ( previous->left == NULL )
                    {
                        prev->left = NULL;
                        temp = previous;
                        break;
                    }

                    prev = previous;
                    previous = previous->left;
                }

                break;
            }

            if (index < temp->index)
            {
                if (temp->left != NULL)
                {
                    previous = temp;
                    temp = temp->left;
                }

                else
                {
                    break;
                }
            }

            else
            {
                if (temp->right != NULL)
                {
                    previous = temp;
                    temp = temp->right;
                }

                else
                {
                    break;
                }
            }
        }
    }

    TreeNode* retrieve( int index )
    {
        if (root == NULL)
        {
            return NULL;
        }

        TreeNode* temp = root;

        while (true)
        {
            if (temp->index == index)
            {
                return temp;
                break;
            }

            if( temp->index > index )
            {
                if( temp->left != NULL )
                {
                    temp = temp->left;
                }

                else
                    break;
            }

            else
            {
                if( temp->right != NULL )
                {
                    temp = temp->right;
                }

                else
                    break;
            }
        }

        return NULL;
    }

    void update( int index, TreeNode *node )
    {
        TreeNode* temp = retrieve( index );
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
};