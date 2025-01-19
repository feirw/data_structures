#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Δομή για τον κόμβο του δέντρου
struct treenode {
    int data;  // Δεδομένα του κόμβου
    struct treenode *left;  // Δείκτης στον αριστερό υποκόμβο
    struct treenode *right; // Δείκτης στον δεξιό υποκόμβο
};

// Ορισμός τύπου "tree" ως δείκτη σε κόμβο
typedef struct treenode *tree;

// Συνάρτηση για την εισαγωγή ενός νέου κόμβου στο δέντρο
tree insert(int value) {
    tree new_node = malloc(sizeof(struct treenode));  // Δημιουργία νέου κόμβου
    new_node->data = value;  // Ανάθεση της τιμής στον κόμβο
    new_node->left = NULL;    // Το αριστερό παιδί είναι NULL (κανένας αριστερός κόμβος)
    new_node->right = NULL;   // Το δεξί παιδί είναι NULL (κανένας δεξιός κόμβος)

    return new_node;  // Επιστρέφουμε τον νέο κόμβο
}

// Συνάρτηση για την εκτύπωση της διαδρομής inorder (ενδιάμεση διαδρομή) του δέντρου o(N)
void print_inorder(tree root) {
    if (root == NULL) return;  // Αν ο κόμβος είναι NULL, επιστρέφουμε
    print_inorder(root->left);  // Επισκέπτεται το αριστερό υποδέντρο
    printf("%d ", root->data);  // Εκτυπώνει τα δεδομένα του τρέχοντος κόμβου
    print_inorder(root->right); // Επισκέπτεται το δεξιό υποδέντρο
}

// Συνάρτηση για την εκτύπωση της διαδρομής postorder (μεταγενέστερη διαδρομή) του δέντρου
void print_postorder(tree root) {
    if (root == NULL) return;  // Αν ο κόμβος είναι NULL, επιστρέφουμε
    print_postorder(root->left);   // Επισκέπτεται το αριστερό υποδέντρο
    print_postorder(root->right);  // Επισκέπτεται το δεξιό υποδέντρο
    printf("%d ", root->data);     // Εκτυπώνει τα δεδομένα του τρέχοντος κόμβου
}

// Συνάρτηση για την εκτύπωση της διαδρομής preorder (προγενέστερη διαδρομή) του δέντρου
void print_preorder(tree root) {
    if (root == NULL) return;  // Αν ο κόμβος είναι NULL, επιστρέφουμε
    printf("%d ", root->data);  // Εκτυπώνει τα δεδομένα του τρέχοντος κόμβου
    print_preorder(root->left);  // Επισκέπτεται το αριστερό υποδέντρο
    print_preorder(root->right); // Επισκέπτεται το δεξιό υποδέντρο
}

// Συνάρτηση για να ελέγξει αν ένα στοιχείο υπάρχει στο δέντρο
int exists(tree root, int data) {
    if (root == NULL) {
        return 0;  // Αν ο κόμβος είναι NULL, το στοιχείο δεν υπάρχει
    }
        
    if (root->data == data) {
        return 1;  // Βρέθηκε το στοιχείο στο δέντρο
    }
        
    if (data < root->data) {
        // Αν το στοιχείο είναι μικρότερο από τον τρέχοντα κόμβο, ψάχνουμε στο αριστερό υποδέντρο
        return exists(root->left, data);
    } else {
        // Αν το στοιχείο είναι μεγαλύτερο από τον τρέχοντα κόμβο, ψάχνουμε στο δεξιό υποδέντρο
        return exists(root->right, data);
    }
}

// Συνάρτηση για την εύρεση του μέγιστου βάθους του δέντρου (ύψος του δέντρου)
int depth(tree root) {
    if (root == NULL) {
        return -1;  // Αν ο κόμβος είναι NULL, το βάθος είναι -1
    }
    // Υπολογίζουμε το βάθος του αριστερού και του δεξιού υποδέντρου
    int left_depth = depth(root->left);
    int right_depth = depth(root->right);

    // Επιστρέφουμε το μέγιστο βάθος μεταξύ των δύο υποδέντρων, συν 1 για τον τρέχοντα κόμβο
    if(left_depth > right_depth){
        return 1 + left_depth;
    }else{
        return 1 + right_depth;
    }
}

