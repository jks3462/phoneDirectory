#include<iostream>
#include<fstream>
#include<string.h>
#include<string>
#include<iomanip>
#include<stdio.h>
#include<conio.h>
using namespace std;

class directory{
    char name[20];
    char phone[20];
    char address[50];
    public:
    void getdata()
    {
cout<<"\nEnter name:";
cin>>name;
cout<<"Enter phone no.:";
cin>>phone;
cout<<"Enter address: ";
cin>>address;
}
     void display()
    {
        if(strcmpi(name,""))
        {
  cout << setw(18) << name
            << setw(18) << phone
            << setw(18) << address << endl;
        }
}
    char *getname()
    {
    return name;
    }
    char *getnumber()
    {
    return phone;
    }
     void deletee(){
    strcpy(name,"");
    strcpy(phone,"");
    strcpy(address,"");
    }
    void update(char *n, char *no)
    {
    strcpy(name,n);
    strcpy(phone,no);
    }
    void updatee(char *n,char *pno)
    {
        strcpy (name,n);
        strcpy (address,pno);
    }
};

int compare(char text[], char pattern[]) {
  int c, d, e, text_length, pattern_length, position = -1;

  text_length    = strlen(text);
  pattern_length = strlen(pattern);

  if (pattern_length > text_length) {
    return -1;
  }

  for (c = 0; c <= text_length - pattern_length; c++) {
    position = e = c;

    for (d = 0; d < pattern_length; d++) {
      if (pattern[d] == text[e]) {
        e++;
      }
      else {
        break;
      }
    }
    if (d == pattern_length) {
      return 1;
    }
  }

  return -1;
}


int main(){
directory record;
fstream inoutfile;
inoutfile.open("phone.txt", ios::ate | ios::in | ios::out | ios::binary);
char ch;
char nm[20];
char no[20];
char pno[20];
int choice,found=0;
cout<<"-------------------------DIRECTORY-------------------------";
while(1){
    cout<<"\n\n1.add new record\n";
    cout<<"2.Display all records\n";
    cout<<"3.Search a record \n";
    cout<<"4.Update record\n";
     cout<<"5.Delete a record\n";
    cout<<"6.Exit";
    cout<<"\nEnter your choice:\t";
    cin>>choice;
    if(choice==6)
        break;
   if(choice==5){
     cout<<"Enter name:\t";
    cin>>nm;
    cout<<"Enter contact no:\t";
    cin>>pno;
    inoutfile.seekg(0,ios::beg);
    found=0;
    int l=0;
     while(inoutfile.read((char*)&record,sizeof(record)))
     {
         l++;
         if(strcmpi(nm,record.getname())==0 && strcmpi(pno,record.getnumber())==0)
         {
             found=1;
             break;
         }
     }
     inoutfile.clear();
     if(found==0)
        cout<<"\nRecord not found\n";
     else{
        int p=(l-1)*sizeof(record);
       if(inoutfile.eof())
            inoutfile.clear();
        inoutfile.seekp(p,ios::beg);
        record.deletee();
        inoutfile.write((char*)&record,sizeof(record));
        cout<<"\nRecord deleted ";
     }
        }

    else{
            found=0;
    switch(choice){
case 1:
        record.getdata();
        inoutfile.write((char*)&record,sizeof(record));
        break;

case 2:
    inoutfile.seekg(0,ios::beg);
    cout<<"\n\n*************************Records****************************\n";
    cout << setw(18) << "NAME" << setw(18)<< "CONTACT"<< setw(18) << "ADDRESS\n\n";
    while(inoutfile.read((char*)&record,sizeof(record))){
        if(!inoutfile.eof())
            record.display();
    }
    cout<<"\n************************************************************\n";
    inoutfile.clear();
    break;

case 3:
    {
        int subcase;
        cout << "1. search by name or part of name\n 2. search by phone number or part of phone number\t ";
        cin >> subcase;
        switch(subcase)
        {

        case 1:
    cout<<"\nEnter name/part of name:\t";
    cin>>nm;
    inoutfile.seekg(0,ios::beg);
    found=0;
    while(inoutfile.read((char*)&record,sizeof(record)))
    {
        if(strcmpi(nm,record.getname())==0 || compare(record.getname(),nm)==1)
    {
        found=1;
        record.display();
    }
    }
    inoutfile.clear();
    if(found==0)
        cout<<"\nRecord not found\n";

            break;

case 2:
    cout<<"\nEnter contact no.:\t";
        cin>>no;
        inoutfile.seekg(0,ios::beg);
        found=0;
        while(inoutfile.read((char*)&record,sizeof(record)))
        {
            if(strcmpi(no,record.getnumber())==0 || compare(record.getnumber(),no)==1)
            {
                found=1;
                record.display();
            }
        }
        inoutfile.clear();
        if(found==0)
            cout<<"\nRecord not found\n";
        break;
    }}
    break;
case 4:
    cout<<"Enter name:\t";
    cin>>nm;

    cout<<"Enter previous contact no:\t";
    cin>>pno;
    inoutfile.seekg(0,ios::beg);
    found=0;
    int l=0;
     while(inoutfile.read((char*)&record,sizeof(record)))
     {
         l++;
         if(strcmpi(nm,record.getname())==0 && strcmpi(pno,record.getnumber())==0)
         {
             found=1;
             break;
         }
     }
     inoutfile.clear();
     if(found==0)
        cout<<"\nRecord was not found\n";
     else{
        int p=(l-1)*sizeof(record);
       if(inoutfile.eof())
            inoutfile.clear();
    cout << "what do you want to update? \n 1. contact number \n 2. address\n 3. Both";
    int cho;
    cin >>cho;
    if(cho==1){
        cout<<"Enter new contact no.:\t";
        cin>>no;
        inoutfile.seekp(p,ios::beg);
        record.update(nm,no);
        inoutfile.write((char*)&record,sizeof(record));
    }
     if(cho==2){
        cout<<"Enter new address:\t";
        cin>>pno;
        inoutfile.seekp(p,ios::beg);
        record.updatee(nm,pno);
        inoutfile.write((char*)&record,sizeof(record));
    }
     if(cho==3){
        cout<<"Enter new contact no.:\t";
        cin>>no;
         cout<<"Enter new address:\t";
        cin>>pno;
        inoutfile.seekp(p,ios::beg);
        record.update(nm,no);
        inoutfile.write((char*)&record,sizeof(record));
         inoutfile.seekp(p,ios::beg);
        record.updatee(nm,pno);
        inoutfile.write((char*)&record,sizeof(record));
    }
     }
     break;
    }}
}
inoutfile.close();

return 0;
}
