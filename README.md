# Sisteme-de-Operare-
PROIECT :  <br />
SimulareCabinet – Sa se implementeze un program care simuleaza activitatea dintr-un cabinet medical: vor fi create un numar dat de thread-uri pacienti care  <br />
vor astepta pentru eliberarea unor resurse reprezentand doctorii (pot fi niste structuri iar consultatia sa consiste blocarea acelei structuri si afisarea id-ului doctorului). <br />
Clientii vor ocupa resursa doctor pentru o perioada random care sa nu depaseasca o limita data. Fiecare pacient va fi generat la un interval aleator pentru o perioada data de timp.  <br />
Dupa consultatie, pacientul ısi va afisa timpul de asteptare si timpul consultatiei.  <br />

LABORATOR 4:<br />
Sarcini de laborator<br />
1. Creati un proces nou folosind fork(2) si afisati fisierele din directorul curent cu ajutorul execve(2). Din procesul initial afisati pid-ul propriu si 
 pid-ul copilului. <br />
 De exemplu:<br />
$ ./ forkls <br />
My PID =41875 , Child PID =62668<br />
Makefile collatz . c forkls . c so - lab -4. tex <br />
collatz forkls ncollatz . c <br />
Child 62668 finished <br />
2. Ipoteza Collatz spune ca plecand de la orice numar natural daca aplicam repetat urmatoarea operatie <br />
n = n/2 , daca mod (n, 2) = 0 sau 3n + 1 daca  mod (n, 2) != 0 <br />
sirul ce rezulta va atinge valoarea 1. Implementati un program care foloseste fork(2) si testeaza ipoteza generand sirul <br />
asociat unui numar dat in procesul copil. <br />
Exemplu: <br />
$ ./ collatz 24 <br />
24: 24 12 6 3 10 5 16 8 4 2 1. <br />
Child 52923 finished <br />
3. Implementati un program care sa testeze ipoteza Collatz pentru mai multe numere date. Pornind de la un singur proces parinte, este creat cate un copil care <br /> se ocupa  de un singur numar. Parintele va astepta sa termine executia fiecare copil.  Programul va demonstra acest comportament folosind functiile getpid(2) si getppid(2). <br />
  Exemplu: <br />
$ ./ ncollatz 9 16 25 36 <br />
Starting parent 6202 <br />
9: 9 28 14 7 22 11 34 17 52 26 13 40 20 10 5 16 8 4 2 1 <br />
36: 36 18 9 28 14 7 22 11 34 17 52 26 13 40 20 10 5 16 8 4 2 1 <br />
Done Parent 6202 Me 40018 <br />
Done Parent 6202 Me 30735 <br />
16: 16 8 4 2 1 <br />
25: 25 76 38 19 58 29 88 44 22 11 34 17 52 26 13 40 <br />
20 10 5 16 8 4 2 1 <br />
Done Parent 6202 Me 13388 <br />
Done Parent 6202 Me 98514 <br />
Done Parent 58543 Me 6202 <br />

