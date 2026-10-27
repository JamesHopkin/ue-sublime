@syntax Packages/C#/C#.sublime-syntax
@comment //

# C# syntax-test spec — source of truth for syntax_test_csharp.cs.
# Generate:  gen_syntax_test.py syntax_test_csharp.spec -o syntax_test_csharp.cs
# Check:     gen_syntax_test.py syntax_test_csharp.spec -o syntax_test_csharp.cs --check
# Assertions use substrings; keep tokens on a line unambiguous (or use tok#N).

# ===== comments + runaway recovery (design §8.6) =====
# An apostrophe / quote inside a // comment must not open a literal that leaks.
> // it's a comment with a " quote
= "//" comment.line
> int afterComment = 1;
= int storage.type
= 1 constant.numeric

> /// <summary>Doc.</summary>
= "///" comment.block.documentation
= summary entity.name.tag

# ===== string forms + EOL recovery (§8.7) =====
# Code after the string keeps real scopes -> the string closed cleanly.
> string s = "ok"; int n2 = 5;
= string storage.type
= "ok" string.quoted.double
= int storage.type
= 5 constant.numeric
> char c = '\n';
= "\n" constant.character.escape
> var vb = @"C:\not\escaped";
= "C:" string.quoted.double
> var it = $"hi {who}!";
= "hi " string.quoted.double
= "{" punctuation.section.interpolation.begin
> var rw = """triple""";
= triple string.quoted.triple

# ===== numbers (most-specific base first) =====
> int dec = 1_000;
= 1_000 constant.numeric
> int hex = 0xFF_00;
= 0xFF_00 constant.numeric.hex
> int bin = 0b1010_0101;
= 0b1010_0101 constant.numeric.binary
> double flt = 6.022e23;
= 6.022e23 constant.numeric
> decimal mny = 19.99m;
= 19.99m constant.numeric

# ===== keyword bands =====
> if (ready) return; else throw e;
= if keyword.control
= return keyword.control
= else keyword.control
= throw keyword.control
> public static readonly partial async
= public storage.modifier
= static storage.modifier
= readonly storage.modifier
= partial storage.modifier
= async storage.modifier
> const int x = 0; bool flag; string str;
= const storage.modifier
= int storage.type
= bool storage.type
= string storage.type
> obj is Thing && a as B;
= is keyword.operator.word
= as keyword.operator.word
> return true || false || null;
= true constant.language
= false constant.language
= null constant.language
> this.value = base.ok;
= this variable.language
= base variable.language

# ===== type heuristic: `Type name` only, members stay default (§7, §8.12) =====
> IProcessResult RunResult;
= IProcessResult storage.type
= RunResult source.cs - storage.type
> var w = new LogEventParser();
= new keyword.operator.word
= LogEventParser storage.type
> Console.WriteLine(arg);
= Console source.cs - storage.type
= WriteLine variable.function
> total = obj.Field + Helper.Run();
= Field variable.other.member
= Run variable.function

# ===== operators =====
> a => b ?? c?.d;
= "=>" keyword.operator
= "??" keyword.operator
= "?." keyword.operator

# ===== namespace + using directives =====
> namespace Demo.App;
= namespace keyword.declaration.namespace
= Demo entity.name.namespace
= App entity.name.namespace
> using System.Text;
= using keyword.control.import
= System entity.name.namespace
= Text entity.name.namespace
> using static System.Math;
= static storage.modifier

# ===== attribute must NOT derail the class decl that follows (regression) =====
# Previously `Help(` matched function-decl, trapping `class` under meta.function.
# (Bodies are required: a bodyless decl leaves its context open and swallows the
#  next line — that is correct grammar behaviour, §8.9, not a bug to test against.)
> [Help("Builds a Plugin")]
= Help support.type.decorator
= "Builds a Plugin" string.quoted.double
> public class ValkyrieCloudBuild : BuildCommand { }
= class storage.type
= ValkyrieCloudBuild entity.name.type
= BuildCommand entity.other.inherited-class

# ===== other type declarations =====
> interface IRunnable { }
= interface storage.type
= IRunnable entity.name.type
> record struct Point(int X, int Y);
= record storage.type
= struct storage.type
= Point entity.name.type
> enum Level { Low, High }
= enum storage.type
= Level entity.name.type
= Low constant.other.enum
= High constant.other.enum

# ===== members: property accessors, constructor + param type =====
> public int Count { get; set; }
= int storage.type
= get storage.modifier
= set storage.modifier
> public Widget(InputType arg) { }
= Widget entity.name.function
= InputType storage.type
= arg source.cs - storage.type

# ===== method body: prototype active inside (§8.8), sibling decl after } (§8.1) =====
> void Body()
= void storage.type
= Body entity.name.function
> {
> string inBody = "literal";
= string storage.type
= "literal" string.quoted.double
> int num = 42;
= int storage.type
= 42 constant.numeric
> }
> int sibling = 9;
= int storage.type
= sibling source.cs - storage.type
= 9 constant.numeric

# ===== preprocessor =====
> #region Setup
= "#" punctuation.definition.keyword
= region keyword.control.preprocessor
> #endif
= endif keyword.control.preprocessor
