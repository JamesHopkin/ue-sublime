@syntax TypeScript.sublime-syntax

# ===========================================================================
# TypeScript (Claude v3) — syntax tests (interleaved-substring source)
#
# Permanent source of truth. Build the runnable Sublime test with:
#   python3 tools/gen_syntax_test.py tests/typescript_v3.spec -o syntax_test_typescript_v3.ts
# Check it is up to date (CI / pre-commit):
#   python3 tools/gen_syntax_test.py tests/typescript_v3.spec -o syntax_test_typescript_v3.ts --check
#
# Format: `>` source line, `=` <substring> <scope...> asserts on the line above.
# A bare substring asserts EVERY occurrence; `tok#N` targets the Nth.
# ===========================================================================

# ---------------------------------------------------------------------------
# AGENT_PROMPT self-check scenarios (1-8) — formerly "mentally trace through"
# ---------------------------------------------------------------------------

# 1. enum pops cleanly; the following declaration is recognized fresh
> enum Color { Red, Green }
=   enum    storage.type
=   Color   entity.name.type
=   Red     constant
=   Green   constant
> function afterEnum() {}
=   function    storage.type
=   afterEnum   entity.name.function

# 2. function body terminates; a trailing `};` is flagged redundant
> function withBody(): string {};
=   function   storage.type
=   withBody   entity.name.function
=   string     storage.type
=   ;          invalid.illegal.redundant-semicolon
> afterBody();
=   afterBody   entity.name.function

# 3. export {} block pops; Q1 mandates meta.preprocessor.c inside it
> export { Alpha, Beta };
=   export   keyword.control.export
=   Alpha    meta.preprocessor.c
=   ,        keyword.operator
> afterExport();
=   afterExport   entity.name.function

# 4. regex character classes \d \w are `support`, not `string`
> /\d+\.\w*/g
=   \d   string.regexp support
=   \w   string.regexp support
=   +    string.regexp constant
=   *    string.regexp constant

