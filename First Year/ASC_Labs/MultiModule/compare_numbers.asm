bits 32

global compare

segment code use32 class=code
    compare:
    
        cmp ebx, [esp+4]
        jb bigger
            mov ebx, [esp+4]
        bigger:
        ret