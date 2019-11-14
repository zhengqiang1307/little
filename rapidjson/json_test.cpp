// Hello World example
// This example shows basic usage of DOM-style API.

#include "rapidjson/document.h"     // rapidjson's DOM-style API
#include "rapidjson/prettywriter.h" // for stringify JSON
#include <cstdio>

#include <string>
#include "GuideSprite.h"
#include "jsontxt.h"
#include <iostream>

using namespace rapidjson;
using namespace std;
using namespace detail;

void printBook(Book book)
{
  vector<string> lines;
  lines.push_back("{");
  lines.push_back(" book: [");
  lines.push_back("   {");
  for (auto page : book._pages)
  {
    lines.push_back("     page: {");
    lines.push_back("       pageid: " + page._pageid);
    lines.push_back("       mode: " + page._mode);
    lines.push_back("       sound: " + page._sound);
    lines.push_back("       groupset: [");
    lines.push_back("         {");
    for (auto groupMember : page._groupSet)
    {
      lines.push_back("           groupid: " + groupMember._groupid);
      lines.push_back("           questionset: [");

      for (auto questionMember : groupMember._questionSet)
      {
        lines.push_back("             {");
        lines.push_back("               question: {");
        lines.push_back("               questionid: " + questionMember._question._questionid);
        lines.push_back("               delay: " + questionMember._question._delay);
        lines.push_back("               sound: " + questionMember._question._sound);
        lines.push_back("               mode: " + questionMember._question._mode);
        lines.push_back("               animationgroup: [" );
        for(auto animation:questionMember._question._animationgroup)
        {
          lines.push_back("                 {" );
          lines.push_back("                   groupid: " + animation._groupid);
          lines.push_back("                   spritetag: " + animation._spritetag);
          lines.push_back("                 }" );
        }
        lines.push_back("           }," );
      }
      lines.push_back("   }" );
    }
  }
  lines.push_back("}" );

  for (auto line : lines)
  {
    cout << line << endl;
  }
}

