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


# 相关文档
[韦东山freeRTOS系列教程](https://blog.csdn.net/thisway_diy/article/details/121399484)       
[freertos-addons](https://github.com/michaelbecker/freertos-addons)         
[FreeRTOS-Sim](https://github.com/Muriukidavid/FreeRTOS-Sim)            
[freertos-linux](https://github.com/sean93park/freertos-linux)      
[FreeRTOS源码解读](https://github.com/Nrusher/FreeRTOS-Book)    
[freertos-qemu](https://github.com/mghicho/freertos-qemu)
