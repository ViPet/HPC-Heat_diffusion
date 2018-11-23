set terminal png font b018015l 14

set output "1_before.png"
plot "input_small.txt" with image

set output "1_after.png"
plot "output_small.txt" with image
