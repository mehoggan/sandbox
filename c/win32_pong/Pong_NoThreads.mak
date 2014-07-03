Pong_NoThreads.exe:Pong_NoThreads.c
    cl /EHs Pong_NoThreads.c kernel32.lib user32.lib gdi32.lib
    cl /EHs Pong_NoThreads.obj kernel32.lib user32.lib gdi32.lib
