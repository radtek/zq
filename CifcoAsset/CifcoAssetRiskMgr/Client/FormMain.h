#pragma warning(disable : 4819)

#pragma once

#include <string>
#include "RiskEvt.h"
#include "ForceShortcutForm.h"
#include "ForceManualForm.h"
#include "RiskMsgNotify.h"
#include "TcpLayer.h"
#include "QueryTransfer.h"
#include "QueryRiskEvt.h"
#include "QueryMeaasge.h"
#include "ChangePassword.h"
#include "DlgRealTimeOrderInfo.h"
#include "CDlgRealTimeTradeInfo.h"
#include "CDlgRealTimePositionInfo.h"
#include "CDlgRealTimeFundInfo.h"
#include "Login.h"
#include "CDataInfo.h"
#include "Tools.h"
#include "QueryInvestorInfo.h"
#include "RiskMapForm.h"
#include "ReportForm.h"
#include "ReportDataProviderFactory.h"
#include "RiskMsgNotify.h"
#include "RiskMsgNotifyTip.h"
#include "RiskCombinationScreenSelect.h"
#include "QueryFundNetValueModule.h"
#include <cliext/vector>
namespace Client {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace ReportDataProvider;
	using namespace System::Xml;
	public ref class AutoScreenConfig
	{
	public:
		Int32 mnType;
		Int32 mnOrgID;
		String^ msOrgName;
		Int32 mnProID;
		String^ msProName;	
	public:
		AutoScreenConfig()
		{
			mnType = 0; //无效的类型
		}
	};

