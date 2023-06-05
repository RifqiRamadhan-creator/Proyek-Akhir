#include <stdio.h>
#include <string.h>
#include <stdlib.h>


 struct temps{
	char name[20];
	char depart[20];
	char tujan[20];
	char type[20];
	int	 prices;
};

typedef struct data {
	char nama[20];
	char awal[20];
	char tuj[20];
	char jenis[20];
	int harga;
	struct data* next;
} data;

data* head = NULL;

void createlink(data** h) {
	char kode[20];
	char aw[20];
	char tujn[20];
	char jenis[20];
	int price;
	
	printf("=========Menambah Jadwal=========\n");
	printf("Jenis Kendaraan: ");
	scanf("%s", jenis);
	printf("Nama Kendaraan: ");
	scanf("%s", kode);
	printf("Kota Keberangkatan: ");
	scanf("%s", aw);
	printf("Kota Tujuan: ");
	scanf("%s", tujn);
	printf("Harga: ");
	scanf("%d", &price);

	if (*h == NULL) {
		*h = (data*)malloc(sizeof(data));
		strcpy((*h)->nama, kode);
		strcpy((*h)->jenis, jenis);
		strcpy((*h)->awal, aw);
		strcpy((*h)->tuj, tujn);
		(*h)->harga = price;
		(*h)->next = NULL;
	} else {
		data* current = *h;
		while (current->next != NULL) {
			current = current->next;
		}
		current->next = (data*)malloc(sizeof(data));
		current = current->next;
		strcpy(current->nama, kode);
		strcpy(current->jenis, jenis);
		strcpy(current->awal, aw);
		strcpy(current->tuj, tujn);
		current->harga = price;
		current->next = NULL;
	}
}

void printlink(data* h) {
	if (h == NULL) {
		printf("Linked list is empty.\n");
		return;
	}

	while (h != NULL) {
		printf("%s\t%s\t%s\t%s\t%d\n", h->jenis, h->nama, h->awal, h->tuj, h->harga);
		h = h->next;
	}
}

void delete(data** h) {
	char kode[20];
	printlink(head);
	printf("\nMasukkan Nama Kendaraan yang akan dihapus: ");
	scanf("%s", kode);

	if (*h == NULL) {
		printf("Linked list is empty.\n");
		return;
	}

	data* current = *h;
	data* prev = NULL;

	// Check if the first node needs to be deleted
	if (strcmp(current->nama, kode) == 0) {
		*h = current->next;
		free(current);
		printf("Kendaraan berhasil dihapus.\n");
		return;
	}

	// Traverse the linked list to find the node to delete
	while (current != NULL) {
		if (strcmp(current->nama, kode) == 0) {
			prev->next = current->next;
			free(current);
			printf("Kendaraan berhasil dihapus.\n");
			return;
		}
		prev = current;
		current = current->next;
	}

	// If the node is not found
	printf("Kendaraan tidak ditemukan.\n");
}


void filewrite(data* h) {
	FILE *op = fopen("data.csv", "w");
	while( h!= NULL){
		fprintf(op,"%s,%s,%s,%s,%d\n",
							h->jenis,
							h->nama,
							h->awal,
							h->tuj,
							h->harga);
		h=h->next;
	}
	fclose(op);
}


void readfile(data**h,  struct temps a[]){
	FILE *op = fopen("data.csv","r" );
	int kolom = 0;
	int baris = 0;
	if ( op == NULL){
		printf("\nError Membuka File");
	}
	
	do{
			kolom = fscanf(op,
							"%49[^,],%49[^,],%49[^,],%49[^,],%d\n",
							a[baris].type,
							a[baris].name,
							a[baris].depart,
							a[baris].tujan,
							&a[baris].prices);
				if ( kolom == 5){
				baris++;
				}
				
				if (*h == NULL) {
					*h = (data*)malloc(sizeof(data));
					strcpy((*h)->nama, a[baris-1].name);
					strcpy((*h)->jenis,a[baris-1].type);
					strcpy((*h)->awal, a[baris-1].depart);
					strcpy((*h)->tuj, a[baris-1].tujan);
					(*h)->harga = a[baris-1].prices;
					(*h)->next = NULL;
					} 
				else {
					data* current = *h;
					while (current->next != NULL) {
						current = current->next;
						}
					current->next = (data*)malloc(sizeof(data));
					current = current->next;
					strcpy(current->nama, a[baris-1].name);
					strcpy(current->jenis, a[baris-1].type);
					strcpy(current->awal, a[baris-1].depart);
					strcpy(current->tuj, a[baris-1].tujan);
					current->harga = a[baris-1].prices;
					current->next = NULL;
					}
				if ( kolom == 5){
				baris++;
				}
				if ( kolom != 5){
				printf("\nData Masih Kosong");
				return 0;
				}
			
								
	}while( !feof (op));
	fclose(op);
	
}

