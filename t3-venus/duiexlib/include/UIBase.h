#ifndef __UIBASE_H__
#define __UIBASE_H__

namespace DuiLib {
/////////////////////////////////////////////////////////////////////////////////////
//

#define UI_WNDSTYLE_CONTAINER  (0)
#define UI_WNDSTYLE_FRAME      (WS_VISIBLE | WS_OVERLAPPEDWINDOW)
#define UI_WNDSTYLE_CHILD      (WS_VISIBLE | WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN)
#define UI_WNDSTYLE_DIALOG     (WS_VISIBLE | WS_POPUPWINDOW | WS_CAPTION | WS_DLGFRAME | WS_CLIPSIBLINGS | WS_CLIPCHILDREN)

#define UI_WNDSTYLE_EX_FRAME   (WS_EX_WINDOWEDGE)
#define UI_WNDSTYLE_EX_DIALOG  (WS_EX_TOOLWINDOW | WS_EX_DLGMODALFRAME)

#define UI_CLASSSTYLE_CONTAINER  (0)
#define UI_CLASSSTYLE_FRAME      (CS_VREDRAW | CS_HREDRAW)
#define UI_CLASSSTYLE_CHILD      (CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS | CS_SAVEBITS)
#define UI_CLASSSTYLE_DIALOG     (CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS | CS_SAVEBITS)


/////////////////////////////////////////////////////////////////////////////////////
//
#ifndef ASSERT
#define ASSERT(expr)  _ASSERTE(expr)
#endif

#ifdef _DEBUG
#ifndef TRACE
#define TRACE __Trace
#endif
#define TRACEMSG __TraceMsg
#else
#ifndef TRACE
#define TRACE
#endif
#define TRACEMSG _T("")
#endif

void UILIB_API __Trace(LPCTSTR pstrFormat, ...);
LPCTSTR UILIB_API __TraceMsg(UINT uMsg);

/////////////////////////////////////////////////////////////////////////////////////
//

class STRINGorID
{
public:
    STRINGorID(LPCTSTR lpString) : m_lpstr(lpString)
    { }
    STRINGorID(UINT nID) : m_lpstr(MAKEINTRESOURCE(nID))
    { }
    LPCTSTR m_lpstr;
};

/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CPoint : public tagPOINT
{
public:
    CPoint();
    CPoint(const POINT& src);
    CPoint(int x, int y);
    CPoint(LPARAM lParam);
};


/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CSize : public tagSIZE
{
public:
    CSize();
    CSize(const SIZE& src);
    CSize(const RECT rc);
    CSize(int cx, int cy);
};


/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CRect : public tagRECT
{
public:
    CRect();
    CRect(const RECT& src);
    CRect(int iLeft, int iTop, int iRight, int iBottom);

    int GetWidth() const;
    int GetHeight() const;
    void Empty();
    bool IsNull() const;
    void Join(const RECT& rc);
    void ResetOffset();
    void Normalize();
    void Offset(int cx, int cy);
    void Inflate(int cx, int cy);
    void Deflate(int cx, int cy);
    void Union(CRect& rc);
};

/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CStdPtrArray
{
public:
	CStdPtrArray(int iPreallocSize = 0);
	CStdPtrArray(const CStdPtrArray& src);
	~CStdPtrArray();

	void Empty();
	void Resize(int iSize);
	bool IsEmpty() const;
	int Find(LPVOID iIndex) const;
	bool Add(LPVOID pData);
	bool SetAt(int iIndex, LPVOID pData);
	bool InsertAt(int iIndex, LPVOID pData);
	bool Remove(int iIndex);
	int GetSize() const;
	LPVOID* GetData();

	LPVOID GetAt(int iIndex) const;
	LPVOID operator[] (int nIndex) const;

protected:
	LPVOID* m_ppVoid;
	int m_nCount;
	int m_nAllocated;
};


/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CStdValArray
{
public:
    CStdValArray(int iElementSize, int iPreallocSize = 0);
    ~CStdValArray();

	void Empty();
	bool IsEmpty() const;
	bool Add(LPCVOID pData);
	bool Remove(int iIndex);
	int GetSize() const;
	LPVOID GetData();

	LPVOID GetAt(int iIndex) const;
	LPVOID operator[] (int nIndex) const;

protected:
	LPBYTE m_pVoid;
	int m_iElementSize;
	int m_nCount;
	int m_nAllocated;
};


/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CStdString
{
public:
    enum { MAX_LOCAL_STRING_LEN = 63 };

    CStdString();
    CStdString(const TCHAR ch);
    CStdString(const CStdString& src);
    CStdString(LPCTSTR lpsz, int nLen = -1);
    ~CStdString();

    void Empty();
    int GetLength() const;
    bool IsEmpty() const;
    TCHAR GetAt(int nIndex) const;
    void Append(LPCTSTR pstr);
    void Assign(LPCTSTR pstr, int nLength = -1);
    LPCTSTR GetData();

    void SetAt(int nIndex, TCHAR ch);
    operator LPCTSTR() const;

    TCHAR operator[] (int nIndex) const;
    const CStdString& operator=(const CStdString& src);
    const CStdString& operator=(const TCHAR ch);
    const CStdString& operator=(LPCTSTR pstr);
#ifndef _UNICODE
    const CStdString& CStdString::operator=(LPCWSTR lpwStr);
#endif
    CStdString operator+(const CStdString& src);
    CStdString operator+(LPCTSTR pstr);
    const CStdString& operator+=(const CStdString& src);
    const CStdString& operator+=(LPCTSTR pstr);
    const CStdString& operator+=(const TCHAR ch);

    bool operator == (LPCTSTR str) const;
    bool operator != (LPCTSTR str) const;
    bool operator <= (LPCTSTR str) const;
    bool operator <  (LPCTSTR str) const;
    bool operator >= (LPCTSTR str) const;
    bool operator >  (LPCTSTR str) const;

    int Compare(LPCTSTR pstr) const;
    int CompareNoCase(LPCTSTR pstr) const;

    void MakeUpper();
    void MakeLower();

    CStdString Left(int nLength) const;
    CStdString Mid(int iPos, int nLength = -1) const;
    CStdString Right(int nLength) const;

    int Find(TCHAR ch, int iPos = 0) const;
    int Find(LPCTSTR pstr, int iPos = 0) const;
    int ReverseFind(TCHAR ch) const;
    int Replace(LPCTSTR pstrFrom, LPCTSTR pstrTo);

    int __cdecl Format(LPCTSTR pstrFormat, ...);
    int __cdecl SmallFormat(LPCTSTR pstrFormat, ...);

protected:
    LPTSTR m_pstr;
    TCHAR m_szBuffer[MAX_LOCAL_STRING_LEN + 1];
};


/////////////////////////////////////////////////////////////////////////////////////
//

struct TITEM
{
    CStdString/*tString*//*LPCTSTR*/ Key;
    LPVOID Data;
    struct TITEM* pNext;

};

class UILIB_API CStdStringPtrMap
{
public:
    CStdStringPtrMap(int nSize = 83);
    ~CStdStringPtrMap();

