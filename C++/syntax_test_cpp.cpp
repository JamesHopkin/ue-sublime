@ SYNTAX TEST "C++.sublime-syntax"

#include "abc.h"
@  <- meta.preprocessor.c -keyword.control.import
 @  <- keyword.control.import
@ ^^^^^^ keyword.control.import
  #include <wootle>
@          ^^^^^^^^ string

// number filenames in system paths are highlighted - accident due to prototype but kind of ok
#include <0x123.txt
// (testing include is closed at end of line, just as damage limitation in case of a problem)

 #if 0
@    ^ constant.numeric

UCLASS(BlueprintType, Blah="hello")
@  <- comment
@    ^^^^^^^^^^^^^^^^^^^^^^^^^ comment

# endif
@  <- meta.preprocessor.c -keyword.control.import
@ ^^^^^ meta.preprocessor.c keyword.control.import


#
@  <- meta.preprocessor.c
# if ECAPS_ < 2
@  <- meta.preprocessor.c -keyword.control.import
@ ^^ meta.preprocessor.c keyword.control.import
@    ^^^^^^ meta.preprocessor.c
@           ^ meta.preprocessor keyword.operator
@             ^ constant.numeric

# define  BLAH  jks class
@ ^^^^^^ keyword.control.import.define
@         ^^^^ entity.name.function.preprocessor

