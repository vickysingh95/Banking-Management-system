#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
#include<conio.h>
#include<string>
#include<ctime>
#include<cstring>
using namespace std;
class bank
{
	int acno;
	char name[50];	
	int a,deposit;
	char type;
	
public:
	void intro();
	void date_time();//function to display date and time
	void create_account();	//function to get data from user
	void show_account();
	int store_account();//function to store data on a file
	void show_file();//functio to show data of a file
	void delete_account(int n);//function to delete record in a file
	void modify_account(int n);//function to modify a record in a file
	void deposit_account(int n);//function to deposit an amount
	void withdraw_account(int n);//function to withdrown amount
	void display_sp(int n);//function to display specfic record in a file
};
void bank::intro(){
	cout<<"\n\n\n\n\n\t\t\t\t\t\t************************************************************************";
	cout<<"\n\t\t\t\t\t\t\t\t\tBANK MANAGEMENT SYSTEM";
	cout<<"\n\t\t\t\t\t\t************************************************************************";
	cout<<"\n\n\n\n\n\n\t\t\t\t\t\tMADE BY        :      GROUP MEMBERS";
	cout<<"\n\n\n\n\n\t\t\t\t\t\t\t\t     1. Abhimanyu Kumar";
	
		date_time();
	cout<<"\n\t\t\t\t\t\t\t\t\t\tPRESS ANY KEY TO CONTINUE PROJECT...";
	getch();
}

void bank::date_time(){
	time_t currentime=time(0);
	tm* ltm=localtime(&currentime);
	int year=1900+ltm->tm_year;
	int month=1+ltm->tm_mon;
	int day=ltm->tm_mday;
	cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\tDATE:	"<<day<<"/"<<month<<"/"<<year<<endl;
	int hour=ltm->tm_hour;
	int min=ltm->tm_min;
	int sec=ltm->tm_sec;
	cout<<"\n\tTIME:	"<<hour<<":"<<min<<":"<<sec<<endl;
}

void bank::create_account(){
	cout<<"\n\n\t\t\t\t\t\t\t***************************************************************";
		cout<<"\n\t\t\t\t\t\t\t\t\t\t****APPLICATION FORM****";
		cout<<"\n\t\t\t\t\t\t\t***************************************************************";
		cout<<"\n\t\t\t\t\t\tACCOUNT NUMBER\t\t\t\t:";
		cin>>acno;
		cout<<"\n\t\t\t\t\t\tACCOUNT HOLDER NAME\t\t\t:";
		cin.ignore();// used to ignore or clear one or more characters from the input buffer.
		cin.getline(name,50);
       	cout<<"\n\t\t\t\t\t\tGENDER OF ACCOUNT HOLDER(M/F/T)\t\t:";
    	cin>>type;
    	cout<<"\n\t\t\t\t\t\tNAME OF NOMINEE\t\t\t\t:";
    	cin.ignore();
    	cin.getline(name,50);
    	cout<<"\n\t\t\t\t\t\tGENDER OF NOMINEE(M/F/T)\t\t:";
    	cin>>type;
		cout<<"\n\t\t\t\t\t\tACCOUNT TYPE(C/S)\t\t\t:";
		cin>>type;
		type=toupper(type);
		cout<<"\n\t\t\t\t\t\tOPENING BALANCE\t\t\t\t:";
		cin>>deposit;
		cout<<"\n\n\n\t\t\t\t\t\t\t\t\tCONGRATULATIONS ACCOUNT IS CREATED...\t\t:";
		cout<<"\n\n\n\n\t\t\t\t\t\t\t\t\tPRESS ANY KEY TO CONTINUE...\t\t:";
		getch();
}

void bank::show_account(){
		a=strlen(name);//return the length of given string
		a=37-a;	
		cout<<"\n\n\t\t\t\t\t\t"<<acno<<setw(27)<<name<<setw(a)<<type<<setw(36)<<deposit<<endl;
				}
				
int bank::store_account(){
			ofstream fout;
			fout.open("file2.dat",ios::app|ios::binary);
				create_account();
			fout.write((char*)this,sizeof(*this));
			fout.close();
		}
		
