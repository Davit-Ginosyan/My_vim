#include <iostream>
#include <string>
#include <vector>
using namespace std;

string get_comand(string);
string get_name(string);

class Root
{
  public: 
         string name;
         bool is_dir;
         vector <Root*> ptr;

         Root(string,bool);
         
 
};

int main() 
{
  string str,com,name;
  Root* head;
  vector <Root*> point;
  Root root("root",true);
  head = &root;
  
  int current = 0;

  while(str != "end")
   {
    getline(cin,str);
    com = get_comand(str);
    name = get_name(str);

    if(com == "mkdir")
    {  
       head->ptr.push_back(new Root(get_name(str),true));
    }

    if(com == "touch")
    {
      head->ptr.push_back(new Root(get_name(str),false));
    }

    if(com == "cd")
    {
      if(get_name(str) == "..")
      {
        head = point[current-1];
        --current;
      }
      else if(get_name(str) != "..")
      {
        for(int i = 0; i <= head->ptr.size(); ++i)
       {
        if(get_name(str) == head->ptr[i]->name)
         {
           if(head->ptr[i]->is_dir == true)
           {
             point.push_back(new Root(name,true));
             point[current] = head;
             ++current;
             head = head->ptr[i];
           }
           else if(head->ptr[i]->is_dir == false)
           {
             cout << "ERROR:This is a file. Print in: " << head->name <<".folder"<<endl;
           }
         }
       }
      }
    }

    if(com == "ls")
    {
      for(int i = 0; i < head->ptr.size(); ++i)
      {
        cout << head->ptr[i]->name <<'\t'; 
      }
      cout<< endl;
    }

    if(com == "rm")
    {
      for(int i = 0; i < head->ptr.size(); ++i)
      {
        if(get_name(str) == head->ptr[i]->name)
        {
          if(head->ptr[i]->is_dir == false)
          {
            delete head->ptr[i];
            head->ptr.pop_back();
          }
          else
          {
            cout  <<" ERROR:this is a folder. To delete a folder use the command: rmdir"<<endl;
          }
        }
      }
    }

    if(com == "rmdir")
    {
      for(int i = 0; i < head->ptr.size(); ++i)
      {
        if(get_name(str) == head->ptr[i]->name)
        {
          if(head->ptr[i]->is_dir == true)
          {
            delete head->ptr[i];
            head->ptr.pop_back();
          }
          else
          {
            cout  <<" ERROR:this is a file. To delete a file use the command: rm"<<endl;
          }
        }
      }
    }

    if(com == "pwd")
    {
      for(int i = 0;i < current; ++i)
      {
        cout << point[i]->name << " >> " ;
      }
      cout << head->name << endl;
    }
  }
}

string get_comand(string str)
{
  int i = 0;
  string tmp;
  while( str[i] != ' ' && str[i] != '\0')
  {
    tmp.push_back(str[i]);
    ++i;
  }
  return tmp;
}

string get_name(string str)
{

  string tmp;
  for( int i = 0 ; i <= sizeof(str);++i)
  {
   if( str[i] == ' ')
   {
     ++i;
     while(str[i] != ' ' && str[i] != '\0')
     {
       tmp.push_back(str[i]);
       ++i;
     }
   }
  }
  return tmp;
} 
Root::Root(string str,bool is_dir )
{
   this->name = str;
   this->is_dir = is_dir;
}

