#ifndef guidesprite
#define guidesprite

#include <vector>
#include <string>

using namespace std;

typedef struct {
    int _groupid;
    int _spritetag;
} Animation;

typedef struct {
    int _questionid;
    int _delay;
    string _mode;
    vector<Animation> _animationgroup;
} Question;

typedef struct{
    int _answerid;
    string _mode;
    string _sound;
    string _keyword;
} AnswerData;

typedef struct {
    string _answermode;
    string _mode;
    int _quantity;
    vector<AnswerData> _answerset;
} Answer;

typedef struct {
    string _sound;
    vector<Animation> _animationgroup;
}listData;

typedef struct {
    string _mode;
    string _type;
    vector<listData> _list;
} Prompt;

typedef struct {
    Question _question;
    Answer _answer;
    vector<Prompt> _promptSet;
} QuestionSet;

typedef struct {
    int _groupid;
    vector<QuestionSet> _questionSet;
} GroupSet;

typedef struct {
    int _pageid;
    string _mode;
    string _sound;
    vector<GroupSet> _groupSet;
} Page;

typedef struct {
    vector<Page> _page;
} Book;

#endif