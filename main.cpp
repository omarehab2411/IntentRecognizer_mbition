#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <bits/stdc++.h>

class IntentRecognizer
{

public:
  IntentRecognizer()
   {

    for(auto word:WeatherWords)
    {
       WordMap[word] ="weather";
    }

   for(auto word:CityWords)
    {
       WordMap[word] ="city";
    }

    for(auto word:FactWords)
    {
       WordMap[word] ="fact";
    }

   }

std::string IntentRecognizer_GetIntent(std::string phrase)
{
  return (IntentRecognizer_FormIntent( IntentRecognizer_ClassifyIntent(phrase) ) );
}

private :

 std::unordered_map<std::string,bool> classified;
 std::map<std::string,std::string> WordMap;

 std::vector<std::string> WeatherWords ={"weather","rain","rainy","sunny","windy","cold","hot","warm","snow","snowy"};
 std::vector<std::string> CityWords    ={"Paris","Cairo","Tokyo","London","Berlin","city"};
 std::vector<std::string> FactWords    ={"fact"};

 bool IntentRecognizer_ClassifyIntent(std::string phrase)
 {
  bool LocalReturn = false;
  std::stringstream StrStream(phrase);
  std::string Word;

   while (StrStream >> Word)
    {
        if((Word[Word.length()-1]>='a'&&Word[Word.length()-1]<='z') || (Word[Word.length()-1]>='A'&&Word[Word.length()-1]<='Z')  )
        {
         if(WordMap[Word]!="")
         {
             classified[WordMap[Word]] = true;
             LocalReturn = true;
         }
         else
         {
             //do nothing
         }
        }
        else
        {
         Word = Word.substr(0,Word.length()-1);
         if(WordMap[Word]!="")
         {
             classified[WordMap[Word]] = true;
             LocalReturn = true;
         }
         else
         {
             //do nothing
         }
        }
    }

 return LocalReturn;
 }

 std::string IntentRecognizer_FormIntent(bool status)
 {
    std::unordered_map<std::string,bool>::iterator it;
    std::string Intent;

    if(status == true)
    {
    Intent.append("Intent: Get ");

    for (it = classified.begin(); it != classified.end(); it++)
       {
          if(it->second == true)
          {
              Intent.append(it->first);
              Intent.append(" ");
              it->second = false;
          }
          else
          {
              //do nothing
          }
       }
    }
    else
    {
      Intent.append("Intent: No valid Intent please check keywords");
    }

  return Intent;
 }

};



int main()
{
     std::string input;
     IntentRecognizer usrIntent;
     std::cout<<"Enter your phrase to continue or type exit to close."<<"\r\n";

   while(true)
     {
     getline(std::cin,input);

     if(input!="exit")
     {
     std::cout<<usrIntent.IntentRecognizer_GetIntent(input.substr(0,input.length()))<<"\r\n";
     }
     else
     {
      std::cout <<"Closing..."<<"\r\n";
      break;
     }

     };

    return 0;
}
