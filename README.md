# MyGameEngine

制作自己的游戏引擎

基于教程：[陈文礼--从零开始敲次世代游戏引擎](https://zhuanlan.zhihu.com/c_119702958)


## 游戏引擎设计思路

1.我们首先需要一个建立一个跨平台的模块，它能够在不同的操作系统+图形API环境当中，为我们创建这个基本的上下文。（可能是窗口，可能是全屏FrameBuffer，也可能是Off Screen Buffer）

2.然后，我们需要对平台的硬件能力进行查询和遍历，找到平台硬件（这里特指GPU）所能够支持的画布格式，并且将1所创建的上下文的FrameBuffer格式指定为这个格式，GPU才能够在上面作画。

3.CPU使用平台所支持的图形API创建绘图所需要的各种Heap/Buffer/View，生成资源描述子（RootSignature或者Descriptor），将各种资源的元数据（Meta Data)填入描述子，并传递给GPU

4.CPU根据场景描述信息进行顶点数据/索引/贴图/Shader等的加载，并将其展开在GPU所能看到的（也就是在描述子里面登记过的）Buffer当中

5.帧循环开始

6.CPU读取用户输入（在之前的文章当中还未涉及），并更新用户可操作场景物体的位置和状态

7.CPU执行游戏逻辑（包括动画、AI），并更新对应物体的位置和状态

8.CPU进行物体的裁剪，找出需要绘制的物体（可见的物体）

9.CPU将可见物体的位置和状态翻译成为常量，并把常量上传到GPU可见的常量缓冲区

10.CPU生成记录GPU绘图指令的Buffer （CommandList），并记录绘图指令

11.CPU创建Fence，以及相关的Event，进行CPU和GPU之间的同步

12.CPU提交记录了绘图指令的Buffer（CommandList），然后等待GPU完成绘制（通过观察Fence）

13.CPU提交绘制结果，要求显示（Flip或者Present）

14.帧循环结束


## 游戏引擎涉及模块

1。输入管理模块，用来获取用户输入

2。策略模块，用来执行策略

3。场景管理模块，用来管理场景和更新场景

4。渲染模块，用来执行渲染和画面输出

5。音频音效模块，用来管理声音，混音和播放

6。网络通信模块，用来管理网络通信

7。文件I/O模块，用来管理资源的加载和参数的保存回复

8。内存管理模块，用来调度管理内存上的资源

9。驱动模块，用来根据时间，事件等驱动其它模块

10。辅助模块，用来执行调试，log输出等辅助功能

11。应用程序模块，用来抽象处理配置文件，特定平台的通知，创建窗口等需要与特定平台对接的部分




## 具体教程



1.[从零开始敲次世代游戏引擎（一）-- 初建项目，git使用](https://zhuanlan.zhihu.com/p/28589792)


2.[从零开始敲次世代游戏引擎（二）-- Windows环境clang编译环境构建](https://zhuanlan.zhihu.com/p/28598462)


3.[从零开始敲次世代游戏引擎（三）-- Linux环境的clang环境搭建](https://zhuanlan.zhihu.com/p/28619982)



4.[从零开始敲次世代游戏引擎（四）-- 游戏引擎设计方法论](https://zhuanlan.zhihu.com/p/28615565)


5.[从零开始敲次世代游戏引擎（五）-- 游戏引擎框架初建](https://zhuanlan.zhihu.com/p/28619982)


6.[从0开始敲次世代引擎（六）--图形界面初入](https://zhuanlan.zhihu.com/p/28633100)

7.[从0开始敲次世代引擎（七）--windows环境下图形界面](https://zhuanlan.zhihu.com/p/28641118)

10.[从0开始敲次世代引擎（十）--Windows下用gpu画图](https://zhuanlan.zhihu.com/p/28711014)

13.[从0开始敲次世代引擎（十三）--Windows下用opengl画图](https://zhuanlan.zhihu.com/p/28800368)

14.[从0开始敲次世代引擎（十四）--Windows下用directX 12 画图](https://zhuanlan.zhihu.com/p/28809434)

18.[从0开始敲次世代引擎（十八）--游戏引擎内存管理初入](https://zhuanlan.zhihu.com/p/29023579)






