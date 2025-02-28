#pragma once
#define _WIN32_DCOM
//#include <iostream>
#include <comdef.h>
#include <Wbemidl.h>

#pragma comment(lib, "wbemuuid.lib")

class EventSink : public IWbemObjectSink
{
    LONG m_lRef;
    bool bDone;

public:
    EventSink() { m_lRef = 0; bDone = false; }
    ~EventSink() { bDone = true; }

    virtual ULONG STDMETHODCALLTYPE AddRef();
    virtual ULONG STDMETHODCALLTYPE Release();
    virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppv);

    virtual HRESULT STDMETHODCALLTYPE Indicate(
        LONG lObjectCount,
        IWbemClassObject __RPC_FAR* __RPC_FAR* apObjArray
    );

    virtual HRESULT STDMETHODCALLTYPE SetStatus(
        LONG lFlags,
        HRESULT hResult,
        BSTR strParam,
        IWbemClassObject __RPC_FAR* pObjParam
    );
};
