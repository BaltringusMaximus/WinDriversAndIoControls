#pragma once
#include <ntddk.h>
#include <wdf.h>
#include <wdmsec.h>
#define NDIS630
#include <ndis.h>
#define INITGUID
#include <fwpmk.h>
#include <fwpsk.h>
#include <fwpmu.h>
#include <guiddef.h>
#define ALLOC_TAG_NAME (ULONG)'TG_1'
#define INVERTED_QUEUE_LIST\
    X(WDFQUEUE, INVERTED_QUEUE) \
    X(WDFQUEUE, INVERTED_QUEUE_2) \
    X(WDFQUEUE, INVERTED_QUEUE_3) \
    X(WDFQUEUE, INVERTED_QUEUE_4) \
    X(WDFQUEUE, INVERTED_QUEUE_5) \
    X(WDFQUEUE, INVERTED_QUEUE_6) \
    X(WDFQUEUE, INVERTED_QUEUE_7) \
    X(WDFQUEUE, INVERTED_QUEUE_8) \
    X(WDFQUEUE, INVERTED_QUEUE_9) \
    X(WDFQUEUE, INVERTED_QUEUE_10) 

typedef struct {
#define X(type, name) type name;
    INVERTED_QUEUE_LIST
#undef X
}structInvertedQueueList;
structInvertedQueueList rxInvertedIoQueue;
//code not reviewed simply pasted from https://v3ded.github.io/redteam/red-team-tactics-writing-windows-kernel-drivers-for-advanced-persistence-part-2
DEFINE_GUID(CALLOUT_GUID_INBOUND, 0x8aadb11d, 0xe10e, 0x480d, 0xa6, 0x69, 0x61, 0xdb, 0xcc, 0x86, 0x58, 0xe6);
DEFINE_GUID(SUB_LAYER_GUID, 0xa7e76cdd, 0x5b2e, 0x4ffd, 0xa8, 0x9d, 0xf5, 0x69, 0x91, 0x17, 0x56, 0xe7);
// {24B3F93C-ACED-45EF-90D0-3CB082B8363A}
DEFINE_GUID(CALLOUT_GUID_OUTBOUND, 0x24b3f93c, 0xaced, 0x45ef, 0x90, 0xd0, 0x3c, 0xb0, 0x82, 0xb8, 0x36, 0x3a);


PDEVICE_OBJECT  filterDeviceObject; // Device object for the filter engine
HANDLE          engineHandle;       // Handle to the filter engine
UINT32          registerCalloutIdIn = 1;  // Identifier of the registered callout
UINT32          registerCalloutIdOut = 2;
UINT32          addCalloutIdIn;       // Identifier of the added callout
UINT32          addCalloutIdOut;
UINT64          filterIdIn;           // Identifier of the added filter
UINT64          filterIdOut;

NTSTATUS  CalloutRegister(GUID CALLOUT_GUID, UINT32 *registerCalloutId, FWPS_CALLOUT_CLASSIFY_FN3 CalloutFilter);
VOID      CalloutFilterIn(const FWPS_INCOMING_VALUES* inFixedValues, const FWPS_INCOMING_METADATA_VALUES* inMetaValues, void* layerData, const void* classifyContext, const FWPS_FILTER* filter, UINT64 flowContext, FWPS_CLASSIFY_OUT* classifyOut);
VOID      CalloutFilterOut(const FWPS_INCOMING_VALUES* inFixedValues, const FWPS_INCOMING_METADATA_VALUES* inMetaValues, void* layerData, const void* classifyContext, const FWPS_FILTER* filter, UINT64 flowContext, FWPS_CLASSIFY_OUT* classifyOut);
NTSTATUS  CalloutNotify(FWPS_CALLOUT_NOTIFY_TYPE notifyType, const GUID* filterKey, FWPS_FILTER* filter);
NTSTATUS  CalloutAdd(GUID CALLOUT_GUID, GUID LayerApplied, UINT32 *addCalloutId);
NTSTATUS  SublayerAdd();
NTSTATUS  FilterAdd(GUID CALLOUT_GUID, GUID LayerApplied, UINT64 *filterId);

//testing contiguous memory allocation variables
WDFMEMORY contiguousMemoryForPacket = NULL;
VOID* pBufferContiguousMemory = NULL;
MDL* pMdlBufferContiguousMemory = NULL;
#define lengthBufferContiguousMemory 500000
VOID* pStartAddressOfMappedPages = NULL;
VOID** pAddressValueStartAddressOfMappedPages = &pStartAddressOfMappedPages;
INT intByteOffsetFromContiguousMemory = 0;
INT intNumberOfDroppedPacket = 0;
INT intNumberOfActivePacket = 0;
WDFREQUEST currentInRequest = NULL;
NTSTATUS statusRequestIn;
NTSTATUS statusPurge;

VOID TermCalloutIds(UINT32 registerCalloutId, UINT32 addCalloutId, UINT64 filterId);
VOID Cleanup(UINT32 registerCalloutId, UINT32 addCalloutId, UINT64 filterId);
//end of code not reviewed
#define IOCTL_TEST CTL_CODE(FILE_DEVICE_UNKNOWN, 0x2049, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_TEST_INVERTED CTL_CODE(FILE_DEVICE_UNKNOWN, 0x2050, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_TEST_INVERTED_2 CTL_CODE(FILE_DEVICE_UNKNOWN, 0x2053, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_TEST_INVERTED_3 CTL_CODE(FILE_DEVICE_UNKNOWN, 0x2054, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_TEST_INVERTED_4 CTL_CODE(FILE_DEVICE_UNKNOWN, 0x2055, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_TEST_INVERTED_5 CTL_CODE(FILE_DEVICE_UNKNOWN, 0x2056, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_TEST_INVERTED_6 CTL_CODE(FILE_DEVICE_UNKNOWN, 0x2057, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_TEST_INVERTED_7 CTL_CODE(FILE_DEVICE_UNKNOWN, 0x2058, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_TEST_INVERTED_8 CTL_CODE(FILE_DEVICE_UNKNOWN, 0x2059, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_TEST_INVERTED_9 CTL_CODE(FILE_DEVICE_UNKNOWN, 0x2060, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_TEST_INVERTED_10 CTL_CODE(FILE_DEVICE_UNKNOWN, 0x2061, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_PURGE_ALL_NON_DEFAULT_QUEUES CTL_CODE(FILE_DEVICE_UNKNOWN, 0x4095, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_GET_KERNEL_BUFFER_ADDRESS CTL_CODE(FILE_DEVICE_UNKNOWN, 0x4094, METHOD_BUFFERED, FILE_ANY_ACCESS)


//#define IOCTL_INVERT_NOTIFICATION CTL_CODE(FILE_DEVICE_INVERTED, 2051, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_INVERT_SIMULATE_EVENT_OCCURRED CTL_CODE(FILE_DEVICE_UNKNOWN, 0x2052, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define NTDEVICE_NAME_STRING      L"\\Device\\NONPNP1"
#define SYMBOLIC_NAME_STRING     L"\\??\\SpotlessDeviceLink"
#define POOL_TAG                   'ELIF'
#define WFP_NBL_POOL_TAG           'gogo'
#define WDF_MEMORY_POOL_TAG        'bron'
typedef struct _CONTROL_DEVICE_EXTENSION {

    HANDLE   FileHandle; // Store your control data here

} CONTROL_DEVICE_EXTENSION, * PCONTROL_DEVICE_EXTENSION;

WDF_DECLARE_CONTEXT_TYPE_WITH_NAME(CONTROL_DEVICE_EXTENSION,
    ControlGetData)

    DRIVER_INITIALIZE DriverEntry;
//EVT_WDF_DRIVER_DEVICE_ADD KmdfHelloWorldEvtDeviceAdd;
EVT_WDF_DRIVER_UNLOAD DriverUnload;
EVT_WDF_DEVICE_CONTEXT_CLEANUP NonPnpEvtDriverContextCleanup;
EVT_WDF_IO_QUEUE_IO_DEVICE_CONTROL FileEvtIoDeviceControl;
//EVT_WDF_IO_QUEUE_IO_DEVICE_CONTROL FileEvtIoDeviceControl2;
EVT_WDF_IO_QUEUE_IO_DEFAULT FileEvtIoDefault;
EVT_WDF_DEVICE_FILE_CREATE NonPnpEvtDeviceFileCreate;
EVT_WDF_FILE_CLOSE NonPnpEvtFileClose;
NTSTATUS NonPnpDeviceAdd(IN WDFDRIVER Driver, IN PWDFDEVICE_INIT DeviceInit);
NDIS_HANDLE handleNetBufferListPool = NULL;

WDFQUEUE                            queueIoInverted;
WDFQUEUE                            queueIoInverted_2;
WDFQUEUE                            queueIoInverted_3;
WDFQUEUE                            queueIoInverted_4;
WDFQUEUE                            queueIoInverted_5;
WDFQUEUE                            queueIoInverted_6;
WDFQUEUE                            queueIoInverted_7;
WDFQUEUE                            queueIoInverted_8;
WDFQUEUE                            queueIoInverted_9;
WDFQUEUE                            queueIoInverted_10;
WDFQUEUE                            queueIoPurgeEvent;
#define segmentTotalMemory  3276800
int remainingMemory = segmentTotalMemory;


