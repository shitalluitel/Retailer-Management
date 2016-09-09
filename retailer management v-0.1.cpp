#include<iostream>
#include<process.h>
#include<fstream>
#include<conio.h>
#include<string>
#include<ctime>
#include <windows.h>

using namespace std;

char ch;
int x,y,go=0,sn,array_size=0,day,month,year;
char choice1[2],choice[2],choice2[2];
static int flag=0;

typedef struct temp_data{
    string temp_name;
   	int temp_number;
    int check ;
   	int temp_code;
}temp_data;

void loading();
void wait(int);
void set_border();
void display_anime(int);
void set_cursor(int ,int);

class admin{

	private:
		string username;
		string password;

	protected:
		string name_of_file;
		int no_of_data;

	public:
		void get_user_pw();
		int check();
		void get_data(){
            ifstream data_file;
            data_file.open("data.dat");
			if(data_file.is_open()){
                while(!data_file.eof()){
					data_file>>username>>password;
				}
			}
			data_file.close();
		}
		int get_name_of_file();
		void enter_data();
		void add_data();
		int check_new();
};
class user:public admin{

    string item;
    temp_data tem_dat[300];
	int code_of_item,no_of_item;
	double price_of_item,total_price;
	int no_of_list[20],total_item_purched;

	public:
		user(){
			for(int i=0;i<20;i++){
				no_of_list[i]=15*i;
			}
			total_item_purched=total_price=0;
			get_data();
        }
        void delete_record();
		void calculate();
        void check_list();
        int display(int,int);
        void billing(int );
        void update_record();
		void display_update(int);
};

int admin::get_name_of_file(){
	char choice[3];
		set_border();
        x=10;y=2;
	    set_cursor(x,y++);
		cout<<"                             .-'''-.";set_cursor(x,y++);
		cout<<"                            / .===. \\";set_cursor(x,y++);
		cout<<"                            \\/ 6 6 \\/";set_cursor(x,y++);
		cout<<"                            ( \\___/ )";set_cursor(x,y++);
		cout<<"  ____________________ooo____\\_____/____ooo____________________";set_cursor(x,y++);
		cout<<" |                                                             |";set_cursor(x,y++);
		cout<<" |                                                             |";set_cursor(x,y++);
		cout<<" |                                                             |";set_cursor(x,y++);
		cout<<" |                                                             |";set_cursor(x,y++);
		cout<<" |                                                             |";set_cursor(x,y++);
		cout<<" |                                                             |";set_cursor(x,y++);
		cout<<" |                                                             |";set_cursor(x,y++);
		cout<<" |                                                             |";set_cursor(x,y++);
	    cout<<" |                                                             |";set_cursor(x,y++);
		cout<<" |_____________________________________________________________|";set_cursor(x,y++);
		cout<<"                             |__|__|";set_cursor(x,y++);
		cout<<"                             /_'Y'_\\";set_cursor(x,y++);
		cout<<"                            (__/ \\__)";
		x=12;y=8;
		set_cursor(12,y);
		cout<<"                   SELECT THE  SECTION";
		set_cursor(12,++y);
		cout<<"-------------------------------------------------------------";
		set_cursor(x,++y);
		cout<<" 1. Snacks And Foods             2. Fruits And  Vegetables";
		set_cursor(x,++y);
		cout<<" 3. Cosmatics And Beauty         4. Clothes";
		set_cursor(x,++y);
		cout<<" 5. Electrical And Electronics   6. Kitchen Items";
		set_cursor(x,++y);
		cout<<"                     	7. BACK";
		set_cursor(12,++y);
		cout<<"-------------------------------------------------------------";
        set_cursor(x,++y);
		cout<<"                 CHOICE: ";
		cin>>choice;
		switch(choice[0]){
			case '1':
				name_of_file = "snacks.dat";
				break;
			case '2':
				name_of_file = "fruits.dat";
				break;
			case '3':
				name_of_file = "cosmatics.dat";
				break;
			case '4':
				name_of_file = "clothes.dat";
				break;
			case '5':
				name_of_file = "electrical.dat";
				break;
			case '6':
				name_of_file = "kitchen.dat";
				break;
        }
        if(choice[0]== '1' || choice[0]=='2' || choice[0]=='3' || choice[0]=='4' || choice[0]=='5' || choice[0]=='6' ){
			return 1;
        }
		else if( choice[0] == '7'){
			return 0;
		}
		else {
			return get_name_of_file();
		}
}
		