	/// <summary>
	/// Summary for FormMain
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class FormMain : public System::Windows::Forms::Form
	{
	public:
		FormMain(void)
		{
			InitializeComponent();
			this->WindowState = FormWindowState::Maximized;
			//
			//TODO: Add the constructor code here
			m_pdataInfo = CDataInfo::NewInstance();

			m_nAccountCount = 0;
            RiskMsgNotifyTipModule = nullptr;
			

			m_bAutoStart		= 0;
			m_strAutoStartName	= "";
			m_strAutoPassword	= "";
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~FormMain()
		{
			CDataInfo::DestroyInstance();
			if (components)
			{
				delete components;
			}
		}


			 //风险事件处理模块，包括当前风险事件、历史风险事件、用户风险列表
	private: RiskEvt^  RiskEvtModule;
	private: QueryTransfer^ QueryTransferModule; //查询出入金模块
	private: QueryMeaasge^ QueryMeaasgeModule; //查询消息通知
	private: ForceManualForm^ ForceManualModule; //手动强平模块
	private: ForceShortcutForm^ ForceShortcutModule;//快捷强平模块
    private: RiskMsgNotify^ RiskMsgNotifyModule;//风险消息通知模块
    private: RiskMsgNotifyTip^ RiskMsgNotifyTipModule;//风险消息通知模块
	private: DlgRealTimeOrderInfo^ dlgOrderInfoObject;		// 查询实时报单推送
	private: CDlgRealTimeTradeInfo^ dlgTradeInfoObject;		// 查询实时报单推送
	private: CDlgRealTimePositionInfo^ dlgPositionInfoObject;		// 查询实时报单推送
	private: CDlgRealTimeFundInfo^ dlgFundInfoObject;		// 查询实时报单推送
	private: QueryInvestorInfo^ QueryInvestorInfoModule;//查询投资者信息
	private: QueryRiskEvt^ QueryRiskEvtModule;//查询用户风险事件
	private: QueryFundNetValueModule^ QueryFundNetValue;//查询基金历史净值

    private: System::Windows::Forms::StatusStrip^  statusStrip1;
    private: System::Windows::Forms::MenuStrip^  menuStrip1;
    private: System::Windows::Forms::ToolStripMenuItem^  SystemToolStripMenuItem;
    private: System::Windows::Forms::ToolStrip^  toolStrip1;
    private: System::Windows::Forms::ToolStripMenuItem^  ModifyPasswordToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^  LockWindowToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^  QuitToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^  FunctionToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^  ViewTableToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^  SetupToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^  TableColumnSetupToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^  MessageToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^  RiskMessageNoticeToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^  InquiryToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^  TodayTableInquiryToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^  TodayTradeInquiryToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^  TodayHoldInquiryToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^  TodayMoneyInquiryToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^  TodayOutInMoneyInquiryToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^  InvestorInfoInquiryToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^  MessageNotifyInquiryToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^  UserEventInquiryToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  FundNetValueInquiryToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^  ForceToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^  FastForceToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^  ManualForceToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^  HelpToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^  VersionInfoToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^  HelpDocToolStripMenuItem;
    private: System::Windows::Forms::Panel^  MainWndClientPanel;
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem1;



	public: Login^ login;
	public: ChangePassword^ changePassword;
	public: int m_nAccountCount;
	private: System::ComponentModel::IContainer^  components;
	public: 
	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>

    private: System::Windows::Forms::ToolStripMenuItem^  MapViewToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  账户权益绩效统计ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  账户持仓统计ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  账户交易绩效统计ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel1;
	private: System::Windows::Forms::ToolStripProgressBar^  toolStripProgressBar1;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel2;
	private: System::Windows::Forms::ToolStripMenuItem^  组屏展示ToolStripMenuItem;
	private: System::Windows::Forms::Timer^  timer1;



	public: CDataInfo*  m_pdataInfo;
			bool        m_bAutoStart;       //true则自动登录
			String^     m_strAutoStartName; //自动登录用的用户名
			String^     m_strAutoPassword;  //自动登录用的密码
			void SetAutoStartPara(bool bAutoStart, String^ strAutoStartName, String^ strAutoPassword)
			{//用于每天早上重启，重新登录用
				m_bAutoStart		= bAutoStart;
				m_strAutoStartName	= strAutoStartName;
				m_strAutoPassword	= strAutoPassword;
			}

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
			this->toolStripStatusLabel1 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->toolStripProgressBar1 = (gcnew System::Windows::Forms::ToolStripProgressBar());
			this->toolStripStatusLabel2 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->SystemToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ModifyPasswordToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->LockWindowToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->QuitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->FunctionToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ViewTableToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->账户权益绩效统计ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->账户交易绩效统计ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->账户持仓统计ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->MapViewToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->组屏展示ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->SetupToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->TableColumnSetupToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->MessageToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->RiskMessageNoticeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->InquiryToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->TodayTableInquiryToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->TodayTradeInquiryToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->TodayHoldInquiryToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->TodayMoneyInquiryToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->TodayOutInMoneyInquiryToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->InvestorInfoInquiryToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->MessageNotifyInquiryToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->UserEventInquiryToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->FundNetValueInquiryToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ForceToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->FastForceToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ManualForceToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->HelpToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->VersionInfoToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->HelpDocToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStrip1 = (gcnew System::Windows::Forms::ToolStrip());
			this->MainWndClientPanel = (gcnew System::Windows::Forms::Panel());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->statusStrip1->SuspendLayout();
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// statusStrip1
			// 
			this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->toolStripStatusLabel1, 
				this->toolStripProgressBar1, this->toolStripStatusLabel2});
			this->statusStrip1->Location = System::Drawing::Point(0, 381);
			this->statusStrip1->Name = L"statusStrip1";
			this->statusStrip1->Size = System::Drawing::Size(734, 22);
			this->statusStrip1->TabIndex = 0;
			this->statusStrip1->Text = L"statusStrip1";
			// 
			// toolStripStatusLabel1
			// 
			this->toolStripStatusLabel1->Name = L"toolStripStatusLabel1";
			this->toolStripStatusLabel1->Size = System::Drawing::Size(53, 17);
			this->toolStripStatusLabel1->Text = L"初始化：";
			// 
			// toolStripProgressBar1
			// 
			this->toolStripProgressBar1->Name = L"toolStripProgressBar1";
			this->toolStripProgressBar1->Size = System::Drawing::Size(100, 16);
			// 
			// toolStripStatusLabel2
			// 
			this->toolStripStatusLabel2->Name = L"toolStripStatusLabel2";
			this->toolStripStatusLabel2->Size = System::Drawing::Size(17, 17);
			this->toolStripStatusLabel2->Text = L"0%";
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(7) {this->SystemToolStripMenuItem, 
				this->FunctionToolStripMenuItem, this->SetupToolStripMenuItem, this->MessageToolStripMenuItem, this->InquiryToolStripMenuItem, 
				this->ForceToolStripMenuItem, this->HelpToolStripMenuItem});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(734, 24);
			this->menuStrip1->TabIndex = 1;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// SystemToolStripMenuItem
			// 
			this->SystemToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {this->toolStripMenuItem1, 
				this->ModifyPasswordToolStripMenuItem, this->LockWindowToolStripMenuItem, this->QuitToolStripMenuItem});
			this->SystemToolStripMenuItem->Name = L"SystemToolStripMenuItem";
			this->SystemToolStripMenuItem->Size = System::Drawing::Size(41, 20);
			this->SystemToolStripMenuItem->Text = L"系统";
			// 
			// toolStripMenuItem1
			// 
			this->toolStripMenuItem1->Name = L"toolStripMenuItem1";
			this->toolStripMenuItem1->Size = System::Drawing::Size(118, 22);
			this->toolStripMenuItem1->Text = L"登录";
			this->toolStripMenuItem1->Click += gcnew System::EventHandler(this, &FormMain::toolStripMenuItem1_Click);
			// 
			// ModifyPasswordToolStripMenuItem
			// 
			this->ModifyPasswordToolStripMenuItem->Name = L"ModifyPasswordToolStripMenuItem";
			this->ModifyPasswordToolStripMenuItem->Size = System::Drawing::Size(118, 22);
			this->ModifyPasswordToolStripMenuItem->Text = L"修改密码";
			this->ModifyPasswordToolStripMenuItem->Click += gcnew System::EventHandler(this, &FormMain::ModifyPasswordToolStripMenuItem_Click);
			// 
			// LockWindowToolStripMenuItem
			// 
			this->LockWindowToolStripMenuItem->Name = L"LockWindowToolStripMenuItem";
			this->LockWindowToolStripMenuItem->Size = System::Drawing::Size(118, 22);
			this->LockWindowToolStripMenuItem->Text = L"锁定窗口";
			// 
			// QuitToolStripMenuItem
			// 
			this->QuitToolStripMenuItem->Name = L"QuitToolStripMenuItem";
			this->QuitToolStripMenuItem->Size = System::Drawing::Size(118, 22);
			this->QuitToolStripMenuItem->Text = L"退出登录";
			this->QuitToolStripMenuItem->Click += gcnew System::EventHandler(this, &FormMain::QuitToolStripMenuItem_Click);
			// 
			// FunctionToolStripMenuItem
			// 
			this->FunctionToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->ViewTableToolStripMenuItem, 
				this->MapViewToolStripMenuItem, this->组屏展示ToolStripMenuItem});
			this->FunctionToolStripMenuItem->Name = L"FunctionToolStripMenuItem";
			this->FunctionToolStripMenuItem->Size = System::Drawing::Size(41, 20);
			this->FunctionToolStripMenuItem->Text = L"功能";
			// 
			// ViewTableToolStripMenuItem
			// 
			this->ViewTableToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->账户权益绩效统计ToolStripMenuItem, 
				this->账户交易绩效统计ToolStripMenuItem, this->账户持仓统计ToolStripMenuItem});
			this->ViewTableToolStripMenuItem->Name = L"ViewTableToolStripMenuItem";
			this->ViewTableToolStripMenuItem->Size = System::Drawing::Size(136, 22);
			this->ViewTableToolStripMenuItem->Text = L"视图报表";
			// 
			// 账户权益绩效统计ToolStripMenuItem
			// 
			this->账户权益绩效统计ToolStripMenuItem->Name = L"账户权益绩效统计ToolStripMenuItem";
			this->账户权益绩效统计ToolStripMenuItem->Size = System::Drawing::Size(166, 22);
			this->账户权益绩效统计ToolStripMenuItem->Text = L"账户权益绩效统计";
			this->账户权益绩效统计ToolStripMenuItem->Click += gcnew System::EventHandler(this, &FormMain::ReportView_Interest_MenuClick);
			// 
			// 账户交易绩效统计ToolStripMenuItem
			// 
			this->账户交易绩效统计ToolStripMenuItem->Name = L"账户交易绩效统计ToolStripMenuItem";
			this->账户交易绩效统计ToolStripMenuItem->Size = System::Drawing::Size(166, 22);
			this->账户交易绩效统计ToolStripMenuItem->Text = L"账户交易绩效统计";
			this->账户交易绩效统计ToolStripMenuItem->Click += gcnew System::EventHandler(this, &FormMain::ReportView_Trades_MenuClick);
			// 
			// 账户持仓统计ToolStripMenuItem
			// 
			this->账户持仓统计ToolStripMenuItem->Name = L"账户持仓统计ToolStripMenuItem";
			this->账户持仓统计ToolStripMenuItem->Size = System::Drawing::Size(166, 22);
			this->账户持仓统计ToolStripMenuItem->Text = L"账户持仓统计";
			this->账户持仓统计ToolStripMenuItem->Click += gcnew System::EventHandler(this, &FormMain::ReportView_Hold_Click);
			// 
			// MapViewToolStripMenuItem
			// 
			this->MapViewToolStripMenuItem->Name = L"MapViewToolStripMenuItem";
			this->MapViewToolStripMenuItem->Size = System::Drawing::Size(136, 22);
			this->MapViewToolStripMenuItem->Text = L"地图展示";
			this->MapViewToolStripMenuItem->Click += gcnew System::EventHandler(this, &FormMain::MapViewToolStripMenuItem_Click);
			// 
			// 组屏展示ToolStripMenuItem
			// 
			this->组屏展示ToolStripMenuItem->Name = L"组屏展示ToolStripMenuItem";
			this->组屏展示ToolStripMenuItem->Size = System::Drawing::Size(136, 22);
			this->组屏展示ToolStripMenuItem->Text = L"2*2组屏展示";
			this->组屏展示ToolStripMenuItem->Click += gcnew System::EventHandler(this, &FormMain::组屏展示ToolStripMenuItem_Click);
			// 
			// SetupToolStripMenuItem
			// 
			this->SetupToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->TableColumnSetupToolStripMenuItem});
			this->SetupToolStripMenuItem->Name = L"SetupToolStripMenuItem";
			this->SetupToolStripMenuItem->Size = System::Drawing::Size(41, 20);
			this->SetupToolStripMenuItem->Text = L"设置";
			// 
			// TableColumnSetupToolStripMenuItem
			// 
			this->TableColumnSetupToolStripMenuItem->Name = L"TableColumnSetupToolStripMenuItem";
			this->TableColumnSetupToolStripMenuItem->Size = System::Drawing::Size(130, 22);
			this->TableColumnSetupToolStripMenuItem->Text = L"表格列设置";
			// 
			// MessageToolStripMenuItem
			// 
			this->MessageToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->RiskMessageNoticeToolStripMenuItem});
			this->MessageToolStripMenuItem->Name = L"MessageToolStripMenuItem";
			this->MessageToolStripMenuItem->Size = System::Drawing::Size(41, 20);
			this->MessageToolStripMenuItem->Text = L"消息";
			// 
			// RiskMessageNoticeToolStripMenuItem
			// 
			this->RiskMessageNoticeToolStripMenuItem->Name = L"RiskMessageNoticeToolStripMenuItem";
			this->RiskMessageNoticeToolStripMenuItem->Size = System::Drawing::Size(142, 22);
			this->RiskMessageNoticeToolStripMenuItem->Text = L"风险消息通知";
			this->RiskMessageNoticeToolStripMenuItem->Click += gcnew System::EventHandler(this, &FormMain::RiskMessageNoticeToolStripMenuItem_Click);
			// 
			// InquiryToolStripMenuItem
			// 
			this->InquiryToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(9) {this->TodayTableInquiryToolStripMenuItem, 
				this->TodayTradeInquiryToolStripMenuItem, this->TodayHoldInquiryToolStripMenuItem, this->TodayMoneyInquiryToolStripMenuItem, 
				this->TodayOutInMoneyInquiryToolStripMenuItem, this->InvestorInfoInquiryToolStripMenuItem, this->MessageNotifyInquiryToolStripMenuItem, 
				this->UserEventInquiryToolStripMenuItem, this->FundNetValueInquiryToolStripMenuItem});
			this->InquiryToolStripMenuItem->Name = L"InquiryToolStripMenuItem";
			this->InquiryToolStripMenuItem->Size = System::Drawing::Size(41, 20);
			this->InquiryToolStripMenuItem->Text = L"查询";
			// 
			// TodayTableInquiryToolStripMenuItem
			// 
			this->TodayTableInquiryToolStripMenuItem->Name = L"TodayTableInquiryToolStripMenuItem";
			this->TodayTableInquiryToolStripMenuItem->Size = System::Drawing::Size(166, 22);
			this->TodayTableInquiryToolStripMenuItem->Text = L"当日报单查询";
			this->TodayTableInquiryToolStripMenuItem->Click += gcnew System::EventHandler(this, &FormMain::TodayTableInquiryToolStripMenuItem_Click);
			// 
			// TodayTradeInquiryToolStripMenuItem
			// 
			this->TodayTradeInquiryToolStripMenuItem->Name = L"TodayTradeInquiryToolStripMenuItem";
			this->TodayTradeInquiryToolStripMenuItem->Size = System::Drawing::Size(166, 22);
			this->TodayTradeInquiryToolStripMenuItem->Text = L"当日成交查询";
			this->TodayTradeInquiryToolStripMenuItem->Click += gcnew System::EventHandler(this, &FormMain::TodayTradeInquiryToolStripMenuItem_Click);
			// 
			// TodayHoldInquiryToolStripMenuItem
			// 
			this->TodayHoldInquiryToolStripMenuItem->Name = L"TodayHoldInquiryToolStripMenuItem";
			this->TodayHoldInquiryToolStripMenuItem->Size = System::Drawing::Size(166, 22);
			this->TodayHoldInquiryToolStripMenuItem->Text = L"当日持仓查询";
			this->TodayHoldInquiryToolStripMenuItem->Click += gcnew System::EventHandler(this, &FormMain::TodayHoldInquiryToolStripMenuItem_Click);
			// 
			// TodayMoneyInquiryToolStripMenuItem
			// 
			this->TodayMoneyInquiryToolStripMenuItem->Name = L"TodayMoneyInquiryToolStripMenuItem";
			this->TodayMoneyInquiryToolStripMenuItem->Size = System::Drawing::Size(166, 22);
			this->TodayMoneyInquiryToolStripMenuItem->Text = L"当日资金查询";
			this->TodayMoneyInquiryToolStripMenuItem->Click += gcnew System::EventHandler(this, &FormMain::TodayMoneyInquiryToolStripMenuItem_Click);
			// 
			// TodayOutInMoneyInquiryToolStripMenuItem
			// 
			this->TodayOutInMoneyInquiryToolStripMenuItem->Name = L"TodayOutInMoneyInquiryToolStripMenuItem";
			this->TodayOutInMoneyInquiryToolStripMenuItem->Size = System::Drawing::Size(166, 22);
			this->TodayOutInMoneyInquiryToolStripMenuItem->Text = L"当日出入金查询";
			this->TodayOutInMoneyInquiryToolStripMenuItem->Click += gcnew System::EventHandler(this, &FormMain::TodayOutInMoneyInquiryToolStripMenuItem_Click);
			// 
			// InvestorInfoInquiryToolStripMenuItem
			// 
			this->InvestorInfoInquiryToolStripMenuItem->Name = L"InvestorInfoInquiryToolStripMenuItem";
			this->InvestorInfoInquiryToolStripMenuItem->Size = System::Drawing::Size(166, 22);
			this->InvestorInfoInquiryToolStripMenuItem->Text = L"投资者信息查询";
			this->InvestorInfoInquiryToolStripMenuItem->Click += gcnew System::EventHandler(this, &FormMain::InvestorInfoInquiryToolStripMenuItem_Click);
			// 
			// MessageNotifyInquiryToolStripMenuItem
			// 
			this->MessageNotifyInquiryToolStripMenuItem->Name = L"MessageNotifyInquiryToolStripMenuItem";
			this->MessageNotifyInquiryToolStripMenuItem->Size = System::Drawing::Size(166, 22);
			this->MessageNotifyInquiryToolStripMenuItem->Text = L"消息通知查询";
			this->MessageNotifyInquiryToolStripMenuItem->Click += gcnew System::EventHandler(this, &FormMain::MessageNotifyInquiryToolStripMenuItem_Click);
			// 
			// UserEventInquiryToolStripMenuItem
			// 
			this->UserEventInquiryToolStripMenuItem->Name = L"UserEventInquiryToolStripMenuItem";
			this->UserEventInquiryToolStripMenuItem->Size = System::Drawing::Size(166, 22);
			this->UserEventInquiryToolStripMenuItem->Text = L"用户事件查询";
			this->UserEventInquiryToolStripMenuItem->Click += gcnew System::EventHandler(this, &FormMain::UserEventInquiryToolStripMenuItem_Click);
			// 
			// FundNetValueInquiryToolStripMenuItem
			// 
			this->FundNetValueInquiryToolStripMenuItem->Name = L"FundNetValueInquiryToolStripMenuItem";
			this->FundNetValueInquiryToolStripMenuItem->Size = System::Drawing::Size(166, 22);
			this->FundNetValueInquiryToolStripMenuItem->Text = L"基金历史信息查询";
			this->FundNetValueInquiryToolStripMenuItem->Click += gcnew System::EventHandler(this, &FormMain::FundNetValueInquiryToolStripMenuItem_Click);
			// 
			// ForceToolStripMenuItem
			// 
			this->ForceToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->FastForceToolStripMenuItem, 
				this->ManualForceToolStripMenuItem});
			this->ForceToolStripMenuItem->Name = L"ForceToolStripMenuItem";
			this->ForceToolStripMenuItem->Size = System::Drawing::Size(41, 20);
			this->ForceToolStripMenuItem->Text = L"强平";
			// 
			// FastForceToolStripMenuItem
			// 
			this->FastForceToolStripMenuItem->Name = L"FastForceToolStripMenuItem";
			this->FastForceToolStripMenuItem->Size = System::Drawing::Size(118, 22);
			this->FastForceToolStripMenuItem->Text = L"快捷强平";
			this->FastForceToolStripMenuItem->Click += gcnew System::EventHandler(this, &FormMain::FastForceToolStripMenuItem_Click);
			// 
			// ManualForceToolStripMenuItem
			// 
			this->ManualForceToolStripMenuItem->Name = L"ManualForceToolStripMenuItem";
			this->ManualForceToolStripMenuItem->Size = System::Drawing::Size(118, 22);
			this->ManualForceToolStripMenuItem->Text = L"手动强平";
			this->ManualForceToolStripMenuItem->Click += gcnew System::EventHandler(this, &FormMain::ManualForceToolStripMenuItem_Click);
			// 
			// HelpToolStripMenuItem
			// 
			this->HelpToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->VersionInfoToolStripMenuItem, 
				this->HelpDocToolStripMenuItem});
			this->HelpToolStripMenuItem->Name = L"HelpToolStripMenuItem";
			this->HelpToolStripMenuItem->Size = System::Drawing::Size(41, 20);
			this->HelpToolStripMenuItem->Text = L"帮助";
			// 
			// VersionInfoToolStripMenuItem
			// 
			this->VersionInfoToolStripMenuItem->Name = L"VersionInfoToolStripMenuItem";
			this->VersionInfoToolStripMenuItem->Size = System::Drawing::Size(118, 22);
			this->VersionInfoToolStripMenuItem->Text = L"版本信息";
			// 
			// HelpDocToolStripMenuItem
			// 
			this->HelpDocToolStripMenuItem->Name = L"HelpDocToolStripMenuItem";
			this->HelpDocToolStripMenuItem->Size = System::Drawing::Size(118, 22);
			this->HelpDocToolStripMenuItem->Text = L"帮助文档";
			// 
			// toolStrip1
			// 
			this->toolStrip1->Location = System::Drawing::Point(0, 24);
			this->toolStrip1->Name = L"toolStrip1";
			this->toolStrip1->Size = System::Drawing::Size(734, 25);
			this->toolStrip1->TabIndex = 2;
			this->toolStrip1->Text = L"toolStrip1";
			// 
			// MainWndClientPanel
			// 
			this->MainWndClientPanel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->MainWndClientPanel->Location = System::Drawing::Point(0, 49);
			this->MainWndClientPanel->Name = L"MainWndClientPanel";
			this->MainWndClientPanel->Size = System::Drawing::Size(734, 332);
			this->MainWndClientPanel->TabIndex = 3;
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Interval = 1000;
			this->timer1->Tick += gcnew System::EventHandler(this, &FormMain::timer1_Tick);
			// 
			// FormMain
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(734, 403);
			this->Controls->Add(this->MainWndClientPanel);
			this->Controls->Add(this->toolStrip1);
			this->Controls->Add(this->statusStrip1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"FormMain";
			this->Text = L"中期风控终端";
			this->Load += gcnew System::EventHandler(this, &FormMain::FormMain_Load);
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &FormMain::FormMain_FormClosing);
			this->statusStrip1->ResumeLayout(false);
			this->statusStrip1->PerformLayout();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) 
			 {
			 }


			 //重载WndProc，以处理WM_COMMAND消息
	protected:virtual void WndProc( Message% m ) override
			{
				if (  m.Msg == WM_COMMAND_Win && m.WParam.ToInt32()==WndCmd_DataArrival )
				{
					CTcpLayer::ParseRecvPackageInWindowThread();						
				}
				else  if (  m.Msg == WM_COMMAND_Win && m.WParam.ToInt32()==WndCmd_YourPkgArrival )
				{
					char *p = (char*)m.LParam.ToInt32();
					Stru_UniPkgHead head;					
					memset(&head, 0, sizeof(head));
					memcpy(&head, p, sizeof(head));
					switch(head.cmdid)
					{
					case Cmd_RM_QryAssetMgmtOrg_Rsp:
						{
							if ( head.userdata1 == OPERATOR_SUCCESS )
							{
								MAPAssetMgmtOrg mapAssetMgmtOrg;
								int nCount = head.len / sizeof(AssetMgmtOrganization);
								for ( int i = 0; i < nCount; i++ )
								{
									AssetMgmtOrganization* pAssetMgmtOrg = (AssetMgmtOrganization*)((char*)(p+sizeof(Stru_UniPkgHead)) + i*sizeof(AssetMgmtOrganization));
									mapAssetMgmtOrg[pAssetMgmtOrg->nAssetMgmtOrgID] = *pAssetMgmtOrg;
								}
								m_pdataInfo->SetAeestMgmtOrg(mapAssetMgmtOrg);
								if(head.userdata2 == head.userdata3 -1)
									m_pdataInfo->FinishAeestMgmtOrganization(true);

								double dbPercent = m_pdataInfo->GetinitProgress();
								char strPercent[128];
								sprintf(strPercent, "%0.0f%%", dbPercent*100);
								this->toolStripStatusLabel2->Text = Tools::string2String(strPercent);
								this->toolStripProgressBar1->Value = (int)(dbPercent*100);

							}
							else
							{
								string str = (char*)(p+sizeof(Stru_UniPkgHead));
								String^ strtemp = Tools::string2String(str.c_str());
								MessageBox::Show(strtemp, "提示",MessageBoxButtons::OK);
							}
							break;
						}
					case Cmd_RM_QryFinancialProduct_Rsp:
						{
							if ( head.userdata1 == OPERATOR_SUCCESS )
							{
								int nCount = head.len / sizeof(FinancialProduct);
								for ( int i = 0; i < nCount; i++ )
								{
									FinancialProduct* pFinancialProduct = (FinancialProduct*)((char*)(p+sizeof(Stru_UniPkgHead)) + i*sizeof(FinancialProduct));
									m_pdataInfo->SetFinancialProduct(pFinancialProduct);									
								}
								if(head.userdata2 == head.userdata3 -1)
									m_pdataInfo->FinishFinancialProduct(true);

								double dbPercent = m_pdataInfo->GetinitProgress();
								char strPercent[128];
								sprintf(strPercent, "%0.0f%%", dbPercent*100);
								this->toolStripStatusLabel2->Text = Tools::string2String(strPercent);
								this->toolStripProgressBar1->Value = (int)(dbPercent*100);
							}
							else
							{
								string str = (char*)(p+sizeof(Stru_UniPkgHead));
								String^ strtemp = Tools::string2String(str.c_str());
								MessageBox::Show(strtemp, "提示",MessageBoxButtons::OK);
							}
							break;
						}				
					case Cmd_RM_QryRiskIndModule_Rsp:
						{
							if ( head.userdata1 == OPERATOR_SUCCESS )
							{
								int nCount = head.len / sizeof(RiskIndicatorModule);
								for ( int i = 0; i < nCount; i++ )
								{
									RiskIndicatorModule* pIndModule = (RiskIndicatorModule*)((char*)(p+sizeof(Stru_UniPkgHead)) + i*sizeof(RiskIndicatorModule));
									m_pdataInfo->SetRiskIndicatorModule(pIndModule);	
								}
								if(head.userdata2 == head.userdata3 -1)
									m_pdataInfo->FinishRiskIndicatorModule(true);

								double dbPercent = m_pdataInfo->GetinitProgress();
								char strPercent[128];
								sprintf(strPercent, "%0.0f%%", dbPercent*100);
								this->toolStripStatusLabel2->Text = Tools::string2String(strPercent);
								this->toolStripProgressBar1->Value = (int)(dbPercent*100);
							}
							else
							{
								string str = (char*)(p+sizeof(Stru_UniPkgHead));
								String^ strtemp = Tools::string2String(str.c_str());
								MessageBox::Show(strtemp, "提示",MessageBoxButtons::OK);
							}
							break;
						}
					case Cmd_RM_QryRiskIndicator_Rsp:
						{
							if ( head.userdata1 == OPERATOR_SUCCESS )
							{
								int nCount = head.len / sizeof(RiskIndicator);
								for ( int i = 0; i < nCount; i++ )
								{
									RiskIndicator* pIndModule = (RiskIndicator*)((char*)(p+sizeof(Stru_UniPkgHead)) + i*sizeof(RiskIndicator));
									m_pdataInfo->SetRiskIndicator(pIndModule);	
								}
								if(head.userdata2 == head.userdata3 -1)
									m_pdataInfo->FinishRiskIndicator(true);

								double dbPercent = m_pdataInfo->GetinitProgress();
								char strPercent[128];
								sprintf(strPercent, "%0.0f%%", dbPercent*100);
								this->toolStripStatusLabel2->Text = Tools::string2String(strPercent);
								this->toolStripProgressBar1->Value = (int)(dbPercent*100);
							}
							else
							{
								string str = (char*)(p+sizeof(Stru_UniPkgHead));
								String^ strtemp = Tools::string2String(str.c_str());
								MessageBox::Show(strtemp, "提示",MessageBoxButtons::OK);
							}
							break;							
						}
					case Cmd_RM_QryTradeAccountByOrgID_Rsp:
						{
							if ( head.userdata1 == OPERATOR_SUCCESS )
							{
								int nCount = head.len / sizeof(TrustTradeAccount);
								for ( int i = 0; i < nCount; i++ )
								{
									TrustTradeAccount* pIndModule = (TrustTradeAccount*)((char*)(p+sizeof(Stru_UniPkgHead)) + i*sizeof(TrustTradeAccount));
									m_pdataInfo->SetTrustTradeAccount(pIndModule);	
									m_pdataInfo->SetOrgID2TrustTradeAccount(pIndModule);	
									m_pdataInfo->SetFinancialID2TrustTradeAccount(pIndModule);
								}
								if(head.userdata2 == head.userdata3 -1)
								{
									m_pdataInfo->FinishTrustTradeAccount(true);
									MAPTrustTradeAccount mapTrustTradeAccount;
									m_pdataInfo->GetTrustTradeAccount(mapTrustTradeAccount);	

									LoginRsp loginRsp;
									m_pdataInfo->GetLoginRsp(loginRsp); 
									MAPTrustTradeAccount::iterator it = mapTrustTradeAccount.begin();
									for(; it != mapTrustTradeAccount.end(); )
									{//不监控资管组织iD和理财产品与登录风控员不一样的情况
										TrustTradeAccount tAccount = it->second;
										if(tAccount.nAssetMgmtOrgID != loginRsp.nAssetMgmtOrgID 
										|| tAccount.nFinancialProductID != loginRsp.nFinancialProductID)
											it = mapTrustTradeAccount.erase(it);
										else
											++it;										
									}
									
									int nSize = mapTrustTradeAccount.size();
									m_nAccountCount = nSize;//需要请求风险预警信息的账号数目
									if(m_nAccountCount == 0)//没有任何需要监控的账号，则这一项初始化没有必要
										m_pdataInfo->FinishProductRiskWarning(true);
									if(nSize >0)
									{
										int *p = new int[nSize];
										int i = 0;
										for(MAPTrustTradeAccount::iterator it = mapTrustTradeAccount.begin(); it != mapTrustTradeAccount.end(); it++)
										{
											int nAccount = it->first;
											p[i++] = nAccount;
											//查询品种风险预警信息
											CTcpLayer::SendData(Cmd_RM_QryProductRiskWarning_Req, &nAccount, sizeof(int), 0);
										}
										//订阅风险事件请求										
										CTcpLayer::SendData(Cmd_RM_SubscribeRiskEvent_Req, (void *)p, sizeof(int)*nSize, 0);
										//订阅风险事件处理请求
										CTcpLayer::SendData(Cmd_RM_SubscribeRiskEvtHandling_Req, (void *)p, sizeof(int)*nSize, 0);
										//订阅所有账户资金信息
										CTcpLayer::SendData(Cmd_RM_SubscribeFund_Req, (void *)p, sizeof(int)*nSize, 0);
										RiskEvtModule->DlgAllAccountFundInfo1->SetAllQueryAccout();
										delete []p;
									}
								}
								double dbPercent = m_pdataInfo->GetinitProgress();
								char strPercent[128];
								sprintf(strPercent, "%0.0f%%", dbPercent*100);
								this->toolStripStatusLabel2->Text = Tools::string2String(strPercent);
								this->toolStripProgressBar1->Value = (int)(dbPercent*100);
							}
							else
							{
								string str = (char*)(p+sizeof(Stru_UniPkgHead));
								String^ strtemp = Tools::string2String(str.c_str());
								MessageBox::Show(strtemp, "提示",MessageBoxButtons::OK);
							}
							break;
						}
					case Cmd_RM_QryTraderByOrgID_Rsp:
						{
							if ( head.userdata1 == OPERATOR_SUCCESS )
							{
								int nCount = head.len / sizeof(TraderInfo);
								for ( int i = 0; i < nCount; i++ )
								{
									TraderInfo* pIndModule = (TraderInfo*)((char*)(p+sizeof(Stru_UniPkgHead)) + i*sizeof(TraderInfo));
									m_pdataInfo->SetTraderInfo(pIndModule);	
								}
								if(head.userdata2 == head.userdata3 -1)
									m_pdataInfo->FinishTraderInfo(true);

								double dbPercent = m_pdataInfo->GetinitProgress();
								char strPercent[128];
								sprintf(strPercent, "%0.0f%%", dbPercent*100);
								this->toolStripStatusLabel2->Text = Tools::string2String(strPercent);
								this->toolStripProgressBar1->Value = (int)(dbPercent*100);
							}
							else
							{
								string str = (char*)(p+sizeof(Stru_UniPkgHead));
								String^ strtemp = Tools::string2String(str.c_str());
								MessageBox::Show(strtemp, "提示",MessageBoxButtons::OK);
							}
							break;								
						}
					case Cmd_RM_QryAssetOrgProRelation_Rsp:
						{
							if ( head.userdata1 == OPERATOR_SUCCESS )
							{
								int nCount = head.len / sizeof(AssetOrgProRelation);
								for ( int i = 0; i < nCount; i++ )
								{
									AssetOrgProRelation* pAOPR = (AssetOrgProRelation*)((char*)(p+sizeof(Stru_UniPkgHead)) + i*sizeof(AssetOrgProRelation));
									m_pdataInfo->SetMulmapMgmtOrg2Financial(pAOPR);									
								}
								if(head.userdata2 == head.userdata3 -1)
									m_pdataInfo->FinishMgmtOrg2Financial(true);

								double dbPercent = m_pdataInfo->GetinitProgress();
								char strPercent[128];
								sprintf(strPercent, "%0.0f%%", dbPercent*100);
								this->toolStripStatusLabel2->Text = Tools::string2String(strPercent);
								this->toolStripProgressBar1->Value = (int)(dbPercent*100);
							}
							else
							{
								string str = (char*)(p+sizeof(Stru_UniPkgHead));
								String^ strtemp = Tools::string2String(str.c_str());
								MessageBox::Show(strtemp, "提示",MessageBoxButtons::OK);
							}
							break;
						}
					case Cmd_RM_InstrumentInfoList_Rsp:
						{
							if ( head.userdata1 == OPERATOR_SUCCESS )
							{
								int nCount = head.len / sizeof(InstrumentField);
								for ( int i = 0; i < nCount; i++ )
								{
									InstrumentField* pIndModule = (InstrumentField*)((char*)(p+sizeof(Stru_UniPkgHead)) + i*sizeof(InstrumentField));
									m_pdataInfo->SetInstrumentField(pIndModule);	
								}
								if(head.userdata2 == head.userdata3 -1)
									m_pdataInfo->FinishInstrumentField(true);

								double dbPercent = m_pdataInfo->GetinitProgress();
								char strPercent[128];
								sprintf(strPercent, "%0.0f%%", dbPercent*100);
								this->toolStripStatusLabel2->Text = Tools::string2String(strPercent);
								this->toolStripProgressBar1->Value = (int)(dbPercent*100);
							}
							else
							{
								string str = (char*)(p+sizeof(Stru_UniPkgHead));
								String^ strtemp = Tools::string2String(str.c_str());
								MessageBox::Show(strtemp, "提示",MessageBoxButtons::OK);
							}
							break;								
						}
					case Cmd_RM_QryPermissionValueByID_Rsp :
						{
							int nCount = head.len / sizeof(PermissionValue);
							for ( int i = 0; i < nCount; i++ )
							{
								PermissionValue* pIndModule = (PermissionValue*)((char*)(p+sizeof(Stru_UniPkgHead)) + i*sizeof(PermissionValue));
								m_pdataInfo->SetPermissionValue(pIndModule);	
							}
							if(head.userdata2 == head.userdata3 -1)
								m_pdataInfo->FinishPermissionValue(true);


							double dbPercent = m_pdataInfo->GetinitProgress();
							char strPercent[128];
							sprintf(strPercent, "%0.0f%%", dbPercent*100);
							this->toolStripStatusLabel2->Text = Tools::string2String(strPercent);
							this->toolStripProgressBar1->Value = (int)(dbPercent*100);

                            //风控终端权限
                            bool bPermission = false;
                            if(m_pdataInfo != NULL)
                            {
                                bPermission = m_pdataInfo->HasPermission(FORMS_STATISTICS);
                                if(!bPermission)
                                    ViewTableToolStripMenuItem->Enabled = bPermission;
                                bPermission = m_pdataInfo->HasPermission(MESSAGE_SEND);
                                if(!bPermission)
                                    RiskMessageNoticeToolStripMenuItem->Enabled = bPermission;
                                bPermission = m_pdataInfo->HasPermission(TODAY_OPEN_ORDER_QUERY);
                                if(!bPermission)
                                    TodayTableInquiryToolStripMenuItem->Enabled = bPermission;
                                bPermission = m_pdataInfo->HasPermission(TODAY_TRADE_QUERY);
                                if(!bPermission)
                                    TodayTradeInquiryToolStripMenuItem->Enabled = bPermission;
                                bPermission = m_pdataInfo->HasPermission(TODAY_POSITION_QUERY);
                                if(!bPermission)
                                    TodayHoldInquiryToolStripMenuItem->Enabled = bPermission;
                                bPermission = m_pdataInfo->HasPermission(TODAY_ACCOUNT_QUERY);
                                if(!bPermission)
                                    TodayMoneyInquiryToolStripMenuItem->Enabled = bPermission;
                                bPermission = m_pdataInfo->HasPermission(TODAY_DEPOSIT_QUERY);
                                if(!bPermission)
                                    TodayOutInMoneyInquiryToolStripMenuItem->Enabled = bPermission;
                                bPermission = m_pdataInfo->HasPermission(INVESTOR_INFO_QUERY);
                                if(!bPermission)
                                    InvestorInfoInquiryToolStripMenuItem->Enabled = bPermission;
                                bPermission = m_pdataInfo->HasPermission(UNREAD_MSG_QUERY);
                                if(!bPermission)
                                    MessageNotifyInquiryToolStripMenuItem->Enabled = bPermission;
                                bPermission = m_pdataInfo->HasPermission(RISK_EVENT_QUERY);
                                if(!bPermission)
                                    UserEventInquiryToolStripMenuItem->Enabled = bPermission;
                                bPermission = m_pdataInfo->HasPermission(FORCE_CLOSE_ORDER);
                                    ForceToolStripMenuItem->Enabled = bPermission;

                                    FastForceToolStripMenuItem->Enabled = false;//快捷强平暂时不可用
                            }

							break;
						}
					case Cmd_RM_QryAccountByOrgID_Rsp:
						{
							if ( head.userdata1 == OPERATOR_SUCCESS )
							{
								int nCount = head.len / sizeof(RiskMgmtUserInfo);
								for ( int i = 0; i < nCount; i++ )
								{
									RiskMgmtUserInfo* pIndModule = (RiskMgmtUserInfo*)((char*)(p+sizeof(Stru_UniPkgHead)) + i*sizeof(RiskMgmtUserInfo));
									m_pdataInfo->SetRiskMgmtUserInfo(pIndModule);	
								}
								if(head.userdata2 == head.userdata3 -1)
									m_pdataInfo->FinishRiskMgmtUserInfo(true);

								double dbPercent = m_pdataInfo->GetinitProgress();
								char strPercent[128];
								sprintf(strPercent, "%0.0f%%", dbPercent*100);
								this->toolStripStatusLabel2->Text = Tools::string2String(strPercent);
								this->toolStripProgressBar1->Value = (int)(dbPercent*100);

								
							}
							else
							{
								string str = (char*)(p+sizeof(Stru_UniPkgHead));
								String^ strtemp = Tools::string2String(str.c_str());
								MessageBox::Show(strtemp, "提示",MessageBoxButtons::OK);
							}
							break;								
						}
                    case Cmd_RM_SendUnReadMessage_Push://消息通知提示
                        {
                            if ( head.userdata1 == OPERATOR_SUCCESS )
                            {                                
                                int nCount = head.len / sizeof(MessageInfo);
                                for ( int i = 0; i < nCount; i++ )
                                {
                                    MessageInfo* pMessageInfo = (MessageInfo*)((char*)(p+sizeof(Stru_UniPkgHead)) + i*sizeof(MessageInfo));

                                    if(RiskMsgNotifyTipModule == nullptr)                                    
                                        RiskMsgNotifyTipModule = (gcnew RiskMsgNotifyTip);  

                                    RiskMsgNotifyTipModule->UpdateContent(*pMessageInfo);
                                    RiskMsgNotifyTipModule->Show();                                     
                                }
                            }

                            break;
                        }
                    case Cmd_RM_SendUnReadMessage_Rsp://未通知到的消息
                        {
                            if ( head.userdata1 == OPERATOR_SUCCESS )
                            {                                
                                int nCount = head.len / sizeof(MessageInfo);
                                for ( int i = 0; i < nCount; i++ )
                                {
                                    MessageInfo* pMessageInfo = (MessageInfo*)((char*)(p+sizeof(Stru_UniPkgHead)) + i*sizeof(MessageInfo));
                                    
                                    if(RiskMsgNotifyTipModule == nullptr)                                    
                                        RiskMsgNotifyTipModule = (gcnew RiskMsgNotifyTip);  
                                    
                                    RiskMsgNotifyTipModule->UpdateContent(*pMessageInfo);
                                    RiskMsgNotifyTipModule->Show();                                     
                                }
                            }
                            
                            break;
						}
					case Cmd_RM_QryProductRiskWarning_Rsp:
						{//按品种查询风险预警返回
							if ( head.userdata1 == OPERATOR_SUCCESS )
							{
								int nCount = head.len / sizeof(ProductRiskWarning);
								for ( int i = 0; i < nCount; i++ )
								{
									ProductRiskWarning* pIndModule = (ProductRiskWarning*)((char*)(p+sizeof(Stru_UniPkgHead)) + i*sizeof(ProductRiskWarning));
									
									m_pdataInfo->SetProductRiskWarning(pIndModule);	
								}
								if(head.userdata2 == head.userdata3 -1)
								{
									--m_nAccountCount;
									if(m_nAccountCount == 0)
									{
										m_pdataInfo->FinishProductRiskWarning(true);
										if(m_pdataInfo->IsInit())
										{
											login->Close();
											ShowStatus(false);
										}
									}
								}

								double dbPercent = m_pdataInfo->GetinitProgress();
								char strPercent[128];
								sprintf(strPercent, "%0.0f%%", dbPercent*100);
								this->toolStripStatusLabel2->Text = Tools::string2String(strPercent);
								this->toolStripProgressBar1->Value = (int)(dbPercent*100);

								
							}
							else
							{
								string str = (char*)(p+sizeof(Stru_UniPkgHead));
								String^ strtemp = Tools::string2String(str.c_str());
								MessageBox::Show(strtemp, "提示",MessageBoxButtons::OK);
							}

							break;
						}
					case Cmd_RM_QryRiskWarning_Rsp:
						{//查询风险预警返回
							if ( head.userdata1 == OPERATOR_SUCCESS )
							{
								int nCount = head.len / sizeof(RiskWarning);
								for ( int i = 0; i < nCount; i++ )
								{
									RiskWarning* pIndModule = (RiskWarning*)((char*)(p+sizeof(Stru_UniPkgHead)) + i*sizeof(RiskWarning));

									m_pdataInfo->SetRiskWarning(pIndModule);	
								}
								if(head.userdata2 == head.userdata3 -1)
								{
									m_pdataInfo->FinishRiskWarning(true);
									if(m_pdataInfo->IsInit())
									{
										login->Close();
										ShowStatus(false);
									}
								}

								double dbPercent = m_pdataInfo->GetinitProgress();
								char strPercent[128];
								sprintf(strPercent, "%0.0f%%", dbPercent*100);
								this->toolStripStatusLabel2->Text = Tools::string2String(strPercent);
								this->toolStripProgressBar1->Value = (int)(dbPercent*100);

								
							}
							else
							{
								string str = (char*)(p+sizeof(Stru_UniPkgHead));
								String^ strtemp = Tools::string2String(str.c_str());
								MessageBox::Show(strtemp, "提示",MessageBoxButtons::OK);
							}

							break;
						}
					}
						
					
				}

				Form::WndProc ( m );
			}
	private: System::Void Base_Load(System::Object^  sender, System::EventArgs^  e)
			 {
				 //订阅事件
				 IntPtr hWnd=this->Handle;
				 //所有资管中心详情
				 CTcpLayer::SubscribePkg(Cmd_RM_QryAssetMgmtOrg_Rsp, (int)(hWnd.ToInt32()));
				 //查询理财产品信息
				 CTcpLayer::SubscribePkg(Cmd_RM_QryFinancialProduct_Rsp, (int)(hWnd.ToInt32()));
				 //查询资管组织与理财产品关系
				 CTcpLayer::SubscribePkg(Cmd_RM_QryAssetOrgProRelation_Rsp, (int)(hWnd.ToInt32()));
				 //查询风险指标模型信息
				 CTcpLayer::SubscribePkg(Cmd_RM_QryRiskIndModule_Rsp, (int)(hWnd.ToInt32()));
				 //查询风险指标信息
				 CTcpLayer::SubscribePkg(Cmd_RM_QryRiskIndicator_Rsp, (int)(hWnd.ToInt32()));
				 //所有委托交易账号查询
				 CTcpLayer::SubscribePkg(Cmd_RM_QryTradeAccountByOrgID_Rsp, (int)(hWnd.ToInt32()));
				 //查询交易员信息
				 CTcpLayer::SubscribePkg(Cmd_RM_QryTraderByOrgID_Rsp, (int)(hWnd.ToInt32()));			
				 //合约详情列表
				 CTcpLayer::SubscribePkg(Cmd_RM_InstrumentInfoList_Rsp, (int)(hWnd.ToInt32()));	
				 //查询权限内容返回
				 CTcpLayer::SubscribePkg(Cmd_RM_QryPermissionValueByID_Rsp, (int)(hWnd.ToInt32()));	
				 //查询某资管组织下属所有账号请求
				 CTcpLayer::SubscribePkg(Cmd_RM_QryAccountByOrgID_Rsp, (int)(hWnd.ToInt32()));
				 //查询品种风险预警信息
				 CTcpLayer::SubscribePkg(Cmd_RM_QryProductRiskWarning_Rsp, (int)(hWnd.ToInt32()));
				 //查询风险预警
				 CTcpLayer::SubscribePkg(Cmd_RM_QryRiskWarning_Rsp, (int)(hWnd.ToInt32()));
                 //查询尚未接收的消息列表
                 CTcpLayer::SubscribePkg(Cmd_RM_SendUnReadMessage_Rsp,(int)(hWnd.ToInt32()));
                 //订阅消息推送
                 CTcpLayer::SubscribePkg(Cmd_RM_SendUnReadMessage_Push,(int)(hWnd.ToInt32()));
			 }

		//Form要关闭时，先停止CTcpLayer的网络收发工作
	private: System::Void Form1_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) 
		 {
		 }

	private: System::Void FormMain_Load(System::Object^  sender, System::EventArgs^  e) 
		 {
			 //Form加载后，将主窗口句柄设置到TcpLayer中去
			 IntPtr hWnd=this->Handle;
			 CTcpLayer::SetMainWndHandle((int)(hWnd.ToInt32()));
			 Base_Load(sender, e);
			 //加载风险事件模块
			 RiskEvtModule = (gcnew RiskEvt());
			 RiskEvtModule->TopLevel=false;
			 RiskEvtModule->Parent=MainWndClientPanel;
			 RiskEvtModule->Dock = System::Windows::Forms::DockStyle::Fill;
			 RiskEvtModule->Show();
			 this->RiskEvtModule->VibrateEvent1 += gcnew RiskEvt::VibrateEventHandler(this, &FormMain::Vibrate);
			 this->RiskEvtModule->CurRiskEventPanel1->CurRiskEvent_FastForce += gcnew CurRiskEventPanel::CurRiskEvent_FastForceEventHandler(this, &FormMain::FastForce);
			 this->RiskEvtModule->CurRiskEventPanel1->CurRiskEvent_ManualForce += gcnew CurRiskEventPanel::CurRiskEvent_ManualForceEventHandler(this, &FormMain::ManualForce);

			 dlgOrderInfoObject = gcnew DlgRealTimeOrderInfo();
			 dlgTradeInfoObject = gcnew CDlgRealTimeTradeInfo();
			 dlgPositionInfoObject = gcnew CDlgRealTimePositionInfo();
			 dlgPositionInfoObject->SetRiskEvtModule(RiskEvtModule);
			 dlgFundInfoObject = gcnew CDlgRealTimeFundInfo();

			 login = gcnew Login;
			 this->login->LoginEvent1 += gcnew Login::LoginEventEventHandler(this, &FormMain::Login_Event);

			 if(m_bAutoStart)
			 {//带两个命令行参数（用户名， 密码）就自动登录
				 login->SetAutoStartPara(m_strAutoStartName, m_strAutoPassword);			 
				
				 login->LoginClick(); 							
			 }			
			 login->ShowDialog(this);

             LoginRsp login;
             m_pdataInfo->GetLoginRsp(login);
             //请求尚未接收的消息列表
             CTcpLayer::SendData(Cmd_RM_QryUnReadMessage_Req, (void*)&login.nAccountID, sizeof(int), 0);

			 if(!m_pdataInfo->IsInit())
				 this->Close();

				
		 }
	private: System::Void FormMain_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) 
		 {
			 dlgOrderInfoObject->ReleaseForm();
			 dlgTradeInfoObject->ReleaseForm();
			 dlgPositionInfoObject->ReleaseForm();
			 dlgFundInfoObject->ReleaseForm();
			 CTcpLayer::Stop();
			 e->Cancel = false;
			 }

	private: System::Void TodayOutInMoneyInquiryToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) 
			 {
				 if(m_pdataInfo==NULL)
					 return;
				 if(m_pdataInfo->HasPermission(TODAY_DEPOSIT_QUERY)) 
				 {
					 if(QueryTransferModule != nullptr)
					 {
						 delete QueryTransferModule;
						 QueryTransferModule = nullptr;
					 }
					 {
						 //加载出入金查询模块
						 QueryTransferModule = (gcnew QueryTransfer());
						 QueryTransferModule->Show();
					 }


				 }
			 }
 public:void ShowStatus(bool bShow)
		{
			if(!bShow)
			{
				this->toolStripStatusLabel1->Text= "完成";
				this->toolStripStatusLabel2->Visible = false;
				this->toolStripProgressBar1->Visible = false;	
			}
			else
			{
				this->toolStripStatusLabel2->Visible = true;
				this->toolStripProgressBar1->Visible = true;

				this->toolStripStatusLabel1->Text = L"初始化：";
				double dbPercent = 0;
				char strPercent[128];
				sprintf(strPercent, "%0.0f%%", dbPercent*100);
				this->toolStripStatusLabel2->Text = Tools::string2String(strPercent);
				this->toolStripProgressBar1->Value = (int)(dbPercent*100);
			}
		}

