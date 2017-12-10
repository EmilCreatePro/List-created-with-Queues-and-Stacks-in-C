#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

int nr_mesaje, nr_mesaje_ordinare;
/*
    fiind variabile globale sunt automat puse pe valoare 0 si avem
    nevoie de ele ca sa stim cum se vor introduce elementele in lista
*/

typedef struct mesaj
{
    int prioritate;// 0-> urgent si 1->prioritar
    char destinatar[40], continut[40];

    struct mesaj *next;

}cutie_postala;

cutie_postala *primul = NULL, *curent, *ultim;
/*
poiterul primul pointeaza spre primul element in lista;
ultim pointeaza spre ultimul element
ne folosim de curent sa parcurgem lista si/sau sa creeam noi elemente
*/


void trimitere_mesaj(int prioritate2, char *destinatar2, char *continut2)
{
    if(nr_mesaje == 0)      //daca nu avem mesaje in lista cream primul nod(mesaj) al listei
        {
            curent = (cutie_postala*)malloc(sizeof(cutie_postala));
            curent->prioritate = prioritate2;
            strcpy(curent->destinatar, destinatar2);
            strcpy(curent->continut, continut2);

            curent->next = NULL;

            primul = ultim = curent;
            if(prioritate2 == 1) nr_mesaje_ordinare++;//daca primul mesaj in lista este unul de prioritate ordinara
        }
        else
        {
            /*
                suntem pe ramura in cazul in care avem mesaje in lista(cutia postala)
            */
            if(prioritate2 == 0)
            /*
                daca mesajul ce trebuie introdus are prioritate
                urgenta atuncea il punem la inceputul listei
            */

            {
                curent = (cutie_postala*)malloc(sizeof(cutie_postala));
                curent->prioritate = prioritate2;
                strcpy(curent->destinatar, destinatar2);
                strcpy(curent->continut, continut2);

                curent->next = primul; // nodul nou creat va pointa spre primul element
                primul = curent;// primul element devine noul nod(mesaj)
            }
            else
            {
                /*
                    in cazul in care trebuie pus un mesaj ordinar in lista care deja are cel putin un element
                */
                if(nr_mesaje_ordinare == 0)
                /*
                    daca nu avem deja in lista mesaje ordinare atuncea este
                    clar ca primul mesaj ordinar din lista va fi pus ultimul
                */
                {
                    curent = (cutie_postala*)malloc(sizeof(cutie_postala));
                    strcpy(curent->destinatar, destinatar2);
                    strcpy(curent->continut, continut2);
                    curent->prioritate = prioritate2;

                    curent->next = NULL;
                    ultim->next = curent;  //ultimul element pointeaza spre noul nod
                    ultim = curent;  //ultimul nod devine noul nod creat
                    nr_mesaje_ordinare++;
                }
                else
                {
                    /*
                        daca deja avem cel putin un mesaj cu prioritate
                        ordinara atuncea trebuie sa ne decidem unde il
                        vom plasa in lista(cutia postala) noastra
                    */

                    cutie_postala *parcurg = primul; // cu parcurg o sa parcurgem lista

                    curent = (cutie_postala*)malloc(sizeof(cutie_postala));
                    strcpy(curent->destinatar, destinatar2);
                    strcpy(curent->continut, continut2);
                    curent->prioritate = prioritate2;

                    if(nr_mesaje_ordinare != 1)
                    {
                        /*
                            daca avem mai mult de 1 mesaj ordinar in casuta postala
                        */

                        /*
                        if((nr_mesaje - nr_mesaje_ordinare) == 0)
                        {
                            if(strcmp(destinatar2,parcurg->destinatar)<0)
                            {
                                curent->next = primul;
                                primul = curent;
                            }
                            nr_mesaje++;
                            nr_mesaje_ordinare++;
                            return;
                        }

                        */
                        //blocul if de mai sus nu are nicio importanta

                        while((parcurg!=NULL) && (parcurg->next->prioritate == 0))
                        /*
                        vreau sa ajung la ultimul element care are prioritatea
                         urgenta pt ca stiu ca dupa urmeaza mesajele ordinare
                        */
                            {
                                if(parcurg->next == NULL) break;
                                /* 
                                    in cazul in care suntem la ultimul nod din lista sa nu ne crape
                                    programul cand testam mai jos pe parcurg->next->destinatar
                                */

                                parcurg = parcurg->next;
                            }

                        if(strcmp(destinatar2,parcurg->next->destinatar)<0) 
                        /*
                            daca trebuie pus acest element chiar inaintea 
                            primulului mesaj ordinar atuncea facem schimbarea 
                        */
                        {
                            curent->next = parcurg->next;
                            parcurg->next = curent;
                            nr_mesaje++;
                            nr_mesaje_ordinare++;
                            return;
                        }
                        else if(parcurg->next!=NULL) parcurg = parcurg->next;
                        /*
                            daca nu trebuie pus chiar inaintea primulului mesaj ordinar,  
                            atunci 'parcurg'' poate fi primul element ordinar din lista
                        */

                        while((parcurg!=NULL) && (parcurg->next!=NULL) &&(strcmp(destinatar2, parcurg->next->destinatar)>0 && parcurg->next!=NULL))
                        /*
                            parcurgem atata timp cat numele urmatorului element este mai mare din punct de vedere lexicografic
                            (adica trebuie sa fie pozititonat noul mesaj dupa el) si parcurgem asa deaorece nu  vrem sa pierdem 
                            adresa nodului dupa care vrem sa inseram noul nostru mesaj
                        */
                            {
                                if(strcmp(destinatar2,parcurg->next->destinatar)<0) break;
                                /*
                                    daca ne aflam la ultimul nod atunci iesim din while ca sa nu fie parcurg = NULL
                                */
                                parcurg=parcurg->next;
                            }

                        if(parcurg->next!=NULL) 
                       /*
                            daca nu ne aflam la ultimul element al listei
                            inseamna ca am gasit un element care trebuie sa urmeze
                            dupa nodul nou creat si satfel stabilim legatura intre ei
                       */
                        {
                            curent->next = parcurg->next;//pointam spre elementul care urmeaza dupa nodul care trebuie sa fie inaintea noului nod
                            parcurg->next = curent;//nodul care trebuie sa fie inaintea noului nod va pointa spre noul nod
                            parcurg = curent;
                        }
                        else
                         /* 
                            daca parcurg->next e NULL atuncea ne aflam la ultimul element din lista 
                            si trebuie sa punem noul nod ca fiind ultimul nod deaorece nu am gasit 
                            un alt element care ar trebui sa fie dupa el
                        */
                        {
                            curent->next = NULL;
                            ultim->next = curent;
                            ultim = curent;
                            /*
                                setam noul nod sa fie ultimul
                            */
                        }
                    }
                    /*
                    in cazul in care avem doar un nod ordinar
                    */
                    else
                    {
                        if(nr_mesaje == 1)
                        /*
                            daca numarul de mesaje este 1 atunci singurul element din lista este unul ordinar 
                            si trebuie sa verificam daca punem noul nod la inceputul sau la sfarsitul listei
                        */
                        {
                            if(primul->next==NULL)
                            {
                                if(strcmp(destinatar2,primul->destinatar)<0)
                                {
                                    curent->next = primul;
                                    primul = curent;
                                }
                                else
                                {
                                    curent->next = NULL;
                                    ultim->next = curent;
                                    ultim = curent;
                                }

                                nr_mesaje_ordinare++;
                                nr_mesaje++;
                                return;
                            }
                        }
                        /*
                            daca nu avem doar un singur mesaj in lista care e de 
                            tip ordinar atuncea trebuie sa parcurgem lista sa 
                            ajungem la ultimul mesaj urgent in lista
                            si sa facem aceleasi operatii ca mai sus
                        */

                        while((parcurg->next->next!=NULL) && (parcurg->prioritate == 0 || strcmp(destinatar2, parcurg->destinatar)>0))
                        {
                            parcurg = parcurg->next;
                        }

                        if(strcmp(destinatar2,parcurg->next->destinatar)<0)
                        {
                            curent->next = parcurg->next;
                            parcurg->next = curent;
                            parcurg = curent;
                        }
                        else
                        {
                            curent->next = NULL;
                            ultim->next = curent;
                            ultim = curent;
                        }
                    }
                    nr_mesaje_ordinare++;
                }
            }
        }

    nr_mesaje++;
}

