typedef struct TreeNode {
   int data;
   struct TreeNode* left;
   struct TreeNode * right;
} TreeNode;

typedef enum {
   PREORDER,
   INORDER,
   POSTORDER
} TraversalType;

void build_tree(TreeNode** root, const int elements[], const int count);
void traverse(TreeNode** root, const TraversalType type);
void cleanup_tree(TreeNode** root);
