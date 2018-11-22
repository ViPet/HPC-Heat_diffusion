set terminal png font b018015l 14
set output "before.png"

plot "input_small.txt" with image

set output "after.png"
plot "output_small.txt" with image