void primire_mesaj(char *destinatar2)
{
    if(primul == NULL) //daca nu avem mesaje nu are rost sa cautam in cutia postala
    {
        printf("Nu sunt mesaje in casuta postala!");
        return;
    }

    int gasita = 0;// presupunem ca nu vom gasi mesajul destinatarului in casuta
    curent = primul;

    while(curent!=NULL)
    {
        if(strcmp(curent->destinatar,destinatar2)==0) 
        /*
            daca gasim o coincidenta de destinatari atuncea o afisam
            e clar ca o vom afisa pe cea cu prioritate cea mai mare 
            pentru ca cele urgente sunt primele si apoi vin cele ordinare in lista
        */
            {
                if(curent->prioritate == 0)
                    printf("\nDestinatarul %s are o scrisoare URGENTA!\nCu continutul: %s", destinatar2, curent->continut);
                else
                    printf("\nDestinatarul %s are o scrisoare ORDINARA\nCu continutul: %s", destinatar2, curent->continut);
                gasita = 1;
                break; //daca am gasit cea mai prioritara scriosare a destinatarului nu mai are rost sa parcurgem lista si iesim din while
            }
        curent = curent->next;
    }

    if(gasita == 0) // daca nu am gasit nicio scrisoare pentru destinatarul cerut afisam un mesaj
    {
        printf("Destinatarul %s nu are niciun mesaj in cutia postala.", destinatar2);
    }
}

