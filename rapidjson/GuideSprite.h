#ifndef guidesprite
#define guidesprite

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

// using namespace rapidjson;

using namespace std;

namespace detail{
typedef struct
{
    string _groupid;
    string _spritetag;
} Animation;

typedef struct
{
    string _questionid;
    string _delay;
    string _sound;
    string _mode;
    vector<Animation> _animationgroup;
} Question;

typedef struct
{
    string _answerid;
    string _mode;
    string _sound;
    string _keyword;
} AnswerData;

typedef struct
{
    string _answermode;
    string _mode;
    string _quantity;
    vector<AnswerData> _answerset;
} Answer;

typedef struct
{
    string _sound;
    vector<Animation> _animationgroup;
} List;

typedef struct
{
    string _mode;
    string _type;
    vector<List> _list;
} Prompt;

typedef struct
{
    Question _question;
    Answer _answer;
    vector<Prompt> _promptSet;
} QuestionSet;

typedef struct
{
    string _groupid;
    vector<QuestionSet> _questionSet;
} GroupSet;

typedef struct
{
    string _pageid;
    string _mode;
    string _sound;
    vector<GroupSet> _groupSet;
} Page;

typedef struct
{
    vector<Page> _pages;
} Book;

class BookParser
{
};

string initBook(const string jsonFile)
{
    fstream fs(jsonFile, fs.in);
    string fileString;
    if(!fs.is_open())
    {
        cout << "failed to open " << jsonFile << endl;
    }

    fs.seekg(0,fs.end);
    std::size_t len = fs.tellg();
    fs.seekg(0,fs.beg);
    char str[len];
    fs.read(str,len);
    fs.close();

    return str;
}
}
#endif