public:void ShowDailogWithScreenConfig(AutoScreenConfig ^  nConfig,bool bAdjustSize,int nIndex)
	   {
		   System::Drawing::Size lSize =
			   System::Drawing::Size(System::Windows::Forms::Screen::PrimaryScreen->WorkingArea.Width/2,
			   System::Windows::Forms::Screen::PrimaryScreen->WorkingArea.Height/2);

			AutoScreenConfig ^ lConfig = nConfig;
			int i = nIndex;
		   if(lConfig)
		   {
			   if(lConfig->mnType == 1)
					 {
						 //组织机构
						 DepartmentShow ^ ltempShowForm = gcnew DepartmentShow();
						 ltempShowForm->CurrentOrgID = lConfig->mnOrgID;
						 if(bAdjustSize)
							 ltempShowForm->CombinationScreenSetting( Point( (i%2)*lSize.Width ,(i/2)*lSize.Height ),lSize);
						 ltempShowForm->Show();


					 }
			   if(lConfig->mnType == 2)
					 {
						 //理财产品
						 ProductShow ^ lp = gcnew ProductShow();
						 lp->CurrentOrgID = lConfig->mnOrgID;
						 lp->CurrentProductID =lConfig->mnProID;
						 lp->CurrentProductName = lConfig->msProName;
						 if(bAdjustSize)
							 lp->CombinationScreenSetting( Point( (i%2)*lSize.Width ,(i/2)*lSize.Height ),lSize);
						 lp->Show();

					 }
			   if(lConfig->mnType == 3)
					 {
						 //理财产品
						 RiskMapForm ^ lp = gcnew RiskMapForm();
					/*	 lp->CurrentOrgID = lConfig->mnOrgID;
						 lp->CurrentProductID =lConfig->mnProID;
						 lp->CurrentProductName = lConfig->msProName;*/
						 if(bAdjustSize)
							 lp->CombinationScreenSetting( Point( (i%2)*lSize.Width ,(i/2)*lSize.Height ),lSize);
						 lp->Show();

					 }
		   }
	   }
