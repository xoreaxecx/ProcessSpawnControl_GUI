#include "SpawnControl.h"

namespace SpawnControl
{
    std::atomic<bool> ControlEnabled = false;
    IWbemServices* pSvc = NULL;
    IWbemLocator* pLoc = NULL;
    IUnsecuredApartment* pUnsecApp = NULL;
    IUnknown* pStubUnk = NULL;
    EventSink* pSink = NULL;
    IWbemObjectSink* pStubSink = NULL;

    OperationStatus Start()
    {
        HRESULT hres;
        hres = CoInitializeEx(0, COINIT_MULTITHREADED);
        if (FAILED(hres))
        {
            return OperationStatus::ERR_COINIT;
        }

        //hres = CoInitializeSecurity(
        //    NULL,
        //    -1,
        //    NULL,
        //    NULL,
        //    RPC_C_AUTHN_LEVEL_DEFAULT,
        //    RPC_C_IMP_LEVEL_IMPERSONATE,
        //    NULL,
        //    EOAC_NONE,
        //    NULL);
        //if (FAILED(hres))
        //{
        //    CoUninitialize();
        //    return OperationStatus::ERR_COINIT_SEC;
        //}

        pLoc = NULL;
        hres = CoCreateInstance(CLSID_WbemLocator, 0, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID*)&pLoc);
        if (FAILED(hres))
        {
            CoUninitialize();
            return OperationStatus::ERR_CREATE_WBEMLOC;
        }

        pSvc = NULL;
        hres = pLoc->ConnectServer(_bstr_t(L"ROOT\\CIMV2"), NULL, NULL, 0, NULL, 0, 0, &pSvc);
        if (FAILED(hres))
        {
            pLoc->Release();
            CoUninitialize();
            return OperationStatus::ERR_CONNECT;
        }

        hres = CoSetProxyBlanket(
            pSvc,
            RPC_C_AUTHN_WINNT,
            RPC_C_AUTHZ_NONE,
            NULL,
            RPC_C_AUTHN_LEVEL_CALL,
            RPC_C_IMP_LEVEL_IMPERSONATE,
            NULL,
            EOAC_NONE);

        if (FAILED(hres))
        {
            pSvc->Release();
            pLoc->Release();
            CoUninitialize();
            return OperationStatus::ERR_PROXY;
        }

        pUnsecApp = NULL;
        hres = CoCreateInstance(CLSID_UnsecuredApartment, NULL, CLSCTX_LOCAL_SERVER,
            IID_IUnsecuredApartment, (void**)&pUnsecApp);

        if (FAILED(hres))
        {
            pSvc->Release();
            pLoc->Release();
            CoUninitialize();
            return OperationStatus::ERR_CREATE_UNSECAP;
        }

        pSink = new EventSink;
        pSink->AddRef();

        pStubUnk = NULL;
        pUnsecApp->CreateObjectStub(pSink, &pStubUnk);

        pStubSink = NULL;
        pStubUnk->QueryInterface(IID_IWbemObjectSink, (void**)&pStubSink);

        hres = pSvc->ExecNotificationQueryAsync(
            _bstr_t("WQL"),
            _bstr_t("SELECT * FROM __InstanceCreationEvent WITHIN 1 WHERE TargetInstance ISA 'Win32_Process'"),
            WBEM_FLAG_SEND_STATUS,
            NULL,
            pStubSink);

        if (FAILED(hres))
        {
            pSvc->Release();
            pLoc->Release();
            pUnsecApp->Release();
            pStubUnk->Release();
            pSink->Release();
            pStubSink->Release();
            CoUninitialize();
            return OperationStatus::ERR_QUERY;
        }

        ControlEnabled.store(true, std::memory_order_seq_cst);
        return OperationStatus::SUCCESS;
    }

    void Stop()
    {
        if (ControlEnabled.load(std::memory_order_seq_cst))
        {
            ControlEnabled.store(false, std::memory_order_seq_cst);
            pSvc->CancelAsyncCall(pStubSink);
            pSvc->Release();
            pLoc->Release();
            pUnsecApp->Release();
            pStubUnk->Release();
            pSink->Release();
            pStubSink->Release();
            CoUninitialize();
        }
    }
}
