# 依赖
```bash
sudo apt-get install libc6-dev-i386
```

# 命名规则
- u :代表unsigned。
- s :代表short。
- c :char。 所以类似uc，us类的变量就是unsigned char，unsigned short，分别对应uint8_t,uint16_t。
- x :为用户自定义的数据类型，比如结构体，队列等。 常看到ux开头的函数，就是unsigned且用户自定义的类型。需要注意的是size_t变量前缀也是ux。
- e :枚举变量
- p :指针变量. 类似(uint16_t *)变量前缀为pus。
- prv : (private)static函数，c文件内部使用
- v: void函数

# 优先级
FreeRTOS的优先级数值越小，任务优先级越低，空闲任务的优先级是 0。
configMAX_PRIORITIES值越大，内核花销的内存空间就越大

# 调度方式
- 时间片轮转
- 抢占式
- configUSE_TIME_SLICING 控制

# 内存
## 分配算法
![](https://pic4.zhimg.com/80/v2-e802afa55069db8742d63f57bfaf5557_720w.webp)
## API 
xPortGetFreeHeapSize();

# 例子
## 任务
1. 抢占式调度总是选择具有最高优先级的可运行任务来执行. 如果高优先级任务没有主动退出运行态，低等级任务无法得到运行 
- [任务优先级](./user/task1.c)
此例中, vTask1任务优先级最高，且一直在无限循环，所有其他任务得不到执行
taskYIELD()将当前任务主动放弃CPU的执行权，使得其他优先级相同的任务有机会执行。
但taskYIELD()时，相同优先级的任务可能不是就绪态，浪费此次机会。因此任务运行次数会大量减少

```c
void vTask1(void* parameter)
{
    while(1)
    {
        taskYIELD();
    }
}
```

- [任务栈溢出检测](./user/task2.c)

## 信号量
使用场景:

## 队列
- [传输int数据]
- [传输数组]
    接收外设传输的数据时，先将数据放到队列里，然后其他任务再慢慢处理，防止可能出现丢数据的情况

## 事件标志组(EventGroup)
使用信号量来同步的话任务只能与单个的事件或任务进行同步。
有时候某个任务可能会需要与多个事件或任务进行同步, 这时即可以使用事件标志组


# 相关文档
[韦东山freeRTOS系列教程](https://blog.csdn.net/thisway_diy/article/details/121399484)       
[freertos-addons](https://github.com/michaelbecker/freertos-addons)         
[FreeRTOS-Sim](https://github.com/Muriukidavid/FreeRTOS-Sim)            
[freertos-linux](https://github.com/sean93park/freertos-linux)      
[FreeRTOS源码解读](https://github.com/Nrusher/FreeRTOS-Book)    
[freertos-qemu](https://github.com/mghicho/freertos-qemu)
