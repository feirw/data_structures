#include <stdio.h>
#include <stdlib.h>

struct treenode{
    int data;
    struct treenode *left;
    struct treenode *right;
};

typedef struct treenode *tree;

// eisagogh komvoy sto dendro
tree insert(int value){
    tree new_node = malloc(sizeof(struct treenode));
    new_node->data = value;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}

//ektypwsh inorder

void print_inorder(tree root) {
    if (root == NULL) return;
    print_inorder(root->left);
    printf("%d ", root->data);
    print_inorder(root->right);
}

//ektypwsh postorder
void print_postorder(tree root) {
    if (root == NULL) return;
    print_postorder(root->left);
    print_postorder(root->right);
    printf("%d ", root->data);
}

//ektypwsh preorder

void print_preorder(tree root) {
    if (root == NULL) return;
    printf("%d ", root->data);
    print_preorder(root->left);
    print_preorder(root->right);
}

//anazitisi stoixeioy dendroy 
int exists(tree root, int data) {
    if (root == NULL){
        return 0;
    }
        
    if (root->data == data){
        return 1;
    }
        
    if (data < root->data){
        return exists(root->left, data);
        return exists(root->right, data);
    }
}

//μεγιστο βαθος δενδρου = υψος δενδρου 
int depth(tree root) {
    if (root == NULL){
        return -1;
    }
    int left_depth = depth(root->left);
    int right_depth = depth(root->right);

    if(left_depth > right_depth){
        return 1 + left_depth;
    }else{
        return 1 + right_depth;
    }
    // εναλλακτικα
    // return 1 + ((left_depth > right_depth) ? left_depth : right_depth);
}

//ελεγχος αν το δεντρο ειναι κενο
int is_empty(tree root) {
    return root == NULL;
}