// Συνάρτηση για να ελέγξει αν το δέντρο είναι άδειο
int is_empty(tree root) {
    return root == NULL;  // Αν ο κόμβος είναι NULL, το δέντρο είναι άδειο
}

// Συνάρτηση για εύρεση του ελάχιστου κόμβου σε ένα υποδέντρο (χρησιμοποιείται για διαγραφή κόμβων)
tree find_min(tree root) {
    while (root->left != NULL) {
        root = root->left;  // Εξετάζουμε το αριστερό υποδέντρο μέχρι να φτάσουμε στο ελάχιστο κόμβο
    }
    return root;  // Επιστρέφουμε τον κόμβο με την ελάχιστη τιμή
}

// Συνάρτηση για τη διαγραφή ενός κόμβου από το δέντρο (ειδικά από δέντρο δυαδικής αναζήτησης)
tree delete_node(tree root, int value) {
    if (root == NULL) {
        return root;  // Αν το δέντρο είναι άδειο, επιστρέφουμε NULL
    }

    if (value < root->data) {
        // Αν το στοιχείο είναι μικρότερο από τον τρέχοντα κόμβο, ψάχνουμε στο αριστερό υποδέντρο
        root->left = delete_node(root->left, value);
    } else if (value > root->data) {
        // Αν το στοιχείο είναι μεγαλύτερο από τον τρέχοντα κόμβο, ψάχνουμε στο δεξιό υποδέντρο
        root->right = delete_node(root->right, value);
    } else {
        // Βρέθηκε ο κόμβος προς διαγραφή
        if (root->left == NULL && root->right == NULL) {
            // Περίπτωση 1: Ο κόμβος είναι φύλλο, απλά τον διαγράφουμε
            free(root);
            return NULL;
        } else if (root->left == NULL) {
            // Περίπτωση 2: Ο κόμβος έχει μόνο δεξί παιδί, επιστρέφουμε το δεξί παιδί
            tree temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            // Περίπτωση 2: Ο κόμβος έχει μόνο αριστερό παιδί, επιστρέφουμε το αριστερό παιδί
            tree temp = root->left;
            free(root);
            return temp;
        } else {
            // Περίπτωση 3: Ο κόμβος έχει δύο παιδιά
            tree temp = find_min(root->right);  // Βρίσκουμε τον ελάχιστο κόμβο στο δεξί υποδέντρο
            root->data = temp->data;  // Αντικαθιστούμε τα δεδομένα του τρέχοντος κόμβου με αυτά του ελάχιστου
            root->right = delete_node(root->right, temp->data);  // Διαγράφουμε τον ελάχιστο κόμβο
        }
    }

    return root;  // Επιστρέφουμε τη ριζική δομή του δέντρου μετά τη διαγραφή
}

// Συνάρτηση για εύρεση του μέγιστου στοιχείου σε ένα δέντρο
int max(tree root, int maxel) {
    tree temp = root;
    if (temp == NULL) {
        return maxel;  // Αν το δέντρο είναι άδειο, επιστρέφουμε το τρέχον μέγιστο στοιχείο
    }
    if (temp->data > maxel) {
        maxel = temp->data;  // Αν βρούμε μεγαλύτερο στοιχείο, το ανανεώνουμε
    }
    // maxel = max(root->left, maxel);  // Ελέγχουμε το αριστερό υποδέντρο
    maxel = max(temp->right, maxel); // Ελέγχουμε το δεξί υποδέντρο
    return maxel;  // Επιστρέφουμε το μέγιστο στοιχείο
}
//αθροισμα κομβων
int sumnodes(tree root, int sum) {
    if (root == NULL) {
        return sum;
    }
    sum = sumnodes(root->left, sum);  
    sum += root->data;               
    sum = sumnodes(root->right, sum); 
    
    return sum; // Return the total sum after traversing the whole tree
}

