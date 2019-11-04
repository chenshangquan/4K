// chartoPY.cpp: implementation of the CCharToPY class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "chartoPY.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CString CCharToPY::m_ArrQWSecond[32];
CCharToPY g_PYChar;

CCharToPY::CCharToPY()
{
    m_ArrQWSecond[0]="CJWGNSPGCGNESYPBTYYZDXYKYGTDJNNJQMBSGZSCYJSYYQPGKBZGYCYWJKGKLJSWKPJQHYTWDDZLSGMRYPYWWCCKZNKYDG";
    
    m_ArrQWSecond[1]="TTNGJEYKKZYTCJNMCYLQLYPYQFQRPZSLWBTGKJFYXJWZLTBNCXJJJJZXDTTSQZYCDXXHGCKBPHFFSSWYBGMXLPBYLLLHLX";
    
    m_ArrQWSecond[2]="SPZMYJHSOJNGHDZQYKLGJHSGQZHXQGKEZZWYSCSCJXYEYXADZPMDSSMZJZQJYZCDJZWQJBDZBXGZNZCPWHKXHQKMWFBPBY";
    
    m_ArrQWSecond[3]="DTJZZKQHYLYGXFPTYJYYZPSZLFCHMQSHGMXXSXJJSDCSBBQBEFSJYHWWGZKPYLQBGLDLCCTNMAYDDKSSNGYCSGXLYZAYBN";
    
    m_ArrQWSecond[4]="PTSDKDYLHGYMYLCXPYCJNDQJWXQXFYYFJLEJBZRXCCQWQQSBNKYMGPLBMJRQCFLNYMYQMSQTRBCJTHZTQFRXQHXMJJCJLX";
    
    m_ArrQWSecond[5]="QGJMSHZKBSWYEMYLTXFSYDSGLYCJQXSJNQBSCTYHBFTDCYZDJWYGHQFRXWCKQKXEBPTLPXJZSRMEBWHJLBJSLYYSMDXLCL";
    
    m_ArrQWSecond[6]="QKXLHXJRZJMFQHXHWYWSBHTRXXGLHQHFNMNYKLDYXZPWLGGTMTCFPAJJZYLJTYANJGBJPLQGDZYQYAXBKYSECJSZNSLYZH";
    
    m_ArrQWSecond[7]="ZXLZCGHPXZHZNYTDSBCJKDLZAYFMYDLEBBGQYZKXGLDNDNYSKJSHDLYXBCGHXYPKDJMMZNGMMCLGWZSZXZJFZNMLZZTHCS";
    
    m_ArrQWSecond[8]="YDBDLLSCDDNLKJYKJSYCJLKOHQASDKNHCSGANHDAASHTCPLCPQYBSDMPJLPCJOQLCDHJJYSPRCHNWJNLHLYYQYYWZPTCZG";
    
    m_ArrQWSecond[9]="WWMZFFJQQQQYXACLBHKDJXDGMMYDJXZLLSYGXGKJRYWZWYCLZMSSJZLDBYDCFCXYHLXCHYZJQSFQAGMNYXPFRKSSBJLYXY";
    
    m_ArrQWSecond[10]="SYGLNSCMHCWWMNZJJLXXHCHSYDSTTXRYCYXBYHCSMXJSZNPWGPXXTAYBGAJCXLYSDCCWZOCWKCCSBNHCPDYZNFCYYTYCKX";
    
    m_ArrQWSecond[11]="KYBSQKKYTQQXFCWCHCYKELZQBSQYJQCCLMTHSYWHMKTLKJLYCXWHEQQHTQHZPQSQSCFYMMDMGBWHWLGSSLYSDLMLXPTHMJ";
    
    m_ArrQWSecond[12]="HWLJZYHZJXHTXJLHXRSWLWZJCBXMHZQXSDZPMGFCSGLSXYMJSHXPJXWMYQKSMYPLRTHBXFTPMHYXLCHLHLZYLXGSSSSTCL";
    
    m_ArrQWSecond[13]="SLDCLRPBHZHXYYFHBBGDMYCNQQWLQHJJZYWJZYEJJDHPBLQXTQKWHLCHQXAGTLXLJXMSLXHTZKZJECXJCJNMFBYCSFYWYB";
    
    m_ArrQWSecond[14]="JZGNYSDZSQYRSLJPCLPWXSDWEJBJCBCNAYTWGMPAPCLYQPCLZXSBNMSGGFNZJJBZSFZYNDXHPLQKZCZWALSBCCJXJYZGWK";
    
    m_ArrQWSecond[15]="YPSGXFZFCDKHJGXDLQFSGDSLQWZKXTMHSBGZMJZRGLYJBPMLMSXLZJQQHZYJCZYDJWBMJKLDDPMJEGXYHYLXHLQYQHKYCW";
    
    m_ArrQWSecond[16]="CJMYYXNATJHYCCXZPCQLBZWWYTWBQCMLPMYRJCCCXFPZNZZLJPLXXYZTZLGDLDCKLYRZZGQTGJHHHJLJAXFGFJZSLCFDQZ";
    
    m_ArrQWSecond[17]="LCLGJDJCSNCLLJPJQDCCLCJXMYZFTSXGCGSBRZXJQQCTZHGYQTJQQLZXJYLYLBCYAMCSTYLPDJBYREGKLZYZHLYSZQLZNW";
    
    m_ArrQWSecond[18]="CZCLLWJQJJJKDGJZOLBBZPPGLGHTGZXYGHZMYCNQSYCYHBHGXKAMTXYXNBSKYZZGJZLQJDFCJXDYGJQJJPMGWGJJJPKQSB";
    
    m_ArrQWSecond[19]="GBMMCJSSCLPQPDXCDYYKYFCJDDYYGYWRHJRTGZNYQLDKLJSZZGZQZJGDYKSHPZMTLCPWNJAFYZDJCNMWESCYGLBTZCGMSS";
    
    m_ArrQWSecond[20]="LLYXQSXSBSJSBBSGGHFJLWPMZJNLYYWDQSHZXTYYWHMCYHYWDBXBTLMSYYYFSXJCSDXXLHJHFSSXZQHFZMZCZTQCXZXRTT";
    
    m_ArrQWSecond[21]="DJHNNYZQQMNQDMMGYYDXMJGDHCDYZBFFALLZTDLTFXMXQZDNGWQDBDCZJDXBZGSQQDDJCMBKZFFXMKDMDSYYSZCMLJDSYN";
    
    m_ArrQWSecond[22]="SPRSKMKMPCKLGDBQTFZSWTFGGLYPLLJZHGJJGYPZLTCSMCNBTJBQFKTHBYZGKPBBYMTTSSXTBNPDKLEYCJNYCDYKZDDHQH";
    
    m_ArrQWSecond[23]="SDZSCTARLLTKZLGECLLKJLQJAQNBDKKGHPJTZQKSECSHALQFMMGJNLYJBBTMLYZXDCJPLDLPCQDHZYCBZSCZBZMSLJFLKR";
    
    m_ArrQWSecond[24]="ZJSNFRGJHXPDHYJYBZGDLQCSEZGXLBLGYXTWMABCHECMWYJYZLLJJYHLGBDJLSLYGKDZPZXJYYZLWCXSZFGWYYDLYHCLJS";
    
    m_ArrQWSecond[25]="CMBJHBLYZLYCBLYDPDQYSXQZBYTDKYXJYYCNRJMPDJGKLCLJBCTBJDDBBLBLCZQRPPXJCGLZCSHLTOLJNMDDDLNGKAQHQH";
    
    m_ArrQWSecond[26]="JGYKHEZNMSHRPHQQJCHGMFPRXHJGDYCHGHLYRZQLCYQJNZSQTKQJYMSZSWLCFQQQXYFGGYPTQWLMCRNFKKFSYYLQBMQAMM";
    
    m_ArrQWSecond[27]="MYXCTPSHCPTXXZZSMPHPSHMCLMLDQFYQXSZYJDJJZZHQPDSZGLSTJBCKBXYQZJSGPSXQZQZRQTBDKYXZKHHGFLBCSMDLDG";
    
    m_ArrQWSecond[28]="DZDBLZYYCXNNCSYBZBFGLZZXSWMSCCMQNJQSBDQSJTXXMBLTXZCLZSHZCXRQJGJYLXZFJPHYMZQQYDFQJJLZZNZJCDGZYG";
    
    m_ArrQWSecond[29]="CTXMZYSCTLKPHTXHTLBJXJLXSCDQXCBBTJFQZFSLTJBTKQBXXJJLJCHCZDBZJDCZJDCPRNPQCJPFCZLCLZXZDMXMPHJSGZ";
    
    m_ArrQWSecond[30]="GSZZQJYLWTJPFSYASMCJBTZKYCWMYTCSJJLJCQLWZMALBXYFBPNLSFHTGJWEJJXXGLLJSTGSHJQLZFKCGNNDSZFDEQFHBS";
    
    m_ArrQWSecond[31]="AQTGLLBXMMYGSZLDYDQMJJRGBJTKGDHGKBLQKBDMBYLXWCXYTTYBKMRTJZXQJBHLMHMJJZMQASLDCYXYQDLQCAFYWYXQHZ";
}

