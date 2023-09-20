#include <iostream>
#include <stdlib.h>
#include <string.h>

#define SIZE 100
using namespace std;

int pokeId = 0;
int count = 0;

struct pokemon{

    char name[25];
    char element[10];
    char skill[20];
    int level;
    int damage;

    char id[8];

    struct pokemon *next, *prev;

} *head[SIZE], *tail[SIZE];

int hashKey(char id[]){

    int sum = 0;
    for(int i = 0; i < strlen(id); i++){

        sum = sum + id[i];

    }

    return sum % 100;

}

struct pokemon *addPokemon(char name[], char element[], char skill[], int level, int damage){

    struct pokemon *newPokemon = (pokemon*)malloc(sizeof(pokemon));

    pokeId++;
    sprintf(newPokemon->id, "PK%03d", pokeId);
    
    count++;

    strcpy(newPokemon->name, name);
    strcpy(newPokemon->element, element);
    strcpy(newPokemon->skill, skill);
    newPokemon->level = level;
    newPokemon->damage = damage;

    newPokemon->next = NULL;
    newPokemon->prev = NULL;

    return newPokemon;

}

void insert(char name[], char element[], char skill[], int level, int damage){

    struct pokemon *newPokemon = addPokemon(name, element, skill, level, damage);
    

    int key = hashKey(newPokemon->id);

    if(head[key] == NULL){

        head[key] = newPokemon;
        tail[key] = newPokemon;

    }
    else{

        // head[key]->prev = newPokemon;
        // newPokemon->next = head[key];
        // head[key] = newPokemon;
        // head[key]->next = newPokemon;
        // newPokemon->prev = head[key];
        // tail[key] = newPokemon;

        tail[key]->prev = newPokemon;
        newPokemon->next = tail[key];
        head[key] = newPokemon;

    }

}

void viewRemove(char id[]){

    int key = hashKey(id);

    struct pokemon *curr = head[key];
        
    while(curr != NULL){

        printf("ID: %10s | Name: %10s | Element: %10s | Skill: %10s | Level: %10d | Damage: %10d |\n", curr->id, curr->name, curr->element, curr->skill, curr->level, curr->damage);
        curr = curr->next;

    }

}

void remove(char id[]){

    int key = hashKey(id);

    if(head[key] == NULL){

        puts("ID not found");
        getchar();
        return;

    }

    viewRemove(id);

    if(head[key] == tail[key] || strcmpi(head[key]->id, id) == 0){

        head[key] = NULL;
        tail[key] = NULL;
        count--;

    }

    else if(strcmpi(head[key]->id, id) == 0){

        head[key]->next->prev = NULL;
        head[key]->next = NULL;
        head[key] = tail[key];
        free(head[key]->prev);
        count--;

    }
    else if(strcmpi(tail[key]->id, id) == 0){

        tail[key]->prev->next = NULL;
        tail[key]->prev = NULL;
        tail[key] = head[key];
        free(tail[key]->next);
        count--;
        

    }
    else{

        struct pokemon *curr = head[key]->next;

        while(curr != NULL){

            if(strcmpi(curr->id, id) == 0){

                curr->next->prev = curr->prev;
                curr->prev->next = curr->next;
                curr->next = NULL;
                curr->prev = NULL;
                free(curr);
                count--;

                return;

            }
            curr = curr->next;

        }

    }

    getchar();


}

void insertMenu(){

    char name[25];
    char element[10];
    char skill[20];
    int level;
    int damage;
    char confirm[10];
    
    do{

        printf("Insert Pokemon Name [5 - 20]: ");
        scanf("%[^\n]", &name); getchar();

    }while(strlen(name) < 5 || strlen(name) > 20);

    do{

        printf("Insert Pokemon Element [Fire | Water | Grass](case sensitive): ");
        scanf("%s", &element); getchar();

    }while(strcmp(element, "Fire") != 0 && strcmp(element, "Water") != 0 && strcmp(element, "Grass") != 0);

    do{

        printf("Insert Pokemon Skill [Tackle | Dragon breath | Overgrow](case insensitive): ");
        scanf("%[^\n]", &skill); getchar();

    }while(strcmpi(skill, "Tackle") != 0 && strcmpi(skill, "Dragon breath") != 0 && strcmpi(skill, "Overgrow") != 0);

    do{

        printf("Insert Pokemon Level [1 - 99]: ");
        scanf("%d", &level); getchar();

    }while(level < 1 || level > 99);

    do{

        printf("Insert Pokemon Damage [100 - 10000]: ");
        scanf("%d", &damage); getchar();

    }while(damage < 100 || damage > 10000);

    do{

        printf("Are you sure want to add pokemon [yes | no](case sensitive): ");
        scanf("%s", &confirm); getchar();

    }while((strcmp(confirm, "yes") == 1) && (strcmp(confirm, "no") == 1));

    if(strcmp(confirm, "no") == 0){

        puts("Failed to add pokemon");
        getchar();
        return;

    }
    else
        insert(name, element, skill, level, damage);
        

}

void view(){

    // puts("masuk");
    if(count == 0){

        puts("No Pokemon Yet");
        return;

    }
    
    // puts("%10s | %10s | %10s | %10s | %10s | %10s |", "ID", "Name", "Element", "Skill", "Level", "Damage");
    for(int i = 0; i < SIZE; i++){

        struct pokemon *curr = head[i];
        
        if(head[i] == NULL)
            continue;
        
        while(curr != NULL){

            printf("ID: %10s | Name: %10s | Element: %10s | Skill: %10s | Level: %10d | Damage: %10d |\n", curr->id, curr->name, curr->element, curr->skill, curr->level, curr->damage);
            curr = curr->next;

        }

    }

}

void removeMenu(){

    if(count == 0){

        puts("No Pokemon Yet");
        return;

    }

    view();

    char id[10];

    printf("Delete Pokemon ID (case insensitive): ");
    scanf("%s", &id); getchar();

    remove(id);

}



void menu(){

    int choice;
    
    do{

        puts("Pokemon Book");
        puts("=============");
        puts("1. Add Pokemon");
        puts("2. View Pokemon");
        puts("3. Delete Pokemon");
        puts("4. Exit");

        scanf("%d", &choice); getchar();


        switch(choice){

            case 1:
                insertMenu();
                break;
            
            case 2:
                view();
                break;
            
            case 3:
                removeMenu();
                break;
            
            case 4:
                return;

        }

    }while(choice != 4);

}

int main(){

    menu();


    return 0;
}