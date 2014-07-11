clear
A = load('cluster_1.txt');
l = length(A(:,1));
z = A(1:l-1,1);
y = A(1:l-1,2);
tx = A(l,1)
length(z)

scatter(z,y)
hold on
xx = linspace(100,700,100);
b = tx*A(1,1) - A(1,2);
yy = linear_func(xx, b, tx);
plot(xx,yy)