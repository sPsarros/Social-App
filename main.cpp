#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;
static int IDnum=1;

//Structure for user
struct user{
    string username;
    string password;
    struct photo *list;
};

//Structure for photos
struct photo{
    int id;
    string desc;
    string filename;
    string location;
    string date;
    struct tag *tagged;
    struct photo *next;
    struct photo *prev;
};

//Structure for tags in photos
struct tag{
    string username;
    struct tag *next;
};

struct user* authentication(struct user *p,int size, const string name,const string pass);
bool menu(struct user *list,struct user *p,int size);
void load(struct user *p,int size);
void uploadPic(struct user *p);
void tagUser(struct user *list,struct user *p,int size);
string getTime();
void detail(struct user *p);
void removeTag(struct user *p);
void removePhoto(struct user *p);


int main(void){
    const int size=2;
    struct user *userlist = new struct user[size];
    load(userlist,size);
   
   
    string name,pass;
    cout<<"username: ";
    cin>>name;
    cout<<"password: ";
    cin>>pass;
    
    //returns null if user has not an account
    struct user *logIn = authentication(userlist,size,name,pass);
    
    if(logIn != nullptr) 
        while(menu(userlist,logIn,size));//In loop until user enters 6

    delete[] userlist;
    return 0;
}


//Turn time-date into string
string getTime(){
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];

    time (&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer,sizeof(buffer),"%d-%m-%Y %H:%M:%S",timeinfo);
    string str(buffer);

    return str;
}

//Menu of the user
bool menu(struct user *list,struct user *p,int size){
    cout<<"---------MENU---------"<<endl;
    cout<<"1) Upload a photo"<<endl;
    cout<<"2) Delete a photo"<<endl;
    cout<<"3) View details of a photo"<<endl;
    cout<<"4) Tag a user in a photo"<<endl;
    cout<<"5) Remove tagged user from a photo"<<endl;
    cout<<"6) Log out"<<endl;

    int choice;
    POINT:
    cout<<"Enter a choice: ";
    cin>>choice;
        switch(choice){
                case 1:
                    uploadPic(p);
                    break;
                case 2:
                    removePhoto(p);
                    break;
                case 3:
                    detail(p);
                    break;
                case 4: 
                    tagUser(list,p,size);
                    break;
                case 5:
                    removeTag(p);
                    break;
                case 6:
                    cout<<"Logging out..."<<endl;
                    return false;
                default:
                    cout<<"Something went wrong..."<<endl;
                    goto POINT;
            }
    }

//Using const so the parameters can not be modified
struct user* authentication(struct user *p,int size, const string name,const string pass){
    for(int i=0;i<size;i++){
        //Checks if the user is valid
        if(p[i].username == name && p[i].password==pass){
            cout<<"Welcome back "<<name<<endl;
            return &p[i];
        }
    }

    cout<<"User not found!"<<endl;
    return nullptr;
}

//Function to load users from given file
void load(struct user *p, int size){
    int count=0;
    string name,pass;
    
    //Open file
    ifstream file("users.txt");
    if(!file.is_open()){
        cout<<"Error while opening the file, please try again!\n";
        return;
    } 

    //Copying characters until reeds space
    while(getline(file,name,' ') && getline(file,pass)){
        if(count>size) break;
        
        p[count].username=name;
        p[count].password=pass;
        p[count].list=nullptr;
        count++;

    }

    file.close();

}

//Funtion used for uploading photos
void uploadPic(struct user *p){
    
    struct photo *pic = new struct photo;
    string line;
   
    //Initialize each 
    pic->id=IDnum++;
    cout<<"Description: ";
    cin.ignore();
    getline(cin,line);
    pic->desc=line;
    cout<<"File name: ";
    getline(cin,line);
    pic->filename=line;
    cout<<"Location: ";
    getline(cin,line);
    pic->location=line;
    pic->date=getTime();
    pic->tagged=nullptr;
    pic->next=nullptr;
    pic->prev=nullptr;

    //Photo list is empty
    if(p->list==nullptr){
        p->list=pic;
    }else{
        struct photo *temp=p->list;
        
        //Search for the last photo in the list
        while(temp->next!=nullptr)
            temp=temp->next;
        
        temp->next=pic;
        pic->prev=temp;
    }

}
 

