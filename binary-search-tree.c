/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * School of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int key;
    struct node *left;
    struct node *right;
} Node;

int initializeBST(Node** h);
void inorderTraversal(Node* ptr);
void preorderTraversal(Node* ptr);
void postorderTraversal(Node* ptr);
int insert(Node** head, int key);
int deleteLeafNode(Node* head, int key);
Node* searchRecursive(Node* ptr, int key);
Node* searchIterative(Node* head, int key);
int freeBST(Node* head);

int main()
{
    char command;
    int key;
    Node* head = NULL;
    Node* ptr = NULL;

    do {
        printf("\n\n");
        printf("[----- [박조현] [2021053017] -----]");
        printf("----------------------------------------------------------------\n");
        printf("                   Binary Search Tree #1                        \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize BST       = z                                       \n");
        printf(" Insert Node          = n      Delete Node                  = d \n");
        printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
        printf(" Preorder Traversal   = p      Search Node Iteratively      = f \n");
        printf(" Postorder Traversal  = t      Quit                         = q \n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command);

        switch(command) {
            case 'z': case 'Z':
                initializeBST(&head);
                break;
            case 'q': case 'Q':
                freeBST(head);
                break;
            case 'n': case 'N':
                printf("Your Key = ");
                scanf("%d", &key);
                insert(&head, key);
                break;
            case 'd': case 'D':
                printf("Your Key = ");
                scanf("%d", &key);
                deleteLeafNode(head, key);
                break;
            case 'f': case 'F':
                printf("Your Key = ");
                scanf("%d", &key);
                ptr = searchIterative(head, key);
                if(ptr != NULL)
                    printf("\n node [%d] found at %p\n", ptr->key, ptr);
                else
                    printf("\n Cannot find the node [%d]\n", key);
                break;
            case 's': case 'S':
                printf("Your Key = ");
                scanf("%d", &key);
                ptr = searchRecursive(head, key);
                if(ptr != NULL)
                    printf("\n node [%d] found at %p\n", ptr->key, ptr);
                else
                    printf("\n Cannot find the node [%d]\n", key);
                break;
            case 'i': case 'I':
                inorderTraversal(head);
                break;
            case 'p': case 'P':
                preorderTraversal(head);
                break;
            case 't': case 'T':
                postorderTraversal(head);
                break;
            default:
                printf("\n       >>>>>   Concentration!!   <<<<<     \n");
                break;
        }
    } while(command != 'q' && command != 'Q');

    return 1;
}

int initializeBST(Node** h) {
    /* if the tree is not empty, then remove all allocated nodes from the tree */
    if(*h != NULL)
        freeBST(*h);

    /* create a head node */
    *h = NULL;  // 트리의 헤드를 NULL로 설정하여 초기화하는 것으로 코드 변경
    return 1;
}


void inorderTraversal(Node* ptr) {     // 중위 순회
    if (ptr) {
        inorderTraversal(ptr->left);   // 왼쪽 서브트리를 순회하도록 재귀적인 방법으로 함수 호출
        printf("%d ", ptr->key);       // 노드의 key 값 출력
        inorderTraversal(ptr->right);  // 오른쪽 서브트리를 순회하도록 재귀적인 방법으로 함수 호출
    }
}

void preorderTraversal(Node* ptr) {     // 전위 순회
    if (ptr) {
        printf("%d ", ptr->key);        // 노드의 key 값 출력
        preorderTraversal(ptr->left);   // 왼쪽 서브트리를 순회하도록 재귀적인 방법으로 함수 호출
        preorderTraversal(ptr->right);  // 오른쪽 서브트리를 순회하도록 재귀적인 방법으로 함수 호출
    }
}

void postorderTraversal(Node* ptr) {      // 후위 순회
    if (ptr) {
        postorderTraversal(ptr->left);    // 왼쪽 서브트리를 순회하도록 재귀적인 방법으로 함수 호출
        postorderTraversal(ptr->right);   // 오른쪽 서브트리를 순회하도록 재귀적인 방법으로 함수 호출
        printf("%d ", ptr->key);          // 노드의 key 값 출력
    }
}

int insert(Node* head, int key) {    //노드 삽입 함수 (1은 성공, 0은 실패)
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->left = newNode->right = NULL;

    if (head == NULL) {          // 트리가 비어있는 경우
        head = newNode;          // 트리의 헤드에 새 노드 추가
        return 1;
    }

    Node* searchNode = head;    

    while (searchNode) {                      // 트리가 비어있지 않은 경우 반복
        if (key == searchNode->key) {         // 이미 같은 key값이 존재하는 경우
            free(newNode);                    // 새 노드를 free
            return 1;
        } else if (key < searchNode->key) {   // 새 노드의 key값이 현재 노드의 key값보다 작은 경우  
            if (searchNode->left == NULL) {   // 현재 노드의 왼쪽 자식 노드가 비어있는 경우
                searchNode->left = newNode;   // 현재 노드의 왼쪽 자식 노드에 새 노드 추가
                return 1;
            } else {
                searchNode = searchNode->left;    // 현재 노드를 현재 노드의 왼쪽 자식 노드로 변경
            }
        } else {                                  // 새 노드의 key값이 현재 노드의 key값보다 큰 경우
            if (searchNode->right == NULL) {      // 현재 노드의 오른쪽 자식 노드가 비어있는 경우
                searchNode->right = newNode;      // 현재 노드의 오른쪽 자식 노드에 새 노드 추가
                return 1;
            } else {
                searchNode = searchNode->right;   // 현재 노드를 현재 노드의 오른쪽 자식 노드로 변경
            }
        }
    }
    return 0;
}


int deleteLeafNode(Node* head, int key) {                      // leaf 노드 삭제 함수
    Node* parentNode = NULL;                                   // 부모 노드를 NULL로 초기화
    Node* searchNode = head;                                   // 현재 노드를 트리의 head로 초기화

    while (searchNode != NULL && searchNode->key != key) {     // 현재 노드가 NULL이 아니고 key값이 일치하지 않는 경우 반복
        parentNode = searchNode;                               // 부모 노드에 현재 노드 저장
        if (key < searchNode->key) {                           // key값이 현재 노드의 key값보다 작은 경우
            searchNode = searchNode->left;                     // 현재 노드를 현재 노드의 왼쪽 자식 노드로 변경
        } else {                                               // key값이 현재 노드의 key값보다 큰 경우
            searchNode = searchNode->right;                    // 현재 노드를 현재 노드의 오른쪽 자식 노드로 변경
        }
    }

    if (searchNode == NULL) {                                  // 트리를 다 순회했음에도 key값을 찾지 못한 경우
        printf("삭제할 노드가 없습니다.\n");                
        return 0;
    }

    if (searchNode->left == NULL && searchNode->right == NULL) {    // key값에 해당하는 노드가 leaf 노드인 경우
        if (searchNode == head) {                                   // key 값에 해당하는 노드가 head 노드인 경우
            free(searchNode);                                       // 그 해당 노드를 free
            return 1;
        }

        if (parentNode->left == searchNode) {                        // key 값에 해당하는 노드가 부모 노드의 왼쪽 자식 노드인 경우
            parentNode->left = NULL;        				         // 부모 노드의 왼쪽 자식 노드를 NULL로 변경 
        } else {                                                     // key 값에 해당하는 노드가 부모 노드의 오른쪽 자식 노드인 경우
            parentNode->right = NULL;                                // 부모 노드의 오른쪽 자식 노드를 NULL로 변경
        }
        free(searchNode);                                            // 해당 노드를 free
        return 1;
    } else {                                                         // key값에 해당하는 노드가 leaf 노드가 아닌 경우
        printf("해당 노드는 리프 노드가 아닙니다.\n");
        return 0;
    }
}

Node* searchRecursive(Node* ptr, int key) {                           // 재귀적으로 노드를 검색하여 찾는 함수
    if (ptr == NULL || ptr->key == key)  {                            // 노드가 NULL이거나 key값이 일치하는 경우
		return ptr;                                                   // 해당 노드 반환
	}
    if(key < ptr->key) {                                              // key값이 현재 노드의 key값보다 작은 경우
        return searchRecursive(ptr->left, key);                       // 왼쪽 서브트리를 순회하도록 재귀적으로 함수 호출
    }
    return searchRecursive(ptr->right, key);                          // 오른쪽 서브트리를 순회하도록 재귀적으로 함수 호출
}

Node* searchIterative(Node* head, int key) {                          // while문을 사용하여 노드를 검색하여 찾는 함수
    while(head) {                                                     // 트리가 비어있지 않을 경우에 계속 반복
        if(key == head->key) {                                        // key값이 현재 노드의 key값과 일치할 경우
            return head;                                              // 해당 노드 반환
        }
        if(key < head->key) {                                         // key값이 현재 노드의 key값보다 작은 경우
            head = head->left;                                        // 현재 노드를 현재 노드의 왼쪽 자식으로 변경
        }
        else {                                                        // key값이 현재 노드의 key값보다 큰 경우
            head = head->right;                                       // 현재 노드를 현재 노드의 오른쪽 자식으로 변경
        }
    }
    return NULL;
}

int freeBST(Node* head) {                   // 트리의 모든 노드를 free시키는 함수
    if (head == NULL) {                     // 트리가 비어있는 경우
		return 0;
	}
    freeBST(head->left);                    // 왼쪽 서브트리를 순회하도록 재귀적인 방법으로 함수 호출
    freeBST(head->right);                   // 오른쪽 서브트리를 순회하도록 재귀적인 방법으로 함수 호출

    free(head);                             // head 노드를 free
    return 1;
}