#define  BLAH  jks class   \
    void f() { ---
@        ^ -entity
@              ^ -meta.block


abc "def" ghi "g\"h\ni\\" jkl
@             ^^^^^^^^^^^ string 
@               ^^ string constant.character.escape
@                  ^^ string constant.character.escape 
@                     ^^ string constant.character.escape 

abc 'def' ghi 'g\'h\ni\\' jkl
@             ^^^^^^^^^^^ string 
@               ^^ string constant.character.escape
@                  ^^ string constant.character.escape 
@                     ^^ string constant.character.escape 

L"blah"
@  <- string

/* blah 'hello' */
@   ^ comment
@           ^ -string


template <class X=T<X>> x = 3;      // check variables are recognised after matching template brackets
@  <- storage.type
@        ^ keyword.operator
@         ^^^^^ storage.type
@               ^ -variable
@                ^ keyword.operator
@                    ^^ keyword.operator
@                       ^ variable


void $func();

wooble::eek<abc>();
void Class::operator!<abc>()
{

}

class BLAH_API Class<int>
@     ^^^^^^^^ -entity.name.type
@              ^^^^^ entity.name.type
@                   ^ keyword.operator
@                    ^^^ storage.type
@                       ^ keyword.operator
{
    DEPRECATED(123, "blah", ReplicatedUsing)
@   ^^^^^^^^^^ support.type.ue4
@             ^ keyword.operator
@                 ^ keyword.operator
@                   ^^^^^^ string
@                         ^ keyword.operator

    void func(int param=7)
@                 ^^^^^ -variable
    {

    }


    void func(class Xyz xyz)
@        ^^^^ entity.name.function
@                   ^^^ -entity.name.type
    {

        void not_a_func();
@            ^^^^^^^^^^ -entity.name.function

        .blah 
@        ^^^^ - variable

        var.member;
@           ^^^^^^ variable

        ->blah 
@         ^^^^ -variable

        var->member;
@            ^^^^^^ variable

        var.x1.x2;

        var.x1->x2;

        var->x1->x2;

        var.memfunc();
@           ^^^^^^^ support.function

        var->memfunc();
@            ^^^^^^^ support.function

        case xyz:
@       ^^^^ keyword.control
@            ^^^ constant

        case EType::xyz:
@       ^^^^ keyword.control
@            ^^^^^ storage.type
@                 ^^ keyword.operator
@                   ^^^ constant

label:
@  <- meta.preprocessor.c
@    ^ keyword.operator

        123e7  123.f  123.45e3  .45f  123f  0x369abcdef  0X12.3p2l -123f
@                                                                  ^^^^^ constant.numeric
@                                                        ^^^^^^^^^       constant.numeric
@                                           ^^^^^^^^^^^                  constant.numeric
@                                     ^^^^                               constant.numeric
@                               ^^^^                                     constant.numeric
@                     ^^^^^^^^                                           constant.numeric
@              ^^^^^                                                     constant.numeric
@       ^^^^^                                                            constant.numeric

        1,2,3
@       ^ constant.numeric
@        ^ keyword.operator
@         ^ constant.numeric
@          ^ keyword.operator
@           ^ constant.numeric

        $123
@       ^^^^ -constant

        ABC_DEF
@       ^^^^^^^ constant

    }

    ~Class();
@   ^ entity

    using Super::Type;
@   ^^^^^ keyword.control
@              ^^ keyword.operator
@                ^^^^ entity
@                    ^ keyword.operator
    using (123); // make sure unusual expressions don't mess it up
@   ^^^^^ keyword.control
@         ^ keyword.operator
@             ^^ keyword.operator

    void operator!();
@        ^^^^^^^^^ entity.name.function
@                 ^^^ keyword.operator
    void C :: operator->*();
@        ^^^^^^^^^^^^^^^^ entity.name.function
@                        ^^^ keyword.operator
    void operator ( ) ();
@        ^^^^^^^^^^^^ entity.name.function
@                     ^^^ keyword.operator
    void operator ( ) <X> ();
@        ^^^^^^^^^^^^ entity.name.function
@                     ^ keyword.operator
@                      ^ storage.type
@                       ^ keyword.operator
@                         ^^^ keyword.operator
};


Class::~Class();
@      ^ entity

class Class;
@  <- storage.type
 @  <- storage.type
@ ^^^ storage.type
@     ^^^^^ storage.type
@          ^ keyword.operator

template <class> class Class;
@  <- storage.type
 @  <- storage.type
@ ^^^^^^ storage.type
@        ^ keyword.operator
@         ^^^^^ storage.type
@              ^ keyword.operator
@                ^^^^^ storage.type
@                      ^^^^^ storage.type
@                           ^ keyword.operator


class Blah : public X<blah>
{

}
 @  <-      invalid.illegal

enum Enum
{
    Blah
@   ^^^^ constant
}
 @  <-      invalid.illegal

struct S
{
    enum : int32
    {
        Blah = Another
@       ^^^^ constant
@              ^^^^^^^ constant        
    };
};


namespace nmspc
{

};
 @  <-      invalid.illegal

namespace
{

};



void f();
@  <- storage.type
@    ^ entity.name.function
@     ^^^ keyword.operator

namespace N
{
};
 @  <-      invalid.illegal

namespace
{
  struct Inside;
}
 @  <-      -invalid.illegal

/* blah 'hello' */
@   ^ comment
@           ^ -string

concept Anything = true;
@  <- storage.type
 @  <- storage.type
@ ^^^^^ storage.type
@       ^^^^^^^^ entity.name.concept


// will need a concept context to match = being on the next line
// can then look for { and at least make it like a function scope (no defs inside)

template <class X>
concept C = requires(X x)
@  <- storage.type
 @  <- storage.type
@ ^^^^^ storage.type
@       ^ entity.name.concept
@         ^ keyword.operator
@           ^^^^^^^^ keyword.control
@                   ^ keyword.operator

{
    { std::visit(TakesBlah{}, std::declval<C>()) } -> Anything;


};

// for now, at least make sure this doesn't start a meta block!

@  ^ -meta.block


class BLAH_API Class
@     ^^^^^^^^ -entity.name.type
@              ^^^^^ entity.name.type
{
    void func(class Xyz xyz)
@        ^^^^ entity.name.function
@                   ^^^ -entity.name.type
    {

        void not_a_func();
@            ^^^^^^^^^^ - entity.name.function

        .blah 
@        ^^^^ -variable

        var.member;
@           ^^^^^^ variable

        ->blah 
@         ^^^^ -variable

        var->member;
@            ^^^^^^ variable

        var.memfunc();
@           ^^^^^^^ support.function

        var->memfunc();
@            ^^^^^^^ support.function


    }
};

class BLAH_API Abc::Def {};
@              ^^^^^^^^ entity.name.type

void operator()()
{

}


class Blah : public X<blah>
{

}
 @  <-      invalid.illegal

enum Enum
{
    Blah
}
 @  <-      invalid.illegal


namespace nmspc
{

};
 @  <-      invalid.illegal

namespace
{

};


template <class X>
class C : public X::template T<nullptr_t>::type {}
@                                                 ^      invalid.illegal
@                                               ^^ -keyword.operator
@                                       ^^^ keyword.operator
@                              ^^^^^^^^^ storage.type
@                             ^ keyword.operator
@                   ^^^^^^^^ storage.type
@                 ^^ keyword.operator
@         ^^^^^^ storage.modifier
@     ^ 


enum class Enum : int32
@  <- storage.type
@     ^ storage.type
@          ^^^^ entity.name.type
@               ^ keyword.operator
@                 ^^^^^ entity.other.inherited-class
{
    Holy, Cow
@    ^ constant
@       ^ keyword.operator
@          ^ constant
}
 @  <-      invalid.illegal

enum class Enum : Blah;
@          ^^^^ storage.type
@                 ^^^^ entity.other.inherited-class

enum class Enum::Woo;



namespace nmspc trail
@         ^^^^^ entity.name.type.namespace
@               ^^^^^ -entity.name.type.namespace
{
@  <- -keyword.operator

};
 @  <-      invalid.illegal

namespace
{

};



@  ^ -meta.block


UCLASS(BlueprintType, Blah="hello")
@   <- support.type.ue4
@                          ^^^^^^^ string
class UHomeBaseWorkers : public UObject
@                               ^^^^^^^ entity.other.inherited-class
{
    GENERATED_BODY()
@   ^^^^^^^^^^^^^^ support.type.ue4
@                 ^^ keyword.operator

    UFUNCTION(BlueprintCallable)
    virtual void CallMeMaybe() override;

    UPROPERTY(BlueprintReadWrite)
    int32* Blah;
@   ^^^^^ storage.type.ue4
@        ^ keyword.operator
@          ^^^^ variable
@              ^ keyword.operator

    typedef char Wibble;
@                ^^^^^^ entity.name.type

    // why is rhs a variable? should fix
    using Boo = int32;
@   ^^^^^ keyword.control
@         ^^^ entity.name.type

    typedef char (*X)();
@                ^^ keyword.operator
@                   ^^^^ keyword.operator


    friend char X;
}
 @  <-      invalid.illegal

class Decl* ppp;
@       ^ -entity
@            ^ variable

class Decl & ppp;
@       ^ -entity
@            ^ variable


template <class X>
class C : public X::template T<nullptr_t>::type {}
@                                                 ^      invalid.illegal
@                                               ^^ -keyword.operator
@                                       ^^^ keyword.operator
@                              ^^^^^^^^^ storage.type
@                             ^ keyword.operator
@                   ^^^^^^^^ storage.type
@                 ^^ keyword.operator
@         ^^^^^^ storage.modifier
@     ^ 


namespace nmspc trail
@         ^^^^^ entity.name.type.namespace
@               ^^^^^ -entity.name.type.namespace
{
@  <- -keyword.operator

};
 @  <-      invalid.illegal



class X
{

} name, arse;
 @  <- - invalid
@ ^^^^ variable
@     ^ keyword.operator
@       ^^^^ variable
@           ^ keyword.operator


UCLASS(blah, meta=(hello))
@                 ^ ue4-meta ue4-meta keyword.operator


// what is this about?
void wibble = { f();
@    ^^^^^^ variable
@           ^ keyword.operator
@               ^ support.function

} abc
@  ^ -meta.initializer

void wibble = f()
@    ^^^^^^ variable
@           ^ keyword.operator
@             ^ support.function

; abc  
@  ^ -meta.initializer

int c[3] = { pootle, perkin, posie };
@   ^ variable
@    ^ keyword.operator
@     ^ constant.numeric
@      ^ keyword.operator
@            ^^^^^^ -variable

float f = 3/4;

class C<int> {};

template <>
void Spec<int>();
@    ^^^^ entity.name.function

// known failure (casuality of fixing template return typ   e)
void Spec<X<>>();

template <>
X<> Spec<int>();
@   ^^^^ entity.name.function

// no return type
operator X::T&();
@  <- entity.name.function
@ ^^^^^^^^^^^^ entity.name.function
@             ^^^ keyword.operator

operator T<int>();

void func(...)
@         ^^^ storage.type
{
    blah()->hello;
@       ^^^^ keyword.operator
@           ^^^^^ variable
@                ^ keyword.operator
    blah.hello;
    Spec<int>();
@   ^^^^ support.function
}

IMPLEMENT_GAME_MODULE(Blah);
@   ^ support.type.ue4

DEFINE_LOG_CATEGORY(Woo);
@   ^ support.type.ue4

DECLARE_DELEGATE(FDel)
@   ^ support.type.delegate.ue4
@               ^ keyword.operator
@                ^^^^ entity.name.type
@                    ^ keyword.operator

DECLARE_POOTLE_WIBBLE_DELEGATE_RetVal(S::X&, FRetVal, int)
@   ^ support.type.delegate.ue4
@                                    ^ keyword.operator
@                                     ^ storage.type
@                                      ^^ keyword.operator
@                                        ^ storage.type
@                                         ^^ keyword.operator
@                                            ^^^^^^^ entity.name.type
@                                                   ^ keyword.operator
@                                                     ^^^ storage.type
@                                                        ^ keyword.operator
DECLARE_POOTLE_WIBBLE_DELEGATE(FNoRetVal)
@   ^ support.type.delegate.ue4
@                             ^ keyword.operator
@                              ^^^^^^^^^ entity.name.type
@                                       ^ keyword.operator

DECLARE_POOTLE_WIBBLE_DELEGATE_RetVal_SomeMoreStuff(class int*, FRetValStuff, int)
@   ^ support.type.delegate.ue4
@                                                  ^ keyword.operator
@                                                   ^^^^^ storage.type
@                                                         ^^^ storage.type
@                                                            ^^ keyword.operator
@                                                               ^^^^^^^^^^^^ entity.name.type
@                                                                           ^ keyword.operator
@                                                                             ^^^ storage.type
@                                                                                ^ keyword.operator
DECLARE_POOTLE_WIBBLE_DELEGATE_SomeMoreStuff(FNoRetValStuff, "hello")
@   ^ support.type.delegate.ue4
@                                           ^ keyword.operator
@                                            ^^^^^^^^^^^^^^ entity.name.type
@                                                          ^ keyword.operator


DECLARE_EVENT(UCls, FEvent)
@   ^ support.type.event.ue4
@            ^ keyword.operator
@             ^^^^ storage.type
@                 ^ keyword.operator
@                   ^^^^^^ entity.name.type
@                         ^ keyword.operator

DECLARE_EVENT_SomeMoreStuff(UCls, FEvent, "hello")
@   ^ support.type.event.ue4
@                          ^ keyword.operator
@                           ^^^^ storage.type
@                               ^ keyword.operator
@                                 ^^^^^^ entity.name.type
@                                       ^ keyword.operator

DEFINE_LATENT_AUTOMATION_COMMAND(FCommand)
@   ^ support.type.command.ue4
@                               ^ keyword.operator
@                                ^^^^^^^^ entity.name.type
@                                        ^ keyword.operator

DEFINE_LATENT_AUTOMATION_COMMAND_SomeMoreStuff(FCommand, FType, Name)
@   ^ support.type.command.ue4
@                                             ^ keyword.operator
@                                              ^^^^^^^^ entity.name.type
@                                                      ^ keyword.operator
@                                                        ^^^^^ storage.type
@                                                             ^ keyword.operator


DEFINE_LATENT_AUTOMATION_COMMAND_TWO_PARAMETER(FDeltaSave_TestDeltasCheckedOut, TSharedRef<FDeltaFileTestStorage>, Storage, TArray<FPackagePath>, Expected);

UE_DECLARE_GAMEPLAY_TAG_EXTERN(Boo)
@   ^ support.type.ue4
@                             ^ keyword.operator
@                              ^^^ storage.type
@                                 ^ keyword.operator

UE_DEFINE_GAMEPLAY_TAG(Foo, "Tag.Name");
@   ^ support.type.ue4
@                     ^ keyword.operator
@                      ^^^ entity.name.type
@                           ^^^ string
@                                     ^ keyword.operator


UE_DEFINE_GAMEPLAY_TAG_STATIC(Foo, "Tag.Name");
@   ^ support.type.ue4
@                            ^ keyword.operator
@                             ^^^ entity.name.type
@                                  ^^^ string
@                                            ^ keyword.operator

UE_DEFINE_GAMEPLAY_TAG_COMMENT(Woo, "Tag.Name", "comment");
@   ^ support.type.ue4

junk struct X {};
@           ^ -entity

template <class X> struct Blah {};
@        ^ keyword.operator
@               ^ -entity
@                ^ keyword.operator
@                         ^^^^ entity.name.type

template <

>

@  ^ -meta.template-args

template <
    class X 
    UE_REQUIRES(std::blah<>)
@   ^^^^^^^^^^^ support.type.ue4
>
struct Blah {};

EWooble::xyz
@      ^^ keyword.operator
@        ^^^ support.constant.ue4

EWooble::Type
@        ^^^^ -constant

class C<void (*f)> : public B<>{} c;
@              ^ specialisation-args -entity 

class TypeName const* Region;
@     ^^^^^^^^^^^^^^^ -entity
@                     ^^^^^^ variable
class const TypeName* Region;
@     ^^^^^^^^^^^^^^^ -entity
@                     ^^^^^^ variable

void (*f)() = nullptr;
@  <- -entity
@             ^^^^^^^ constant


// known failure (not recognised as function specialisation)
void f<vector<int>>();

// todo (note: #if near top of file should help verify solutions)

#if 0
#if X
 blah
#endif
more blah
#endif

// hack so std templates are known to be types?, then fallback for std::
std::vector<int> v;
@  <- storage.type
 @  <- storage.type
@ ^ storage.type
@    ^^^^^^ storage.type
@           ^^^ storage.type

void f()
{
    std::invoke(f);
}


DEFINE_EXPRESSION_OPERATOR_NODE(CORE_API, FOr, 0xf15b8ea6, 0x3ef84c48, 0xb1366a99, 0x7e930cf1)
DEFINE_EXPRESSION_NODE_TYPE(FFiBToken,  0x03378490, 0x42D14E26, 0x8E95AD2F, 0x74567868)


// a bit broken - f<int treated a template argument

bool b = x < f<int>();
// SYNTAX TEST "Packages/C++ Test/C++ (Test).sublime-syntax"

USTRUCT(BlueprintType)
@ <- support.type.ue4
@^^^^^^ support.type.ue4
@      ^ keyword.operator
@                    ^ keyword.operator

struct FMyStruct
@      ^^^^^^^^^ entity.name.type

{

    GENERATED_USTRUCT_BODY()
@   ^^^^^^^^^^^^^^^^^^^^^^ support.type.ue4
@                         ^^ keyword.operator

};

USTRUCT(MinimalAPI)
@ <- support.type.ue4
@^^^^^^ support.type.ue4
@      ^ keyword.operator

struct FTestStruct

{

    GENERATED_BODY()
@   ^^^^^^^^^^^^^^ support.type.ue4
@                 ^^ keyword.operator

};

UENUM(BlueprintType)
@ <- support.type.ue4
@^^^^ support.type.ue4
@    ^ keyword.operator
@                  ^ keyword.operator

enum class EMyEnum
@          ^^^^^^^ entity.name.type

{

    Value1,
@   ^^^^^^ constant

    Value2 UMETA(DisplayName="X"),
@   ^^^^^^ constant
@          ^^^^^ support.type.ue4
@               ^ keyword.operator
@                            ^^^ string

    Value3 UMETA(Hidden)
@   ^^^^^^ constant
@          ^^^^^ support.type.ue4
@               ^ keyword.operator

};

UINTERFACE(MinimalAPI, BlueprintType)
@ <- support.type.ue4
@^^^^^^^^^ support.type.ue4
@         ^ keyword.operator

class UMyInterface : public UInterface

{

    GENERATED_UINTERFACE_BODY()
@   ^^^^^^^^^^^^^^^^^^^^^^^^^ support.type.ue4
@                            ^^ keyword.operator

};

UINTERFACE(Blueprintable)
@ <- support.type.ue4
@^^^^^^^^^ support.type.ue4
@         ^ keyword.operator

class UTestInterface : public UInterface

{

    GENERATED_BODY()
@   ^^^^^^^^^^^^^^ support.type.ue4
@                 ^^ keyword.operator

};

UCLASS(Abstract)
@ <- support.type.ue4
@^^^^^ support.type.ue4
@     ^ keyword.operator

class AMyActor : public AActor

{

    GENERATED_UCLASS_BODY()
@   ^^^^^^^^^^^^^^^^^^^^^ support.type.ue4
@                        ^^ keyword.operator

};

DEPRECATED(4.26, "X")
@ <- support.type.ue4
@^^^^^^^^^ support.type.ue4
@         ^ keyword.operator
@                ^^^ string

void OldFunction();

PROPERTY_BINDING_IMPLEMENTATION(FMyStruct, MyProperty)
@ <- support.type.ue4
@^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ support.type.ue4
@                              ^ keyword.operator

ENUM_CLASS_FLAGS(EMyFlags)
@ <- support.type.ue4
@^^^^^^^^^^^^^^^ support.type.ue4
@               ^ keyword.operator

enum class EMyFlags

{

    None = 0,

    Flag1 = 1 << 0,

    Flag2 = 1 << 1

};

ENUM_RANGE_BY_COUNT(EMyEnum, EMyEnum::First, EMyEnum::Count)
@ <- support.type.ue4
@^^^^^^^^^^^^^^^^^^ support.type.ue4
@                  ^ keyword.operator

ENUM_RANGE_BY_FIRST_AND_LAST(EMyEnum, EMyEnum::First, EMyEnum::Last)
@ <- support.type.ue4
@^^^^^^^^^^^^^^^^^^^^^^^^^^^ support.type.ue4
@                           ^ keyword.operator

ENUM_RANGE_BY_VALUES(EMyEnum, EMyEnum::Value1, EMyEnum::Value2)
@ <- support.type.ue4
@^^^^^^^^^^^^^^^^^^^ support.type.ue4
@                   ^ keyword.operator

ASSET_REGISTRY_ACCESSOR(MyAsset)
@ <- support.type.ue4
@^^^^^^^^^^^^^^^^^^^^^^ support.type.ue4
@                      ^ keyword.operator

ASSET_BUNDLE_DATA_ACCESSOR(MyBundle)
@ <- support.type.ue4
@^^^^^^^^^^^^^^^^^^^^^^^^^ support.type.ue4
@                         ^ keyword.operator

Expose_TNameOf(FMyStruct)
@ <- support.type.ue4
@^^^^^^^^^^^^^ support.type.ue4

BEGIN_JSON_SERIALIZER
@ <- support.type.ue4
@^^^^^^^^^^^^^^^^^^^^ support.type.ue4

END_JSON_SERIALIZER
@ <- support.type.ue4
@^^^^^^^^^^^^^^^^^^ support.type.ue4

JSON_SERIALIZE("X", MyField)
@ <- support.type.ue4
@^^^^^^^^^^^^^ support.type.ue4
@             ^ keyword.operator
@              ^^^ string

JSON_SERIALIZE_ARRAY_SERIALIZABLE("X", Items, FMyStruct)
@ <- support.type.ue4
@^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ support.type.ue4
@                                ^ keyword.operator

JSON_SERIALIZE_OBJECT_SERIALIZABLE("X", Data, FMyData)
@ <- support.type.ue4
@^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ support.type.ue4
@                                 ^ keyword.operator

BEGIN_ONLINE_JSON_SERIALIZER
@ <- support.type.ue4
@^^^^^^^^^^^^^^^^^^^^^^^^^^ support.type.ue4

END_ONLINE_JSON_SERIALIZER
@ <- support.type.ue4
@^^^^^^^^^^^^^^^^^^^^^^^^ support.type.ue4

SLATE_BEGIN_ARGS(SMyWidget)
@ <- storage.type.ue4
@^^^^^^^^^^^^^^^ storage.type.ue4
@               ^ keyword.operator

SLATE_END_ARGS()
@ <- storage.type.ue4
@^^^^^^^^^^^^^ storage.type.ue4
@             ^^ keyword.operator

SLATE_ARGUMENT(FText, Label)
@ <- storage.type.ue4
@^^^^^^^^^^^^^ storage.type.ue4
@             ^ keyword.operator

SLATE_ATTRIBUTE(FText, Text)
@ <- storage.type.ue4
@^^^^^^^^^^^^^^ storage.type.ue4
@              ^ keyword.operator

SLATE_EVENT(FOnClicked, OnClicked)
@ <- storage.type.ue4
@^^^^^^^^^^ storage.type.ue4
@          ^ keyword.operator

SLATE_DEFAULT_SLOT(FArguments, Content)
@ <- storage.type.ue4
@^^^^^^^^^^^^^^^^^ storage.type.ue4
@                 ^ keyword.operator

SLATE_NAMED_SLOT(FArguments, Header)
@ <- storage.type.ue4
@^^^^^^^^^^^^^^^ storage.type.ue4
@               ^ keyword.operator

SLATE_SUPPORTS_SLOT(FSlot)
@ <- storage.type.ue4
@^^^^^^^^^^^^^^^^^^ storage.type.ue4
@                  ^ keyword.operator

SLATE_SUPPORTS_SLOT_WITH_ARGS(FSlotArguments)
@ <- storage.type.ue4
@^^^^^^^^^^^^^^^^^^^^^^^^^^^^ storage.type.ue4
@                            ^ keyword.operator

DECLARE_DELEGATE(FMyDelegate)
@ <- support.type.delegate.ue4
@^^^^^^^^^^^^^^^ support.type.delegate.ue4
@               ^ keyword.operator
@                ^^^^^^^^^^^ entity.name.type

DECLARE_DELEGATE_OneParam(FMyDelegateOneParam, int32)
@ <- support.type.delegate.ue4
@^^^^^^^^^^^^^^^^^^^^^^^^ support.type.delegate.ue4
@                        ^ keyword.operator
@                         ^^^^^^^^^^^^^^^^^^^ entity.name.type

DECLARE_DELEGATE_TwoParams(FMyDelegateTwoParams, int32, float)
@ <- support.type.delegate.ue4
@^^^^^^^^^^^^^^^^^^^^^^^^^ support.type.delegate.ue4
@                         ^ keyword.operator
@                          ^^^^^^^^^^^^^^^^^^^^ entity.name.type

DECLARE_DELEGATE_RetVal(bool, FMyRetValDelegate)
@ <- support.type.delegate.ue4
@^^^^^^^^^^^^^^^^^^^^^^ support.type.delegate.ue4
@                      ^ keyword.operator
@                       ^^^^ storage.type
@                             ^^^^^^^^^^^^^^^^^ entity.name.type

DECLARE_MULTICAST_DELEGATE(FMyMulticastDelegate)
@ <- support.type.delegate.ue4
@^^^^^^^^^^^^^^^^^^^^^^^^^ support.type.delegate.ue4
@                         ^ keyword.operator
@                          ^^^^^^^^^^^^^^^^^^^^ entity.name.type

DECLARE_DYNAMIC_DELEGATE(FMyDynamicDelegate)
@ <- support.type.delegate.ue4
@^^^^^^^^^^^^^^^^^^^^^^^ support.type.delegate.ue4
@                       ^ keyword.operator
@                        ^^^^^^^^^^^^^^^^^^ entity.name.type

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMyDynamicMulticastDelegate)
@ <- support.type.delegate.ue4
@^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ support.type.delegate.ue4
@                                 ^ keyword.operator
@                                  ^^^^^^^^^^^^^^^^^^^^^^^^^^^ entity.name.type

