#ifndef SAFEADAPTER_H
#define SAFEADAPTER_H

#include "osp.h"
#include "kdvtype.h"


class ILock
{
public:
	ILock(){}
	virtual ~ILock(){}
	virtual BOOL32 Lock(u32 dwTimeout = INFINITE) = 0;
	virtual BOOL32 Unlock() = 0;
};

template<class T, class S = CLock>
class CTAapater
{
protected:
	class LockProxy
	{
	public:
		LockProxy(T* pT, S& Lock): m_pT(pT), m_rLock(Lock)
		{
			m_rLock.Lock();
		}
		~LockProxy() 
		{
			m_rLock.Unlock();
		}
		
		T* operator->()    {  return m_pT; }
		
	private:
		T* m_pT;
		S& m_rLock;
	};
	
	public:
		CTAapater()  {  m_pT = new T;  }
		~CTAapater() {  delete m_pT;  }
		LockProxy operator->()  
		{ 
			return LockProxy(m_pT, m_Lock); 
		}
		
	private:
		T* m_pT;
		S m_Lock;
};

/**
 * 局部锁.在作用域内进行lock.析构时自动unlock
 */

class ScopedLock
{
public:
    explicit ScopedLock(ILock& lock) : m_lock(lock)
    {
        m_lock.Lock();
    }
    explicit ScopedLock(ILock* pLock) : m_lock(*pLock)
    {
        m_lock.Lock();
    }
    ~ScopedLock()
    {
        m_lock.Unlock();
    }
protected:
    ILock& m_lock;

private:
	ScopedLock( const ScopedLock& );
	const ScopedLock& operator=( const ScopedLock& ){ return *this; }
};

class COspLock : public ILock
{
	SEMHANDLE m_hSem;
public:
	COspLock()
	{
		::OspSemBCreate(&m_hSem);
	}
	virtual ~COspLock()
	{
		::OspSemDelete(m_hSem);
	}
	virtual BOOL32 Lock(u32 dwTimeout = INFINITE)
	{
		return ::OspSemTakeByTime(m_hSem, dwTimeout);
	}

	virtual BOOL32 Unlock()
	{
		return ::OspSemGive(m_hSem);
	}
};
#define SCOPED_LOCK_OSP(theLock) ScopedLock NoNameLock##__LINE__(theLock)

#ifdef _WINDOWS_
class CLock : public ILock
{
	HANDLE m_hMutex;
public:
	CLock()
	{
		m_hMutex = ::CreateMutex(NULL, FALSE, NULL);
	};
	~CLock()
	{
		::CloseHandle(m_hMutex);
	};
public:

	virtual BOOL32 Lock(u32 dwTimeout = INFINITE)
	{
		return (::WaitForSingleObject(m_hMutex, dwTimeout) == WAIT_OBJECT_0);
	}

	virtual BOOL32 Unlock()
	{
		return ::ReleaseMutex(m_hMutex);
	}
};
#define SCOPED_LOCK_MX(theLock) ScopedLock NoNameLock##__LINE__(theLock)

class CWinCsLock : public ILock
{
public:
	CWinCsLock()
	{
		::InitializeCriticalSection(&m_cs);
	}
	~CWinCsLock()
	{
		::DeleteCriticalSection(&m_cs);
	}
	virtual BOOL32 Lock(u32 dwTimeout = INFINITE)
	{
		EnterCriticalSection(&m_cs);
		return TRUE;
	}
	virtual BOOL32 Unlock()
	{
		LeaveCriticalSection(&m_cs);
		return TRUE;
	}
private:
	CRITICAL_SECTION m_cs;
};
#define SCOPED_LOCK_CS(theLock) ScopedLock NoNameLock##__LINE__(theLock)
#endif

#endif