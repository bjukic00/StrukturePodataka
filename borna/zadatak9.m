A = [1 2 8 9; 4 5 1 0];

pol1 = A(1,:);
pol2 = A(2,:);

t = 0:0.1:20;

x = polyval(pol1,t);
y = polyval(pol2,t);

plot(t, x, 'r', t, y, 'g');

title('naslov');
xlabel('x-os');
ylabel('y-os');