void initializare() // initializam lista, niciun mesaj
{
    curent = (cutie_postala*)malloc(sizeof(cutie_postala));
    primul = ultim = curent = NULL;
    nr_mesaje = nr_mesaje_ordinare = 0;
}

void afisare_date_complet()// functia asta am pus-o ca sa afisam toate datele
{
     if(primul == NULL)
        {
            printf("NU AVEM MESAJE IN CUTIA POSTALA!");
            return;
        }
    int i = 0, separ_rand = 0;

    curent = primul;

    printf("Datele sunt: \n");
    while(curent!=NULL)
    {
        if(curent->prioritate == 0)
            printf(" %d -> Prioritate:Urgent Destinatar:%s Continut:%s \n", ++i, curent->destinatar, curent->continut);
        else
        {
            if(!separ_rand) // se foloseste pentru a separa cu UN RAND doar O DATA! scrisorile urgente de cele prioritare la afisare
            {
                printf("\n");
                separ_rand++;
            }
            printf(" %d -> Prioritate:Ordinar Destinatar:%s Continut:%s \n", ++i, curent->destinatar, curent->continut);
        }
        curent=curent->next;
    }
}

void sortare()// ne folosim de bubble sort ca s sortam mesajele ordinare in ordine alfabetica inversa fata de destinatar
{
    cutie_postala *prim_element_ordinar;
    prim_element_ordinar = curent;

    //ultim2->next = NULL;

    cutie_postala *ptr = prim_element_ordinar;

    int sortat = 0;

    while(sortat == 0)
    {
        sortat = 1;
        ptr = prim_element_ordinar;

        while(ptr->next!=NULL)
        {
            if(strcmp(ptr->destinatar,ptr->next->destinatar)<0)
            {
                char aux_destinatar[30], aux_continut[40];

                strcpy(aux_destinatar, ptr->destinatar);
                strcpy(ptr->destinatar, ptr->next->destinatar);
                strcpy(ptr->next->destinatar, aux_destinatar);

                strcpy(aux_continut, ptr->continut);
                strcpy(ptr->continut, ptr->next->continut);
                strcpy(ptr->next->continut, aux_continut);

                sortat = 0;
            }
            ptr = ptr->next;
        }

    }

}