    void Resize(int nSize = 83);
    LPVOID Find(LPCTSTR key) const;
    bool Insert(LPCTSTR key, LPVOID pData);
    LPVOID Set(LPCTSTR key, LPVOID pData);
    bool Remove(LPCTSTR key);
    int GetSize() const;
    LPCTSTR GetAt(int iIndex) const;
    LPCTSTR operator[] (int nIndex) const;

protected:
    TITEM** m_aT;
    int m_nBuckets;
};


/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CWindowWnd
{
public:
    CWindowWnd();

    HWND GetHWND() const;
    operator HWND() const;

    bool RegisterWindowClass();
    bool RegisterSuperclass();

    HWND Create(HWND hwndParent, LPCTSTR pstrName, DWORD dwStyle, DWORD dwExStyle, const RECT rc, HMENU hMenu = NULL);
    HWND Create(HWND hwndParent, LPCTSTR pstrName, DWORD dwStyle, DWORD dwExStyle, int x = CW_USEDEFAULT, int y = CW_USEDEFAULT, int cx = CW_USEDEFAULT, int cy = CW_USEDEFAULT, HMENU hMenu = NULL);
    HWND Subclass(HWND hWnd);
    void Unsubclass();
    void ShowWindow(bool bShow = true, bool bTakeFocus = true);
    bool ShowModal();
    void Close();
    void CenterWindow();
    void SetIcon(UINT nRes);

    LRESULT SendMessage(UINT uMsg, WPARAM wParam = 0, LPARAM lParam = 0L);
    LRESULT PostMessage(UINT uMsg, WPARAM wParam = 0, LPARAM lParam = 0L);
    void ResizeClient(int cx = -1, int cy = -1);

protected:
    virtual LPCTSTR GetWindowClassName() const = 0;
    virtual LPCTSTR GetSuperClassName() const;
    virtual UINT GetClassStyle() const;

    virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
    virtual void OnFinalMessage(HWND hWnd);

    static LRESULT CALLBACK __WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    static LRESULT CALLBACK __ControlProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

protected:
    HWND m_hWnd;
    WNDPROC m_OldWndProc;
    bool m_bSubclassed;
};


/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CWaitCursor
{
public:
    CWaitCursor();
    ~CWaitCursor();

protected:
    HCURSOR m_hOrigCursor;
};

 
 
 


/*****************************************************************************
* 功能:单例基类	 
* @remarks	该基类的子类无需进行初始化等创建操作，可直接通过GetSingletonPtr()来获取指针 
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2012/11/29     1.0         俞锦锦      创建
******************************************************************************/
template<class T> class ISingleTon 
{
protected:
	static T* ms_pSingleton; 


	ISingleTon( void )
	{  
	}

public:
	~ISingleTon( void )
	{
		RemoveInstance();

	}

	static T* GetSingletonPtr( void )
	{  
		if ( NULL == ms_pSingleton )
		{
			ms_pSingleton = new T ;

		}
		return ms_pSingleton;
	}


	static void RemoveInstance()
	{
		if(ms_pSingleton)
		{
			delete ms_pSingleton;
		}
		ms_pSingleton = NULL;
	}
};

template <class T> T * ISingleTon<T>::ms_pSingleton = NULL;

} // namespace DuiLib


