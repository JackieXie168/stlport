##记录STLport源码学习笔记！


+ 为了使用vs2010，需要修改配置文件
+ 编译安装，产生lib库文件
    1. 在开始菜单中找到vs2010的命令行工具；
    2. 切换到STLport目录；
    3. 运行`configure -help`查看编译选项；
    4. 使用MSVC编译器编译，使用命令：
        `configure msvc10`
    5. 输入命令：
        `cd build`
        `cd lib`
    6. 输入命令：
        `nmake clean install`
    7. 编译完成！