void loading(){
	set_border();
	for(int i=14;i<=64;i++){
        set_cursor(35,11);
        cout<<"LOADING "<<(i-14)*2<<" % ";
        for(int k=14;k<78-i;k++){
            set_cursor(k,12);
            cout<< char(177);
        }
        for(int j=14;j<i;j++){
			set_cursor(j,12);
			cout<< char(219);
        }
        if(( i-14==50)){
			Sleep(500);
        }
		Sleep(25);
	}
}

void wait(int n){
    for(int i=0;i<=n;i++){
		Sleep (1000);
		if( _kbhit()){
			getch();
			set_border();
			return;
	     	}
	}
}

int user::display(int c,int s){
    string code,temp_item,temp_no_of_item,temp_price_of_item;
    set_border();
	x=3,y=2;
	sn=0;


	if(c==0){//to minimize error of displaying same data twice
		if((s-1)<0){
            set_border();
			display_anime(2);
			set_cursor(35,11);
			cout<<"NO DATA TO DISPLAY";
			wait(15);
			int temp;
			temp=display(1,1);
			return temp;
		}
		flag=s;
	}
	else{
		flag=0;
	}


	ifstream output;
	output.open(name_of_file.c_str());
	if(output.is_open()){
	    set_cursor(x,y++);
		cout<<".----.------.--------------------.--------.-------.";
		set_cursor(x,y++);
		cout<<"| SN | ITEM |        ITEM        | No. OF | PRICE |";
		set_cursor(x,y++);
		cout<<"|    | CODE |                    |  ITEM  |(/ITEM)|";
		set_cursor(x,y++);
		cout<<"|----|------|--------------------|--------|-------|";
		set_cursor(x,y);
		cout<<"|    |      |                    |        |       |";
		set_cursor(x,y+1);
		cout<<"'----'------'--------------------'--------'-------'";
   	    while(!output.eof()){
			sn++;
			output>>code>>temp_item>>temp_no_of_item>>temp_price_of_item;
			y++;
			if(y!=6 && sn>no_of_list[s-1] && sn<=no_of_list[s]){
			    set_cursor(x,y-1);
				cout<<"|    ";
				set_cursor(x+2,y-1);
				cout<<sn;
				set_cursor(x+5,y-1);
				cout<<"|      ";
				set_cursor(x+7,y-1);
				cout<<code;
				set_cursor(x+12,y-1);
				cout<<"|                     ";
				set_cursor(x+14,y-1);
	  			cout<<temp_item;
	   			set_cursor(x+33,y-1);
				cout<<"|         ";
				set_cursor(x+35,y-1);
	   			cout<<temp_no_of_item;
				set_cursor(x+42,y-1);
				cout<<"|       |";
				set_cursor(x+44,y-1);
	   			cout<<temp_price_of_item;
				set_cursor(x,y);
	   			cout<<"'----'------'--------------------'--------'-------'";
			}

			if(sn%15==0 && sn!=0 && c==1){
				flag+=1;
			}
		  	if(y==21){
				y=6;
				if(sn==no_of_list[s]){
	                output.close();
					return flag;
				}
			}
	   }
	   if(flag==20 || s<=0){
			flag=-1;
	   }
   	}
   	else{
        set_border();
		display_anime(2);
		set_cursor(35,11);
		cout<<"FILE NOT FOUND";
		wait(15);
		return 0;
   	}
   	output.close();
   	return flag+1;
}