void bank::show_file(){
	 	ifstream fin;
			fin.open("file2.dat",ios::in|ios::binary);
			if(!fin)
			cout<<"\nRecord not found";
			else{
				cout<<"\n\n\t\t\t\t\t\t\t\t****************************************************";
				cout<<"\n\t\t\t\t\t\t\t\t\t***ALL ACCOUNT HOLDER LIST***";
				cout<<"\n\t\t\t\t\t\t\t\t****************************************************";
				cout<<"\n\n\n\n\n\t\t\t\t\t\tACCOUNT NUMBER"<<setw(30)<<"ACCOUNT HOLDER NAME"<<setw(30)<<"ACCOUNT TYPE"<<setw(30)<<"BALANCE";
				cout<<"\n\t\t\t\t\t\t_________________________________________________________________________________________________________";
				fin.read((char*)this,sizeof(*this));
				while(!fin.eof()){
					show_account();
					fin.read((char*)this,sizeof(*this));
				}
				fin.close();
			}
			cout<<"\n\n\n\n\t\t\t\t\t\t\t\t\tPRESS ANY KEY TO CONTINUE...\t\t:";
			getch();
			
}

void bank::delete_account(int n){
	ifstream fin;
	ofstream fout;
	fin.open("file2.dat",ios::in|ios::binary);
	if(!fin){
		cout<<"File could not be open !! Press any Key...";
		return;}
	else{
		fout.open("tempfile.dat",ios::out|ios::binary);
		fin.read((char*)this,sizeof(*this));
		while(!fin.eof()){
			if(acno!=n)
			fout.write((char*)this,sizeof(*this));
			fin.read((char*)this,sizeof(*this));
		}
		fin.close();
		fout.close();
		remove("file2.dat");
		rename("tempfile.dat","file2.dat");
		cout<<"\n\n\tRecord Deleted ..";
	}
}

void bank::modify_account(int n){
	bool flag=false;
	fstream file;
	file.open("file2.dat",ios::in|ios::out|ios::ate|ios::binary);
	file.seekg(0);
	file.read((char*)this,sizeof(*this));
	while(!file.eof()){
		if(acno==n){
			cout<<"\n\n\n\n\n\t\t\t\t\t\tACCOUNT NUMBER"<<setw(30)<<"ACCOUNT HOLDER NAME"<<setw(30)<<"ACCOUNT TYPE"<<setw(30)<<"BALANCE";
	    	cout<<"\n\t\t\t\t\t\t_________________________________________________________________________________________________________";
			show_account();
			create_account();
			int count = (int)file.tellp() - sizeof(*this);
            file.seekp(count);
			file.write((char*)this,sizeof(*this));
			cout<<"\n\n"<<setw(40)<<"RECORD UPDATED";
			flag =true;	
		}
		file.read((char*)this,sizeof(*this));
	}
	file.close();
	if(flag==false)
		cout<<"\n\n"<<setw(40)<<" RECORD NOT FOUND ";
}

void bank::deposit_account(int n){
	int amt;
	bool flag=false;
	fstream file;
	file.open("file2.dat",ios::in|ios::out|ios::ate|ios::binary);
	file.seekg(0);
	if(!file){
	cout<<"File not found";
	return;}
	file.read((char*)this,sizeof(*this));
	while(!file.eof()){
		if(acno==n){
			show_account();
			cout<<"\n\n\tTO DEPOSITE AMOUNT ";
			cout<<"\n\n\tENTER AMOUNT TO DEPOSITE. :";
			cin>>amt;
			deposit+=amt;
			int count = (int)file.tellp() - sizeof(*this);
            file.seekp(count);
			file.write((char*)this,sizeof(*this));
			cout<<"\n\n"<<setw(40)<<"RECORD UPDATED";
			flag=true;
		}
		file.read((char*)this,sizeof(*this));
		
	}
	 file.close();
	if(flag==false)
		cout<<"\n\n"<<setw(40)<<" RECORD NOT FOUND ";
}

void bank::withdraw_account(int n){
int amt;
bool flag=false;
	fstream file;
	file.open("file2.dat",ios::in|ios::out|ios::ate|ios::binary);
	file.seekg(0);
	if(!file){
	cout<<"File not found";
	return;}
	file.read((char*)this,sizeof(*this));
	while(!file.eof()){
		if(acno==n){
			show_account();
			cout<<"\n\n\tTO WITHDRAWN AMOUNT ";
			cout<<"\n\nENTER AMOUNT TO WITHDRAWN. :";
			cin>>amt;
			deposit-=amt;
			int count = (int)file.tellp() - sizeof(*this);
            file.seekp(count);
			file.write((char*)this,sizeof(*this));
			cout<<"\n\n"<<setw(40)<<"RECORD UPDATED";
			flag=true;
		}
		file.read((char*)this,sizeof(*this));
		
	}
	 file.close();	
	 if(flag==false)
	  cout<<"\n\n"<<setw(40)<<" RECORD NOT FOUND ";
}

