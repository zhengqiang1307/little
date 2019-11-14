 #include <vector>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;
namespace jsontxt{
typedef struct
{
    float _x;
    float _y;
        } EndPosition;
        
        typedef struct{
            float _duration;
            EndPosition _endPosition;
            float _delay;
            float _opacity;
            float _scaleX;
            float _scaleY;
        } Property;
        
        typedef struct{
            string _style;
            string _touch;
            string _category;
            Property _property;
    //        float _duration;
    //        float _x;
    //        float _y;
        } Animation;
        
        typedef struct{
            vector<Animation> _animations;
        } AnimationSet;
        
        typedef struct{
            string _event;
            int _spriteTag;
            string _animationType;
            AnimationSet _animationSet;
        } AnimationGroupMem;
        
        typedef struct{
            vector<AnimationGroupMem> _animationGroupMems;
        } AnimationGroup;
        
        typedef struct{
            vector<AnimationGroup> _animationGroups;
        } AnimationGroupSet;
        }