//////////////////////////////////////////////////////////////////////////
//
template <class T>
struct /*UILIB_API*/ TSNode
{
	int m_nKey;
	T   m_val;
	TSNode<T>* m_pNext;

	TSNode()
	{
		m_nKey = -1;
		memset( &m_val, 0, sizeof(m_val) );
		m_pNext = NULL;
	}

	~TSNode()
	{
		Clear();
	}

	inline void Clear()
	{
		m_nKey = -1;
		memset( &m_val, 0, sizeof(m_val) );
		m_pNext = NULL;
	}
};

template <class T>
class /*UILIB_API*/ CStdDataList
{
public:
	CStdDataList();
	CStdDataList( const CStdDataList<T>& src );
	~CStdDataList(){ Clear(); };

public:
	void Clear();
	bool IsEmpty() const;
	int GetSize() const;
	
	bool InsertItem(int nKey, T val);			  //nKey 不允许重复
	bool InsertAt(int nIndex, int nKey, T val);   //nKey 不允许重复
	bool Remove(int nKey);

	bool SetAt(int nKey, T val);
	T GetAt(int nKey);
	
	TSNode<T>* FindByKey(int nKey);
	TSNode<T>* GetFirstNode();
	TSNode<T>* GetLastNode();
	
	TSNode<T>* ReverseList();
	
	CStdDataList<T>& operator = ( const CStdDataList<T>& src );

protected:
	TSNode<T>* m_pHead;
	TSNode<T>* m_pLast;
	int m_nCount;
};

template <class T> 
CStdDataList<T>::CStdDataList() : m_pHead(NULL), m_pLast(NULL), m_nCount(0)
{
}

template <class T> 
CStdDataList<T>::CStdDataList(const CStdDataList<T>& src) : m_pHead(NULL), m_pLast(NULL), m_nCount(0)
{
	if ( NULL != src.m_pHead && NULL != src.m_pLast && 0 != src.GetSize() )
	{
		TSNode<T>* pNode = src.m_pHead;
		for( int i = 0; i < src.GetSize(); i++ )
		{
			InsertItem( pNode->m_nKey, pNode->m_val );
			pNode = pNode->m_pNext;
		} 
	}
}

template <class T> 
void CStdDataList<T>::Clear()
{
	if( NULL != m_pHead && NULL != m_pLast )
	{
		TSNode<T>* pNode = m_pHead;
		TSNode<T>* pTemp = NULL;

		for ( int i = 0; i < m_nCount; i++ )
		{
			pTemp = pNode->m_pNext;
			pNode->Clear();
			free(pNode);
			pNode = pTemp;
		}
	}

	m_pHead = m_pLast = NULL;
	m_nCount = 0;
}

template <class T> 
bool CStdDataList<T>::IsEmpty() const
{
	return m_nCount == 0;
}

