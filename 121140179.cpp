#include <iostream>

using namespace std;

/*
ubahhh
    Nama    : Farhan Apri Kesuma
    NIM     : 121140179
    Kelas   : RC
    ASD - TUGAS 5
    Link github: https://github.com/parhannn/tugasLimaASD_ITERA/blob/main/121140179.cpp
*/

typedef int infotype;
typedef struct circularLinkedList* address;

typedef struct circularLinkedList
{
    //komponen
    infotype info;
    address next;
}; 

circularLinkedList nodeList;

typedef struct tList 
{
    //komponen
    address head;
}; 

tList List;

//kelas circular linked list yang berisikan fungsi-fungsi dan variabel private
class circularLinkedList_Func
{
    //berisikan variabel yang hanya dapat diakses di dalam class circularLinkedList_Func
    private:
        address newNode, temp, temp1, temp2, predNode, predTemp;
        bool found;

    //berisikan fungsi-fungsi yang dapat diakses di program main
    public:

        //membuat list kosong
        void CreateEmpty(tList* daftar) 
        { 
            (*daftar).head = NULL; 
        }

        //kondisi jika list kosong
        bool IsEmpty(tList daftar) 
        { 
            return daftar.head == NULL; 
        }

        //eksekusi untuk meletakkan list baru
        address Allocation(infotype isiData) 
        {
            newNode = new circularLinkedList;
            newNode->info = isiData;
            newNode->next = NULL;

            return newNode;
        }

        //eksekusi untuk menghapus list yang ada
        void deAllocation(address hapus) 
        { 
            delete hapus; 
        }

        //menambahkan list baru di list pertama
        void addFirst(tList* daftar, infotype isiData) 
        {
            newNode = Allocation(isiData);

            if (!IsEmpty(*daftar)) 
            {
                newNode->next = (*daftar).head; 
                temp = (*daftar).head;

                while (temp->next != (*daftar).head) 
                    temp = temp->next;
                
                temp->next = newNode; 
                (*daftar).head = newNode; 
            }
            else 
            {
                (*daftar).head = newNode;      
                newNode->next = (*daftar).head; 
            }
        }

        //menambahkan list baru di list setelahnya
        void addAfter(address predNode, infotype isiData) 
        {

            newNode = Allocation(isiData);

            newNode->next = predNode->next;
            predNode->next = newNode;
        }

        //menambahkan list baru di list terakhir
        void addLast(tList* daftar, infotype isiData) {
            newNode = Allocation(isiData);

            if (!IsEmpty(*daftar)) 
            {
                temp = (*daftar).head;

                while (temp->next != (*daftar).head) 
                    temp = temp->next;

                // temp->next = newNode; 
                // newNode->next = (*daftar).head; 
                addAfter(temp, isiData);
            }
            else
            {
                addFirst(daftar, isiData);
            }
        }

        //menghapus list pertama
        void deleteFirst(tList* daftar, infotype* hapus) 
        {
            if (!IsEmpty(*daftar)) {
                temp1 = temp2 = (*daftar).head;
                *hapus = temp1->info;

                if (temp1->next != (*daftar).head) 
                {
                    while (temp2->next != (*daftar).head) 
                        temp2 = temp2->next;

                    (*daftar).head = (*daftar).head->next; 
                    temp2->next = (*daftar).head;       
                    temp1->next = NULL;             
                }
                else 
                {
                    temp1->next = NULL; 
                    (*daftar).head = NULL; 
                }

                deAllocation(temp1);
            }
        }

        //menghapus list setelahnya
        void deleteAfter(address predNode, infotype* hapus) 
        {
            if (predNode->next != NULL) 
            {
                temp = predNode->next;
                *hapus = temp->info;
                predNode->next = temp->next;
                temp->next = NULL;

                deAllocation(temp);
            }
        }

        //menghapus list terakhir
        void deleteLast(tList* daftar, infotype* hapus) 
        {
            if (!IsEmpty(*daftar)) 
            {
                predTemp = NULL;
                temp = (*daftar).head;
                *hapus = temp->info;

                if (temp->next != (*daftar).head) 
                {
                    while (temp->next != (*daftar).head) 
                    {
                        predTemp = temp;
                        temp = temp->next;
                    }

                    // predTemp->next = (*daftar).head; 
                    // temp->next = NULL; 

                    // deAllocation(temp);
                    deleteAfter(predTemp, hapus);
                }
                else
                {
                    deleteFirst(daftar, hapus);
                }
            }
        }

