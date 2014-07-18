clear
files = dir('cluster*.txt');
i = 0
for file = files'
    
    A = load(file.name);
    l = length(A(:,1));
    z = A(1:l-1,1);
    y = A(1:l-1,2);
    tx = A(l,1);
    if mod(i,20)==0
        figure;
    end
    scatter(z,y,'r','x')
    hold on
    xx = linspace(0,800,100);
    b = -tx*A(1,1) + A(1,2);
    yy = linear_func(xx, b, tx);
    plot(xx,yy)
    i=i+1
end


