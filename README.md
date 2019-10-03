# lox++

A script language implementation based on [Crafting Interpreters](http://craftinginterpreters.com/) yet implemented in C++.

## TODO

- 一个异构的数组，元素是指针，内存另行保存。元素可以有几位指明类型，方便解析
- 一个变量可以更改变量类型，不需要类型声明

上述两条非常重要

- 像lua的table一样的数据结构
  - 自动销毁
  - 匿名数据结构，变量仅为指针
- 可以在runtime加载新的代码块
- 函数式