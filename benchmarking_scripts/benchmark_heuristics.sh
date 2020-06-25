# run from project's directory
cd datasets/
mkdir ../benchmark_results&
rm "../benchmark_results/benchmark_heuristics.txt"&
for f in ./*
do
    "../build/bin/benchmark_heuristics" "value-ordered" 0 $f >> "../benchmark_results/benchmark_heuristics.txt"
    "../build/bin/benchmark_heuristics" "density-ordered" 0 $f >> "../benchmark_results/benchmark_heuristics.txt"
done
cd ..