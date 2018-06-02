// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 ALGORITHM_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// ALGORITHM_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#pragma once

#include "Interface.h"
#include <mutex>
#include <atomic>
#include <sstream>
#include <hash_map>
#include "Algparam.h"
#include "AlgOutstream.h"

#ifdef _DEBUG
//TODO: 解决warning C4251问题 https://blog.csdn.net/shellching/article/details/7090742
#pragma warning(disable: 4251)
#endif // _DEBUG
class ALGORITHM_API cv::Mat;
class ALGORITHM_API std::mutex;
struct ALGORITHM_API atomic_bool;
class ALGORITHM_API ostringstream;
class ALGORITHM_API AlgOutstream;



class ALGORITHM_API AlgorithmControler 
	:public Interface_Alg 
{
protected:
	cv::Mat _srcimg, _dstimg;
	Interface_GUI*_gui;//符合Interface_GUI的接口类实例指针
	State_E _sta = State_E::init_pre;
#define CHANGE_STATE(sta) {_sta=sta;_gui->ReportState(sta);}

	//std::set<std::string>algonames;
	std::hash_map<std::string, Algparam>params;
	//std::map<std::string, std::map<std::string, Algparam>>params;
/*线程安全注意：
 *	【重要】任何在运行中不能被调用的函数在开头都应调用LOCKRUN。
 *	【重要】任何对类成员变量和全局变量的写入操作之前应调用写保护。
 *		LOCKWRITE是全局锁，在生存期内原则上就不能再写入
 *		对单个变量进行保护可以使用原子操作std::atomic进行声明，简单起见可以将所有共享变量声明为atomic
 *	LOCKRUN、LOCKWRITE是RAII类，会在退出作用域之前自动解锁。
 *		故在线程安全的前提下，应尽量缩小作用域，尤其不能声明静态和全局作用域的LOCKRUN、LOCKWRITE
*/
	typedef std::lock_guard<std::mutex>alglock_t;
	std::mutex _write_mutex, _run_mutex;
	#define LOCKRUN alglock_t lockrun(_run_mutex);//尝试运行。
	#define LOCKWRITE alglock_t lockwrite(_write_mutex);//尝试写入
	std::atomic_bool _is_init = false, _is_pause = false, _is_stop = false;
public:
	AlgorithmControler(const Interface_GUI*gui):aout(gui) { Init(gui); }
	virtual ~AlgorithmControler() { Release(); }

	virtual bool Init(const Interface_GUI*gui) override;
	virtual bool Release() override;
	virtual bool Reset() override;

	virtual bool LoadSrc(cv::InputArray src) override;
	virtual bool LoadSetting() override;
	virtual bool LoadParam() override;

	virtual bool ReadRst(cv::OutputArray rst) override;
	virtual bool ReadParam() const override;
	virtual State_E ReadState()const override;

	//virtual bool Run() override;
	virtual bool Pause(bool ispause) override;
	virtual bool Stop() override;

	virtual bool IsInit() const override;
	virtual bool IsRun() override;
	virtual bool IsWrite() override;

	AlgOutstream aout;

};