//to display the list
void user::check_list(){
	x=3,y=3;
	int no;
	sn=0;
	go=display(1,1);
	do{
	   	x=56;
		y=7;
		set_cursor(x,y++);
		cout<<"1. MAIN MENU";
		set_cursor(x,y++);
		cout<<"2. SHOW SECTION";
		set_cursor(x,y++);
		cout<<"3. PREVIOUS";
		set_cursor(x,y++);
		cout<<"4. NEXT";
	    set_cursor(x,y++);
		cout<<"5. SELECT";
		set_cursor(x,y++);
		cout<<"6. BILLING";
		set_cursor(x,y++);
		cout<<"7. CANCEL TRANSACTION";
		set_cursor(x-1,y);
		cout<<"                      ";
		set_cursor(x,y++);
		cout<<"CHOICE: ";
		cin>>choice;
		set_cursor(x,y-1);
		cout<<"                     ";
		switch(choice[0]){
			case '1':
				set_border();
				flag=0;
				go=0;
             	if(check()){
					return ;
             	}
             	go=display(1,1);
             	break;
            case '2':
				if(get_name_of_file()){
				}
				go= display(1,1);
                break;
			case '3':
				go=display(0,go-1);
				set_cursor(55,19);
				break;
			case '4':
                go=display(1,go+1);
                set_cursor(55,20);
	            break;
			case '5':
				calculate();
				break;
			case '6':
				billing(1);
   				wait(10);
   				go=display(1,1);
				break;
			case '7':
				billing(2);
				go=display(1,1);
				break;
			default :
				break;
		}
	}while(1);
}

void user::billing(int n){
	int status = 0;
	if(n!=1){
		loading();
		set_border();
        flag=sn=go=total_item_purched=total_price=array_size=0;
        return;
	}
	loading();
	set_border();
    for(int j=0;j<array_size;j++){
        ifstream input;
		input.open(name_of_file.c_str());
		ofstream tempfile;
		tempfile.open("temp.dat");
		while(!input.eof()){
            input>>code_of_item>>item>>no_of_item>>price_of_item;
            if(code_of_item == tem_dat[j].temp_code){
				no_of_item -=tem_dat[j].temp_number;
				if(no_of_item <0){
                	no_of_item +=tem_dat[j].temp_number;
                	total_item_purched -= tem_dat[j].temp_number;
					total_price -= tem_dat[j].temp_number*price_of_item;
                   /* set_border();
                    display_anime(1);
                    system("color 4f");
                	set_cursor(30,11);
                	cout<<"\aINVALID SELECTION MADE";*/
                	status = 1;
                	tem_dat[j].check = 1;
				}
            }
            tempfile<<"\n"<<code_of_item<<" "<<item<<" "<<no_of_item<<" "<<price_of_item;
		}
		input.close();
		tempfile.close();
		ifstream input1;
		input1.open("temp.dat");
		ofstream tempfile1;
		tempfile1.open(name_of_file.c_str());
		while(!input1.eof()){
			input1>>code_of_item>>item>>no_of_item>>price_of_item;
			tempfile1<<"\n"<<code_of_item<<" "<<item<<" "<<no_of_item<<" "<<price_of_item;
		}
		tempfile1.close();
		input1.close();
	}
	Sleep(500);
	set_border();
	set_cursor(5,3);
	cout<<"Total number of items Purched: "<<total_item_purched;
	set_cursor(5,4);
	cout<<"Total cost:                   "<<total_price;
	set_cursor(5,5);
	cout<<"List of items are: ";
	x=5;y=5;
	int sn=0;
	for(int i=0;i<array_size;i++){
		if(tem_dat[i].check != 1){
            set_cursor(x,++y);
			cout<<++sn<<". "<<tem_dat[i].temp_name;
		}
		if(y==22){
			x=x+22;
			y==5;
		}
		if(x==49 && y==22){
			x=y=5;
		}
	}
	if(status == 1){
        wait(30);
        set_border();
        display_anime(1);
        system("color 4f");
    	set_cursor(30,11);
    	cout<<"\aINVALID SELECTION MADE";
    	wait(2);
		sn=0;
		set_border();
		set_cursor(5,5);
		cout<<"List of Invalid items are: ";
		x=5;y=5;
		for(int i=0;i<array_size;i++){
			if(tem_dat[i].check == 1){
	            set_cursor(x,++y);
				cout<<++sn<<". "<<tem_dat[i].temp_name;
			}
			if(y==22){
				x=x+22;
				y==5;
			}
			if(x==49 && y==22){
				x=y=5;
			}
		}
	}
	remove("temp.dat");
	flag=sn=go=total_item_purched=total_price=array_size=0;
}