public:void ShowStatistics()
	   {
		  /* System::Object^  sender;
		   System::EventArgs^  e;
			组屏展示ToolStripMenuItem_Click(sender, e);*/
		   cliext::vector<AutoScreenConfig^>^ nScreensConfig = gcnew cliext::vector<AutoScreenConfig^>();
		   LoadAutoConfig(nScreensConfig);
	
		   if(nScreensConfig->size() != 4 && nScreensConfig->size() > 0)
		   {
			   ShowDailogWithScreenConfig(nScreensConfig[0],false,0);

		   }
		   else if(nScreensConfig->size() == 4)
		   {
			  for(int i = 0 ; i < 4 ; i ++)
			   {				  
				 ShowDailogWithScreenConfig(nScreensConfig[i],true,i);
			   }
		   }

		 
	   }
private: System::Void toolStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
#if 0
			 login = gcnew Login;
			 if(login->ShowDialog(this) == ::DialogResult::OK)
			 {
				 double dbPercent = 0;
				 char strPercent[128];
				 sprintf(strPercent, "%0.0f%%", dbPercent*100);
				 this->toolStripStatusLabel2->Text = Tools::string2String(strPercent);
				 this->toolStripProgressBar1->Value = (int)(dbPercent*100);
			 }
#endif
		 }
