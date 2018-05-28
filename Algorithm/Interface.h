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

/*�ӿڴ�����
	GUI���̨�㷨ͨ��
	�㷨�̳в�����ʵ�ָýӿڣ�GUIʵ����Ӧ��ָ�벢���÷���������������GUI->ALG
	����:
		class Alg_withinterface:public Interface_Alg,protected Algorithm{}
		class GUI:{Interface_Alg*palg=new Alg_withinterface;}
*/
class Interface_Alg
{
public:
	virtual bool Init() = 0;//��ʼ���㷨
	virtual bool Release() = 0;//�ͷ���Դ
	
	virtual bool LoadSrcImg() = 0;//����ԴͼƬ
	virtual bool LoadSetting() = 0;//�����趨
	virtual bool LoadParam() = 0;//�������

	virtual bool ReadRstImg() = 0;//��ȡ���
	virtual bool ReadParam() = 0;//��ȡ����
	virtual bool ReadState() = 0;//��ȡ��ǰ״̬

	virtual bool Run() = 0;//���У�������
	virtual bool RunOnce() = 0;//���У����Σ�
	virtual bool Pause() = 0;//��ͣ
	virtual bool Stop() = 0;//ֹͣ����ɵ�ǰ����֮��
	virtual bool Terminate() = 0;//����ֹͣ�������Ƿ����ڹ�����

	virtual bool Train() = 0;//ѵ��
	
	virtual bool IsInit() = 0;//����Ƿ��ʼ�����
	virtual bool IsBusy() = 0;//����Ƿ�æ
};


/*�ӿڴ�����
	��̨�㷨��GUIͨ��
	GUI�̳в�����ʵ�ָýӿڣ�ALGʵ����Ӧ��ָ�벢���÷���������������ALG->GUI
*/
class Interface_GUI
{
	virtual bool ShowImg()=0;//��ʾͼƬ
	virtual bool TextOut()=0;//�������
	virtual bool ReportProgress() = 0;//�������
};
