bits 32

global _compare

segment code use32 class=code
    _compare:
        mov ebx, [esp+4]
        cmp ebx, [esp+8]
        ja same_minim
            mov ebx, [esp+8]
        same_minim:
        mov eax, ebx
        ret