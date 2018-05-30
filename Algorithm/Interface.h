#pragma once
/* ================================================================================
 * \�ļ� Interface.h
 * \ʱ�� 2018/05/28 11:38
 * \�汾 ver 0.1
 *		+=ver 0.1 ��������趨
 *
 * \���� yyx11
 *
 * \��� �㷨�Ľӿڴ�����
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

//����״̬ö���������
//	��STATE_E_CONSTRUCTOR(init)��չ��Ϊ��
//	init_pre,init_ing,init_end
#define STATE_E_CONSTRUCTOR(name) name##_pre,name##_ing,name##_end
/*enum class State_E
 *	����״̬ö����
 *	��־�����״̬��ÿ����Ϊǰ���С�������С�׶�
 *		ǰ(pre)����ʼ���Խ����״̬������ʧ��
 *		��(ing)���ɹ�����״̬
 *		��(end)����״̬����
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
//����״̬ö�����ַ��������
//	��STATE_STR_CONSTRUCTOR("init")��չ��Ϊ��
//	"init_pre","init_ing","init_end"
#define STATE_STR_CONSTRUCTOR(name) name"_pre",name"_ing",name"_end"
/*const static char *State_Str[]
*	����״̬ö�����ַ���
*	State_E��Ӧ���ַ��������ʱע������Ӧ
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
/*�ӿڴ�����
	GUI���̨�㷨ͨ��
	�㷨�̳в�����ʵ�ָýӿڣ�GUIʵ����Ӧ��ָ�벢���÷���������������GUI->ALG
	����:
		class Alg_withinterface:public Interface_Alg,protected Algorithm{}
		class GUI:{Interface_Alg*palg=new Alg_withinterface;}
	���к�׺_Async�Ĵ����첽����������Ҫ�ȴ���ز�������д��δ��ɡ���һ�������ú���δ�������������еȣ����������ʹ��
*/
class Interface_Alg
{
public:
	virtual bool Init(const Interface_GUI*gui) = 0;//��ʼ���㷨
	virtual bool Reset() = 0;//����Ϊ��ʼ״̬
	virtual bool Release() = 0;//�ͷ���Դ 

	virtual bool LoadSrc(cv::InputArray src) = 0;//����ԴͼƬ
	virtual bool LoadSetting() = 0;//�����趨
	virtual bool LoadParam() = 0;//�������

	virtual bool ReadRst(cv::OutputArray rst) = 0;//��ȡ���
	virtual bool ReadParam()const = 0;//��ȡ����
	virtual State_E ReadState()const = 0;//��ȡ��ǰ״̬

	virtual bool Run() = 0;//���У�������
	virtual bool Pause(bool ispause) = 0;//��ͣ
	virtual bool Stop() = 0;//ֹͣ����ɵ�ǰ����֮��
	
	virtual bool IsInit() const = 0;//����Ƿ��ʼ�����
	virtual bool IsRun() = 0;//����Ƿ���������
	virtual bool IsWrite() = 0;//����Ƿ�����д��
};
ALGORITHM_API Interface_Alg*Create_Interface_Alg(const Interface_GUI*gui);

/*�ӿڴ�����
	��̨�㷨��GUIͨ��
	GUI�̳в�����ʵ�ָýӿڣ�ALGʵ����Ӧ��ָ�벢���÷���������������ALG->GUI
*/
class Interface_GUI
{
public:
	virtual bool ShowImg(const cv::InputArray img) = 0;//��ʾͼƬ
	virtual bool ShowText(std::string text) = 0;//�������
	virtual bool ReportState(State_E state) = 0;//����״̬
	virtual bool ReportProgress(int progress) = 0;//�������
	virtual bool ReportError(std::string msg) = 0;//�������
	virtual bool SaveData(const cv::InputArray data) = 0;//��������

	//virtual bool IsInit() const = 0;
	virtual bool IsBusy() const = 0;
	virtual bool wait(int msec=0)const = 0;//�ȴ���QTʵ�ֵĵȴ��������ڵ���wait()�ȴ�ʱ�������н����ػ�Ͳ���
};
