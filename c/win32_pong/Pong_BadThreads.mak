Pong_BadThreads.exe:Pong_BadThreads.c
    cl /EHs /MT Pong_BadThreads.c kernel32.lib user32.lib gdi32.lib libcmt.lib
    cl /EHs /MT Pong_BadThreads.obj kernel32.lib user32.lib gdi32.lib libcmt.lib