# 5. template ${ } carry explicit punctuation scopes (section 12.4)
> `hello ${world}`
=   `#1     punctuation.definition.string.template.begin
=   hello   string.template
=   ${      punctuation.definition.template-expression.begin
=   }       punctuation.definition.template-expression.end

# 6. multi-char operators are not split by the single-char catch-all
> a?.b ?? c
=   ?.   keyword.operator
=   ??   keyword.operator
> x => y
=   =>   keyword.operator

# 7. control keyword `if` is not matched as a function declaration (F1)
> if (x) {}
=   if   keyword.control
=   (    keyword.operator

# 8. a multi-line import survives the newlines (F19)
> import {
=   import   keyword.control.import
>   Member
=   Member   meta.preprocessor.c
> } from 'mod';
=   from   keyword.operator
=   mod    string.single-quote
> afterImport();
=   afterImport   entity.name.function

# ---------------------------------------------------------------------------
# Flag-fix regressions
# ---------------------------------------------------------------------------

# F25: a bodyless generic return type closes the function scope, so the next
# member is parsed as a declaration (entity), not a call.
> class Woo {
=   class   storage.type
=   Woo     entity.name.type
>     f(): Promise<void>;
=   f         entity.name.function
=   Promise   storage.type
=   void      storage.type
>     g();
=   g         entity.name.function
> }

# F25 regression: same shape but WITH a body — next member still a declaration.
> class Bod {
=   Bod   entity.name.type
>     j(): number { return 1; }
=   j        entity.name.function
=   number   storage.type
=   return   keyword.control
>     k();
=   k        entity.name.function
> }

# F25 inside an interface: chained bodyless signatures.
> interface IShape {
=   interface   storage.type
=   IShape      entity.name.type
>     area(): number;
=   area     entity.name.function
=   number   storage.type
>     name(): string;
=   name     entity.name.function
=   string   storage.type
> }

# F8: spread / rest operator
> const items = [...rest];
=   const   storage.type
=   ...     keyword.operator.spread

# F9 / M13-M15: binary, octal, hex, separators, BigInt
> const nums = [0b1010, 0o17, 0xFF, 1_000, 10n];
=   0b1010   constant.numeric
=   0o17     constant.numeric
=   0xFF     constant.numeric
=   1_000    constant.numeric
=   10n      constant.numeric

# F20 / M10: import * and import type — keyword.operator inside the block
> import * as ns from 'lib';
=   import   keyword.control.import
=   *        keyword.operator
=   as       keyword.operator
> import type { T } from 'lib';
=   type   keyword.operator

# M3: private fields
> this.#count;
=   this     variable.language
=   #count   variable.other.property

# F4: string escape sequences (\t and \uNNNN)
> const s = "a\tb\u0041c";
=   \t       constant.character.escape
=   \u0041   constant.character.escape

# constant.language values
> const flags = [true, false, null, undefined];
=   true        constant.language
=   false       constant.language
=   null        constant.language
=   undefined   constant.language

# storage.modifier keywords
> class Access { private a; static b; }
=   Access    entity.name.type
=   private   storage.modifier
=   static    storage.modifier

# Decorators — with and without parens
> @Component({})
=   @Component   support.type.decorator
> @Input
=   @Input   support.type.decorator

# Q5: TODO highlighting in comments
> // TODO: fix later
=   TODO   markup.bold

# Q1 / F29: doc-comment punctuation (/**, *, */) is comment-styled like the rest of
# the comment; only the text carries the meta.preprocessor.c highlight. meta_scope
# covers the begin/end tokens, so the /** opener needs its own comment scope.
> /** doc here */
=   /**   comment
=   doc   meta.preprocessor.c
=   */    comment
> /**
=   /**   comment
>   * Handles the error
=   *         comment
=   Handles   meta.preprocessor.c
>   */
=   */   comment

# Regex-vs-division ambiguity (methodology §9): leading / opens a regex...
> const re = /ab+c/gi;
=   /#1    punctuation.definition.string.begin
=   ab+c   string.regexp
# ...but a division / after an identifier stays an operator.
> const q = a / b;
=   /   keyword.operator

# Substring assertions hit every occurrence by default (punctuation)
> arr[0] + arr[1];
=   [   keyword.operator
=   ]   keyword.operator
=   +   keyword.operator

# F26: a stray/unterminated quote recovers at EOL instead of swallowing the file.
# The line-3 assertion is the regression guard — pre-fix the open string on line 1
# ran to EOF, so `const` here was highlighted as string.single-quote.
> const broken = 'oops
=   const   storage.type
=   oops    string.single-quote
> const fine = 1;
=   const   storage.type
=   1       constant.numeric

# F26 + import swallow: an apostrophe in the lines after a semicolon-less import
# can no longer run away across the rest of the file.
> import Thing from 'mod'
=   import   keyword.control.import
> oh it's prose
=   oh   meta.preprocessor.c
> const back = 2;
=   const   storage.type

# F27: // and /* */ comments inside a multi-line import are scoped as comments,
# stacked under meta.preprocessor.c. `note` is past the apostrophe, so it also
# guards F26 (the apostrophe must stay inside the comment, not open a string).
> import {
=   import   keyword.control.import
>   Foo, // it's a note
=   note   meta.preprocessor.c comment
>   Bar /* blocky */
=   blocky   meta.preprocessor.c comment
> } from 'x';
=   from   keyword.operator
> const afterImport2 = 1;
=   const   storage.type

# F27: same for // inside an export block
> export {
=   export   keyword.control.export
>   Thing // trailing
=   trailing   meta.preprocessor.c comment
> };
> const afterExport2 = 2;
=   const   storage.type

# M21: const/let/var arrow functions — the binding name is a definition, but only
# when a => is confirmed on the line. Bodies parse as expressions (calls stay
# support.function), never as definition sites.
> const add = (a, b) => a + b;
=   const   storage.type
=   add     entity.name.function
=   =>      keyword.operator
# bare single-param arrow
> const id = x => x;
=   id   entity.name.function
# body guard: a call in an unbraced body is support.function, NOT a definition
> const k = () => callThing(x);
=   k           entity.name.function
=   callThing   support.function
# braced body works; the next statement is still recognized as its own decl
> const run = () => { return doWork(); };
=   run      entity.name.function
=   return   keyword.control
=   doWork   support.function
> function afterArrow() {}
=   afterArrow   entity.name.function
# NEGATIVE: a comma/paren expression is NOT an arrow — PascalCase name must fall
# through to storage.type (M21's entity.name.function would override it if it fired).
> const Pair = (a, b);
=   Pair   storage.type

# M21 regression guard: prototype-provided rules (comments, strings, numbers) must
# still work INSIDE a function body. M21's arrow trigger lived in `common`, which is
# reachable from the prototype (via template ${}); pushing from there pulled
# function-block into the prototype's reachable set, which disables prototype
# injection there — silently killing in-function comments/strings/numbers.
> function withInner() {
=   function    storage.type
=   withInner   entity.name.function
>   // a line comment in a function
=   comment   comment
>   /* a block comment in a function */
=   block   comment
>   const s = "in-func string";
=   string   string.double-quote
>   const n = 42;
=   42   constant.numeric
>   const cb = (e) => e;
=   cb   entity.name.function
> }
# a comment in an arrow's braced body must also be a comment
> const wrap = () => { /* inner */ return 1; };
=   wrap     entity.name.function
=   inner    comment
=   return   keyword.control