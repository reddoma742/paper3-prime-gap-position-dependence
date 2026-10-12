# Appendix A — Extended Tables

## A.1 Descriptive Power-Law Fits for S(M, L)

Referenced from Section 5.4. Fitted exponents α_S(M) are
descriptive summaries over the observed range L ∈ [19.96, 29.93];
they are not claimed as asymptotic laws.

**Table A.1 — Descriptive power-law fits S(M, L) = a · L^(−α).**

| M | a | α | R² |
|---|---|---|-----|
| 6 | 0.6143 | 1.170 | 0.994 |
| 30 | 5.110 | 1.177 | 0.995 |
| 210 | 2.932 | 0.753 | 0.997 |
| 2310 | 2.275 | 0.564 | 0.998 |
| 30030 | 2.016 | 0.458 | 0.999 |
| 510510 | 1.831 | 0.385 | 0.999 |

## A.2 Descriptive Power-Law Fits for |ρ_resid(M, L)|

Referenced from Section 5.4. Same caveat as A.1.

\needspace{12\baselineskip}

**Table A.2 — Descriptive power-law fits |ρ_resid(M, L)| = a · L^(−α).**

| M | a | α | R² |
|---|---|---|-----|
| 6 | 0.8412 | 1.117 | 0.989 |
| 30 | 0.4869 | 0.980 | 0.995 |
| 210 | 0.2973 | 0.881 | 0.998 |
| 2310 | 0.2114 | 0.824 | 0.999 |
| 30030 | 0.1556 | 0.775 | 0.999 |
| 510510 | 0.1231 | 0.742 | 0.999 |

## A.3 Normalised Ratios R(M, L)

Referenced from Section 5.5. The normalisation R(M, L) =
S(M, L) / S(M, A) tests whether the position dependence is
universal across moduli. No exact collapse is observed.

\needspace{12\baselineskip}

**Table A.3 — Normalised ratios R(M, L).**

| Window | L | R(6) | R(30) | R(210) | R(2310) | R(30030) | R(510510) |
|--------|---|------|-------|--------|---------|----------|-----------|
| A | 19.96 | 1.000 | 1.000 | 1.000 | 1.000 | 1.000 | 1.000 |
| P1 | 21.30 | 0.958 | 0.958 | 0.973 | 0.979 | 0.982 | 0.985 |
| B | 23.13 | 0.865 | 0.860 | 0.905 | 0.925 | 0.938 | 0.948 |
| P2 | 23.13 | 0.864 | 0.859 | 0.905 | 0.925 | 0.938 | 0.947 |
| P3 | 25.34 | 0.773 | 0.768 | 0.839 | 0.876 | 0.896 | 0.912 |
| C | 27.63 | 0.688 | 0.692 | 0.791 | 0.839 | 0.868 | 0.887 |
| P4 | 27.63 | 0.688 | 0.692 | 0.791 | 0.839 | 0.868 | 0.887 |
| P5 | 29.93 | 0.635 | 0.625 | 0.742 | 0.799 | 0.831 | 0.857 |

## A.4 Model Comparison on the Combined Window Set

Referenced from Section 6.5. The combined set includes W1,
W2, W3 from protocol v1 whose gap counts vary by a factor of
approximately 80.5 (from 10,490,870 in W1 to 844,953,415 in W3).

**Table A.4 — S(L) model comparison, combined set (n = 11).**

| M | Winner | ΔAICc to 2nd |
|---|--------|---------------|
| 6 | reciprocal | 1.4 |
| 30 | reciprocal | 0.7 |
| 210 | power | 0.6 |
| 2310 | power | 1.9 |
| 30030 | power | 0.7 |
| 510510 | power | 1.7 |

\needspace{12\baselineskip}

**Table A.5 — ρ_resid(L) model comparison, combined set.**

| M | Winner | ΔAICc to 2nd |
|---|--------|---------------|
| 6 | reciprocal | 0.4 |
| 30 | reciprocal | 0.02 |
| 210 | log | 2.1 |
| 2310 | log | 2.6 |
| 30030 | log | 1.6 |
| 510510 | log | 0.9 |

## A.5 Full ΔAICc Table

Referenced from Section 6.3. The main text of Section 6.3
reports only the difference between the leading and the
second-ranked model at each modulus. Table A.6 lists the
full ΔAICc for all four candidate models at each modulus,
extracted from model_comparison_output.txt (PRIMARY fixed-n
set, quantity S). The comparison script labels the reciprocal
model "inverse"; the paper uses "reciprocal" for the same
y = a + b / L form.

**Table A.6 — Full ΔAICc, S(L) on the fixed-n set (n = 8).**

| M | power | reciprocal | log | linear |
|---|------:|-----------:|----:|-------:|
| 6 | 1.753 | 0.651 | 0.000 | 6.804 |
| 30 | 2.933 | 1.440 | 0.000 | 8.172 |
| 210 | 0.280 | 1.856 | 0.000 | 7.168 |
| 2310 | 0.000 | 2.549 | 0.281 | 7.388 |
| 30030 | 0.060 | 2.591 | 0.000 | 5.350 |
| 510510 | 0.000 | 2.940 | 0.465 | 7.030 |

## A.6 Linear vs Quadratic Detrending

Referenced from C2. Table A.7 compares S_linear (from the
variable-count CSVs of Section 3) and S_quad (from the
quadratic-diagnostic CSVs) for each window and modulus. All
differences are 0 to the six decimal places of the CSV
extraction precision, hence below 10^-6.

\needspace{25\baselineskip}

**Table A.7 — S_linear vs S_quad per window and modulus.**

| Window | M | S_linear | S_quad | Difference |
|--------|---|---------:|-------:|-----------:|
| W1 | 6 | 0.019670 | 0.019670 | 0 |
| W1 | 30 | 0.162635 | 0.162635 | 0 |
| W1 | 210 | 0.323706 | 0.323706 | 0 |
| W1 | 2310 | 0.437143 | 0.437143 | 0 |
| W1 | 30030 | 0.525091 | 0.525091 | 0 |
| W1 | 510510 | 0.592241 | 0.592241 | 0 |
| W2 | 6 | 0.017458 | 0.017458 | 0 |
| W2 | 30 | 0.142455 | 0.142455 | 0 |
| W2 | 210 | 0.296759 | 0.296759 | 0 |
| W2 | 2310 | 0.410226 | 0.410226 | 0 |
| W2 | 30030 | 0.500907 | 0.500907 | 0 |
| W2 | 510510 | 0.568517 | 0.568517 | 0 |
| W3 | 6 | 0.015317 | 0.015317 | 0 |
| W3 | 30 | 0.125040 | 0.125040 | 0 |
| W3 | 210 | 0.272725 | 0.272725 | 0 |
| W3 | 2310 | 0.385438 | 0.385438 | 0 |
| W3 | 30030 | 0.475868 | 0.475868 | 0 |
| W3 | 510510 | 0.544106 | 0.544106 | 0 |
| W3 | 9699690 | 0.604431 | 0.604431 | 0 |
