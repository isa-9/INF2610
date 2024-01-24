;
; Ecole polytechnique de Montreal - GIGL
; Automne  2023
; Initlab - minisys.asm
;
; ajoutez vos noms, prénoms et matricules
; Isabella Santacuz 2204379, Michelle Nguyen 2212694
;
; Documentation NASM: http://www.nasm.us/doc/nasmdoc3.html
;
; Déclarations de constantes (equivalent à #define)
    sys_write           equ    1
    sys_exit            equ    60
    stdout              equ    1
    sys_nanosleep       equ    35

; Déclarations de variables
; db=char, dw=short, dd=int, dq=long

SECTION .data
; données initialisées
; man ascii -> code ascii en hexa de \n est 0x0A
    msg         db    "INF2610-TP1 ", 0x0A        ; char * msg = "INF2610-TP1 \n";
    msg_len     equ   $-msg                       ; msg_len = taille de msg


; Voir: man nanosleep pour les paramètres
; premier paramètre, à passer à sys_nanosleep, est de type struct timespec :  delay1 (3 secondes, 100 nanosecondes)
    delay1      dq  3
                dq  100
; deuxième paramètre à passer à sys_nanosleep
    delay2      dq  0
                dq  0
                
; TODO  ajouter si necessaire d'autres déclarations de variables
    msg_fin     db    "Fin de la pause!", 0x0A    ; char * msg_fin = "Fin de la pause!\n";
    msg_len_fin equ   $-msg_fin                   ; msg_len_fin = taille de msg
   
SECTION .text
global  _start
_start:
    ;
    ; Convention d'appel systeme Linux x86_64
    ; parametres: rdi, rsi, rdx, r10, r8, r9
    ; numero de l'appel systeme: rax
    ; valeur de retour: rax
    ;

    ;
    ; afficher msg sur la sortie standard
    ; prototype: int write( unsigned int fd,
    ;                       const char *buf,
    ;                       size_t count)
    ;
        mov     rdi, stdout         ; argument 1
        mov     rsi, msg            ; argument 2
        mov     rdx, msg_len        ; argument 3
        mov     rax, sys_write      ; appel systeme dans rax
        syscall                     ; interruption logicielle

    ; TODO: Pause avec sys_nanosleep suivi de sys_write "Fin de la pause!\n"
    ; prototype: nanosleep(   struct timespec *time1,
    ;                         struct timespec *time2)
    ;
        mov     rdi, delay1         ; argument 1
        mov     rsi, delay2         ; argument 2
        mov     rax, sys_nanosleep  ; appel système dans rax
        syscall                     ; interruption logicielle

        mov     rdi, stdout         ; argument 1
        mov     rsi, msg_fin        ; argument 2
        mov     rdx, msg_len_fin    ; argument 3
        mov     rax, sys_write      ; appel systeme dans rax
        syscall 

    
    ;
    ; Terminaison du processus
    ; prototype: _exit(int status)
    ;
        xor     rdi, rdi      ; remise a zero
        mov     rax, sys_exit ; appel systeme dans rax
        syscall               ; interruption logicielle