DECLARE_EVENT(UMyClass, FMyEvent)
@ <- support.type.event.ue4
@^^^^^^^^^^^^ support.type.event.ue4
@            ^ keyword.operator
@             ^^^^^^^^ storage.type
@                       ^^^^^^^^ entity.name.type


DECLARE_MULTICAST_DELEGATE_WITH_SIGNATURE(FMySignatureDelegate, void())
@ <- support.type.delegate.ue4
@^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ support.type.delegate.ue4
@                                        ^ keyword.operator

DEFINE_LATENT_AUTOMATION_COMMAND(FMyTestCommand)
@ <- support.type.command.ue4
@^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ support.type.command.ue4
@                               ^ keyword.operator
@                                ^^^^^^^^^^^^^^ entity.name.type

DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FMyTestOneParam, int32, Value)
@ <- support.type.command.ue4
@^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ support.type.command.ue4
@                                             ^ keyword.operator
@                                              ^^^^^^^^^^^^^^^ entity.name.type

// probably should define the types
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FMyTest, "MyCategory.MyTest", EAutomationTestFlags::ApplicationContextMask)
@ <- support.type.ue4
@^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ support.type.ue4
@                               ^ keyword.operator
@                                ^^^^^^^ storage.type

IMPLEMENT_COMPLEX_AUTOMATION_TEST(FMyComplexTest, "MyCategory.MyComplexTest", EAutomationTestFlags::ApplicationContextMask)
@ <- support.type.ue4
@^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ support.type.ue4
@                                ^ keyword.operator
@                                 ^^^^^^^^^^^^^^ storage.type

