
# Course project: Lexical Analyzer

<!-- MarkdownTOC -->

- [Project Requirement](#project-requirement)
- [Symbols](#symbols)
- [Requirement 1: Preprocess](#requirement-1-preprocess)
    - [What shall be done during this procedure](#what-shall-be-done-during-this-procedure)
- [Requirement 2: Identify all the tokens](#requirement-2-identify-all-the-tokens)
    - [What shall be done during this procedure](#what-shall-be-done-during-this-procedure-1)
- [Analyses](#analyses)
    - [The source character set](#the-source-character-set)
    - [Limitations](#limitations)
    - [What is the scope of a *token*](#what-is-the-scope-of-a-token)
    - [What is the scope of a *processing token*](#what-is-the-scope-of-a-processing-token)
    - [How to identify a *preprocessing-token* and  a *token*](#how-to-identify-a-preprocessing-token-and--a-token)
- [Implement](#implement)
- [Reference](#reference)

<!-- /MarkdownTOC -->


### Project Requirement
+ User select a C source file as input
+ This system will output a source file which is preprocessed (With the comment, new line token, white-space characters deleted).
+ This system will identify all *token* in the source file and classifies them according to the type they are.
+ This system will read data from a file in the disk which content is a C programming language instead of pre-storing it in the program.

### Symbols
+ All the form is the same meaning with what is defined in C11 International standard (ISO/IEC 9899:2011) 

### Requirement 1: Preprocess

#### What shall be done during this procedure
1. Trigraph will be replaced by corresponding single-character.
1. Each instance of a backslash character (\\) immediately followed by a new-line character will be deleted. Only the one in the end of file will be retained.
1. Preprocessing tokens will be identified.
1. White-space characters and comments shall be deleted as more as possible and a single blank will take the place.
1. The macro shall be identified and be replaced.
1. Headers or source files in `#include` will be preprocessing from step 1 \- 5.
1. Adjacent string literal tokens will be concatenated.
1. All preprocessing tokens will be separated with a blank in the output stream.

### Requirement 2: Identify all the tokens

#### What shall be done during this procedure
1. White-space characters separating tokens are no longer significant.
1. Each preprocessing token will be converted into a token.
1. The list of tokens will be printed to the standard output device.

### Analyses

#### The source character set
+ the 26 letters of the Latin alphabet (including the uppercase and lowercase):
    * **a** **A** **b** **B** **c** **C** **d** **D** **e** **E** **f** **F** **g** **G** **h** **H** **i** **I** **j** **J** **k** **K** **l** **L** **m** **M** **n** **N** **o** **O** **p** **P** **q** **Q** **r** **R** **s** **S** **t** **T** **u** **U** **v** **V** **w** **W** **x** **X** **y** **Y** **z** **Z**
+ the 10 decimal digits:
    * **0** **1** **2** **3** **4** **5** **6** **7** **8** **9**
+ the following 29 graphic characters:
    * **\!** **"** **\#** **%** **&** **'** **\(** **\)** **\*** **\+** **,** **\-** **\.** **/** **:** **;** **<** **=** **>** **?** **\[** **\\** **\]** **^** **\_** **\{** **|** **\}** **~**
+ Trigraph sequence:
    * **??=** **??\(** **??/** **??\)** **??'** **??<** **??!** **??>** **??\-**
+ Multibyte character

#### Limitations
+ 127 nesting levels of blocks
+ 63 nesting levels of conditional inclusion
+ 12 pointer, array, and function declarators (in any combinations) modifying an arithmetic, structure, union, or **void** type in a declaration
+ 63 nesting levels of parenthesized declarators within a full declarator
+ 63 nesting levels of parenthesized expressions within a full expression
+ 63 significant initial characters in an internal identifier or a macro name (each universal character name or extended source character is considered a single character)
+ 31 significant initial characters in an external identifier (each universal character name specifying a short identifier of 0000FFFF or less is considered 6 characters, each universal character name specifying a short identifier of 00010000 or more is considered 10 characters, and each extended source character is considered the same number of characters as the corresponding universal character name, if any)
+ 4095 external identifiers in one translation unit
+ 511 identifiers with block scope declared in one block
+ 4095 macro identifiers simultaneously defined in one preprocessing translation unit
+ 127 parameters in one function definition
+ 127 arguments in one function call
+ 127 parameters in one macro definition
+ 127 arguments in one macro invocation
+ 4095 characters in a logical source line
+ 4095 characters in a string literal (after concatenation)
+ 65535 bytes in an object (in a hosted environment only) 
+ 15 nesting levels for **\#included** files 
+ 1023 **case** labels for a **switch** statement (excluding those for any nested **switch** statements)
+ 1023 members in a single structure or union
+ 1023 enumeration constants in a single enumeration
+ 63 levels of nested structure or union definitions in a single struct-declaration-list

#### What is the scope of a *token*
+ According to C11, a *token* is the minimal lexical element in the translation after preprocessing.
+ *token*:
    * *keyword*
    * *identifier*
    * *constant*
    * *string-literal*
    * *punctuator*
+ *keyword*: one of
    -  **auto**  **break** **case** **char** **const** **continue** **default** **do** **double** **else** **enum** **extern** **float** **for** **goto** **if** **inline** **int** **long** **register** **restrict** **return** **short** **signed** **sizeof** **static** **struct** **switch** **typedef** **union** **unsigned** **void** **volatile** **while** **_Alignas** **\_Alignof** **\_Atomic** **\_Bool** **\_Complex** **\_Generic** **\_Imaginary** **\_Noreturn** **\_Static\_assert** **\_Thread\_local**
* *identifier*:
    * *identifier-nondigit*
    * *identifier identifier-nondigit*
    * *identifier digit*
+ identifier-nondigit:
    * *nondigit*
    * *universal-character-name*
    * other implementation-defined characters
* *nondigit*: one of
    - **a** **A** **b** **B** **c** **C** **d** **D** **e** **E** **f** **F** **g** **G** **h** **H** **i** **I** **j** **J** **k** **K** **l** **L** **m** **M** **n** **N** **o** **O** **p** **P** **q** **Q** **r** **R** **s** **S** **t** **T** **u** **U** **v** **V** **w** **W** **x** **X** **y** **Y** **z** **Z** **_**
* *digit*: one of
    - **0** **1** **2** **3** **4** **5** **6** **7** **8** **9**
* *universal-character-name*:
    - **\\u** hex-quad
    - **\\U** hex-quad
+ *hex-quad*:
    * *hexadecimal-digit* *hexadecimal-digit* *hexadecimal-digit* *hexadecimal-digit*
    * Note: Each universal character name in an identifier shall designate a character whose encoding in **ISO/IEC 10646** falls into one of the ranges specified in D.1. (A universal character name shall not specify a character whose short identifier is less than 00A0).
+ *constant*:
    - *integer-constant*:
    - *floating-constant*
    - *enumeration-constant*
    - *character-constant*
+ *integer-constant*:
    * *decimal-constant* *integer-suffix* (opt)
    * *octal-constant* *integer-suffix* (opt)
    * *hexadecimal-constant* *integer-suffix* (opt)
+ *decimal-constant*:
    + *nonzero-digit*
    + *decimal-constant* *digit*
+ *octal-constant*:
    * **0**
    * *octal-constant* *octal-digit*
+ *hexadecimal-constant*:
    * *hexadecimal-prefix* *hexadecimal-digit*
    * *hexadecimal-constant* *hexadecimal-digit*
+ *hexadecimal-prefix*: one of
    * **0x** **0X**
+ *nonzero-digit*: one of
    * **1** **2** **3** **4** **5** **6** **7** **8** **9**
+ *octal-digit*: one of
    * **0** **1** **2** **3** **4** **5** **6** **7**
+ *hexadecimal-digit*: one of
    * **0** **1** **2** **3** **4** **5** **6** **7** **8** **9** **a** **A** **b** **B** **c** **C** **d** **D** **e** **E** **f** **F**
+ *integer-suffix*:
    * *unsigned-suffix* *long-suffix* (opt)
    * *unsigned-suffix* *long-long-suffix*
    * *long-suffix* *unsigned-suffix* (opt)
    * *long-long-suffix* *unsigned-suffix*(opt)
+ *unsigned-suffix*: one of
    * **u** **U**
+ *long-suffix*: one of
    * **l** **L**
+ *long-long-suffix*: one of
    * **ll** **LL**
+ *floating-constant*:
    * *decimal-floating-constant*
    * *hexadecimal-floating-constant*
+ *decimal-floating-constant*:
    * *fractional-constant* *exponent-part* (opt) *floating-suffix* (opt)
    * *digit-sequence* *exponent-part* *floating-suffix* (opt)
+ *hexadecimal-floating-constant*:
    * *hexadecimal-prefix* *hexadecimal-fractional-constant* *binary-exponent-part* *floating-suffix* (opt)
    * *hexadecimal-prefix* *hexadecimal-digit-sequence* *binary-exponent-part* *floating-suffix* (opt)
+ *fractional-constant*:
    * *digit-sequence* (opt) **\.** *digit-sequence*
    * *digit-sequence* **\.**
* *exponent-part*:
    - **e** *sign* (opt) digit-sequence
    - **E** *sign* (opt) digit-sequence
* *sign*: one of
    - **\+** **\-**
* *digit-sequence*:
    - *digit*
    - *digit-sequence* *digit*
* *hexadecimal-fractional-constant*:
    * *hexadecimal-digit-sequence* (opt) **\.** *hexadecimal-digit-sequence*
    * *hexadecimal-digit-sequence* **\.**
* *binary-exponent-part*:
    - **p** *sign* (opt) digit-sequence
    - **P** *sign* (opt) digit-sequence
* *hexadecimal-digit-sequence*:
    - *hexadecimal-digit*
    - *hexadecimal-digit-sequence* *hexadecimal-digit*
* *floating-suffix*: one of
    - **f** **l** **F** **L**
* *enumeration-constant*:
    - *identifier*
* *character-constant*:
    - **'** *c-char-sequence* **'**
    - **L'** *c-char-sequence* **'**
    - **u'** *c-char-sequence* **'**
    - **U'** *c-char-sequence* **'**
+ *c-char-sequence*:
    * *c-char*
    * *c-char-sequence* *c-char*
* *c-char*:
    - any member of the source character set expect the single-quote, backslash, or new-line character
    - *escape-sequence*
* *escape-sequence*:
    - *simple-escape-sequence*
    - *octal-escape-sequence*
    - *hexadecimal-escape-sequence*
    - *universal-character-name*
+ *simple-escape-sequence*: one of
    * **\\'** **\\"** **\\?** **\\\\** **\\a** **\\b** **\\f** **\\n** **\\r** **\\t** **\\v**
+ *octal-escape-sequence*:
    * **\\** *octal-digit*
    * **\\** *octal-digit* *octal-digit*
    * **\\** *octal-digit* *octal-digit* *octal-digit*
+ *hexadecimal-escape-sequence*:
    * **\x** *hexadecimal-digit* 
    * *hexadecimal-escape-sequence* *hexadecimal-digit*
+ *string-literal*:
    * encoding-prefix(opt) **"** *s-char-sequence* (opt) **"**
* *encoding-prefix*:
    - **u8**
    - **u**
    - **U**
    - **L**
* *s-char-sequence*:
    - *s-char*
    - *s-char-sequence* *s-char*
* *s-char*:
    - any member of the source character set expect the double-quote, backslash, or new-line character
    - *escape-sequence*
+ *punctuator*: one of
    * **\[** **\]** **\(** **\)** **\{** **\}** **\.** **\-\>** **\+\+** **\-\-** **&** **\*** **\+** **\-** **~** **\!** **/** **%** **<<** **\>\>** **<** **\>** **<=** **\>=** **==** **\!=** **^** **|** **&&** **||** **?** **:** **;** **\.\.\.** **=** **\*=** **/=** **%=** **\+=** **\-=** **<<=** **\>\>=** **&=** **^=** **|=** **,** **\#** **\#\#** **<\:** **:\>** **<%** **%\>** **%:** **%:%:**

#### What is the scope of a *processing token*
+ According to C11, a *preprocessing token* is the minimal lexical element in the procedure of preprocessing.
+ *preprocessing-token*:
    * *header-name*
    * *identifier*
    * *pp-number*
    * *character-constant*
    * *string-literal*
    * *punctuator*
    * each non-white-space character that cannot be one of the above
+ *header-name*:
    * **<** h-char-sequence **\>**
    * **"** q-char-sequence **"**
+ *h-char-sequence*:
    * *h-char*
    * *h-char-sequence* *h-char*
* *h-char*:
    - any member of the source character set except the new-line character and **\>**
* *q-char-sequence*:
    - *q-char*
    - *q-char-sequence* *q-char*
* *q-char*:
    - any member of the source character set except the new-line character and **"**
* *pp-number*:
    - *digit*
    - **\.** *digit*
    - *pp-number* *digit*
    - *pp-number* *identifier-nondigit*
    - *pp-number* **e** *sign*
    - *pp-number* **E** *sign*
    - *pp-number* **p** *sign*
    - *pp-number* **P** *sign*
    - *pp-number* **.**

#### How to identify a *preprocessing-token* and  a *token*
+ According to the lexical grammar, the characters in source file will be scan one by one and to match them with the perhaps tokens type.
+ The next matching will start immediately the previous failed.
+ if there isn't a corresponding token, an error will be thrown.

### Implement
+ Arrays that contain different terminals set will be used for the identification of multi-words terminals.
+ Functions will be defined to match both terminals and nonterminals, if success, the length of the token will be return.
+ Two threads are used to implement both the two requirement.
+ The thread one is used for preprocessing.
+ The thread two is waiting for every time thread one finishing its staged work, and than categorizes it.

### Reference
+ ISO/IEC 9899:2011, Programming languages -- C.