void desortare(cutie_postala *prim_elmn_ordinar)//o folosim ca sa readucem mesajele ordinare inapoi la starea lor initiala(ordonata alfabetic)
{
    //ultim2->next = NULL;

    cutie_postala *ptr = prim_elmn_ordinar;

    int sortat = 0;

    while(sortat == 0)
    {
        sortat = 1;
        ptr = prim_elmn_ordinar;

        while(ptr->next!=NULL)
        {
            if(strcmp(ptr->destinatar,ptr->next->destinatar)>0)
            {
                char aux_destinatar[30], aux_continut[40];

                strcpy(aux_destinatar, ptr->destinatar);
                strcpy(ptr->destinatar, ptr->next->destinatar);
                strcpy(ptr->next->destinatar, aux_destinatar);

                strcpy(aux_continut, ptr->continut);
                strcpy(ptr->continut, ptr->next->continut);
                strcpy(ptr->next->continut, aux_continut);

                sortat = 0;
            }
            ptr = ptr->next;
        }

    }
}

void afisare()
{
    if(primul == NULL)// daca nu avem mesaje nu le putem afisa
        {
            printf("NU AVEM MESAJE IN CUTIA POSTALA!");
            return;
        }

    if(nr_mesaje_ordinare == 0)// daca nu avem mesaje ordinare nu le putem afisa
    {
        printf("NU AVEM MESAJE ORDINARE IN CUTIA POSTALA!");
            return;
    }

    curent = primul;

    int i = 0;

    while(curent!=NULL)
    {
        if(curent->prioritate == 1) break;

        curent = curent->next;
    }//vrem sa ajungem la primul mesaj ordinar din lista cu curent

    cutie_postala *prim_element_ordinar = curent;//tiem minte pozitia primului mesaj ordinar din lista ca sa readucem mesajele ordinare la starea lor initiala

    if(nr_mesaje_ordinare > 1) sortare();// daca avem un singur mesaj ordinar nu are rost sa-l sortam, 

    /*
        daca am ajuns aici inseamna ca mesajele ordinare au fost invers ordonate dupa destinatar
        si le afisam cu curent care tine minte primul element ordinar
    */
    while(curent!=NULL)
    {
        printf(" %d -> Prioritate:Ordinar Destinatar:%s Continut:%s \n", ++i, curent->destinatar, curent->continut);
        curent=curent->next;
    }

    desortare(prim_element_ordinar);// readucem lista in starea ei initiala
}

int main()// meniu smek ca la aplicatia1
{
    int opt, i;
    char destinatar3[40], continut3[40];
    int prioitate3;

    while(opt!=0)
    {
        system("cls");
        printf("\n1->Trimiteti mesaj\n2->Primiti Mesaj\n3->Afisare Mesaje Ordinare\n4->Afisare Toate Mesaje\n5->Initializare\n\n\n0->Iesire\n\n");
        for(i = 0; i < 25; i++) printf("-");
        printf("\n\nRaspuns: ");
        scanf("%d",&opt);

        switch(opt)
        {
            case 1:
                {
                    getchar();
                    printf("\n\nDati destinatar: ");
                    gets(destinatar3);
                    //printf("%s\n", titlu_carte2);

                    printf("\nDati continut: ");
                    gets(continut3);

                    printf("\nDati prioritatea:\n0->urgent\n1->ordinar\n\nRaspuns: ");
                    scanf("%d", &prioitate3);

                    while(prioitate3!=0 && prioitate3!=1)
                    {
                        printf("\nAti introdus o valoare gresita! Incercati din nou: ");
                        scanf("%d", &prioitate3);
                    }

                    trimitere_mesaj(prioitate3,destinatar3,continut3);
                    //getch();
                    break;
                }
            case 2:
                {
                    //printf("\nPrimeste mesaj");
                    getchar();

                    printf("\n\nDati destinatarul care trebuie sa primeasca o scrioare: ");
                    gets(destinatar3);

                    //daca si-o ridica atuncea trebuie sa dispara din cutia postala?

                    primire_mesaj(destinatar3);
                    getch();
                    break;
                }
            case 3:
                {
                    //printf("\nAfisare mesaj");
                    afisare();
                    getch();
                    break;
                }
            case 4:
                {
                    //printf("\nAfisare mesaj");
                    afisare_date_complet();
                    getch();
                    break;
                }
            case 5 :
                {
                    initializare();
                    printf("\nCutia postala a fost initializata.");
                    getch();
                    break;
                }
            case 0 :
                {
                    break;
                }

            default:
                {
                    printf("\n\nOptiune Gresita!!!");
                    getch();
                }
        }
    }
    return 0;
}
