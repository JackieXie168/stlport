##记录STLport源码学习笔记！


+ 为了使用vs2010，需要修改配置文件

+ 编译安装，产生lib库文件
    1. 在开始菜单中找到vs2010的命令行工具；（选择64bit命令行，win7 64bit）
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

+ 使用产生的lib库文件进行第一个程序
    1. 新建工程，设置为x64；
    2. 添加include和lib路径；
    3. 设置Code Generation为/MTd模式；
    4. 使用rope相关函数编写一个简单实例进行环境调试；
    5. 环境成功搭建！