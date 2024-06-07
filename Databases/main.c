#define _CRT_SECURE_NO_WARNINGS
#define MAX_BUFFER 1024
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Create Node
struct Book 
{
    char name[MAX_BUFFER];
    char author[MAX_BUFFER];
    char genre[MAX_BUFFER];
    int year;
    int price;
    int rating;

    struct Book* left;
    struct Book* right;
    int height;
};

int height(struct Book* book);
bool search_book(struct Book* book, char* token);
struct Book* new_book(char* name, char* author, char* genre, int year, int price, int rating);                         
struct Book* right_rotate(struct Book* y);
struct Book* left_rotate(struct Book* x);
int get_balance(struct Book* book);
struct Book* insert_book(struct Book* book, char* name, char* author, char* genre, int year, int price, int rating);
struct Book* min_value_book(struct Book* book);
struct Book* delete_book(struct Book* root, char* name);
bool search_book_name(struct Book* book, char* name);
struct Book* edit(struct Book* book, char* name_to_replace, char* name, char* author, char* genre, int year, int price, int rating);
void lnr_printtree(struct Book* root);
void nlr_printtree(struct Book* root);
void lrn_printtree(struct Book* root);


int main() 
{
    struct Book* root = NULL;

    while (true)
    {
        char input[MAX_BUFFER];
        fgets(input, MAX_BUFFER, stdin);

        char* token = strtok(input, " ");
        token[strcspn(token, "\n")] = 0;

        if (strcmp(token, "ADD") == 0)
        {
            char name[MAX_BUFFER];
            char author[MAX_BUFFER];
            char genre[MAX_BUFFER];
            int year, price, rating;

            if ((token = strtok(NULL, " ")) == NULL)
            {
                printf("Parse error\n");
                continue;
            }
            else
            {
                token[strcspn(token, "\n")] = 0;
                strcpy(name, token);
            }

            if ((token = strtok(NULL, " ")) == NULL)
            {
                printf("Parse error\n");
                continue;
            }
            else
            {
                token[strcspn(token, "\n")] = 0;
                strcpy(author, token);
            }

            if ((token = strtok(NULL, " ")) == NULL)
            {
                printf("Parse error\n");
                continue;
            }
            else
            {
                token[strcspn(token, "\n")] = 0;
                strcpy(genre, token);
            }

            if ((token = strtok(NULL, " ")) == NULL)
            {
                printf("Parse error\n");
                continue;
            }
            else
            {
                token[strcspn(token, "\n")] = 0;
                year = atoi(token);
            }

            if ((token = strtok(NULL, " ")) == NULL)
            {
                printf("Parse error\n");
                continue;
            }
            else
            {
                token[strcspn(token, "\n")] = 0;
                price = atoi(token);
            }

            if ((token = strtok(NULL, " ")) == NULL)
            {
                printf("Parse error\n");
                continue;
            }
            else
            {
                token[strcspn(token, "\n")] = 0;
                rating = atoi(token);
            }

            root = insert_book(root, name, author, genre, year, price, rating);
        }
        else if (strcmp(token, "DELETE") == 0)
        {
            if ((token = strtok(NULL, " ")) == NULL)
            {
                printf("Parse error\n");
                continue;
            }
            else
            {
                token[strcspn(token, "\n")] = 0;
                root = delete_book(root, token);
            }
        }
        else if (strcmp(token, "SEARCH") == 0)
        {
            if ((token = strtok(NULL, " ")) == NULL)
            {
                printf("Parse error\n");
                continue;
            }
            else
            {
                token[strcspn(token, "\n")] = 0;

                if (search_book(root, token))
                {
                    printf("YES\n");
                }
                else
                {
                    printf("NO\n");
                }
            }
        }
        else if (strcmp(token, "EDIT") == 0)
        {
            char old_name[MAX_BUFFER];
            char new_name[MAX_BUFFER];
            char author[MAX_BUFFER];
            char genre[MAX_BUFFER];
            int year, price, rating;

            if ((token = strtok(NULL, " ")) == NULL)
            {
                printf("Parse error\n");
                continue;
            }
            else
            {
                token[strcspn(token, "\n")] = 0;
                token[strcspn(token, ":")] = 0;
                strcpy(old_name, token);
            }

            if ((token = strtok(NULL, " ")) == NULL)
            {
                printf("Parse error\n");
                continue;
            }
            else
            {
                token[strcspn(token, "\n")] = 0;
                strcpy(new_name, token);
            }

            if ((token = strtok(NULL, " ")) == NULL)
            {
                printf("Parse error\n");
                continue;
            }
            else
            {
                token[strcspn(token, "\n")] = 0;
                strcpy(author, token);
            }

            if ((token = strtok(NULL, " ")) == NULL)
            {
                printf("Parse error\n");
                continue;
            }
            else
            {
                token[strcspn(token, "\n")] = 0;
                strcpy(genre, token);
            }

            if ((token = strtok(NULL, " ")) == NULL)
            {
                printf("Parse error\n");
                continue;
            }
            else
            {
                token[strcspn(token, "\n")] = 0;
                year = atoi(token);
            }

            if ((token = strtok(NULL, " ")) == NULL)
            {
                printf("Parse error\n");
                continue;
            }
            else
            {
                token[strcspn(token, "\n")] = 0;
                price = atoi(token);
            }

            if ((token = strtok(NULL, " ")) == NULL)
            {
                printf("Parse error\n");
                continue;
            }
            else
            {
                token[strcspn(token, "\n")] = 0;
                rating = atoi(token);
            }

            root = edit(root, old_name, new_name, author, genre, year, price, rating);
        }
        else if (strcmp(token, "LNRPRINTTREE") == 0)
        {
            lnr_printtree(root);
        }
        else if (strcmp(token, "NLRPRINTTREE") == 0)
        {
            nlr_printtree(root);
        }
        else if (strcmp(token, "LRNPRINTTREE") == 0)
        {
            lrn_printtree(root);
        }
        else
        {
            printf("Parse error\n");
        }
    }
}


