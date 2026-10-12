# 7. Claims and Non-Claims

## 7.1 Purpose

Sections 3–6 established a set of empirical facts about the phase-decomposed covariance of prime gaps, together with a demonstrated limitation: the functional form of the position dependence is not identified by the available data. This section states explicitly what the paper claims and what it does not. The separation matters because the observed trends are strong, systematic, and reproducible, yet they are confined to a narrow range of L and their interpretation requires care.

## 7.2 Claims We Make

**C1. Falsification of T6.** The preregistered prediction T6 (that S(M) at higher windows would be greater than or equal to S(M) at lower windows, for the same M) is falsified. S(M) decreases systematically from W1 to W3 for every M tested.

- Support: Table 3.2; all adjacent window pairs decrease, and all 18 pairwise window–modulus comparisons decrease
- Scope: W1 = [10⁸, 3×10⁸), W2 = [10⁹, 3×10⁹), W3 = [10¹⁰, 3×10¹⁰)

**C2. Robustness to linear detrending.** The decrease of S(M) is not an artifact of the linear form of the global detrending. Re-running the analysis with a quadratic detrending g ≈ a + b·z + c·z² leaves S unchanged to six decimal places in all 19 cases (6 in W1, 6 in W2, 7 in W3). See Table A.6 for the per-window, per-modulus comparison.

- Scope: Robust to one specific smooth-curvature alternative; not a proof of invariance under arbitrary detrending choices.

**C3. Position dependence with gap count held approximately fixed.** Across eight windows at n ≈ 10⁸ ± 5.1%, S(M) and |ρ_resid(M)| decrease monotonically with L = log p for every M tested. The total relative decrease is 14–37% for S and 25–36% for ρ_resid, depending on M.

- Scope: n ≈ 10⁸; L ∈ [19.96, 29.93]; six moduli.

**C4. Strong disfavouring of the sample-size hypothesis.** The decrease of S(M) is not attributable to a pure sample-size effect, because n varies by less than 5.1% across the eight fixed-count windows while S varies by 14–37%.

- Scope: Empirical, not causal; see §4.7 for caveats on window width in x and on the proxy role of L.

**C5. Sensitivity of functional form.** For S(M, L), the logarithmic form is within ΔAICc < 2 of the leading model at every modulus, the power-law form at five of six, and the reciprocal form at three of six. The linear-in-L form is substantially poorer, with ΔAICc between 5.35 and 8.17 relative to the leading model. For ρ_resid(M, L), the preferred form in the fixed-count set changes with M, but the observation is exploratory.

- Scope: Four two-parameter forms over L ∈ [19.96, 29.93]; n = 8 windows per M.

**C6. Persistence of negative residual correlation.** For every M in every window analysed, ρ_resid < 0, and every within-window block-bootstrap 95% confidence interval excludes zero.

- Scope: 48/48 values negative in the fixed-count set; all 19 within-window bootstrap intervals in the W-set are strictly negative (6 in W1, 6 in W2, 7 in W3). Intervals are marginal within-window; they are not treated as independent tests.

**C7. Internal consistency and reproducibility.** The ABCD decomposition closes to machine precision in every window (max |A+X+Y+D − Cov| ≤ 7.1×10⁻¹⁴). The variance split holds to machine precision. The window W3 reproduces Paper 2 exactly at M = 9699690 (S = 60.4431%, ρ_resid = −0.010306). Two pairs of fixed-count windows at duplicated positions (B/P2, C/P4) differ by at most 3.7 × 10^-4 in S (at M = 510510) and 1.7 × 10^-5 in ρ_resid. These differences exceed the last printed digit for the larger-modulus S values but remain ~200× smaller than the total A-to-P5 decrease reported in Section 5.

## 7.3 Claims We Do Not Make

**N1. No asymptotic scaling law.** We do not claim that S(M, L) ~ L^(−α(M)) or any other specific form is the correct asymptotic behaviour. The fitted exponents reported in Section 5.4 are descriptive summaries over the observed L range. As L → ∞, the four candidate models of Section 6 have qualitatively different limits, and the data cannot distinguish them.

**N2. No validated exponent ladder.** The fitted exponent α_S(M) is approximately decreasing in M, with a small non-monotonicity at M = 6 and M = 30 (α_S = 1.170 and 1.177 respectively), while α_ρ(M) appears monotone decreasing over the observed modulus ladder, but these are descriptive quantities from a single dataset and have not been independently validated. The crossing of the two sequences between M = 30 and M = 210 is an empirical feature of the selected fit, not a confirmed law.

