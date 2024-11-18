#include <Windows.h>
#include <process.h>
#include <jni.h>
#include <cstdio>

unsigned __stdcall threadFunc(void*) {
    JavaVM* jvm;
    JNIEnv* env;

    jint res = JNI_GetCreatedJavaVMs(&jvm, 1, nullptr);
    if (res == JNI_OK && jvm != nullptr) {
        res = jvm->AttachCurrentThread((void**)&env, nullptr);
        if (res == JNI_OK) {
            jclass mc = env->FindClass("ave");
            printf_s("ptr: %p\n", (void*)mc);
            jvm->DetachCurrentThread();
        }
    }
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hmod, DWORD r, LPVOID) {
    if (r == DLL_PROCESS_ATTACH || r == DLL_THREAD_ATTACH) {
        AllocConsole();

        FILE* stream;
        freopen_s(&stream, "CONOUT$", "w", stdout);

        _beginthreadex(nullptr, 0, threadFunc, nullptr, 0, nullptr);
    }
    return TRUE;
}