void user::calculate(){
    x=55;
	y=14;
	int temp;
	int no,f=0;
    set_cursor(x,y);
	cout<<"ITEM CODE: ";
	cin>>temp;
	set_cursor(x,y);
	cout<<"                    ";
	set_cursor(x,y);
	cout<<"NUMBER OF ITEM: ";
	cin>>no;
	set_cursor(x,y);
	cout<<"                    ";
 	ifstream input;
	input.open(name_of_file.c_str());
	while(!input.eof()){
		input>>code_of_item>>item>>no_of_item>>price_of_item;
		if(code_of_item == temp){
			tem_dat[array_size].temp_name=item;
			tem_dat[array_size].temp_number=no;
			tem_dat[array_size].temp_code=code_of_item;
			tem_dat[array_size].check = 0;
			array_size++;
			f=1;
			total_item_purched += no;
			total_price += no*price_of_item;
		}
	}
	if(f==0){
		set_border();
		system("color 4f");
		display_anime(1);
		set_cursor(30,11);
		cout<<"\aINVALID ITEM CODE";
		wait(5);
		set_border();

	}
	input.close();
}
void admin::get_user_pw(){
	display_anime(2);
	set_cursor(17,8);
	cout<<"           SET YOUR USERNAME AND PASSWORD          ";
	set_cursor(17,9);
	cout<<"---------------------------------------------------";
	set_cursor(38,11);
	cout<<"USERNAME: ";
	cin>>username;
	set_cursor(38,13);
	cout<<"PASSWORD: ";
	cin>>password;
	ofstream output;
	output.open("data.dat");
	output<<username<<"\n"<<password<<"\n";
	output.close();
}
void display_anime(int n){
    x=15;y=2;
    set_cursor(x,y++);
	cout<<"                        .-'''-.";set_cursor(x,y++);
	cout<<"                       / .===. \\";set_cursor(x,y++);
	cout<<"                       \\/ 6 6 \\/";set_cursor(x,y++);
	if(n==1){
    cout<<"                       (   o   )";set_cursor(x,y++);
	}
	else{
	cout<<"                       ( \\___/ )";set_cursor(x,y++);
	}
	cout<<"  _______________ooo____\\_____/____ooo_______________";set_cursor(x,y++);
	cout<<" |                                                   |";set_cursor(x,y++);
	cout<<" |                                                   |";set_cursor(x,y++);
	cout<<" |                                                   |";set_cursor(x,y++);
	cout<<" |                                                   |";set_cursor(x,y++);
	cout<<" |                                                   |";set_cursor(x,y++);
	cout<<" |                                                   |";set_cursor(x,y++);
	cout<<" |                                                   |";set_cursor(x,y++);
	cout<<" |                                                   |";set_cursor(x,y++);
    cout<<" |                                                   |";set_cursor(x,y++);
	cout<<" |___________________________________________________|";set_cursor(x,y++);
	cout<<"                        |__|__|";set_cursor(x,y++);
	cout<<"                        /_'Y'_\\";set_cursor(x,y++);
	cout<<"                       (__/ \\__)";
}
int admin:: check(){
    string temp_user,temp_pass;
    display_anime(2);
    set_cursor(17,8);
	cout<<"                 USERNAME AND PASSWORD";
	set_cursor(17,9);
	cout<<"---------------------------------------------------";
	set_cursor(32,11);
	cout<<"USERNAME: ";
	cin>>temp_user;
	set_cursor(32,13);
	cout<<"PASSWORD: ";
	cin>>temp_pass;
	if(temp_user==username && temp_pass==password){
		return 1;
	}
	set_border();
	display_anime(1);
	system("color 4f");
	set_cursor(34,11);
	cout<<"INCORRECT PASSWORD\a";
	wait(20);
	system("color 2f");
	return 0;
}
void admin:: enter_data(){
	ofstream input;
    input.open(name_of_file.c_str());
    string code,item, no_of_item, price_of_item;
	int x=3,y=3,sn=0,no_of_data,i=0;
	set_border();
	set_cursor(7,12);
	cout<<"Enter the number of data that you want to insert:";
	cin>>no_of_data;
	set_border();
	set_cursor(x,y++);
	cout<<".----.------.--------------------.--------.-------.";
	set_cursor(x,y++);
	cout<<"| SN | ITEM |        ITEM        | No. OF | PRICE |";
	set_cursor(x,y++);
	cout<<"|    | CODE |                    |  ITEM  |(/ITEM)|";
	set_cursor(x,y++);
	cout<<"|----|------|--------------------|--------|-------|";
	while(i<no_of_data){
		x=3;
        if(y<22){
			set_cursor(x,y);
			cout<<"|    |      |                    |        |       |";
			set_cursor(x,y+1);
			cout<<"'----'------'--------------------'--------'-------'";
		}
		set_cursor(x,y);
		cout<<"| "<<++sn;
		set_cursor(x += 5,y);
		cout<<"| ";
		cin>>code;
		set_cursor(x += 7,y);
		cout<<"| ";
		cin>>item;
		set_cursor(x += 21,y);
		cout<<"| ";
		cin>>no_of_item;
		set_cursor(x += 11,y);
		cin>>price_of_item;
		input<<"\n"<<code<<" "<<item<<" "<<no_of_item<<" "<<price_of_item;
		y++;
		i++;
		if(y==22){
			y=3;
			set_border();
			set_cursor(x,y++);
			cout<<".----.------.--------------------.--------.-------.";
			set_cursor(x,y++);
			cout<<"| SN | ITEM |        ITEM        | No. OF | PRICE |";
			set_cursor(x,y++);
			cout<<"|    | CODE |                    |  ITEM  |(/ITEM)|";
			set_cursor(x,y++);
			cout<<"|----|------|--------------------|--------|-------|";
		}
	}
	input.close();
}
void admin:: add_data(){
	fstream input(name_of_file.c_str(), fstream::in | fstream::out | fstream::app );
    string code,item,no_of_item,price_of_item;
	int x=3,y=3,sn=0,no_of_data,i=0;
	set_border();
	set_cursor(7,12);
	cout<<"Enter the number of data that you want to insert:";
	cin>>no_of_data;
	set_border();
	set_cursor(x,y++);
	cout<<".----.------.--------------------.--------.-------.";
	set_cursor(x,y++);
	cout<<"| SN | ITEM |        ITEM        | No. OF | PRICE |";
	set_cursor(x,y++);
	cout<<"|    | CODE |                    |  ITEM  |(/ITEM)|";
	set_cursor(x,y++);
	cout<<"|----|------|--------------------|--------|-------|";
	while(i<no_of_data){
		x=3;
		set_cursor(x,y);
		cout<<"|    |      |                    |        |       |";
		set_cursor(x,y+1);
		cout<<"'----'------'--------------------'--------'-------'";
		set_cursor(x,y);
		cout<<"| "<<++sn;
		set_cursor(x += 5,y);
		cout<<"| ";
		cin>>code;
		set_cursor(x += 7,y);
		cout<<"| ";
		cin>>item;
		set_cursor(x += 21,y);
		cout<<"| ";
		cin>>no_of_item;
		set_cursor(x += 11,y);
		cin>>price_of_item;
		input<<"\n"<<code<<" "<<item<<" "<<no_of_item<<" "<<price_of_item;
		y++;
		i++;
		if(y==22){
			y=3;
			set_border();
			set_cursor(x,y++);
			cout<<".----.------.--------------------.--------.-------.";
			set_cursor(x,y++);
			cout<<"| SN | ITEM |        ITEM        | No. OF | PRICE |";
			set_cursor(x,y++);
			cout<<"|    | CODE |                    |  ITEM  |(/ITEM)|";
			set_cursor(x,y++);
			cout<<"|----|------|--------------------|--------|-------|";
		}
	}
	input.close();
}
void user::display_update(int n){
    x=3,y=3;
	int no;
	sn=0;
	go=display(1,go+1);
	do{
	   	x=55;
		y=7;
		set_cursor(x,y++);
		cout<<"1. BACK                ";
		set_cursor(x,y++);
		cout<<"2. PREVIOUS            ";
		set_cursor(x,y++);
		cout<<"3. NEXT                ";
	    if(n==1){
            set_cursor(x,y++);
			cout<<"4. UPDATE              ";
	    }
	    else{
            set_cursor(x,y++);
			cout<<"4. DELETE              ";
	    }
		set_cursor(x,y);
		cout<<"                       ";
		set_cursor(x,y++);
		cout<<"CHOICE: ";
		cin>>choice;
		set_cursor(x,y-1);
		cout<<"                       ";
		switch(choice[0]){
			case '1':
				set_border();
			    flag=0;
			    go=0;
             	return;
			case '2':
				go=display(0,go-1);
				break;
			case '3':
                go=display(1,go+1);
	            break;
			case '4':
				if(n==1){
                    update_record();

				}
				else{
					delete_record();
				}
				set_border();
				go=display(1,1);
				break;
			default :
				break;
		}
	}while(1);

}
void user:: update_record(){
	int flag=1;
	string temp_item, temp_no_of_item,temp_price_of_item;
	int code;
	ifstream input;
	input.open(name_of_file.c_str());
	ofstream output;
	output.open("temp.dat");
	x=55;
	y=7;
	set_cursor(x,y++);
	cout<<"             ";
	set_cursor(x,y++);
	cout<<"              ";
	set_cursor(x,y++);
	cout<<"               ";
	set_cursor(x,y++);
	cout<<"             ";
	set_cursor(x,y);
	cout<<"             ";
	set_cursor(x,y++);
	cout<<"             ";
	set_cursor(x,y-1);
	cout<<"             ";
	y=7;
	set_cursor(x,y++);
	cout<<"ITEM CODE: ";
	cin>>code;
	y=7;
    set_cursor(x,y++);
    cout<<"                   ";
	while(!input.eof()){
		input>>code_of_item>>item>>no_of_item>>price_of_item;
		if(code == code_of_item ){
            y=7;
			flag=1;
			set_cursor(x,y++);
			cout<<"NEW CODE: ";
			cin>>code_of_item;
            set_cursor(x,y++);
			cout<<"ITEM: ";
			cin>>temp_item;
            set_cursor(x,y++);
			cout<<"QUANTITY: ";
			cin>>temp_no_of_item;
			set_cursor(x,y++);
			cout<<"PRICE: ";
			cin>>temp_price_of_item;
			output<<"\n"<<code_of_item<<" "<<temp_item<<" "<<temp_no_of_item<<" "<<temp_price_of_item;
			continue;
		}
		output<<"\n"<<code_of_item<<" "<<item<<" "<<no_of_item<<" "<<price_of_item;
	}
	input.close();
	output.close();
	ifstream input1;
	input1.open("temp.dat");
	ofstream tempfile1;
	tempfile1.open(name_of_file.c_str());
	while(!input1.eof()){
		input1>>code_of_item>>item>>no_of_item>>price_of_item;
		tempfile1<<"\n"<<code_of_item<<" "<<item<<" "<<no_of_item<<" "<<price_of_item;
	}
	tempfile1.close();
	input1.close();
	remove("temp.dat");
}
void user:: delete_record(){
	int flag=1;
	string temp_item, temp_no_of_item,temp_price_of_item;
	int code;
	ifstream input;
	input.open(name_of_file.c_str());
	ofstream output;
	output.open("temp.dat");
	x=55;
	y=7;
	set_cursor(x,y++);
	cout<<"             ";
	set_cursor(x,y++);
	cout<<"              ";
	set_cursor(x,y++);
	cout<<"               ";
	set_cursor(x,y++);
	cout<<"             ";
	set_cursor(x,y);
	cout<<"             ";
	set_cursor(x,y++);
	cout<<"             ";
	set_cursor(x,y-1);
	cout<<"             ";
	y=7;
	set_cursor(x,y++);
	cout<<"ITEM CODE: ";
	cin>>code;
	y=7;
    set_cursor(x,y++);
    cout<<"                   ";
	while(!input.eof()){
		input>>code_of_item>>item>>no_of_item>>price_of_item;
		if(code == code_of_item ){
            continue;
		}
		output<<"\n"<<code_of_item<<" "<<item<<" "<<no_of_item<<" "<<price_of_item;
	}
	input.close();
	output.close();
	ifstream input1;
	input1.open("temp.dat");
	ofstream tempfile1;
	tempfile1.open(name_of_file.c_str());
	while(!input1.eof()){
		input1>>code_of_item>>item>>no_of_item>>price_of_item;
		tempfile1<<"\n"<<code_of_item<<" "<<item<<" "<<no_of_item<<" "<<price_of_item;
	}
	tempfile1.close();
	input1.close();
	remove("temp.dat");
}
inline void set_cursor(int x_coordinate, int y_coordinate){
	HANDLE hout;
	COORD coord;
	coord.X=x_coordinate;
	coord.Y=y_coordinate;
	hout= GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hout, coord);
}
void set_today(){
    time_t t = time(0);   // get time now
	struct tm * now = localtime( & t );
	year= (now->tm_year + 1900) ;
	month= (now->tm_mon + 1) ;
	day=now->tm_mday;
	set_cursor(10,24);
	printf("  PRESENTED BY: SHITAL BABU LUITEL ");
    set_cursor(55,24);
	cout<<"DATE: "<<year<<"-"<<month<<"-"<<day;
}
inline void set_border(){
	system("color 3f");
    Sleep(300);
	system("cls");
    HANDLE hout;
	COORD coord;
	hout= GetStdHandle(STD_OUTPUT_HANDLE);//screen status
    SetConsoleCursorPosition(hout, coord);//coursour positioning
		for(int i=0;i<=79;i++){
			if(i==1 || i== 78){
				for(int j=0;j<24;j++){
    				coord.X=i;
					coord.Y=j;
    				SetConsoleCursorPosition(hout, coord);//to select position pf cursor
					cout<<char(219);//to assign '*' where the cursor is denoting
				}
			}
            coord.X=i;
	     	coord.Y=0;
			SetConsoleCursorPosition(hout, coord);
			cout<< char(219);
		}
		for(int i=0;i<=79;i++){
			if(i==0 || i== 79){
				for(int j=1;j<24;j++){
					coord.X=i;
					coord.Y=j;
					SetConsoleCursorPosition(hout, coord);
					cout<<char(219);
				}
			}
            coord.X=i;
    		SetConsoleCursorPosition(hout, coord);
			cout<<char(219);
		}
  		set_today();
}
int admin::check_new(){
    ifstream record;
	record.open("data.dat");
	if(!record.is_open()){
		record.close();
		return 1;
	}
	else{
		record.close();
		return 0;
	}
}

