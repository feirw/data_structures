#include <stdio.h>
#include <stdlib.h>

// Δομή κόμβου του δέντρου
struct treenode {
    int data;
    struct treenode *left;
    struct treenode *right;
};

typedef struct treenode *tree;

// Συνάρτηση για προσθήκη στοιχείου στο ταξινομημένο δυαδικό δέντρο
tree addtree(tree root, int x) {
    if (root == NULL) {
        root = malloc(sizeof(struct treenode));
        root->data = x;
        root->left = NULL;
        root->right = NULL;
    } else if (x < root->data) {
        root->left = addtree(root->left, x);
    } else if (x > root->data) {
        root->right = addtree(root->right, x);
    }
    return root;
}

// Συνάρτηση για εκτύπωση του δέντρου in-order
void print_inorder(tree root) {
    if (root != NULL) {
        print_inorder(root->left);
        printf("%d ", root->data);
        print_inorder(root->right);
    }
}

int main() {
    tree root = NULL;

    // Προσθήκη στοιχείων στο δέντρο
    root = addtree(root, 4);
    root = addtree(root, 2);
    root = addtree(root, 6);
    root = addtree(root, 1);
    root = addtree(root, 3);
    root = addtree(root, 5);
    root = addtree(root, 7);

    // Εκτύπωση του δέντρου in-order
    printf("In-order traversal: ");
    print_inorder(root);
    printf("\n");

    return 0;
}
