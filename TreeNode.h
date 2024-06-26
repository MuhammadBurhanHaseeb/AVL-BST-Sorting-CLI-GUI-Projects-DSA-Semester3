#include <iostream>

using namespace std;

class TreeNode
{
public:

    int height;
    int index;
    string id;
    string firstName;
    string lastName;
    string company;
    string city;
    string country;
    string phone1;
    string phone2;
    string email;
    string subscriptionDate;
    string website;
    TreeNode *left;
    TreeNode *right;

    TreeNode()
    {
        index = height = 0;
        id = firstName = lastName = company = city = country = phone1 = phone2 = email = subscriptionDate = website;
        left = right = NULL;
    }

};