CCharToPY::~CCharToPY()
{

}


void CCharToPY::GetFirstLetter(CString strName, CString& strFirstLetter)
{
    TBYTE ucHigh, ucLow;
    //int  nCode;
    CString strRet;
    
    strFirstLetter.Empty();
    int nStrLength = strName.GetLength();
    
    for ( int i = 0; i < nStrLength; i++ )
    {
        if ( (TBYTE)strName[i] < 0x80 )
        {
            strRet = strName[i];
            strRet.MakeUpper();
            strFirstLetter += strRet;
            continue;
        }
        
        if ( i+1 >= nStrLength )
        {
            break;
        }
        
        ucHigh = (TBYTE)strName[i];		
        ucLow  = (TBYTE)strName[i+1];
        if ( ucHigh < 0xa1 || ucLow < 0xa1)
        {
            continue;
        }
        else
        {
            strRet = GetPYChar( strName[i], strName[i+1] ); 
            //nCode = (ucHigh - 0xa0) * 100 + ucLow - 0xa0;
        }
        
        /*if ( nCode < 5590 )
        {
            strRet = FirstLetter( nCode );
        }
        else
        {
            strRet = GetPYChar( strName[i], strName[i+1] ); 
        }*/
        
        strFirstLetter += strRet;
        i++;
    }
}

