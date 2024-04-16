#ifndef VECTOR_H
#define VECTOR_H


class Vector{
public:
    int *p;
    int n;

    int get_n() const{return n;}
    int* get_p() const{return p;}
    //конструктор без параметров, задающий пустой вектор
    Vector(){
        p = nullptr;
        n = 0;
        p = new int[n];
        cout<<"Vector()"<<endl;
    }

    Vector(int *p, int n) //Коструктор на входе массив, задающий вектор
    {
        this->n = n; // Задаем число элементов
        this->p = new int[n]; // Выделяем память
        for (int i = 0; i < n; i++) this->p[i] = p[i]; // Копируем один массив в другой
        cout<<"Vector(int *p, int n)"<<endl;
    }
    //Конструктор копирования
    Vector(const Vector& V)
    {
        n = V.n;
        p = new int[n];
        for (int i = 0; i < n; i++)
            p[i] = V.p[i];
        cout<<"Vector(const Vector & V) n="<<n<<endl;
    }
    // Конструктор перемещения
    Vector(Vector&& V)  // Параметр - правосторонняя ссылка
    {
        p = V.p;  // Или инициализировать так
        n = V.n;
        // Присвойте данным-членам исходного объекта значения по умолчанию. Это не позволяет деструктору освобождать память
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
//разница между конструкторами копированием и перемещением



//разница между операциями присваивания с копированиям и перемещением
    Vector & operator =(const Vector& v2) // Оператор- функция копирования объекта
    {
        if (this!=&v2) // Запрет копирования вектора самого в себя
        {
            n = v2.n;
            if (p != nullptr) delete[] p; // Освобождаем память старого вектора
            p = new int[n]; // Выделяем память для нового вектора
            for (int i = 0; i < n; i++) p[i] = v2.p[i];
        }
        cout<<"Vector & operator =(const Vector& v2)"<<endl;
        return *this; // Возвращаем ссылку на текущий объект
    }


    Vector & operator =(Vector&& v2) // Оператор- функция перемещения объекта
    {
        if (this!=&v2) // Запрет перемещения вектора самого в себя
        {
            n = v2.n;
            if (p != nullptr) delete[] p; // Освобождаем память старого вектора
            p = v2.p; // Перемещаем данные
            v2.p=nullptr; // Перемещаемый вектор пуст

        }
        cout<<"Vector & operator =(Vector&& v2)"<<endl;
        return *this; // Возвращаем ссылку на текущий объект
    }

    ~Vector() // Деструктор
    {
        cout<<"~Vector() n="<<n <<endl;
        if (p!=nullptr) delete[] p; // Освобождаем память
    }

};


#endif // VECTOR_H