int main(int, char *[])
{
  Value::MemberIterator it;
  string fileString = initBook("rapidjson/guidesprite.txt");
  // std::cout << fileString << std::endl;

  char buffer[fileString.length()];
  memcpy(buffer, fileString.c_str(), fileString.length());

  Document document;
  if (document.Parse(buffer).HasParseError())
  {
    std::cout << "document parse failed" << std::endl;
    return 1;
  }

  printf("\nParsing to document succeeded.\n");
  printf("\nAccess values in document:\n");

  assert(document.HasMember("book"));
  SizeType pageNum = document["book"].Size();
  pageNum = 1;
  Book book;
  book._pages.resize(pageNum);


  for (SizeType i = 0; i < pageNum; ++i)
  {
    Value &pageJson = document["book"][i]["page"];
    if ((it = pageJson.FindMember("pageid")) != pageJson.MemberEnd())
      book._pages[i]._pageid = it->value.GetString();

    if ((it = pageJson.FindMember("mode")) != pageJson.MemberEnd())
      book._pages[i]._mode = it->value.GetString();

    if ((it = pageJson.FindMember("sound")) != pageJson.MemberEnd())
      book._pages[i]._sound = it->value.GetString();

    assert((it = pageJson.FindMember("groupset")) != pageJson.MemberEnd());
    SizeType groupsetNum = it->value.Size();
    book._pages[i]._groupSet.resize(groupsetNum);

    for (SizeType j = 0; j < groupsetNum; ++j)
    {
      Value &groupsetMemberJson = it->value[j];

      assert(groupsetMemberJson.HasMember("groupid"));
      book._pages[i]._groupSet[j]._groupid = groupsetMemberJson["groupid"].GetString();

      assert(groupsetMemberJson.HasMember("questionset"));
      SizeType questionsetNum = groupsetMemberJson["questionset"].Size();
      book._pages[i]._groupSet[j]._questionSet.resize(questionsetNum);

      for (SizeType k = 0; k < questionsetNum; ++k)
      {
        Value &questionsetMemberJson = groupsetMemberJson["questionset"][k];
        //question
        assert(questionsetMemberJson.HasMember("question"));
        Value &questionJson = questionsetMemberJson["question"];

        if (questionJson.HasMember("questionid"))
          book._pages[i]._groupSet[j]._questionSet[k]._question._questionid = questionJson["questionid"].GetString();

        if (questionJson.HasMember("delay"))
          book._pages[i]._groupSet[j]._questionSet[k]._question._delay = questionJson["delay"].GetString();

        if (questionJson.HasMember("sound"))
          book._pages[i]._groupSet[j]._questionSet[k]._question._sound = questionJson["sound"].GetString();

        assert(questionJson.HasMember("mode"));
        book._pages[i]._groupSet[j]._questionSet[k]._question._mode = questionJson["mode"].GetString();

        assert(questionJson.HasMember("animationgroup"));
        SizeType animationgroupNum = questionJson["animationgroup"].Size();
        book._pages[i]._groupSet[j]._questionSet[k]._question._animationgroup.resize(animationgroupNum);

        for (SizeType l = 0; l < animationgroupNum; ++l)
        {
          Value &animationJson = questionJson["animationgroup"][l];
          assert(animationJson.HasMember("groupid"));
          book._pages[i]._groupSet[j]._questionSet[k]._question._animationgroup[l]._groupid = animationJson["groupid"].GetString();
          assert(animationJson.HasMember("spritetag"));
          book._pages[i]._groupSet[j]._questionSet[k]._question._animationgroup[l]._spritetag = animationJson["spritetag"].GetString();
        }
        //answer
        assert(questionsetMemberJson.HasMember("answer"));
        Value &answerJson = questionsetMemberJson["answer"];

        assert(answerJson.HasMember("answermode"));
        book._pages[i]._groupSet[j]._questionSet[k]._answer._answermode = answerJson["answermode"].GetString();

        if (answerJson.HasMember("quantity"))
          book._pages[i]._groupSet[j]._questionSet[k]._answer._quantity = answerJson["quantity"].GetString();

        assert(answerJson.HasMember("answerset"));
        SizeType answersetNum = answerJson["answerset"].Size();
        book._pages[i]._groupSet[j]._questionSet[k]._answer._answerset.resize(answersetNum);

        for (SizeType m = 0; m < answersetNum; ++m)
        {
          Value &answerdataJson = answerJson["answerset"][m]["answer"];

          if (answerdataJson.HasMember("answerid"))
            book._pages[i]._groupSet[j]._questionSet[k]._answer._answerset[m]._answerid = answerdataJson["answerid"].GetString();

          if (answerdataJson.HasMember("mode"))
            book._pages[i]._groupSet[j]._questionSet[k]._answer._answerset[m]._mode = answerdataJson["mode"].GetString();

          if (answerdataJson.HasMember("sound"))
            book._pages[i]._groupSet[j]._questionSet[k]._answer._answerset[m]._sound = answerdataJson["sound"].GetString();

          if ((it = answerdataJson.FindMember("keyword")) != answerdataJson.MemberEnd())
            book._pages[i]._groupSet[j]._questionSet[k]._answer._answerset[m]._keyword = it->value.GetString();
        }

        //promptset
        assert(questionsetMemberJson.HasMember("promptset"));
        Value &promptsetJson = questionsetMemberJson["promptset"];

        assert(promptsetJson.IsArray());
        SizeType promptsetNum = promptsetJson.Size();
        book._pages[i]._groupSet[j]._questionSet[k]._promptSet.resize(promptsetNum);
        for (SizeType n = 0; n < promptsetNum; ++n)
        {
          Value &promptJson = promptsetJson[n]["prompt"];

          if ((it = promptJson.FindMember("mode")) != promptJson.MemberEnd())
            book._pages[i]._groupSet[j]._questionSet[k]._promptSet[n]._mode = it->value.GetString();

          if ((it = promptJson.FindMember("type")) != promptJson.MemberEnd())
            book._pages[i]._groupSet[j]._questionSet[k]._promptSet[n]._type = it->value.GetString();

          assert((it = promptJson.FindMember("list")) != promptJson.MemberEnd());
          Value &listJson = it->value;
          assert(listJson.IsArray());
          SizeType listNum = listJson.Size();
          book._pages[i]._groupSet[j]._questionSet[k]._promptSet[n]._list.resize(listNum);
          for (SizeType listIndex = 0; listIndex < listNum; ++listIndex)
          {
            Value &listMemberJson = listJson[listIndex];
            if ((it = listMemberJson.FindMember("sound")) != promptJson.MemberEnd())
              book._pages[i]._groupSet[j]._questionSet[k]._promptSet[n]._list[listIndex]._sound = it->value.GetString();

            assert((it = listMemberJson.FindMember("animationgroup")) != promptJson.MemberEnd());
            Value &animationgroupJson = it->value;
            assert(animationgroupJson.IsArray());
            SizeType animationgroupNumOfList = animationgroupJson.Size();
            book._pages[i]._groupSet[j]._questionSet[k]._promptSet[n]._list[listIndex]._animationgroup.resize(animationgroupNumOfList);
            for (SizeType animationgroupIndexOfList = 0; animationgroupIndexOfList < animationgroupNumOfList; ++animationgroupIndexOfList)
            {

              Value &animationOfListJson = animationgroupJson[animationgroupIndexOfList];

              if ((it = animationOfListJson.FindMember("groupid")) != promptJson.MemberEnd())
                book._pages[i]._groupSet[j]._questionSet[k]._promptSet[n]._list[listIndex]._animationgroup[animationgroupIndexOfList]._groupid = it->value.GetString();

              if ((it = animationOfListJson.FindMember("spritetag")) != promptJson.MemberEnd())
                book._pages[i]._groupSet[j]._questionSet[k]._promptSet[n]._list[listIndex]._animationgroup[animationgroupIndexOfList]._spritetag = it->value.GetString();
            }
          }
        }
      }
    }

    printBook(book);
  }
  return 0;
}

