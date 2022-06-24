struct Node {
   Item val;
   struct Node* next;
};

typedef struct Node Node;

Node* newNode(Item val) {
   Node* l = malloc(sizeof(Node));
   l->val = val;
   l->next = NULL;
   return l;
}
