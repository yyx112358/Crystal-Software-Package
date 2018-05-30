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
#include <opencv2/core/mat.hpp>
#include <string>
#include "dllmain.h"

class ALGORITHM_API Interface_Alg;
class ALGORITHM_API Interface_GUI;

//程序状态枚举量构造宏
//	如STATE_E_CONSTRUCTOR(init)将展开为：
//	init_pre,init_ing,init_end
#define STATE_E_CONSTRUCTOR(name) name##_pre,name##_ing,name##_end
/*enum class State_E
 *	程序状态枚举量
 *	标志程序的状态，每个分为前、中、后三个小阶段
 *		前(pre)：开始尝试进入该状态，可能失败
 *		中(ing)：成功进入状态
 *		后(end)：该状态结束
 */
enum class State_E:unsigned int
{
	STATE_E_CONSTRUCTOR(init),
	STATE_E_CONSTRUCTOR(reset),
	STATE_E_CONSTRUCTOR(release),
	STATE_E_CONSTRUCTOR(load),
	STATE_E_CONSTRUCTOR(run),
	STATE_E_CONSTRUCTOR(pause),
	STATE_E_CONSTRUCTOR(stop),
	STATE_E_CONSTRUCTOR(iter),
	STATE_E_CONSTRUCTOR(complete),
};
//程序状态枚举量字符串构造宏
//	如STATE_STR_CONSTRUCTOR("init")将展开为：
//	"init_pre","init_ing","init_end"
#define STATE_STR_CONSTRUCTOR(name) name"_pre",name"_ing",name"_end"
/*const static char *State_Str[]
*	程序状态枚举量字符串
*	State_E对应的字符串，添加时注意次序对应
*/
const static char *State_Str[] =
{
	STATE_STR_CONSTRUCTOR("init"),
	STATE_STR_CONSTRUCTOR("reset"),
	STATE_STR_CONSTRUCTOR("release"),
	STATE_STR_CONSTRUCTOR("load"),
	STATE_STR_CONSTRUCTOR("run"),
	STATE_STR_CONSTRUCTOR("pause"),
	STATE_STR_CONSTRUCTOR("stop"),
	STATE_STR_CONSTRUCTOR("iter"),
	STATE_STR_CONSTRUCTOR("complete"),
};
#undef STATE_E_CONSTRUCTOR
#undef STATE_STR_CONSTRUCTOR
/*接口纯虚类
	GUI向后台算法通信
	算法继承并公有实现该接口，GUI实现相应的指针并调用方法。控制流单向，GUI->ALG
	举例:
		class Alg_withinterface:public Interface_Alg,protected Algorithm{}
		class GUI:{Interface_Alg*palg=new Alg_withinterface;}
	带有后缀_Async的代表异步函数，不需要等待相关操作（如写入未完成、上一个被调用函数未结束、正在运行等）结束后就能使用
*/
class Interface_Alg
{
public:
	virtual bool Init(const Interface_GUI*gui) = 0;//初始化算法
	virtual bool Reset() = 0;//重置为初始状态
	virtual bool Release() = 0;//释放资源 

	virtual bool LoadSrc(cv::InputArray src) = 0;//载入源图片
	virtual bool LoadSetting() = 0;//载入设定
	virtual bool LoadParam() = 0;//载入参数

	virtual bool ReadRst(cv::OutputArray rst) = 0;//读取结果
	virtual bool ReadParam()const = 0;//读取参数
	virtual State_E ReadState()const = 0;//读取当前状态

	virtual bool Run() = 0;//运行（连续）
	virtual bool Pause(bool ispause) = 0;//暂停
	virtual bool Stop() = 0;//停止（完成当前迭代之后）
	
	virtual bool IsInit() const = 0;//检查是否初始化完成
	virtual bool IsRun() = 0;//检查是否正在运行
	virtual bool IsWrite() = 0;//检查是否正在写入
};
ALGORITHM_API Interface_Alg*Create_Interface_Alg(const Interface_GUI*gui);

/*接口纯虚类
	后台算法向GUI通信
	GUI继承并公有实现该接口，ALG实现相应的指针并调用方法。控制流单向，ALG->GUI
*/
class Interface_GUI
{
public:
	virtual bool ShowImg(const cv::InputArray img) = 0;//显示图片
	virtual bool ShowText(std::string text) = 0;//输出文字
	virtual bool ReportState(State_E state) = 0;//报告状态
	virtual bool ReportProgress(int progress) = 0;//报告进度
	virtual bool ReportError(std::string msg) = 0;//报告错误
	virtual bool SaveData(const cv::InputArray data) = 0;//保存数据

	//virtual bool IsInit() const = 0;
	virtual bool IsBusy() const = 0;
	virtual bool wait(int msec=0)const = 0;//等待。QT实现的等待函数能在调用wait()等待时继续进行界面重绘和操作
};
