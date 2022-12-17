/*
 * ALGO2 IN1 20C LAB01
 * Robert Franczak
 * fr47434@zut.edu.pl
 */


#include <iostream>
#include <iomanip>
#include "math.h"
#include <random>
#include "unistd.h"
#include "chrono"
#define DEFAULT_VALUE 0
//#define SHOW 1

template<typename T>
class LinkedList;

struct dummyStruct{
    int DefaultA;
    char DefaultB;

    bool operator<(const dummyStruct& a_TData)
    {
        bool b_result = false;
        if(DefaultA == a_TData.DefaultA)
        {
            b_result = DefaultB < a_TData.DefaultB;
        }
        else
        {
            b_result = DefaultA < a_TData.DefaultA;
        }
        return b_result;
    }

    bool operator>(const dummyStruct& a_TData)
    {
        bool b_result = false;
        if(DefaultA == a_TData.DefaultA)
        {
            b_result = DefaultB > a_TData.DefaultB;
        }
        else
        {
            b_result = DefaultA > a_TData.DefaultA;
        }
        return b_result;
    }

private:
    template<typename T>
   friend class LinkedList;
   bool operator== (const dummyStruct& a_rsObj)
    {
        bool isTrue = false;
        if((DefaultA == a_rsObj.DefaultA) &&(DefaultB == a_rsObj.DefaultB))
        {
            isTrue = true;
        }
        return isTrue;
    }

};


std::ostream &operator<<(std::ostream &os, const dummyStruct& sdummyStructObj)
{
    os << "[ "<< "INT: " <<sdummyStructObj.DefaultA << " CHAR: "<< sdummyStructObj.DefaultB<< "]" << std::endl;

    return os;
}

std::ostream &operator<<(std::ostream &os, const dummyStruct* sdummyStructObj)
{
    os << "[ "<< "INT: " <<sdummyStructObj->DefaultA << " CHAR: " <<sdummyStructObj->DefaultB<< "]" << std::endl;

    return os;
}

template<typename T>
class LinkedList {
public:
    LinkedList(): length(DEFAULT_VALUE), pHead(nullptr),pTail(nullptr){ printf("Class *LinkedList* created - successful\n");};
    ~LinkedList() = default;

    struct Node{
        T TData;
        Node* sNext;
        Node* sPrev;
        Node():sNext(nullptr),sPrev(nullptr){};

        bool operator<(const Node& a_TData)
        {
            return TData < a_TData.TData;
        }

        bool operator>(const Node& a_TData)
        {
            return TData > a_TData.TData;
        }
    };

    uint64_t size()
    {
        return length;
    }

    // a)
    void backPush(const T& a_TElement)
    {
        Node* newTail = new Node();
        newTail->TData = a_TElement;

        if(nullptr == pTail)
        {
            pHead = newTail;
        }
        else
        {
            pTail->sNext = newTail;
            newTail->sPrev = pTail;
            newTail->sNext = nullptr;
        }
        pTail = newTail;
        length++;
    }

    // b)
    void frontPush(const T& a_TData)
    {
        Node *pNewHead = new Node();
        pNewHead->TData = a_TData;

        if(nullptr == pHead)
        {
            pTail = pNewHead;
            pNewHead->sPrev = nullptr;
        }
        else
        {
            pNewHead->sPrev = nullptr;
            pNewHead->sNext = pHead;
            pHead->sPrev = pNewHead;
        }

        pHead = pNewHead;
        length++;
    }

    // c)
    void deleteLast()
    {
        if(pTail->sPrev != nullptr)
        {
            Node* sTemporary;
            sTemporary = pTail->sPrev;
            sTemporary->sNext = nullptr;

            delete(pTail);
            pTail = sTemporary;
            length--;
        }
        else
        {
            delete(pTail);
            pTail = nullptr;
            pHead = nullptr;
            length--;
        }
    }

    // d)
    void deleteFirst()
    {
        if(pHead->sNext != nullptr)
        {
            Node* sTemporary;
            sTemporary = pHead->sNext;
            sTemporary->sPrev = nullptr;
#ifdef SHOW
            //std::cout << "Deleted HEAD node: "<< pHead<< std::endl;
#endif
            delete(pHead);
            pHead = sTemporary;
            length--;
        }
        else
        {
            delete(pHead);
            pTail = nullptr;
            pHead = nullptr;
            length--;
#ifdef SHOW
            //std::cout << "Deleted HEAD node: "<< pHead<< std::endl;
#endif
        }
    }

    // e)
    T* getData(const unsigned a_Index)
    {
        T* result = nullptr;
        unsigned int Index = 0;

       if(a_Index >= size())
       {
#ifdef SHOW
           std::cout << "Index out of range..." << std::endl;
#endif
       }
       else
       {
           for (Node* sIndex = pHead; sIndex; sIndex = sIndex->sNext)
           {
               if (Index == a_Index)
               {
                   result = &(sIndex->TData);
                   break;
               }
               Index++;
           }
       }
        return result;
    }