template <class T> 
bool CStdDataList<T>::InsertItem(int nKey, T val)
{
	if ( NULL != FindByKey(nKey) )
	{
		return false;
	}

	TSNode<T>* pNode = static_cast<TSNode<T>*>( malloc( sizeof(TSNode<T>) ) );
	if ( NULL == pNode )
	{
		return false;
	}
	pNode->m_nKey = nKey;
	pNode->m_val = val;
	pNode->m_pNext = NULL;
	
	if ( NULL == m_pHead || NULL == m_pLast )
	{
		m_pHead = m_pLast = pNode;
	}
	else
	{
		m_pLast->m_pNext = pNode;
		m_pLast = pNode;
	}

	m_nCount++;
	return true;
}

template <class T> 
bool CStdDataList<T>::InsertAt(int nIndex, int nKey, T val)
{
	if ( NULL != FindByKey(nKey) || nIndex > m_nCount )
	{
		return false;
	}

	if ( nIndex == m_nCount )
	{
		return InsertItem(nKey, val);
	}

	TSNode<T>* pNode = static_cast<TSNode<T>*>( malloc( sizeof(TSNode<T>) ) );
	if ( NULL == pNode )
	{
		return false;
	}
	pNode->m_nKey = nKey;
	pNode->m_val = val;
	pNode->m_pNext = NULL;

	if ( NULL == m_pHead || NULL == m_pLast )
	{
		m_pHead = m_pLast = pNode;
	}
	else
	{
		if ( 0 == nIndex )
		{
			pNode->m_pNext = m_pHead;
			m_pHead = pNode;
		}
		else if ( 1 == nIndex )
		{
			pNode->m_pNext = m_pHead->m_pNext;
			m_pHead->m_pNext = pNode;
		}
		else
		{
			TSNode<T>* pPre = m_pHead;
			for ( int i = 0; i < nIndex - 1; i++ )
			{
				pPre = pPre->m_pNext;
			}
			pNode->m_pNext = pPre->m_pNext;
			pPre->m_pNext = pNode;
		}
	}

	m_nCount++;
	return true;
}

template <class T> 
bool CStdDataList<T>::SetAt(int nKey, T val)
{
	TSNode<T>* pNode = FindByKey(nKey);
	if ( NULL != pNode )
	{
		pNode->m_val = val;
		return true;
	}

	return false;
}

template <class T> 
bool CStdDataList<T>::Remove(int nKey)
{
	TSNode<T>* pNode = FindByKey(nKey);
	if ( NULL == pNode )
	{
		return false;
	}

	if ( m_pHead == pNode )
	{
		m_pHead = m_pHead->m_pNext;
	}
	else
	{
		TSNode<T>* pTemp = m_pHead;
		while ( NULL != pTemp->m_pNext )
		{
			if ( pNode == pTemp->m_pNext )
			{
				break;
			}
			pTemp = pTemp->m_pNext;
		}

		pTemp->m_pNext = pNode->m_pNext;

		if ( m_pLast == pNode )
		{
			m_pLast = pTemp;
		}
	}

	pNode->Clear();
	free(pNode);
	pNode = NULL;
	m_nCount--;

	return true;
}

template <class T> 
int CStdDataList<T>::GetSize() const
{
	return m_nCount;
}

template <class T> 
TSNode<T>* CStdDataList<T>::GetFirstNode()
{
	return m_pHead;
}

template <class T> 
TSNode<T>* CStdDataList<T>::GetLastNode()
{
	return m_pLast;
}

template <class T>
TSNode<T>* CStdDataList<T>::ReverseList()
{
	TSNode<T>* p = m_pHead;
	TSNode<T>* q = NULL;
	TSNode<T>* r = NULL;

	while( p != NULL )
	{
		q = p->m_pNext;
		p->m_pNext = r;
		r = p;
		p = q;
	}

	m_pLast = m_pHead;
	m_pHead = r;
	return r;
}

template <class T> 
T CStdDataList<T>::GetAt(int nKey)
{
	TSNode<T>* pNode = FindByKey(nKey);
	if ( NULL == pNode )
	{
		return false;
	}
	else
	{
		return pNode->m_val;
	}
}

template <class T> 
CStdDataList<T>& CStdDataList<T>::operator = ( const CStdDataList<T>& src )
{
	Clear();

	if ( NULL != src.m_pHead && NULL != src.m_pLast && 0 != src.GetSize() )
	{
		TSNode<T>* pNode = src.m_pHead;
		for( int i = 0; i < src.GetSize(); i++ )
		{
			InsertItem( pNode->m_nKey, pNode->m_val );
			pNode = pNode->m_pNext;
		} 
	}

	return *this;
}