UE_DECLARE_GAMEPLAY_TAG_EXTERN(MyGameplayTag)
@ <- support.type.ue4
@^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ support.type.ue4
@                             ^ keyword.operator
@                              ^^^^^^^^^^^^^ storage.type

UE_DEFINE_GAMEPLAY_TAG(MyTag, "X")
@ <- support.type.ue4
@^^^^^^^^^^^^^^^^^^^^^ support.type.ue4
@                     ^ keyword.operator
@                      ^^^^^ entity.name.type
@                             ^^^ string

UE_DEFINE_GAMEPLAY_TAG_STATIC(MyStaticTag, "X")
@ <- support.type.ue4
@^^^^^^^^^^^^^^^^^^^^^^^^^^^^ support.type.ue4
@                            ^ keyword.operator
@                             ^^^^^^^^^^^ entity.name.type
@                                          ^^^ string

UE_DEFINE_GAMEPLAY_TAG_COMMENT(MyCommentTag, "X", "Y")
@ <- support.type.ue4
@^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ support.type.ue4
@                             ^ keyword.operator
@                              ^^^^^^^^^^^^ entity.name.type
@                                            ^^^ string

PERSISTENCE_FRAMEWORK_DECLARE_GAMEPLAY_TAG_EXTERN(MyPersistenceTag)
@ <- support.type.ue4
@^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ support.type.ue4
@                                                ^ keyword.operator
@                                                 ^^^^^^^^^^^^^^^^ storage.type