//功能：检测Value  是否在Lp..Hp之间   
BOOL CCharToPY::In(int Lp, int Hp,int Value)   
{   
    ASSERT(Lp<=Hp);   
    return  ((Value<=Hp)&&(Value>=Lp));   
}  

//参数：一个汉字   
//返回值：该汉字的拼音   
char CCharToPY::GetPYChar(CString HZ)   
{   
    ASSERT(HZ.GetLength()==2); 
    return GetPYChar(HZ.GetAt(0),HZ.GetAt(1));
}   

//参数：一个汉字   
//返回值：该汉字的拼音   
char CCharToPY::GetPYChar(TCHAR c1,TCHAR c2)   
{   
    WORD  Hi=WORD(c1)<<8;   
    WORD  Lo=BYTE(c2);   
    int  n= Hi + Lo;
    if ( n<=0xD7F9 )
    {
        if   (In(0xB0A1,0xB0C4,n))   return   'A';   
        if   (In(0XB0C5,0XB2C0,n))   return   'B';   
        if   (In(0xB2C1,0xB4ED,n))   return   'C';   
        if   (In(0xB4EE,0xB6E9,n))   return   'D';   
        if   (In(0xB6EA,0xB7A1,n))   return   'E';   
        if   (In(0xB7A2,0xB8C0,n))   return   'F';   
        if   (In(0xB8C1,0xB9FD,n))   return   'G';   
        if   (In(0xB9FE,0xBBF6,n))   return   'H';   
        if   (In(0xBBF7,0xBFA5,n))   return   'J';   
        if   (In(0xBFA6,0xC0AB,n))   return   'K';   
        if   (In(0xC0AC,0xC2E7,n))   return   'L';   
        if   (In(0xC2E8,0xC4C2,n))   return   'M';   
        if   (In(0xC4C3,0xC5B5,n))   return   'N';   
        if   (In(0xC5B6,0xC5BD,n))   return   'O';   
        if   (In(0xC5BE,0xC6D9,n))   return   'P';   
        if   (In(0xC6D1,0xC8BA,n))   return   'Q';   
        if   (In(0xC8BB,0xC8F5,n))   return   'R';   
        if   (In(0xC8F6,0xCBF9,n))   return   'S';   
        if   (In(0xCBFA,0xCDD9,n))   return   'T';   
        if   (In(0xCDDA,0xCEF3,n))   return   'W';   
        if   (In(0xCEF4,0xD1B8,n))   return   'X';   
        if   (In(0xD1B9,0xD4D0,n))   return   'Y';   
        if   (In(0xD4D1,0xD7F9,n))   return   'Z';  
        return   char(0);
    }
    else
    {
        char b1 = (c1&0x7F)-0x20 - 56;
        char b2 = (c2&0x7F)-0x20 - 1;
        if (b1>=0 && b1<=31 && b2>=0 && b2<=93)
        {
            return m_ArrQWSecond[b1].GetAt(b2);
        }
        return   char(0);
    }
}   
