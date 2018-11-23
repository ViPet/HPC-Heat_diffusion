set terminal png font b018015l 14

set output "2_before.png"
plot "input_medium.txt" with image

set output "2_after.png"
plot "output_medium.txt" with image
