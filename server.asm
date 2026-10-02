BITS 32

; Assemble as ELF32 and link for Linux i386. The server listens on port 8080.

%define SYS_EXIT       1
%define SYS_READ       3
%define SYS_WRITE      4
%define SYS_CLOSE      6
%define SYS_SOCKETCALL 102

%define SOCKET         1
%define BIND           2
%define LISTEN         4
%define ACCEPT         5

%define AF_INET        2
%define SOCK_STREAM    1
%define BACKLOG        5
%define BUF_SIZE       1024

section .data
sockaddr:
    dw AF_INET
    dw 0x901F                 ; Port 8080 in network byte order
    dd 0                      ; Bind to any local IPv4 address
    times 8 db 0
sockaddr_len equ $ - sockaddr

socket_args  dd AF_INET, SOCK_STREAM, 0
bind_args    dd 0, sockaddr, sockaddr_len
listen_args  dd 0, BACKLOG
accept_args  dd 0, 0, 0
listen_sock  dd -1

response:
    db 'HTTP/1.1 200 OK', 13, 10
    db 'Content-Type: text/plain; charset=utf-8', 13, 10
    db 'Content-Length: 15', 13, 10
    db 'Connection: close', 13, 10, 13, 10
    db 'Hello, World!', 13, 10
response_len equ $ - response

error_message db 'server.asm: system call failed', 10
error_message_len equ $ - error_message

section .bss
conn_sock   resd 1
buf         resb BUF_SIZE

section .text
global _start

_start:
    ; Create an IPv4 TCP socket.
    mov eax, SYS_SOCKETCALL
    mov ebx, SOCKET
    mov ecx, socket_args
    int 0x80
    test eax, eax
    js fatal
    mov [listen_sock], eax
    mov [bind_args], eax
    mov [listen_args], eax
    mov [accept_args], eax

    ; Bind to port 8080 and start listening.
    mov eax, SYS_SOCKETCALL
    mov ebx, BIND
    mov ecx, bind_args
    int 0x80
    test eax, eax
    js fatal

    mov eax, SYS_SOCKETCALL
    mov ebx, LISTEN
    mov ecx, listen_args
    int 0x80
    test eax, eax
    js fatal

accept_loop:
    mov eax, SYS_SOCKETCALL
    mov ebx, ACCEPT
    mov ecx, accept_args
    int 0x80
    test eax, eax
    js fatal
    mov [conn_sock], eax

    ; Read a request before sending the fixed response.
    mov eax, SYS_READ
    mov ebx, [conn_sock]
    mov ecx, buf
    mov edx, BUF_SIZE
    int 0x80
    test eax, eax
    jle close_client

    mov esi, response
    mov edi, response_len
write_response:
    mov eax, SYS_WRITE
    mov ebx, [conn_sock]
    mov ecx, esi
    mov edx, edi
    int 0x80
    test eax, eax
    jle close_client
    add esi, eax
    sub edi, eax
    jnz write_response

close_client:
    mov eax, SYS_CLOSE
    mov ebx, [conn_sock]
    int 0x80
    jmp accept_loop

fatal:
    mov eax, SYS_WRITE
    mov ebx, 2
    mov ecx, error_message
    mov edx, error_message_len
    int 0x80

    cmp dword [listen_sock], -1
    je exit_program
    mov eax, SYS_CLOSE
    mov ebx, [listen_sock]
    int 0x80

exit_program:
    mov eax, SYS_EXIT
    mov ebx, 1
    int 0x80