private: System::Void FastForceClick() 
		 {
			 //加载快捷强平模块(有所改动：因为风险事件和持仓没有必然联系所以也弹出手动强平窗口）
             RiskEvent riskEvent;
             RiskEvtModule->CurRiskEventPanel1->GetSelItemRiskEvent(riskEvent);
             if (riskEvent.nRiskEventID<0)
             {
                 string str = "没有选择合约，请点击列表选择";
                 String^ strtemp = Tools::string2String(str.c_str());
                 MessageBox::Show(strtemp, "提示",MessageBoxButtons::OK);
                 return;
             }

             TrustTradeAccount fP;
             m_pdataInfo->GetTrustTradeAccount(riskEvent.nTradeAccountID, fP);

			 BOOL bSelected = RiskEvtModule->CurRiskEventPanel1->TradeAccountHasRiskEvent(atoi(fP.szAccount));
			 if(bSelected)
			 {
				 //ForceShortcutModule = (gcnew ForceShortcutForm());
				 //ForceShortcutModule->ShowDialog();
				 ForceManualModule = (gcnew ForceManualForm());
                 ForceManualModule->SetTradeAccount(riskEvent.nTradeAccountID);
                 ForceManualModule->SetIndicatorLevel(riskEvent.nRiskLevelID);
                 ForceManualModule->ShowDialog();
			 }
			 else
			 {
				 string str = "没有触发风险事件，无法操作";
				 String^ strtemp = Tools::string2String(str.c_str());
				 MessageBox::Show(strtemp, "提示",MessageBoxButtons::OK);	
			 }
		 }
