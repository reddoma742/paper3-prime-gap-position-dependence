# Appendix C — Numerical Stability of the OLS Detrending

## C.1 Purpose

The eight fixed-count windows span prime locations from 10^8
to 10^13. As the position increases, the log p range within a
window narrows, and the OLS slope β becomes statistically
imprecise. This appendix reports a direct check that the
reported quantities S(M) and ρ_resid(M) do not depend on this
imprecision.

## C.2 Method

The detrending in the main pipeline fits g_n ≈ α + β · log p_n
by ordinary least squares over the raw log p values. In the
numerical-stability check, we replace this with an algebraically
equivalent fit on a centered and scaled variable:

  p_mid = (LO + HI) / 2
  z_n   = log1p((p_n − p_mid) / p_mid)
  g_n  ≈ α' + β' · z_n

The two forms are equivalent: β = β', and the residuals e_n are
identical up to floating-point rounding. The centered form
avoids subtracting two large logarithms and preserves precision
at position 10^13.

We implemented the centered form in a separate source file
(test_multiwindow_v2.cpp; sha256 in data inventory) and re-ran
four narrow windows (P3, P4, P5, and C) with both
pipelines. For each window, S(M) and ρ_resid(M) were extracted
from the resulting CSVs and compared.

## C.3 Results

**Table C.1 — Numerical stability of S and ρ.**

| Window | Var(log p) | β_v1   | β_v2   | se(β_v2) | max|ΔS| | max|Δρ| |
|--------|-----------:|-------:|-------:|---------:|----------:|----------:|
| P3     | 5.2×10^-5  | 1.0729 | 1.0729 | 0.313    | 0         | 0         |
| P4     | 6.4×10^-7  | 1.7601 | 1.7601 | 3.116    | 0         | 0         |
| P5     | 7.5×10^-9  | −2.3099| −2.3098| 31.363   | 0         | 0         |
| C      | 6.4×10^-7  | 1.7317 | 1.7317 | 3.108    | 0         | 0         |

All differences max|ΔS| and max|Δρ| are 0.00e+00 to six
decimal places (the extraction precision of the CSV files).
The largest difference in β between the two pipelines occurs
in P5 and equals 7.1 × 10^-5, which is ~2.3 × 10^-6 of the OLS
standard error (se ≈ 31.4).

## C.4 Interpretation

Two facts follow:

1. The OLS slope β is statistically under-determined in the
   highest-position windows. In P5 the standard error of β is
   ~31, so the fitted value β = −2.31 lies within 0.1 σ of the
   expected value 1. In P4 and C the standard errors are 3.1
   and 3.1 respectively; in P3 it is 0.31. The fitted slopes lie
   within 0.3 σ of 1 in all four windows.

2. Nevertheless, the quantities S(M) and ρ_resid(M) — which
   are the reported empirical results — are numerically
   insensitive to this imprecision. The residuals differ between
   the two pipelines by at most |β − 1|·Δlog p ≈ 10^-3 in P5,
   compared with a residual standard deviation of ~27. The
   fractional effect is < 5 × 10^-5 and is therefore invisible
   at the reported precision.

## C.5 Statement

The four narrow windows examined — P3, P4, P5, and C — do not
carry any detectable numerical bias from the OLS detrending.
The reported S(M) and ρ_resid(M) values are reproduced exactly
by an independent centered-variable implementation. The
narrowness of these windows affects the identifiability of β,
not the empirical quantities of interest.