template <class T> 
TSNode<T>* CStdDataList<T>::FindByKey(int nKey)
{
	if ( NULL == m_pHead || NULL == m_pLast || nKey < 0 )
	{
		return NULL;
	}

	TSNode<T>* pNode = m_pHead;
	for ( int i = 0; i < m_nCount; i++ )
	{
		if ( NULL == pNode )
		{
			return NULL;
		}

		if ( nKey == pNode->m_nKey )
		{
			return pNode;
		}

		pNode = pNode->m_pNext;
	}

	return NULL;
}
//////////////////////////////////////////////////////////////////////////
//
template <class T>
class /*UILIB_API*/ CStdDataArray
{
public:
	CStdDataArray();
	CStdDataArray( const CStdDataArray<T>& src );
	~CStdDataArray(){ Clear(); };

public:
	void Clear();
	bool IsEmpty() const;
	int GetSize() const;

	bool AddAtAnd(T val);
	bool AddAt(int nIndex, T val);
	bool Remove(int nIndex);

	bool SetAt(int nIndex, T val);
	T GetAt(int nIndex);
	
	TSNode<T>* FindByKey(int nIndex);
	int FindByData(T tData);

	TSNode<T>* GetFirstNode();
	TSNode<T>* GetLastNode();

	TSNode<T>* ReverseList();

	CStdDataArray<T>& operator = (const CStdDataArray<T>& src);
	T/*&*/ operator[](int nIndex);

protected:
	TSNode<T>* m_pHead;
	TSNode<T>* m_pLast;
	int m_nCount;
};

template <class T> 
CStdDataArray<T>::CStdDataArray() : m_pHead(NULL), m_pLast(NULL), m_nCount(0)
{
}

template <class T> 
CStdDataArray<T>::CStdDataArray(const CStdDataArray<T>& src) : m_pHead(NULL), m_pLast(NULL), m_nCount(0)
{
	if ( NULL != src.m_pHead && NULL != src.m_pLast && 0 != src.GetSize() )
	{
		TSNode<T>* pNode = src.m_pHead;
		for( int i = 0; i < src.GetSize(); i++ )
		{
			AddAt( pNode->m_nKey, pNode->m_val );
			pNode = pNode->m_pNext;
		} 
	}
}

template <class T> 
void CStdDataArray<T>::Clear()
{
	if( NULL != m_pHead )
	{
		TSNode<T>* pNode = m_pHead;
		TSNode<T>* pTemp = NULL;

		for ( int i = 0; i < m_nCount; i++ )
		{
			pTemp = pNode->m_pNext;
			pNode->Clear();
			free(pNode);
			pNode = pTemp;
		}
	}

	m_pHead = m_pLast = NULL;
	m_nCount = 0;
}

template <class T> 
bool CStdDataArray<T>::AddAtAnd(T val)
{
	TSNode<T>* pNode = static_cast<TSNode<T>*>( malloc( sizeof(TSNode<T>) ) );
	if ( NULL == pNode )
	{
		return false;
	}
	pNode->m_nKey = m_nCount;
	pNode->m_val = val;
	pNode->m_pNext = NULL;

	if ( NULL == m_pHead || NULL == m_pLast )
	{
		m_pHead = m_pLast = pNode;
	}
	else
	{
		m_pLast->m_pNext = pNode;
		m_pLast = pNode;
	}

	m_nCount++;

	return true;
}

template <class T>
bool CStdDataArray<T>::AddAt(int nIndex, T val)
{
	if ( nIndex > m_nCount )
	{
		return false;
	}

	if ( nIndex == m_nCount )
	{
		return AddAtAnd( val );
	}

	TSNode<T>* pNode = static_cast<TSNode<T>*>( malloc( sizeof(TSNode<T>) ) );
	if ( NULL == pNode )
	{
		return false;
	}
	pNode->m_nKey = nIndex;
	pNode->m_val = val;
	pNode->m_pNext = NULL;

	TSNode<T>* pOld = FindByKey(nIndex);
	if ( NULL == pOld )
	{
		return false;
	}

	if ( 0 == nIndex )
	{
		pNode->m_pNext = m_pHead;
		m_pHead = pNode;
	}
	else
	{
		TSNode<T>* pPre = FindByKey(nIndex - 1);
		if ( NULL == pPre )
		{
			return false;
		}

		pPre->m_pNext = pNode;
		pNode->m_pNext = pOld;
	}

	while( NULL != pOld )
	{
		pOld->m_nKey = pOld->m_nKey + 1;
		pOld = pOld->m_pNext;
	}

	m_nCount++;

	return true;
}

