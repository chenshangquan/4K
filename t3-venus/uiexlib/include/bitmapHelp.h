#ifndef BITMAPHELP_HEAD_H
#define BITMAPHELP_HEAD_H
#include "ibaseItem.h"
class CBitmapHelp  
{
	typedef IItem< IBaseItem, int > IItemList;
public:
	CBitmapHelp();
	virtual ~CBitmapHelp();
	
	static Bitmap* CreateBitmap( IItemList* pItemList );
	static Bitmap* CreateBitmap( IBaseItem* pBaseItem );
	static Bitmap* CreateBitmap( Image* pImg, CString strText, Font* pFont, StringFormat& strFormat, Color& col );
	
	static BOOL GetBitmap( Bitmap* pBitmap, IItemList* pItemList );
	
protected:
	static void DrawItem( IItemList* pItemList, IArgs* pArgs );
	
private:
	static Bitmap* m_pBitmap;
};

#endif