// Συνάρτηση για εύρεση του ελάχιστου κόμβου σε ένα υποδέντρο
tree find_min(tree root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

// Συνάρτηση για διαγραφή κόμβου από BST και το δενδρο να παραμενει δυαδικο δενδρο αναζητησης
tree delete_node(tree root, int value) {
    if (root == NULL) {
        return root; // Αν το δέντρο είναι άδειο
    }

    if (value < root->data) {
        // Αναζήτηση στο αριστερό υποδέντρο
        root->left = delete_node(root->left, value);
    } else if (value > root->data) {
        // Αναζήτηση στο δεξί υποδέντρο
        root->right = delete_node(root->right, value);
    } else {
        // Βρέθηκε ο κόμβος προς διαγραφή
        if (root->left == NULL && root->right == NULL) {
            // Περίπτωση 1: Φύλλο
            free(root);
            return NULL;
        } else if (root->left == NULL) {
            // Περίπτωση 2: Ένα παιδί (δεξί)
            tree temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            // Περίπτωση 2: Ένα παιδί (αριστερό)
            tree temp = root->left;
            free(root);
            return temp;
        } else {
            // Περίπτωση 3: Δύο παιδιά
            tree temp = find_min(root->right); // Βρίσκουμε τον ελάχιστο κόμβο στο δεξί υποδέντρο
            root->data = temp->data;          // Αντικαθιστούμε την τιμή του κόμβου
            root->right = delete_node(root->right, temp->data); // Διαγράφουμε τον ελάχιστο κόμβο
        }
    }

    return root;
}

//Ευρεση μεγιστου στοιχειου ενος δυαδικου δενδρου αναζητησης
int max(tree root,int maxel){
    tree temp = root;
    if(temp == NULL){
        return maxel;
    }
    if(temp->data > maxel){
        maxel = temp->data;
    }
    maxel = max(root->left, maxel);
    maxel = max(temp->right,maxel);
    return maxel;
}


int main(){

    tree root = insert(4);
    root->left = insert(2);
    root->right = insert(7);

    root->left->left = insert(1);
    root->left->right = insert(3);

    root->right->left = insert(5);
    root->right->right = insert(8);

    print_inorder(root);

    printf("\n");

    print_postorder(root);

    printf("\n");

    print_preorder(root);
    
    printf("\n");

    if(exists(root,2)){
        printf("it exists\n");
    }else{
        printf("no\n");
    }

    if(is_empty(root)){
        printf("no\n");
    }else{
        printf("yes\n");
    }

    int maxel = -1;

    printf("%d\n",max(root,maxel));


    root = delete_node(root, 2); // Διαγραφή φύλλου
    print_preorder(root);
    printf("\n");
    return 0;

}

// 1. Inorder Traversal (Ενδιάμεση διαδρομή)
// Η ενδιάμεση διαδρομή (Inorder traversal) περνάει από κάθε κόμβο του δέντρου σε αυτή την ακολουθία:

// Πρώτα επισκέπτεται το αριστερό υποδέντρο,
// Στη συνέχεια τον ίδιο τον κόμβο,
// Και τέλος το δεξιό υποδέντρο.
// Αυτός ο αλγόριθμος χρησιμοποιείται για την εκτύπωση των στοιχείων ενός δυαδικού δέντρου αναζήτησης σε αύξουσα σειρά.

// Χρονική Πολυπλοκότητα (Time Complexity):
// Ο αλγόριθμος επισκέπτεται κάθε κόμβο του δέντρου ακριβώς μία φορά.
// Επομένως, η χρονική πολυπλοκότητα είναι: O(n), όπου n είναι ο αριθμός των κόμβων του δέντρου.
// Χωρική Πολυπλοκότητα (Space Complexity):
// Η χωρική πολυπλοκότητα είναι κυρίως το αποτέλεσμα της αναδρομής.
// Στην περίπτωση του απλού αλγορίθμου (χωρίς στοίβα ή άλλες επιπλέον δομές), η αναδρομή διατηρεί O(h) χώρο στο call stack, όπου h είναι το ύψος του δέντρου.
// Στο χειρότερο σενάριο, αν το δέντρο είναι άκρως ακανόνιστο (σαν λίστα), το ύψος θα είναι O(n).
// Αν το δέντρο είναι ισχυρά ισορροπημένο, το ύψος θα είναι O(log n).
// Επομένως, η χωρική πολυπλοκότητα είναι O(h), όπου h το ύψος του δέντρου.
// 2. Postorder Traversal (Μεταγενέστερη διαδρομή)
// Η μεταγενέστερη διαδρομή (Postorder traversal) περνάει από κάθε κόμβο του δέντρου σε αυτή την ακολουθία:

// Πρώτα επισκέπτεται το αριστερό υποδέντρο,
// Στη συνέχεια το δεξιό υποδέντρο,
// Και τέλος τον ίδιο τον κόμβο.
// Αυτός ο αλγόριθμος χρησιμοποιείται συνήθως για να διαγράψει ένα δέντρο ή για να το αναλύσει πλήρως (π.χ. να υπολογίσει το μέγεθός του).

// Χρονική Πολυπλοκότητα (Time Complexity):
// Κάθε κόμβος επισκέπτεται ακριβώς μία φορά.
// Επομένως, η χρονική πολυπλοκότητα είναι O(n), όπου n είναι ο αριθμός των κόμβων του δέντρου.
// Χωρική Πολυπλοκότητα (Space Complexity):
// Η χωρική πολυπλοκότητα είναι επίσης O(h) λόγω της αναδρομής.
// Στο χειρότερο σενάριο, αν το δέντρο είναι άκρως ακανόνιστο, το ύψος θα είναι O(n).
// Σε ισχυρά ισορροπημένα δέντρα, το ύψος είναι O(log n).
// 3. Preorder Traversal (Προγενέστερη διαδρομή)
// Η προγενέστερη διαδρομή (Preorder traversal) περνάει από κάθε κόμβο του δέντρου σε αυτή την ακολουθία:

// Πρώτα επισκέπτεται τον ίδιο τον κόμβο,
// Στη συνέχεια το αριστερό υποδέντρο,
// Και τέλος το δεξιό υποδέντρο.
// Αυτός ο αλγόριθμος χρησιμοποιείται συνήθως για την αντιγραφή ή αναδημιουργία του δέντρου.

// Χρονική Πολυπλοκότητα (Time Complexity):
// Κάθε κόμβος επισκέπτεται ακριβώς μία φορά.
// Επομένως, η χρονική πολυπλοκότητα είναι O(n), όπου n είναι ο αριθμός των κόμβων του δέντρου.
// Χωρική Πολυπλοκότητα (Space Complexity):
// Η χωρική πολυπλοκότητα είναι επίσης O(h) λόγω της αναδρομής.
// Στο χειρότερο σενάριο, αν το δέντρο είναι άκρως ακανόνιστο, το ύψος θα είναι O(n).
// Σε ισχυρά ισορροπημένα δέντρα, το ύψος είναι O(log n).
// Συνοπτικά:
// Για τις τρεις μεθόδους (Inorder, Postorder, Preorder):

// Χρονική Πολυπλοκότητα: O(n), όπου n είναι ο αριθμός των κόμβων του δέντρου.
// Χωρική Πολυπλοκότητα: O(h), όπου h είναι το ύψος του δέντρου.
// Παράδειγμα:
// Για το δέντρο:

// markdown
// Αντιγραφή
// Επεξεργασία
//        60
//        /  \
//      40    70
//     /        \
//    20         80
// Inorder: 20, 40, 60, 70, 80
// Preorder: 60, 40, 20, 70, 80
// Postorder: 20, 40, 80, 70, 60




// BFS O(N) O(N)
// Χαρακτηριστικό	        DFS	                                BFS
// Πολιτική Αναζήτησης	    Βαθιά (depth-first)	                Οριζόντια (breadth-first)
// Δομή Δεδομένων	        Στοίβα (stack) ή Αναδρομή	        Ουρά (queue)
// Τρόπος Εξερεύνησης	    Εξετάζει το βάθος του δέντρου	    Εξετάζει επίπεδα (γραμμικά)
// Χρονική Πολυπλοκότητα	O(n)	                            O(n)
// Χωρική Πολυπλοκότητα	O(h) (ύψος δέντρου)	                O(n) (σε περίπτωση πλήρους γραφήματος)
// Κατάλληλο για	        Εξερεύνηση και εύρεση μονοπατιών	Εύρεση της μικρότερης διαδρομής σε γράφο/δενδρο
//                         ανίχνευση κύκλων                    πρόγραμμα με λαβυρινθους
//                         Μεγίστου στοιχειου σε δενδρο       Το μονοπατι π ακολουθει ειναι το μικροτερο δυνατο
//                         μικρο βαθος                         αποφυγη αναδρομης
//                         αναδρομικη διερευνηση