// Calculate height
int height(struct Book* book)
{
    if (book == NULL)
    {
        return 0;
    }

    return book->height;
}

// Returns true if book exists, false if not
bool search_book(struct Book* book, char* token)
{
    if (book == NULL)
    {
        return false;
    }
    else
    {
        if (strcmp(token, book->name) == 0 || strcmp(token, book->author) == 0 || strcmp(token, book->genre) == 0)
        {
            return true;
        }

        if (atoi(token) == book->year || atoi(token) == book->price || atoi(token) == book->rating)
        {
            return true;
        }

        if ((book->left == NULL) || (book->right == NULL))
        {
            struct Book* temp = book->left ? book->left : book->right;
            search_book(temp, token);
            free(temp);
        }
        else
        {
            search_book(book->left, token);
            search_book(book->right, token);
        }
    }
}

// Create a node
struct Book* new_book(char* name, char* author, char* genre, int year, int price, int rating)
{
    struct Book* book = (struct Book*)malloc(sizeof(struct Book));

    strcpy(book->name, name);
    strcpy(book->author, author);
    strcpy(book->genre, genre);
    book->year = year;
    book->price = price;
    book->rating = rating;

    book->left = NULL;
    book->right = NULL;
    book->height = 1;

    return (book);
}

// Right rotate
struct Book* right_rotate(struct Book* y)
{
    struct Book* x = y->left;
    struct Book* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

// Left rotate
struct Book* left_rotate(struct Book* x)
{
    struct Book* y = x->right;
    struct Book* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

// Get the balance factor
int get_balance(struct Book* book)
{
    if (book == NULL)
    {
        return 0;
    }

    return height(book->left) - height(book->right);
}

// Insert node
struct Book* insert_book(struct Book* book, char* name, char* author, char* genre, int year, int price, int rating)
{
    // Find the correct position to insertNode the node and insertNode it
    if (book == NULL)
    {
        printf("ADD_DONE\n");
        return (new_book(name, author, genre, year, price, rating));
    }

    if (strcmp(name, book->name) < 0)
    {
        book->left = insert_book(book->left, name, author, genre, year, price, rating);
    }
    else if (strcmp(name, book->name) > 0)
    {
        book->right = insert_book(book->right, name, author, genre, year, price, rating);
    }
    else
    {
        printf("ADD_ALREADY\n");
        return book;
    }

    // Update the balance factor of each node and
    // Balance the tree
    book->height = 1 + max(height(book->left), height(book->right));

    int balance = get_balance(book);

    if (balance > 1 && strcmp(name, book->left->name) < 0)
    {
        return right_rotate(book);
    }

