t = 0:0.05:15;
f = 1.5;

y = cos(2 * pi * f * t);

disp(y);

plot(t, y, 'r');