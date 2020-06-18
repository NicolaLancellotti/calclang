# Calc Programming Language

The interpreter has been tested only on macOS.

## Building calclang

#### Generate UNIX makefiles
`mkdir build; cd build; cmake -G "Unix Makefiles" ..`

#### Build
`make`

#### Make a symbolic link to the interpreter
`ln -s lib/Interpreter/calclang calclang`

## Running calclang

### Run in interactive mode (no input file)
`./calclang`

insert:

`1 + 2`

press return and then `control + D` (EOF)

### Run in noninteractive mode (with input file)

`./calclang ../example/main1.calc`

### Flags

Meaning                        					 |  Flag
|------------------------------------------------|-------------------|
Lexical analysis               					 | -l
Lexical analysis verbose        				 | -lv
Dump tokens to file            					 | -dtokens=`<file>`
Dump tokens to standard error   			     | -dtokens
Syntactic analysis             					 | -p
Syntactic analysis verbose     					 | -pv
Dump AST to file                                 | -dast=`<file>`
Dump AST to standard error                       | -dast
Semantic analysis                                | -s
Evaluation (default if no other is specified)    | -e

#### Example
`./calclang -dast=ast.xml ../examples/main1.calc`

`cat ast.xml`

```
<BodyAST loc="main1.calc:1:1">
    <BinaryOpAST loc="main1.calc:1:1" op="Plus">
        <NumberAST loc="main1.calc:1:1">1</NumberAST>
        <NumberAST loc="main1.calc:1:5">2</NumberAST>
    </BinaryOpAST>
</BodyAST>
```

## Grammar
[calclang bison grammar](https://github.com/NicolaLancellotti/calclang/blob/master/lib/ParseLex/bison.y%2B%2B)


