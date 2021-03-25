disp('Unesi velicinu redne matrice: ');
N = input('');

mat = zeros(1, N);

for i = 1:N
   
    fprintf('Unesi %d. element matrice: ', i);
    mat = input('');
end
mat_sr = mean(mat);

dev = sqrt((1/(N-1)) * (mat - mat_sr));

disp(dev);
