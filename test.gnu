set terminal postscript eps enhanced color font 'Helvetica,10'

set output "test.eps"

splot "./build/example.txt" u 1:2:3:4 
