# massimo in un vettore versione corta
a = [1,2,3,-1,4,-9,4,0]
puts "max = #{a.max}"

idx=0
a.each_with_index do |v,i|
  idx = i if v > a[idx];
end
puts "max = #{a[idx]}"

# versione C-like
idx=0
for i in 1...a.length
  idx = i if a[i] > a[idx];
end
puts "max = #{a[idx]}"
