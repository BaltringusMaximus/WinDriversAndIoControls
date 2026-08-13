#include <stdio.h>
#include <windows.h>
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

#define IOCTL_INVERT_SIMULATE_EVENT_OCCURRED CTL_CODE(FILE_DEVICE_UNKNOWN, 0x2052, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_PURGE_ALL_NON_DEFAULT_QUEUES CTL_CODE(FILE_DEVICE_UNKNOWN, 0x4095, METHOD_BUFFERED, FILE_ANY_ACCESS)

DWORD WINAPI CompletionPortThread(LPVOID PortHandle);
DWORD WINAPI CompletionPortThread_2(LPVOID PortHandle);
DWORD WINAPI CompletionPortThread_3(LPVOID PortHandle);
DWORD WINAPI CompletionPortThread_4(LPVOID PortHandle);
DWORD WINAPI CompletionPortThread_5(LPVOID PortHandle);
DWORD WINAPI CompletionPortThread_6(LPVOID PortHandle);
DWORD WINAPI CompletionPortThread_7(LPVOID PortHandle);
DWORD WINAPI CompletionPortThread_8(LPVOID PortHandle);
DWORD WINAPI CompletionPortThread_9(LPVOID PortHandle);
DWORD WINAPI CompletionPortThread_10(LPVOID PortHandle);
VOID fPacketCounter();
typedef struct _OVL_WRAPPER {
    OVERLAPPED  Overlapped;
    unsigned char        ReturnedSequence;
} OVL_WRAPPER, * POVL_WRAPPER;

typedef struct {
    OVERLAPPED overlapped;
    unsigned char outBuffer;
} dataOverlapped;
//HANDLE driverHandle;
HANDLE device = INVALID_HANDLE_VALUE;
HANDLE deviceInverted = INVALID_HANDLE_VALUE;
HANDLE deviceInverted_2 = INVALID_HANDLE_VALUE;
HANDLE deviceInverted_3 = INVALID_HANDLE_VALUE;
HANDLE deviceInverted_4 = INVALID_HANDLE_VALUE;
HANDLE deviceInverted_5 = INVALID_HANDLE_VALUE;
HANDLE deviceInverted_6 = INVALID_HANDLE_VALUE;
HANDLE deviceInverted_7 = INVALID_HANDLE_VALUE;
HANDLE deviceInverted_8 = INVALID_HANDLE_VALUE;
HANDLE deviceInverted_9 = INVALID_HANDLE_VALUE;
HANDLE deviceInverted_10 = INVALID_HANDLE_VALUE;

unsigned char inBuffer[128] = { 0 };
unsigned char outBuffer[128] = { 0 };

unsigned char inBuffer2[128] = { 0 };
unsigned char outBuffer2[128] = { 0 };

unsigned char inBuffer3[128] = { 0 };
unsigned char outBuffer3[128] = { 0 };

unsigned char inBuffer4[128] = { 0 };
unsigned char outBuffer4[128] = { 0 };

unsigned char inBuffer5[128] = { 0 };
unsigned char outBuffer5[128] = { 0 };

unsigned char inBuffer6[128] = { 0 };
unsigned char outBuffer6[128] = { 0 };

unsigned char inBuffer7[128] = { 0 };
unsigned char outBuffer7[128] = { 0 };

unsigned char inBuffer8[128] = { 0 };
unsigned char outBuffer8[128] = { 0 };

unsigned char inBuffer9[128] = { 0 };
unsigned char outBuffer9[128] = { 0 };

unsigned char inBuffer10[128] = { 0 };
unsigned char outBuffer10[128] = { 0 };

DWORD bytesReturned = 0;
int intPacketCount = 0;
int intPendingIo = 0;
BOOL bStopSending = FALSE;

