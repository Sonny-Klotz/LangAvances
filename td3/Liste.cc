#include <iostream>

using namespace std;

class CNoeud
{
	private:
		int val;
		CNoeud *next;
	public:
		CNoeud(int val);
		CNoeud(const CNoeud& n);
		~CNoeud();
		int getVal() const;
		CNoeud* getNext() const;
		void setNext(CNoeud *n);
};

CNoeud::CNoeud(int v){ val = v; next = NULL; }
CNoeud::CNoeud(const CNoeud& n)
{
	val = n.getVal();
	CNoeud *ptr = n.getNext();
	if(ptr == NULL)
		next = NULL;
	
	next = new CNoeud(ptr->getVal());
	ptr = ptr->getNext();
	CNoeud *ptr2 = next;
	while(ptr != NULL)
	{
		ptr2 = new CNoeud(ptr->getVal());
		ptr = ptr->getNext();
		ptr2 = ptr2->getNext();
	}
}
CNoeud::~CNoeud(){ delete next; }
int CNoeud::getVal() const{ return val; }
CNoeud* CNoeud::getNext() const{ return next; }
void CNoeud::setNext(CNoeud *n){ next = n; }
		
class CList
{
	protected:
		CNoeud *tete;
	public:
		CList();
		~CList();
		virtual void push(int i) = 0;
		virtual int getTop() = 0; //la methode est commune, pas besoin d'etre abstraite (pareil pour l'opé >)
		CNoeud* getTete() const;
		virtual CList& operator<(int i) = 0; //voir commentaire main
		virtual CList& operator>(int& i) = 0;
};

CList::CList(){ tete = NULL; }
CList::~CList(){ delete tete; }
CNoeud* CList::getTete() const{ return tete; }
ostream& operator<<(ostream& o, const CList& p)
{
	CNoeud *ptr = p.getTete();
	while(ptr != NULL )
	{
		o << ptr->getVal() << ' ';
		ptr = ptr->getNext();
	}
	o << endl;
	return o;
}

class CPile : public CList
{
	public:
		CPile();
		~CPile();
		void push(int i);
		int getTop();
		CPile& operator<(int i);
		CPile& operator>(int& i);
};

CPile::CPile(){}
CPile::~CPile(){ delete tete; }
void CPile::push(int i)
{
	CNoeud *ptr = tete;
	tete = new CNoeud(i);
	tete->setNext(ptr);	
}
int CPile::getTop(){ return tete->getVal(); }
CPile& CPile::operator<(int i){ push(i); return *this; }
CPile& CPile::operator>(int& i){ i = getTop(); return *this; }

class CFile : public CList
{
	public:
		CFile();
		~CFile();
		void push(int i);
		int getTop();
		CFile& operator<(int i);
		CFile& operator>(int& i); 
};

CFile::CFile(){}
CFile::~CFile(){ delete tete; }
void CFile::push(int i)
{
	CNoeud *tmp = new CNoeud(i);
	if(tete == NULL)
		tete = tmp;
	else
	{
		CNoeud *ptr;
		ptr = tete;
	
		while(ptr->getNext() != NULL)
			ptr = ptr->getNext();
		
		ptr->setNext(tmp);
	}
}
int CFile::getTop(){ return tete->getVal(); }
CFile& CFile::operator<(int i){ push(i); return *this; }
CFile& CFile::operator>(int& i){ i = getTop(); return *this; }
		
int main()
{
	CPile pile;
	CFile file;
	
	CList *ptlist = &file;
	*ptlist < 0 < 1; //ptlist est de type CList, la methode doit etre definie au niveau statique pour pouvoir compiler
	//voir indication dans le corps de la classe
	cout << *ptlist;
	int i;
	*ptlist > i;
	cout << *ptlist << "i=" << i << endl;
	
	 ptlist = &pile;
	 *ptlist < 0 < 1;
	cout << *ptlist;
	*ptlist > i;
	cout << *ptlist << "i=" << i << endl;
	//si l'exo demande pop, au lieu de getTop, definir la copie de liste pour gerer les delete correctement
	//edit : on peut pop sans passer par la copie de liste : il faut sauvegarder le next, l'affecter a null puis delete la tete,
	// on remet ensuite la tete a la valeur sauvegardé. le delete récursif s'arrete vu qu'affecte a null, et donc on conserve le reste de la liste
	
	return 0;
}