PERSISTENCE_FRAMEWORK_DEFINE_GAMEPLAY_TAG(MyPersistenceTag, "Persistence.MyTag")
@ <- support.type.ue4
@^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ support.type.ue4
@                                        ^ keyword.operator
@                                         ^^^^^^^^^^^^^^^^ entity.name.type

IMPLEMENT_MODULE(FDefaultModuleImpl, MyModule)
@ <- support.type.ue4
@^^^^^^^^^^^^^^^ support.type.ue4
@               ^ keyword.operator

IMPLEMENT_GAME_MODULE(FMyGameModule, MyGame)
@ <- support.type.ue4
@^^^^^^^^^^^^^^^^^^^^ support.type.ue4
@                    ^ keyword.operator

IMPLEMENT_PRIMARY_GAME_MODULE(FDefaultGameModuleImpl, MyGame, "MyGame")
@ <- support.type.ue4
@^^^^^^^^^^^^^^^^^^^^^^^^^^^^ support.type.ue4
@                            ^ keyword.operator

DEFINE_LOG_CATEGORY(LogMyModule)
@ <- support.type.ue4
@^^^^^^^^^^^^^^^^^^ support.type.ue4
@                  ^ keyword.operator

DEFINE_LOG_CATEGORY_STATIC(LogMyStatic, Log, All)
@ <- support.type.ue4
@^^^^^^^^^^^^^^^^^^^^^^^^^ support.type.ue4
@                         ^ keyword.operator