int test2()
{
  ////////////////////////////////////////////////////////////////////////////
  // 1. Parse a JSON text string to a document.

  char json[] =
      " { \"hello\" : \"world\", \"t\" : true , \"f\" : false, \"n\": null, "
      "\"i\":123, \"pi\": 3.1416, \"a\":[1, 2, 3, 4] } ";
  printf("Original JSON:\n %s\n", json);

  Document
      document; // Default template parameter uses UTF8 and MemoryPoolAllocator.

#if 0
    // "normal" parsing, decode strings to new buffers. Can use other input stream via ParseStream().
    if (document.Parse(json).HasParseError())
        return 1;
#else
  // In-situ parsing, decode strings directly in the source string. Source must
  // be string.
  char buffer[sizeof(json)];
  memcpy(buffer, json, sizeof(json));
  if (document.ParseInsitu(buffer).HasParseError())
    return 1;
#endif

  printf("\nParsing to document succeeded.\n");

  ////////////////////////////////////////////////////////////////////////////
  // 2. Access values in document.

  printf("\nAccess values in document:\n");
  assert(document.IsObject()); // Document is a JSON value represents the root
                               // of DOM. Root can be either an object or array.

  assert(document.HasMember("hello"));
  assert(document["hello"].IsString());
  printf("hello = %s\n", document["hello"].GetString());

  // Since version 0.2, you can use single lookup to check the existing of
  // member and its value:
  Value::MemberIterator hello = document.FindMember("hello");
  assert(hello != document.MemberEnd());

  // Value::MemberIterator it;
  // if((it = document.FindMember("hello")) != document.MemberEnd());
  // it->value;

  assert(hello->value.IsString());
  assert(strcmp("world", hello->value.GetString()) == 0);
  (void)hello;

  assert(document["t"].IsBool()); // JSON true/false are bool. Can also uses
                                  // more specific function IsTrue().
  printf("t = %s\n", document["t"].GetBool() ? "true" : "false");

  assert(document["f"].IsBool());
  printf("f = %s\n", document["f"].GetBool() ? "true" : "false");

  printf("n = %s\n", document["n"].IsNull() ? "null" : "?");

  assert(document["i"].IsNumber());           // Number is a JSON type, but C++ needs more
                                              // specific type.
  assert(document["i"].IsInt());              // In this case, IsUint()/IsInt64()/IsUint64()
                                              // also return true.
  printf("i = %d\n", document["i"].GetInt()); // Alternative (int)document["i"]

  assert(document["pi"].IsNumber());
  assert(document["pi"].IsDouble());
  printf("pi = %g\n", document["pi"].GetDouble());

  {
    const Value &a = document["a"]; // Using a reference for consecutive access
                                    // is handy and faster.
    assert(a.IsArray());
    for (SizeType i = 0; i < a.Size();
         i++) // rapidjson uses SizeType instead of size_t.
      printf("a[%d] = %d\n", i, a[i].GetInt());

    int y = a[0].GetInt();
    (void)y;

    // Iterating array with iterators
    printf("a = ");
    for (Value::ConstValueIterator itr = a.Begin(); itr != a.End(); ++itr)
      printf("%d ", itr->GetInt());
    printf("\n");

    for (auto &v : a.GetArray())
    {
      v.GetInt();
    }
  }

  // Iterating object members
  static const char *kTypeNames[] = {"Null", "False", "True", "Object",
                                     "Array", "String", "Number"};
  for (Value::ConstMemberIterator itr = document.MemberBegin();
       itr != document.MemberEnd(); ++itr)
    printf("Type of member %s is %s\n", itr->name.GetString(),
           kTypeNames[itr->value.GetType()]);

  ////////////////////////////////////////////////////////////////////////////
  // 3. Modify values in document.

  // Change i to a bigger number
  {
    u_int64_t f20 = 1; // compute factorial of 20
    for (u_int64_t j = 1; j <= 20; j++)
      f20 *= j;
    document["i"] = f20;            // Alternate form: document["i"].SetUint64(f20)
    assert(!document["i"].IsInt()); // No longer can be cast as int or uint.
  }

  // Adding values to array.
  {
    Value &a = document["a"]; // This time we uses non-const reference.
    Document::AllocatorType &allocator = document.GetAllocator();
    for (int i = 5; i <= 10; i++)
      a.PushBack(
          i,
          allocator); // May look a bit strange, allocator is needed for
                      // potentially realloc. We normally uses the document's.

    // Fluent API
    a.PushBack("Lua", allocator).PushBack("Mio", allocator);
  }

  // Making string values.

  // This version of SetString() just store the pointer to the string.
  // So it is for literal and string that exists within value's life-cycle.
  {
    document["hello"] = "rapidjson"; // This will invoke strlen()
                                     // Faster version:
    // document["hello"].SetString("rapidjson", 9);
  }

  // This version of SetString() needs an allocator, which means it will
  // allocate a new buffer and copy the the string into the buffer.
  Value author;
  {
    char buffer2[10];
    int len =
        sprintf(buffer2, "%s %s", "Milo",
                "Yip"); // synthetic example of dynamically created string.

    author.SetString(buffer2, static_cast<SizeType>(len),
                     document.GetAllocator());
    // Shorter but slower version:
    // document["hello"].SetString(buffer, document.GetAllocator());

    // Constructor version:
    // Value author(buffer, len, document.GetAllocator());
    // Value author(buffer, document.GetAllocator());
    memset(buffer2, 0, sizeof(buffer2)); // For demonstration purpose.
  }
  // Variable 'buffer' is unusable now but 'author' has already made a copy.
  document.AddMember("author", author, document.GetAllocator());

  assert(
      author.IsNull()); // Move semantic for assignment. After this variable is
                        // assigned as a member, the variable becomes null.

  ////////////////////////////////////////////////////////////////////////////
  // 4. Stringify JSON

  printf("\nModified JSON with reformatting:\n");
  StringBuffer sb;
  PrettyWriter<StringBuffer> writer(sb);
  document.Accept(
      writer); // Accept() traverses the DOM and generates Handler events.
  puts(sb.GetString());
  return 0;
}

