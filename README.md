<div align="center">

# <span style="color:#1976D2">PhysicalSimulation</span>

<img src="https://img.shields.io/badge/C++-20-blue"> 
<img src="https://img.shields.io/badge/build-cmake-blue">

</div>

>  [!NOTE]
> **注意：本项目是长期项目，仍在开发中，功能尚不完善。**

---

## 项目简介

**PhysicalSimulation (PS)** 是一个面向物理模拟的工具集，目前支持 2D 刚体动力学模拟，未来将扩展至 3D。涵盖但不限于刚体动力学、流体模拟、分子动力学等功能。

## 快速开始

本项目采用 [SDL3](https://github.com/libsdl-org/SDL/releases/tag/release-3.2.14) 静态链接，作者主要在 [CMake](https://cmake.org/download/) + [MinGW](https://sourceforge.net/projects/mingw/) 环境下测试。其他构建工具请自行适配。

**项目目录结构：**
```
PhysicalSimulation
├─bin                   # 可执行文件目录
│   └─SDL3.dll
├─include
│  └─Dependencies
│      ├─PS             # PS 核心库
│      │  ├─include
│      │  └─src
│      └─SDL3           # SDL 官方头文件
│           ├─SDL3.h
│           └─...
├─libs
│  └─SDL3               # SDL 官方静态库
│       └─libSDL3.dll.a    
├─res
└─src
```

**构建步骤：**
1. 下载依赖并放入对应目录。
2. 在项目根目录执行以下命令：
    ```shell
    mkdir build
    cd build
    cmake -G "MinGW Makefiles" -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ ..
    mingw32-make
    ```

## 演示

![heap](/res/heap.png)
![newton-cradle](/res/newton_cradle.png)
---

## 功能

- 线性代数类
- 碰撞检测
  - Narrowphase
    - 碰撞检测
      - SAT 算法
      - GJK & EPA 算法
    - CCD连续碰撞检测
  - Broadphase
    - AABB 轴对齐包围盒
    - 动态层次包围体树
    - 均匀网格法
- 碰撞点
- 刚体模拟
- 约束关节
  - 点约束
  - 距离约束
- 测试 Scene
- 基本 2D 计算几何算法
  - 基本图元映射
  - 相交测试
  - 凸体检测
  - 三角形三心计算
  - 外/内接圆  

---

## 参考与致谢

- [FLAT](https://github.com/yuanming-hu/FLAT)
- [Let's Make a Physics Engine](https://www.youtube.com/watch?v=lzI7QUyl66g&list=PLSlpr6o9vURwq3oxVZSimY8iC-cdd3kIs)
- [PixelPhysics](https://www.youtube.com/@pixel_physics)
- [2D凸多边形碰撞检测算法](https://zhuanlan.zhihu.com/p/178841676)
- [游戏物理引擎笔记](https://www.zhihu.com/column/c_1286651106643099648)
- [jMonkeyEngine 初学者教程（中文版）](https://www.jmecn.net/tutorial-for-beginners/chapter-16-physics-engine.hpptml)
- [游戏开发物理学](https://cread.jd.com/read/startRead.action?bookId=30358337&readType=1)
- [SDL Wiki](https://wiki.libsdl.org/SDL3/Tutorials/FrontPage)
- [Unity3D Scripting API](https://docs.unity3d.com/ScriptReference/)
- [Cppreference](https://zh.cppreference.com/)
- [BOX2D](https://github.com/erincatto/box2d)
- [ps](https://github.com/acrlw/ps)
- [dyn4j](https://github.com/dyn4j/dyn4j)
- [matterjs](https://github.com/liabru/matter-js)
- [nphysics](https://github.com/dimforge/nphysics)
- [Box2D Publications](https://box2d.org/publications/)
- [dyn4j Official Blog](https://dyn4j.org/blog/)
- [Game Physics For Beginners - liabru](https://brm.io/game-physics-for-beginners/)
- [Allen Chou's Blog](http://allenchou.net/game-physics-series/)
- [Physics Constraints Series - Allen Chou](https://www.youtube.com/c/MingLunChou/videos)
- [Soft Constraints - ODE](https://ode.org/ode-latest-userguide.hpptml#sec_3_8_0)
- [Gaffer's on Games](https://gafferongames.com/#posts)
- [Randy Gaul's Blog](https://randygaul.github.io/)
- [Winter's Dev](https://blog.winter.dev/)
- [Primitives and Intersection Acceleration](https://www.pbr-book.org/3ed-2018/Primitives_and_Intersection_Acceleration/Bounding_Volume_Hierarchies)
- [Real-Time Rendering Intersection](http://www.realtimerendering.com/intersections.hpptml)
- [Inigo Quilez's 2D SDF Functions](https://www.iquilezles.org/www/articles/distfunctions2d/distfunctions2d.hpptm)
- [*A Simple Time-Corrected Verlet Integration Method* - Jonathan Dummer](https://archive.gamedev.net/archive/reference/programming/features/verlet/)
- [*Introduction to rigid body pipeline, collision detection* - Erwin Coumans](https://docs.google.com/presentation/d/1wGUJ4neOhw5i4pQRfSGtZPE3CIm7MfmqfTp5aJKuFYM/edit#slide=id.g644a5aa5f_1_116)
- *Foundations of Physically Based Modeling and Animation* - Donald House and John C. Keyser
- *Real-Time Collision Detection* by Christer Ericson
- *Game Programming Gems 7* - Scott Jacobs
- *Game Physics Cookbook* - Gabor Szauer