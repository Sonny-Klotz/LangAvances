#include <iostream>

using namespace std;

template <class T>
class CNoeud;

template <class T>
class CList;

template <class T>
ostream& operator<<(ostream& o, const CList<T>& p);

template <class T>
class CPile;

template <class T>
class CFile;

template <class T>
class CNoeud
{
	private:
		T val;
		CNoeud<T> *next;
	public:
		CNoeud(T v){ val = v; next = NULL; }
		CNoeud(const CNoeud<T>& n)
		{
			val = n.getVal();
			CNoeud<T> *ptr = n.getNext();
			if(ptr == NULL)
				next = NULL;
		
			next = new CNoeud<T>(ptr->getVal());
			ptr = ptr->getNext();
			CNoeud<T> *ptr2 = next;
			while(ptr != NULL)
			{
				ptr2 = new CNoeud<T>(ptr->getVal());
				ptr = ptr->getNext();
				ptr2 = ptr2->getNext();
			}
		}
		~CNoeud(){ delete next; next = NULL; }
		T getVal() const{ return val; }
		CNoeud<T>* getNext() const{ return next; }
		void setNext(CNoeud<T> *n){ next = n; }
};

template <class T>
class CList
{
	protected:
		CNoeud<T> *tete;
	public:
		CList(){ tete = NULL; }
		~CList(){ delete tete; tete = NULL; }
		CNoeud<T>* getTete() const{ return tete; }
		virtual CList<T>& operator<(T i) = 0;
		CList<T>& operator>(T& i)
		{
			CNoeud<T> *tmp = tete->getNext();
			tete->setNext(NULL);
			i = tete->getVal();
			delete tete;
			tete = tmp;
			return *this;
		}
		friend ostream& operator<< <>(ostream& o, const CList<T>& p);
};

template <class T>
ostream& operator<<(ostream& o, const CList<T>& p)
{
	CNoeud<T> *ptr = p.getTete();
	while(ptr != NULL )
	{
		o << ptr->getVal() << ' ';
		ptr = ptr->getNext();
	}
	o << endl;
	return o;
}

template <class T>
class CPile : public CList<T>
{
	public:
		CPile(){}
		~CPile(){}
		CPile<T>& operator<(T i)
		{
			CNoeud<T> *ptr = this->tete;
			this->tete = new CNoeud<T>(i);
			this->tete->setNext(ptr);
			return *this;
		}
};

template <class T>
class CFile : public CList<T>
{
	public:
		CFile(){}
		~CFile(){}
		CFile<T>& operator<(T i)
		{ 
			CNoeud<T> *tmp = new CNoeud<T>(i);
			if(this->tete == NULL)
				this->tete = tmp;
			else
			{
				CNoeud<T> *ptr;
				ptr = this->tete;
	
				while(ptr->getNext() != NULL)
					ptr = ptr->getNext();
		
				ptr->setNext(tmp);
			}
			return *this;
		}
};
		
int main()
{
	CPile<int> pile;
	CFile<int> file;
	
	CList<int> *ptlist = &file;
	*ptlist < 0 < 1;
	cout << *ptlist;
	int i;
	*ptlist > i;
	cout << *ptlist << "i=" << i << endl;
	
	 ptlist = &pile;
	 *ptlist < 0 < 1;
	cout << *ptlist;
	*ptlist > i;
	cout << *ptlist << "i=" << i << endl;
	
	return 0;
}