private: System::Void FastForceToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			FastForceClick();
         }
private: System::Void ManualForceClick() 
		 {
			 //加载手动强平模块
             RiskEvent riskEvent;
             RiskEvtModule->CurRiskEventPanel1->GetSelItemRiskEvent(riskEvent);
			 if (riskEvent.nRiskEventID<0)
			 {
				 string str = "没有选择合约，请点击列表选择";
				 String^ strtemp = Tools::string2String(str.c_str());
				 MessageBox::Show(strtemp, "提示",MessageBoxButtons::OK);
				 return;
			 }

             TrustTradeAccount fP;
             m_pdataInfo->GetTrustTradeAccount(riskEvent.nTradeAccountID, fP);

             BOOL bSelected = RiskEvtModule->CurRiskEventPanel1->TradeAccountHasRiskEvent(atoi(fP.szAccount));
			 if(bSelected)
			 {
				 ForceManualModule = (gcnew ForceManualForm());
				 ForceManualModule->SetTradeAccount(riskEvent.nTradeAccountID);
				 ForceManualModule->SetIndicatorLevel(riskEvent.nRiskLevelID);
				 ForceManualModule->ShowDialog();
			 }
			 else
			 {
				 string str = "没有触发风险事件，无法操作";
				 String^ strtemp = Tools::string2String(str.c_str());
				 MessageBox::Show(strtemp, "提示",MessageBoxButtons::OK);	
			 }
		 }
