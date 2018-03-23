# FWT
位运算每一位都是独立的，所以就一位一位做。
设
$$ A = (A_0, A_1) $$
$$ B = (B_0, B_1) $$
因此，就是求
$$ C = A \bigotimes B = (\sum_{j \bigoplus k = 0}A_j * B_k, \sum_{j \bigoplus k = 1}A_j * B_k)$$
类似于FFT，所以要构造出变换$ tf $及其逆变换$ utf $，且满足$ tf(A) * tf(B) = tf(C) $
## XOR
$$ C = (A_0 * B_0 + A_1 * B_1, A_0 * B_1 + A_1 * B_0) $$
那么
$$ tf(A) = (tf(A_0) + tf(A_1), tf(A_0) - tf(A_1)) $$
$$ utf(A) = (utf(\frac{A_0 + A_1}{2}, utf(\frac{A_0 - A_1}{2})) $$
即可满足
## AND
$$ C = (A_0 * B_0 + A_0 * B_1 + A_1 * B_0, A_1 * B_1) $$
$$ tf(A) = (tf(A_0) + tf(A_1), tf(A_1)) $$
$$ utf(A) = (utf(A_0) - utf(A_1), utf(A_1)) $$
## OR
$$ C = (A_0 * B_0, A_0 * B_1 + A_1 * B_0 + A_1 * B_1) $$
$$ tf(A) = (tf(A_0), tf(A_1) + tf(A_0)) $$
$$ utf(A) = (utf(A_0), utf(A_1) - utf(A_0)) $$