    // f)
    void swapData(const unsigned a_Index, const T& a_TData)
    {
        int Index = 0;

        if(a_Index >= size())
        {
#ifdef SHOW
            std::cout << "Index out of range..." << std::endl;
#endif
        }
        else
        {
            for (Node* sIndex = pHead; sIndex; sIndex = sIndex->sNext)
            {
                if(Index == a_Index)
                {
                    sIndex->TData = a_TData;
                    break;
                }
                Index++;
            }
        }
    }

    // g)
    Node* findElement(const T& a_TElement)
    {
        Node* sResult = nullptr;

        for (Node* sIndex = pHead; sIndex; sIndex = sIndex->sNext)
        {
            if(sIndex->TData == a_TElement)
            {
#ifdef SHOW
                std::cout << "Element found: " <<  sIndex <<std::endl;
#endif
                sResult = sIndex;
                break;
            }
        }
        if(nullptr == sResult)
        {
#ifdef SHOW
            std::cout << "Element not found..." << std::endl;
#endif
        }
        return sResult;
    }

    // h)
    bool findAndDelete(const T& a_TElement)
    {
        Node* sDelElement =  findElement(a_TElement);
        bool isDeleted = false;

        if(nullptr != sDelElement)
        {
            if(sDelElement == pHead)
            {
                deleteFirst();
#ifdef SHOW
                std::cout << "Deleted Node: " << sDelElement << std::endl;
#endif
            }
            else if(sDelElement == pTail)
            {
                deleteLast();
#ifdef SHOW
                std::cout << "Deleted Node: " << sDelElement << std::endl;
#endif
            }
            else
            {
                sDelElement->sNext->sPrev = sDelElement->sPrev;
                sDelElement->sPrev->sNext = sDelElement->sNext;
                isDeleted = true;
#ifdef SHOW
                std::cout << "Deleted Node: " << sDelElement << std::endl;

#endif
                length--;
                delete(sDelElement);
            }
        }

        return isDeleted;
    }

    // i)
    void addOrdered(const T& a_TData)
    {
        if(nullptr == pHead || (pHead->TData > a_TData))
        {
            frontPush(a_TData);
        }
        else if(pTail->TData < a_TData)
        {
            backPush(a_TData);
        }
        else
        {
            Node* sTemp = new Node;
            sTemp->TData =a_TData;
            for(Node* sIndex = pHead; sIndex; sIndex = sIndex->sNext)
            {
                if(sIndex->TData > a_TData)
                {
                    sTemp->sNext = sIndex;
                    sTemp->sPrev = sIndex->sPrev;

                    sIndex->sPrev->sNext =sTemp;
                    sIndex->sPrev = sTemp;
                    break;
                }
            }
            length++;
        }
    }

    // j)
    void clearList()
    {
        int delIndex = length;
        for (int Index = 0; Index < delIndex; Index++)
        {
            deleteLast();
        }
        pHead = nullptr;
        pTail = nullptr;
#ifdef SHOW
        std::cout << "List is cleared..."<< std::endl;
#endif
    }

    void show()
    {
        if(nullptr != pHead)
        {
            for (Node* sIndex = pHead; sIndex;sIndex = sIndex->sNext)
            {
//                std::cout << "Node address: " << i << std::endl;
//                std::cout << "Next: " << i->sNext << std::endl;
//                std::cout << "Previous: " << i->sPrev << std::endl;
                std::cout << sIndex->TData;
                std::cout << std::endl;
            }
            std::cout << "List size: " << size() << std::endl;
        }
        else
        {
            std::cout << "List is empty..." << std::endl;
        }
    }


private:
    Node *pHead;
    Node *pTail;
    int length;
};