private: System::Void ManualForceToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
          ManualForceClick();    
     }
private: System::Void RiskMessageNoticeToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
          RiskMsgNotifyModule = (gcnew RiskMsgNotify());
          RiskMsgNotifyModule->ShowDialog();
      }
private: System::Void MessageNotifyInquiryToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if(m_pdataInfo==NULL)
				 return;
			 if(m_pdataInfo->HasPermission(UNREAD_MSG_QUERY))
			 {
				 //加载消息通知模块
				 if(QueryMeaasgeModule != nullptr)
				 {
					 delete QueryMeaasgeModule;
					 QueryMeaasgeModule = nullptr;
				 }

				 {

					 QueryMeaasgeModule = (gcnew QueryMeaasge());
					 QueryMeaasgeModule->Owner = this;
					 QueryMeaasgeModule->Show();
				 }
			 }
		 }
private: System::Void ModifyPasswordToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
		 {
			 changePassword = gcnew ChangePassword;
			 if(changePassword->ShowDialog() == ::DialogResult::OK)
			 {
			 }
		 }
private: System::Void TodayTableInquiryToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(m_pdataInfo==NULL)
				 return;
			 if(m_pdataInfo->HasPermission(TODAY_OPEN_ORDER_QUERY)) {
				 dlgOrderInfoObject->Owner = this;
				 dlgOrderInfoObject->Show();
			 }
		 }
private: System::Void TodayTradeInquiryToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(m_pdataInfo==NULL)
				 return;
			 if(m_pdataInfo->HasPermission(TODAY_TRADE_QUERY)) {
				 dlgTradeInfoObject->Owner = this;
				 dlgTradeInfoObject->Show();
			 }
		 }