**N3. No universality of the L-dependence.** The normalised ratios R(M, L) = S(M, L)/S(M, A) do not collapse onto a single curve. The shape of S(M, L) depends on M, and no simple rescaling eliminates this dependence over the observed range.

**N4. No comparison with analytic number theory.** We do not derive our results from Montgomery–Odlyzko pair correlation, the Goldston–Pintz–Yıldırım small-gap results, the Maynard bounded-gap theorem, or the Lemke Oliver–Soundararajan residue-pair biases. The Lemke Oliver–Soundararajan study of consecutive-prime residue-pair biases [9] is the closest contextual framework to our residue-class conditioning, but to our knowledge, it does not provide a quantitative prediction for the specific non-D covariance share studied here. We do not claim a comparison that the present data cannot support.

**N5. No connection to zeta zeros.** We make no claim about the distribution of non-trivial zeros of the Riemann zeta function. The prime-gap data analysed here are strictly finite-range and empirical.

**N6. No claim beyond the observed range.** No claim is made about the sign of ρ_resid, the form of S(M, L), or the rate of decay at positions beyond the windows examined here.

**N7. No test of Cramér's model.** The present paper does not test Cramér's heuristic model directly, nor does it evaluate the model's ability to reproduce the observed position dependence.

**N8. No statistical comparison with Papers 1 and 2 beyond reproduction.** Paper 1 established persistent negative lag-one dependence up to 10⁹; Paper 2 established the ABCD decomposition at a single window. Paper 3 extends these results to new windows. Beyond the direct reproduction of Paper 2's central number (C7), no statistical comparison between papers is offered.

## 7.4 Relation to Papers 1 and 2

Paper 1 (Zenodo DOI 10.5281/zenodo.23162269) established persistent negative lag-one dependence in locally detrended prime-gap windows up to N = 10⁹. The present work extends the analysis to higher positions (up to 10¹³) and to a larger family of moduli, and confirms that the negative residual correlation persists across the extended range (C6).

Paper 2 (Zenodo DOI 10.5281/zenodo.23222536) introduced the ABCD decomposition and applied it to the single window [10¹⁰, 3×10¹⁰) with 844,953,415 gaps. The central number of Paper 2 — S = 60.4% at M = 9699690 — is reproduced exactly in W3 of the present work (C7). This identity verifies that the pipeline of Paper 3 is a faithful extension of Paper 2's code.

Paper 3 does not supersede Papers 1 and 2; it extends them.

## 7.5 Methodological Caveats

**(a) Detrending.** We detrend with a global polynomial in log p of degree at most two. Other smooth forms (splines, local regression) may yield different residual distributions. The quadratic diagnostic (C2) addresses one specific alternative to linear detrending and does not establish invariance under arbitrary detrending choices.

**(b) Sieve and base primes.** Gap enumeration uses an odd-only segmented sieve with base primes up to ⌈√HI⌉ + 100. The small-scale validations (10⁶, 10⁷) reproduce known prime counts exactly. An independent enumeration check was completed at 10¹² (Appendix B), and a numerical-stability check of the OLS detrending is reported in Appendix C. A second independent high-position enumeration check near 10¹³ remains desirable.

**(c) Bootstrap.** The block bootstrap (40 blocks, 1000 replicates, seed base 20261006 + k·1000) provides confidence intervals for ρ_resid within a single window. It does not provide confidence intervals for the fitted exponents α(M), which would require a joint bootstrap across windows. The α values are therefore reported as descriptive only, consistent with C5 and N1.

**(d) Modulus eligibility.** Modulus eligibility was determined dynamically by the minimum class count over all residues in the window, with a modulus excluded when its smallest non-empty class count is below 50 and classes between 50 and 99 flagged diagnostic. This rule differs from the fixed seven-modulus list used in Paper 2.

## 7.6 Summary

Paper 3 establishes seven claims (C1–C7) and explicitly declines eight (N1–N8). The claims concern falsification of a preregistered prediction, a fixed-count diagnostic that strongly disfavours a pure sample-size explanation, an empirical description of the position dependence, a sensitivity analysis of the functional form, and internal consistency checks. The paper does not advance a theoretical model, does not connect to analytic number theory, and does not claim asymptotic behaviour.
