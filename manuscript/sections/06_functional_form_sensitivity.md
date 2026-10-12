# 6. Functional-Form Sensitivity

## 6.1 Motivation

Section 5 reported descriptive power-law fits with R² ≥ 0.989. High R² over a narrow L range does not establish a power law; many smooth functions fit the same data with comparable R². This section compares the power-law form against three alternatives on the same data.

## 6.2 Models Considered

Four two-parameter forms were fit to S(M, L) and ρ_resid(M, L) for each M:

**Table 6.1 — Candidate functional forms.**

| Label | Form | Parameters |
|-------|------|------------|
| power | y = a · L^(−α) | (a, α) |
| reciprocal | y = a + b / L | (a, b) |
| log | y = a + b · log(L) | (a, b) |
| linear | y = a + b · L | (a, b) |

All four have two free parameters, so information-criterion comparisons are not affected by differences in model complexity. Fits used nonlinear least squares with moment-based starting values (paper3_model_comparison.py; sha256 in the data inventory). Two metrics are reported in the main text: the residual sum of squares from the full fit, and the small-sample corrected Akaike Information Criterion AICc = n · ln(RSS/n) + 2k + 2k(k+1)/(n−k−1). A leave-one-window-out cross-validation RMSE is also computed by the comparison script and stored in model_comparison_output.txt as a secondary sensitivity diagnostic.

For n = 8 and k = 2, the correction term is 2k(k+1)/(n−k−1) = 2·2·3/5 = 2.4. With only eight windows, AICc rankings are descriptive sensitivity summaries rather than decisive model-selection evidence. Models with ΔAICc < 2 are described as similarly supported within the present candidate set; the term is not used in a strict probabilistic sense.

## 6.3 Results for S(L), Fixed-Count Set

**Table 6.2 — S(L) model comparison, fixed-count set (n = 8 windows per M).**

| M | Winner | ΔAICc to 2nd | Ranking |
|---|--------|---------------|---------|
| 6 | log | 0.65 | log > reciprocal > power > linear |
| 30 | log | 1.44 | log > reciprocal > power > linear |
| 210 | log | 0.28 | log > power > reciprocal > linear |
| 2310 | power | 0.28 | power > log > reciprocal > linear |
| 30030 | log | 0.06 | log > power > reciprocal > linear |
| 510510 | power | 0.47 | power > log > reciprocal > linear |

Every ΔAICc between best and second-best is below 2. No unique winner emerges among the specific two-parameter forms considered over the present finite L range.

Among the four candidate forms, the linear-in-L model has substantially poorer AICc support for S(M, L) over this dataset, with ΔAICc between 5.35 and 8.17 relative to the leading model in every case (Table A.6). This indicates genuine curvature in S with respect to L over the observed range.

## 6.4 Results for ρ_resid(L), Fixed-Count Set

**Table 6.3 — ρ_resid(L) model comparison, fixed-count set.**

| M | Winner | ΔAICc to 2nd | Ranking |
|---|--------|---------------|---------|
| 6 | log | 7.8 | log > linear > reciprocal > power |
| 30 | log | 2.3 | log > linear > power > reciprocal |
| 210 | linear | 3.1 | linear > log > power > reciprocal |
| 2310 | linear | 5.2 | linear > log > power > reciprocal |
| 30030 | linear | 4.9 | linear > log > power > reciprocal |
| 510510 | linear | 5.8 | linear > log > power > reciprocal |

For ρ_resid, the picture differs from S. At small M (6, 30), the logarithmic form has the best AICc support, with ΔAICc of 7.8 and 2.3. At large M (210–510510), the linear form has the best support, with ΔAICc between 3.1 and 5.8. The power-law and reciprocal forms are not preferred for ρ_resid at any M in the fixed-count set.

The apparent change in preferred form with M is recorded as an exploratory observation. With only six values of M, and without an independent validation set, this pattern is suggestive but not confirmed.

## 6.5 Results on the Combined Window Set

The same comparison was applied to the combined set of 11 windows (adding W1, W2, W3 from protocol v1, whose gap counts vary by a factor of approximately 80.5 (from 10,490,870 in W1 to 844,953,415 in W3)).

**Table 6.4 — S(L) model comparison, combined set (n = 11).**

| M | Winner | ΔAICc to 2nd |
|---|--------|---------------|
| 6 | reciprocal | 1.4 |
| 30 | reciprocal | 0.7 |
| 210 | power | 0.6 |
| 2310 | power | 1.9 |
| 30030 | power | 0.7 |
| 510510 | power | 1.7 |

**Table 6.5 — ρ_resid(L) model comparison, combined set.**

| M | Winner | ΔAICc to 2nd |
|---|--------|---------------|
| 6 | reciprocal | 0.4 |
| 30 | reciprocal | 0.02 |
| 210 | log | 2.1 |
| 2310 | log | 2.6 |
| 30030 | log | 1.6 |
| 510510 | log | 0.9 |

The winner changes when n is no longer fixed. For S(L), the fixed-count set alternates between log and power; the combined set alternates between reciprocal and power. For ρ_resid, the fixed-count set gives log at small M and linear at large M; the combined set gives reciprocal at small M and log at large M.

This inconsistency across datasets is a feature of a dataset whose L-range is too narrow to separate the candidate forms. The change in the leading candidate across the fixed-count and combined datasets reinforces the sensitivity of these model rankings to window design and sample composition.

## 6.6 Summary of Section 6

Within the observed range L ∈ [19.96, 29.93]:

- No unique winner emerges among the four two-parameter forms considered for S(M, L).
- The linear-in-L form has substantially poorer AICc support for S(M, L) over this dataset.
- For ρ_resid(M, L), the preferred form in the fixed-count set changes with M (log at small M, linear at large M), but the observation is exploratory.
- The identity of the winning form is sensitive to which windows are included in the fit.

## 6.7 What This Section Does Not Establish

- **N1.** The comparison does not establish that power-law, log, or reciprocal forms are the true functional forms. It establishes only that these forms are similarly supported by the observed data.
- **N2.** The comparison does not establish that the true form lies within the four tested. Other smooth forms of comparable complexity could also fit the data over this range.
- **N3.** The comparison does not establish asymptotic behaviour. As L → ∞, the four candidate forms have qualitatively different limits. Extrapolation beyond the observed range is not justified.
- **N4.** The crossing of the α_S and α_ρ sequences reported in Section 5.4 is not explained by this section.

## 6.8 Recommendations for Future Work

To break the non-identifiability, future experiments should pursue one or more of the following:

**(a)** Extend the L range. The current set spans L ∈ [19.96, 29.93], a factor of approximately 1.50. A factor of 2 or more would begin to distinguish the four candidates. This requires windows at 10¹⁴ and beyond, which are computationally feasible with the current sieve at moderate cost.

**(b)** Add additional squarefree CRT-aligned moduli, ideally intermediate primorial products or explicitly documented products of distinct small primes.

**(c)** Independent sieve verification. Extend the independent comparison to a second high-position window, preferably near 10¹³. The internal reproductions reported in Sections 3.5 and 4.5 are encouraging but do not exclude a systematic error shared by all runs.

**(d)** Broader detrending forms. A systematic study using local polynomial regression, splines, or detrending on log log p would test whether the ABCD decomposition is robust to broader families of detrending choices.

**(e)** Joint bootstrap across windows. A joint bootstrap would provide confidence intervals for the fitted exponents and for the crossing point of the α-ladder. This is a methodological improvement, not a new empirical question.