int main() {
	int optmm, optm1, adjaw, adprin, addel, adhelp, p, n=0, i;
  char kota_awal[100], kota_tujuan[100], current[100][100], temp[100];
	struct temps a[100];
	readfile(&head,a);
	do {
		system("cls");
		printf("===========Selamat datang di Travel Guide Companion==========\n");
		printf("Silahkan memilih option Dibawah:");
		printf("\n1. Jadwal Server");
		printf("\n2. Searching");
		printf("\n9. Help Menu");
		printf("\n0. Exit Program");
		printf("\nOption User: ");
		scanf("%d", &optmm);

		switch (optmm) {
			case 1:
				do {
					system("cls");
					printf("1. Buat Jadwal");
					printf("\n2. Tampilkan Jadwal");
					printf("\n3. Menghapus Jadwal");
					printf("\n4. Safe To File");
					printf("\n0. Go Back");
					printf("\nOption User: ");
					scanf("%d", &optm1);
					switch (optm1) {
						case 1:
							do {
								createlink(&head);
								printf("\n1. Lanjut");
								printf("\n2. Go back\n");
								scanf("%d", &adjaw);
							} while (adjaw != 2);
							break;
						case 2:
							do {
							printf("\nBerikut adalah 7 Kota Tersebut beserta Kodenya");
							printf("\n========================================================");
							printf("\n1. Jakarta\t= J");
							printf("\n2. Bandung\t= B");
							printf("\n3. Bogor\t= BG");
							printf("\n4. TasikMalaya\t= T");
							printf("\n5. Jogjakarta\t= JG");
							printf("\n6. Depok\t= D");
							printf("\n7. Surabaya\t= S");
							printf("\n========================================================\n");
								printlink(head);
								printf("\nTekan 0 untuk Kembali\n");
								scanf("%d", &adprin);
							} while (adprin != 0);
							break;
						case 3:
							do {
								delete(&head);
								printf("\nTekan 0 untuk Kembali\n");
								scanf("%d", &addel);
							} while (addel != 0);
							break;
						case 4:
								system("cls");
								printf("\nFile akan di save ke 'data.csv\n'");
								filewrite(head);
								system("pause");
					}
				} while (optm1 != 0);
				break;
			case 2:
        printf("kota keberangkatan: ");
				scanf("%s", kota_awal);
				
				printf("Kota tujuan: ");
				scanf("%s", kota_tujuan);
				
				struct data *ptr;
				ptr = head;
				
				while (ptr != NULL) {
					n++;
					ptr = ptr->next;
				}
				printf("n = %d\n", n);
				
				ptr = head;
				
				strcpy(temp, kota_tujuan);
				while(strcmp(kota_awal, temp)!=0){
					for(i=0; i<n; i++){
						if(ptr!=NULL){
							if(strcmp(temp, ptr->tuj)==0){
								strcpy(temp, ptr->awal);
								strcpy(current[p], ptr->awal);
								p++;
							}
							ptr = ptr->next;
						}				
					}
					ptr = head;
					i=0;
				}
				
				for(i=p-1; i>=0; i--){
					printf("%s->", current[i]);
				}
				printf("%s\n", kota_tujuan);
				system("pause");
				system("cls");
				p=0;
				break;
			case 9:
				do {
					system("cls");
					printf("=========Selamat Datang Di Menu Help=========");
					printf("\n1. Kode Kota");
					printf("\n2. Nama Kendaraan");
					printf("\n3. Jenis Kendaraan");
					printf("\n0. Go Back");
					printf("\nSilahkan Pilih Menu Diatas: ");
					scanf("%d", &adhelp);
					switch (adhelp) {
						case 1:
							system("cls");
							printf("Terdapat Kode Kota yang digunakan Dalam Program Ini");
							printf("\nUntuk Sementara, Program hanya dapat memproses 7 Kota");
							printf("\nBerikut adalah 7 Kota Tersbut beserta Kodenya");
							printf("\n========================================================");
							printf("\n1. Jakarta\t= J");
							printf("\n2. Bandung\t= B");
							printf("\n3. Bogor\t= BG");
							printf("\n4. TasikMalaya\t= T");
							printf("\n5. Jogjakarta\t= JG");
							printf("\n6. Depok\t= D");
							printf("\n7. Surabaya\t= S");
							printf("\n========================================================");
							printf("\nDiatas Adalah List Kota yang dapat diproses beserta Kodenya\n");
							system("pause");
							break;

						case 2:
							system("cls");
							printf("Program ini menggunakan sebuah format dalam penamaan kendaraanya.");
							printf("\nHal tersebut dilakukan untuk membantu mengorganisir dan aksesibilitas kendaraan");
							printf("\nFormat tersebut adalah :");
							printf("\n[Jenis Kendaraan][Kota Berangkat][To][Kota Tujuan]");
							printf("Contoh :\n");
							printf("\nBJTS");
							printf("\nB = Jenis Kendaraan (Bus)");
							printf("\nJ = Kota Keberangkatan (Jakarta)");
							printf("\nT = To");
							printf("\nS = Kota Tujuan (Surabaya)\n");
							system("pause");
							break;

						case 3:
							system("cls");
							printf("Program ini men-support 3 jenis kendaraan");
							printf("\nKendaraan tersebut adalah :");
							printf("\n1. Kereta\t= 'k'");
							printf("\n2. Bus\t= 'B'");
							printf("\n3. Motor\t= 'M'\n");
							system("pause");
							break;
					}
				} while (adhelp != 0);
				break;

		}
	} while (optmm != 0);

	return 0;
}