int main()
{
    //HANDLE device = INVALID_HANDLE_VALUE;
    BOOL status = FALSE;
//    DWORD bytesReturned = 0;
//    CHAR inBuffer[128] = { 0 };
//    CHAR outBuffer[128] = { 0 };
    DWORD   code;
    HANDLE hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    HANDLE  completionPortHandle;
    HANDLE  completionPortHandle_2;
    HANDLE  completionPortHandle_3;
    HANDLE  completionPortHandle_4;
    HANDLE  completionPortHandle_5;
    HANDLE  completionPortHandle_6;
    HANDLE  completionPortHandle_7;
    HANDLE  completionPortHandle_8;
    HANDLE  completionPortHandle_9;
    HANDLE  completionPortHandle_10;

    HANDLE  completionPortHandlePurge;
    DWORD   dwThreadId = 0;
    DWORD   dwThreadId2 = 1;
    DWORD   dwThreadId3 = 2;
    DWORD   dwThreadId4 = 3;
    DWORD   dwThreadId5 = 4;
    DWORD   dwThreadId6 = 5;
    DWORD   dwThreadId7 = 6;
    DWORD   dwThreadId8 = 7;
    DWORD   dwThreadId9 = 8;
    DWORD   dwThreadId10 = 9;
    DWORD   dwThreadIdPacketCounter = 10;
    HANDLE  hThread;
    HANDLE  hThread2;
    HANDLE  hThread3;
    HANDLE  hThread4;
    HANDLE  hThread5;
    HANDLE  hThread6;
    HANDLE  hThread7;
    HANDLE  hThread8;
    HANDLE  hThread9;
    HANDLE  hThread10;
    HANDLE  hThreadPC;
    DWORD  dwExitCode = 0;
    DWORD statusWait;
    BOOL statusCloseHandle;
    BOOL statusTerminateThread;
    int waitTest;
    OVERLAPPED overlapped;
    memset(&overlapped, 0, sizeof(OVERLAPPED));
    OVERLAPPED overlappedM;
    OVERLAPPED overlappedM2;
    OVERLAPPED overlappedM3;
    OVERLAPPED overlappedM4;
    OVERLAPPED overlappedM5;
    OVERLAPPED overlappedM6;
    OVERLAPPED overlappedM7;
    OVERLAPPED overlappedM8;
    OVERLAPPED overlappedM9;
    OVERLAPPED overlappedM10;
    memset(&overlappedM, 0, sizeof(OVERLAPPED));
    memset(&overlappedM2, 0, sizeof(OVERLAPPED));
    memset(&overlappedM3, 0, sizeof(OVERLAPPED));
    memset(&overlappedM4, 0, sizeof(OVERLAPPED));
    memset(&overlappedM5, 0, sizeof(OVERLAPPED));
    memset(&overlappedM6, 0, sizeof(OVERLAPPED));
    memset(&overlappedM7, 0, sizeof(OVERLAPPED));
    memset(&overlappedM8, 0, sizeof(OVERLAPPED));
    memset(&overlappedM9, 0, sizeof(OVERLAPPED));
    memset(&overlappedM10, 0, sizeof(OVERLAPPED));
    dataOverlapped *mainOverlapped;
    mainOverlapped = (dataOverlapped*)(malloc(sizeof(dataOverlapped)));
    memset(mainOverlapped, 0, sizeof(dataOverlapped));
    /*
    mainOverlapped.overlapped.Offset = 0;
    mainOverlapped.overlapped.OffsetHigh = 0;
    mainOverlapped.overlapped.hEvent = hEvent;
    
    overlapped.Offset = 0;
    overlapped.OffsetHigh = 0;
    overlapped.hEvent = hEvent;
    */
    printf("hellow\n inBuffer=%wZ\n",inBuffer);
    device = CreateFileW(L"\\\\.\\SpotlessDeviceLink", GENERIC_WRITE | GENERIC_READ | GENERIC_EXECUTE, 0, 0, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, 0);
    deviceInverted = CreateFileW(L"\\\\.\\SpotlessDeviceLink", GENERIC_WRITE | GENERIC_READ | GENERIC_EXECUTE, 0, 0, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, 0);
    deviceInverted_2 = CreateFileW(L"\\\\.\\SpotlessDeviceLink", GENERIC_WRITE | GENERIC_READ | GENERIC_EXECUTE, 0, 0, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, 0);
    deviceInverted_3 = CreateFileW(L"\\\\.\\SpotlessDeviceLink", GENERIC_WRITE | GENERIC_READ | GENERIC_EXECUTE, 0, 0, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, 0);
    deviceInverted_4 = CreateFileW(L"\\\\.\\SpotlessDeviceLink", GENERIC_WRITE | GENERIC_READ | GENERIC_EXECUTE, 0, 0, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, 0);
    deviceInverted_5 = CreateFileW(L"\\\\.\\SpotlessDeviceLink", GENERIC_WRITE | GENERIC_READ | GENERIC_EXECUTE, 0, 0, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, 0);
    deviceInverted_6 = CreateFileW(L"\\\\.\\SpotlessDeviceLink", GENERIC_WRITE | GENERIC_READ | GENERIC_EXECUTE, 0, 0, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, 0);
    deviceInverted_7 = CreateFileW(L"\\\\.\\SpotlessDeviceLink", GENERIC_WRITE | GENERIC_READ | GENERIC_EXECUTE, 0, 0, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, 0);
    deviceInverted_8 = CreateFileW(L"\\\\.\\SpotlessDeviceLink", GENERIC_WRITE | GENERIC_READ | GENERIC_EXECUTE, 0, 0, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, 0);
    deviceInverted_9 = CreateFileW(L"\\\\.\\SpotlessDeviceLink", GENERIC_WRITE | GENERIC_READ | GENERIC_EXECUTE, 0, 0, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, 0);
    deviceInverted_10 = CreateFileW(L"\\\\.\\SpotlessDeviceLink", GENERIC_WRITE | GENERIC_READ | GENERIC_EXECUTE, 0, 0, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, 0);
    printf("device = 0x%X\n", device);
    if (device == INVALID_HANDLE_VALUE)
    {
        printf("Could not open device: 0x%x\n", GetLastError());
    }
    if (deviceInverted == INVALID_HANDLE_VALUE)
    {
        printf("ERROR: Second device couldn't be created honey 0x%X\n", GetLastError());
    }
    completionPortHandle = CreateIoCompletionPort(deviceInverted,
        NULL,
        1,
        0);
    if (completionPortHandle == NULL) {

        code = GetLastError();

        printf("ERROR: CreateIoCompletionPort failed with error 0x%lx\n", code);

        return(code);

    }
    else if (completionPortHandle)
    {
        printf("SUCCESS: successfully created the completion port handle\n");
    }
    completionPortHandle_2 = CreateIoCompletionPort(deviceInverted_2,
        NULL,
        2,
        0);
    if (completionPortHandle_2 == NULL) {

        code = GetLastError();

        printf("ERROR: CreateIoCompletionPort failed with error 0x%lx\n", code);

        return(code);

    }
    completionPortHandle_3 = CreateIoCompletionPort(deviceInverted_3,
        NULL,
        3,
        0);
    if (completionPortHandle_3 == NULL) {

        code = GetLastError();

        printf("ERROR: CreateIoCompletionPort failed with error 0x%lx\n", code);

        return(code);

    }
    completionPortHandle_4 = CreateIoCompletionPort(deviceInverted_4,
        NULL,
        4,
        0);
    if (completionPortHandle_4 == NULL) {

        code = GetLastError();

        printf("ERROR: CreateIoCompletionPort failed with error 0x%lx\n", code);

        return(code);

    }
    completionPortHandle_5 = CreateIoCompletionPort(deviceInverted_5,
        NULL,
        5,
        0);
    if (completionPortHandle_5 == NULL) {

        code = GetLastError();

        printf("ERROR: CreateIoCompletionPort failed with error 0x%lx\n", code);

        return(code);

    }
    completionPortHandle_6 = CreateIoCompletionPort(deviceInverted_6,
        NULL,
        6,
        0);
    if (completionPortHandle_6 == NULL) {

        code = GetLastError();

        printf("ERROR: CreateIoCompletionPort failed with error 0x%lx\n", code);

        return(code);

    }
    completionPortHandle_7 = CreateIoCompletionPort(deviceInverted_7,
        NULL,
        7,
        0);
    if (completionPortHandle_7 == NULL) {

        code = GetLastError();

        printf("ERROR: CreateIoCompletionPort failed with error 0x%lx\n", code);

        return(code);

    }
    completionPortHandle_8 = CreateIoCompletionPort(deviceInverted_8,
        NULL,
        8,
        0);
    if (completionPortHandle_8 == NULL) {

        code = GetLastError();

        printf("ERROR: CreateIoCompletionPort failed with error 0x%lx\n", code);

        return(code);

    }
    completionPortHandle_9 = CreateIoCompletionPort(deviceInverted_9,
        NULL,
        9,
        0);
    if (completionPortHandle_9 == NULL) {

        code = GetLastError();

        printf("ERROR: CreateIoCompletionPort failed with error 0x%lx\n", code);

        return(code);

    }
    completionPortHandle_10 = CreateIoCompletionPort(deviceInverted_10,
        NULL,
        10,
        0);
    if (completionPortHandle_10 == NULL) {

        code = GetLastError();

        printf("ERROR: CreateIoCompletionPort failed with error 0x%lx\n", code);

        return(code);

    }
    hThread = CreateThread(NULL,               // Default thread security descriptor
        0,                     // Default stack size
        CompletionPortThread,  // Start routine
        completionPortHandle,  // Start routine parameter
        0,                     // Run immediately
        &dwThreadId);          // Thread ID
    hThread2 = CreateThread(NULL,
        0,
        CompletionPortThread_2,
        completionPortHandle_2,
        0,
        &dwThreadId2);
    hThread3 = CreateThread(NULL,
        0,
        CompletionPortThread_3,
        completionPortHandle_3,
        0,
        &dwThreadId3);
    hThread4 = CreateThread(NULL,
        0,
        CompletionPortThread_4,
        completionPortHandle_4,
        0,
        &dwThreadId4);
    hThread5 = CreateThread(NULL,
        0,
        CompletionPortThread_5,
        completionPortHandle_5,
        0,
        &dwThreadId5);
    hThread6 = CreateThread(NULL,
        0,
        CompletionPortThread_6,
        completionPortHandle_6,
        0,
        &dwThreadId6);
    hThread7 = CreateThread(NULL,
        0,
        CompletionPortThread_7,
        completionPortHandle_7,
        0,
        &dwThreadId7);
    hThread8 = CreateThread(NULL,
        0,
        CompletionPortThread_8,
        completionPortHandle_8,
        0,
        &dwThreadId8);
    hThread9 = CreateThread(NULL,
        0,
        CompletionPortThread_9,
        completionPortHandle_9,
        0,
        &dwThreadId9);
    hThread10 = CreateThread(NULL,
        0,
        CompletionPortThread_10,
        completionPortHandle_10,
        0,
        &dwThreadId10);
    hThreadPC = CreateThread(NULL,               // Default thread security descriptor
        0,                     // Default stack size
        fPacketCounter,  // Start routine
        NULL,  // Start routine parameter
        0,                     // Run immediately
        &dwThreadIdPacketCounter);          // Thread ID
    if (hThread == NULL) {
        code = GetLastError();

        printf("ERROR: CreateThread failed with error 0x%lx\n", code);

        return(code);
    }
    else if (hThread)
    {
        printf("SUCCESS. Created completion handling thread\n");
    }
    status = DeviceIoControl(device, IOCTL_TEST, inBuffer, sizeof(inBuffer), outBuffer, sizeof(outBuffer), &bytesReturned, (LPOVERLAPPED)NULL);
    status = DeviceIoControl(device, IOCTL_TEST, inBuffer, sizeof(inBuffer), outBuffer, sizeof(outBuffer), &bytesReturned, (LPOVERLAPPED)NULL);
    status = DeviceIoControl(device, IOCTL_TEST, inBuffer, sizeof(inBuffer), outBuffer, sizeof(outBuffer), &bytesReturned, (LPOVERLAPPED)NULL);
    printf("sent io control with status 0x%X\n", status);
    for (int i = 0; i < 10; i++)
    {
        inBuffer[0] = 1 + i + 16;
        printf("inBuffer = %X\n", inBuffer[0]);
//        status = DeviceIoControl(deviceInverted, IOCTL_TEST_INVERTED, inBuffer, sizeof(inBuffer), &mainOverlapped->outBuffer, sizeof(LONG), &bytesReturned, &mainOverlapped->overlapped);
        status = DeviceIoControl(deviceInverted, IOCTL_TEST_INVERTED, inBuffer, sizeof(inBuffer), outBuffer, sizeof(LONG), &bytesReturned, (LPOVERLAPPED)&overlappedM);
        intPendingIo++;
        printf("sent io control with status 0x%X\n", status);
        inBuffer2[0] = inBuffer[0] + 16;
        printf("inBuffer = %X\n", inBuffer2[0]);
        status = DeviceIoControl(deviceInverted_2, IOCTL_TEST_INVERTED_2, inBuffer2, sizeof(inBuffer), outBuffer2, sizeof(outBuffer), &bytesReturned, (LPOVERLAPPED)&overlappedM2);
        intPendingIo++;
        printf("sent io control with status 0x%X\n", status);
        inBuffer3[0] = inBuffer2[0] + 16;
        printf("inBuffer = %X\n", inBuffer3[0]);
        status = DeviceIoControl(deviceInverted_3, IOCTL_TEST_INVERTED_3, inBuffer3, sizeof(inBuffer), outBuffer3, sizeof(outBuffer), &bytesReturned, (LPOVERLAPPED)&overlappedM3);
        intPendingIo++;
        printf("sent io control with status 0x%X\n", status);
        inBuffer4[0] = inBuffer3[0] + 16;
        printf("inBuffer = %X\n", inBuffer4[0]);
        status = DeviceIoControl(deviceInverted_4, IOCTL_TEST_INVERTED_4, inBuffer4, sizeof(inBuffer), outBuffer4, sizeof(outBuffer), &bytesReturned, (LPOVERLAPPED)&overlappedM4);
        intPendingIo++;
        printf("sent io control with status 0x%X\n", status);
        inBuffer5[0] = inBuffer4[0] + 16;
        printf("inBuffer = %X\n", inBuffer5[0]);
        status = DeviceIoControl(deviceInverted_5, IOCTL_TEST_INVERTED_5, inBuffer5, sizeof(inBuffer), outBuffer5, sizeof(outBuffer), &bytesReturned, (LPOVERLAPPED)&overlappedM5);
        intPendingIo++;
        printf("sent io control with status 0x%X\n", status);
        inBuffer6[0] = inBuffer5[0] + 16;
        printf("inBuffer = %X\n", inBuffer6[0]);
        status = DeviceIoControl(deviceInverted_6, IOCTL_TEST_INVERTED_6, inBuffer6, sizeof(inBuffer), outBuffer6, sizeof(outBuffer), &bytesReturned, (LPOVERLAPPED)&overlappedM6);
        intPendingIo++;
        printf("sent io control with status 0x%X\n", status);
        inBuffer7[0] = inBuffer6[0] + 16;
        printf("inBuffer = %X\n", inBuffer7[0]);
        status = DeviceIoControl(deviceInverted_7, IOCTL_TEST_INVERTED_7, inBuffer7, sizeof(inBuffer), outBuffer7, sizeof(outBuffer), &bytesReturned, (LPOVERLAPPED)&overlappedM7);
        intPendingIo++;
        printf("sent io control with status 0x%X\n", status);
        inBuffer8[0] = inBuffer7[0] + 16;
        printf("inBuffer = %X\n", inBuffer8[0]);
        status = DeviceIoControl(deviceInverted_8, IOCTL_TEST_INVERTED_8, inBuffer8, sizeof(inBuffer), outBuffer8, sizeof(outBuffer), &bytesReturned, (LPOVERLAPPED)&overlappedM8);
        intPendingIo++;
        printf("sent io control with status 0x%X\n", status);
        inBuffer9[0] = inBuffer8[0] + 16;
        printf("inBuffer = %X\n", inBuffer9[0]);
        status = DeviceIoControl(deviceInverted_9, IOCTL_TEST_INVERTED_9, inBuffer9, sizeof(inBuffer), outBuffer9, sizeof(outBuffer), &bytesReturned, (LPOVERLAPPED)&overlappedM9);
        intPendingIo++;
        printf("sent io control with status 0x%X\n", status);
        inBuffer10[0] = inBuffer9[0] + 16;
        printf("inBuffer = %X\n", inBuffer10[0]);
        status = DeviceIoControl(deviceInverted_10, IOCTL_TEST_INVERTED_10, inBuffer10, sizeof(inBuffer), outBuffer10, sizeof(outBuffer), &bytesReturned, (LPOVERLAPPED)&overlappedM10);
        intPendingIo++;
        printf("sent io control with status 0x%X\n", status);
//        printf("inBuffer = %X\n", inBuffer[0]);
    }
    waitTest = 0;
    while (waitTest != 3)
    {
        printf("type 1 to send an IO control to be queued, type 2 to send an IO control simulating an event\n");
        scanf_s("%d", &waitTest);
        printf("waiting... %d\n", waitTest);
        switch (waitTest)
        {
        case 1:
        {
            status = DeviceIoControl(deviceInverted, (DWORD)IOCTL_TEST_INVERTED, inBuffer, sizeof(inBuffer), outBuffer, sizeof(outBuffer), &bytesReturned, (LPOVERLAPPED)&overlapped);
            printf("sent io control with status 0x%X\n", status);
            break;
        }
        case 2:
        {
            status = DeviceIoControl(device, (DWORD)IOCTL_INVERT_SIMULATE_EVENT_OCCURRED, inBuffer, sizeof(inBuffer), outBuffer, sizeof(outBuffer), &bytesReturned, (LPOVERLAPPED)&overlapped);
            printf("sent io control with status 0x%X\n", status);
            break;
        }
        case 3:
        {
            bStopSending = TRUE;
            OVERLAPPED overlappedPurge;
            memset(&overlappedPurge, 0, sizeof(OVERLAPPED));
            DWORD byteCountPurge = 0;
            ULONG_PTR compKeyPurge = 0;
            completionPortHandlePurge = CreateIoCompletionPort(device, NULL, 999, 0);
            if (completionPortHandlePurge == NULL) {

                code = GetLastError();

                printf("ERROR: CreateIoCompletionPort failed with error 0x%lx\n", code);

                return(code);

            }
            status = DeviceIoControl(device, IOCTL_PURGE_ALL_NON_DEFAULT_QUEUES, inBuffer, sizeof(inBuffer), outBuffer, sizeof(outBuffer), &bytesReturned, (LPOVERLAPPED)&overlappedPurge);
            printf("sent io control with status 0x%X\n", status);
            BOOL workedPurge = GetQueuedCompletionStatus(completionPortHandlePurge, &byteCountPurge, &compKeyPurge, &overlappedPurge, INFINITE);
            printf("worked? = %X\n", workedPurge);
            Sleep(2000);
            statusCloseHandle = CloseHandle(device);
            code = GetLastError();
            printf("closed handle with status 0x%X, GetLastError returns 0x%X\n", statusCloseHandle,code);
            statusCloseHandle = CloseHandle(deviceInverted);
            code = GetLastError();
            printf("closed handle with status 0x%X, GetLastError returns 0x%X\n", statusCloseHandle, code);
            statusCloseHandle = CloseHandle(deviceInverted_2);
            code = GetLastError();
            printf("closed handle with status 0x%X, GetLastError returns 0x%X\n", statusCloseHandle, code);
            statusCloseHandle = CloseHandle(deviceInverted_3);
            code = GetLastError();
            printf("closed handle with status 0x%X, GetLastError returns 0x%X\n", statusCloseHandle, code);
            statusCloseHandle = CloseHandle(deviceInverted_4);
            code = GetLastError();
            printf("closed handle with status 0x%X, GetLastError returns 0x%X\n", statusCloseHandle, code);
            statusCloseHandle = CloseHandle(deviceInverted_5);
            code = GetLastError();
            printf("closed handle with status 0x%X, GetLastError returns 0x%X\n", statusCloseHandle, code);
            statusCloseHandle = CloseHandle(deviceInverted_6);
            code = GetLastError();
            printf("closed handle with status 0x%X, GetLastError returns 0x%X\n", statusCloseHandle, code);
            statusCloseHandle = CloseHandle(deviceInverted_7);
            code = GetLastError();
            printf("closed handle with status 0x%X, GetLastError returns 0x%X\n", statusCloseHandle, code);
            statusCloseHandle = CloseHandle(deviceInverted_8);
            code = GetLastError();
            printf("closed handle with status 0x%X, GetLastError returns 0x%X\n", statusCloseHandle, code);
            statusCloseHandle = CloseHandle(deviceInverted_9);
            code = GetLastError();
            printf("closed handle with status 0x%X, GetLastError returns 0x%X\n", statusCloseHandle, code);
            statusCloseHandle = CloseHandle(deviceInverted_10);
            code = GetLastError();
            printf("closed handle with status 0x%X, GetLastError returns 0x%X\n", statusCloseHandle, code);
            statusTerminateThread = TerminateThread(hThread,dwExitCode);
            code = GetLastError();
            printf("closed thread with status 0x%X, GetLastError returns 0x%X\n", statusTerminateThread, code);
            statusTerminateThread = TerminateThread(hThread2, dwExitCode);
            code = GetLastError();
            printf("closed thread with status 0x%X, GetLastError returns 0x%X\n", statusTerminateThread, code);
            statusTerminateThread = TerminateThread(hThread3, dwExitCode);
            code = GetLastError();
            printf("closed thread with status 0x%X, GetLastError returns 0x%X\n", statusTerminateThread, code);
            statusTerminateThread = TerminateThread(hThread4, dwExitCode);
            code = GetLastError();
            printf("closed thread with status 0x%X, GetLastError returns 0x%X\n", statusTerminateThread, code);
            statusTerminateThread = TerminateThread(hThread5, dwExitCode);
            code = GetLastError();
            printf("closed thread with status 0x%X, GetLastError returns 0x%X\n", statusTerminateThread, code);
            statusTerminateThread = TerminateThread(hThread6, dwExitCode);
            code = GetLastError();
            printf("closed thread with status 0x%X, GetLastError returns 0x%X\n", statusTerminateThread, code);
            statusTerminateThread = TerminateThread(hThread7, dwExitCode);
            code = GetLastError();
            printf("closed thread with status 0x%X, GetLastError returns 0x%X\n", statusTerminateThread, code);
            statusTerminateThread = TerminateThread(hThread8, dwExitCode);
            code = GetLastError();
            printf("closed thread with status 0x%X, GetLastError returns 0x%X\n", statusTerminateThread, code);
            statusTerminateThread = TerminateThread(hThread9, dwExitCode);
            code = GetLastError();
            printf("closed thread with status 0x%X, GetLastError returns 0x%X\n", statusTerminateThread, code);
            statusTerminateThread = TerminateThread(hThread10, dwExitCode);
            code = GetLastError();
            printf("closed thread with status 0x%X, GetLastError returns 0x%X\n", statusTerminateThread, code);
            statusTerminateThread = TerminateThread(hThreadPC, dwExitCode);
            code = GetLastError();
            printf("closed thread with status 0x%X, GetLastError returns 0x%X\n", statusTerminateThread, code);
            printf("closed handles and threads\n");
            break;
        }
        }
        
        continue;
    }
//    statusWait = WaitForSingleObject(hThread, INFINITE);
//    printf("status of wait is: %ld", statusWait);
    /*
    while (TRUE)
    {
        printf("INFO: handing around\n");
    }
    */
    printf("SHOULD terminate the program\n");
    exit(EXIT_SUCCESS);
    return 0;
}
void fPacketCounter()
{
    while (bStopSending == FALSE)
    {
        Sleep(2000);
        printf("don't mind me i'm counting nothing %d\n", intPacketCount);
    }
}
    

