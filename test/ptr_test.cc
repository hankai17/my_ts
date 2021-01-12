#include <iostream>

#include "ts/Ptr.h"

class MyString {
public:
    MyString() {
        m_len = 0;
        m_str = new char[1];
        m_str[0] = '\0';
    }

    MyString(const char* str) {
        m_len = strlen(str);
        m_str = new char[m_len + 1];
        strcpy(m_str, str);
    }

    MyString(const MyString& str) {
        m_len = str.m_len;
        m_str = new char[m_len + 1];
        strcpy(m_str, str.m_str);
    }

    const char* c_str() { return m_str; };
    int size() { return m_len; };

    MyString& operator=(const MyString& str) {
        if (m_str != NULL) {
            delete [] m_str;
            m_str = NULL;
        }
        m_len = str.m_len;
        m_str = new char[m_len + 1];
        strcpy(m_str, str.m_str);
        return *this;
    }

    MyString& operator=(const char* str) {
        if (m_str != NULL) {
            delete [] m_str;
            m_str = NULL;
        }
        m_len = strlen(str);
        m_str = new char[m_len + 1];
        strcpy(m_str, str);
        return *this;
    }

    ~MyString() {
        if (m_str != NULL) {
            delete [] m_str;
            m_str = NULL;
        }
        m_len = 0;
    }

private:
    char*   m_str;
    int     m_len;
};

class A : public RefCountObj {
public:
    A() :m_ptr(new int(0)) {
        std::cout<<"construct"<<std::endl;
    }

    A(const A& a) :m_ptr(new int(*a.m_ptr)) {
        std::cout<<"cp construct"<<std::endl;
    }

    A(A&& a) :m_ptr(a.m_ptr) { //为什么move构造 只是一个浅拷贝? 因为他是右值 因为它不需要深拷贝 只需要转移控制权限就可以了
        std::cout<<"move construct"<<std::endl;
        a.m_ptr = nullptr;
    }

    std::string toString() {
        return std::string("test");
    }

    ~A() {
        std::cout<<"destruct"<<std::endl;
        delete m_ptr;
    }
private:
    int* m_ptr;
};

class B : public RefCountObj {
public:
    B() :m_b(0) {
        std::cout<<"construct"<<std::endl;
    }

    B(const B& a) :m_b(a.m_b) {
        std::cout<<"cp construct"<<std::endl;
    }

    B(B&& a) :m_b(a.m_b) { //为什么move构造 只是一个浅拷贝? 因为他是右值 因为它不需要深拷贝 只需要转移控制权限就可以了
        std::cout<<"move construct"<<std::endl;
        a.m_b = 0;
    }

    std::string toString() {
        return std::string("test");
    }

    ~B() {
        std::cout<<"destruct"<<std::endl;
    }

    Ptr<B> next;
    int m_b;
};

int test() {
    A* a = new A();
    std::cout << "a->refcount: " << a->refcount() << std::endl;

    Ptr<A> smart_obj = Ptr<A>(a);
    std::cout << "a->refcount: " << a->refcount() <<
            ", smart_obj->refcount: " << smart_obj->refcount() << std::endl; // refOBJ Only become Ptr. Thus refObj can ++

    Ptr<A> smart_obj1(smart_obj);                                            // Call Ptr's copy construct. Note that Ptr's copy construct CAN NOT lead obj copy
    std::cout << "smart_obj1->refcount: " << smart_obj1->refcount() << std::endl;

    Ptr<A> smart_obj2 = smart_obj;
    std::cout << "smart_obj2->refcount: " << smart_obj2->refcount() << std::endl;

    Ptr<A> smart_obj3;
    smart_obj3 = smart_obj;
    std::cout << "smart_obj3->refcount: " << smart_obj3->refcount()
            << ", smart_obj->refcount: " << smart_obj->refcount() << std::endl;

    A* a1 = new A();
    Ptr<A> smart_obj4 = Ptr<A>(a1);
    smart_obj4 = smart_obj3;
    std::cout << "smart_obj4->refcount: " << smart_obj4->refcount()
            << ", smart_obj->refcount: " << smart_obj->refcount() << std::endl;

    Ptr<A> smart_obj5 = Ptr<A>(a);
    std::cout << "a->refcount: " << a->refcount()
            << ", smart_obj5->refcount: " << smart_obj5->refcount() << std::endl;

    //A* b = smart_obj.to_ptr();
    //std::cout << "b: " << b->toString() << std::endl;

    return 0;
}

Ptr<B> internal_test() {
    B* b = new B();
    Ptr<B> smart_obj = Ptr<B>(b);

    B* b1 = new B();
    Ptr<B> smart_obj1 = Ptr<B>(b1);

    B* b2 = new B();
    Ptr<B> smart_obj2 = Ptr<B>(b2);

    B* b3 = new B();
    Ptr<B> smart_obj3 = Ptr<B>(b3);

    smart_obj->next = smart_obj1;
    smart_obj1->next = smart_obj2;
    smart_obj2->next = smart_obj3;

    std::cout << "smart_obj->refcount: " << smart_obj->refcount() << std::endl;
    std::cout << "smart_obj1->refcount: " << smart_obj1->refcount() << std::endl;
    std::cout << "smart_obj2->refcount: " << smart_obj2->refcount() << std::endl;
    std::cout << "smart_obj3->refcount: " << smart_obj3->refcount() << std::endl;

    // b->b1->b2->b3 // 除了本身 还有前一个节点惦记

    //b->next = b1->next;
    ////b->next = b2;

    //std::cout << "smart_obj->refcount: " << smart_obj->refcount() << std::endl;
    //std::cout << "smart_obj1->refcount: " << smart_obj1->refcount() << std::endl;
    //std::cout << "smart_obj2->refcount: " << smart_obj2->refcount() << std::endl;
    //std::cout << "smart_obj3->refcount: " << smart_obj3->refcount() << std::endl;
    
    return smart_obj;
}

int test1() {
    Ptr<B> smart_obj = internal_test();
    std::cout << "---------------------" << std::endl;

    //std::cout << "smart_obj->refcount: " << smart_obj->refcount() << std::endl;
    //std::cout << "smart_obj->next->refcount: " << smart_obj->next->refcount() << std::endl;

    //for (; smart_obj != nullptr; smart_obj = smart_obj->next) {
    //    std::cout << "smart_obj->refcount: " << smart_obj->refcount() << std::endl;
    //}

    //for (Ptr<B> smart_obj_tmp = smart_obj; 
    //        smart_obj_tmp != nullptr; 
    //        smart_obj_tmp = smart_obj_tmp->next) {
    //    std::cout << "smart_obj_tmp->refcount: " << smart_obj_tmp->refcount() << std::endl;
    //}

    B* ptr = smart_obj;
    for (; ptr != nullptr; ptr = ptr->next) {
      std::cout << "--" << std::endl;
    }

    return 0;
}


int main() {
    //test();
    test1();

    //MyString str("aaaaaaaaaa");
    //std::cout << "str: " << str.c_str() << std::endl;
    return 0;
}
