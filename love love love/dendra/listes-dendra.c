#include <stdio.h>
#include <stdlib.h>


//μετατρεπω ενα δενδτρο σε λιστα 

// Δομή κόμβου του δέντρου
struct treenode {
    int data;
    struct treenode *left;
    struct treenode *right;
};

typedef struct treenode *tree;

// Δομή κόμβου της συνδεδεμένης λίστας
struct listnode {
    int value;
    struct listnode *next;
};

typedef struct listnode *list;

void print_inorder(tree root) {
    if (root == NULL) return;  // Αν ο κόμβος είναι NULL, επιστρέφουμε
    print_inorder(root->left);  // Επισκέπτεται το αριστερό υποδέντρο
    printf("%d ", root->data);  // Εκτυπώνει τα δεδομένα του τρέχοντος κόμβου
    print_inorder(root->right); // Επισκέπτεται το δεξιό υποδέντρο
}

// Συνάρτηση για την εισαγωγή ενός νέου κόμβου στη συνδεδεμένη λίστα
void insert(list *head, int value) {
    list new_node = malloc(sizeof(struct listnode));  // Δημιουργία νέου κόμβου
    new_node->value = value;  // Αποθήκευση της τιμής
    new_node->next = *head;  // Ο νέος κόμβος δείχνει στον προηγούμενο πρώτο κόμβο
    *head = new_node;  // Η κεφαλή δείχνει στον νέο κόμβο
}

// Συνάρτηση για την in-order traversal του δέντρου και γέμισμα της λίστας
void fill_the_list(tree root, list *head) {
    if (root == NULL) return;

    // Αναδρομική κλήση για το αριστερό υποδέντρο
    fill_the_list(root->right, head);

    // Εισαγωγή του δεδομένου του τρέχοντος κόμβου στη λίστα
    insert(head, root->data);

    // Αναδρομική κλήση για το δεξί υποδέντρο
    fill_the_list(root->left, head);
}

// Συνάρτηση για την εκτύπωση της συνδεδεμένης λίστας
void print_list(list head) {
    while (head != NULL) {
        printf("%d ", head->value);
        head = head->next;
    }
    printf("\n");
}

// Συνάρτηση για τη δημιουργία ενός νέου κόμβου στο δέντρο
tree insert_tree(int value) {
    tree new_node = malloc(sizeof(struct treenode));  // Δημιουργία νέου κόμβου
    new_node->data = value;  // Αποθήκευση της τιμής
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

int main() {
    // Δημιουργία ενός δυαδικού δέντρου
    tree root = insert_tree(4);
    root->left = insert_tree(2);
    root->right = insert_tree(7);
    root->left->left = insert_tree(1);
    root->left->right = insert_tree(3);
    root->right->left = insert_tree(5);
    root->right->right = insert_tree(8);

    // Δημιουργία συνδεδεμένης λίστας και γέμισμα με τα δεδομένα του δέντρου
    list head = NULL;
    fill_the_list(root, &head);

    print_inorder(root);
    printf("\n");
    // Εκτύπωση της λίστας
    print_list(head);

    return 0;
}
