#pragma once
/* ================================================================================
 * \文件 Interface.h
 * \时间 2018/05/28 11:38
 * \版本 ver 0.1
 *		+=ver 0.1 最基本的设定
 *
 * \作者 yyx11
 *
 * \简介 算法的接口纯虚类
 *
 * TODO: long description
 *
 * \note
 * ================================================================================*/
#include "stdafx.h"

/*接口纯虚类
	GUI向后台算法通信
	算法继承并公有实现该接口，GUI实现相应的指针并调用方法。控制流单向，GUI->ALG
	举例:
		class Alg_withinterface:public Interface_Alg,protected Algorithm{}
		class GUI:{Interface_Alg*palg=new Alg_withinterface;}
*/
class Interface_Alg
{
public:
	virtual bool Init() = 0;//初始化算法
	virtual bool Release() = 0;//释放资源
	
	virtual bool LoadSrcImg() = 0;//载入源图片
	virtual bool LoadSetting() = 0;//载入设定
	virtual bool LoadParam() = 0;//载入参数

	virtual bool ReadRstImg() = 0;//读取结果
	virtual bool ReadParam() = 0;//读取参数
	virtual bool ReadState() = 0;//读取当前状态

	virtual bool Run() = 0;//运行（连续）
	virtual bool RunOnce() = 0;//运行（单次）
	virtual bool Pause() = 0;//暂停
	virtual bool Stop() = 0;//停止（完成当前迭代之后）
	virtual bool Terminate() = 0;//立即停止（无论是否正在工作）

	virtual bool Train() = 0;//训练
	
	virtual bool IsInit() = 0;//检查是否初始化完成
	virtual bool IsBusy() = 0;//检查是否忙
};


/*接口纯虚类
	后台算法向GUI通信
	GUI继承并公有实现该接口，ALG实现相应的指针并调用方法。控制流单向，ALG->GUI
*/
class Interface_GUI
{
	virtual bool ShowImg()=0;//显示图片
	virtual bool TextOut()=0;//输出文字
	virtual bool ReportProgress() = 0;//报告进度
};
