#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node *nodePointer;
typedef struct node{
    int data;
    nodePointer link;
}node;

void pile_over(nodePointer b_end, nodePointer a_start, nodePointer *before_a);
void put_back(nodePointer start);

//global variable
int pos_record[1009];
nodePointer pos[1009];
int from, to, N, M; //N個方塊，M筆操作

int main(){
    scanf("%d %d", &N, &M);

    //initialize every node 
    for (int i = 1; i <= N; i++){
        pos[i] = (nodePointer)malloc(sizeof(node));

        if (pos[i] == NULL){
            printf("Fatal error: out of memory!\n");
            exit(1);
        }

        pos[i] -> data = i;
        pos[i] -> link = NULL;
        pos_record[i] = i;
    }

    nodePointer a, b;
    char verb[5], instruction[5];
    for (int i = 0; i < M; i++){
        scanf("%s%d%s%d", verb, &from, instruction, &to);

        if (from == to){
            continue;
        }

        //search for a
        nodePointer *before_a;
        before_a = &pos[pos_record[from]];
        a = *before_a;

        while (a -> data != from){
            *before_a = a;
            a = a -> link;
        }

        b = pos[pos_record[to]];

        if (strcmp(verb, "move") == 0){
            //put back blocks on a
            put_back(a -> link);

            //move a onto b
            if (strcmp(instruction, "onto") == 0){
                //search for b
                while (b -> data != to){
                    b = b -> link;
                }

                //put blocks on b back
                put_back(b -> link);

                //make b link to a
                b -> link = a;
                a -> link = NULL;
                pos_record[from] = pos_record[to];
            }
            //move a over b
            else{
                //go to the end of b
                while (b -> link != NULL){
                    b = b -> link;
                }

                b -> link = a;
                a -> link = NULL;

                pos_record[from] = pos_record[to];
            }

            *before_a = NULL;
        }
        else {
            //pile a onto b
            if (strcmp(instruction, "onto") == 0){
                //move to b
                while (b -> data != to){
                    b = b -> link;
                }

                //put back blocks on b
                put_back(b -> link);
            }
            //pile a over b
            else{
                //move to the end of b
                while (b -> link != NULL){
                    b = b -> link;
                }
            }

            pile_over(b, a, before_a);
        }    
    }

    //free
    for (int i = 1; i <= N; i++){
        printf("%d: ", i);

        //follow the nodes until NULL
        nodePointer tmp, tmp_tmp;
        if (pos[i] == NULL){
            printf("\n");
            continue;
        }
        else {
            tmp = pos[i] -> link;
            printf("%d ", pos[i] -> data);
            free(pos[i]);

            while (tmp != NULL){
                printf("%d ", tmp -> data);
                tmp_tmp = tmp;
                tmp = tmp -> link;

                free(tmp_tmp);
            }

        printf("\n");
        }
    }
}

//把各方塊移回原地
void put_back(nodePointer start){
    int val;

    while (start != NULL){
        val = start -> data;
        pos[val] = start;
        start = start -> link;
        pos[val] -> link = NULL;
        
        //reset the pos_record
        pos_record[val] = val;
    }
}

//把整疊移過去
void pile_over(nodePointer b_end, nodePointer a_start, nodePointer *before_a){
    //make the tail of b (or b itself) points to a
    b_end -> link = a_start;

    //set the one before a to NULL (or itself)
    if (a_start == *before_a){
        *before_a = NULL;
    }
    else {
        (*before_a) -> link = NULL;
    }

    //reset pos_record
    int tmp;
    while (a_start != NULL){
        tmp = a_start -> data;
        pos_record[tmp] = pos_record[to];
        a_start = a_start -> link;
    }
}