// SYNTAX TEST "C++.sublime-syntax"

#include "abc.h"
// <- meta.preprocessor.c -keyword.control.import
 // <- keyword.control.import
//^^^^^^ keyword.control.import
  #include <wootle>
//         ^^^^^^^^ string

// number filenames in system paths are highlighted - accident due to prototype but kind of ok
#include <0x123.txt
// (testing include is closed at end of line, just as damage limitation in case of a problem)

 #if 0
//   ^ constant.numeric

UCLASS(BlueprintType, Blah="hello")
// <- comment
//   ^^^^^^^^^^^^^^^^^^^^^^^^^ comment

# endif
// <- meta.preprocessor.c -keyword.control.import
//^^^^^ meta.preprocessor.c keyword.control.import


#
// <- meta.preprocessor.c
# if ECAPS_ < 2
// <- meta.preprocessor.c -keyword.control.import
//^^ meta.preprocessor.c keyword.control.import
//   ^^^^^^ meta.preprocessor.c
//          ^ meta.preprocessor keyword.operator
//            ^ constant.numeric

# define  BLAH  jks class
//^^^^^^ keyword.control.import.define
//        ^^^^ entity.name.function.preprocessor

#define  BLAH  jks class   \
    void f() { ---
//       ^ -entity
//             ^ -meta.block


abc "def" ghi "g\"h\ni\\" jkl
//            ^^^^^^^^^^^ string 
//              ^^ string constant.character.escape
//                 ^^ string constant.character.escape 
//                    ^^ string constant.character.escape 

abc 'def' ghi 'g\'h\ni\\' jkl
//            ^^^^^^^^^^^ string 
//              ^^ string constant.character.escape
//                 ^^ string constant.character.escape 
//                    ^^ string constant.character.escape 

L"blah"
// <- string

/* blah 'hello' */
//  ^ comment
//          ^ -string


template <class X=T<X>> x = 3;      // check variables are recognised after matching template brackets
// <- storage.type
//       ^ keyword.operator
//        ^^^^^ storage.type
//              ^ -variable
//               ^ keyword.operator
//                   ^^ keyword.operator
//                      ^ variable


void $func();

wooble::eek<abc>();
void Class::operator!<abc>()
{

}

auto concept LessThanComparable<typename T> {
    bool operator=(T, T);
}

class BLAH_API Class<int>
//    ^^^^^^^^ -entity.name.type
//             ^^^^^ entity.name.type
//                  ^ keyword.operator
//                   ^^^ storage.type
//                      ^ keyword.operator
{
    DEPRECATED(123, "blah", ReplicatedUsing)
//  ^^^^^^^^^^ support.type.ue4
//            ^ keyword.operator
//                ^ keyword.operator
//                  ^^^^^^ string
//                        ^ keyword.operator

    void func(int param=7)
//                ^^^^^ -variable
    {

    }


    void func(class Xyz xyz)
//       ^^^^ entity.name.function
//                  ^^^ -entity.name.type
    {

        void not_a_func();
//           ^^^^^^^^^^ -entity.name.function

        .blah 
//       ^^^^ - variable

        var.member;
//          ^^^^^^ variable

        ->blah 
//        ^^^^ -variable

        var->member;
//           ^^^^^^ variable

        var.x1.x2;

        var.x1->x2;

        var->x1->x2;

        var.memfunc();
//          ^^^^^^^ support.function

        var->memfunc();
//           ^^^^^^^ support.function

        case xyz:
//      ^^^^ keyword.control
//           ^^^ constant

        case EType::xyz:
//      ^^^^ keyword.control
//           ^^^^^ storage.type
//                ^^ keyword.operator
//                  ^^^ constant

label:
// <- meta.preprocessor.c
//   ^ keyword.operator

        123e7  123.f  123.45e3  .45f  123f  0x369abcdef  0X12.3p2l -123f
//                                                                 ^^^^^ constant.numeric
//                                                       ^^^^^^^^^       constant.numeric
//                                          ^^^^^^^^^^^                  constant.numeric
//                                    ^^^^                               constant.numeric
//                              ^^^^                                     constant.numeric
//                    ^^^^^^^^                                           constant.numeric
//             ^^^^^                                                     constant.numeric
//      ^^^^^                                                            constant.numeric

        1,2,3
//      ^ constant.numeric
//       ^ keyword.operator
//        ^ constant.numeric
//         ^ keyword.operator
//          ^ constant.numeric

        $123
//      ^^^^ -constant

        ABC_DEF
//      ^^^^^^^ constant

    }

    ~Class();
//  ^ entity

    using Super::Type;
//  ^^^^^ keyword.control
//             ^^ keyword.operator
//               ^^^^ entity
//                   ^ keyword.operator
    using (123); // make sure unusual expressions don't mess it up
//  ^^^^^ keyword.control
//        ^ keyword.operator
//            ^^ keyword.operator

    void operator!();
//       ^^^^^^^^^ entity.name.function
//                ^^^ keyword.operator
    void C :: operator->*();
//       ^^^^^^^^^^^^^^^^ entity.name.function
//                       ^^^ keyword.operator
    void operator ( ) ();
//       ^^^^^^^^^^^^ entity.name.function
//                    ^^^ keyword.operator
    void operator ( ) <X> ();
//       ^^^^^^^^^^^^ entity.name.function
//                    ^ keyword.operator
//                     ^ storage.type
//                      ^ keyword.operator
//                        ^^^ keyword.operator
};


Class::~Class();
//     ^ entity

class Blah : public X<blah>
{

}
 // <-      invalid.illegal

enum Enum
{
    Blah
//  ^^^^ constant
}
 // <-      invalid.illegal

struct S
{
    enum : int32
    {
        Blah = Another
//      ^^^^ constant
//             ^^^^^^^ constant        
    };
};


namespace nmspc
{

};
 // <-      invalid.illegal

namespace
{

};



void f();
// <- storage.type
//   ^ entity.name.function
//    ^^^ keyword.operator

namespace N
{
};
 // <-      invalid.illegal

namespace
{
  struct Inside;
}
 // <-      -invalid.illegal

/* blah 'hello' */
//  ^ comment
//          ^ -string

auto concept LessThanComparable<typename T> {
// <- storage.type
//   ^^^^^^^ storage.type
    bool operator=(T, T);
}
 // <-      invalid.illegal

class BLAH_API Class
//    ^^^^^^^^ -entity.name.type
//             ^^^^^ entity.name.type
{
    void func(class Xyz xyz)
//       ^^^^ entity.name.function
//                  ^^^ -entity.name.type
    {

        void not_a_func();
//           ^^^^^^^^^^ - entity.name.function

        .blah 
//       ^^^^ -variable

        var.member;
//          ^^^^^^ variable

        ->blah 
//        ^^^^ -variable

        var->member;
//           ^^^^^^ variable

        var.memfunc();
//          ^^^^^^^ support.function

        var->memfunc();
//           ^^^^^^^ support.function


    }
};

class BLAH_API Abc::Def {};
//             ^^^^^^^^ entity.name.type

void operator()()
{

}


class Blah : public X<blah>
{

}
 // <-      invalid.illegal

enum Enum
{
    Blah
}
 // <-      invalid.illegal


namespace nmspc
{

};
 // <-      invalid.illegal

namespace
{

};


template <class X>
class C : public X::template T<nullptr_t>::type {}
//                                                ^      invalid.illegal
//                                              ^^ -keyword.operator
//                                      ^^^ keyword.operator
//                             ^^^^^^^^^ storage.type
//                            ^ keyword.operator
//                  ^^^^^^^^ storage.type
//                ^^ keyword.operator
//        ^^^^^^ storage.modifier
//    ^ 

enum class Enum : int32
// <- storage.type
//    ^ storage.type
//         ^^^^ entity.name.type
//              ^ keyword.operator
//                 ^ storage.type.ue4
{
    Holy, Cow
//   ^ constant
//      ^ keyword.operator
//         ^ constant
}
 // <-      invalid.illegal


namespace nmspc trail
//        ^^^^^ entity.name.type.namespace
//              ^^^^^ -entity.name.type.namespace
{
// <- -keyword.operator

};
 // <-      invalid.illegal

namespace
{

};


UCLASS(BlueprintType, Blah="hello")
//  <- support.type.ue4
//                         ^^^^^^^ string
class UHomeBaseWorkers : public UObject
{
    GENERATED_BODY()
//  ^^^^^^^^^^^^^^ support.type.ue4
//                ^^ keyword.operator

    UFUNCTION(BlueprintCallable)
    virtual void CallMeMaybe() override;

    UPROPERTY(BlueprintReadWrite)
    int32* Blah;
//  ^^^^^ storage.type.ue4
//       ^ keyword.operator
//         ^^^^ variable
//             ^ keyword.operator

    SSlate<int> UCaps;

    typedef char (*X)();
    friend char X;
}
 // <-      invalid.illegal

class Decl* ppp;
//      ^ -entity
//           ^ variable

class Decl & ppp;
//      ^ -entity
//           ^ variable


template <class X>
class C : public X::template T<nullptr_t>::type {}
//                                                ^      invalid.illegal
//                                              ^^ -keyword.operator
//                                      ^^^ keyword.operator
//                             ^^^^^^^^^ storage.type
//                            ^ keyword.operator
//                  ^^^^^^^^ storage.type
//                ^^ keyword.operator
//        ^^^^^^ storage.modifier
//    ^ 

enum class Enum : int32
// <- storage.type
//    ^ storage.type
//              ^ keyword.operator
//                 ^ storage.type.ue4
{
    Holy, Cow
//   ^ constant
//      ^ keyword.operator
//         ^ constant
}
 // <-      invalid.illegal

enum class Enum : Blah;
//         ^^^^ storage.type
//                ^^^^ entity.other.inherited-class

enum class Enum::Woo;


namespace nmspc trail
//        ^^^^^ entity.name.type.namespace
//              ^^^^^ -entity.name.type.namespace
{
// <- -keyword.operator

};
 // <-      invalid.illegal

namespace
{

};

// ^ -meta.block

class X
{

} name, arse;
 // <- - invalid
//^^^^ variable
//    ^ keyword.operator
//      ^^^^ variable
//          ^ keyword.operator

UCLASS(BlueprintType, Blah="hello")
//                         ^^^^^^^ string
class UHomeBaseWorkers : public UObject
//                              ^^^^^^^ entity.other.inherited-class
{
    GENERATED_BODY()
//  ^^^^^^^^^^^^^^ support.type.ue4

    UFUNCTION(BlueprintCallable)
    virtual void CallMeMaybe() override;

    UPROPERTY(BlueprintReadWrite)
    int32* Blah;
//  ^^^^^ storage.type.ue4
//       ^ keyword.operator
//         ^^^^ variable
//             ^ keyword.operator

    typedef char Wibble;
//               ^^^^^^ entity.name.type

    typedef char (*X)();
//               ^^ keyword.operator
//                  ^^^^ keyword.operator
    friend char X;
}
 // <-      invalid.illegal


UCLASS(blah, meta=(hello))
//                ^ ue4-meta ue4-meta keyword.operator


void wibble = { f();
//   ^^^^^^ variable
//          ^ keyword.operator
//              ^ support.function

} abc
// ^ -meta.initializer

void wibble = f()
//   ^^^^^^ variable
//          ^ keyword.operator
//            ^ support.function

; abc  
// ^ -meta.initializer

int c[3] = { pootle, perkin, posie };
//  ^ variable
//   ^ keyword.operator
//    ^ constant.numeric
//     ^ keyword.operator
//           ^^^^^^ -variable

float f = 3/4;

class C<int> {};

template <>
void Spec<int>();
//   ^^^^ entity.name.function

// known failure (casuality of fixing template return type)
void Spec<X<>>();

template <>
X<> Spec<int>();
//  ^^^^ entity.name.function

// no return type
operator X::T&();
// <- entity.name.function
//^^^^^^^^^^^^ entity.name.function
//            ^^^ keyword.operator

operator T<int>();

void func(...)
//        ^^^ storage.type
{
    blah()->hello;
//      ^^^^ keyword.operator
//          ^^^^^ variable
//               ^ keyword.operator
    blah.hello;
    Spec<int>();
//  ^^^^ support.function
}

IMPLEMENT_GAME_MODULE(Blah);
//  ^ support.type.ue4

DEFINE_LOG_CATEGORY(Woo);
//  ^ support.type.ue4

DECLARE_DELEGATE(FDel)
//  ^ support.type.delegate.ue4
//              ^ keyword.operator
//               ^^^^ entity.name.type
//                   ^ keyword.operator

DECLARE_POOTLE_WIBBLE_DELEGATE_RetVal(S::X&, FRetVal, int)
//  ^ support.type.delegate.ue4
//                                   ^ keyword.operator
//                                    ^ storage.type
//                                     ^^ keyword.operator
//                                       ^ storage.type
//                                        ^^ keyword.operator
//                                           ^^^^^^^ entity.name.type
//                                                  ^ keyword.operator
//                                                    ^^^ storage.type
//                                                       ^ keyword.operator
DECLARE_POOTLE_WIBBLE_DELEGATE(FNoRetVal)
//  ^ support.type.delegate.ue4
//                            ^ keyword.operator
//                             ^^^^^^^^^ entity.name.type
//                                      ^ keyword.operator

DECLARE_POOTLE_WIBBLE_DELEGATE_RetVal_SomeMoreStuff(class int*, FRetValStuff, int)
//  ^ support.type.delegate.ue4
//                                                 ^ keyword.operator
//                                                  ^^^^^ storage.type
//                                                        ^^^ storage.type
//                                                           ^^ keyword.operator
//                                                              ^^^^^^^^^^^^ entity.name.type
//                                                                          ^ keyword.operator
//                                                                            ^^^ storage.type
//                                                                               ^ keyword.operator
DECLARE_POOTLE_WIBBLE_DELEGATE_SomeMoreStuff(FNoRetValStuff, "hello")
//  ^ support.type.delegate.ue4
//                                          ^ keyword.operator
//                                           ^^^^^^^^^^^^^^ entity.name.type
//                                                         ^ keyword.operator


DECLARE_EVENT(UCls, FEvent)
//  ^ support.type.event.ue4
//           ^ keyword.operator
//            ^^^^ storage.type
//                ^ keyword.operator
//                  ^^^^^^ entity.name.type
//                        ^ keyword.operator

DECLARE_EVENT_SomeMoreStuff(UCls, FEvent, "hello")
//  ^ support.type.event.ue4
//                         ^ keyword.operator
//                          ^^^^ storage.type
//                              ^ keyword.operator
//                                ^^^^^^ entity.name.type
//                                      ^ keyword.operator

DEFINE_LATENT_AUTOMATION_COMMAND(FCommand)
//  ^ support.type.command.ue4
//                              ^ keyword.operator
//                               ^^^^^^^^ entity.name.type
//                                       ^ keyword.operator

DEFINE_LATENT_AUTOMATION_COMMAND_SomeMoreStuff(FCommand, FType, Name)
//  ^ support.type.command.ue4
//                                            ^ keyword.operator
//                                             ^^^^^^^^ entity.name.type
//                                                     ^ keyword.operator
//                                                       ^^^^^ storage.type
//                                                            ^ keyword.operator


DEFINE_LATENT_AUTOMATION_COMMAND_TWO_PARAMETER(FDeltaSave_TestDeltasCheckedOut, TSharedRef<FDeltaFileTestStorage>, Storage, TArray<FPackagePath>, Expected);

UE_DECLARE_GAMEPLAY_TAG_EXTERN(Boo)
//  ^ support.type.ue4
//                            ^ keyword.operator
//                             ^^^ storage.type
//                                ^ keyword.operator

UE_DEFINE_GAMEPLAY_TAG(Foo, "Tag.Name");
//  ^ support.type.ue4
//                    ^ keyword.operator
//                     ^^^ entity.name.type
//                          ^^^ string
//                                    ^ keyword.operator


UE_DEFINE_GAMEPLAY_TAG_STATIC(Foo, "Tag.Name");
//  ^ support.type.ue4
//                           ^ keyword.operator
//                            ^^^ entity.name.type
//                                 ^^^ string
//                                           ^ keyword.operator

UE_DEFINE_GAMEPLAY_TAG_COMMENT(Woo, "Tag.Name", "comment");
//  ^ support.type.ue4


junk struct X {};
//          ^ -entity

template <class X> struct Blah {};
//       ^ keyword.operator
//              ^ -entity
//               ^ keyword.operator
//                        ^^^^ entity.name.type

EWooble::xyz
//     ^^ keyword.operator
//       ^^^ support.constant.ue4

EWooble::Type
//       ^^^^ -constant

class C<void (*f)> : public B<>{} c;
//             ^ specialisation-args -entity 

class TypeName const* Region;
//    ^^^^^^^^^^^^^^^ -entity
//                    ^^^^^^ variable
class const TypeName* Region;
//    ^^^^^^^^^^^^^^^ -entity
//                    ^^^^^^ variable

void (*f)() = nullptr;
// <- -entity
//            ^^^^^^^ constant


// known failure (not recognised as function specialisation)
void f<vector<int>>();

// todo (note: #if near top of file should help verify solutions)

#if 0
#if X
 blah
#endif
more blah
#endif


