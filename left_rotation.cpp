class TreeNode
{
    public:
    TreeNode* left;
    TreeNode* right;
};

TreeNode* rotateLeft( TreeNode* x )
{
    TreeNode* y = x->right;
    TreeNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    return y;
}