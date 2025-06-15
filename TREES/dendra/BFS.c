#include <stdio.h>
#include <stdlib.h>

// Δομή για τον κόμβο του δέντρου
typedef struct treenode {
    int value;
    struct treenode *left;
    struct treenode *right;
} *tree;

// Δομή για τον κόμβο της ουράς
typedef struct listnode {
    tree treenode;
    struct listnode *next;
} *list;

// Συνάρτηση για εισαγωγή στοιχείου στην ουρά (στο τέλος της λίστας)
void insert(list *head, tree root) {
    list new_node = malloc(sizeof(struct listnode));
    new_node->treenode = root;
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
    } else {
        list temp = *head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

// Συνάρτηση για αφαίρεση του πρώτου στοιχείου από την ουρά (από την αρχή)
tree pop(list *head) {
    if (*head == NULL) return NULL;

    list temp = *head;
    *head = temp->next;
    tree treenode = temp->treenode;
    free(temp);
    return treenode;
}

// Συνάρτηση BFS
void bfs(tree root) {
    if (root == NULL) return;

    list worklist = NULL;
    insert(&worklist, root);

    while (worklist != NULL) {
        tree tmp = pop(&worklist);
        printf("%d ", tmp->value);

        if (tmp->left) insert(&worklist, tmp->left);
        if (tmp->right) insert(&worklist, tmp->right);
    }
}

// Συνάρτηση για δημιουργία ενός νέου κόμβου δέντρου
tree create_node(int value) {
    tree node = malloc(sizeof(struct treenode));
    node->value = value;
    node->left = node->right = NULL;
    return node;
}

int main() {
    // Δημιουργία ενός δέντρου για δοκιμές
    tree root = create_node(1);
    root->left = create_node(2);
    root->right = create_node(3);
    root->left->left = create_node(4);
    root->left->right = create_node(5);
    root->right->left = create_node(6);
    root->right->right = create_node(7);

    // Εκτέλεση BFS
    printf("BFS Traversal: ");
    bfs(root);
    printf("\n");

    return 0;
}
