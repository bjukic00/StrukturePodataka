A = [1 4 6; 3 2 5; 9 2 -6];
B = [9 23 87; -12 45 4; 2 3 4];

disp(A .* B);

%razlika je u tome što s .* množimo svaki element prve matrice s elementom
%druge matrice koji se nalazi na istoj poziciji, a običnim množenjem 
%zbrajamo umnoške svih elemenata n-tog retka i m-tog stupca iste pozicije
%za rezultantnu matricu gdje će se taj rezultat nalaziti na poziciji (n, m)