void bank ::display_sp(int n){
	bool flag=false;
	ifstream infile;
	infile.open("file2.dat",ios::in|ios::binary);
	if(!infile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
		cout<<"\nBALANCE DETAILS\n";
		while(!infile.eof()){
		infile.read((char*)this,sizeof(*this));	
		if(acno==n){
			cout<<"\n\n\n\n\n\n\n\n\t\t\t\t\t\tACCOUNT NUMBER"<<setw(30)<<"ACCOUNT HOLDER NAME"<<setw(30)<<"ACCOUNT TYPE"<<setw(30)<<"BALANCE";
			cout<<"\n\t\t\t\t\t\t_________________________________________________________________________________________________________";
			show_account();
			flag=true;
		}
		}
		infile.close();
	    if(flag==false)
		cout<<"\n\n\t\t\t\t\tACCOUNT NUMBER DOES NOT EXISTS";
}

int main(){
	char ch;
	bank b1;
	int num;
	b1.intro();
		system("cls");
		cout<<"\n\n\t\t\t\t\t\t******************************************************************************";
		cout<<"\n\t\t\t\t\t\t\t\t\t WELCOME TO THE GENERAL BANK";
		cout<<"\n\t\t\t\t\t\t******************************************************************************";
		do{
				system("cls");
		cout<<"\n\n\t\t\t\t\t\t******************************************************************************";
		cout<<"\n\t\t\t\t\t\t\t\t\t WELCOME TO THE GENERAL BANK";
		cout<<"\n\t\t\t\t\t\t******************************************************************************";
			
		cout<<"\n\n\n\n\t\t\t\t\t\t\t\t\t\t*** MAIN MANU ***";
		cout<<"\n\t\t\t\t\t\t\t\t\t\t_________________";
		cout<<"\n\n\n\n\t\t\t\t\t\t01. NEW ACCOUNT\t\t\t\t\t\t\t02. DEPOSIT AMOUNT";
		cout<<"\n\n\n\t\t\t\t\t\t03. WITDRAW AMOUNT\t\t\t\t\t\t04. ALL ACCOUNT HOLDER LIST";;
		cout<<"\n\n\n\t\t\t\t\t\t05. BALANCE ENQUIRY \t\t\t\t\t\t06. CLOSE AN ACCOUNT";
		cout<<"\n\n\n\t\t\t\t\t\t07. MODIFY AN ACCOUNT\t\t\t\t\t\t08. EXIT";
			cout<<"\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\tSelect Your Option (1-8)... :";
			cin>>ch;
				system("cls");
				cout<<"\n\n\t\t\t\t\t\t******************************************************************************";
				cout<<"\n\t\t\t\t\t\t\t\t\t WELCOME TO THE GENERAL BANK";
				cout<<"\n\t\t\t\t\t\t******************************************************************************";
				switch(ch){
					case '1':
						b1.store_account();
						break;
					case '2':
						cout<<"\n\n\t\t\t\tENTER ACCOUNT NUMBER. : ";
					    cin>>num;
						b1.deposit_account(num);
						break;
					case '3':
						cout<<"\n\n\t\t\t\tENTER ACCOUNT NUMBER. : "; 
						cin>>num;
			   			b1.withdraw_account(num);
						break;					
					case '4':
						b1.show_file();
						break;
					case '5':
						cout<<"\n\n\t\t\t\tENTER ACCOUNT NUMBER. : "; 
						cin>>num;
						b1.display_sp(num);
						break;
			        case '6':
			        	cout<<"\n\n\t\t\t\tENTER ACCOUNT NUMBER. : "; 
						cin>>num;
						b1.delete_account(num);
						break;
					case '7':						
						cout<<"\n\n\n\t\t\t\t\t\t\t ENTER ACCOUNT NO TO UPDATE RECORD:";
						cin>>num;
						b1.modify_account(num);
						break;					
					case '8':
					cout<<"\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\tTHANKS FOR USING BANK MANAGEMENT SYSTEM";
					break;
			        	
					default :cout<<"\a";
					}
					cin.ignore();
		            cin.get();
		        	}
    				while(ch!='8');
						return 0;
					}
