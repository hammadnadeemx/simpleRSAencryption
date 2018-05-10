#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;
class Matrix{
	int row,col;
	float **ptr;
	public:
	Matrix(){
		row=0;
		col=0;
		ptr=NULL;		
	}
	Matrix(int r, int c){
		row=r;
		col=c;
		ptr=new float*[row];
		for(int i=0;i<row;i++){
			*(ptr+i)=new float[col];
		}
	}
	Matrix(int r, int c,int n){//initialize with random values ranging from 0 to n-1;
		row=r;
		col=c;
		ptr=new float*[row];
		for(int i=0;i<row;i++){
			*(ptr+i)=new float[col];
		}
		for(int i=0;i<row;i++){
			for(int j=0;j<col;j++){
				*(*(ptr+i)+j)=rand() % n +1;
			}
		}
	}
	Matrix(const Matrix & inp){
		row=inp.row;
		col=inp.col;
		ptr=new float*[row];
		for(int i=0;i<row;i++){
			*(ptr+i)=new float[col];
		}
		for(int i=0;i<row;i++){
			for(int j=0;j<col;j++){
				*(*(ptr+i)+j)=*(*(inp.ptr+i)+j);
			}
		}		
	}
	void set(int i, int j, float val){
		*(*(ptr+i)+j)=val;		
	}
	float get(int i, int j){
		return *(*(ptr+i)+j);
	}
	Matrix assign(const Matrix & inp){
		Matrix *temp;
		temp=new Matrix(inp.row,inp.col);
		for(int i=0;i<inp.row;i++){
			for(int j=0;j<inp.col;j++){
				*(*(temp->ptr+i)+j)=*(*(inp.ptr+i)+j);
				}
			}
			return *temp;
		}
	void copy(const Matrix & inp){
		if(ptr!=NULL){
		for(int i=0;i<row;i++){
			delete [] *(ptr+i);
		}
		delete [] ptr;
		}
		row=inp.row;
		col=inp.col;
		ptr=new float*[row];
		for(int i=0;i<row;i++){
			*(ptr+i)=new float[col];
		}
		for(int i=0;i<row;i++){
			for(int j=0;j<col;j++){
				*(*(ptr+i)+j)=*(*(inp.ptr+i)+j);
			}
		}		
	}
	Matrix add(const Matrix & inp){//adds two Matrices and returns the result
		if((col==inp.col)&(row==inp.row)){//try assert
		Matrix *temp;
		temp=new Matrix(row,col);
		for(int i=0;i<row;i++){
			for(int j=0;j<col;j++){
				*(*(temp->ptr+i)+j)=*(*(ptr+i)+j)+*(*(inp.ptr+i)+j);
				}
			}
		return *temp;		
		}
		else{
			cout<<"the matrices have different dimensions\n";
		}
	}
	Matrix subtract(const Matrix & inp){//subtracts two Matrices and returns the result
		if((col==inp.col)&(row==inp.row)){//try assert
		Matrix *temp;
		temp=new Matrix(row,col);
		for(int i=0;i<row;i++){
			for(int j=0;j<col;j++){
				*(*(temp->ptr+i)+j)=*(*(ptr+i)+j)-*(*(inp.ptr+i)+j);
				}
			}
		return *temp;		
		}
		else{
			cout<<"the matrices have different dimensions\n";
		}
	}
	Matrix multiply(const Matrix & inp){//multiplies two Matrices and returns the result
		if(col==inp.row){//try assert
		Matrix *temp;
		float t=0;
		temp=new Matrix(row,inp.col);
		for(int i=0;i<row;i++){ //2
			for(int j=0;j<inp.col;j++){// 1
				for(int q=0;q<col;q++){//3
					t+=*(*(ptr+i)+q)**(*(inp.ptr+q)+j);
				}
				*(*(temp->ptr+i)+j)+=t;
				t=0;				
			}
		}
		return *temp;		
		}
		else{
			cout<<"the matrices have different dimensions\n";
		}
	}	
	Matrix powern(int n){
			if(row==col){
				Matrix *temp;
				temp=new Matrix(row,col);
				for(int i=0;i<row;i++){
						for(int j=0;j<col;j++){
							*(*(temp->ptr+i)+j)=*(*(ptr+i)+j);
						}
					}
				if(n<=1){
					temp->modn(10);
					return *temp;
				}
				else {
					while(n>1){
						temp->copy(this->multiply(*temp));
						--n;
						temp->modn(10);
					}
					return *temp;	
				}			
			}
			cout<<"matrix has to be NxN\n";	
	}		
Matrix indipower(int n){// try do simple rsa here p-1Xq-1
			if(row==col){
				Matrix *temp;
				temp=new Matrix(row,col);
				for(int i=0;i<row;i++){
						for(int j=0;j<col;j++){
							*(*(temp->ptr+i)+j)=*(*(ptr+i)+j);
						}
					}
				if(n<=1){
					temp->modn(10);
					return *temp;
				}
				else {
					while(n>1){
						for(int i=0;i<row;i++){
							for(int j=0;j<col;j++){
								*(*(temp->ptr+i)+j)*=*(*(ptr+i)+j);
							}
						}
						--n;
						
					}
					temp->modn(10);
					return *temp;	
				}			
			}
			cout<<"matrix has to be NxN\n";	
	}		
	
	
	
	Matrix add(float val){//assigns a constant to every element
		Matrix *temp;
		temp=new Matrix(row,col);
		for(int i=0;i<row;i++){
			for(int j=0;j<col;j++){
				*(*(temp->ptr+i)+j)=*(*(ptr+i)+j)+val;
				}
			}
		return *temp;		
	}
	Matrix multiply(float val){//multiplies every element with a constant
		Matrix *temp;
		temp=new Matrix(row,col);
		for(int i=0;i<row;i++){
			for(int j=0;j<col;j++){
				*(*(temp->ptr+i)+j)=*(*(ptr+i)+j)*val;
				}
			}
		return *temp;		
	}
	void display(){
		for(int i=0;i<row;i++){
			for(int j=0;j<col;j++){
				cout<<*(*(ptr+i)+j)<<"  ";
			}
			cout<<endl;
		}
	}
	void modn(int n){
		for(int i=0;i<row;i++){
			for(int j=0;j<col;j++){
				while(*(*(ptr+i)+j)>=n){
					*(*(ptr+i)+j)-=n;
				}
				while(*(*(ptr+i)+j)<0){
					*(*(ptr+i)+j)+=n;
				}
			}
		}		
	}
	~Matrix(){
		if(ptr!=NULL){
		for(int i=0;i<row;i++){
			delete [] *(ptr+i);
		}
		delete [] ptr;
		}
	}
};

int main(){
	srand(time(0));
	Matrix a(2,2,9),b(2,2),e(2,2);//initialize matrices of 2x2 with random values from 0 to 9
	cout<<"Original image\n";
	a.display();
	b.copy(a.indipower(3));
	//b.modn(10);
	cout<<"Encrypted image\n";
	b.display();
	e.copy(b.indipower(7));
	//e.modn(10);
	cout<<"Decrypted image\n";
	e.display();
	//e.copy(b.powern(3));
	//e.display();
	return 0;
}