void tagUser(struct user *list,struct user *p,int size){
    //If photo list exists
    if(p->list==nullptr){
        cout<<"There are no uploaded photos"<<endl;
        return;
    }

    int id;
    cout<<"Enter photo's id: ";
    cin>>id;

    struct photo *pic=p->list;

    //if the photo id is correct
    while(pic!=nullptr && pic->id!=id)
        pic=pic->next;

    if(pic==nullptr){
        cout<<"Wrong id..."<<endl;
        return;
    }

    string name;
    cout<<"Enter tag: ";
    cin>>name;

    //Check if the username of the tag is valid
    bool flag=false;
    for(int i=0;i<size;i++){
        if(list[i].username==name)
            flag=true;
    }
    
    //There is no such username 
    if(!flag){
        cout<<name<<" does not exist"<<endl;    
        return;
    }
    
    //Username was found
    struct tag *newTag = new struct tag;
    newTag->username = name;
    newTag->next=nullptr;

    struct tag *temp=pic->tagged;

    if(temp==nullptr){
        pic->tagged=newTag;
        cout<<newTag->username<<" has been successfully tagged"<<endl;
    }else{
        while(temp!=nullptr){
            //If user has been already tagged
            if(temp->username==newTag->username) {
                cout<<temp->username<<" is already tagged"<<endl;
                delete newTag;
                return;
            }
            
            //Reached the last node in photo list 
            if(temp->next==nullptr) 
                break;

            temp=temp->next;
        }

        temp->next=newTag;
        cout<<newTag->username<<" has been successfully tagged"<<endl;
    }


}


//Details of a photo
void detail(struct user *p){
    //There is no photo to view
    if(p->list==nullptr){
        cout<<"There are no photos!"<<endl;
        return;
    }
    
    int id;
    cout<<"Enter photo's id: ";
    cin>>id;

    struct photo *temp=p->list;

    //Searching for the photo with the given id 
    while(temp!=nullptr && temp->id!=id){
        temp=temp->next;
    }

    if(temp==nullptr){
        cout<<"Wrong id!!!"<<endl;
        return;
    }

    if(temp->id==id){
        cout<<"-----------------------"<<endl;
        cout<<"Details of the photo: "<<endl;
        cout<<"ID: "<<temp->id<<endl;
        cout<<"Description: "<<temp->desc<<endl;
        cout<<"Location: "<<temp->location<<endl;
        cout<<"Time and Date: "<<temp->date<<endl;
        cout<<"Tagged users: ";

        //Printing tagged users
        struct tag *x=temp->tagged;
        if(x==nullptr){
            cout<<"-"<<endl;
            cout<<"-----------------------"<<endl;
            return;
        }

        while(x!=nullptr) {
            cout<<x->username<<" ";
            x=x->next;
        }

        cout<<endl<<"-----------------------"<<endl;
    }
}


//Remove a tag
void removeTag(struct user *p){
    if(p->list==nullptr){
        cout<<"There are no photos"<<endl;
        return;
    }

    int id;
    cout<<"Please enter id of the photo: ";
    cin>>id;

    struct photo *pic=p->list;

    //Searching for the photo
    while(pic!=nullptr && pic->id!=id){
        pic->next;
    }

    if(pic==nullptr){
        cout<<"Wrong id, try again"<<endl;
        return;
    }

    //Temporary tag node pointer
    struct tag *current=pic->tagged;

    if(current==nullptr){
        cout<<"No user is tagged"<<endl;
        return;
    }

    string name;
    cout<<"Enter name: ";
    cin>>name;

    //Search and remove the tag
    if(current->username==name){
        pic->tagged=current->next;
        delete current;
       
    }else{
        //Second temporary pointer to simplify the removal
        struct tag *temp=current->next;
        while(temp!=nullptr && temp->username!=name){
            temp=temp->next;
            current=current->next;
        }

        //search if the tag exists
        if(temp==nullptr){
            cout<<name<<" isn't tagged"<<endl;
            return;
        }

        current->next=temp->next;
        delete temp;
        
    }
    cout<<name<<" has been removed"<<endl;

}


void removePhoto(struct user *p){
    //If photos have been created
    if(p->list==nullptr){
        cout<<"There are no photos"<<endl;
        return;
    }

    int id;
    cout<<"Enter photo's id: ";
    cin>>id;
    
    //Temporary pointer to simplify the removal
    struct photo *pic = p->list;

    //Find the given photo
    while(pic!=nullptr && pic->id!=id){
        pic=pic->next;
    }

    if(pic==nullptr){
        cout<<"Wrong photo id!"<<endl;
        return;
    }

    //If tags exist in a photo
    if(pic->tagged!=nullptr){
        
        struct tag *x=pic->tagged;

        //remove tags
        while(pic->tagged!=nullptr){
            pic->tagged=pic->tagged->next;
            delete x;
            x=pic->tagged;
        }
    }

    if(pic->next==nullptr){
        pic->prev=nullptr;
        delete pic;
    }else{
        struct photo *prevPic=pic->prev;
        struct photo *nextPic=pic->next;

        prevPic->next=nextPic;
        nextPic->prev=prevPic;
        delete pic;
    }

    cout<<"Photo "<<id<<" has been deleted"<<endl;
}