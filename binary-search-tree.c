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
int insert(Node* head, int key);
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
                insert(head, key);
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
                inorderTraversal(head->left);
                break;
            case 'p': case 'P':
                preorderTraversal(head->left);
                break;
            case 't': case 'T':
                postorderTraversal(head->left);
                break;
            default:
                printf("\n       >>>>>   Concentration!!   <<<<<     \n");
                break;
        }
    } while(command != 'q' && command != 'Q');

    return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
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

int insert(Node* head, int key) {    // 노드 삽입 함수 (1은 성공, 0은 실패)
    Node* newNode = (Node*)malloc(sizeof(Node));

    newNode->key = key;
    newNode->left = newNode->right = NULL;

    if (head->left == NULL) {
        head->left = newNode; // 트리가 비어있다면 새로운 노드를 루트로 설정
        return 1;
    }

    Node* parentNode = NULL;
    Node* searchNode = head->left; // 루트 노드부터 시작

    while (searchNode) {
        if(searchNode->key == key) { // 이미 같은 key값이 존재하는 경우
            printf("이미 중복된 값이 존재합니다.\n");
            free(newNode); // 새 노드를 free시킴
            return 0; // 중복된 값이므로 실패 반환
        }
        parentNode = searchNode; // 부모 노드 갱신
        searchNode = (key < searchNode->key) ? searchNode->left : searchNode->right; // 새 노드의 key값이 현재 노드의 key값보다 작으면 왼쪽, 크면 오른쪽으로 이동
    }

    // 새로운 노드를 부모 노드의 왼쪽 또는 오른쪽에 삽입
    if (key < parentNode->key) {
        parentNode->left = newNode;
    } else {
        parentNode->right = newNode;
    }

    return 1; // 삽입 성공
}


int deleteLeafNode(Node* head, int key) {                      // leaf 노드 삭제 함수
    if (head == NULL || head->left == NULL) {                  // 트리가 비어있거나 루트 노드가 없는 경우
        printf("삭제할 노드가 없습니다.\n");
        return 0;
    }

    Node* parentNode = head;
    Node* searchNode = head->left;                             // 현재 노드를 트리의 루트로 초기화

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
        if (parentNode->left == searchNode) {                        // key 값에 해당하는 노드가 부모 노드의 왼쪽 자식 노드인 경우
            parentNode->left = NULL;                                 // 부모 노드의 왼쪽 자식 노드를 NULL로 변경 
        } else if (parentNode->right == searchNode) {                // key 값에 해당하는 노드가 부모 노드의 오른쪽 자식 노드인 경우
            parentNode->right = NULL;                                // 부모 노드의 오른쪽 자식 노드를 NULL로 변경
        } else {                                                     // 루트 노드인 경우
            head->left = NULL;
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
     if (head == NULL) {                    // 트리가 비어있는 경우
        return 0;
    }
    if (head->left != NULL) {               // 왼쪽 서브트리가 존재하는 경우
        freeBST(head->left);                // 재귀적으로 왼쪽 서브트리를 순회하도록 함수 호출
    }
    if (head->right != head) {              // 오른쪽 서브트리가 존재하는 경우
        freeBST(head->right);               // 재귀적으로 오른쪽 서브트리를 순회하도록 함수 호출
    }
    free(head);                          //// head 노드 free
    return 1;                           
}






