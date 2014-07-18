clear
files=dir('cluster*.txt');
i=1;
for file = files'
   A = load(file.name);
   l = length(A(:,1));
   z = A(1:l-1,1);
   y = A(1:l-1,2);
   tx = A(l,1);
   sigma = 0.05;
   dof = l-1-2;
   b = -tx*A(1,1) + A(1,2);
   chi2(i) = sum(((y-(tx*z+b))/sigma).^2);
   chi2dof = chi2/dof;
   i=i+1;   
end

hist(chi2dof)