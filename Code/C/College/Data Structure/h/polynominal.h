#ifndef POLYNOMINAL_H
#define POLYNOMINAL_H

#ifndef IOSTREAM
#define IOSTREAM

#include <iostream>

#endif // IOSTREAM

#ifndef STDLIB_H
#define STDLIB_H

#include <stdlib.h>

#endif // STDLIB_H

#ifndef USING
#define USING

using std::cin;
using std::cout;
using std::endl;
using std::ostream;
using std::istream;

#endif // USING

extern void flush();

class term
{
public:
	term(const int c,const int e, term* next = NULL): coef(c), exp(e){
		link = next;
	}
	term* insertAfter(const int c,const int e){
		link = new term(c, e, link);
		return link;
	}
private:
	int coef;
	int exp;
	term* link;
	friend ostream& operator <<(ostream&, const term&);
	friend class polynominal;
};

class polynominal
{
public:
	polynominal(){
		theList = new term(0, -1);
		theList->link = NULL;
	}
	~polynominal(){
		term *p = theList->link;
		while(p!=NULL){
			theList->link = p->link;
			delete p;
			p = theList->link;
		}
	}
	void addTerms(istream& in){
		term *q = theList;
		int c, e;
		cout << "Input terms(coef, exp): " << endl;
		while(1) {
		    scanf("%d%d", &c, &e);
		    flush();
		    if (e<0) {
		    	cout << "End." << endl;
		    	break;
		    }
		    q = q->insertAfter(c, e);
		}
	}
	void output(ostream& out) const{
		int first = true;
		term *p = theList->link;
		for (; p!=NULL; p=p->link){
			if (!first && p->coef>0) out << "+";
			first = false;
			out << *p;
		}
		cout << endl;
	}
	void polyAdd(const polynominal& r){
		term *q, *q1 = theList, *p;
		p = r.theList->link;
		q = q1->link;
		while(p!=NULL) {
		    while(q!=NULL && p->exp<q->exp) {
		        q1 = q; q = q->link;
		    }
		    if (q!=NULL && p->exp == q->exp){
		    	q->coef = q->coef + p->coef;
		    	if (!q->coef){
		    		q1->link = q->link;
		    		delete q;
		    		q = q1->link;
		    	}
		    	else{
		    		q1 = q; q = q->link;
		    	}
		    }
		    else{
		    	q1 = q1->insertAfter(p->coef, p->exp);
		    }
		    p = p->link;
		}
	}
	polynominal polyAddToAnother(const polynominal& r){
		term *q, *p;
		polynominal  c;
		term *res = c.theList;
		p = r.theList->link;
		q = theList->link;
		while(p!=NULL || q!=NULL) {
			if (p==NULL){
				res = res->insertAfter(q->coef, q->exp);
				q = q->link;
			}
			else if (q==NULL){
				res = res->insertAfter(p->coef, p->exp);
		    	p = p->link;
			}
		    else if(p->exp>q->exp){
		    	res = res->insertAfter(p->coef, p->exp);
		    	p = p->link;
		    }
			else if(p->exp<q->exp){
				res = res->insertAfter(q->coef, q->exp);
				q = q->link;
			}
			else{
				res = res->insertAfter(q->coef+p->coef, q->exp);
				p = p->link;
				q = q->link;
			}
		}
		return c;
	}
	void polyMul(const polynominal& a){
			polynominal *b, c;
			term *p = theList->link, *q;
			while(p!=NULL){
				b = new polynominal();
				term *r = b->theList;
				q = a.theList->link;
				while(q!=NULL){
					r = r->insertAfter(p->coef*q->coef, p->exp+q->exp);
					q = q->link;
				}
				c.polyAdd(*b);
				delete b;
				p = p->link;
			}
			cout << c;
	}
private:
	term* theList;
	friend ostream& operator <<(ostream&, const polynominal&);
	friend istream& operator >>(istream&, polynominal&);
	friend polynominal operator +(polynominal&, const polynominal&);
	friend void operator *(polynominal&, const polynominal&);	
};

ostream& operator <<(ostream& out, const term& val){
	if(!val.coef) return out;
	if(val.exp == 0 || val.coef != 1){
		out << val.coef;
	}
	switch(val.exp){
		case 0: break;
		case 1: out << "x"; break;
		default: out << "x^" << val.exp; break;
	}
	return out;
}

ostream& operator <<(ostream& out, const polynominal &x){
	x.output(out); return out;
}

istream& operator >>(istream& in, polynominal &x){
	x.addTerms(in); return in;
}

polynominal operator + (polynominal &a, const polynominal &b){
	return a.polyAddToAnother(b);
}

void operator *(polynominal &a, const polynominal &b){
	a.polyMul(b);
}

#endif // POLYNOMINAL_H
