#include "ts/List.h"

class Foo
{
public:
    int x;

    void
    foo()
    {
    }

    /*
    class Link_link {
      public:
        static Foo* &
        next_link(Foo *c)
        {
          //return NULL;
          return c->slink.next;
        }

        static const Foo*
        next_link(const Foo *c)
        {
          //return NULL;
          return c->slink.next;
        }

    };
    class Link_slink {
      public:
        static Foo* &
        next_link(Foo *c)
        {
          return c->slink.next;
        }

        static const Foo*
        next_link(const Foo *c)
        {
          return c->slink.next;
        }
    };
    SLink<Foo> slink;
    */

    SLINK(Foo, slink);
    LINK(Foo, dlink);

    Foo(int i = 0) : x(i) {}
};

// 0SLL链表模板类本质是一个全局链表  里面只有一个head指针 并且next方法依赖反转
// 1.1链表元素/entry/node/foo中必须有SLink 用于记录next指针
// 1.2必须提供 next方法

int
main() {
    SList(Foo, slink) s; //SLL<Foo, Foo::Link_slink> s;
    DList(Foo, dlink) d;

    Foo *f1 = new Foo;
    f1->x   = 1;
    Foo *f2 = new Foo;
    f2->x   = 2;

    s.push(f1);
    s.push(f2);

    printf("s.empty(): %d\n", s.empty());
    printf("s.pop(): %d\n", (s.pop())->x);

    return 0;
}

int
main2()
{
    SList(Foo, slink) s; // SLL<Foo, Foo::Link__slink> s;
    DList(Foo, dlink) d; // DLL<Foo, Foo::Link__dlink> d;
    Que(Foo, dlink) q;

    Foo *f = new Foo;
    f->x   = 7;
    s.push(f);
    d.push(s.pop());
    q.enqueue(d.pop());
    for (int i = 0; i < 100; i++) {
        q.enqueue(new Foo(i));
    }
    int tot = 0;
    for (int i = 0; i < 101; i++) {
        Foo *foo = q.dequeue();
        tot += foo->x;
        delete foo;
    }
    if (tot != 4957) {
        printf("test_List FAILED\n");
        exit(1);
    } else {
        printf("test_List PASSED\n");
        exit(0);
    }
}
