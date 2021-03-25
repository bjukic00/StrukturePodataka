stup1= zeros(8,1);
stup2 = zeros(8,1);

for i = 1:8
    
    fprintf('Unesi %d. element prve matrice: ', i);
    stup1(i, 1) = input('');
    
    fprintf('Unesi %d. element druge matrice: ', i);
    stup2(i, 1) = input('');

end

if(sum(stup1)>sum(stup2))
    disp(sum(stup1));
    
else
    disp(sum(stup2));
    
end
    