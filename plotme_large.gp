set terminal png font b018015l 14

set output "3_before.png"
plot "input_large.txt" with image

set output "3_after.png"
plot "output_large.txt" with image
