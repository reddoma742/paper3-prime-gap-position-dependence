"""Regenerate Table A.6 (Linear vs Quadratic Detrending) for Paper 3.

Compares S_nonD from the variable-count linear CSVs (W1-W3, Section 3)
against S_nonD from the quadratic-diagnostic CSVs in
test_multiwindow_quad_v1/. Prints the Markdown table and the case count.

Usage:
    python table_a7_check.py
"""
import csv

WINDOWS = {
    "W1": ("phase_decomp_100000000_300000000.csv",
           "test_multiwindow_quad_v1/phase_decomp_quad_100000000_300000000.csv"),
    "W2": ("phase_decomp_1000000000_3000000000.csv",
           "test_multiwindow_quad_v1/phase_decomp_quad_1000000000_3000000000.csv"),
    "W3": ("phase_decomp_10000000000_30000000000.csv",
           "test_multiwindow_quad_v1/phase_decomp_quad_10000000000_30000000000.csv"),
}


def load(path):
    with open(path, encoding="utf-8-sig") as f:
        return {row["M"]: float(row["S_nonD"]) for row in csv.DictReader(f)}


def main():
    print("| Window | M | S_linear | S_quad | Difference |")
    print("|--------|---|---------:|-------:|-----------:|")
    total = 0
    worst = 0.0
    for window, (linear_path, quad_path) in WINDOWS.items():
        linear = load(linear_path)
        quad = load(quad_path)
        for mod in quad:
            diff = abs(quad[mod] - linear[mod])
            total += 1
            worst = max(worst, diff)
            print("| %s | %s | %.6f | %.6f | %g |"
                  % (window, mod, linear[mod], quad[mod], diff))
    print("cases=%d max_diff=%g" % (total, worst))


if __name__ == "__main__":
    main()
