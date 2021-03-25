A = [1 4 6; 3 2 5; 9 2 -6];
C = A(1,:);

m = 1;
n = length(C);

D = ones(m, n);
D = D + C;

D %#ok<NOPTS>

