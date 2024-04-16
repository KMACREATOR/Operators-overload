#include <iostream>
#include <fstream>

using namespace std;
//��� ������� - int
//���������� ����� ++ (���������), ��� ���� ������ ������� ��������� ������� ������������� �� 1, ��������� �������� - ���������� ������.

class Vector{
public:
    int *p;
    int n;

    int get_n() const{return n;}
    int* get_p() const{return p;}
    //����������� ��� ����������, �������� ������ ������
    Vector(){
        p = nullptr;
        n = 0;
        p = new int[n];
        cout<<"Vector()"<<endl;
    }

    Vector(int *p, int n) //���������� �� ����� ������, �������� ������
    {
        this->n = n; // ������ ����� ���������
        this->p = new int[n]; // �������� ������
        for (int i = 0; i < n; i++) this->p[i] = p[i]; // �������� ���� ������ � ������
        cout<<"Vector(int *p, int n)"<<endl;
    }
    //����������� �����������
    Vector(const Vector& V)
    {
        n = V.n;
        p = new int[n];
        for (int i = 0; i < n; i++)
            p[i] = V.p[i];
        cout<<"Vector(const Vector & V) n="<<n<<endl;
    }
    // ����������� �����������
    Vector(Vector&& V)  // �������� - �������������� ������
    {
        p = V.p;  // ��� ���������������� ���
        n = V.n;
        // ��������� ������-������ ��������� ������� �������� �� ���������. ��� �� ��������� ����������� ����������� ������
        V.p = nullptr;
        V.n = 0;
    }
    int& operator [](int index){
        return p[index];
    }



friend operator ++(Vector &V){
    for(int i = 0; i <= V.n; ++i){
        ++V[i];
    }
}
//������� ����� �������������� ������������ � ������������



//������� ����� ���������� ������������ � ������������ � ������������
    Vector & operator =(const Vector& v2) // ��������- ������� ����������� �������
    {
        if (this!=&v2) // ������ ����������� ������� ������ � ����
        {
            n = v2.n;
            if (p != nullptr) delete[] p; // ����������� ������ ������� �������
            p = new int[n]; // �������� ������ ��� ������ �������
            for (int i = 0; i < n; i++) p[i] = v2.p[i];
        }
        cout<<"Vector & operator =(const Vector& v2)"<<endl;
        return *this; // ���������� ������ �� ������� ������
    }


    Vector & operator =(Vector&& v2) // ��������- ������� ����������� �������
    {
        if (this!=&v2) // ������ ����������� ������� ������ � ����
        {
            n = v2.n;
            if (p != nullptr) delete[] p; // ����������� ������ ������� �������
            p = v2.p; // ���������� ������
            v2.p=nullptr; // ������������ ������ ����

        }
        cout<<"Vector & operator =(Vector&& v2)"<<endl;
        return *this; // ���������� ������ �� ������� ������
    }

    ~Vector() // ����������
    {
        cout<<"~Vector() n="<<n <<endl;
        if (p!=nullptr) delete[] p; // ����������� ������
    }

};


ostream& operator<< (ostream& stream, Vector& V){
    stream << "V.n = ";
    stream << V.get_n() << endl;
    if (V.get_p() != nullptr){
    for(int i = 0; i < V.get_n(); ++i){
            stream << "V.p[" << i << "] = ";
            stream << V.get_p()[i] << "\t";
            }
    }
    else{
        stream << "������ ����!" << endl;
    }
    return stream;
}

istream& operator >> (istream& stream, Vector& V){
    for(int i = 0; i < V.n; ++i){
            stream >> V.p[i];
    }
    return stream;
}

fstream& operator >> (fstream& stream, const Vector& V){
    for (int i = 0; i < V.n; ++i){
        stream >> V.p[i];
    }
    return stream;
}


int main()
{
    setlocale(LC_ALL, "RUSSIAN");
    fstream vs_file;
    vs_file.open("input.txt");
    int quantity;
    int *l;
    int cnt;
    vs_file >> cnt;
    l = new int[cnt];
    for (int i = 0; i < cnt; ++i){
        vs_file >> l[i];
    }
    //��������� ���� ��� ������
    fstream res_file;
    res_file.open("output.txt");
    res_file << "������ ����� ����������...\n";
//������ �������� ������� �� ����������� �������, ���������� �� �����
    Vector V0(l, cnt);
    res_file << "������ V0: \n" << V0 << endl;
//������ �������� ������� �������, ������������ ������� �� �����, ��������� ���������� ���������� ��������� >>
    vs_file >> quantity;
    res_file << "quantity = " << quantity << endl;
    Vector V1;
    V1.n = quantity;
    vs_file >> V1;
    res_file << "������ V1: \n" << V1 << endl;

//���� ������������������ ������ ���������� �������� ���������� ��� �������� ������ Vector

    ++V0;
    res_file << "������ 0 ����� ���������� �������� ����������: \n" << V0 << endl;
    ++V1;
    res_file << "������ 1 ����� ���������� �������� ����������: \n" << V1 << endl;

//� ������ ������������ �����������, ������� ������� ������������� �������� �� �������� �������
//�������� � ������ ������� V2 ����������� ����������� �� V1
    res_file << "�������� ����������� ����������� �� ������� V1 ��� �������� ������� V2: \n";
    Vector V2(V1);
    res_file << "������ V2: \n" << V2 << endl;
    res_file << "������ V1: \n" << V1 << endl;
//��� �����, �������� ������� V2 �� ����������, � V3 ������ �������� V2
//� ������ ������������ �����������, �������� �� ������������� ��� ����������� ������� ���������
    res_file << "�������� ����������� ����������� �� ������� V1 ��� �������� ������� V3: \n";
    Vector V3(move(V1));
    res_file << "������ V3: \n" << V3 << endl;
    res_file << "������ V1: \n" << V1 << endl;
//�������� ������� V1 ������������� � ������ V3 � ��������� �� ������� V1
//������� ����� ���������� � ������������ � � ������������
//�������� ����������� ����������� �������� ������� ������ ������� �����, ������ �� ������� ������ ������
    res_file << "�������� �������� ����������� �� ������� V3 � ������ V0:\n";
    V0 = V3;
    res_file << "������ V0: \n" << V0 << endl;
    res_file << "������ V3: \n" << V3 << endl;
//�������� ����������� ����������� �������� ������� ������ ������� �����, �� ������� ������ ������
    res_file << "�������� ������ V5\n";
    int m2[] = {2, 6, 7, 3, 2};
    Vector V5(m2, 5);
    res_file << "������ V5: \n" << V5 << endl;
    res_file << "���������� �������� �� ���� � V1:\n";
    V1 = move(V5);
    res_file << "������ V1: \n" << V1 << endl;
    res_file << "������ V5: \n" << V5 << endl;
    cout << "����� ���������." << endl;
    return 0;

}