DWORD WINAPI CompletionPortThread(LPVOID PortHandle)
{
    DWORD byteCount = 0;
    ULONG_PTR compKey = 0;
//    OVERLAPPED* overlapped = NULL;
    OVERLAPPED *overlapped;
    
    OVERLAPPED overlapped2;
    OVERLAPPED overlappedEmpty;
    POVL_WRAPPER wrap;
    DWORD code;
    BOOL returnedValue;
    BOOL status = FALSE;
    HANDLE hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    dataOverlapped* currentOverlapped;
   // printf("test...1\n");
    while (bStopSending == FALSE) {
//        Sleep(1000);
//        printf("INFO: waiting for da completion statussy\n");
        // Wait for a completion notification.
        overlapped = NULL;
        //memset(&overlapped, 0, sizeof(OVERLAPPED));
        memset(&overlapped2, 0, sizeof(OVERLAPPED));
        //printf("test...2\n");

        /*
        currentOverlapped->overlapped.Internal = 0;
        currentOverlapped->overlapped.InternalHigh = 0;
        currentOverlapped->overlapped.Offset = 0;
        currentOverlapped->overlapped.OffsetHigh = 0;
        currentOverlapped->overlapped.hEvent = hEvent;
        */
        //printf("test...3\n");
        BOOL worked = GetQueuedCompletionStatus(PortHandle,                // Completion port handle
            &byteCount,                // Bytes transferred
            &compKey,                  // Completion key... don't care
            &overlapped,               // OVERLAPPED structure
            INFINITE);                 // Notification time-out interval
        //currentOverlapped = (dataOverlapped*)&overlapped;

//        currentOverlapped.outBuffer = &overlapped[sizeof(OVERLAPPED)];
        //printf("outputbuffer = %ld\n", currentOverlapped->outBuffer);
//        printf("did it work? did the adventure finish safely? %d\n", worked);
        //
        // If it's our notification ioctl that's just been completed...
        // don't do anything special. 
        // 
        /*
        if (byteCount == 0) {

            continue;
        }

        if (overlapped == NULL) {
            printf("INFO: overlapped structure is null\n");
            // An unrecoverable error occurred in the completion port.
            // Wait for the next notification.
            continue;
        }
        */
        //
        // Because the wrapper structure STARTS with the OVERLAPPED structure,
        // the pointers are the same.  It would be nicer to use
        // CONTAINING_RECORD here... however you do that in user-mode.
        // 
        //wrap = (POVL_WRAPPER)overlapped;
        
//        code = GetLastError();
//       printf("last error after GetQueuedCompletionStatus= 0x%X\n", code);
        returnedValue = GetOverlappedResult(device, overlapped, &byteCount, FALSE);
        printf("output Buffer = %X\n", outBuffer[0]);
        inBuffer[0] = outBuffer[0];
//        code = GetLastError();
        intPacketCount = intPacketCount + outBuffer[1];
//        printf("INFO: num packets = %d\n",intPacketCount);
//        printf("returned value overlapped = %d with error code = 0x%X\n", returnedValue,code);
//        printf("number of bytes returned = 0x%X\n", byteCount);
//        printf("INFO: Notification received.  Sequence = %lu\n", overlapped->Internal);
//        printf("INFO: CompKey = %d\n", compKey);
        if (bStopSending == FALSE)
        {
            status = DeviceIoControl(deviceInverted, (DWORD)IOCTL_TEST_INVERTED, inBuffer, sizeof(inBuffer), outBuffer, sizeof(outBuffer), &bytesReturned, (LPOVERLAPPED)&overlapped2);
        }
        /*
        for (int i = 0; i < 10; i++)
        {
            status = DeviceIoControl(deviceInverted, (DWORD)IOCTL_TEST_INVERTED, inBuffer, sizeof(inBuffer), outBuffer, sizeof(outBuffer), &bytesReturned, (LPOVERLAPPED)&overlapped2);
        }
        */
//        printf("INFO: sent io control with status 0x%X\n", status);
//        break;
        
    }
}