        //menambahkan list sekaligus melakukan sorting pada data
        void addNum(tList* daftar, infotype isiData) 
        {
            if (IsEmpty(*daftar) || isiData <= (*daftar).head->info)
                addFirst(daftar, isiData);
            else 
            {
                temp = (*daftar).head;

                while (temp->next != (*daftar).head) 
                {
                    if (isiData > temp->info && isiData <= temp->next->info)
                        break;

                    temp = temp->next;
                }

                addAfter(temp, isiData);
            }
        }

        //menghapus list sesuai dengan input data user
        void deleteNum(tList* daftar, infotype isiData) 
        {
            if (!IsEmpty(*daftar)) 
            {
                predNode = NULL;
                temp = (*daftar).head;
                found = false;

                while (temp->next != (*daftar).head) 
                {
                    if (isiData == temp->info) 
                    {
                        found = true;

                        break;
                    }

                    predNode = temp;
                    temp = temp->next;
                }

                if (found || isiData == temp->info)
                {
                    if (temp == (*daftar).head)
                        deleteFirst(daftar, &isiData);
                    else
                        deleteAfter(predNode, &isiData);
                }
                else
                {
                    cout << "Data " << isiData << " Tidak Tersimpan pada List!" << endl;
                }
            }
        }

        //mencetak hasil list yang ada
        void printList(tList* daftar) 
        {
            temp = (*daftar).head;

            while (temp->next != (*daftar).head) 
            {
                cout << "Data Node Ini: " << temp->info << endl;
                cout << "Data Node Selanjutnya: " << temp->next->info << endl;

                temp = temp->next;
            }

            cout << "Data Node Ini: " << temp->info << endl;
            cout << "Data Node Selanjutnya: " << temp->next->info << endl;
        }
};


int main() 
{
    //objek dari circular linked list yakni "bilangan"
    circularLinkedList_Func bilangan;
    //komponen linked list
    tList bilanganBulat;
    int hapus;

    bilangan.CreateEmpty(&bilanganBulat);

    /*
    addFirst(&data, 10);
    addLast(&data, 20);
    addFirst(&data, 100);
    addFirst(&data, 90);
    addLast(&data, 50);
    addLast(&data, 80);
    addFirst(&data, 40);
    addFirst(&data, 60);
    addLast(&data, 30);
    addFirst(&data, 70);

    deleteFirst(&data, &hapus);
    cout << "Data yang Dihapus = " << hapus << endl;
    deleteLast(&data, &hapus);
    cout << "Data yang dihapus = " << hapus << endl;
    */

    bilangan.addNum(&bilanganBulat, 8);
    bilangan.addNum(&bilanganBulat, 3);
    bilangan.addNum(&bilanganBulat, 6);
    bilangan.addNum(&bilanganBulat, 2);
    bilangan.addNum(&bilanganBulat, 1);
    bilangan.addNum(&bilanganBulat, 7);
    bilangan.addNum(&bilanganBulat, 5);
    bilangan.addNum(&bilanganBulat, 4);
    bilangan.addNum(&bilanganBulat, 9);

    bilangan.deleteNum(&bilanganBulat, 5);
    bilangan.deleteNum(&bilanganBulat, 9);
    bilangan.deleteNum(&bilanganBulat, 1);

    //bilangan.addNum(&bilanganBulat, 8);
    //bilangan.addNum(&bilanganBulat, 3);
    //bilangan.addNum(&bilanganBulat, 6);
    //bilangan.addNum(&bilanganBulat, 2);
    //bilangan.addNum(&bilanganBulat, 1);
    //bilangan.addNum(&bilanganBulat, 7);
    //bilangan.addNum(&bilanganBulat, 5);
    //bilangan.addNum(&bilanganBulat, 4);
    //bilangan.addNum(&bilanganBulat, 9);

    bilangan.deleteNum(&bilanganBulat, 10);

    bilangan.printList(&bilanganBulat);

    return 0;
}   