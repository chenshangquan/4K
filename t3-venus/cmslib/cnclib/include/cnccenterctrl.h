#include "cnsSession.h"


class CCncCenterCtrl : public CCncCenterCtrlIF
{
public:
	CCncCenterCtrl(CCnsSession &cSession);
	virtual ~CCncCenterCtrl();

    /** 
	* 功能  设置系统电源
	* @param [in]  emPower  开关
	* @return 
	* @remarks 
	*/
    virtual u16 SetSysPower( EmSchPower emPower );
    /** 
	* 功能  设置灯光全开
	* @param [in]  emLight  开关
	* @return 
	* @remarks 
	*/
    virtual u16 SetSysAllLight( EmSchLight emLight );
    /** 
	* 功能  设置主灯开关
	* @param [in]  emMidLight  开关
	* @return 
	* @remarks 
	*/
    virtual u16 SetMainLight( EmSchMidLight emMidLight );
    /** 
	* 功能  设置辅灯开关
	* @param [in]  emScrLight  开关
	* @return 
	* @remarks 
	*/
    virtual u16 SetAuxiLight( EmSchScrLight emScrLight );
    /** 
	* 功能  选择电视机
	* @param [in]  byIndex  序号
	* @return 
	* @remarks 
	*/
	virtual u16 SelectTV( u8 byIndex );
    /** 
	* 功能  设置电视机电源
	* @param [in]  byIndex  序号
	* @return 
	* @remarks 
	*/
    virtual u16 SetTVPowerMode( u8 byIndex, EmTvPowerMode emMode );
    /** 
	* 功能  设置电视机视听模式
	* @param [in]  emMode  视听模式
	* @return 
	* @remarks 
	*/
    virtual u16 SetTVAudVisMode( EmTVAudVisMode emMode );
    /** 
	* 功能  设置电视机显示模式
	* @param [in]  emMode  显示模式
	* @return 
	* @remarks 
	*/
    virtual u16 SetTVDisMode( EmTVDisplayMode emMode );
    /** 
	* 功能  设置电视机输入选择
	* @param [in]  emSelect  输入选择
	* @return 
	*/
    virtual u16 SetTVInpSelect( u8 byIndex, EmTVInputSelect emSelect );
    /** 
	* 功能  获取电视机配置
	* @return TCentreTVCfg*  电视机配置数组指针
	*/
    virtual TCentreTVCfg* GetCentreTVCfg(); 

    /** 
	* 功能  设置文档摄像机开关
    * @param [in]  emPower  开关
	* @return 
	*/
    virtual u16 SetDCamPower( EmDCamPower emPower );
    /** 
	* 功能  设置文档摄像机自动聚焦模式
	* @param [in]  emMode  模式
	* @return 
	*/
    virtual u16 SetDCamAFMode( EmDCamAFMode emMode );
    /** 
	* 功能  设置文档摄像机白平衡模式
	* @param [in]  emMode  模式
	* @return 
	*/
    virtual u16 SetDCamWBMode( EmDCamWBMode emMode );
    /** 
	* 功能  设置文档摄像机视野调节
	* @param [in]  emZoom  视野
	* @return 
	*/
    virtual u16 SetDCamZoom( EmDCamZoom emZoom, EmCnAction emAction );
    /** 
	* 功能  保存文档摄像机预置位
	* @param [in]  emNum  预置位
	* @return 
	*/
    virtual u16 SetDCamPreset( EmDCamPresetNum emNum );
    /** 
	* 功能  调度文档摄像机预置位
	* @param [in]  emNum  预置位
	* @return 
	*/
    virtual u16 SetDCamRecall( EmDCamRecallNum emNum );

