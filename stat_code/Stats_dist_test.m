% set a seed
rng(652123)
Ndist = 1e5;
% exponential distribution variable
exp_gamma = 3.2;
% triangle distribution variables
tri_a = .3; tri_b = .8; tri_c = .7;
tri_rtf = (tri_c-tri_a)/(tri_b-tri_a);
% pareto distribution variables
par_alpha = 5.5;

% generate distributed random variables
% rand_normal = randn(Ndist,1);
% rr = 1/2*(1+erf(rand_normal/sqrt(2))); % convert normally-distributed to uniformly-distributed random values
rr = rand(Ndist,1); % uniformly distributed random values
rand_normal = sqrt(2)*erfinv(2*rr-1);
rand_uniform = rr;
rand_exp = -log(1-rr)/exp_gamma;
rand_triangle = (tri_a + sqrt(rr*(tri_b-tri_a)*(tri_c-tri_a))).*(rr <= tri_rtf) + ...
    (tri_b - sqrt((1-rr)*(tri_b-tri_a)*(tri_b-tri_c))).*(rr > tri_rtf);
rand_pareto = 1./abs(1-rr).^(1/par_alpha);


% test the matlab mean of distributions versus the analytical value
[mean(rand_normal),0] % should be 0.0
[mean(rand_uniform),.5] % should be 0.5
[mean(rand_exp),1/exp_gamma] % should be 1/gamma
[mean(rand_triangle),mean([tri_a,tri_b,tri_c])] % should be (a+b+c)/3
[mean(rand_pareto),par_alpha/(par_alpha-1)]

% test the matlab std of distributions versus the analytical value
[std(rand_normal),1] % should be 1.0
[std(rand_uniform),sqrt(1/12)] % should be sqrt(1/12)
[std(rand_exp),1/exp_gamma] % should be 1/gamma
[std(rand_triangle), sqrt((tri_a^2+tri_b^2+tri_c^2 - tri_a*tri_b - tri_a*tri_c - tri_b*tri_c)/18)]
[std(rand_pareto), sqrt(par_alpha/((par_alpha-1)^2*(par_alpha-2)))]

% test the matlab skewness of distributions versus the analytical value
[skewness(rand_normal),0] % should be 0.0
[skewness(rand_uniform),0] % should be 0.0
[skewness(rand_exp),2] % should be 2
[skewness(rand_triangle), sqrt(2)/5*(tri_a+tri_b-2*tri_c)*(2*tri_a-tri_b-tri_c)*(tri_a-2*tri_b+tri_c)/(tri_a^2+tri_b^2+tri_c^2 - tri_a*tri_b - tri_a*tri_c - tri_b*tri_c)^1.5]
[skewness(rand_pareto), 2*(1+par_alpha)/(par_alpha-3)*sqrt((par_alpha-2)/par_alpha)]

% test the matlab kurtosis of distributions versus the analytical value
[kurtosis(rand_normal)-3,0] % should be 0.0
[kurtosis(rand_uniform)-3,-1.2] % should be -1.2
[kurtosis(rand_exp)-3,6] % should be 6
[kurtosis(rand_triangle)-3,-3/5] % should be -3/5
[kurtosis(rand_pareto)-3, 6*(par_alpha^3 + par_alpha^2 - 6*par_alpha - 2)/(par_alpha*(par_alpha-3)*(par_alpha-4))]








