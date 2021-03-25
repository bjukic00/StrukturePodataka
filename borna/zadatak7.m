k = [-30, 50, 15 + 3j, 15-3j];
y = poly(k);

t = -30:0.01:50;

y1 = polyval(y,t);
y2 = -1 * y1;

xlabel('x-os');
ylabel('y-os');
title('Naslov');

plot(y1, 'y', 'LineWidth', 2);
hold on;
plot(y2, 'r:', 'LineWidth', 0.5);