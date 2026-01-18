// SYNTAX TEST "Typescript.sublime-syntax"

url.replace(/^file:\/\//, "")

/ xxx +*?{0} $^[ \*\{ \S\D (?> /g;
// ^ string.regexp
//    ^^^^^^ string.regexp constant 
//           ^^^ string.regexp constant.character.escape 
//               ^^^^ string.regexp string
//                    ^^^^ string.regexp support
//                         ^^^ string.regexp entity

export const SchemaDocDecoder = validation.object({
  /\d+\.\d+\.\.d+/

/ (?:abc) a\{\|0} (?: woo) /

/ac/

function g() {
  const f = () => /test/.test(x);
  return /test/.test(x);
}

/** any need for regex following open brace? */

abc[/def/]

/\//
'\n'

/\\/g more stuff


      - meta_scope: string
      - match: '\\[\\bnr/|()*+?.{}^$]'
        scope: constant.character.escape
      - match: '[\[\]|^$.]'
        scope: constant.character.escape
      - match: '[*?+]'
        scope: constant
      - match: '\{[\d,]+\}'
        scope: constant
      - match: '\((?:\?(?::|!|<=|>=|<!|>))?|\)'
        scope: entity
      - match: '\\[dDsSwW]' 
        scope: support
      - match: '/([igmsuy]*)'
        scope: string.regexp


     this._maxRetries = Math.ceil(maxRetryTimeMs / _ctx.maxPollInterval);
     this._maxLastRvnSeenCnt = Math.floor(_ctx.ttl / _ctx.maxPollInterval) + 1;
     return Math.round((now - acquiredAt)/1000);
             }, (updateErr ? 5000 : (ttl/2)));
     const ddbCleanupAfter = Math.floor((new Date().getTime() + ttl) / 1000);
             }, ttl/2);

/(?<=[=({\[,:;!?>]|return|throw|case|^)/

// Storage type tests
const myVar = 10;
// <- storage.type
let anotherVar = "hello";
// <- storage.type
var oldStyle = true;
// <- storage.type
function myFunction() {}
// <- storage.type
class MyClass {}
// <- storage.type
interface MyInterface {}
// <- storage.type
type MyType = string;
// <- storage.type
enum MyEnum { A, B }
// <- storage.type

// Entity name tests
class UserService {
//    ^^^^^^^^^^^ entity.name.type
  constructor() {}
}

interface IUser {
//        ^^^^^ entity.name.type
  name: string;
}

type Person = { age: number };
//   ^^^^^^ entity.name.type

function getUserName() {
//       ^^^^^^^^^^^ entity.name.function
  return "John";
}

const getAge = () => 25;
// known failure
//-   ^^^^^^ entity.name.function

// Typed const as entity.name.function
export const ProductDefinitionCacheEntryDecoder: validation.Decoder<ProductDefinitionCacheEntry> = validation.object({
//           ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ entity.name.function

// Keyword operator tests
const sum = 1 + 2;
//            ^ keyword.operator
const result = a === b;
//               ^^^ keyword.operator
const arrow = () => null;
//               ^^ keyword.operator
const spread = [...items];
// todo: fix this soon!
//-              ^^^ keyword.operator
const assign = x = 5;
//               ^ keyword.operator

// String tests
const singleQuote = 'hello';
//                  ^^^^^^^ string
const doubleQuote = "world";
//                  ^^^^^^^ string
const template = `value: ${x}`;
//               ^^^^^^^^ string
//                       ^^^^ meta.template

// Nested template string test
const nested = `outer ${`inner ${x}`} end`;
//             ^^^^^^^ string.template
//                    ^^ punctuation.definition.template-expression
//                      ^^^^^^^ string.template
//                             ^^ punctuation.definition.template-expression
//                               ^ source.js.embedded.expression 
//                                ^ punctuation.definition.template-expression
//                                  ^ punctuation.definition.template-expression.end
//                                    ^^^^ string.template

// Comment tests
// This is a single line comment
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ comment

/* This is a
   multi-line comment */
// ^^^^^^^^^^^^^^^^^^^^^ comment