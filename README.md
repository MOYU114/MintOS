# MintOS

本实验参考OrangeS代码，扩展其chapter11/a/代码。

## 使用说明

编译时直接输入`$ sh bash.sh`，因为多需要make command文件。

遇到

```
Device:[HD]
Messaget ata0-0t could not open hard drive image file '80m,img'
```

是因为bochs没有正常退出，把目录下的`80m.img.lock`删除后再调用bash.sh即可。

## 任务进度

- [x] 整合代码
- [x] 编写可执行程序
- [x] 扩展shell支持多任务
- [x] 实现基于分页的虚拟内存管理(maybe)
- [x] shellcode注入代码
- [x] 缓冲区溢出代码
- [x] 静态度量
- [x] 动态度量
- [x] 体系扩充(hook)

## 文件说明

- pagesandqueue：实现week11-1，代码整合尝试
- shell：实现week11-2、3，week12-体系扩充
- StackOverflow：实现week12 缓冲区溢出/动态度量
- FileInjection：实现week12 shellcode文件注入/静态度量

## 可执行程序说明

- `mintos`：展示欢迎界面
- `list`：用于展示当前目录下的所有文件
- `rm`：用于删除文件，可以多个文件名并列
- `touch`：用于创建新文件，可以多个文件名并列
- `addAll`: 累加
- `inject`:向指定文件注入shellcode
- `injectAllELF`:向所有ELF文件注入shellcode
- `stackoverflow`:尝试栈溢出
- `hook`:用于劫持系统调用
  
## shell多任务说明

多个任务间用 **|** 隔开即可

## 静态度量说明

修改FileInjection文件夹global.h中的STATIC_CHECK为1即可开启


