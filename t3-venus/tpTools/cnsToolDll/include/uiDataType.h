
#ifndef UIDATATYPE_H
#define UIDATATYPE_H

#define ARRAY   vector

#define FUNNAME_MAXLEN 64	//函数名最大长度
#define ITEMNAME_MAXLEN 32	//条目名称最大长度
#define PATH_MAX		512

//菜单条目
typedef struct tagMenuItem
{   
	char szName[ITEMNAME_MAXLEN];		     //条目名称
	char szClickFunName[FUNNAME_MAXLEN];	 //click处理函数名
 	char szItemType[ITEMNAME_MAXLEN];        //条目类型，具体内容在itemInfo.xml 配置
 	char szImgFolder[PATH_MAX];			  	 //条目图片路径
 
	void SetItemName( LPCSTR lpstring  )
	{ 
		_snprintf( szName, sizeof(szName), "%s", lpstring );	
	}

	void SetItemFuncName( LPCSTR lpstring  )
	{ 
		_snprintf( szClickFunName, sizeof(szClickFunName), "%s", lpstring );	
	}

	void SetItemType( LPCSTR lpstring  )
	{ 
		_snprintf( szItemType, sizeof(szItemType), "%s", lpstring );	
	}

	void SetItemImg( LPCSTR lpstring  )
	{ 
		_snprintf( szImgFolder, sizeof(szImgFolder), "%s", lpstring );	
	}


	tagMenuItem()
	{
		ZeroMemory( this, sizeof(tagMenuItem) );
	}

} TMenuItem, *PTMenuItem;

 



#endif