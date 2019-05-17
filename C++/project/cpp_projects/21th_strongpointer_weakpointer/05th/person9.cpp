
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <utils/RefBase.h>

using namespace std;
using namespace android;


class Person : public RefBase {

private:
	char *name;
	
	wp<Person> father;
	wp<Person> son;

public:
	Person() {
		cout <<"Pserson()"<<endl;
	}

	Person(char *name) {
		cout <<"Pserson(char *name)"<<endl;
		this->name = name;
	}

	~Person()
	{
		cout << "~Person()"<<endl;
	}

	void setFather(sp<Person> &father)
	{
		this->father = father;
	}

	void setSon(sp<Person> &son)
	{
		this->son = son;
	}

	char *getName(void)
	{
		return name;
	}
	
	void printInfo(void)
	{
		sp<Person> f = father.promote();
		sp<Person> s = son.promote();
		
		//cout<<"just a test function"<<endl;
		cout<<"I am "<<name<<endl;

		if (f != 0)
			cout<<"My Father is "<<f->getName()<<endl;

		if (s != 0)
			cout<<"My Son is "<<s->getName()<<endl;
	}
};

/* ��������ﺬ�����������Ա:
 * ����ʱ: �ȹ������������Ա, �ٹ��������
 * ����ʱ: ˳��պ��෴
 */

void test_func()
{
	/* 1. ���� new Person()
	 * 1.1 Person�������father�ȱ�����
	 * 1.2 Person�������son������
	 * 1.3 Person������
	 * 2. Person�����ָ�봫��"sp<Person> father"
	 *    ����: sp(T* other) ������
	 *    �����������Person��������ü���(���ڴ�ֵ����1)
	 */
	sp<Person> father = new Person("LiYiShi");


	/* 1. ���� new Person()
	 * 1.1 Person�������father�ȱ�����
	 * 1.2 Person�������son������
	 * 1.3 Person������
	 * 2. Person�����ָ�봫��"sp<Person> son"
	 *    ����: sp(T* other) ������
	 *    �����������Person��������ü���(���ڴ�ֵ����1)
	 */
	sp<Person> son = new Person("LiErShi");

	/* ����һ��"=" : this->son = son
	 * "="������, �����ٴ����Ӹ�Person��������ü���
	 * ����son��Ӧ��Person��������ü�������Ϊ2
	 */
	father->setSon(son);

	/* ����һ��"=" : this->father = father
	 * "="������, �����ٴ����Ӹ�Person��������ü���
	 * ����father��Ӧ��Person��������ü�������Ϊ2
	 */
	son->setFather(father);

	father->printInfo();

	son->printInfo();


	/* ��test_funcִ����ʱ, father��son������
	 * 1. �ȿ�father:
	 *    ~sp(): decStrong, ����Ὣ����ֵ��1 , father��Ӧ��Person�ļ���ֵ����1, ��û����0, ����û��delete
	 * 2. ����son:
	 *    ~sp(): decStrong, ����Ὣ����ֵ��1 , son��Ӧ��Person�ļ���ֵ����1, ��û����0, ����û��delete
	 */
}

int main(int argc, char **argv)
{	
	test_func();

	return 0;
}