DECLARE_LOG_CATEGORY_EXTERN(LogMyExtern, Log, All)
@ <- support.type.ue4
@^^^^^^^^^^^^^^^^^^^^^^^^^^ support.type.ue4
@                          ^ keyword.operator

FUNCTION_CHECK_RETURN(MyFunction())
@ <- support.type.ue4
@^^^^^^^^^^^^^^^^^^^^ support.type.ue4
@                    ^ keyword.operator

} need fixing
 @ <- -meta.function

template <typename T
    UE_REQUIRES(std::is_integral_v<T>)>
@   ^^^^^^^^^^^ support.type.ue4
@              ^ keyword.operator

UE_IMPLEMENT_STRUCT(FMyStruct)
@ <- support.type.ue4
@^^^^^^^^^^^^^^^^^^ support.type.ue4
@                  ^ keyword.operator

DEFINE_EXPRESSION_OPERATOR_NODE(CORE_API, FMyOperator, 0x12345678, 0x9abcdef0, 0x11111111, 0x22222222)
@ <- support.type.ue4
@^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ support.type.ue4
@                              ^ keyword.operator

DEFINE_EXPRESSION_NODE_TYPE(FMyNodeType, 0x12345678, 0x9abcdef0, 0x11111111, 0x22222222)
@ <- support.type.ue4
@^^^^^^^^^^^^^^^^^^^^^^^^^^ support.type.ue4
@                          ^ keyword.operator

