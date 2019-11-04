#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H_

#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "kdvtype.h"

typedef int BOOL, BOOL32;

#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

struct CXMLPlex     // warning variable length structure
{
	CXMLPlex* pNext;

	void* data() { return this+1; }
	
	static CXMLPlex* Create( CXMLPlex*& pHead, u32 nMax, u32 cbElement )
	{
		if( nMax < 0 || cbElement < 0 )
		{
			return NULL;
		}

		CXMLPlex* p = (CXMLPlex*) new u8[sizeof(CXMLPlex) + nMax * cbElement];
		// may throw exception
		p->pNext = pHead;
		pHead    = p;  // change head (adds in reverse order for simplicity)

		return p;
	}
	
	void FreeDataChain()     // free this one and links
	{
		CXMLPlex* p = this;
		while ( NULL != p )
		{
			u8* bytes = (u8*) p;
			CXMLPlex* pNext = p->pNext;
			delete[] bytes;
			p = pNext;
		}
	}	
};

enum EMHashType
{
	emHashNone = 0,
	emSDBMHash,
	emELFHash,
	emHashEnd = 5
};

class CMapStrToInt
{
protected:
	// Association
	struct CAssoc
	{
		CAssoc* pNext;		
		void*   key;
		int     value;
	};
	
public:	
	// Construction
	CMapStrToInt( )
	{
		//assert(dwBlockSize > 0);
		
		m_pHashTable      = NULL;
		m_dwHashTableSize = 17;  // default size
		m_dwCount         = 0;
		m_pFreeList       = NULL;
		m_pBlocks         = NULL;
		m_dwBlockSize     = 10;
	}
	
	~CMapStrToInt()
	{
		RemoveAll();
	}

	// Init
	void InitHashTable( u32 dwHashSize, BOOL bAllocNow = TRUE )
	{
		assert(this);
		assert(m_dwCount == 0);
		assert(dwHashSize > 0);
		
		if ( NULL != m_pHashTable )
		{
			// free hash table
			delete[] m_pHashTable;
			m_pHashTable = NULL;
		}
		
		if ( bAllocNow )
		{
			m_pHashTable = new CAssoc* [dwHashSize];
			memset(m_pHashTable, 0, sizeof(CAssoc*) * dwHashSize);
		}
		
		m_dwHashTableSize = dwHashSize;
	}
	
	// Operations
	// add a new (key, value) pair
	void SetAt( const s8* str, int dwValue, EMHashType emHashType = emSDBMHash )
	{
		u32 dwHashValue = 0;
		if ( !Hash( str, dwHashValue, emHashType) )
		{
			printf("SetAt::Hash error!\n");
			return;
		}

		SetAt( (void*)dwHashValue, dwValue );
	}

	int GetValueAt( void* key ) const
	{
		if ( NULL == m_pHashTable )
		{
			return 0;
		}
		
		u32 nHash = HashKey(key) % m_dwHashTableSize;
		
		// see if it exists
		CAssoc* pAssoc = NULL;
		for ( pAssoc = m_pHashTable[nHash]; pAssoc != NULL; pAssoc = pAssoc->pNext )
		{
			if ( pAssoc->key == key )
			{
				return pAssoc->value;
			}
		}

		return 0;
	}

	// Routine used to user-provided hash keys
	BOOL Hash( const s8* str, u32& dwHashValue, EMHashType emHashType = emSDBMHash )
	{
		if ( NULL == str )
		{
			printf( "Hash NULL string, error!\n" );
			return FALSE;
		}
		
		switch ( emHashType )
		{
			case emSDBMHash:
			{
				dwHashValue = SDBMHash(str);
				return TRUE;
				break;
			}
			case emELFHash:
			{
				dwHashValue = ELFHash(str);
				return TRUE;
				break;
			}
			default:
				break;
		}
		
		return FALSE;
	}
	
	// Lookup
	BOOL Lookup( const s8* str, int& dwValue, EMHashType emHashType = emSDBMHash )
	{
		assert(this);
		u32 dwHashValue = 0;
		if ( !Hash( str, dwHashValue, emHashType) )
		{
			printf( "Lookup::Hash error! key:%s\n", str );
			return FALSE;
		}

		BOOL bFind = Lookup( (void*)dwHashValue, dwValue );
		if (!bFind)
		{
			printf( "Not Find value for key: %s\n", str );	
		}
		return bFind;
	}

	// removing existing (key, ?) pair
	BOOL RemoveKey( const s8* str, EMHashType emHashType = emSDBMHash )
	{
		assert(this);

		u32 dwHashValue = 0;
		if ( !Hash( str, dwHashValue, emHashType) )
		{
			printf( "Lookup::Hash error!:%d\n", str );
			return FALSE;
		}

		return RemoveKey( (void*)dwHashValue );
	}
		
	// advanced features
	u32  GetHashTableSize() const 
	{
		return m_dwHashTableSize; 
	}

	u32  GetCount() const 
	{
		return m_dwCount; 
	}

	BOOL IsEmpty() const 
	{
		return m_dwCount == 0; 
	}

	void SetBlockSize(u32 dwBlockSize, u32 dwHashSize = 17)
	{
		m_dwBlockSize = dwBlockSize;
		m_dwHashTableSize = dwHashSize;
	}
	
	// Implementation
protected:
	CAssoc**   m_pHashTable;
	u32        m_dwHashTableSize;
	u32        m_dwCount;
	CAssoc*    m_pFreeList;

	CXMLPlex*  m_pBlocks;
	u32        m_dwBlockSize;

