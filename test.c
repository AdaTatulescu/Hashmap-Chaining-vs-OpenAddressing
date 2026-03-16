#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct articol
{
    char nume[20];
    int marime;
    char culoare[20];
    struct articol * next;
};

struct articol * creare_articol(char * nume, int marime, char * culoare)
{
    struct articol * nou=malloc(sizeof(struct articol));
    strcpy(nou->nume,nume);
    nou->marime=marime;
    strcpy(nou->culoare,culoare);
    nou->next=NULL;
    return nou;
}

struct articol * adaugare_articol(struct articol * head, char * nume, int marime,char * culoare)
{
    struct articol * curent=head;
    struct articol * nou=creare_articol(nume,marime,culoare);
    if(head==NULL)
    return nou;
    while(curent->next!=NULL)
    curent=curent->next;
    curent->next=nou;
    return head;
}

int get_hash(char * nume, int marime, char * culoare, int m)
{
    int suma=0;
    for(int i=0;nume[i]!='\0';i++)
    {
        suma=suma+nume[i];
    }
    for(int i=0;culoare[i]!='\0';i++)
    {
        suma=suma+culoare[i];
    }
    return (suma+marime)%m;
}

void afisare(struct articol * head)
{
    struct articol * ptr=head;
    while(ptr!=NULL)
    {
       printf("%s %d %s\n",ptr->nume,ptr->marime,ptr->culoare);
       ptr=ptr->next;
    }
}

void afisare_hashmap(struct articol ** hashmap,int m)
{
    for(int i=0;i<m;i++)
    {
        while(hashmap[i]!=NULL)
        {
            printf("%s %d %s %d\n",hashmap[i]->nume,hashmap[i]->marime,hashmap[i]->culoare,i);
            hashmap[i]=hashmap[i]->next;
        }
    }
}

int hash_identice(struct articol ** hashmap1, struct articol ** hashmap2,int m)
{
    int ok=1;
    for(int i=0;i<m;i++)
    {
        while(hashmap1[i]!=NULL && hashmap2[i]!=NULL)
        {
            if(strcmp(hashmap1[i]->nume,hashmap2[i]->nume)!=0 || strcmp(hashmap1[i]->culoare,hashmap2[i]->culoare)!=0 || hashmap1[i]->marime!=hashmap2[i]->marime)
            {
              ok=0;
            }
            hashmap1[i]=hashmap1[i]->next;
            hashmap2[i]=hashmap2[i]->next;
        }
        if(hashmap1[i]!=NULL || hashmap2[i]!=NULL)
        {
           ok=0;
        }
    }
    return ok;
}

void test3_minim(struct articol * Articol,int m,int n)
{
    int dim_min=m;
    int ok=1;
    while(ok==1)
    {
    struct articol ** hashmap_chaining=calloc(m,sizeof(struct articol*));
    struct articol** hashmap_open=calloc(m,sizeof(struct articol*));
    struct articol * ptr=Articol;
    
    while(ptr!=NULL)
    {
        int index=get_hash(ptr->nume,ptr->marime,ptr->culoare,dim_min);
        hashmap_chaining[index]=adaugare_articol(hashmap_chaining[index],ptr->nume,ptr->marime,ptr->culoare);
        
        int open_index=index;
        while(hashmap_open[open_index]!=NULL)
        {
            open_index=(open_index+1)%dim_min;
        }
        hashmap_open[open_index]=creare_articol(ptr->nume,ptr->marime,ptr->culoare);
        ptr=ptr->next;
    }
    
    if(hash_identice(hashmap_chaining,hashmap_open,dim_min)!=0)
    {
        printf("%d\n",dim_min);
       ok=0;
    }
    dim_min++;
   }
   
}
void elibereaza_lista(struct articol *head) {
    struct articol *temp;
    while (head != NULL) {
        temp = head;        
        head = head->next;  
        free(temp);         
    }
}
void elibereaza_hashmap(struct articol **hashmap, int m) {
    for (int i = 0; i < m; i++) {
        elibereaza_lista(hashmap[i]); 
    }
    free(hashmap); 
}
int main()
{
    int m,n;
    char nume[20];
    int marime;
    char culoare[20];
    scanf("%d",&m);
    scanf("%d",&n);
    struct articol * Articol=NULL;
    struct articol ** hashmap=calloc(m,sizeof(struct articol*));
    for(int i=0;i<n;i++)
    {
        scanf("%s",nume);
        scanf("%d",&marime);
        scanf("%s",culoare);
        hashmap[get_hash(nume,marime,culoare,m)]=adaugare_articol(hashmap[get_hash(nume,marime,culoare,m)],nume,marime,culoare);
        Articol=adaugare_articol(Articol,nume,marime,culoare);
        
    }
    int test;
    scanf("%d",&test);
    if(test==1)
    {
        afisare(Articol);
    }
    if(test==2)
    {
        afisare_hashmap(hashmap,m);
    }
    elibereaza_hashmap(hashmap, m); 
    elibereaza_lista(Articol);
    return 0;
}