/*
{
    "name":"jack",//常规的
    "age":18,
    "sub":["a","b"],//value是数组
    "elp":[ {"a":"A","b":"B"},//value是一个数组且里面每个元素又是一个json格式
            {"c":"C","d":"D"},
          ]
}
*/
std::string build_json_msg()
{
  Document doc;
  doc.SetObject();
  Document::AllocatorType &a = doc.GetAllocator();

  doc.AddMember("name", "jack", a);
  doc.AddMember("age", 18, a);

  Value sub(kArrayType);
  sub.PushBack("a", a);
  sub.PushBack("b", a);
  doc.AddMember("sub", sub, a);

  Value json(kArrayType);
  Value obj(kObjectType);
  obj.AddMember("a", "A", a);
  obj.AddMember("b", "B", a);
  json.PushBack(obj, a);

  Value obj1(kObjectType);
  obj1.AddMember("c", "C", a);
  obj1.AddMember("d", "D", a);
  json.PushBack(obj1, a);

  doc.AddMember("elp", json, a);

  StringBuffer s;
  Writer<StringBuffer> writer(s);
  doc.Accept(writer);
  return std::string(s.GetString());
}

void test1()
{
  std::string o = build_json_msg();
  printf("dom is %s\n", o.c_str());
}

namespace jsontxt{
AnimationGroupSet getAnimationnGroup(const rapidjson::Value &animationGroupSetJson);

int init2()
{
  string fileString = initBook("rapidjson/json.txt");

    // "book_res/" +
    // std::string bookPath =  BookParser::getInstance()->getBookPath();
    // auto jsonStr = FileUtils::getInstance()->getStringFromFile(bookPath + "/json.txt");

    Document doc;
    if (doc.Parse(fileString.c_str()).HasParseError())
    {
        printf("&&& doc parse failed");
        return 1;
    }
    
    assert(doc.HasMember("book"));
    rapidjson::Value &book = doc["book"];
    //    int pageNum = book.Size();
    
    // int currentPage = BookParser::getInstance()->getCurrentPage();
    int currentPage = 3;
    rapidjson::Value &pageJson = book[currentPage - 1]["page"];
    rapidjson::Value::MemberIterator it;
    
    if ((it = pageJson.FindMember("animationgroupset")) != pageJson.MemberEnd())
    {
        rapidjson::Value &animationGroupSetJson = it->value;
        getAnimationnGroup(animationGroupSetJson);
    }
        
    return 0;
}

AnimationGroupSet getAnimationnGroup(const rapidjson::Value& animationGroupSetJson)
{
    rapidjson::Value::ConstMemberIterator it;
    AnimationGroupSet animationGroupSet;
    assert(animationGroupSetJson.IsArray());
    rapidjson::SizeType groupNum = animationGroupSetJson.Size();
    animationGroupSet._animationGroups.resize(groupNum);
    
    for(rapidjson::SizeType i = 0; i < groupNum; ++i)
    {
        const rapidjson::Value& animationGroupJson = animationGroupSetJson[i]["animationgroup"];
        assert(animationGroupJson.IsArray());
        rapidjson::SizeType memNum = animationGroupJson.Size();
        animationGroupSet._animationGroups.at(i)._animationGroupMems.resize(memNum);
        
        for(rapidjson::SizeType j = 0; j < memNum; ++j)
        {
            AnimationGroupMem* animationGroupMem = &animationGroupSet._animationGroups.at(i)._animationGroupMems.at(j);
            
            if ((it = animationGroupJson[j].FindMember("event")) != animationGroupJson[j].MemberEnd())
                animationGroupMem->_event = it->value.GetString();
            
            if ((it = animationGroupJson[j].FindMember("spritetag")) != animationGroupJson[j].MemberEnd())
                animationGroupMem->_spriteTag = stoi(it->value.GetString());
            
            if ((it = animationGroupJson[j].FindMember("animationset")) != animationGroupJson[j].MemberEnd())
            {
                const rapidjson::Value& animationSetJson = animationGroupJson[j]["animationset"];
                assert(animationSetJson.IsArray());
                rapidjson::SizeType animationNum = animationSetJson.Size();
                
                animationGroupMem->_animationSet._animations.resize(animationNum);
                
                for(rapidjson::SizeType k = 0; k < animationNum; ++k)
                {
                    const rapidjson::Value& animationJson = animationSetJson[k]["animation"];
                    Animation* animation = &animationGroupMem->_animationSet._animations.at(k);
                    
                    if ((it = animationJson.FindMember("style")) != animationJson.MemberEnd())
                    {
                        animation->_style = it->value.GetString();
                        printf("&&& style = %s", it->value.GetString());
                    }
                    
                    if ((it = animationJson.FindMember("category")) != animationJson.MemberEnd())
                        animation->_category = it->value.GetString();
                    
                    if ((it = animationJson.FindMember("touch")) != animationJson.MemberEnd())
                        animation->_touch = it->value.GetString();
                    
                    if ((it = animationJson.FindMember("property")) != animationJson.MemberEnd())
                    {
                        const rapidjson::Value& propertyJson = it->value;
                        
                        if ((it = propertyJson.FindMember("delay")) != propertyJson.MemberEnd())
                            animation->_property._delay = stof(it->value.GetString());
                        
                        if ((it = propertyJson.FindMember("duration")) != propertyJson.MemberEnd())
                            animation->_property._duration = stof(it->value.GetString());
                        
                        if ((it = propertyJson.FindMember("opacity")) != propertyJson.MemberEnd())
                            animation->_property._opacity = stof(it->value.GetString());
                        
                        if ((it = propertyJson.FindMember("scaleX")) != propertyJson.MemberEnd())
                            animation->_property._scaleX = stof(it->value.GetString());
                        
                        if ((it = propertyJson.FindMember("scaleY")) != propertyJson.MemberEnd())
                            animation->_property._scaleY = stof(it->value.GetString());
                        
                        if ((it = propertyJson.FindMember("endposition")) != propertyJson.MemberEnd())
                        {
                            const rapidjson::Value& endPositionJson = it->value;
                            
                            if ((it = endPositionJson.FindMember("x")) != endPositionJson.MemberEnd())
                                animation->_property._endPosition._x = stof(it->value.GetString());
                            
                            if ((it = endPositionJson.FindMember("y")) != endPositionJson.MemberEnd())
                                animation->_property._endPosition._y = stof(it->value.GetString());
                        }
                    }
                }
            }
        }
    }
    return animationGroupSet;
}
}