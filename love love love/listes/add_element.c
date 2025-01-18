#include <stdio.h>
#include <stdlib.h>

struct listnode {
    int value;
    struct listnode *next;
};
typedef struct listnode *List;

// Συνάρτηση για προσθήκη στοιχείου στην αρχή της λίστας
void insert_start(List *head, int value) {
    List current_head = *head; // Αποθηκεύουμε την τρέχουσα κεφαλή σε μια μεταβλητή
    List new_head = malloc(sizeof(struct listnode)); // Δημιουργία νέου κόμβου
    new_head->value = value; // Αποθήκευση της τιμής στον νέο κόμβο
    new_head->next = current_head; // Ο νέος κόμβος δείχνει στον προηγούμενο πρώτο κόμβο
    *head = new_head; // Η κεφαλή δείχνει στον νέο κόμβο
}

// Συνάρτηση για προσθήκη στοιχείου στο τέλος της λίστας
void insert_end(List *head, int value) {
    List new_node = malloc(sizeof(struct listnode)); // Δημιουργία νέου κόμβου
    new_node->value = value; // Αποθήκευση της τιμής
    new_node->next = NULL; // Ο νέος κόμβος είναι ο τελευταίος, δείχνει στο NULL

    if (*head == NULL) { // Αν η λίστα είναι κενή
        *head = new_node; // Η κεφαλή δείχνει στον νέο κόμβο
    } else {
        // Διασχίζουμε τη λίστα για να βρούμε τον τελευταίο κόμβο
        List current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        // Ο τελευταίος κόμβος δείχνει στον νέο κόμβο
        current->next = new_node;
    }
}
//Προσθηκη στην θεση pos που θα δωσει ο χρηστης
void insert_at_position(List *head, int value, int pos) {
    // Δημιουργία του νέου κόμβου
    List new_node = malloc(sizeof(struct listnode));
    if (new_node == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    new_node->value = value;

    // Ειδική περίπτωση: Εισαγωγή στην αρχή της λιστας
    if (pos == 1) {
        new_node->next = *head;
        *head = new_node;
        return;
    }
    // Διασχίζουμε τη λίστα μέχρι να φτάσουμε στη θέση pos - 1
    List current = *head; // ειμαστε εκει που δειχνει η κεφαλη δλδ στον πρωτο κομβο
    int current_position = 1;

    while (current != NULL && current_position < pos - 1) {//ξεκιναμε να διασχιζουμε την λιστα
        current = current->next;
        current_position++; 
    }

    // Αν η θέση pos είναι εκτός ορίων
    if (current == NULL) {
        printf("Invalid position: %d\n", pos);
        free(new_node); // Απελευθέρωση μνήμης
        return;
    }

    // Εισαγωγή του νέου κόμβου στη θέση pos
    new_node->next = current->next; // ο νεος κομβος δειχνει τωρα εκει που εδειχνε ο κομβος που βρισκεται στην θεση pos-1 
    current->next = new_node; //ο κιμβος π βρισκεται στηνν θση pos -1 δειχνει τωρα στον νεο κομβο που φτιαξαμε
}

//Διαγραφουμε εναν κομβο ο οποιος εχει μια συγκεκριμενη τιμη
void delete_one_node(List *head,int value){
    List temp;
    while((*head != NULL) && (*head)->value != value) { //οσο η λιστα δεν ειναι κενη και οσο δεν βρισκουμε τον κομβο με την συγκεκριμενη τιμη
        head = &((*head)->next); // το list είναι δείκτης στον δείκτη της λίστας γι' αυτό χρησιμοποιούμε το &((*list)->next) για να προχωρήσουμε στον επόμενο κόμβο
    }
    if (*head != NULL) {//Ελέγχει αν βρήκαμε τον κόμβο με την τιμή value ή αν φτάσαμε στο τέλος της λίστας χωρίς να τον βρούμε.
        temp = *head; // Αποθηκεύουμε τον κόμβο που θέλουμε να διαγράψουμε σε μια μεταβλητή temp. Χρειαζόμαστε αυτό το "αντίγραφο" για να μπορέσουμε να το απελευθερώσουμε αργότερα με το free().
        *head = temp->next; //Ο δείκτης της λίστας (*list) δείχνει πλέον στον επόμενο κόμβο του τρέχοντος κόμβου (δηλαδή παραλείπουμε τον κόμβο που θέλουμε να διαγράψουμε).
        free(temp);//Εδώ απελευθερώνουμε τη μνήμη που είχαμε δεσμεύσει για τον κόμβο με την τιμή value. Έτσι, διαγράφουμε τον κόμβο από τη μνήμη.
    }
}
//Διαγραφουμε ολη την λιστα απο την αρχη της
void delete_all(List *head) {
    List temp;
    // Ενώ η λίστα δεν είναι άδεια (δηλαδή υπάρχουν ακόμα κόμβοι)
    while (*head != NULL) {
        // Αποθηκεύουμε τον τρέχοντα κόμβο σε μια προσωρινή μεταβλητή
        temp = *head;
        // Κάνουμε την κεφαλή να δείχνει στον επόμενο κόμβο
        *head = (*head)->next;
        // Απελευθερώνουμε τη μνήμη του τρέχοντος κόμβου
        free(temp);
    }
}

//Διαγραφη από το τελος
void delete_all_reverse(List *head) {
    List temp, current;
    // Αν η λίστα είναι κενή, δεν κάνουμε τίποτα
    if (*head == NULL) {
        return;
    }
    // Διασχίζουμε όλη τη λίστα για να φτάσουμε στον τελευταίο κόμβο
    current = *head;
    while (current != NULL && current->next != NULL) {
        current = current->next;
    }
    // Αν έχουμε μόνο έναν κόμβο, τότε το head δείχνει στον ίδιο κόμβο
    while (*head != NULL) {
        // Ψάχνουμε τον κόμβο πριν τον τελευταίο
        current = *head;
        while (current->next && current->next->next != NULL) {
            current = current->next;
        }
        // Αποθηκεύουμε τον τελευταίο κόμβο και ελευθερώνουμε τη μνήμη του
        temp = current->next;
        current->next = NULL; // Ο τελευταίος κόμβος διαγράφεται
        free(temp); // Ελευθερώνουμε τη μνήμη του τελευταίου κόμβου
    }
    // Η λίστα είναι άδεια τώρα, οπότε το head θα δείχνει στο NULL
    *head = NULL;
}

// Συνάρτηση για εκτύπωση της λίστας
void printlist(List head) {
    printf("List: ");
    while (head != NULL) { // Όσο δεν έχουμε φτάσει στο τέλος της λίστας
        printf("-> %d ", head->value); // Εκτύπωση της τιμής του κόμβου
        head = head->next; // Μετάβαση στον επόμενο κόμβο
    }
    printf("-> NULL\n"); // Τέλος λίστας
}

//Αναζήτηση στοιχειου με τιμη value σε μια λιστα
List find(List head, int value) {
    while(head != NULL && head->value != value) {
        head = head->next;
    }
    return head;
}

//Έλεγχος αν η λιστα ειναι κενη
int is_empty(List head) {
    return head == NULL;
}

//Εύρεση μήκους της λίστας
int length(List head) {
    if (head == NULL){
        return 0;
    }
    return 1 + length(head->next);
}

//Αναστροφη λιστας
void reverseList(List *head) {
    List prev = NULL;       // Δεν υπάρχει προηγούμενος στην αρχή
    List current = *head; // Ξεκινάμε από την αρχή της λίστας
    List next = NULL;       // Θα χρησιμοποιηθεί για να κρατάμε τον επόμενο κόμβο

    while (current != NULL) {
        next = current->next;  // Αποθηκεύουμε τον επόμενο κόμβο
        current->next = prev;  // Αντιστρέφουμε τον δείκτη του current
        prev = current;        // Προχωράμε τον prev στο current
        current = next;        // Προχωράμε τον current στον επόμενο
    }

    *head = prev;          // Ο νέος head είναι ο τελευταίος κόμβος
}

//Ταξινόμηση της λιστας

// Κύριο πρόγραμμα
int main() {
    List head = NULL; // Αρχικοποίηση της λίστας ως κενής

    if(is_empty(head)){
        printf("is empty\n");
    }

    // Προσθήκη στοιχείων στην αρχή
    insert_start(&head, 10);
    insert_start(&head, 11);
    insert_start(&head, 12);

    // Προσθήκη στοιχείων στο τέλος
    insert_end(&head, 13);
    insert_end(&head, 14);

    insert_at_position(&head,20,3);

    // Εκτύπωση της λίστας
    printlist(head);

    if(find(head,2) != NULL){
        printf("yes\n");
    }else{
        printf("no\n");
    }


    if(is_empty(head)){
        printf("is empty\n");
    }else{
        printf("isnt empty\n");
    }

    printf("%d\n",length(head));

    reverseList(&head);

     printlist(head);
    
    delete_all(&head);

    printlist(head);

    return 0;
}
