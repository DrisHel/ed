#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 7

typedef struct Node {
    char ip[16];
    char domain[256];
    struct Node* next;
} Node;

typedef struct {
    Node* table[TABLE_SIZE];
} HashTable;

unsigned int hashFunction(const char* key) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash << 5) + *key++;
    }
    return hash % TABLE_SIZE;
}

Node* createNode(const char* ip, const char* domain) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->ip, ip);
    strcpy(newNode->domain, domain);
    newNode->next = NULL;
    return newNode;
}

void insertByIP(HashTable* ht, const char* ip, const char* domain) {
    unsigned int index = hashFunction(ip);
    Node* newNode = createNode(ip, domain);
    newNode->next = ht->table[index];
    ht->table[index] = newNode;
}

void insertByDomain(HashTable* ht, const char* domain, const char* ip) {
    unsigned int index = hashFunction(domain);
    Node* newNode = createNode(ip, domain);
    newNode->next = ht->table[index];
    ht->table[index] = newNode;
}

Node* searchByIP(HashTable* ht, const char* ip) {
    unsigned int index = hashFunction(ip);
    Node* current = ht->table[index];
    while (current) {
        if (strcmp(current->ip, ip) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

Node* searchByDomain(HashTable* ht, const char* domain) {
    unsigned int index = hashFunction(domain);
    Node* current = ht->table[index];
    while (current) {
        if (strcmp(current->domain, domain) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void initializeHashTable(HashTable* ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht->table[i] = NULL;
    }
}

void prepopulateHashTable(HashTable* ht) {
    insertByIP(ht, "8.8.8.8", "www.google.com");
    insertByIP(ht, "203.0.113.2", "www.pichau.com.br");
    // insertByIP(ht, "2.23.104.228", "br.pinterest.com");
    // insertByIP(ht, "186.192.81.152", "www.techtudo.com.br");
    // insertByIP(ht, "172.217.29.174", "www.youtube.com");
    // insertByIP(ht, "31.13.85.36", "www.facebook.com");
    // insertByIP(ht, "157.240.226.174", "www.instagram.com");
    // insertByIP(ht, "186.192.81.31", "g1.globo.com");
    // insertByIP(ht, "216.239.38.21", "www.orkut.com");
    // insertByIP(ht, "195.200.68.224", "pt.wikipedia.org");
    // insertByIP(ht, "192.0.66.108", "www.nasa.gov");
    // insertByIP(ht, "208.84.244.116", "www.terra.com.br");
    // insertByIP(ht, "170.249.212.42", "ofuxico.com.br");
    // insertByIP(ht, "192.0.66.120", "veja.abril.com.br");
    // insertByIP(ht, "172.64.154.161", "odia.ig.com.br");
    // insertByIP(ht, "201.7.177.244:", "oglobo.globo.com");
    // insertByIP(ht, "23.227.38.32", "www.casadocodigo.com.br");
    // insertByIP(ht, "104.26.1.170", "www.alura.com.br");
    // insertByIP(ht, "76.76.21.21", "www.rocketseat.com.br");
    // insertByIP(ht, "172.67.167.201", "ifrs.edu.br");
}

void displayData(HashTable* ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* current = ht->table[i];
        printf("Dados %d:\n", i);
        while (current) {
            printf("  IP: %s, Domain: %s\n", current->ip, current->domain);
            current = current->next;
        }
    }
}

void menu(HashTable* ht) {
    int choice;
    char ip[16], domain[256];
    Node* result;

    do {
        printf("1. Inserir novo registro\n");
        printf("2. Buscar por IP\n");
        printf("3. Buscar por domínio\n");
        printf("4. Mostrar dados inseridos\n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Digite o IP: ");
                scanf("%s", ip);
                printf("Digite o domínio: ");
                scanf("%s", domain);
                insertByIP(ht, ip, domain);
                insertByDomain(ht, domain, ip);
                break;
            case 2:
                printf("Digite o IP: ");
                scanf("%s", ip);
                result = searchByIP(ht, ip);
                if (result) {
                    printf("Domínio encontrado: %s\n", result->domain);
                } else {
                    printf("IP não encontrado. Deseja adicionar? (1-Sim, 0-Não): ");
                    int add;
                    scanf("%d", &add);
                    if (add) {
                        printf("Digite o domínio: ");
                        scanf("%s", domain);
                        insertByIP(ht, ip, domain);
                        insertByDomain(ht, domain, ip);
                    }
                }
                break;
            case 3:
                printf("Digite o domínio: ");
                scanf("%s", domain);
                result = searchByDomain(ht, domain);
                if (result) {
                    printf("IP encontrado: %s\n", result->ip);
                } else {
                    printf("Domínio não encontrado. Deseja adicionar? (1-Sim, 0-Não): ");
                    int add;
                    scanf("%d", &add);
                    if (add) {
                        printf("Digite o IP: ");
                        scanf("%s", ip);
                        insertByIP(ht, ip, domain);
                        insertByDomain(ht, domain, ip);
                    }
                }
                break;
            case 4:
                displayData(ht);
                break;
            case 5:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (choice != 5);
}

int main() {
    HashTable ht;
    initializeHashTable(&ht);
    prepopulateHashTable(&ht);
    menu(&ht);
    return 0;
}