    /** 
	* 功能  调度空调温度
	* @param [in]  wTemp  温度
	* @return 
	*/
    virtual u16 SetACTemp( u8 byTemp );
    /** 
	* 功能  调度空调温度
	* @param [in]  wTemp  温度
	* @return 
	*/
    u16 SetACMode( EmCentreACMode emMode );
    /** 
	* 功能  调度新风风量
	* @param [in]  byVol  风量
	* @return 
	*/
    virtual u16 SetACAirVol( EmCentreACAirVol emAirVol );
	/** 
	* 功能  调度空调界面电源开关
	* @param [in] empower 电源开关
	* @return 
	*/
 /*   virtual u16 SetAirPower( EmCentreACPower emPower );*/
    /** 
	* 功能  选择空调
	* @param [in]  byIndex  序号
	* @return 
	* @remarks 
	*/
	virtual u16 SelectAir( u8 byIndex );
	/** 
	* 功能  获取空调界面配置
	* @return TCentreACCfg*  空调界面数组指针
	*/
    virtual void GetCentreACCfg( vector<TCentreACCfg> &vecTCentreACCfg )const; 
    /** 
	* 功能  设置空调电源
	* @param [in]  byIndex  序号
	* @return 
	* @remarks 
	*/
    virtual u16 SetACPowerMode( u8 byIndex, EmCentreACPower emMode );
    /** 
	* 功能  设置应用到所有
	* @param [in]  byIndex  序号
	* @return 
	* @remarks 
	*/
	virtual u16 SetApplyToAll( u8 byIndex, BOOL** atbIsCtrl );
	virtual BOOL* GetApplyToAllInfo();

	virtual u16 SetCentreTVModle( EmTVModle emTvMode);
	virtual u16 SetDisplayShowCmd( BOOL bDisplayShow);
	virtual u16 SetCurtainState( BOOL** bIsCtrl, EmCurAction emCurAction );

	void GetCentreCurName( vector<TCentreCurName> &vecTCentreCurName )const;
	
	virtual u16 SetDisplayCmd( BOOL bDisplay, const TTPDisplayType& tDisplayType1, const TTPDisplayType& tDisplayType3 );
	virtual const BOOL& GetDisplayState() const;
	virtual const TTPDisplayType& GetDisplayType1() const;
	virtual const TTPDisplayType& GetDisplayType3() const;

	virtual const BOOL& GetDisplayShowState() const;

	virtual const TCentreCurInfo& GetCurtainInfo( ) const;

	virtual	u16 SetPanCamNumber( const u8 &byPanCamNum ) const;
	virtual	u16 SetDCamZoomValueCmd( const u16& wZoom );
	virtual	u16 SetDCCamFocus( EmFocus emFocusMode ,EmCnAction emAction ) const;
	virtual	u16 SetDCCamExposure( EmExpMode emExpMode ) const;
	virtual	u16 SetDCCamExpGainCmd( EmDCamGain emExpGain ) const;
	virtual	u16 SetDCCamAperture( EmDCamIris emAperture ) const;
	virtual	u16 SetDCCamShutCmd( EmDCamShutSpd emShutSpd ) const;
	virtual	u16 SetDcCamRGainCmd( const u16& wRGain ) const;
	virtual	u16 SetDcCamBGainCmd( const u16& wRGain ) const;
	virtual u16 SetCurtainNumberCmd( const u8& byCurNum ) const;
	virtual u16 SetCurtainName( const u8& byCurIndex, const TCentreCurName &tCurtainName) const;
	virtual	u16 SetCurtainOpen( const BOOL& bOpen ) const;
	virtual	u16 SetDuoVideoCmd( const BOOL& bOpen ) const;
	virtual u16 SetDCCamOpenCmd( const BOOL& bOpen ) const;
	virtual	u16 SetDCCamPreset( const BOOL& bPreset ) const;
	virtual u16 SetAirConditionCmd( const u8& byAcNum ) const;
	virtual u16 SetDcCamModel( EmDCamProType emDcCamType ) const;
	virtual u16 SetPaCamModel( EmQCamProType emPaCamType ) const;
protected:
    virtual void OnTimeOut(u16 wEvent); 
    virtual void DispEvent(const CMessage &cMsg);
	void BuildEventsMap();
	//断链消息处理
	void OnLinkBreak(const CMessage& cMsg);


