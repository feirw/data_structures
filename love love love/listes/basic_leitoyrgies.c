#include <stdio.h>
#include <stdlib.h>

// Ορισμός δομής κόμβου για τη συνδεδεμένη λίστα
struct listnode {
    int value;  // Τιμή του κόμβου
    struct listnode *next;  // Δείκτης στον επόμενο κόμβο
};

typedef struct listnode *List;  // Ορισμός τύπου List ως δείκτης σε κόμβο

// typedef struct listnode{
//     int value;
//     struct listnode *next;
// }*List;

// Συνάρτηση για προσθήκη στοιχείου στην αρχή της λίστας
void insert_start(List *head, int value) {
    List current_head = *head;  // Αποθήκευση της τρέχουσας κεφαλής
    List new_head = malloc(sizeof(struct listnode));  // Δημιουργία νέου κόμβου
    new_head->value = value;  // Αποθήκευση της τιμής
    new_head->next = current_head;  // Ο νέος κόμβος δείχνει στον προηγούμενο πρώτο κόμβο
    *head = new_head;  // Η κεφαλή δείχνει στον νέο κόμβο
}

// Συνάρτηση για προσθήκη στοιχείου στο τέλος της λίστας
void insert_end(List *head, int value) {
    List new_node = malloc(sizeof(struct listnode));  // Δημιουργία νέου κόμβου
    new_node->value = value;  // Αποθήκευση της τιμής
    new_node->next = NULL;  // Ο νέος κόμβος είναι ο τελευταίος, δείχνει στο NULL

    if (*head == NULL) {  // Αν η λίστα είναι κενή
        *head = new_node;  // Η κεφαλή δείχνει στον νέο κόμβο
    } else {
        // Διασχίζουμε τη λίστα για να βρούμε τον τελευταίο κόμβο
        List current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;  // Ο τελευταίος κόμβος δείχνει στον νέο κόμβο
    }
}