void MyFunction()

{

    SCOPE_CYCLE_COUNTER(STAT_MyFunction)
@   ^^^^^^^^^^^^^^^^^^^ support.type.ue4
@                      ^ keyword.operator

}

EOS_DECLARE_FUNC(EOS_EResult) EOS_Auth_Login;
@ <- support.type.eos
@^^^^^^^^^^^^^^^ support.type.eos
@               ^ keyword.operator

UCLASS(BlueprintType, Category="X")
@ <- support.type.ue4
@^^^^^ support.type.ue4
@     ^ keyword.operator
@                              ^^^ string

class UMyObject : public UObject

{

    GENERATED_BODY()
@   ^^^^^^^^^^^^^^ support.type.ue4
@                 ^^ keyword.operator

    UPROPERTY(BlueprintReadWrite, Category="X")
@   ^^^^^^^^^ support.type.ue4
@            ^ keyword.operator
@                                          ^^^ string

    int32 MyProperty;

    UFUNCTION(BlueprintCallable, Category="X")
@   ^^^^^^^^^ support.type.ue4
@            ^ keyword.operator
@                                         ^^^ string

    void MyFunction();

};

TEXT("abc")
@ ^ comment

TEXT("abc
@        ^ invalid

TEXT("abc" \
@          ^ -invalid
    "woo" )
@   ^ string

"%a %ls"
@^^ -keyword.control
@   ^^^ keyword.control
