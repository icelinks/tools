//**************************************************
//Author          :  fh         
//Date            :  2017/09/12
//Version         :
//Modify Date     :
//Description     :  简单的测试版内存池
//**************************************************
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALIGN_SIZE 8

struct apr_slice{
	struct apr_slice* next;
	int ref;
	int sz;
};

struct apr_heap{
	struct apr_slice* used;
	struct apr_slice* free;
};

struct apr_heap p;

/*apr内存池初始化*/
void 
apr_init(){
	p.used = NULL;
	p.free = NULL;
}

/*malloc申请新空间*/
void *
apr_create(int size){
	int sz = (sizeof(struct apr_slice)+size+ALIGN_SIZE-1)/ALIGN_SIZE;
	struct apr_slice* q = NULL;
	q = (struct apr_slice*)calloc(sz*ALIGN_SIZE);
	if(q==NULL){
		free(q);
		return NULL;
	}
	q->ref = 1;
	q->sz = sz;
	q->next = p.used;
	p.used = q;
	return p.used;
}

/*引用为0内存空间回收*/
int
apr_collect(){
	if(p.used==NULL){
		return -1;
	}
	else{
		struct apr_slice *s;
		struct apr_slice *q;
		s = p.used;
		if(p.used->ref==0){
			if(p.free==NULL){
				p.free = p.used;
				p.used = p.used->next;
				p.free->next = NULL;
			}
			else{
				q = p.used->next;
				p.used->next = p.free;
				p.free = p.used;
				p.used = q;
			}
		}
		while(s->next!=NULL){
			if(s->next->ref==0){
				if(p.free==NULL){
					p.free = s->next;
					s->next = s->next->next;
					p.free->next = NULL;
				}
				else{
					q = s->next->next;
					s->next->next = p.free;
					p.free = s->next;
					s->next = q;
				}
			}
			s = s->next;
		}
	}
	return 0;
}

/*内存申请*/
void*
apr_alloc(int size){
	struct apr_slice *q,*s;
	int sz_ = (sizeof(struct apr_slice)+size+ALIGN_SIZE-1)/ALIGN_SIZE;
	
	if(p.free==NULL){
		if((q = apr_create(size))==NULL)
			return NULL;
		return q;
	}
	else{
		s = p.free;
		while(s!=NULL){
			if(((p.free->sz)*ALIGN_SIZE)>=sz_){
				p.free->next = p.used;
				p.used = p.free;
				p.free = NULL;
				return p.used;
			}
			else if(s->next==NULL){
				break;
			}
			else if(((s->next->sz)*ALIGN_SIZE)>=sz_){
				q = s->next->next;
				s->next->next = p.used;
				p.used = s->next;
				s->next = q;
				return p.used;
			}
			s = s->next;
		}
		if((q = apr_create(size))==NULL)
			return NULL;
		return q;
	}
}

/*引用增加*/
void
apr_grap(struct apr_slice* q){
	q->ref++;
}

/*引用释放*/
int
apr_realease(struct apr_slice* q){
	q->ref--;
	if(q->ref==0||q->ref==-1){
		q->ref = 0;
		if(apr_collect()!=0)
			return -1;
	}
	return 0;
}

/*apr内存池释放*/
void
apr_free(){
	struct apr_slice *q = NULL;
	while(p.used!=NULL){
		q = p.used;
		p.used = p.used->next;
		q->next = NULL;
		free(q);
		q = NULL;
	}
	
	while(p.free!=NULL){
		q = p.free;
		p.free = p.free->next;
		q->next = NULL;
		free(q);
		q = NULL;
	}
}

void *
apr_get_ptr(struct apr_slice* q){
	int sz = sizeof(struct apr_slice);
	return q+sz;
}

int main()
{
	char *q;
	struct apr_slice *q_;
	apr_init();
	while(1){
		q_ = apr_alloc(0);
		q = apr_get_ptr(q_);
		if(q!=NULL){
			sprintf(q,"helloworld");
			printf("%s\n",q);
		}
		else{
			printf("error\n");
		}
		apr_realease(q_);
		sleep(1);
	}
	apr_free();
	return 0;
}