template <class T> 
bool CStdDataArray<T>::SetAt(int nIndex, T val)
{
	TSNode<T>* pNode = FindByKey(nIndex);
	if ( NULL != pNode )
	{
		pNode->m_val = val;
		return true;
	}

	return false;
}

template <class T> 
bool CStdDataArray<T>::Remove(int nIndex)
{
	TSNode<T>* pNode = FindByKey(nIndex);
	if ( NULL == pNode )
	{
		return false;
	}

	TSNode<T>* pNodeNext = pNode->m_pNext;

	if ( m_pHead == pNode )
	{
		m_pHead = m_pHead->m_pNext;
	}
	else
	{
		TSNode<T>* pPre = FindByKey(nIndex - 1);

		pPre->m_pNext = pNode->m_pNext;

		if ( m_pLast == pNode )
		{
			m_pLast = pPre;
		}
	}

	while( NULL != pNodeNext )
	{
		pNodeNext->m_nKey = pNodeNext->m_nKey - 1;
		pNodeNext = pNodeNext->m_pNext;
	}
	pNode->Clear();
	free(pNode);
	pNode = NULL;

	m_nCount--;

	return true;
}

template <class T> 
int CStdDataArray<T>::GetSize() const
{
	return m_nCount;
}

template <class T> 
TSNode<T>* CStdDataArray<T>::GetFirstNode()
{
	return m_pHead;
}

template <class T> 
TSNode<T>* CStdDataArray<T>::GetLastNode()
{
	return m_pLast;
}

template <class T>
TSNode<T>* CStdDataArray<T>::ReverseList()
{
	TSNode<T>* p = m_pHead;
	TSNode<T>* q = NULL;
	TSNode<T>* r = NULL;

	while( p != NULL )
	{
		q = p->m_pNext;
		p->m_pNext = r;
		r = p;
		p = q;
	}

	m_pLast = m_pHead;
	m_pHead = r;
	return r;
}


template <class T> 
T CStdDataArray<T>::GetAt(int nIndex)
{
	TSNode<T>* pNode = FindByKey(nIndex);
	if ( NULL == pNode )
	{
		return false;
	}
	else
	{
		return pNode->m_val;
	}
}

template <class T> 
CStdDataArray<T>& CStdDataArray<T>::operator = ( const CStdDataArray<T>& src )
{
	Clear();

	if ( NULL != src.m_pHead && NULL != src.m_pLast && 0 != src.GetSize() )
	{
		TSNode<T>* pNode = src.m_pHead;
		for( int i = 0; i < src.GetSize(); i++ )
		{
			AddAt( pNode->m_nKey, pNode->m_val );
			pNode = pNode->m_pNext;
		} 
	}

	return *this;
}

template <class T> 
T/*&*/ CStdDataArray<T>::operator[]( int nIndex )
{
	TSNode<T>* pNode = FindByKey(nIndex);
	if ( NULL == pNode )
	{
		return false;
	}
	else
	{
		return pNode->m_val;
	}
}

template <class T> 
TSNode<T>* CStdDataArray<T>::FindByKey(int nIndex)
{
	if ( NULL == m_pHead || NULL == m_pLast || nIndex < 0 )
	{
		return NULL;
	}

	TSNode<T>* pNode = m_pHead;
	for ( int i = 0; i < m_nCount; i++ )
	{
		if ( NULL == pNode )
		{
			return NULL;
		}

		if ( nIndex == pNode->m_nKey )
		{
			return pNode;
		}

		pNode = pNode->m_pNext;
	}

	return NULL;
}

template <class T> 
int CStdDataArray<T>::FindByData(T tData)
{
	if ( NULL == m_pHead || NULL == m_pLast )
	{
		return -1;
	}

	TSNode<T>* pFindNode = m_pHead;
	for ( int nIndex = 0; nIndex < m_nCount; nIndex++ )
	{
		if ( NULL == pFindNode )
		{
			return -1;
		}

		if ( pFindNode->m_val == tData )
		{
			return pFindNode->m_nKey;
		}

		pFindNode = pFindNode->m_pNext;
	}

	return -1;
}

#endif // __UIBASE_H__