int main() {

#ifdef SHOW
    auto *linkedList = new LinkedList<dummyStruct>();

    dummyStruct sDummy1 = {1,'A'};
    dummyStruct sDummy2 = {2,'B'};
    dummyStruct sDummy3 = {4,'D'};
    dummyStruct sDummy4 = {5,'E'};

    dummyStruct sDummy0 = {0,'X'};
    dummyStruct sDummyOrder = {2,'A'};

    // POINTERS
//     LinkedList<dummyStruct*> *linkedList2= new LinkedList<dummyStruct*>();
//     dummyStruct* sDummy6 = new dummyStruct;
//     sDummy6->DefaultA = 10;
//     sDummy6->DefaultB = 'J';
//     linkedList2->frontPush(sDummy6);

    std::cout << "MAŁA LISTA" << std::endl;
    // DODANIE ELMENTU NA KONIEC LISTY

    std::cout <<"ADDING 3 NEW NODES" << std::endl;
    linkedList->backPush(sDummy2);
    linkedList->backPush(sDummy3);
    linkedList->backPush(sDummy4);
    std::cout <<"SHOW METHOD AFTER ADDING 3 ELEMENTS:" << std::endl;
    linkedList->show();
    std::cout << std::endl;


    //DODANIE ELEMNTU NA POCZATEK LISTY
    std::cout <<"FRONT PUSH ONE NODE" << std::endl;
    linkedList->frontPush(sDummy1);
    std::cout <<"SHOW METHOD AFTER APUSH ONE ELEMENT (FRONT):" << std::endl;
    linkedList->show();
    std::cout << std::endl;

    //USUNIECIE OSTATNIEGO ELEMENTU
    std::cout <<"DELETE LAST NODE" << std::endl;
    linkedList->deleteLast();
    std::cout <<"SHOW METHOD AFTER DELETE LAST NODE:" << std::endl;
    linkedList->show();
    std::cout << std::endl;

    //USUNIECIE PIERWSZEGO ELEMENTU
    std::cout <<"DELETE FIRST NODE" << std::endl;
    linkedList->deleteFirst();
    std::cout <<"SHOW METHOD AFTER DELETE FIRST NODE:" << std::endl;
    linkedList->show();
    std::cout << std::endl;

    // GET DATA
    std::cout <<"GET DATA OF PARTICULAR NODE" << std::endl;
    auto *x = linkedList->getData(1);
    if(x != nullptr)
    {
        std::cout << "Data address: " << x << std::endl;
        std::cout << "INT: " << x->DefaultA << "CHAR: " << x->DefaultB << std::endl;
    }
    std::cout << std::endl;

    // PODMIANA DANYCH
    std::cout <<"SWAP DATA OF PARTICULAR NODE" << std::endl;
    linkedList->swapData(0,sDummy0);
    std::cout <<"SHOW METHOD AFTER SWAP DATA:" << std::endl;
    linkedList->show();
    std::cout << std::endl;

    //WYSZUKOWANIE ELEMENTU
    std::cout <<"FIIND PARTICULAR NODE" << std::endl;
    auto *d =linkedList->findElement(sDummy0);
    if(nullptr != d)
    {

        std::cout << "Found element: Data address: " << d << std::endl;
        std::cout << "INT: " << d->TData.DefaultA << " CHAR: " << d->TData.DefaultB << std::endl;
    }
    std::cout << std::endl;
        // ADD MORE ELEMENTS TO TEST
    std::cout <<"ADDING MORE NODE FOR EXAMPLES (3)" << std::endl;
        linkedList->backPush(sDummy1);
        linkedList->backPush(sDummy2);
        linkedList->backPush(sDummy4);


        // WYSZUKANIE I USUNIECIE ELEMENTU
        std::cout <<"FIND AND DELETE NODE" << std::endl;
        linkedList->findAndDelete(sDummy3);
        std::cout <<"SHOW METHOD AFTER FIND AND DELETE:" << std::endl;
        linkedList->show();
        std::cout << std::endl;

        //DODANIE NOWEGO ELEMENTU Z WYMUSZENIEM PORZADKU
        std::cout <<"ADD NEW NODE WITH ORDER" << std::endl;
        linkedList->addOrdered(sDummy3);
        std::cout <<"SHOW METHOD AFTER ADD WITH ORDER:" << std::endl;
        linkedList->show();
        std::cout << std::endl;

        // CZYSZCZENIE LISTY
        std::cout <<"CLEAR LIST" << std::endl;
        linkedList->clearList();
        std::cout <<"SHOW METHOD AFTER CLEAR LIST:" << std::endl;
        linkedList->show();
        std::cout << std::endl;
        delete(linkedList);
#endif

#ifndef SHOW
        //                      WSKAZNIKI
//
//            LinkedList<dummyStruct>* ll = new LinkedList<dummyStruct*>();
//            uint16_t nrOfNodes = 1000;
//            uint16_t elemendsTofound = 100;
//            std::random_device rd;
//            std::mt19937 gen(rd());
//            std::uniform_int_distribution<> distr(65, 90);
//
//            std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
//            for (int j = 0; j < nrOfNodes; ++j) {
//                uint16_t randomINT = rand() % 100;
//                dummyStruct so = new dummyStruct;
//                so->DefaultA = randomINT;
//                so->DefaultB = distr(gen);
//                std::cout << so;
//                ll->backPush(so);
//            }
//            std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
//            std::cout <<"Create "<< nrOfNodes <<" Nodes, and show datas:  " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
//
//            begin = std::chrono::steady_clock::now();
//            for (int i = 0; i < elemendsTofound; ++i) {
//                uint16_t randomINT = rand() % 100;
//                u_char s = distr(gen);
//                dummyStruct so = {randomINT,s};
//
//                ll->findElement(&so);
//            }
//            end = std::chrono::steady_clock::now();
//            std::cout<<"Elements to find ["<< elemendsTofound <<"] :  " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;

        //                          STATYCZNIE
         LinkedList<dummyStruct>* ll = new LinkedList<dummyStruct>();
            std::random_device rd;
            std::mt19937 gen(time(nullptr));
            std::uniform_int_distribution<> distr(65, 90);
            std::uniform_int_distribution<> DISTaa(0, 100);
            for (int j = 0; j < 1000; ++j) {
                char pp = distr(gen);
                int randomINT = DISTaa(gen);
                dummyStruct so = {randomINT,pp};
                std::cout << j << so << std::endl;
                ll->addOrdered(so);
            }
            ll->deleteLast();
            ll->show();

            //linkedList->showList();
    delete(ll);
#endif
    return 0;
}