// Συνάρτηση για προσθήκη στοιχείου σε συγκεκριμένη θέση
void insert_at_position(List *head, int value, int pos) {
    List new_node = malloc(sizeof(struct listnode));  // Δημιουργία νέου κόμβου
    if (new_node == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    new_node->value = value;

    if (pos == 1) {  // Εισαγωγή στην αρχή της λίστας
        new_node->next = *head;
        *head = new_node;
        return;
    }
    
    List current = *head;
    int current_position = 1;

    // Διασχίζουμε τη λίστα μέχρι να φτάσουμε στη θέση pos - 1
    while (current != NULL && current_position < pos - 1) {
        current = current->next;
        current_position++;
    }

    // Αν η θέση είναι εκτός ορίων
    if (current == NULL) {
        printf("Invalid position: %d\n", pos);
        free(new_node);
        return;
    }

    // Εισαγωγή του νέου κόμβου στη θέση pos
    new_node->next = current->next;
    current->next = new_node;
}

// Συνάρτηση για διαγραφή ενός κόμβου με συγκεκριμένη τιμή
void delete_one_node(List head, int value) {
    List temp;
    while ((head != NULL) && head->value != value) {  // Όσο η λίστα δεν είναι κενή και δεν βρούμε τον κόμβο
        head = head->next;  // Προχωράμε στον επόμενο κόμβο
    }

    if (head != NULL) {  // Αν βρούμε τον κόμβο με την τιμή value
        temp = head;  // Αποθηκεύουμε τον κόμβο σε μια μεταβλητή temp
        head = temp->next;  // Ο δείκτης της λίστας δείχνει στον επόμενο κόμβο
        free(temp);  // Απελευθερώνουμε τη μνήμη του κόμβου
    }
}

// Συνάρτηση για διαγραφή όλων των κόμβων της λίστας
void delete_all(List *head) {
    List temp;
    while (*head != NULL) {  // Όσο η λίστα δεν είναι κενή
        temp = *head;  // Αποθηκεύουμε τον τρέχοντα κόμβο
        *head = (*head)->next;  // Κάνουμε την κεφαλή να δείχνει στον επόμενο κόμβο
        free(temp);  // Απελευθερώνουμε τη μνήμη
    }
}

// Συνάρτηση για εκτύπωση της λίστας
void printlist(List head) {
    printf("List: ");
    while (head != NULL) {  // Όσο δεν φτάσουμε στο τέλος της λίστας
        printf("-> %d ", head->value);  // Εκτύπωση της τιμής του κόμβου
        head = head->next;  // Μετάβαση στον επόμενο κόμβο
    }
    printf("-> NULL\n");  // Τέλος λίστας
}

// Συνάρτηση για αναζήτηση στοιχείου σε μια λίστα
List find(List head, int value) {
    while (head != NULL && head->value != value) {  // Διασχίζουμε τη λίστα για να βρούμε το στοιχείο
        head = head->next;
    }
    return head;  // Επιστρέφουμε τον κόμβο ή NULL αν δεν βρούμε το στοιχείο
}

// Συνάρτηση για έλεγχο αν η λίστα είναι κενή
int is_empty(List head) {
    return head == NULL;  // Επιστρέφει 1 αν η λίστα είναι κενή, αλλιώς 0
}

// Συνάρτηση για εύρεση του μήκους της λίστας
int length(List head) {
    if (head == NULL){
        return 0;
    }
    return 1 + length(head->next);  // Αναδρομική συνάρτηση για υπολογισμό του μήκους
}


// Συνάρτηση για ένωση δύο λιστών
List merge_lists(List head, List head2) {
    if (head == NULL) return head2;  // Αν η πρώτη λίστα είναι κενή, επιστρέφουμε τη δεύτερη
    if (head2 == NULL) return head;  // Αν η δεύτερη λίστα είναι κενή, επιστρέφουμε την πρώτη

    List merged = head;
    List current = head;

    while (current->next != NULL) {  // Βρίσκουμε τον τελευταίο κόμβο της πρώτης λίστας
        current = current->next;
    }

    current->next = head2;  // Σύνδεση του τελευταίου κόμβου της πρώτης λίστας με την αρχή της δεύτερης

    return merged;
}

// Συνάρτηση για αναστροφή της λίστας!!
void reverseList(List *head) {
    List prev = NULL, current = *head, next = NULL;

    while (current != NULL) {  // Διασχίζουμε τη λίστα
        next = current->next;  // Αποθηκεύουμε τον επόμενο κόμβο
        current->next = prev;  // Αντιστρέφουμε τον δείκτη του κόμβου
        prev = current;  // Προχωράμε τον prev
        current = next;  // Προχωράμε τον current
    }

    *head = prev;  // Ο νέος head είναι ο τελευταίος κόμβος
}

// Συνάρτηση για συγχώνευση δύο ταξινομημένων λιστών
List merge_sorted_lists(List left, List right) {
    if (left == NULL) return right;  // Αν η πρώτη λίστα είναι κενή
    if (right == NULL) return left;  // Αν η δεύτερη λίστα είναι κενή

    List result = NULL;

    if (left->value <= right->value) {  // Επιλέγουμε το μικρότερο στοιχείο
        result = left;
        result->next = merge_sorted_lists(left->next, right);
    } else {
        result = right;
        result->next = merge_sorted_lists(left, right->next);
    }
    return result;
}

// Συνάρτηση για διαίρεση της λίστας σε δύο μέρη
void split_list(List source, List *front, List *back) {
    List slow = source;
    List fast = source->next;

    while (fast != NULL) {  // Ο δείκτης fast κινείται δύο φορές πιο γρήγορα από τον slow
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *front = source;  // Το front είναι το πρώτο μέρος της λίστας
    *back = slow->next;  // Το back είναι το δεύτερο μέρος
    slow->next = NULL;  // Διαχωρίζουμε τις δύο λίστες
}

// Συνάρτηση Merge Sort για ταξινόμηση συνδεδεμένης λίστας
void merge_sort(List *head) {
    List current = *head;
    if (current == NULL || current->next == NULL) return;  // Αν η λίστα έχει 0 ή 1 στοιχείο, είναι ήδη ταξινομημένη

    List left = NULL;
    List right = NULL;

    split_list(current, &left, &right);  // Διαχωρίζουμε τη λίστα σε δύο μέρη

    merge_sort(&left);  // Αναδρομική ταξινόμηση του πρώτου μέρους
    merge_sort(&right);  // Αναδρομική ταξινόμηση του δεύτερου μέρους

    *head = merge_sorted_lists(left, right);  // Συγχώνευση των δύο ταξινομημένων μερών
}
// Συνάρτηση για εισαγωγή στοιχείου στη σωστή θέση ώστε η λίστα να παραμένει ταξινομημένη
void insert_sorted(List *head, int value) {
    List new_node = malloc(sizeof(struct listnode));  // Δημιουργία νέου κόμβου
    new_node->value = value;
    new_node->next = NULL;

    if (*head == NULL || (*head)->value >= value) {  // Αν η λίστα είναι κενή ή αν το νέο στοιχείο είναι μικρότερο από την κεφαλή
        new_node->next = *head;  // Ο νέος κόμβος δείχνει στην αρχή της λίστας
        *head = new_node;  // Ο νέος κόμβος γίνεται η κεφαλή
    } else {
        List current = *head;
        // Βρίσκουμε τη θέση όπου το νέο στοιχείο πρέπει να τοποθετηθεί
        while (current->next != NULL && current->next->value < value) {
            current = current->next;
        }
        new_node->next = current->next;  // Ο νέος κόμβος δείχνει στον επόμενο κόμβο
        current->next = new_node;  // Ο προηγούμενος κόμβος δείχνει στον νέο κόμβο
    }
}

// Συνάρτηση για υπολογισμό του αθροίσματος των στοιχείων της λίστας
int sum_list(List head) {
    int sum = 0;
    List current = head;

    while (current != NULL) {  // Διασχίζουμε τη λίστα
        sum += current->value;  // Προσθέτουμε την τιμή κάθε κόμβου στο άθροισμα
        current = current->next;  // Προχωράμε στον επόμενο κόμβο
    }

    return sum;
}

// Συνάρτηση για εύρεση του μέγιστου στοιχείου στη λίστα
int max_element(List head, int max) {
    List current = head;
    while (current != NULL) {
        if (current->value > max) {
            max = current->value;
        }
        current = current->next;
    }
    return max;
}

// Κύριο πρόγραμμα
int main() {

    List head = NULL;  // Αρχικοποίηση κενής λίστας
    
    List head2 = NULL;

    // Έλεγχος αν η λίστα είναι κενή
    if (is_empty(head) == 1) {
        printf("is empty\n");
    }

    // Προσθήκη στοιχείων στη λίστα
    insert_start(&head, 10);
    insert_start(&head, 11);
    insert_start(&head, 12);
/////////////////////////////////////////////////////
    insert_end(&head, 13);
    insert_end(&head, 14);

    insert_at_position(&head, 20, 3);

    /////////////////////////////////////////////

    insert_sorted(&head2,70);
    insert_sorted(&head2, 40);
    insert_sorted(&head2,24);
    insert_sorted(&head2,80);

    //print list 2
    printlist(head2);


    // Εκτύπωση της λίστας 1
    printlist(head);

    // Αναζήτηση ενός στοιχείου
    if (find(head, 2) != NULL) {
        printf("yes\n");
    } else {
        printf("no\n");
    }

    // Έλεγχος αν η λίστα είναι κενή
    if (is_empty(head)) {
        printf("is empty\n");
    } else {
        printf("isnt empty\n");
    }

    // Υπολογισμός μέγιστου στοιχείου
    int max = -1;
    max_element(head, max);
    printf("%d\n", max_element(head, max));

    // Υπολογισμός μέσου όρου
    printf("%d\n", sum_list(head) / length(head));

    // Αναστροφή της λίστας και εκτύπωση
    reverseList(&head);
    printlist(head);

    // Συγχώνευση λιστών και εκτύπωση
    List merged = merge_lists(head, head2);
    printlist(merged);

    // Ταξινόμηση λίστας με merge sort
    merge_sort(&merged);
    printlist(merged);

    // Διαγραφή όλων των κόμβων
    delete_all(&merged);
    printlist(merged);

    return 0;
}
