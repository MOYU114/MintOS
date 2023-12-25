# MintOS

本实验参考OrangeS代码，调用其chapter11/a/代码。

## 使用说明

调用时直接输入`$ sh bash.sh`，因为多需要make command文件。

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
- [ ] 实现基于分页的虚拟内存管理
- [ ] shellcode注入代码
- [x] 缓冲区溢出代码
- [ ] 静态度量
- [ ] 动态度量

## 文件说明

- pagesandqueue：实现week11-1
- shell：实现week11-2、3
- attackandprotect：实现week12

## 可执行程序说明

- `mintos`：展示欢迎界面
- `list`：用于展示当前目录下的所有文件
- `rm`：用于删除文件，可以多个文件名并列
- `touch`：用于创建新文件，可以多个文件名并列

# shell多任务说明

多个任务间用**|**隔开即可

## This makes no sense
只是展示一下我可以**随时随地***push*

## This makes no sense, too
只是展示一下我**也**可以**随时随地***push*
## This also makes no sense
to test my laptop