DWORD WINAPI CompletionPortThread_2(LPVOID PortHandle)
{
    DWORD byteCount = 0;
    ULONG_PTR compKey = 0;
    OVERLAPPED* overlapped = NULL;
    OVERLAPPED overlapped2;
    OVERLAPPED overlappedEmpty;
    POVL_WRAPPER wrap;
    DWORD code;
    BOOL returnedValue;
    BOOL status = FALSE;


    while (bStopSending == FALSE) {
        overlapped = NULL;
        memset(&overlapped2, 0, sizeof(OVERLAPPED));
        BOOL worked = GetQueuedCompletionStatus(PortHandle,                // Completion port handle
            &byteCount,                // Bytes transferred
            &compKey,                  // Completion key... don't care
            &overlapped,               // OVERLAPPED structure
            INFINITE);                 // Notification time-out interval
//        code = GetLastError();
        returnedValue = GetOverlappedResult(device, overlapped, &byteCount, FALSE);
//        code = GetLastError();
        intPacketCount = intPacketCount + outBuffer2[1];
        printf("output Buffer = %X\n", outBuffer2[0]);
        inBuffer2[0] = outBuffer2[0];
//        printf("INFO: CompKey = %d\n", compKey);
        if (bStopSending == FALSE)
        {
            status = DeviceIoControl(deviceInverted_2, (DWORD)IOCTL_TEST_INVERTED_2, inBuffer2, sizeof(inBuffer), outBuffer2, sizeof(outBuffer), &bytesReturned, (LPOVERLAPPED)&overlapped2);
        }

    }
}

