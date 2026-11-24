from statistics import median
from time import perf_counter_ns

def median_call_us(run, warmup=10, repeats=100):
    for _ in range(warmup):
        run()

    samples = []
    for _ in range(repeats):
        start = perf_counter_ns()
        run()
        samples.append(perf_counter_ns() - start)

    return median(samples) / 1_000