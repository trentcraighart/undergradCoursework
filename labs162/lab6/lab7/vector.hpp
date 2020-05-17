#include <stdlib.h>
#include <iostream>
#include <stdexcept>
using std::cout;
using std::endl;
using std::exception;
using std::out_of_range;
template <class T>
class vector {
   private:
      T *v;
      int s;
   public:
      vector(){
	 s=0;
	 v=NULL;
      }

//Copy Constructor

      vector(vector<T> &x){
         s = x.s;
         v = new T[s];
         for(int i = 0; i < s; i++){
            v[i] = x.v[i];
      	 }
      }
      
      ~vector(){
	 delete [] v;
      }
      
      int size() {
	 return s;
      }
      
      void push_back(T ele) {
	 T *temp;
	 temp = new T[++s];
	 for(int i=0; i<s-1; i++)
	    temp[i]=v[i];

	 delete [] v;
	 v=temp;
	 v[s-1]=ele;
      }

//Assignment Operator Overload

	void operator=(vector<T> &d){
		s = d.s;
		v = d.v;
	}

	T at(int x){
		try{
			return v[x];
		}
		catch(T v[x]){
			cout << "bad input";
			throw out_of_range("out of my vector bounds");
			cout << "doesn't work" << endl;
		}
	}








};