//ελεγχος αν το δυαδικο δενδρο ειναι δυαδικο δενδρο αναζητησης
int isBSTUtil(tree root, int *prev) {
    if (root == NULL) {
        return 1;  // Κενό υποδέντρο είναι πάντα BST
    }

    // Ελέγχουμε πρώτα το αριστερό υποδέντρο
    if (!isBSTUtil(root->left, prev)) {
        return 0;
    }

    // Αν η τρέχουσα τιμή είναι μικρότερη ή ίση από την προηγούμενη τιμή, δεν είναι BST
    if (root->data <= *prev) {
        return 0;
    }

    // Ενημερώνουμε την προηγούμενη τιμή και προχωρούμε στο δεξί υποδέντρο
    *prev = root->data;

    return isBSTUtil(root->right, prev);
}

// Συνάρτηση για να ελέγξουμε αν το δέντρο είναι Binary Search Tree (BST)
int is_binarytree(tree root) {
    int prev = INT_MIN;  // Η προηγούμενη τιμή στην in-order αναδρομή
    return isBSTUtil(root, &prev);
}

// Συνάρτηση για να βρούμε το μέγιστο άθροισμα διαδρομής
int max_sum_path(tree root, int *result) {
    if (root == NULL) {
        return 0;
    }

    // Αναδρομική κλήση για τα αριστερά και δεξιά υποδέντρα
    int left_sum = max_sum_path(root->left, result);
    int right_sum = max_sum_path(root->right, result);

    // Βρίσκουμε το μέγιστο άθροισμα διαδρομής που περνάει από τον κόμβο
    int max_single;
    if (left_sum > right_sum) {
        max_single = left_sum + root->data;
    } else {
        max_single = right_sum + root->data;
    }

    // Μέγιστο άθροισμα διαδρομής με ή χωρίς το κόμβο στο κέντρο
    int max_top = left_sum + right_sum + root->data;

    // Ενημέρωση του μέγιστου αποτελέσματος
    if (*result > max_top) {
        *result = *result;
    } else {
        *result = max_top;
    }

    // Επιστρέφουμε το μέγιστο άθροισμα για να το χρησιμοποιήσει ο γονέας
    if (max_single > 0) {
        return max_single;
    } else {
        return 0;
    }
}

int main() {
    // Δημιουργία δέντρου και εισαγωγή στοιχείων
    tree root = insert(4);
    root->left = insert(2);
    root->right = insert(7);
    root->left->left = insert(1);
    root->left->right = insert(3);
    root->right->left = insert(5);
    root->right->right = insert(8);


    if (is_binarytree(root)) {
        printf("Το δέντρο είναι Binary Search Tree (BST).\n");
    } else {
        printf("Το δέντρο δεν είναι Binary Search Tree (BST).\n");
    }
    int result = INT_MIN;
    printf("%d\n",max_sum_path(root,&result));

    
    // Εκτύπωση διαδρομών inorder, postorder και preorder
    print_inorder(root);  // Εκτυπώνει: 1 2 3 4 5 7 8
    printf("\n");

    print_postorder(root);  // Εκτυπώνει: 1 3 2 5 8 7 4
    printf("\n");

    print_preorder(root);  // Εκτυπώνει: 4 2 1 3 7 5 8
    printf("\n");

    // Έλεγχος αν το στοιχείο 2 υπάρχει στο δέντρο
    if (exists(root, 2)) {
        printf("it exists\n");
    } else {
        printf("no\n");
    }

    // Έλεγχος αν το δέντρο είναι άδειο
    if (is_empty(root)) {
        printf("no isnt empty\n");
    } else {
        printf("yes\n");
    }

    // Ευρεση του μέγιστου στοιχείου
    int maxel = -1;
    printf("max : %d\n", max(root, maxel));  // Εκτυπώνει το μέγιστο στοιχείο

    //Αθροισμα στοιχειων κομβου
    int sum = 0;
    printf("sum : %d\n",sumnodes(root,sum));



    // Διαγραφή κόμβου με τιμή 2 και εκτύπωση του δέντρου μετά τη διαγραφή
    root = delete_node(root, 2);
    print_preorder(root);  // Εκτύπωση του δέντρου μετά τη διαγραφή του κόμβου
    printf("\n");

    return 0;
}