    if (balance < -1 && strcmp(name, book->right->name) > 0)
    {
        return left_rotate(book);
    }
    if (balance > 1 && strcmp(name, book->left->name) > 0)
    {
        book->left = left_rotate(book->left);
        return right_rotate(book);
    }

    if (balance < -1 && strcmp(name, book->right->name) < 0)
    {
        book->right = right_rotate(book->right);
        return left_rotate(book);
    }

    return book;
}

struct Book* min_value_book(struct Book* book)
{
    struct Book* current = book;

    while (current->left != NULL)
    {
        current = current->left;
    }

    return current;
}

// Delete a nodes
struct Book* delete_book(struct Book* root, char* name)
{
    // Find the node and delete it
    if (root == NULL)
    {
        printf("DELETE_CANNOT\n");
        return root;
    }

    if (strcmp(name, root->name) < 0)
    {
        root->left = delete_book(root->left, name);
    }
    else if (strcmp(name, root->name) > 0)
    {
        root->right = delete_book(root->right, name);
    }
    else
    {
        if ((root->left == NULL) || (root->right == NULL))
        {
            struct Book* temp = root->left ? root->left : root->right;

            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
            {
                *root = *temp;
            }

            printf("DELETE_DONE\n");
            free(temp);
        }
        else
        {
            struct Book* temp = min_value_book(root->right);

            strcpy(root->name, temp->name);

            root->right = delete_book(root->right, temp->name);
        }
    }

    if (root == NULL)
    {
        return root;
    }

    // Update the balance factor of each node and
    // balance the tree
    root->height = 1 + max(height(root->left), height(root->right));

    int balance = get_balance(root);

    if (balance > 1 && get_balance(root->left) >= 0)
    {
        return right_rotate(root);
    }

    if (balance > 1 && get_balance(root->left) < 0)
    {
        root->left = left_rotate(root->left);
        return right_rotate(root);
    }

    if (balance < -1 && get_balance(root->right) <= 0)
    {
        return left_rotate(root);
    }

    if (balance < -1 && get_balance(root->right) > 0)
    {
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }

    return root;
}

// Searches book by its name, return true if found, otherwise returns false
bool search_book_name(struct Book* book, char* name)
{
    if (book == NULL)
    {
        return false;
    }

    if (strcmp(name, book->name) < 0)
    {
        book->left = search_book_name(book->left, name);
    }
    else if (strcmp(name, book->name) > 0)
    {
        book->right = search_book_name(book->right, name);
    }
    else
    {
        return true;
    }
}

// Edits a book
struct Book* edit(struct Book* book, char* old_name, char* new_name, char* author, char* genre, int year, int price, int rating)
{
    if (search_book_name(book, old_name))
    {
        book = delete_book(book, old_name);
        book = insert_book(book, new_name, author, genre, year, price, rating);
        printf("EDIT_DONE\n");
        return book;
    }
    else
    {
        printf("EDIT_CANNOT\n");
        return book;
    }
}

// Print tree by LNR tree traversal
void lnr_printtree(struct Book* root)
{
    if (root == NULL)
    {
        return;
    }
    else
    {
        lnr_printtree(root->left);

        printf("NAME: %s, AUTHOR: %s, GENRE: %s, YEAR: %d, PRICE: %d, RATING: %d\n", root->name, root->author, root->genre, root->year, root->price, root->rating);

        lnr_printtree(root->right);
    }
}

// Print tree by NLR tree traversal
void nlr_printtree(struct Book* root)
{
    if (root == NULL)
    {
        return;
    }
    else
    {
        printf("NAME: %s, AUTHOR: %s, GENRE: %s, YEAR: %d, PRICE: %d, RATING: %d\n", root->name, root->author, root->genre, root->year, root->price, root->rating);

        lnr_printtree(root->left);
        lnr_printtree(root->right);
    }
}

// Print tree by LRN tree traversal
void lrn_printtree(struct Book* root)
{
    if (root == NULL)
    {
        return;
    }
    else
    {
        lnr_printtree(root->left);
        lnr_printtree(root->right);

        printf("NAME: %s, AUTHOR: %s, GENRE: %s, YEAR: %d, PRICE: %d, RATING: %d\n", root->name, root->author, root->genre, root->year, root->price, root->rating);
    }
}