DWORD WINAPI CompletionPortThread_3(LPVOID PortHandle)
{
    DWORD byteCount = 0;
    ULONG_PTR compKey = 0;
    OVERLAPPED* overlapped = NULL;
    OVERLAPPED overlapped2;
    OVERLAPPED overlappedEmpty;
    POVL_WRAPPER wrap;
    DWORD code;
    BOOL returnedValue;
    BOOL status = FALSE;


    while (bStopSending == FALSE) {
        overlapped = NULL;
        memset(&overlapped2, 0, sizeof(OVERLAPPED));
        BOOL worked = GetQueuedCompletionStatus(PortHandle,                // Completion port handle
            &byteCount,                // Bytes transferred
            &compKey,                  // Completion key... don't care
            &overlapped,               // OVERLAPPED structure
            INFINITE);                 // Notification time-out interval
//        code = GetLastError();
//        returnedValue = GetOverlappedResult(device, overlapped, &byteCount, FALSE);
//        code = GetLastError();
        intPacketCount = intPacketCount + outBuffer3[1];
        printf("output Buffer = %X\n", outBuffer3[0]);
        inBuffer3[0] = outBuffer3[0];
//        printf("INFO: CompKey = %d\n", compKey);
        if (bStopSending == FALSE)
        {
            status = DeviceIoControl(deviceInverted_3, (DWORD)IOCTL_TEST_INVERTED_3, inBuffer3, sizeof(inBuffer), outBuffer3, sizeof(outBuffer), &bytesReturned, (LPOVERLAPPED)&overlapped2);
        }

    }
}
DWORD WINAPI CompletionPortThread_4(LPVOID PortHandle)
{
    DWORD byteCount = 0;
    ULONG_PTR compKey = 0;
    OVERLAPPED* overlapped = NULL;
    OVERLAPPED overlapped2;
    OVERLAPPED overlappedEmpty;
    POVL_WRAPPER wrap;
    DWORD code;
    BOOL returnedValue;
    BOOL status = FALSE;


    while (bStopSending) {
        overlapped = NULL;
        memset(&overlapped2, 0, sizeof(OVERLAPPED));
        BOOL worked = GetQueuedCompletionStatus(PortHandle,                // Completion port handle
            &byteCount,                // Bytes transferred
            &compKey,                  // Completion key... don't care
            &overlapped,               // OVERLAPPED structure
            INFINITE);                 // Notification time-out interval
 //       code = GetLastError();
 //       returnedValue = GetOverlappedResult(device, overlapped, &byteCount, FALSE);
 //       code = GetLastError();
        intPacketCount = intPacketCount + outBuffer4[1];
        printf("output Buffer = %X\n", outBuffer4[0]);
        inBuffer4[0] = outBuffer4[0];
//        printf("INFO: CompKey = %d\n", compKey);
        if (bStopSending == FALSE)
        {
            status = DeviceIoControl(deviceInverted_4, (DWORD)IOCTL_TEST_INVERTED_4, inBuffer4, sizeof(inBuffer), outBuffer4, sizeof(outBuffer), &bytesReturned, (LPOVERLAPPED)&overlapped2);
        }

    }
}
DWORD WINAPI CompletionPortThread_5(LPVOID PortHandle)
{
    DWORD byteCount = 0;
    ULONG_PTR compKey = 0;
    OVERLAPPED* overlapped = NULL;
    OVERLAPPED overlapped2;
    OVERLAPPED overlappedEmpty;
    POVL_WRAPPER wrap;
    DWORD code;
    BOOL returnedValue;
    BOOL status = FALSE;


    while (bStopSending == FALSE) {
        overlapped = NULL;
        memset(&overlapped2, 0, sizeof(OVERLAPPED));
        BOOL worked = GetQueuedCompletionStatus(PortHandle,                // Completion port handle
            &byteCount,                // Bytes transferred
            &compKey,                  // Completion key... don't care
            &overlapped,               // OVERLAPPED structure
            INFINITE);                 // Notification time-out interval
//        code = GetLastError();
//        returnedValue = GetOverlappedResult(device, overlapped, &byteCount, FALSE);
//        code = GetLastError();
        intPacketCount = intPacketCount + outBuffer5[1];
        printf("output Buffer = %X\n", outBuffer5[0]);
        inBuffer5[0] = outBuffer5[0];
//        printf("INFO: CompKey = %d\n", compKey);
        if (bStopSending == FALSE)
        {
            status = DeviceIoControl(deviceInverted_5, (DWORD)IOCTL_TEST_INVERTED_5, inBuffer5, sizeof(inBuffer), outBuffer5, sizeof(outBuffer), &bytesReturned, (LPOVERLAPPED)&overlapped2);
        }

    }
}
DWORD WINAPI CompletionPortThread_6(LPVOID PortHandle)
{
    DWORD byteCount = 0;
    ULONG_PTR compKey = 0;
    OVERLAPPED* overlapped = NULL;
    OVERLAPPED overlapped2;
    OVERLAPPED overlappedEmpty;
    POVL_WRAPPER wrap;
    DWORD code;
    BOOL returnedValue;
    BOOL status = FALSE;


    while (bStopSending == FALSE) {
        overlapped = NULL;
        memset(&overlapped2, 0, sizeof(OVERLAPPED));
        BOOL worked = GetQueuedCompletionStatus(PortHandle,                // Completion port handle
            &byteCount,                // Bytes transferred
            &compKey,                  // Completion key... don't care
            &overlapped,               // OVERLAPPED structure
            INFINITE);                 // Notification time-out interval
//        code = GetLastError();
//        returnedValue = GetOverlappedResult(device, overlapped, &byteCount, FALSE);
//        code = GetLastError();
        intPacketCount = intPacketCount + outBuffer6[1];
        printf("output Buffer = %X\n", outBuffer6[0]);
        inBuffer6[0] = outBuffer6[0];
//        printf("INFO: CompKey = %d\n", compKey);
        if (bStopSending == FALSE)
        {
            status = DeviceIoControl(deviceInverted_6, (DWORD)IOCTL_TEST_INVERTED_6, inBuffer6, sizeof(inBuffer), outBuffer6, sizeof(outBuffer), &bytesReturned, (LPOVERLAPPED)&overlapped2);
        }

    }
}
DWORD WINAPI CompletionPortThread_7(LPVOID PortHandle)
{
    DWORD byteCount = 0;
    ULONG_PTR compKey = 0;
    OVERLAPPED* overlapped = NULL;
    OVERLAPPED overlapped2;
    OVERLAPPED overlappedEmpty;
    POVL_WRAPPER wrap;
    DWORD code;
    BOOL returnedValue;
    BOOL status = FALSE;


    while (bStopSending == FALSE) {
        overlapped = NULL;
        memset(&overlapped2, 0, sizeof(OVERLAPPED));
        BOOL worked = GetQueuedCompletionStatus(PortHandle,                // Completion port handle
            &byteCount,                // Bytes transferred
            &compKey,                  // Completion key... don't care
            &overlapped,               // OVERLAPPED structure
            INFINITE);                 // Notification time-out interval
//        code = GetLastError();
//        returnedValue = GetOverlappedResult(device, overlapped, &byteCount, FALSE);
//        code = GetLastError();
        intPacketCount = intPacketCount + outBuffer7[1];
        printf("output Buffer = %X\n", outBuffer7[0]);
        inBuffer7[0] = outBuffer7[0];
//        printf("INFO: CompKey = %d\n", compKey);
        if (bStopSending == FALSE)
        {
            status = DeviceIoControl(deviceInverted_7, (DWORD)IOCTL_TEST_INVERTED_7, inBuffer7, sizeof(inBuffer), outBuffer7, sizeof(outBuffer), &bytesReturned, (LPOVERLAPPED)&overlapped2);
        }

    }
}
DWORD WINAPI CompletionPortThread_8(LPVOID PortHandle)
{
    DWORD byteCount = 0;
    ULONG_PTR compKey = 0;
    OVERLAPPED* overlapped = NULL;
    OVERLAPPED overlapped2;
    OVERLAPPED overlappedEmpty;
    POVL_WRAPPER wrap;
    DWORD code;
    BOOL returnedValue;
    BOOL status = FALSE;


    while (bStopSending == FALSE) {
        overlapped = NULL;
        memset(&overlapped2, 0, sizeof(OVERLAPPED));
        BOOL worked = GetQueuedCompletionStatus(PortHandle,                // Completion port handle
            &byteCount,                // Bytes transferred
            &compKey,                  // Completion key... don't care
            &overlapped,               // OVERLAPPED structure
            INFINITE);                 // Notification time-out interval
 //       code = GetLastError();
 //       returnedValue = GetOverlappedResult(device, overlapped, &byteCount, FALSE);
 //       code = GetLastError();
        intPacketCount = intPacketCount + outBuffer8[1];
        printf("output Buffer = %X\n", outBuffer8[0]);
        inBuffer8[0] = outBuffer8[0];
//        printf("INFO: CompKey = %d\n", compKey);
        if (bStopSending == FALSE)
        {
            status = DeviceIoControl(deviceInverted_8, (DWORD)IOCTL_TEST_INVERTED_8, inBuffer8, sizeof(inBuffer), outBuffer8, sizeof(outBuffer), &bytesReturned, (LPOVERLAPPED)&overlapped2);
        }

    }
}
DWORD WINAPI CompletionPortThread_9(LPVOID PortHandle)
{
    DWORD byteCount = 0;
    ULONG_PTR compKey = 0;
    OVERLAPPED* overlapped = NULL;
    OVERLAPPED overlapped2;
    OVERLAPPED overlappedEmpty;
    POVL_WRAPPER wrap;
    DWORD code;
    BOOL returnedValue;
    BOOL status = FALSE;


    while (bStopSending == FALSE) {
        overlapped = NULL;
        /*
        overlapped2.Internal = 0;
        overlapped2.InternalHigh = 0;
        overlapped2.Offset = 0;
        overlapped2.OffsetHigh = 0;
        overlapped2.hEvent = NULL;
        */
        memset(&overlapped2, 0, sizeof(OVERLAPPED));
        BOOL worked = GetQueuedCompletionStatus(PortHandle,                // Completion port handle
            &byteCount,                // Bytes transferred
            &compKey,                  // Completion key... don't care
            &overlapped,               // OVERLAPPED structure
            INFINITE);                 // Notification time-out interval
//        code = GetLastError();
//        returnedValue = GetOverlappedResult(device, overlapped, &byteCount, FALSE);
//        code = GetLastError();
        intPacketCount = intPacketCount + outBuffer9[1];
        printf("output Buffer = %X\n", outBuffer9[0]);
        inBuffer9[0] = outBuffer9[0];
//        printf("INFO: CompKey = %d\n", compKey);
        if (bStopSending == FALSE)
        {
            status = DeviceIoControl(deviceInverted_9, (DWORD)IOCTL_TEST_INVERTED_9, inBuffer9, sizeof(inBuffer), outBuffer9, sizeof(outBuffer), &bytesReturned, (LPOVERLAPPED)&overlapped2);
        }

    }
}
DWORD WINAPI CompletionPortThread_10(LPVOID PortHandle)
{
    DWORD byteCount = 0;
    ULONG_PTR compKey = 0;
    OVERLAPPED* overlapped = NULL;
    OVERLAPPED overlapped2;
    OVERLAPPED overlappedEmpty;
    POVL_WRAPPER wrap;
    DWORD code;
    BOOL returnedValue;
    BOOL status = FALSE;


    while (bStopSending == FALSE) {
        overlapped = NULL;
        memset(&overlapped2, 0, sizeof(OVERLAPPED));
        BOOL worked = GetQueuedCompletionStatus(PortHandle,                // Completion port handle
            &byteCount,                // Bytes transferred
            &compKey,                  // Completion key... don't care
            &overlapped,               // OVERLAPPED structure
            INFINITE);                 // Notification time-out interval
//        code = GetLastError();
//        returnedValue = GetOverlappedResult(device, overlapped, &byteCount, FALSE);
//        code = GetLastError();
        intPacketCount = intPacketCount + outBuffer10[1];
        printf("output Buffer = %X\n", outBuffer10[0]);
        inBuffer10[0] = outBuffer10[0];
//        printf("INFO: CompKey = %d\n", compKey);
        if (bStopSending == FALSE)
        {
            status = DeviceIoControl(deviceInverted_10, (DWORD)IOCTL_TEST_INVERTED_10, inBuffer10, sizeof(inBuffer), outBuffer10, sizeof(outBuffer), &bytesReturned, (LPOVERLAPPED)&overlapped2);
        }
    }
}
