#ifndef VECTOR_H
#define VECTOR_H


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


#endif // VECTOR_H
