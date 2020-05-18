#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define MAX_WORD 100
#define MAX_LINE 1000
#define MAX_SIZE 500
struct LinkList_colline{
    int val;
    struct LinkList_colline *next;
 };      // dinh nghia linklist cho line va col 
typedef struct LinkList_colline *colline; 
typedef struct {
    char word[MAX_WORD];
    int number;
    colline line;
    colline col;
  } DATA;
struct LinkedList{
    DATA data;
    struct LinkedList *next;
 };
 
typedef struct LinkedList *node; //T? gi? dùng ki?u d? li?u LinkedList có th? thay b?ng node cho ng?n g?n
 
node CreateNode(DATA value){
    node temp; // declare a node
    temp = (node)malloc(sizeof(struct LinkedList)); // C?p phát vùng nh? dùng malloc()
    temp->next = NULL;// Cho next tr? t?i NULL
    temp->data = value; // Gán giá tr? cho Node
    return temp;//Tr? v? node m?i dã có giá tr?	
}
colline CreateNode_colline(int value){                   // tao 1 node col hoac line
    colline temp; // declare a node
    temp = (colline)malloc(sizeof(struct LinkList_colline)); // C?p phát vùng nh? dùng malloc()
    temp->next = NULL;// Cho next tr? t?i NULL
    temp->val = value; // Gán giá tr? cho Node
    return temp;//Tr? v? node m?i dã có giá tr?	
}
colline AddTail_Colline(colline head, int value){            //add vao cuoi 2 danh sach col va line
    colline temp,p;// Khai báo 2 node t?m temp và p
    temp = CreateNode_colline(value);//G?i hàm createNode d? kh?i t?o node temp có next tr? t?i NULL và giá tr? là value
    if(head == NULL){
        head = temp;    //N?u linked list dang tr?ng thì Node temp là head luôn
    }
    else{
        p  = head;// Kh?i t?o p tr? t?i head
        while(p->next != NULL){
            p = p->next;//Duy?t danh sách liên k?t d?n cu?i. Node cu?i là node có next = NULL
        }
        p->next = temp;//Gán next c?a th?ng cu?i = temp. Khi dó temp s? là th?ng cu?i(temp->next = NULL mà)
    }
    return head;
}
node AddTail(node head, DATA value){
    node temp,p;// Khai báo 2 node t?m temp và p
    temp = CreateNode(value);//G?i hàm createNode d? kh?i t?o node temp có next tr? t?i NULL và giá tr? là value
    if(head == NULL){
        head = temp;    //N?u linked list dang tr?ng thì Node temp là head luôn
    }
    else{
        p  = head;// Kh?i t?o p tr? t?i head
        while(p->next != NULL){
            p = p->next;//Duy?t danh sách liên k?t d?n cu?i. Node cu?i là node có next = NULL
        }
        p->next = temp;//Gán next c?a th?ng cu?i = temp. Khi dó temp s? là th?ng cu?i(temp->next = NULL mà)
    }
    return head;
}
 

char* Get(node head, int index){                               // Khong dung den
    int k = 0;
    node p = head;
    while(p != NULL && k != index){
        p = p->next;
    }
    return p->data.word;
}
 
node Search(node head, char s[]){
    int position = 0;
    node p;
    for(p = head; p != NULL; p = p->next){
        if(strcmp(p->data.word,s) == 0){
            return p;
        }
        ++position;
    }
    return NULL;
}
 
void Traverser(node head){                                                // Khong dung den
    printf("\n");
    node p;
    for( p = head; p != NULL; p = p->next){
        printf("%5d", p->data);
    }
}
 
node InitHead(){
    node head;
    head = NULL;
    return head;
}
 
int Length(node head){                                                            // Khong dung den
    int length = 0;
    node p;
    for(p = head; p != NULL; p = p->next){
        ++length;
    }
    return length;
}
  
