struct node{
	int val;
	struct node *next;
	struct node *prev;
};

struct list{
	struct node *head;
	struct node *tail;
};

void init(struct list *);
int pop(struct list *);
void print_row(struct list);

int length(struct list);
void print(struct list);
void push_front(struct list *, int);
void push_back(struct list *, int);

void clear(struct list *);
void remove_val(struct list *, int);
void sort_ascending(struct list *);
void sord_descending(struct list *);

void insert(struct list *, int, int);