NTSTATUS
DriverEntry(
    _In_ PDRIVER_OBJECT     DriverObject,
    _In_ PUNICODE_STRING    RegistryPath
)
{
    WDFDRIVER                      hDriver;
    PWDFDEVICE_INIT                pInit = NULL;
    WDF_OBJECT_ATTRIBUTES          attributes;
    // NTSTATUS variable to record success or failure
    NTSTATUS status = STATUS_SUCCESS;

    // Allocate the driver configuration object
    WDF_DRIVER_CONFIG config;

    // Print "Hello World" for DriverEntry
    KdPrintEx((DPFLTR_IHVDRIVER_ID, DPFLTR_INFO_LEVEL, "KmdfHelloWorld: DriverEntry\n"));
    DbgPrint("INFO: hello from driver entry\n");

    NET_BUFFER_LIST_POOL_PARAMETERS poolParams = { 0 };
    poolParams.Header.Type = NDIS_OBJECT_TYPE_DEFAULT;
    poolParams.Header.Revision = NET_BUFFER_LIST_POOL_PARAMETERS_REVISION_1;
    poolParams.Header.Size = NDIS_SIZEOF_NET_BUFFER_LIST_POOL_PARAMETERS_REVISION_1;
    poolParams.ProtocolId = NDIS_PROTOCOL_ID_DEFAULT;
    // With fAllocateNetBuffer = TRUE and DataSize = 0, NDIS will allocate a net
    // buffer but not any data buffers when we allocate a net buffer and net
    // buffer list.
    poolParams.fAllocateNetBuffer = TRUE;
    poolParams.ContextSize = 0;
    poolParams.PoolTag = WFP_NBL_POOL_TAG;
    poolParams.DataSize = 0;
    handleNetBufferListPool = NdisAllocateNetBufferListPool(NULL, &poolParams);
    if (!handleNetBufferListPool)
    {
        DbgPrint("ERROR: Can't create net buffer list pool\n");
        DriverUnload(NULL);
        return STATUS_UNSUCCESSFUL;
    }
    else if (handleNetBufferListPool)
    {
        DbgPrint("SUCCESS: successfully created a net buffer list pool\n");
    }
    //    pContiguousMemoryForPackets = MmAllocateContiguousMemory(524288, MAXULONG64);
    status = WdfMemoryCreate(WDF_NO_OBJECT_ATTRIBUTES, NonPagedPool, WDF_MEMORY_POOL_TAG, lengthBufferContiguousMemory, &contiguousMemoryForPacket, &pBufferContiguousMemory);
    if (!NT_SUCCESS(status))
    {
        DbgPrint("ERROR: Failed to create a WDFMEMORY object with status 0x%x\n", status);
    }
    else if (NT_SUCCESS(status))
    {
        DbgPrint("SUCCESS: Created a WDFMEMORY object with status 0x%x\n", status);
    }
    //RtlZeroMemory(&pContiguousMemoryForPacket, );
    BYTE* pBufferContiguousMemoryByte = NULL;
    pBufferContiguousMemoryByte = (BYTE*)pBufferContiguousMemory;
    DbgPrint("%x\n%x\n", pBufferContiguousMemoryByte, pBufferContiguousMemory);
    //    RtlZeroMemory(&pBufferContiguousMemoryByte,8);
    DbgPrint("%x\n%x\n", pBufferContiguousMemoryByte, pBufferContiguousMemory);
    size_t sizeBufferSize = 0;
    WdfMemoryGetBuffer(contiguousMemoryForPacket, &sizeBufferSize);
    DbgPrint("size of the buffer = %d\n", sizeBufferSize);
    RtlZeroMemory(pBufferContiguousMemory, sizeBufferSize);
    //    RtlZeroMemory( (& pBufferContiguousMemoryByte), 8);
    DbgPrint("INFO: rtlzeromemory done\n");
    DbgPrint("INFO: buffer value = 0x%X,0x%X at address 0x%p", pBufferContiguousMemoryByte, *(&pBufferContiguousMemoryByte), pBufferContiguousMemoryByte);
    /*
    for (int i = 0; i < sizeBufferSize; i++)
    {
        DbgPrint("%x ", pBufferContiguousMemoryByte[i]);
    }
    */
    DbgPrint("\n");
    DbgPrint("INFO: current MDL for memory buffer 0x%p\n", pMdlBufferContiguousMemory);

    // Since i'm not completely sure casting a size_t sizeBufferSize to a ULONG for the sake of this function call, might wanna stick to the defined lengthBufferContiguousMemory..
    // idk what odd behavious it might trigger if I port it to 32bit so better play it safe. Might wanna check out the rest of the driver for 32bit / 64bit whacky stuff
    
    //the following might have to be called from the evtiocontrol routine?
    /*
    pMdlBufferContiguousMemory = IoAllocateMdl(pBufferContiguousMemory, lengthBufferContiguousMemory, FALSE, FALSE, NULL);
    if (pMdlBufferContiguousMemory == NULL)
    {
        DbgPrint("ERROR: failed to allocate an MDL for the buffer\n");
    }
    else if (pMdlBufferContiguousMemory != NULL)
    {
        DbgPrint("SUCCESS: allocated MDL for memory buffer 0x%p\n", pMdlBufferContiguousMemory);
    }
    MmBuildMdlForNonPagedPool(pMdlBufferContiguousMemory);
    DbgPrint("INFO: Address of mapped pages before MmMapLockedPagesSpecifyCache = %p\n", pStartAddressOfMappedPages);
    pStartAddressOfMappedPages = MmMapLockedPagesSpecifyCache(pMdlBufferContiguousMemory, UserMode, MmWriteCombined, NULL, FALSE, HighPagePriority);
    if (pStartAddressOfMappedPages == NULL)
    {
        DbgPrint("ERROR: failed to map pages for user mode\n");
    }
    else if (pStartAddressOfMappedPages != NULL)
    {
        DbgPrint("SUCCESS: mapped pages for user mode 0x%p\n", pStartAddressOfMappedPages);
        DbgPrint("INFO: value of the address = 0x%llX\n", *pAddressValueStartAddressOfMappedPages);

    }
    */


    // for testing purpose
    UCHAR testChar[4] = {1,2,3,4};
    WdfMemoryCopyFromBuffer(contiguousMemoryForPacket, 0, &testChar, (int)sizeof(testChar));
    DbgPrint("test value at contiguous memory for paccket = %X%X%X%X\n", pBufferContiguousMemoryByte[0], pBufferContiguousMemoryByte[1], pBufferContiguousMemoryByte[2], pBufferContiguousMemoryByte[3]);
    
    // end of copy testing

    // Initialize the driver configuration object to register the
    // entry point for the EvtDeviceAdd callback, KmdfHelloWorldEvtDeviceAdd

    // this 

    /*
    WDF_DRIVER_CONFIG_INIT(&config,
        KmdfHelloWorldEvtDeviceAdd
    );
    */
    // OR 
    WDF_OBJECT_ATTRIBUTES_INIT(&attributes);
    attributes.EvtCleanupCallback = NonPnpEvtDriverContextCleanup;

    WDF_DRIVER_CONFIG_INIT(&config,
        NULL
    );


    config.DriverInitFlags = WdfDriverInitNonPnpDriver;
    config.EvtDriverUnload = DriverUnload;

    // Finally, create the driver object
    status = WdfDriverCreate(DriverObject,
        RegistryPath,
        &attributes,
        &config,
        &hDriver
    );
    if (!NT_SUCCESS(status))
    {
        DbgPrint("ERROR: Failed to create a driver object\n %x\n", status);
    }
    else if (NT_SUCCESS(status))
    {
        DbgPrint("SUCCESS: Created a driver object\n %x\n", status);
    };
    pInit = WdfControlDeviceInitAllocate(
        hDriver,
        &SDDL_DEVOBJ_SYS_ALL_ADM_RWX_WORLD_RW_RES_R
    );
    if (pInit == NULL) {
        status = STATUS_INSUFFICIENT_RESOURCES;
        DbgPrint("ERROR: insufficient ressources for WdfControlDeviceInitAllocate\n");
        return status;
    }
    else if (pInit != NULL) {
        DbgPrint("SUCCESS: WDFDEVICE_INIT structure allocated at %p\n", pInit);
    }
    status = NonPnpDeviceAdd(hDriver, pInit);
    // following code simply to remove the device initialized since there isn't any deviceadd function yet
    // remove if there is a deviceadd function operating
    /*
    WdfDeviceInitFree(pInit);
    DbgPrint("freed device %p\n", pInit);
    pInit = NULL;
    */

    
            
    return status;
}
/*
NTSTATUS
KmdfHelloWorldEvtDeviceAdd(
    _In_    WDFDRIVER       Driver,
    _Inout_ PWDFDEVICE_INIT DeviceInit
)
{
    // We're not using the driver object,
    // so we need to mark it as unreferenced
    UNREFERENCED_PARAMETER(Driver);
    NTSTATUS status;

    // Allocate the device object
    WDFDEVICE hDevice;

    // Print "Hello World"
    KdPrintEx((DPFLTR_IHVDRIVER_ID, DPFLTR_INFO_LEVEL, "KmdfHelloWorld: KmdfHelloWorldEvtDeviceAdd\n"));
    DbgPrint("hello from KmdfHelloWorldEvtDeviceAdd\n");
    // Create the device object
    status = WdfDeviceCreate(&DeviceInit,
        WDF_NO_OBJECT_ATTRIBUTES,
        &hDevice
    );
    return status;
}
*/
VOID
DriverUnload(_In_ WDFDRIVER Driver)
{
    UNREFERENCED_PARAMETER(Driver);
    DbgPrint("INFO: inside DriverUnload registerCalloutIdIn = %u, addCalloutIdIn = %u, filterIdIn = %u\n", registerCalloutIdIn, addCalloutIdIn, filterIdIn);
    Cleanup(registerCalloutIdIn, addCalloutIdIn, filterIdIn);
    DbgPrint("INFO: inside DriverUnload registerCalloutIdOut = %u, addCalloutIdOut = %u, filterIdOut = %u\n", registerCalloutIdOut, addCalloutIdOut, filterIdOut);
    Cleanup(registerCalloutIdOut, addCalloutIdOut, filterIdOut);
    DbgPrint("INFO: hello from DriverUnload\n");
    NdisFreeNetBufferListPool(handleNetBufferListPool);
    DbgPrint("INFO: freeing the NBL POOL\n");
//    MmFreeContiguousMemory(pContiguousMemoryForPackets);
    if (pStartAddressOfMappedPages != NULL && pMdlBufferContiguousMemory != NULL)
    {
        MmUnmapLockedPages(pStartAddressOfMappedPages, pMdlBufferContiguousMemory);
        DbgPrint("INFO: unmapped Mapped pages...\n");
    }
    else
    {
        DbgPrint("INFO: no mapped pages to unmap:/ \n");
    }
    if (pMdlBufferContiguousMemory != NULL)
    {
        IoFreeMdl(pMdlBufferContiguousMemory);
        DbgPrint("INFO: Freed pMdlBufferContiguousMemory\n");
    }
    else
    {
        DbgPrint("INFO: pMdlBufferContiguousMemory is NULL, can't free it\n");
    }
    WdfObjectDelete(contiguousMemoryForPacket);
    DbgPrint("INFO: freeing contiguous memoray\n");
}
VOID
NonPnpEvtDriverContextCleanup(
    IN WDFOBJECT Driver
)
{
    UNREFERENCED_PARAMETER(Driver);
    DbgPrint("INFO: hello from nonpnpndrivercontextcleanup\n");
}
NTSTATUS
NonPnpDeviceAdd(
    IN WDFDRIVER Driver,
    IN PWDFDEVICE_INIT DeviceInit
)
{
    NTSTATUS                       status;
    WDF_OBJECT_ATTRIBUTES           attributes;
    WDFDEVICE   controlDevice;
    WDF_IO_TYPE_CONFIG IoTypeConfig;
    WDF_IO_QUEUE_CONFIG      ioQueueConfig;
    WDFQUEUE                            queue;
    filterDeviceObject = NULL; // is a PDEVICE_OBJECT, will be initialized by casting the WDFDEVICE into it using 
    engineHandle = NULL; // Handle declared above for th WFP engine^^
    DECLARE_CONST_UNICODE_STRING(ntDeviceName, NTDEVICE_NAME_STRING);
    DECLARE_CONST_UNICODE_STRING(symbolicLinkName, SYMBOLIC_NAME_STRING);
    UNREFERENCED_PARAMETER(Driver);
    //   UNREFERENCED_PARAMETER(queue);
    //   UNREFERENCED_PARAMETER(attributes);
    //   UNREFERENCED_PARAMETER(DeviceInit);
    WDF_IO_TYPE_CONFIG_INIT(&IoTypeConfig);
    DbgPrint("INFO: Config size after init = %d\n", IoTypeConfig.Size);
    IoTypeConfig.ReadWriteIoType = WdfDeviceIoBuffered;
    DbgPrint("INFO: Preffered IO Type = %d\n", IoTypeConfig.ReadWriteIoType);
    WdfDeviceInitSetIoTypeEx(DeviceInit, &IoTypeConfig);


    status = WdfDeviceInitAssignName(DeviceInit, &ntDeviceName);
    if (!NT_SUCCESS(status)) {
        DbgPrint("ERROR: failed to assign name with error code 0x%x\n", status);
    }
    else if (NT_SUCCESS(status)) {
        DbgPrint("SUCCESS: successfully assigned name\n");
    }
    WDF_OBJECT_ATTRIBUTES_INIT_CONTEXT_TYPE(&attributes,
        CONTROL_DEVICE_EXTENSION);
    status = WdfDeviceCreate(&DeviceInit,
        &attributes,
        &controlDevice);
    if (!NT_SUCCESS(status)) {
        DbgPrint("ERROR: failed to create a device with error code 0x%x\n", status);
        if (DeviceInit != NULL) {
            WdfDeviceInitFree(DeviceInit);
        }
        return status;
    }
    else if (NT_SUCCESS(status)) {
        DbgPrint("SUCCESS: Created a device\n Device at %p\n", controlDevice);
    }
    DbgPrint("INFO: IRQL level = 0x%X\n", KeGetCurrentIrql());
    filterDeviceObject = WdfDeviceWdmGetDeviceObject(controlDevice);
    if (filterDeviceObject == NULL) {
        DbgPrint("ERROR: failed to extract PDEVICE_OBJECT from WDFDEVICE :/\n");
        if (DeviceInit != NULL) {
            WdfDeviceInitFree(DeviceInit);
        }
    }
    else if (filterDeviceObject != NULL) {
        DbgPrint("SUCCESS: Extracted PDEVICE_OBJECT from WDFDEVICE at 0x%p\n", &filterDeviceObject);
    }
    status = FwpmEngineOpen(NULL, RPC_C_AUTHN_WINNT, NULL, NULL, &engineHandle);
    if (!NT_SUCCESS(status)) {
        DbgPrint("ERROR: Failed to open the filter engine 0x%x\n", status);
        return status;
    }
    else if (NT_SUCCESS(status)) {
        DbgPrint("SUCCESS: engine Handle successfully created at 0x%p with error code 0x%x\n", engineHandle, status);
    }
    DbgPrint("INFO: CALLOUT_GUID_INBOUND=%d at 0x%p\n", CALLOUT_GUID_INBOUND,&CALLOUT_GUID_INBOUND);
    DbgPrint("INFO: CALLOUT_GUID_OUTBOUND=%d at 0x%p\n", CALLOUT_GUID_OUTBOUND,&CALLOUT_GUID_OUTBOUND);
    status = CalloutRegister(CALLOUT_GUID_INBOUND,&registerCalloutIdIn,CalloutFilterIn);
    if (!NT_SUCCESS(status)) {
        DbgPrint("ERROR: Failed to register the filter callout with error code 0x%x\n", status);
    }
    else if (NT_SUCCESS(status)) {
        DbgPrint("SUCCESS: Registered the callout\n");
        DbgPrint("INFO: registerCalloutId at = 0x%p\n", &registerCalloutIdIn);
    }
    status = CalloutRegister(CALLOUT_GUID_OUTBOUND,&registerCalloutIdOut,CalloutFilterOut);
    if (!NT_SUCCESS(status)) {
        DbgPrint("ERROR: Failed to register the filter callout with error code 0x%x\n", status);
    }
    else if (NT_SUCCESS(status)) {
        DbgPrint("SUCCESS: Registered the callout\n");
        DbgPrint("INFO: registerCalloutId at = 0x%p\n", &registerCalloutIdOut);
    }
    status = CalloutAdd(CALLOUT_GUID_INBOUND, FWPM_LAYER_INBOUND_IPPACKET_V4, &addCalloutIdIn);
    if (!NT_SUCCESS(status)) {
        DbgPrint("ERROR: Failed to add the filter callout 0x%X.\n", status);
    }
    else if (NT_SUCCESS(status)) {
        DbgPrint("SUCCESS: added the the filter callout\n");
        DbgPrint("INFO: addCalloutId at = 0x%p\n", &addCalloutIdIn);
    }
    status = CalloutAdd(CALLOUT_GUID_OUTBOUND, FWPM_LAYER_OUTBOUND_IPPACKET_V4, &addCalloutIdOut);
    if (!NT_SUCCESS(status)) {
        DbgPrint("ERROR: Failed to add the filter callout 0x%X.\n", status);
    }
    else if (NT_SUCCESS(status)) {
        DbgPrint("SUCCESS: added the the filter callout\n");
        DbgPrint("INFO: addCalloutId at = 0x%p\n", &addCalloutIdOut);
    }
    status = SublayerAdd();
    if (!NT_SUCCESS(status)) {
        DbgPrint("ERROR: Failed to add the sublayer  0x%X.\n", status);
    }
    else if (NT_SUCCESS(status)) {
        DbgPrint("SUCCESS: added the the sublayer \n");
    }
    status = FilterAdd(CALLOUT_GUID_INBOUND, FWPM_LAYER_INBOUND_IPPACKET_V4, &filterIdIn);
    if (!NT_SUCCESS(status)) {
        DbgPrint("ERROR: Failed to add the filter with error code  0x%X.\n", status);
    }
    else if (NT_SUCCESS(status)) {
        DbgPrint("SUCCESS: added the the filter! \n");
    }
    status = FilterAdd(CALLOUT_GUID_OUTBOUND, FWPM_LAYER_OUTBOUND_IPPACKET_V4, &filterIdOut);
    if (!NT_SUCCESS(status)) {
        DbgPrint("ERROR: Failed to add the filter with error code  0x%X.\n", status);
    }
    else if (NT_SUCCESS(status)) {
        DbgPrint("SUCCESS: added the the filter! \n");
    }
    DbgPrint("INFO: inside NonPnpDeviceAdd registerCalloutIdIn = %u, addCalloutIdIn = %u, filterIdIn = %u\n", *&registerCalloutIdIn, *&addCalloutIdIn, *&filterIdIn);
    DbgPrint("INFO: inside NonPnpDeviceAdd registerCalloutIdOut = %u, addCalloutIdOut = %u, filterIdOut = %u\n", *&registerCalloutIdOut, *&addCalloutIdOut, *&filterIdOut);
    status = WdfDeviceCreateSymbolicLink(controlDevice,
        &symbolicLinkName);
    if (!NT_SUCCESS(status)) {
        DbgPrint("ERROR: failed to create da symbolic link with error code 0x%x\n", status);
        if (DeviceInit != NULL) {
            WdfDeviceInitFree(DeviceInit);
        }
    }
    else if (NT_SUCCESS(status)) {
        DbgPrint("SUCCESS: Created da symbolic link with status 0x%x\n Symbolic link size = %d\n device name size = %d\n symbolic link = %wZ\n", status, sizeof(symbolicLinkName), sizeof(ntDeviceName), symbolicLinkName);
    }
    DbgPrint("INFO: IRQL level = 0x%X\n", KeGetCurrentIrql());

    //ensures that the calling thread is running at an IRQL that is low enough to permit paging.
    PAGED_CODE();

    DbgPrint("INFO: IRQL level = 0x%X\n", KeGetCurrentIrql());
    WDF_IO_QUEUE_CONFIG_INIT_DEFAULT_QUEUE(&ioQueueConfig,
        WdfIoQueueDispatchSequential);
    /*   ioQueueConfig.EvtIoRead = NULL;
       ioQueueConfig.EvtIoWrite = NULL;
       ioQueueConfig.EvtIoDeviceControl = NULL;
       */
    ioQueueConfig.EvtIoDeviceControl = FileEvtIoDeviceControl;
    ioQueueConfig.EvtIoDefault = FileEvtIoDefault;
    WDF_OBJECT_ATTRIBUTES_INIT(&attributes);
    status = WdfIoQueueCreate(controlDevice,
        &ioQueueConfig,
        &attributes,
        &queue
    );

    __analysis_assume(ioQueueConfig.EvtIoStop == 0);
    if (!NT_SUCCESS(status)) {
        DbgPrint("ERROR: failed to create IO queue with error code 0x%x\n", status);
        if (DeviceInit != NULL) {
            WdfDeviceInitFree(DeviceInit);
        }
    }
    else if (NT_SUCCESS(status)) {
        DbgPrint("SUCCESS: Created IO queue with nt_status 0x%x\n", status);
    }
    WDF_IO_QUEUE_CONFIG_INIT(&ioQueueConfig,
        WdfIoQueueDispatchManual);

    // FOLLOWING parameters are ONLY for non manually dispatched queues,
    // I switched back to manual dispatching because on sequential dispatch, the driver automatically retrieves the first input request wether or not an IO control callback is implemented (default call back is required)
    // so the first IO reequest will be retrieved by the default callback and won't be completed which is BAD because one of the described memory segment will therefore be out of the available pool for ever :/ that's why I switched back to manual dispatching
    // originally I believed sequential dispatch might be the only one whose lock wwas managed by the framework,
    // SOURCE : https://community.osr.com/t/are-wdfqueues-thread-safe/45789
    // 
    // 
    // 
//    ioQueueConfig.EvtIoDeviceControl = FileEvtIoDeviceControl2;
//    ioQueueConfig.EvtIoDefault = FileEvtIoDefault;

    //WDF_NO_OBJECT_ATTRIBUTES returns an error... and causes subsequent fatal crash ^^
    //&attributes doesn't change shi, the problem is that  WDF_WORKITEM_CONFIG workitemConfig;
    //The doc explains this. STATUS_WDF_INCOMPATIBLE_EXECUTION_LEVEL means
    //that AutomaticSerialization in your WDF_WORKITEM_CONFIG is set to TRUE
    //    but the parent object’s execution level is not set to passive.
    //   WDF_WORKITEM_CONFIG_INIT, by default, sets AutomaticSerialzation to TRUE.
    //(https://community.osr.com/t/wdfworkitemcreate-error-status-wdf-incompatible-execution-level/27441/4)

    //completely unrelated^^ : https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/wdfio/nf-wdfio-wdfioqueuecreate
    // says that it's because of the quueue config (STATUS_WDF_NO_CALLBACK = 0xC020020BL https://github.com/Microsoft/Windows-Driver-Frameworks/blob/main/src/publicinc/wdf/kmdf/1.17/wdfstatus.h)


    status = WdfIoQueueCreate(controlDevice, &ioQueueConfig, WDF_NO_OBJECT_ATTRIBUTES, &queueIoInverted);
    if (!NT_SUCCESS(status)) {
        DbgPrint("ERROR: failed to create inverted IO queue with error code 0x%x\n", status);
        if (DeviceInit != NULL) {
            WdfDeviceInitFree(DeviceInit);
        }
    }
    else if (NT_SUCCESS(status)) {
        DbgPrint("SUCCESS: Created inverted IO queue with nt_status 0x%x\n", status);
        DbgPrint("SUCCESS: Created inverted IO queue at 0x%p\n", &queueIoInverted);
    }
    status = WdfIoQueueCreate(controlDevice, &ioQueueConfig, WDF_NO_OBJECT_ATTRIBUTES, &queueIoInverted_2);
    if (!NT_SUCCESS(status)) {
        DbgPrint("ERROR: failed to create inverted IO queue with error code 0x%x\n", status);
        if (DeviceInit != NULL) {
            WdfDeviceInitFree(DeviceInit);
        }
    }
    status = WdfIoQueueCreate(controlDevice, &ioQueueConfig, WDF_NO_OBJECT_ATTRIBUTES, &queueIoInverted_3);
    if (!NT_SUCCESS(status)) {
        DbgPrint("ERROR: failed to create inverted IO queue with error code 0x%x\n", status);
        if (DeviceInit != NULL) {
            WdfDeviceInitFree(DeviceInit);
        }
    }
    status = WdfIoQueueCreate(controlDevice, &ioQueueConfig, WDF_NO_OBJECT_ATTRIBUTES, &queueIoInverted_4);
    if (!NT_SUCCESS(status)) {
        DbgPrint("ERROR: failed to create inverted IO queue with error code 0x%x\n", status);
        if (DeviceInit != NULL) {
            WdfDeviceInitFree(DeviceInit);
        }
    }
    status = WdfIoQueueCreate(controlDevice, &ioQueueConfig, WDF_NO_OBJECT_ATTRIBUTES, &queueIoInverted_5);
    if (!NT_SUCCESS(status)) {
        DbgPrint("ERROR: failed to create inverted IO queue with error code 0x%x\n", status);
        if (DeviceInit != NULL) {
            WdfDeviceInitFree(DeviceInit);
        }
    }
    status = WdfIoQueueCreate(controlDevice, &ioQueueConfig, WDF_NO_OBJECT_ATTRIBUTES, &queueIoInverted_6);
    if (!NT_SUCCESS(status)) {
        DbgPrint("ERROR: failed to create inverted IO queue with error code 0x%x\n", status);
        if (DeviceInit != NULL) {
            WdfDeviceInitFree(DeviceInit);
        }
    }
    status = WdfIoQueueCreate(controlDevice, &ioQueueConfig, WDF_NO_OBJECT_ATTRIBUTES, &queueIoInverted_7);
    if (!NT_SUCCESS(status)) {
        DbgPrint("ERROR: failed to create inverted IO queue with error code 0x%x\n", status);
        if (DeviceInit != NULL) {
            WdfDeviceInitFree(DeviceInit);
        }
    }
    status = WdfIoQueueCreate(controlDevice, &ioQueueConfig, WDF_NO_OBJECT_ATTRIBUTES, &queueIoInverted_8);
    if (!NT_SUCCESS(status)) {
        DbgPrint("ERROR: failed to create inverted IO queue with error code 0x%x\n", status);
        if (DeviceInit != NULL) {
            WdfDeviceInitFree(DeviceInit);
        }
    }
    status = WdfIoQueueCreate(controlDevice, &ioQueueConfig, WDF_NO_OBJECT_ATTRIBUTES, &queueIoInverted_9);
    if (!NT_SUCCESS(status)) {
        DbgPrint("ERROR: failed to create inverted IO queue with error code 0x%x\n", status);
        if (DeviceInit != NULL) {
            WdfDeviceInitFree(DeviceInit);
        }
    }
    status = WdfIoQueueCreate(controlDevice, &ioQueueConfig, WDF_NO_OBJECT_ATTRIBUTES, &queueIoInverted_10);
    if (!NT_SUCCESS(status)) {
        DbgPrint("ERROR: failed to create inverted IO queue with error code 0x%x\n", status);
        if (DeviceInit != NULL) {
            WdfDeviceInitFree(DeviceInit);
        }
    }
    WDF_IO_QUEUE_CONFIG_INIT(&ioQueueConfig,
        WdfIoQueueDispatchManual);
    status = WdfIoQueueCreate(controlDevice, &ioQueueConfig, WDF_NO_OBJECT_ATTRIBUTES, &queueIoPurgeEvent);
    if (!NT_SUCCESS(status)) {
        DbgPrint("ERROR: failed to create inverted IO queue with error code 0x%x\n", status);
        if (DeviceInit != NULL) {
            WdfDeviceInitFree(DeviceInit);
        }
    }
    else if (NT_SUCCESS(status)) {
        DbgPrint("SUCCESS: Created all 10 inverted IO queue with nt_status 0x%x\n", status);
        DbgPrint("SUCCESS: Created last inverted IO queue at 0x%p\n", &queueIoInverted_10);
/*        rxInvertedIoQueue = {
            queueIoInverted,queueIoInverted_2,queueIoInverted_3,queueIoInverted_4,queueIoInverted_5,queueIoInverted_6,queueIoInverted_7,queueIoInverted_8,queueIoInverted_9,queueIoInverted_10
        };
*/
        rxInvertedIoQueue.INVERTED_QUEUE = queueIoInverted;
        rxInvertedIoQueue.INVERTED_QUEUE_2 = queueIoInverted_2;
        rxInvertedIoQueue.INVERTED_QUEUE_3 = queueIoInverted_3;
        rxInvertedIoQueue.INVERTED_QUEUE_4 = queueIoInverted_4;
        rxInvertedIoQueue.INVERTED_QUEUE_5 = queueIoInverted_5;
        rxInvertedIoQueue.INVERTED_QUEUE_6 = queueIoInverted_6;
        rxInvertedIoQueue.INVERTED_QUEUE_7 = queueIoInverted_7;
        rxInvertedIoQueue.INVERTED_QUEUE_8 = queueIoInverted_8;
        rxInvertedIoQueue.INVERTED_QUEUE_9 = queueIoInverted_9;
        rxInvertedIoQueue.INVERTED_QUEUE_10 = queueIoInverted_10;
//        UNREFERENCED_PARAMETER(rxInvertedIoQueue);

    }
    WdfControlFinishInitializing(controlDevice);


    return status;
}
VOID FileEvtIoDefault(
    IN WDFQUEUE         Queue,
    IN WDFREQUEST       Request
)
{
    NTSTATUS status = STATUS_SUCCESS;
    UNREFERENCED_PARAMETER(Queue);
    UNREFERENCED_PARAMETER(Request);
    DbgPrint("INFO: Hello from FileEvtIoDefault ntstatus = 0x%X", status);
}
VOID
FileEvtIoDeviceControl(
    IN WDFQUEUE         Queue,
    IN WDFREQUEST       Request,
    IN size_t            OutputBufferLength,
    IN size_t            InputBufferLength,
    IN ULONG            IoControlCode
)
{
    NTSTATUS            status = STATUS_SUCCESS;// Assume success
    /*    PCHAR               inBuf = NULL, outBuf = NULL; // pointer to Input and output buffer
        PCHAR               data = "this String is from Device Driver !!!";
        ULONG               datalen = (ULONG)strlen(data) + 1;//Length of data including null
        PCHAR               buffer = NULL;
        PREQUEST_CONTEXT    reqContext = NULL;
        size_t               bufSize;
        */
    WDFREQUEST notifyRequest;
    ULONG numberOfElementsInInvertedQueue = 0;
    //assuming i'm in a 64 bit environment ULONG should be enough to store an address
    ULONGLONG* ioOutputBuffer;
    UNREFERENCED_PARAMETER(Queue);
    PAGED_CODE();
    if (!OutputBufferLength || !InputBufferLength)
    {
        WdfRequestComplete(Request, STATUS_INVALID_PARAMETER);
        return;
    }
    switch (IoControlCode)
    {
    case IOCTL_TEST:
    {
        status = STATUS_SUCCESS;
        DbgPrint("INFO: SUCCESS: recieved IO CONTROL CODE IOCTL_TEST from USERLAND\n");
        break;
    }
    case IOCTL_GET_KERNEL_BUFFER_ADDRESS:
    {
        status = STATUS_SUCCESS;
        pMdlBufferContiguousMemory = IoAllocateMdl(pBufferContiguousMemory, lengthBufferContiguousMemory, FALSE, FALSE, NULL);
        if (pMdlBufferContiguousMemory == NULL)
        {
            DbgPrint("ERROR: failed to allocate an MDL for the buffer\n");
        }
        else if (pMdlBufferContiguousMemory != NULL)
        {
            DbgPrint("SUCCESS: allocated MDL for memory buffer 0x%p\n", pMdlBufferContiguousMemory);
        }
        MmBuildMdlForNonPagedPool(pMdlBufferContiguousMemory);
        DbgPrint("INFO: Address of mapped pages before MmMapLockedPagesSpecifyCache = %p\n", pStartAddressOfMappedPages);
        pStartAddressOfMappedPages = MmMapLockedPagesSpecifyCache(pMdlBufferContiguousMemory, UserMode, MmWriteCombined, NULL, FALSE, HighPagePriority);
        if (pStartAddressOfMappedPages == NULL)
        {
            DbgPrint("ERROR: failed to map pages for user mode\n");
        }
        else if (pStartAddressOfMappedPages != NULL)
        {
            DbgPrint("SUCCESS: mapped pages for user mode 0x%p\n", pStartAddressOfMappedPages);
            DbgPrint("INFO: value of the address = 0x%llX\n", *pAddressValueStartAddressOfMappedPages);

        }

//        status = WdfRequestRetrieveInputBuffer(Request, 0, (PVOID*)&ioInputBuffer, NULL);
        status = WdfRequestRetrieveOutputBuffer(Request, 0, (PVOID*)&ioOutputBuffer, NULL);
        // get mdl address to check if it's the same
        UCHAR* pBufferFromIoControl = NULL;
        //UCHAR* pBufferFromMappedPages = (UCHAR*)pStartAddressOfMappedPages;
        pBufferFromIoControl = MmGetSystemAddressForMdlSafe(pMdlBufferContiguousMemory, HighPagePriority);
        //DbgPrint("pBufferFromIoControl = %p with value = %X or %X\n", pBufferFromIoControl, pBufferFromIoControl[0], pBufferFromMappedPages[0]);
        //ioOutputBuffer[0] = (ULONGLONG)*pAddressValueStartAddressOfMappedPages;
        ioOutputBuffer[0] = (ULONGLONG)pStartAddressOfMappedPages;
        DbgPrint("INFO: received IOCTL_GET_KERNEL_BUFFER_ADDRESS , completing the request with ioOutputBuffer = 0x%llX, sizeof output buffer = %d\n", ioOutputBuffer, sizeof(ioOutputBuffer));
        WdfRequestCompleteWithInformation(Request, status, 2 * sizeof(ULONG));
        return;
    }
    case IOCTL_TEST_INVERTED:
    {
        status = STATUS_SUCCESS;
        DbgPrint("INFO: SUCCESS: received IO CONTROL CODE IOCTL_TEST_INVERTED, will push to the inverted IO Queue\n");
        if (OutputBufferLength < sizeof(LONG)) {

            //
            // Not enough space? Complete the request with
            // STATUS_INVALID_PARAMETER (as set previously).
            // 
            DbgPrint("INFO: not enough space\n");
            break;
        }
        DbgPrint("INFO: IO queue at 0x%p\n", &queueIoInverted);
        DbgPrint("INFO: Request = 0x%X\n", Request);
        status = WdfRequestForwardToIoQueue(Request, queueIoInverted);
        DbgPrint("INFO: Forwarded with status 0x%X\n",status);
//        DbgPrint("size of queue = %d\n", sizeof(queueIoInverted));
        return;
    }
    case IOCTL_TEST_INVERTED_2:
    {
        status = STATUS_SUCCESS;
        DbgPrint("INFO: SUCCESS: received IO CONTROL CODE IOCTL_TEST_INVERTED_2, will push to the inverted IO Queue\n");
        if (OutputBufferLength < sizeof(LONG)) {

            //
            // Not enough space? Complete the request with
            // STATUS_INVALID_PARAMETER (as set previously).
            // 
            DbgPrint("INFO: not enough space\n");
            break;
        }
        DbgPrint("INFO: IO queue at 0x%p\n", &queueIoInverted_2);
        DbgPrint("INFO: Request = 0x%X\n", Request);
        status = WdfRequestForwardToIoQueue(Request, queueIoInverted_2);
        DbgPrint("INFO: Forwarded with status 0x%X\n", status);
        //        DbgPrint("size of queue = %d\n", sizeof(queueIoInverted));
        return;
    }
    case IOCTL_TEST_INVERTED_3:
    {
        status = STATUS_SUCCESS;
        DbgPrint("INFO: SUCCESS: received IO CONTROL CODE IOCTL_TEST_INVERTED_3, will push to the inverted IO Queue\n");
        if (OutputBufferLength < sizeof(LONG)) {

            //
            // Not enough space? Complete the request with
            // STATUS_INVALID_PARAMETER (as set previously).
            // 
            DbgPrint("INFO: not enough space\n");
            break;
        }
        DbgPrint("INFO: IO queue at 0x%p\n", &queueIoInverted_3);
        DbgPrint("INFO: Request = 0x%X\n", Request);
        status = WdfRequestForwardToIoQueue(Request, queueIoInverted_3);
        DbgPrint("INFO: Forwarded with status 0x%X\n", status);
        //        DbgPrint("size of queue = %d\n", sizeof(queueIoInverted));
        return;
    }
    case IOCTL_TEST_INVERTED_4:
    {
        status = STATUS_SUCCESS;
        DbgPrint("INFO: SUCCESS: received IO CONTROL CODE IOCTL_TEST_INVERTED_4, will push to the inverted IO Queue\n");
        if (OutputBufferLength < sizeof(LONG)) {

            //
            // Not enough space? Complete the request with
            // STATUS_INVALID_PARAMETER (as set previously).
            // 
            DbgPrint("INFO: not enough space\n");
            break;
        }
        DbgPrint("INFO: IO queue at 0x%p\n", &queueIoInverted_4);
        DbgPrint("INFO: Request = 0x%X\n", Request);
        status = WdfRequestForwardToIoQueue(Request, queueIoInverted_4);
        DbgPrint("INFO: Forwarded with status 0x%X\n", status);
        //        DbgPrint("size of queue = %d\n", sizeof(queueIoInverted));
        return;
    }
    case IOCTL_TEST_INVERTED_5:
    {
        status = STATUS_SUCCESS;
        DbgPrint("INFO: SUCCESS: received IO CONTROL CODE IOCTL_TEST_INVERTED_5, will push to the inverted IO Queue\n");
        if (OutputBufferLength < sizeof(LONG)) {

            //
            // Not enough space? Complete the request with
            // STATUS_INVALID_PARAMETER (as set previously).
            // 
            DbgPrint("INFO: not enough space\n");
            break;
        }
        DbgPrint("INFO: IO queue at 0x%p\n", &queueIoInverted_5);
        DbgPrint("INFO: Request = 0x%X\n", Request);
        status = WdfRequestForwardToIoQueue(Request, queueIoInverted_5);
        DbgPrint("INFO: Forwarded with status 0x%X\n", status);
        //        DbgPrint("size of queue = %d\n", sizeof(queueIoInverted));
        return;
    }
    case IOCTL_TEST_INVERTED_6:
    {
        status = STATUS_SUCCESS;
        DbgPrint("INFO: SUCCESS: received IO CONTROL CODE IOCTL_TEST_INVERTED_6, will push to the inverted IO Queue\n");
        if (OutputBufferLength < sizeof(LONG)) {

            //
            // Not enough space? Complete the request with
            // STATUS_INVALID_PARAMETER (as set previously).
            // 
            DbgPrint("INFO: not enough space\n");
            break;
        }
        DbgPrint("INFO: IO queue at 0x%p\n", &queueIoInverted_6);
        DbgPrint("INFO: Request = 0x%X\n", Request);
        status = WdfRequestForwardToIoQueue(Request, queueIoInverted_6);
        DbgPrint("INFO: Forwarded with status 0x%X\n", status);
        //        DbgPrint("size of queue = %d\n", sizeof(queueIoInverted));
        return;
    }
    case IOCTL_TEST_INVERTED_7:
    {
        status = STATUS_SUCCESS;
        DbgPrint("INFO: SUCCESS: received IO CONTROL CODE IOCTL_TEST_INVERTED_7, will push to the inverted IO Queue\n");
        if (OutputBufferLength < sizeof(LONG)) {

            //
            // Not enough space? Complete the request with
            // STATUS_INVALID_PARAMETER (as set previously).
            // 
            DbgPrint("INFO: not enough space\n");
            break;
        }
        DbgPrint("INFO: IO queue at 0x%p\n", &queueIoInverted_7);
        DbgPrint("INFO: Request = 0x%X\n", Request);
        status = WdfRequestForwardToIoQueue(Request, queueIoInverted_7);
        DbgPrint("INFO: Forwarded with status 0x%X\n", status);
        //        DbgPrint("size of queue = %d\n", sizeof(queueIoInverted));
        return;
    }
    case IOCTL_TEST_INVERTED_8:
    {
        status = STATUS_SUCCESS;
        DbgPrint("INFO: SUCCESS: received IO CONTROL CODE IOCTL_TEST_INVERTED_8, will push to the inverted IO Queue\n");
        if (OutputBufferLength < sizeof(LONG)) {

            //
            // Not enough space? Complete the request with
            // STATUS_INVALID_PARAMETER (as set previously).
            // 
            DbgPrint("INFO: not enough space\n");
            break;
        }
        DbgPrint("INFO: IO queue at 0x%p\n", &queueIoInverted_8);
        DbgPrint("INFO: Request = 0x%X\n", Request);
        status = WdfRequestForwardToIoQueue(Request, queueIoInverted_8);
        DbgPrint("INFO: Forwarded with status 0x%X\n", status);
        //        DbgPrint("size of queue = %d\n", sizeof(queueIoInverted));
        return;
    }
    case IOCTL_TEST_INVERTED_9:
    {
        status = STATUS_SUCCESS;
        DbgPrint("INFO: SUCCESS: received IO CONTROL CODE IOCTL_TEST_INVERTED_9, will push to the inverted IO Queue\n");
        if (OutputBufferLength < sizeof(LONG)) {

            //
            // Not enough space? Complete the request with
            // STATUS_INVALID_PARAMETER (as set previously).
            // 
            DbgPrint("INFO: not enough space\n");
            break;
        }
        DbgPrint("INFO: IO queue at 0x%p\n", &queueIoInverted_9);
        DbgPrint("INFO: Request = 0x%X\n", Request);
        status = WdfRequestForwardToIoQueue(Request, queueIoInverted_9);
        DbgPrint("INFO: Forwarded with status 0x%X\n", status);
        //        DbgPrint("size of queue = %d\n", sizeof(queueIoInverted));
        return;
    }
    case IOCTL_TEST_INVERTED_10:
    {
        status = STATUS_SUCCESS;
        DbgPrint("INFO: SUCCESS: received IO CONTROL CODE IOCTL_TEST_INVERTED_10, will push to the inverted IO Queue\n");
        if (OutputBufferLength < sizeof(LONG)) {

            //
            // Not enough space? Complete the request with
            // STATUS_INVALID_PARAMETER (as set previously).
            // 
            DbgPrint("INFO: not enough space\n");
            break;
        }
        DbgPrint("INFO: IO queue at 0x%p\n", &queueIoInverted_10);
        DbgPrint("INFO: Request = 0x%X\n", Request);
        status = WdfRequestForwardToIoQueue(Request, queueIoInverted_10);
        DbgPrint("INFO: Forwarded with status 0x%X\n", status);
        //        DbgPrint("size of queue = %d\n", sizeof(queueIoInverted));
        return;
    }
    case IOCTL_INVERT_SIMULATE_EVENT_OCCURRED:
    {
        DbgPrint("INFO: received event simulation IOCTL\n");
        WdfIoQueueGetState(queueIoInverted, &numberOfElementsInInvertedQueue, NULL);
        DbgPrint("INFO: is queue empty? numberOfElementsInInvertedQueue = %lu\n", numberOfElementsInInvertedQueue);
        if (numberOfElementsInInvertedQueue > 0)
        {
            status = WdfIoQueueRetrieveNextRequest(queueIoInverted,
                &notifyRequest);
            WdfRequestComplete(notifyRequest, status);
            DbgPrint("INFO : queue is not empty\n");
        }
        else if (numberOfElementsInInvertedQueue == 0)
        {
            DbgPrint("ERROR : queue is empty mate\n");
        }
        DbgPrint("INFO: retrieve status = 0x%X\n", status);
        break;
    }
    case IOCTL_PURGE_ALL_NON_DEFAULT_QUEUES:
    {
        DbgPrint("INFO: received purging event\n");
        status = WdfRequestForwardToIoQueue(Request, queueIoPurgeEvent);
        DbgPrint("INFO: Forwarded with status 0x%X\n", status);
        #define X(type,name) \
            DbgPrint("INFO: current queue name = %s\n", #name);\
            WdfIoQueuePurge(rxInvertedIoQueue.name,NULL,NULL);
        INVERTED_QUEUE_LIST
        #undef X
        DbgPrint("INFO: purged all the queues\n");
        DbgPrintEx(DPFLTR_IHVNETWORK_ID, 0xFFFFFFFF, "INFO: purged all the queues\n");
        return;
    }
    default:
    {
        status = STATUS_INVALID_DEVICE_REQUEST;
        DbgPrint("INFO: ERROR: recieved an invalid IOCTL_CODE from USERLAND :(\n");
    }
    }
    WdfRequestComplete(Request, status);
    return;
}
// Unreviewed coode from the same tutorial
NTSTATUS CalloutRegister(GUID CALLOUT_GUID, UINT32 *registerCalloutId, FWPS_CALLOUT_CLASSIFY_FN3 CalloutFilter) {
    NTSTATUS status;
    DbgPrint("registerCalloutId = %u at 0x%p\n", *registerCalloutId, registerCalloutId);
    *registerCalloutId = 0;
    DbgPrint("INFO: GUID = %d at 0x%p\n", CALLOUT_GUID, &CALLOUT_GUID);

    FWPS_CALLOUT callout = {
      .calloutKey = CALLOUT_GUID,    // Unique GUID that identifies the callout (previously defined)
      .flags = 0,               // None
      .classifyFn = CalloutFilter,   // Callout function used to process network data (our ICMP packets)
      .notifyFn = CalloutNotify,   // Callout function used to receive notifications from the filter engine (MUST be defined) 
      .flowDeleteFn = NULL             // Callout function used to process terminated data (does't need to be defined)
    };

    status = FwpsCalloutRegister(filterDeviceObject, &callout, registerCalloutId);

    DbgPrint("*registerCalloutId = %u, registerCalloutIdIn = %u , registerCalloutIdOut = %u\n", *registerCalloutId, registerCalloutIdIn, registerCalloutIdOut);
    return status;
}
VOID CalloutFilterIn(
    const FWPS_INCOMING_VALUES* inFixedValues,
    const FWPS_INCOMING_METADATA_VALUES* inMetaValues,
    void* layerData,
    const void* classifyContext,
    const FWPS_FILTER* filter,
    UINT64 flowContext,
    FWPS_CLASSIFY_OUT* classifyOut
) {
    NTSTATUS status;
//    WDFREQUEST notifyRequest;
    ULONG numberOfElementsInInvertedQueue = 0;
    ULONG numberOfElementsInCurrentInvertedQueue = 0;
    ULONG numberOfElementsInQueuePurgeEvent = 0;
    /*
    ULONG numberOfElementsInInvertedQueue_2 = 0;
    ULONG numberOfElementsInInvertedQueue_3 = 0;
    ULONG numberOfElementsInInvertedQueue_4 = 0;
    ULONG numberOfElementsInInvertedQueue_5 = 0;
    ULONG numberOfElementsInInvertedQueue_6 = 0;
    ULONG numberOfElementsInInvertedQueue_7 = 0;
    ULONG numberOfElementsInInvertedQueue_8 = 0;
    ULONG numberOfElementsInInvertedQueue_9 = 0;
    ULONG numberOfElementsInInvertedQueue_10 = 0;
    */
    UNREFERENCED_PARAMETER(inFixedValues);
    UNREFERENCED_PARAMETER(inMetaValues);
//    UNREFERENCED_PARAMETER(layerData);
    UNREFERENCED_PARAMETER(classifyContext);
    UNREFERENCED_PARAMETER(filter);
    UNREFERENCED_PARAMETER(flowContext);
    UNREFERENCED_PARAMETER(classifyOut);
    WDFREQUEST requestPurge = NULL;
    WDFQUEUE *currentQueue = NULL;
//    BYTE ioInputBuffer[128] = { 0 };
    ULONG* ioInputBuffer;
    ULONG* ioOutputBuffer;
//    UNREFERENCED_PARAMETER(ioInputBuffer);
//    UNREFERENCED_PARAMETER(ioOutputBuffer);
    char bEnoughMemory = -1;
//    CHAR queueName[15] = {0};
//    VOID* pIoInputBuffer = &ioInputBuffer;
// checking if layerData points to actual memory i.e there is indeed a packet
    if (!layerData) {
        DbgPrint("INFO: No layerData, layerData doesn't point to valid memory\n");
        return;
    }
//CHECK IS TEMPORARY FOR TESTING PURPOSE
// checking if recieved packet is ICMP
    /*
    if (inFixedValues->incomingValue[FWPS_FIELD_DATAGRAM_DATA_V4_IP_PROTOCOL].value.uint8 != IPPROTO_ICMP) {
        DbgPrint("INFO: Recieved Non ICMP packet\n");
        return;
    }

//checking if recieved packet is malformed
    if (inMetaValues->ipHeaderSize <= 0) {
        DbgPrint("INFO: Recieved malformed ICMP packet\n");
        return;
    }
*/
    // Packet parsing logic goes here...
    DbgPrint("INFO: Recieved a well formed ICMP packet\n");
    NET_BUFFER_LIST* fragmentList = (NET_BUFFER_LIST*)layerData;
    NET_BUFFER_LIST* cloneNBL = NULL;

    // Note: the linked list should ONLY be accessed through macros such as 'NET_BUFFER_LIST_FIRST_NB()' (https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/nbl/ns-nbl-net_buffer_list)
    NET_BUFFER* firstFragment = NET_BUFFER_LIST_FIRST_NB(fragmentList);
    NET_BUFFER* cloneNB = NULL;
    ULONG  icmpLength = firstFragment->DataLength;  // Size of the ICMP packet
//    UINT32 dataLength = icmpLength - 8;             // ICMP data size    = ICMP packet size - ICMP header size    
//    UINT32 payloadLength = dataLength - 4 - 1;         // ICMP payload size = ICMP packet size - ICMP header size /- 4 (password size) - 1 (reserved flag size) 



    // TEST ALLOCATION PER PACKET, CAUSES LAG, TRYING WITHOUT 

    /*
    PVOID icmpBuffer = ExAllocatePoolWithTag(POOL_FLAG_NON_PAGED, (SIZE_T)icmpLength, ALLOC_TAG_NAME); // Tag name is defined in "Config.h"
    if (!icmpBuffer) {
        return;
    }
    PBYTE icmpPacket = (PBYTE)NdisGetDataBuffer(firstFragment, (ULONG)icmpLength, icmpBuffer, 1, 0);
    if (!icmpPacket) {
        ExFreePoolWithTag((PVOID)icmpBuffer, ALLOC_TAG_NAME);
        return;
    }
    */
    DbgPrint("INFO: packet length = %lu\n", icmpLength);
    DbgPrint("INFO: Packet recieved = \n");
    /*
    for (int i = -34; i < (int)icmpLength; i++) {
        DbgPrint("%X ", icmpPacket[i]);
    }
    */
    //DbgPrint("INFO: Packet recieved = %X\n", icmpPacket);
    MDL* currentMDL = NET_BUFFER_CURRENT_MDL(firstFragment);
    MDL* firstMDL = NET_BUFFER_FIRST_MDL(firstFragment);
//    DbgPrint("firstMDL at 0x%p current MDL at 0x%p\n", firstMDL, currentMDL);
    VOID* pBuffer = MmGetSystemAddressForMdlSafe(firstMDL, HighPagePriority);
    ULONG bufferLength = MmGetMdlByteCount(firstMDL);
    ULONG byteOffset = MmGetMdlByteOffset(firstMDL);
    BYTE *valueMDL = ((BYTE*)pBuffer);
    BYTE* valueMDLOffset = valueMDL + (BYTE)byteOffset;
    UNREFERENCED_PARAMETER(bufferLength);
    UNREFERENCED_PARAMETER(currentMDL);
    UNREFERENCED_PARAMETER(valueMDLOffset);
//    MDL* secondMDL = firstMDL->Next;
//    DbgPrint("INFO: firstMDL->MdlFlags = %hu\n", firstMDL->MdlFlags);
//    DbgPrint("INFO: firstMDL length = %lu\n firstMDL buffer offset = %lu\n so firstMDL buffer should be 0x%p\n icmpPacket is at 0x%p\n firstMDL.MappedSystemVa=0x%p\n or valueMDL = 0x%p\n or *valueMDL = 0x%X\n or valueMDLOffset = 0x%p\n or *valueMDLOffset=0x%X\n", bufferLength, byteOffset, pBuffer, icmpPacket, firstMDL->MappedSystemVa, valueMDL, *valueMDL, valueMDLOffset,*valueMDLOffset );
/*
    for (int i = 0; i < (int)bufferLength; i++) {
        DbgPrint("%X ", valueMDL[i] );
    }
*/
    // the + 34 represents the size of the L2 layer that is being truncated when processed by the calling driver
    
    /*
    for (int i = 0; i < ((int)icmpLength + 34); i++) {
        DbgPrint("%X ", valueMDL[i]);
    }
    */
    DbgPrint("\n");
    
    status = WdfMemoryCopyFromBuffer(contiguousMemoryForPacket, 10, valueMDL, ((int)icmpLength + 34));
    if (!NT_SUCCESS(status))
    {
        DbgPrint("ERROR: Failed to copy the packet to the buffer mate\n");
    }
    else if (NT_SUCCESS(status))
    {
        DbgPrint("SUCCESS: Copied packet to the buffer\n");
    }
    DbgPrint("\n");
    /*
    #define X(type,name) \
        DbgPrint("INFO: current queue name = %s\n", #name);\
        WdfIoQueueGetState(rxInvertedIoQueue.name, &numberOfElementsInCurrentInvertedQueue, NULL);\
        if (numberOfElementsInCurrentInvertedQueue > 0 &&  numberOfElementsInInvertedQueue==0){numberOfElementsInInvertedQueue = numberOfElementsInCurrentInvertedQueue; currentQueue = &rxInvertedIoQueue.name;DbgPrint("INFO: Selected queue = %s",#name);DbgPrintEx(DPFLTR_IHVNETWORK_ID, 0xFFFFFFFF,"INFO: current queue name = %s, currentQueue address = %p source queue address = %p\n", #name, currentQueue, &rxInvertedIoQueue.name);}\
        DbgPrint("INFO: queue size = %lu\n", numberOfElementsInCurrentInvertedQueue);
        INVERTED_QUEUE_LIST
    #undef X
    DbgPrint("INFO: Exited da loop, numberOfElementsInInvertedQueue = %lu\n", numberOfElementsInInvertedQueue);

    */
//    DbgPrintEx(DPFLTR_IHVNETWORK_ID, 0xFFFFFFFF, "INFO: numberOfElementsInInvertedQueue = %lu\n", numberOfElementsInInvertedQueue);
//    DbgPrintEx(DPFLTR_IHVNETWORK_ID, 0xFFFFFFFF, "INFO: OUT OF LOOP: current queue address  = %p\n", currentQueue);
    
    if (currentQueue != NULL)
    {
        WdfIoQueueGetState(*currentQueue, &numberOfElementsInInvertedQueue, NULL);
    }
    
    DbgPrint("INFO: IN FILTER : is queue empty? numberOfElementsInInvertedQueue = %lu\n", numberOfElementsInInvertedQueue);
    if (remainingMemory >= ((int)icmpLength + 34))
    {
        bEnoughMemory = -2;
    }
    
//    switch (currentInRequest)
//    {
    WdfIoQueueGetState(queueIoPurgeEvent, &numberOfElementsInQueuePurgeEvent,NULL);
    if (numberOfElementsInQueuePurgeEvent > 0 && currentInRequest != NULL)
    {

        WdfRequestComplete(currentInRequest, statusRequestIn);
        statusPurge = WdfIoQueueRetrieveNextRequest(queueIoPurgeEvent, &requestPurge);
        WdfRequestComplete(requestPurge, statusPurge);
        DbgPrintEx(DPFLTR_IHVNETWORK_ID, 0xFFFFFFFF, "INFO: IO purge event received, currentInRequeest completed, current amount of packets captured = %d\n",intNumberOfActivePacket);
        currentInRequest = NULL;
        remainingMemory = segmentTotalMemory;
    }

    if (currentInRequest == NULL)
    {

        DbgPrint("INFO: no pending request\n");
        #define X(type,name) \
            DbgPrint("INFO: current queue name = %s\n", #name);\
            WdfIoQueueGetState(rxInvertedIoQueue.name, &numberOfElementsInCurrentInvertedQueue, NULL);\
            DbgPrintEx(DPFLTR_IHVNETWORK_ID, 0xFFFFFFFF, "%lu ", numberOfElementsInCurrentInvertedQueue);\
            if (numberOfElementsInCurrentInvertedQueue > 0 &&  numberOfElementsInInvertedQueue==0){numberOfElementsInInvertedQueue = numberOfElementsInCurrentInvertedQueue; currentQueue = &rxInvertedIoQueue.name;DbgPrint("\nINFO: Selected queue = %s\n",#name)/*;DbgPrintEx(DPFLTR_IHVNETWORK_ID, 0xFFFFFFFF,"INFO: current queue name = %s, currentQueue address = %p source queue address = %p\n", #name, currentQueue, &rxInvertedIoQueue.name)*/;}\
            DbgPrint("INFO: queue size = %lu\n", numberOfElementsInCurrentInvertedQueue);
            INVERTED_QUEUE_LIST
        #undef X
        DbgPrintEx(DPFLTR_IHVNETWORK_ID, 0xFFFFFFFF, "\nINFO: numberOfElementsInInvertedQueue = %lu\n", numberOfElementsInInvertedQueue);
        DbgPrint("INFO: Exited da loop, numberOfElementsInInvertedQueue = %lu\n", numberOfElementsInInvertedQueue);
        switch (numberOfElementsInInvertedQueue)
        {
        case 0:
        {
            DbgPrint("ERROR : IN FILTER : all queues are empty mate\n");
            intNumberOfDroppedPacket++;
            DbgPrintEx(DPFLTR_IHVNETWORK_ID, 0xFFFFFFFF, "INFO: queues empty, had to drop da %d th packet mate:/\n", intNumberOfDroppedPacket);
            remainingMemory = segmentTotalMemory;
            break;
        }
        default:
        {
            DbgPrint("INFO: retrieving request\n");
            statusRequestIn = WdfIoQueueRetrieveNextRequest(*currentQueue,
                &currentInRequest);

            status = WdfRequestRetrieveInputBuffer(currentInRequest, 0, (PVOID*)&ioInputBuffer, NULL);
//            readBuffer = (BYTE*)ioOutputBuffer;
//            DbgPrintEx(DPFLTR_IHVNETWORK_ID, 0xFFFFFFFF, "INFO: numberOfElementsInInvertedQueue = %lu\n", numberOfElementsInInvertedQueue);
//            DbgPrintEx(DPFLTR_IHVNETWORK_ID, 0xFFFFFFFF, "INFO: retrieved a request with output buffer = %X\n", ioInputBuffer[0]);

            intNumberOfActivePacket++;
            DbgPrint("INFO: retrieved request\n");
            remainingMemory = segmentTotalMemory - ((int)icmpLength + 34);

            break;
        }
        }
    }
    else if (currentInRequest != NULL)
    {
        switch (bEnoughMemory)
        {
        case -2:
        {
            remainingMemory = remainingMemory - ((int)icmpLength + 34);
            DbgPrint("INFO: enough memory on current segment\n");
            intNumberOfActivePacket++;
            break;
        }
        case -1:
        {
            DbgPrint("INFO: Not enough memory, completing pending request\n");
            status = WdfRequestRetrieveInputBuffer(currentInRequest, 0, (PVOID*)&ioInputBuffer, NULL);
            status = WdfRequestRetrieveOutputBuffer(currentInRequest, 0, (PVOID*)&ioOutputBuffer, NULL);
            ioOutputBuffer = ioInputBuffer;
            //ioOutputBuffer[1] = intNumberOfActivePacket;
            DbgPrintEx(DPFLTR_IHVNETWORK_ID, 0xFFFFFFFF, "INFO: output Buffer at completion time = %X, status = 0x%X number of captured packets = %d\n", ioOutputBuffer[0], status, intNumberOfActivePacket);
            
            intNumberOfActivePacket = 0;
            WdfRequestCompleteWithInformation(currentInRequest, statusRequestIn, 2*sizeof(ULONG));
            #define X(type,name) \
              DbgPrint("INFO: current queue name = %s\n", #name);\
              WdfIoQueueGetState(rxInvertedIoQueue.name, &numberOfElementsInCurrentInvertedQueue, NULL);\
              DbgPrintEx(DPFLTR_IHVNETWORK_ID, 0xFFFFFFFF, "%lu ", numberOfElementsInCurrentInvertedQueue);\
              if (numberOfElementsInCurrentInvertedQueue > 0 &&  numberOfElementsInInvertedQueue==0){numberOfElementsInInvertedQueue = numberOfElementsInCurrentInvertedQueue; currentQueue = &rxInvertedIoQueue.name;DbgPrint("INFO: Selected queue = %s",#name)/*;DbgPrintEx(DPFLTR_IHVNETWORK_ID, 0xFFFFFFFF,"INFO: current queue name = %s, currentQueue address = %p source queue address = %p\n", #name, currentQueue, &rxInvertedIoQueue.name)*/;}\
              DbgPrint("INFO: queue size = %lu\n", numberOfElementsInCurrentInvertedQueue);
              INVERTED_QUEUE_LIST
            #undef X
            DbgPrintEx(DPFLTR_IHVNETWORK_ID, 0xFFFFFFFF, "\nINFO: numberOfElementsInInvertedQueue = %lu\n", numberOfElementsInInvertedQueue);
            DbgPrint("INFO: Exited da loop, numberOfElementsInInvertedQueue = %lu\n", numberOfElementsInInvertedQueue);
            currentInRequest = NULL;
            remainingMemory = segmentTotalMemory;
            DbgPrint("INFO: completed request \n");
            DbgPrint("INFO: second switch numberofelementsininvertedqueue = %X\n", numberOfElementsInInvertedQueue);
            switch (numberOfElementsInInvertedQueue)

            {
            case 0:
            {
                DbgPrint("ERROR : IN FILTER : all queues are empty mate\n");
                intNumberOfDroppedPacket++;

                DbgPrintEx(DPFLTR_IHVNETWORK_ID, 0xFFFFFFFF, "INFO: remaining queues are empty, had to drop da %d th packet mate:/\n", intNumberOfDroppedPacket);
                break;
            }
            default:
            {
                DbgPrint("INFO: retrieving new request from queue\n");
                statusRequestIn = WdfIoQueueRetrieveNextRequest(*currentQueue,
                    &currentInRequest);
                DbgPrint("INFO: retrieved new request from queue\n");

                status = WdfRequestRetrieveInputBuffer(currentInRequest, 0, (PVOID*)&ioInputBuffer, NULL);
                //            readBuffer = (BYTE*)ioOutputBuffer;
//                DbgPrintEx(DPFLTR_IHVNETWORK_ID, 0xFFFFFFFF, "INFO: numberOfElementsInInvertedQueue = %lu\n", numberOfElementsInInvertedQueue);
//                DbgPrintEx(DPFLTR_IHVNETWORK_ID, 0xFFFFFFFF, "INFO: retrieved a request with output buffer = %X\n", ioInputBuffer[0]);

                remainingMemory = remainingMemory - ((int)icmpLength + 34);
                intNumberOfActivePacket++;
                break;
            }
            }
            break;
        }
        }
    }
//    }
//    DbgPrintEx(DPFLTR_IHVNETWORK_ID, 0x0, "INFO: current queue holds this many pending IO controls %d \n", numberOfElementsInInvertedQueue);
    /*
    switch (intNumberOfActivePacket)
    {
    case 100:
    {
//        status = WdfRequestRetrieveInputBuffer(currentInRequest, 0, (PVOID*)&ioInputBuffer, NULL);
//        status = WdfRequestRetrieveOutputBuffer(currentInRequest, 0, (PVOID*)&ioOutputBuffer, NULL);
 //       BYTE* readBuffer = (BYTE*)ioInputBuffer;
 //       readBuffer = (BYTE*)ioOutputBuffer;
        //DbgPrintEx(DPFLTR_IHVNETWORK_ID, 0xFFFFFFFF, "INFO: output Buffer at completion time = %X, status = 0x%X\n", readBuffer[0], status);
//        WdfRequestCompleteWithInformation(currentInRequest, statusRequestIn,sizeof(BYTE));
        WdfRequestComplete(currentInRequest, statusRequestIn);
        intNumberOfActivePacket = 0;
        DbgPrint("INFO: 10 packets captured, completing da request\n");
//        DbgPrintEx(DPFLTR_IHVNETWORK_ID, 0x0, "INFO: 10 packets captured, completing da request\n");
        break;
    }
    case 0:
    {
        switch (numberOfElementsInInvertedQueue)
        {
        case 0:
        {
            DbgPrint("ERROR : IN FILTER : all queues are empty mate\n");
            intNumberOfDroppedPacket++;
            DbgPrintEx(DPFLTR_IHVNETWORK_ID, 0xFFFFFFFF, "INFO: queues empty, had to drop da %d th packet mate:/\n", intNumberOfDroppedPacket);
            break;
        }
        default:
        {
            statusRequestIn = WdfIoQueueRetrieveNextRequest(*currentQueue,
                &currentInRequest);
            //DbgPrintEx(DPFLTR_IHVNETWORK_ID, 0xFFFFFFFF, "INFO: current queue address = %p\n", currentQueue);
            status = WdfRequestRetrieveInputBuffer(currentInRequest, 0, (PVOID*)&ioInputBuffer, NULL);
            DbgPrint("INFO : IN FILTER : queue is not empty\n");
//            BYTE* readBuffer = (BYTE*)ioInputBuffer;
            //DbgPrintEx(DPFLTR_IHVNETWORK_ID, 0xFFFFFFFF, "INFO: input Buffer = %X, status = 0x%X\n",readBuffer[0], status);
            status = WdfRequestRetrieveOutputBuffer(currentInRequest, 0, (PVOID*)&ioOutputBuffer, NULL);
            ioOutputBuffer = ioInputBuffer;
            
//            status = WdfRequestRetrieveOutputBuffer(currentInRequest, 0, (PVOID*)&ioOutputBuffer, NULL);
//            readBuffer = (BYTE*)ioOutputBuffer;
            //DbgPrintEx(DPFLTR_IHVNETWORK_ID, 0xFFFFFFFF, "INFO: output Buffer = %X, status = 0x%X\n", readBuffer[0], status);
            /*
            status = WdfRequestRetrieveOutputBuffer(currentInRequest, 0, &ioOutputBuffer, NULL);
            readBuffer = (BYTE*)ioOutputBuffer;
            DbgPrintEx(DPFLTR_IHVNETWORK_ID, 0xFFFFFFFF, "INFO: output Buffer after copy = %X, status = 0x%X\n", readBuffer[0], status);
            
//            DbgPrintEx(DPFLTR_IHVNETWORK_ID, 0x0, "INFO: queue not empty, pulling one out\n");
            intNumberOfActivePacket++;
            break;
        }
        }
        break;
    }
    default:
    {
        DbgPrint("INFO: IN FILTER: Number of active packets = %d\n", intNumberOfActivePacket);
//        DbgPrintEx(DPFLTR_IHVNETWORK_ID, 0xFFFFFFFF, "INFO: number of active packets%d \n", intNumberOfActivePacket);
        intNumberOfActivePacket++;
        break;
    }
    }
    */
    /*
    switch (numberOfElementsInInvertedQueue)
    {
    case 0:
    {
        DbgPrint("ERROR : IN FILTER : queue is empty mate\n");
        intNumberOfDroppedPacket++;
        DbgPrintEx(DPFLTR_IHVNETWORK_ID, 0xFFFFFFFF, "INFO: queue empty, had to drop da %d th packet mate:/\n", intNumberOfDroppedPacket);
        break;
    }
    default:
    {
        status = WdfIoQueueRetrieveNextRequest(queueIoInverted,
            &currentInRequest);
        WdfRequestComplete(currentInRequest, status);
        DbgPrint("INFO : IN FILTER : queue is not empty\n");
        break;
    }
    }
    */
    /*
    BYTE* pBufferPointerToPacket = (BYTE*)pBufferContiguousMemory;
    
    for (int i = 0; i < ((int)icmpLength + 34); i++)
    {
        DbgPrint("%X ", pBufferPointerToPacket[i]);
    }
    */
    DbgPrint("\n");
    cloneNBL = NdisAllocateCloneNetBufferList(fragmentList, handleNetBufferListPool, NULL, NDIS_CLONE_FLAGS_USE_ORIGINAL_MDLS);
    DbgPrint("INFO: clone nbl = %X\n", cloneNBL);
    if (!cloneNBL)
    {
        DbgPrint("ERROR: failed to allocate clone\n");
    }
    else if (cloneNBL)
    {
        DbgPrint("SUCCESS: Cloned NBL\n");
        cloneNB = NET_BUFFER_LIST_FIRST_NB(cloneNBL);
        DbgPrint("INFO: clone NB = %X\n", cloneNB);
        MDL* cloneFirstMDL = NET_BUFFER_FIRST_MDL(firstFragment);
        VOID* pCloneBuffer = MmGetSystemAddressForMdlSafe(cloneFirstMDL, HighPagePriority);
        BYTE* cloneValueMDL = ((BYTE*)pCloneBuffer);
        UNREFERENCED_PARAMETER(cloneValueMDL);
        DbgPrint("INFO: cloned packeto = \n");
        /*
        for (int i = 0; i < ((int)icmpLength + 34); i++) {
            DbgPrint("%X ", cloneValueMDL[i]);
        }
        */
        DbgPrint("\n");
        NdisFreeCloneNetBufferList(cloneNBL, NDIS_CLONE_FLAGS_USE_ORIGINAL_MDLS);   
    }
    
//    DbgPrint("INFO: secondMDL = 0x%p\n", secondMDL);
}
VOID CalloutFilterOut(
    const FWPS_INCOMING_VALUES* inFixedValues,
    const FWPS_INCOMING_METADATA_VALUES* inMetaValues,
    void* layerData,
    const void* classifyContext,
    const FWPS_FILTER* filter,
    UINT64 flowContext,
    FWPS_CLASSIFY_OUT* classifyOut
) {
    UNREFERENCED_PARAMETER(inFixedValues);
    UNREFERENCED_PARAMETER(inMetaValues);
    UNREFERENCED_PARAMETER(layerData);
    UNREFERENCED_PARAMETER(classifyContext);
    UNREFERENCED_PARAMETER(filter);
    UNREFERENCED_PARAMETER(flowContext);
    UNREFERENCED_PARAMETER(classifyOut);

    // Packet parsing logic goes here...
    DbgPrint("INFO: Sent a packet I love you Printhigka :D\n");
}
NTSTATUS CalloutNotify(
    FWPS_CALLOUT_NOTIFY_TYPE  notifyType,
    const GUID* filterKey,
    FWPS_FILTER* filter
) {
    UNREFERENCED_PARAMETER(notifyType);
    UNREFERENCED_PARAMETER(filterKey);
    UNREFERENCED_PARAMETER(filter);

    return STATUS_SUCCESS;
}
NTSTATUS CalloutAdd(GUID CALLOUT_GUID, GUID LayerApplied, UINT32 *addCalloutId) {
    NTSTATUS status;
    *addCalloutId = 0;

    FWPM_CALLOUT callout = {
      .flags = 0,                                // None
      .displayData.name = L"MaliciousCalloutName",
      .displayData.description = L"MaliciousCalloutDescription",
      .calloutKey = CALLOUT_GUID,                     // The GUID that uniquely identifies the callout (must match the registered FWPS_CALLOUT GUID)
      .applicableLayer = LayerApplied
    };

    status = FwpmCalloutAdd(engineHandle, &callout, NULL, addCalloutId);
    DbgPrint("addCalloutId = %u, addCalloutIdIn = %u, addCalloutIdOut = %u\n", *addCalloutId,addCalloutIdIn,addCalloutIdOut);
    return status;
}
//sublayeradd is roughly equivalent to the FilterClass, it specifies the priority of the callout when being called by the calling driver. A higher weight means the driver will be called earlier
NTSTATUS SublayerAdd() {

    FWPM_SUBLAYER sublayer = {
      .displayData.name = L"MaliciousSublayerName",
      .displayData.name = L"MaliciousSublayerDescription",
      .subLayerKey = SUB_LAYER_GUID,         // Unique GUID that identifies the sublayer
      .weight = 65535                   // Max UINT16 value, higher weight means higher priority
    };
    DbgPrint("INFO: adding sublayer\n");
    return FwpmSubLayerAdd(engineHandle, &sublayer, NULL);
}
NTSTATUS FilterAdd(GUID CALLOUT_GUID, GUID LayerApplied , UINT64 *filterId) {
    NTSTATUS status;
    *filterId = 0;                                              // Initialize the filterId to 0
    UINT64      weightValue = 0xFFFFFFFFFFFFFFFF;                             // Max UINT64 value
    FWP_VALUE   weight = { .type = FWP_UINT64, .uint64 = &weightValue }; // Weight variable, higher weight means higher priority
    FWPM_FILTER_CONDITION conditions[1] = { 0 };                              // Filter conditions can be empty, we want to process every packet

    FWPM_FILTER filter = {
      .displayData.name = L"MaliciousFilterName",
      .displayData.name = L"MaliciousFilterDescription",
      .layerKey = LayerApplied,  // Needs to work on the same layer as our added callout
      .subLayerKey = SUB_LAYER_GUID,                   // Unique GUID that identifies the sublayer, GUID needs to be the same as the GUID of the added sublayer
      .weight = weight,                           // Weight variable, higher weight means higher priority
      .numFilterConditions = 0,                                // Number of filter conditions (0 because conditions variable is empty)
      .filterCondition = conditions,                       // Empty conditions structure (we don't want to do any filtering)	
      .action.type = FWP_ACTION_CALLOUT_INSPECTION,    // We only want to inspect the packet (https://learn.microsoft.com/en-us/windows/win32/api/fwpmtypes/ns-fwpmtypes-fwpm_action0)
      .action.calloutKey = CALLOUT_GUID                      // Unique GUID that identifies the callout, GUID needs to be the same as the GUID of the added callout
    };
    DbgPrint("INFO: Adding filter\n");

    status = FwpmFilterAdd(engineHandle, &filter, NULL, filterId);
    DbgPrint("INFO: filterID=%u, filterIdIn=%u, filterIdOut=%u\n", *filterId,filterIdIn,filterIdOut);
    return status;
}
VOID TermCalloutIds(UINT32 registerCalloutId, UINT32 addCalloutId, UINT64 filterId) {
    NTSTATUS status;
    DbgPrint("INFO: Terminating callout identifiers.\n");
    
    if (engineHandle) {
        DbgPrint("INFO: engine handle present: 0x%p\n", engineHandle);
        DbgPrint("INFO: inside TermCalloutIds registerCalloutId = %u, addCalloutId = %u, filterId = %u\n", registerCalloutId, addCalloutId, filterId);
        // Clear 'filterId' related data
        if (filterId) {
            DbgPrint("INFO: filterId at = 0x%p\n", &filterId);
            FwpmFilterDeleteById(engineHandle, filterId);
            DbgPrint("INFO: checking if filterId deleted at = 0x%p\n", filterId);
            FwpmSubLayerDeleteByKey(engineHandle, &SUB_LAYER_GUID);
            filterId = 0;
        }
        // Clear 'addCalloutId' related data
        if (addCalloutId) {
            DbgPrint("INFO: addCalloutId at = 0x%p\n", &addCalloutId);
            status = FwpmCalloutDeleteById(engineHandle, addCalloutId);
            DbgPrint("INFO: Deleted addCalloutId with status 0x%X\n", status);
            addCalloutId = 0;
        }
        
        // Clear 'registerCalloutId' related data
        if (registerCalloutId) {
            DbgPrint("INFO: registerCalloutId at = 0x%p\n", &registerCalloutId);
            status = FwpsCalloutUnregisterById(registerCalloutId);
            DbgPrint("INFO: unregistered callout ID with status = 0x%X\n", status);
            registerCalloutId = 0;
        }

    }
}
VOID Cleanup(UINT32 registerCalloutId, UINT32 addCalloutId, UINT64 filterId) {
    DbgPrint("INFO: Cleanup called\n");
    DbgPrint("INFO: inside Cleanup registerCalloutId = %u, addCalloutId = %u, filterId = %u\n", registerCalloutId, addCalloutId, filterId);
    TermCalloutIds(registerCalloutId, addCalloutId, filterId);
    //    TermWfpEngine();
    //    TermFilterDeviceObject();
}

//end of unreviewed code from the tutorial

/*
VOID
NonPnpEvtDeviceFileCreate(
    IN WDFDEVICE            Device,
    IN WDFREQUEST Request,
    IN WDFFILEOBJECT        FileObject
)
{
    PUNICODE_STRING             fileName;
    UNICODE_STRING              absFileName, directory;
    OBJECT_ATTRIBUTES           fileAttributes;
    IO_STATUS_BLOCK             ioStatus;
    PCONTROL_DEVICE_EXTENSION   devExt;
    NTSTATUS                    status;
    USHORT                      length = 0;
    UNREFERENCED_PARAMETER(FileObject);
    devExt = ControlGetData(Device);
    RtlInitUnicodeString(&directory, L"\\SystemRoot\\temp");
    fileName = WdfFileObjectGetFileName(FileObject);
    length = directory.Length + fileName->Length;
    absFileName.Buffer = ExAllocatePool2(POOL_FLAG_PAGED, length, POOL_TAG);
    if (absFileName.Buffer == NULL) {
        status = STATUS_INSUFFICIENT_RESOURCES;
        DbgPrint("ExAllocatePool2 failed\n");
        goto End;
    }
    absFileName.Length = 0;
    absFileName.MaximumLength = length;
    status = RtlAppendUnicodeStringToString(&absFileName, &directory);
    if (!NT_SUCCESS(status)) {
        DbgPrint("RtlAppendUnicodeStringToString failed with status 0x%X\n",status);
        goto End;
    }
    status = RtlAppendUnicodeStringToString(&absFileName, fileName);
    if (!NT_SUCCESS(status)) {
        DbgPrint("RtlAppendUnicodeStringToString failed with status 0x%X\n",
            status);
        goto End;
    }
    InitializeObjectAttributes(&fileAttributes,
        &absFileName,
        OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE,
        NULL, // RootDirectory
        NULL // SecurityDescriptor
    );
    status = ZwCreateFile(
        &devExt->FileHandle,
        SYNCHRONIZE | GENERIC_WRITE | GENERIC_READ,
        &fileAttributes,
        &ioStatus,
        NULL,// alloc size = none
        FILE_ATTRIBUTE_NORMAL,
        FILE_SHARE_READ,
        FILE_OPEN_IF,
        FILE_SYNCHRONOUS_IO_NONALERT | FILE_NON_DIRECTORY_FILE,
        NULL,// eabuffer
        0// ealength
    );
    if (!NT_SUCCESS(status)) {

        DbgPrint("ZwCreateFile failed with status 0x%X", status);
        devExt->FileHandle = NULL;
    }
    DbgPrint("status upon calling createfile = 0x%X", status);
End:
    if (absFileName.Buffer != NULL) {
        ExFreePool(absFileName.Buffer);
    }

    WdfRequestComplete(Request, status);

    return;
}
*/