	// Lookup and add if not there
	int& operator[]( void* key )
	{
		assert(this);
		
		u32 dwHashValue;
		CAssoc* pAssoc;
		if ( NULL == (pAssoc = GetAssocAt(key, dwHashValue)) )
		{
			if ( NULL == m_pHashTable )
			{
				InitHashTable(m_dwHashTableSize);
			}
			
			// it doesn't exist, add a new Association
			pAssoc = NewAssoc();
			
			// 'pAssoc->value' is a constructed object, nothing more
			pAssoc->key = key;
			
			// put into hash table
			pAssoc->pNext = m_pHashTable[dwHashValue];
			m_pHashTable[dwHashValue] = pAssoc;
		}
		
		return pAssoc->value;  // return new reference
	}
	
	// Internal hash function, not used by user.
	u32 HashKey( void* key ) const
	{
		return ((u32)(void*)(u32)key) >> 4;
	}
	
	u32 SDBMHash( const s8* str) const
	{
		u32 dwHashValue = 0;
		s8* p = (s8*)str;
		
		while (*p)
		{
			dwHashValue = (*p++) + (dwHashValue << 6) + (dwHashValue << 16) - dwHashValue;
		}
		
		return dwHashValue;
	}
	
	u32 ELFHash( const s8* str )
	{
		u32 dwHashValue = 0 ;
		u32 x = 0 ;
		
		while  ( *str )
		{
			dwHashValue  =  ( dwHashValue << 4 ) + ( *str++ );
			if ( ( x = dwHashValue & 0xF0000000L ) != 0 )
			{
				dwHashValue ^= ( x >> 24 );
				dwHashValue &= ~x;
			}
		}
		
		return( dwHashValue & 0x7FFFFFFF );
	}

	BOOL Lookup( void* key, int& dwValue ) const
	{
		assert(this);
		
		u32 dwHash = 0;
		CAssoc* pAssoc = GetAssocAt(key, dwHash);
		if ( NULL == pAssoc )
		{
			//printf( "Not Find value for key: %s\n", (s8*)key );	
			return FALSE;  // not in map;
		}
		
		dwValue = pAssoc->value;
		return TRUE;
	}	
	
	void SetAt( void* key, int dwValue ) 
	{ 
		(*this)[key] = dwValue; 
	}

	BOOL RemoveKey( void* key )
	{
		assert(this);
		
		if ( NULL == m_pHashTable )
		{
			return FALSE;  // nothing in the table
		}
		
		CAssoc** ppAssocPrev = NULL;
		ppAssocPrev = &m_pHashTable[HashKey(key) % m_dwHashTableSize];
		
		CAssoc* pAssoc = NULL;
		for ( pAssoc = *ppAssocPrev; pAssoc != NULL; pAssoc = pAssoc->pNext )
		{
			if (pAssoc->key == key)
			{
				// remove it
				*ppAssocPrev = pAssoc->pNext;  // remove from list
				FreeAssoc(pAssoc);
				return TRUE;
			}
			
			ppAssocPrev = &pAssoc->pNext;
		}
		
		return FALSE;  // not found
	}

	CAssoc* NewAssoc()
	{
		if ( NULL == m_pFreeList )
		{
			// add another block
			CXMLPlex* newBlock = CXMLPlex::Create(m_pBlocks, m_dwBlockSize, sizeof(CAssoc));
			// chain them into free list
			CAssoc* pAssoc = (CAssoc*)newBlock->data();
			// free in reverse order to make it easier to debug
			pAssoc += m_dwBlockSize - 1;
			for ( int i = m_dwBlockSize-1; i >= 0; i--, pAssoc-- )
			{
				pAssoc->pNext = m_pFreeList;
				m_pFreeList   = pAssoc;
			}
		}
		assert(m_pFreeList != NULL);  // we must have something
		
		CAssoc* pAssoc = NULL;
		pAssoc         = m_pFreeList;
		m_pFreeList    = m_pFreeList->pNext;
		m_dwCount++;
		assert(m_dwCount > 0);  // make sure we don't overflow
		
		pAssoc->key   = 0;
		pAssoc->value = 0;
		
		return pAssoc;
	}

	void FreeAssoc( CAssoc* pAssoc )
	{
		pAssoc->pNext = m_pFreeList;
		m_pFreeList   = pAssoc;
		m_dwCount--;
		assert(m_dwCount >= 0);  // make sure we don't underflow
		
		// if no more elements, cleanup completely
		if (m_dwCount == 0)
		{
			RemoveAll();
		}
	}

	CAssoc* GetAssocAt( void* key, u32& dwHash ) const
	{
		dwHash = HashKey(key) % m_dwHashTableSize;
		
		if ( NULL == m_pHashTable )
		{
			return NULL;
		}
		
		// see if it exists
		CAssoc* pAssoc = NULL;
		for ( pAssoc = m_pHashTable[dwHash]; pAssoc != NULL; pAssoc = pAssoc->pNext )
		{
			//printf( "nHash:%d, value:%d\n", dwHash, pAssoc->value );
			if ( pAssoc->key == key )
			{
				return pAssoc;
			}
		}

		return NULL;
	}

	void RemoveAll()
	{
		assert(this);
		
		if ( NULL != m_pHashTable )
		{
			delete[] m_pHashTable;
			m_pHashTable = NULL;
		}
		
		m_dwCount   = 0;
		m_pFreeList = NULL;
		m_pBlocks->FreeDataChain();
		m_pBlocks   = NULL;
	}
};

#endif  //_HASH_TABLE_H_
