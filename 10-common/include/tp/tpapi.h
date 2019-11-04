#ifndef _TP_API_H
#define _TP_API_H

#include "protocoladapter.h"
#include "tpstruct.h"
#include "lanman.h"


class CTpTypeAdpt
{
public:
	
	static u8 GetVidPayloadValue(EmTpVideoFormat emFormat);
	static u8 GetAudPayloadValue(EmTpAudioFormat emFormat);
	static EmPAPayloadType GetVideoPT( EmTpVideoFormat emAFormat );
	static u16 GetAudioPT( EmTpAudioFormat emAFormat );
	static EmTpAudioFormat GetAudioFormat( u16 wAFormat );
    static EmTpVideoFormat GetVideoFormat( u16 wVFormat );
	static s8* GetVideoResolutionName( u32 emRes );
	static EmTpVideoResolution GetVideoResolution( u32 emRes );
	static EmPAResolution       GetStackResolution( EmTpVideoResolution emRes );
	static u8 GetDynaPayloadType( u16 wPayload );
	static void GetVidResolution( u32 emRes, u32 &dwWidth, u32 &dwHeight );
	// AAC
	static u8  GetMtAACChnlType( u32 emAacChnlType );
	static u32 GetMtAACSampleFreq( u32 emAacFs );

	static u16 GetAudBitrate(EmTpAudioFormat emAFormat);


	static EmDualReason GetDualReason(EmTPDualReason emType);
	static EmTPDualReason GetDualReason(EmDualReason emType);

	static u32 GetLocalIP(u8 byIndex);
	
	static void ConvertEpTypeFromTpToStack(const EmTPEndpointType& emTpType,
											EmPAEndpointType& emPAType);

	static void ConvertProtocolFromTpToStack(const EmTpConfProtocol& emTpMode, 
											EmPAConfProtocol& emPAMode);
	static void ConvertConfNetAddrFromTpToStack(TPAIPAddress& tPA, 
											const TTPTransAddr& tTp);
	static void ConvertConfNetAddrFromStackToTp(TTPTransAddr& tTp, 
										const TPAIPAddress& tPA);
	static void ConvertAliasFromTpToStack(const TTPAlias& tTp, 
										TPAAlias& tPA);
	static void ConvertAliasFromStackToTp(const TPAAlias& tPA, 
										TTPAlias& tTp, EmTpConfProtocol &emTpProtocal);

	static void ConvertRegNameFromTpToStack(const TTPAlias& tTpAddr, 
											TPARegName& tPAStackAddr);

	static void ConvertRegResultParaFromCnsToStack( EmTPRegResult& emTPRegResult, EmRegResult& emRegResult);

	static void ConvertEpTypeFromStackToTp(const EmPAEndpointType& emStack, 
									EmTPEndpointType& emTp);

	static void ConvertProtocolFromStackToTp(const EmPAConfProtocol& emStackMode, 
									EmTpConfProtocol& emTpMode);


	static void ConvertSipLevelFromTpToStack(const EmTPSipLevel& emTp, EmPASipLevel& emPA  );

	static void ConvertSipLevelFromStackToTp(const EmPASipLevel& emPA, EmTPSipLevel& emTp  );

	static void ConvertRegResultParaFromCnsToStack(const EmTPRegResult& emTP, EmRegResult& emPA  );

	static void ConvertRegResultParaFromStackToCns(const EmRegResult& emPA, EmTPRegResult& emTP);

	static void ConvertResFromCnsToStack(const EmTpVideoResolution& emTpVideoResolution, EmPAResolution& emPAResolution);

	static void ConvertCallReasonFromStackToTp( const EmPACnsCallReason &emPAReason, EmCnsCallReason &emCallReason );
	static void ConvertMixStatusFromStackToTp( const EmPATpMixStatus &emPAStatus, EmTpMixStatus &emTpStatus );
	static void ConvertAliasTypeFromStackToTp( EmTpAliasType &emTpType, const EmPAAliasType &emPAType);
	static void ConvertAliasTypeFromTpToStack( const EmTpAliasType &emTpType, EmPAAliasType &emPAType);

	static void ConvertRegInfoTypeFromTpToStack( const EmGetRegInfoType &emTpType, EmPAGetRegInfoType &emPAType);
	static void ConvertRegInfoTypeFromStackToTp( EmGetRegInfoType &emTpType, const EmPAGetRegInfoType &emPAType);
	
	static void ConvertPackInfoFromTpToStack( const TTPSipRegPackInfo &tPackInfo, TPARegPackInfo &tPAPackInfo );
	static void ConvertPackInfoFromStackToTp( TTPSipRegPackInfo &tPackInfo, const TPARegPackInfo &tPAPackInfo );

	static void ConvertPackRegInfoFromStackToTp( TTPSipRegInfo &tRegInfo, const TPARegInfo &tPARegInfo );
	
	static void ConvertConfListInfoFromStackToTp( const TPAConfCnsList &tPAConfList, TConfCnsInfo &tConfList, EmTpConfProtocol &emTpProtocal );
	static void ConvertTPPtToAFormat( const EmTPPayloadType  &emTPActivePT , EmTpAudioFormat &emTPAudioFormat );
	static void ConvertGKInfoFromStackToTp(const TModuleMtOnlineList &tPAMtOnlineList, TTPMtRegInfo &tTPMtRegInfo);
	static void ConvertSipRegInfoFromStackToTp( const TPARegPack &tPaRegPack, TRegPackInfoEx &tTpRegPackInfoEx);
	static void ConvertCnsInfoFromStackToTP(const TPARegInfoCns &tPaRegInfoCns, TCnsRegInfoEx &tCnsRegInfoEx);
	static void ConvertUmsInfoFromStackToTP(const TPARegInfoUms &tPaRegInfoUms, TUmsRegInfoEx &tUmsRegInfoEx);
	static u32 GetWHByVidResolution(const EmTpVideoResolution &emResolution);

	//协议暂时还没有码流加密的内容
// 	static void ConvertStreamKeyFromTpToStack( const EmTPEncryptType &emTPEncryptBits, EmMdlEncryptType &emMdlEncryptType );
 	static void ConvertStreamKeyFromStackToTp( const EmMdlEncryptType &emMdlEncryptType, EmTPEncryptType &emTPEncryptBits );

	static void ConvertGB2312ToUTF8( s8 *pchGB2312Name, s8 *pchUTF8Name, u16 wLen );
	static void ConvertUTF8ToGB2312( s8 *pchUTF8Name, s8 *pchGB2312Name, u16 wLen );



};


BOOL TpMakeDir(const s8* path );

void TPSetSysTime(TTPTime& tTime);
void TPGetSysTime(TTPTime& tTime);

#endif