    //控制面板
    void OnSchStateNty(const CMessage& cMsg);
    void OnSchTempNty(const CMessage& cMsg);
    void OnSchPowerInd(const CMessage& cMsg);
    void OnSchPowerNty(const CMessage& cMsg);
    void OnSchLightInd(const CMessage& cMsg);
    void OnSchMainLightInd(const CMessage& cMsg);
    void OnSchAuxiLightInd(const CMessage& cMsg);
    void OnSchLightNty(const CMessage& cMsg);
    //显示器
    void OnTvStateNty(const CMessage& cMsg);
    void OnSeleteTvInd(const CMessage& cMsg);
    void OnTvPowerModeInd(const CMessage& cMsg);
    void OnTvAudVisModeInd(const CMessage& cMsg);
    void OnTvDisModeInd(const CMessage& cMsg);
    void OnTvAudInpSelectInd(const CMessage& cMsg);
	void OnCentreTVModleInd(const CMessage& cMsg);
    //文档摄像机
    void OnDCamPowerInd(const CMessage& cMsg);
    void OnDCamAFModeInd(const CMessage& cMsg);
    void OnDCamWBModeInd(const CMessage& cMsg);
    void OnDCamZoomInd(const CMessage& cMsg);
    void OnDCamPresetInd(const CMessage& cMsg);
    void OnDCamRecallInd(const CMessage& cMsg);
    void OnDCamStateNty(const CMessage& cMsg);
    //空调
    void OnACTempInd(const CMessage& cMsg);
    void OnACModeInd(const CMessage& cMsg);
    void OnACAirVolInd(const CMessage& cMsg);
    void OnACStateNty(const CMessage& cMsg);
	void OnAirPowerInd(const CMessage& cMsg);
	void OnSeleteAirInd(const CMessage& cMsg);
	void OnApplyToAllInd(const CMessage& cMsg);
	//窗帘
	void OnCurtainStateNty(const CMessage& cMsg);
	void OnCurtainActInd(const CMessage& cMsg);
	//摄像机
	void OnCamStateNty(const CMessage& cMsg);
    //中控待机
    void OnCentreSleepNty(const CMessage& cMsg);
	//中控电视墙
	void OnDisplayInd(const CMessage& cMsg);
	void OnCfgDisplayShowNty(const CMessage& cMsg);
	void OnCfgDisplayShowInd(const CMessage& cMsg);
	//全景摄像机
	void OnPanCamNty(const CMessage& cMsg);


	void OnDCamExpModeInd( const CMessage& cMsg );
	void OnDCamExpGainNty( const CMessage& cMsg );

	void OnDCamShutSpdNty( const CMessage& cMsg );
	void OnDCamApertureNty( const CMessage& cMsg );
	void OnDCamRGainInd( const CMessage& cMsg );
	void OnDCamBGainInd( const CMessage& cMsg );
	void OnPanCamNumberInd(const CMessage& cMsg);
	void OnDCamZoomValueInd(const CMessage& cMsg);
	void OnCurtainNumberInd( const CMessage& cMsg );
	void OnCurtainNameInd( const CMessage& cMsg );
	void OnCurtainInd( const CMessage& cMsg );
	void OnDualScreenInd( const CMessage& cMsg );
	void OnDualScreenNty( const CMessage& cMsg );
	void OnDCCamCfgInd( const CMessage& cMsg );
	void OnDCCamPresetInd( const CMessage& cMsg );
	void OnAirConditionInd( const CMessage& cMsg );
	void OnDcCamModelInd( const CMessage& cMsg );
	void OnPaCamModelInd( const CMessage& cMsg );
private:
	CCnsSession				*m_pSession;
    TCentreTVCfg            m_atTVCfg[MAX_CENTRETV_NUM];   //显示器信息 
	#define MAX_AC_NUM      3                         //冗余
	vector<TCentreACCfg>	m_vecTCentreACCfg;		//空调显示器信息
	vector<TCentreCurName>  m_vecTCentreCurName;    //窗帘名称向量

	TCentreCurInfo			m_tCentreCurtain;
	BOOL m_atbIsCtrl[3];
	BOOL m_bIsCtrl[3];
	BOOL m_bDisplay;
	BOOL m_bDisplayShow;
	TTPDisplayType m_tDisplayType1;
	TTPDisplayType m_tDisplayType3;
};