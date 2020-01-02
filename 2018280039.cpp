#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h> 
#include <boost/algorithm/string.hpp> 
using namespace std;
typedef struct n{
	string no;
	unsigned int puan;
	struct n *next;
}ogrenci;
ogrenci *sortingpush(ogrenci *n,string no,unsigned int puan){
	if(n==NULL){
		n=(ogrenci *)malloc(sizeof(ogrenci));
		n->puan=puan;
		n->no=no;
		n->next=NULL;
		return n;
	}else if(puan>n->puan){
		ogrenci *n2=NULL;
		n2=sortingpush(n2,no,puan);
		n2->next=n;
		return n2;
	}else{
		ogrenci *n3=n;
		while(n->next!=NULL){ 
			if(n->puan>=puan&&puan>n->next->puan)
				break;
			n=n->next;
		}
		if(n->next==NULL){
			ogrenci *n2=NULL;
			n->next=sortingpush(n2,no,puan);
			return n3;
		}else{
			ogrenci *n2=n->next;
			ogrenci *n4=NULL;
			n4=sortingpush(n4,no,puan);
			n->next=n4;
			n4->next=n2;
			return n3;
		}
	}
}
//https://stackoverflow.com/questions/12241152/boost-no-such-file-or-directory
//https://www.geeksforgeeks.org/boostsplit-c-library/
int main(){
	ifstream dosyaOku ("input.txt");
	ogrenci *a=NULL;
	string satir;
	getline(dosyaOku,satir);
	getline(dosyaOku,satir);
	vector<string> CevapAnahtari; 
    boost::split(CevapAnahtari, satir, boost::is_any_of(","));
    float ortalama=0;
    float min=100,max=0;
    int count=0;
	while(getline(dosyaOku,satir)){
		vector<string> Cevap; 
    	boost::split(Cevap, satir, boost::is_any_of(","));
    	unsigned int puan=0;
    	for(int i=1;i<Cevap.size();++i){
    		if(Cevap[i].empty()){
    			continue;
    		}
    		else if(Cevap[i]==CevapAnahtari[i-1]){
    			puan+=4;
    		}else{
    			puan+=-1;
    		}
    	}
    	a=sortingpush(a,Cevap[0],puan);
    	ortalama+=puan;
    	count++;
    	if(puan<min)
    		min=puan;
    	if(max<puan)
    		max=puan; 	
	}
	ortalama/=(float)count;
	int xas=0;
	int fg;
	int gf;
	if(count%2==1){
		count/=2;
		count+=1;
		xas=1;
	}else{
		xas=0;
		count/=2;
	}
	ofstream dosyaYaz("output.txt");
	while(a!=NULL){
		count--;
		if(xas==1&&count==0){
			fg=a->puan;
		}else if(xas==0){
			if(count==0)
				fg=a->puan;
			else if(count==-1)
				gf=a->puan;
		}
		dosyaYaz<< a->no;
		dosyaYaz<<',';
		dosyaYaz<< a->puan<<endl;
		a=a->next;
	}
	if(xas==0)
		fg=(fg+gf)/(float)2;
	dosyaYaz<<min;
	dosyaYaz<<',';
	dosyaYaz<<max;
	dosyaYaz<<',';
	dosyaYaz<<ortalama;
	dosyaYaz<<',';
	dosyaYaz<<fg;
	dosyaYaz<<',';
	dosyaYaz<<(max-min);
	dosyaYaz<<' '<<endl;
	dosyaYaz.close();

  return 0;
}