int main(){
    system("color 3f");
    user obj;
    int a;
	if(obj.admin::check_new()){
        set_border();
        set_cursor(0,24);
		cout<<"                                                    ";
        y=5;
		set_cursor(26,y++);
		cout<<"*****************************";
		set_cursor(26,y++);
		cout<<"*         WELCOME TO        *";
		set_cursor(26,y++);
		cout<<"*    RETAILER MANAGEMENT    *";
		set_cursor(26,y++);
		cout<<"*****************************";
		y++;
		set_cursor(25,++y);
		cout<<"*******************************";
		set_cursor(25,++y);
		cout<<"*        PRESENTED BY:        *";
		set_cursor(25,++y);
		cout<<"*      SHITAL BABU LUITEL     *";
		set_cursor(25,++y);
		cout<<"*     BIRAT KSHITIZ COLLEGE   *";
		set_cursor(25,++y);
		cout<<"*******************************";
		wait(20);
		set_border();
		obj.admin::get_user_pw();//to detect users 1st use of application
	}
	loading();
	do{
		set_border();
		display_anime(2);
		y=8;
		set_cursor(17,y);
		cout<<"                    MAIN MENU";
		set_cursor(17,++y);
		cout<<"---------------------------------------------------";
        set_cursor(18,++y);
		cout<<"              1. ADD, DELETE AND UPDATE";
		set_cursor(18,++y);
		cout<<"              2. VIEW AND BUY ";
		set_cursor(18,++y);
		cout<<"              3. CHANGE PASSWORD";
		set_cursor(18,++y);
		cout<<"              4. EXIT";
		set_cursor(17,++y);
		cout<<"---------------------------------------------------";
		set_cursor(25,++y);;
		cout<<"CHOICE: ";
		cin>>choice;
		set_border();
		switch(choice[0]){
			case '1':
				if(obj.admin::check()){
     				if(obj.admin::get_name_of_file()){
                        do{
							system("color 3f");
		     				set_border();
		     				display_anime(2);
							x=18;y=8;
							set_cursor(17,y);
							cout<<"                   ADMINISTRATION: ";
							set_cursor(17,++y);
							cout<<"---------------------------------------------------";
							set_cursor(x,++y);
							cout<<"    1. TO ENTER RECORD";
							set_cursor(x,++y);
							cout<<"    2. TO UPDATE RECORD";
							set_cursor(x,++y);
							cout<<"    3. TO DELETE RECORD";
							set_cursor(x,++y);
							cout<<"    4. SELECT SECTION         5. BACK";
							set_cursor(17,++y);
							cout<<"---------------------------------------------------";
		                    set_cursor(x,++y);
							cout<<"                 CHOICE: ";
							cin>>choice1;
							set_border();
							switch(choice1[0]){
								case '1':
		                                do{
	                                        system("color 3f");
	                                        set_border();
			                                display_anime(2);
											x=18;y=8;
											set_cursor(17,y);
											cout<<"                   ADMINISTRATION: ";
											set_cursor(17,++y);
											cout<<"---------------------------------------------------";
											set_cursor(x,++y);
											cout<<"             1. TO ADD IN EXISTING FILE.";
											set_cursor(x,++y);
											cout<<"             2. TO ENTER NEW RECORD.";
											set_cursor(x,++y);
											cout<<"             3. BACK";
											y++;
											set_cursor(17,++y);
											cout<<"---------------------------------------------------";
											set_cursor(x,++y);
											cout<<"             CHOICE: ";
											cin>>choice2;
											set_border();
											switch(choice2[0]){
												case '1':
													system("color 1f");
				                                    obj.admin::add_data();
				                                    loading();
				                                    set_border();
				                                    break;
												case '2':
													system("color f1");
				                                    obj.admin::enter_data();
													loading();
													set_border();
													break;
												default:
													break;
											}
		                                }while(choice2[0]!='3');
										system("color 3f");
										break;
								case '2':
									obj.display_update(1);
									loading();
	                                set_cursor(35,14);
				                    cout<<"RECORD UPDATED";
				                    wait(2);
									break;
								case '3':
	                                obj.display_update(0);
									loading();
									set_cursor(34,14);
				                    cout<<"RECORD DELETED";
				                    wait(2);
									break;
								case '4':
									if(obj.admin::get_name_of_file()){
										a=0;
									}
									break;
							}
						}while(choice1[0]!='5');
     				}
				}
    			break;
			case '2':
				if(obj.admin::get_name_of_file()){
                    obj.check_list();
				}
				break;
			case '3':
				if(obj.admin::check()){
					obj.admin::get_user_pw();
				}
				break;
            case '4':
				set_border();
				display_anime(2);
				set_cursor(38,11);
				cout<<"THANK YOU";
				wait(15);
				return 0;
			default :
				break;
		}
	}while(1);
}