private: System::Void TodayHoldInquiryToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(m_pdataInfo==NULL)
				 return;
			 if(m_pdataInfo->HasPermission(TODAY_POSITION_QUERY)) {
				 dlgPositionInfoObject->Owner = this;
				 dlgPositionInfoObject->Show();
			 }
		 }
private: System::Void TodayMoneyInquiryToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(m_pdataInfo==NULL)
				 return;
			 if(m_pdataInfo->HasPermission(TODAY_ACCOUNT_QUERY)) {
				 dlgFundInfoObject->Owner = this;
				 dlgFundInfoObject->Show();
			 }
		 }
private: System::Void InvestorInfoInquiryToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if(m_pdataInfo==NULL)
				 return;
			 if(m_pdataInfo->HasPermission(INVESTOR_INFO_QUERY)) 
			 {
				 if(QueryInvestorInfoModule != nullptr)
				 {
					 delete QueryInvestorInfoModule;
					 QueryInvestorInfoModule = nullptr;
				 }

				 {
					 //加载投资者信息查询模块
					 QueryInvestorInfoModule = (gcnew QueryInvestorInfo());
					 QueryInvestorInfoModule->Show();
				 }
			 }
		 }
private: System::Void MapViewToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 RiskMapForm^ lRiskMapDialog = gcnew RiskMapForm();
			 if(lRiskMapDialog->ShowDialog() == ::DialogResult::OK)
			 {
			 }
		 }
private: System::Void ReportView_Hold_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 ReportForm^ lReportDialog = gcnew ReportForm();
			 lReportDialog->Text = "持仓统计";
			 lReportDialog->DataProvider =  CAccountHodeReportDataProviderFactory::Instance()->CreateDataProvider();
			 if(lReportDialog->ShowDialog() == ::DialogResult::OK)
			 {
			 }

		 }
private: System::Void ReportView_Interest_MenuClick(System::Object^  sender, System::EventArgs^  e) {
			 ReportForm^ lReportDialog = gcnew ReportForm();
			 lReportDialog->Text = "帐户权益绩效统计";
			 lReportDialog->DataProvider = CAccountInterestsDataProviderFactory::Instance()->CreateDataProvider();
			 lReportDialog->SetInstrumentShow(false);
			 if(lReportDialog->ShowDialog() == ::DialogResult::OK)
			 {
			 }
		 }
private: System::Void ReportView_Trades_MenuClick(System::Object^  sender, System::EventArgs^  e) {
			 ReportForm^ lReportDialog = gcnew ReportForm();
			 lReportDialog->Text = "帐户交易绩效统计";
			 lReportDialog->DataProvider =  CAccountTradesReportDataProviderFactory::Instance()->CreateDataProvider();
			 if(lReportDialog->ShowDialog() == ::DialogResult::OK)
			 {
			 }
		 }
private: System::Void UserEventInquiryToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if(m_pdataInfo==NULL)
				 return;
			 if(m_pdataInfo->HasPermission(RISK_EVENT_QUERY)) 
			 {
				 if(QueryRiskEvtModule != nullptr)
				{
					 delete QueryRiskEvtModule;
					 QueryRiskEvtModule = nullptr;
				 }
				 {
					 //加载用户风险事件查询模块
					 QueryRiskEvtModule = (gcnew QueryRiskEvt());
					 QueryRiskEvtModule->Show();
				 }
			 }
		 }
private: System::Void FundNetValueInquiryToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if(m_pdataInfo==NULL)
				 return;
			 if(QueryFundNetValue != nullptr)
			 {
				 delete QueryFundNetValue;
				 QueryFundNetValue = nullptr;
			 }
			 {
					 //加载用户风险事件查询模块
				 QueryFundNetValue = (gcnew QueryFundNetValueModule());
				 QueryFundNetValue->Show();
			 }			 
		 }

private: System::Void QuitToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->Close();
		 }
	private: System::Void Login_Event(Object^ sender, RiskEventEventArgs^ e)
			 {
				String^ str = e->str;

				this->Text = L"中期风控终端  -  " + str;
			
			 }
public: void Vibration() //震动
		{
			this->TopMost = true; //窗体前端显示
			bool lab = true;
			for (int i = 0; i < 200; i++) //循环里的都能懂吧！
			{
				if (lab)
				{
					this->Top += 8;
					this->Left += 8;
					lab = false;
				}
				else
				{
					this->Top -= 8;
					this->Left -= 8;
					lab = true;
				}
			}
			this->TopMost = false; //取消最前
		}
	 private: System::Void Vibrate(Object^ sender, RiskEventEventArgs^ e)
			  {
				  Vibration();
			  }
 private: System::Void FastForce(Object^ sender, RiskEventEventArgs^ e)
		  {
			  FastForceClick();
		  } 
private: System::Void ManualForce(Object^ sender, RiskEventEventArgs^ e)
		  {
			   ManualForceClick();    
		  }
private: System::Void 组屏展示ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 RiskCombinationScreenSelect ^ lDlg = gcnew RiskCombinationScreenSelect();

			 System::Drawing::Size lSize =
				 System::Drawing::Size(System::Windows::Forms::Screen::PrimaryScreen->WorkingArea.Width/2,
				 System::Windows::Forms::Screen::PrimaryScreen->WorkingArea.Height/2);
			 if(lDlg->ShowDialog() == ::DialogResult::OK)
			 {
				 for(int i = 0 ; i < 4 ; i ++)
				 {
					 ScreenConfig ^ lConfig = lDlg->GetScreenConfigAt(i);
					 if(lConfig)
					 {
						 if(lConfig->mnType == 1)
						 {
							 //组织机构
							 DepartmentShow ^ ltempShowForm = gcnew DepartmentShow();
							 ltempShowForm->CurrentOrgID = lConfig->mnOrgID;
							 ltempShowForm->CombinationScreenSetting( Point( (i%2)*lSize.Width ,(i/2)*lSize.Height ),lSize);
							 ltempShowForm->Show();
					

						 }
						 if(lConfig->mnType == 2)
						 {
							 //理财产品
							 ProductShow ^ lp = gcnew ProductShow();
							 lp->CurrentOrgID = lConfig->mnOrgID;
							 lp->CurrentProductID =lConfig->mnProID;
							 lp->CurrentProductName = lConfig->msProName;
							 lp->CombinationScreenSetting( Point( (i%2)*lSize.Width ,(i/2)*lSize.Height ),lSize);
							 lp->Show();
						
						 }
					 }
				 }
				
			 }
		 }
private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) 
		 {
				 if(m_bAutoStart)
				 {
					 // this->Visible = false;
					 ShowStatistics();
					 m_bAutoStart = false;
				 }		
				if(CTcpLayer::IsDisconnected() == true)
				{
					if(login->Visible)
						return;

					this->timer1->Stop();
					String^ strtemp = "与服务端断开，请退出后重新登录！";
					MessageBox::Show(strtemp, "提示",MessageBoxButtons::OK);

					this->timer1->Interval += 10000;//提示断开后，延迟10分钟再提示
					this->timer1->Start();
				}
				else
				{
					

				}
		 }
private:System::Void LoadAutoConfig(cliext::vector<AutoScreenConfig^>^&  nScreensConfig)
		{
			/*
			<Screens>
			<Screen Type="1" OrgId="2" OrgName="北京" PrdID="" ProName="">      
			</Screen>
			<Screen Type="2" OrgId="2" OrgName="北京" ProID="33" ProName="理财1">      
			</Screen>
			<Screen Type="2" OrgId="2" OrgName="北京" ProID="33" ProName="理财1">      
			</Screen>
			<Screen Type="3" OrgId="" OrgName="" ProID="" ProName="">    //地图   
			</Screen>
			</Screens>
			*/
			//添加4个默认的
			System::Xml::XmlDocument ^ mXmlDoc = gcnew System::Xml::XmlDocument();
			nScreensConfig->clear();			
			
			try
			{
				mXmlDoc->Load("AutoScreens.xml");
			}
			catch(Exception ^ e)
			{
				return;
			}
			

			int i = 0;
			XmlNodeList^ lScreenNodeList = mXmlDoc->SelectNodes("/Screens/Screen");
			if(lScreenNodeList != nullptr)
			{
				 for each (XmlNode^ lScreenNode in lScreenNodeList)
				 {
					
                      AutoScreenConfig ^ lConfig = gcnew AutoScreenConfig();
					
					  lConfig->mnType =  Convert::ToInt32(lScreenNode->Attributes["Type"]->Value);
					  lConfig->mnOrgID =  Convert::ToInt32(lScreenNode->Attributes["OrgId"]->Value);
					  lConfig->msOrgName =  lScreenNode->Attributes["OrgName"]->Value;
					  lConfig->mnProID =  Convert::ToInt32(lScreenNode->Attributes["ProId"]->Value);
					  lConfig->msProName =  lScreenNode->Attributes["ProName"]->Value;	

					  nScreensConfig->push_back(lConfig);
				 }
			}

		}

};
}

