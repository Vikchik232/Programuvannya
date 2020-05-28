// list1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>

using namespace std;


// bool a = true, b = false , c = true, d = false; k..
// Node n3;
// n3.a1 = k;
// n3.a2 = d;

// 1. update Node so that it has two members: a1 and a2
// 2. crete DNF for  (a & b) | (c & d) | (e & f)
// 3. Go though the list (same as you did for printing it) and compute DNF



bool find_bukva(char* zminni, int n, char bukva)
{
    for (int i = 0; i < n; i++)
    {
        if (bukva == zminni[i]) return true;
       
    }
    return false;
}

struct Node
{
    bool* a1;
    bool* a2;
    Node* next;
};

void clear(Node* head)
{
    Node* cur = head;
    while (cur != NULL) {
        Node* node_to_del = cur;
        cur = cur->next;
        delete node_to_del;
    }
    head = NULL;
}


void print(Node head)
{
    Node* cur = &head;
    while (cur != NULL) {
        cout << "  " << *(cur->a1) << ' ';
        cout << *(cur->a2) << endl;
        cur = cur->next;
    }
}

bool DNF(Node head)
{
    bool D = false;
    Node* cur = &head;
    while (cur != NULL) {
        D = D || ((*(cur->a1)) & (*(cur->a2)));
        cur = cur->next;
    }
    return D;
}

// bool_zminni = {1, 1, 1, 1, 1, 1};

//                'a'     'c'        'k'
// bool_zminni = {1,   1, 1,   1, 1, 1};// bool_zminni[200]
//
//void per(bool* bool_zminni, int i, int n)
//{
//    if (i == n)
//    {
//        for (int j = 0; j < n; ++j)
//        {
//            cout << bool_zminni[j] << " ";
//        }
//        cout << endl;
//        return;
//    }
//
//    bool_zminni[i] = true;
//    per(bool_zminni, i + 1, n); 
//
//    bool_zminni[i] = false;
//    per(bool_zminni, i + 1, n);
//}
//
//// bool_zminni = {a, b, c}
//// n = 3
//void perebir(bool* bool_zminni, int n)
//{
//    per(bool_zminni, 0, n);
//}


void per(const Node& head, bool* bool_zminni,  int i, const char* zminni, int n_zm)
{
    if (i == n_zm)
    {
        for (int j = 0; j < n_zm; ++j)
        {
            char z = zminni[j];
            cout << bool_zminni[z] << ' ';  
        }
        
        cout << "| " << DNF(head) << endl;
        return;
    }

    char z = zminni[i];
    bool_zminni[z] = true; // bool_zminni[0] -> true ==>  bool_zminni['a'] = trye
    per(head, bool_zminni, i + 1, zminni, n_zm);

    bool_zminni[z] = false;
    per(head, bool_zminni, i + 1, zminni, n_zm);ы
}

// bool_zminni = {a, b, c}
// n = 3
void perebir(const Node& head, bool* bool_zminni, const char* zminni, int n_zm) // n_zm - kilkist змінних ;
{
    for (int j = 0; j < n_zm; ++j)
    {
        char z = zminni[j];
        cout << z << " ";
    }
    cout << "res" << endl;
    per(head, bool_zminni, 0, zminni, n_zm);
}


int main()
{
    //bool b_z[3];
    //b_z[0] = true;
    //b_z[1] = true;
    //b_z[2] = true;
    //per(b_z, 0, 3);
    /////////////////////

    ifstream file;
    file.open("C:\\programuvannya\\DNF.txt", ios::in);
    char ryad[50];
    int k = 0;
    file.getline(ryad, 50);
    cout << "Input : " << ryad << endl;

    char* zminni = new char[50];
    bool* bool_zminni = new bool[200]; 
    // bool_zminni['b'] -> true/false
    int vilna_k = 0;
    for (int i = 0; i < 50; i++)
    {
        if (ryad[i] == '\0')
            break;
        if ((ryad[i] != '+') && (ryad[i] != '*')) {
            if (!find_bukva(zminni, vilna_k, ryad[i])) {
                zminni[vilna_k] = ryad[i];
                bool_zminni[zminni[vilna_k]] = true;
                vilna_k++;
            }
        }
    }
    int num_zm = vilna_k;
    for (int i = 0; i < num_zm; i++)
    {
        cout << zminni[i] << endl;
    }

    ////////////////// stvoruemo Nody
    int h;
    Node* tmp = NULL;
    for (int i = 0; i < 50; i++)
    {
        if (ryad[i] == '+')
        {
            char zm1 = ryad[i - 3];
            char zm2 = ryad[i - 1];
            cout << "stvoruemo new Node dlya konunktsii " << zm1 << " " << zm2 << endl;
            Node* n1 = new Node();
            n1->a1 = &bool_zminni[zm1];
            n1->a2 = &bool_zminni[zm2];
            n1->next = tmp;
            tmp = n1;

            //cout << bool_zminni[zm1] << " " << bool_zminni[zm2] << endl;
            k++;
            h = i;
        }
    }
    char zm3 = ryad[h + 1];
    char zm4 = ryad[h + 3];
    cout << "stvoruemo new Node dlya konunktsii " << zm3 << " " << zm4 << endl;
    cout << "kilkist konunktsiy " << k + 1 << endl;
    Node* head = new Node(); 
    head->a1 = &bool_zminni[zm3];
    head->a2 = &bool_zminni[zm4];
    head->next = tmp;

    // perevirka
    bool D = false;
    print(*head);
    D = DNF(*head);
    cout << D << " res" << endl;


    // perebir
    // zminni {'a', 'b', 'c'}

    cout << "Perebir : " << endl;
    perebir(*head, bool_zminni, zminni, num_zm);
   
    file.close();
    clear(head);

    return 0;


    /*
  
    bool a = 1, b = 0, c = 1, d = 1, e = 0, f = 0;


    Node n2;
    n2.a1 = &e;
    n2.a2 = &f;
    n2.next = NULL;

    Node n1;

    n1.a1 = &c;
    n1.a2 = &d;
    n1.next = &n2;

    Node head;
    head.a1 = &a;
    head.a2 = &b;
    head.next = &n1;
    bool D = false;

    print(head);
    D = DNF(head);
    cout << D << " res" << endl;

    c = 0;
    print(head);
    D = DNF(head);
    cout << D << " res" << endl;

   */


}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
