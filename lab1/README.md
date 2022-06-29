# Lab 1 - Kompilacja jądra i wywołania systemowe
Celem ćwiczenia jest zapoznanie się z mechanizmem realizacji wywołań
systemowych (ang. system calls, tłumaczone również jako funkcje
systemowe). W trakcie ćwiczenia należy dodać do systemu nowe wywołanie
systemowe, zwracające numer (indeks) procesu w tablicy procesów. Do
przeprowadzenia ćwiczenia niezbędny jest własny obraz systemu MInix 2.0
(minix203.img) uruchamialny w maszynie wirtualnej.

## Zadanie
Dodaj do systemu nowe wywołanie systemowe GETPROCNR, obsługiwane
wewnątrz modułu MM i zwracające numer procesu w tablicy procesów dla
procesu, którego identyfikator (PID) będzie argumentem tego wywołania.
