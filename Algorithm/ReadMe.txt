========================================================================
    动态链接库：Algorithm 项目概述
========================================================================

应用程序向导已为您创建了此 Algorithm DLL。

本文件概要介绍组成 Algorithm 应用程序的每个文件的内容。


Algorithm.vcxproj
    这是使用应用程序向导生成的 VC++ 项目的主项目文件，其中包含生成该文件的 Visual C++ 的版本信息，以及有关使用应用程序向导选择的平台、配置和项目功能的信息。

Algorithm.vcxproj.filters
    这是使用“应用程序向导”生成的 VC++ 项目筛选器文件。它包含有关项目文件与筛选器之间的关联信息。在 IDE 中，通过这种关联，在特定节点下以分组形式显示具有相似扩展名的文件。例如，“.cpp”文件与“源文件”筛选器关联。

Algorithm.cpp
    这是主 DLL 源文件。

/////////////////////////////////////////////////////////////////////////////
其他标准文件:

StdAfx.h, StdAfx.cpp
    这些文件用于生成名为 Algorithm.pch 的预编译头 (PCH) 文件和名为 StdAfx.obj 的预编译类型文件。

/////////////////////////////////////////////////////////////////////////////
其他注释:

应用程序向导使用“TODO:”注释来指示应添加或自定义的源代码部分。

/////////////////////////////////////////////////////////////////////////////


添加新算法步骤：
1.新建一个cpp和h文件，例如Alg_Simpletest.h和Alg_Sipletest.cpp
2.包含头文件#include "AlgorithmControler.h"，并将本文件头文件添加到AlgorithmTable.h
3.建立一个类，公有继承AlgorithmControler如下，并重写Run()函数
	class ALGORITHM_API Alg_Simpletest :
		public AlgorithmControler
	{
	public:
		Alg_Simpletest(Interface_GUI*gui):AlgorithmControler(gui){}
		virtual ~Alg_Simpletest() {}

		virtual bool Run() override;

	};
4.在Run()中实现算法（Run()类似于main()函数），源图像为_srcimg，结果输出到_dstimg