char *Tolower(char s[]){
	int i;
    for ( i=0;i<strlen(s);i++){
        if(isupper(s[i])) s[i] = s[i]+32;
    }
    return s;
}
long int get_number_word(FILE *file)       // tim so luong word lon nhat trong file              // Khong dung den
{
	long int i = 0;
    while(!feof(file)){
        char a[MAX_WORD];
        fscanf(file,"%s%*c",a);
        if (feof(file)) break;
        i+=1;
    }
    rewind(file);
    return i;
}
void Xu_ly(char s[]){                                    // loai bo dau . cuoi cung 
    int n = 0;
    char str[MAX_WORD];
    int i;
  for (i= 0;i<strlen(s);i++) if(isalpha(s[i])) str[n++] = s[i];
  str[n]='\0';
  strcpy(s,str);
}
int check_with_stopw(char s[],char stopw[][MAX_WORD],int num_stop){    // kiem tra xem chuoi co trung voi 1 trong cac chuoi trong file stopw
	int i;
    for (i = 0; i<num_stop;i++)
        if (strcmp(Tolower(s),stopw[i]) == 0) return 0;    
    return 1;
}
void Scan_file_stopw(FILE *file, char  s[][MAX_WORD],int *num_stop){   // doc file stopw
    int i = 0;
    *num_stop = 0;
    while(!feof(file)){
        char a[MAX_WORD];
        fscanf(file,"%s%*c",a);
        if (feof(file)) break;
        strcpy(s[i++],Tolower(a));
        *num_stop +=1;
    }
}

void Add_word(char s[],node *head,int line,int col){      // add word vao trong link list
    node check_find = Search(*head,s);
    char k[MAX_WORD];
    if (check_find != NULL){
         check_find->data.col = AddTail_Colline(check_find->data.col,col);
        check_find->data.line = AddTail_Colline(check_find->data.line,line);
         check_find->data.number++;
    }
    else {
    	DATA data;
        strcpy(data.word,s);
        data.number =1;
        data.line = NULL;
        data.col = NULL;
        data.line = AddTail_Colline(data.line,line);
        data.col = AddTail_Colline(data.col,col);
        *head = AddTail(*head,data);
    }
}
void Scan_file_test(FILE *file, node *head, char stopw[][MAX_WORD],int num_stop){     // doc file vanban.txt
    int line = 1;
    int check;
    int check1 = 1;
    int col = 0;
    while(!feof(file)){
        char get_line[MAX_LINE];
        fgets(get_line,MAX_LINE,file);
        char *token = strtok(get_line," ");
        while(token!=NULL){
            col++;
            char a[MAX_WORD];
            strcpy(a,token);
            if (a[strlen(a)-1]=='.') check = 0;
            else check = 1;
            Xu_ly(a);
            if(a[0]=='\0'){
                token = strtok(NULL," ");
                continue;
            }
            if(isupper(a[0]) && check1 == 1){
                token = strtok(NULL," ");
                continue;
            }
            Tolower(a);
            if(check_with_stopw(a,stopw,num_stop)) Add_word(a,head,line,col);
            check1 = check;
            token = strtok(NULL," ");
        }
        line ++;
        col = 0;
    }
}

void Sort(node head){
	node q = head;
    while ( q->next != NULL){
    	node p = q->next;
        while(p != NULL){
            if (strcmp(q->data.word,p->data.word)>0){
                DATA tmp = q->data;
                q->data=p->data;
                p->data=tmp;
            }
		   p = p->next;  
		}
		q = q->next;
	}
}
void Display(node head){
	node p = head;
    while(p != NULL){
        printf("%s %d,",p->data.word,p->data.number);
        colline col_tmp, line_tmp;  // khai bao 2 bien tam cho col va line
        col_tmp = p->data.col;
        line_tmp = p->data.line;
        while(col_tmp != NULL && line_tmp != NULL ){
            printf("(%d,%d)", col_tmp->val,line_tmp->val);
            if(col_tmp->next != NULL && line_tmp->next != NULL ) printf(",");
            col_tmp = col_tmp->next;
            line_tmp = line_tmp->next;
            
        }
        printf("\n");
        p = p->next;
    }
}
int main(){
    FILE *vanban = fopen("vanban.txt","r");
    FILE *stopw = fopen("stopw.txt","r");
    if(!vanban){
        printf("File vanban.txt not found");
        return 0;
    }
    if(!stopw){
        printf("File stopw.txt not found");
        return 0;
    }
    char string_stopw[MAX_SIZE][MAX_WORD];
    int num_stop;
    node head = InitHead();
    Scan_file_stopw(stopw,string_stopw,&num_stop);
    Scan_file_test(vanban,&head,string_stopw,num_stop);
    Sort(head);
    Display(head);
    fclose(vanban);
    fclose(stopw);
    return 0;
    }