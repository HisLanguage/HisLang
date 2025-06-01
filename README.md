**FORKED FROM [HerLanguage/HerLang](https://github.com/HerLanguage/HerLang), USING MIT LICENSE**

![HisLang](/assets/logo.png)
# HisLang - A code language for he.

Programming is not a female privilege, boys can also program well.

## Demo

```HisLang
function you_can_do_this:
    say "Hello! His World!"
    say "编程很帅，也属于你！"
end

start:
    you_can_do_this
end
```

it outputs:

```
Hello! His World!
编程很帅，也属于你！
```

## How to use

```
Usage: hcp in.hisc out.cpp
```

and then you can use `g++` to build an executable file.

```shell
g++ out.cpp -o out
```

then you can run it!

```shell
./out
```

## How to build

```shell
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

or, you can use Microsoft Visual Studio.

## Notes

This project is still under active development and there may be a lot of issues. You can actively submit fixes.
