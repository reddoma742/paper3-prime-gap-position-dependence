# Paper 3 — Exploratory Protocol v2
# Date: 2026-10-09
# Author: Reddouane Berramdane
# Status: versioned (post hoc) — supersedes protocol v1 after T6 falsification
# Reference: model_comparison_output.txt (sha256 pending)

## 0. Purpose of this document

Protocol v1 (paper3_protocol_v1.md) contained seven frozen predictions (T1–T7).
The first three windows W1, W2, W3 were run under v1.
**T6 was falsified.** Of the remaining predictions, T1–T5 passed
and T7 was reclassified as descriptive, because protocol v1 did
not define a numerical smoothness criterion for it.

This document:
  (a) records the falsification and its scope;
  (b) records the post-falsification exploratory findings;
  (c) records the claims that Paper 3 will and will not make;
  (d) defines what counts as a "result" for this paper.

This document was versioned after the diagnostics were run (post hoc).
It records the results; the diagnostics are exploratory, not preregistered.

---

## 1. Frozen Protocol v1 — outcome summary

| ID  | Prediction                                       | Outcome  | Evidence                              |
|-----|--------------------------------------------------|----------|---------------------------------------|
| T1  | \|A+X+Y+D − Cov\| < 1e-6 every row                | PASS     | max 2.1e-14 across 5 windows          |
| T2  | var_between + var_within = var_e every row        | PASS     | exact to machine precision            |
| T3  | S(M) monotone increasing in M for each window     | PASS     | 6 values × 5 windows                  |
| T4  | ρ_resid < 0 every M every window                  | PASS     | 30/30 negative                        |
| T5  | Bootstrap 95% CIs exclude zero                    | PASS     | 30/30 CIs strictly negative           |
| T6  | S(M) at higher window ≥ S(M) at lower window      | **FAIL** | 30/30 ordered pairs decrease          |
| T7  | A, X, Y, D vary smoothly across windows           | Descriptive | protocol v1 did not define a numerical smoothness criterion |

**T6 is falsified.** The preregistered direction was wrong.

Statement for the paper:
> The preregistered prediction that S(M) would increase with window
> position was falsified. In windows with comparable gap counts,
> S(M) instead decreases systematically with log p over the observed
> range [19.96, 29.93].

---

## 2. Post-falsification diagnostics (exploratory)

### 2.1 Diagnostic — quadratic detrending

Question: is the decrease in S an artifact of the linear-only
detrending form g ≈ a + b·log p?

Method: reran W1, W2, W3 with the quadratic form
        g ≈ a + b·u + c·u²,  u = log p − 0.5·(log LO + log HI).

Result: S_nonD identical to six decimal places in all 19 cases (6 in W1, 6 in W2, 7 in W3).
        Quadratic coefficient |c| ≤ 5×10⁻³, correction c·u² ≤ 2×10⁻³.

Conclusion: the decrease is **not** an artifact of linear detrending.
            Robustness to one specific smooth-curvature alternative.

Caveat (from referee-style review):
> The quadratic diagnostic addresses one specified smooth trend
> alternative; it does not establish invariance under arbitrary
> detrending choices.

### 2.2 Diagnostic — decoupling n from window position

Question: is the decrease driven by n (gap count) or by log p (position)?

Method: five primary windows P1–P5 at fixed n ≈ 10⁸ gaps,
        spanning log p center from 21.30 to 29.93.
        Three auxiliary fixed-n points (A, B, C) extend the
        span to L ∈ [19.96, 29.93]. The complete fixed-n set
        analysed in the paper is {A, P1, B, P2, P3, C, P4, P5}.

Result: S decreases by ~34% across the range, with n held fixed.

Conclusion: the decrease is **associated with window position**,
            not with gap count in the sense of sample size.

Caveat:
> Holding the observed gap count approximately fixed removes the
> most direct sample-size confounding. The remaining systematic
> trend is associated with window position, represented here by
> log p. Other window properties (width in x, candidate count)
> also vary and are not independently controlled.

Among the eight fixed-count windows, two nested pairs appear
at closely matched positions: B (L = 23.1261) is a strict
subset of P2 (L = 23.1296), and C (L = 27.6324) contains
P4 (L = 27.6324). The paired windows share prime intervals
and are therefore not independent replications. They serve
as a boundary-sensitivity check in the main text (§4.5).

---

## 3. Post-falsification model comparison (exploratory)

### 3.1 Method

Four 2-parameter models were fit to S(M, L) and ρ_resid(M, L):

    power    y = a · L^(−α)
    reciprocal  y = a + b / L
    log      y = a + b · log(L)
    linear   y = a + b · L

Metrics: RSS, AICc (n small), leave-one-out RMSE.
A leave-one-window-out cross-validation root-mean-squared
error (LOO-RMSE) is computed by the comparison script and
stored in model_comparison_output.txt as a secondary
sensitivity diagnostic. It is not reproduced in the main
text or in Appendix A; the main-text model comparisons use
RSS and AICc only.
Data: fixed-n set (n=8 points per M) and all-windows set (n=11).

### 3.2 Result — S(L)

Fixed-n set, ΔAICc between best and second-best model, per M:

| M       | winner  | ΔAICc |
|---------|---------|-------|
| 6       | log     | 0.65  |
| 30      | log     | 1.44  |
| 210     | log     | 0.28  |
| 2310    | power   | 0.28  |
| 30030   | log     | 0.06  |
| 510510  | power   | 0.47  |

**All ΔAICc < 2. No functional form is statistically distinguished.**

Linear-only is rejected with ΔAICc ≈ 7–8 in every case.
So S(L) is curved in L, but the specific curve is not identifiable
within the observed L range (factor ≈ 1.5).

### 3.3 Result — ρ_resid(L)

Fixed-n set:

| M       | winner  | ΔAICc |
|---------|---------|-------|
| 6       | log     | 7.8   |
| 30      | log     | 2.3   |
| 210     | linear  | 3.1   |
| 2310    | linear  | 5.2   |
| 30030   | linear  | 4.9   |
| 510510  | linear  | 5.8   |

At small M (6, 30): curved (log) wins with ΔAICc ≈ 2–8.
At large M (210–510510): linear wins with ΔAICc ≈ 3–6.

**The functional form of ρ_resid(L) appears to depend on M.**
This is an exploratory observation, not a confirmed law.
It requires independent validation before any claim is made.

### 3.4 Result — all-windows set (11 points, includes W1–W3)

For S(L): inverse wins at M=6, 30; power wins at M=210–510510.
For ρ(L): inverse wins at M=6, 30; log wins at M=210–510510.

Winner changes with the dataset. **This confirms non-identifiability.**

---

## 4. Algebraic relations (not independent findings)

The following relations hold identically in the code and are
NOT presented as separate empirical laws:

    Cov_1(M, L)   =  ρ_1(L) · Var(e)(L)
    S(M, L)       =  1 − ρ_resid(M, L) / ρ_1(L)    [exact in code]

Empirical observation across the fixed-n set:
    Cov_1 / L ≈ −0.466  (scatter 0.4%, five points)
    Var(e)   ≈ L^{2.19}  (fitted exponent)
    ρ_1      ≈ L^{−1.19} (fitted exponent)

Because Cov_1 = ρ_1 · Var(e), the three statements are algebraically
redundant. Only two are independent, and even those are fitted
power laws whose functional form is not distinguished by the data
(see §3).

Statement for the paper:
> The approximate linearity of Cov_1 in log p is consistent with the
> observed product of the variance and correlation scalings. It is
> not presented as an independent scaling law.

---

## 5. Frozen claims for Paper 3

The following claims **will** be made in Paper 3:

**C1.** The preregistered prediction T6 is falsified.
      In fixed-count windows, S(M) decreases systematically with
      log p over [19.96, 29.93].

**C2.** The decrease is not explained by linear-detrending artifact;
      a quadratic detrending leaves S unchanged to six decimals.

**C3.** The decrease is associated with window position, not gap count.
      Across eight fixed-n windows, S drops by ~34% while n varies by
      5.1%.

**C4.** Within the observed range, the functional form of S(L) is not
      identifiable: power-law, logarithmic, and reciprocal
      descriptions are similarly supported by the data (ΔAICc < 2).

**C5.** The residual correlation ρ_resid(M, L) remains strictly
      negative across all 30 observations and all 30 bootstrap
      confidence intervals exclude zero.

**C6.** The functional form of ρ_resid(L) changes with M in the
      fixed-n data (log at M = 6, 30; linear at M ≥ 210), but this
      is exploratory and requires independent validation.

**C7.** ABCD closure and the variance split hold to machine precision
      in every window (max deviation ≤ 2.1e-14).

**C8.** The W3 window reproduces Paper 2 exactly:
      S(M=9699690) = 0.604431, ρ_resid = −0.010306.
      The paired fixed-count windows (B/P2, C/P4) are nested and
      provide a boundary-sensitivity check, not an independent
      replication.

The following claims **will not** be made:

**N1.** No claim that S ∝ (log p)^(−α) as an asymptotic law.
**N2.** No claim of a specific monotone law α(M).
**N3.** No claim of a strict scaling law derived from six points.
**N4.** No comparison with Montgomery–Odlyzko, GPY, Maynard,
      or Lemke Oliver–Soundararajan.
**N5.** No claim relating to zeta zeros.
**N6.** No claim of universality beyond the observed window range.

---

## 6. Structure of Paper 3

| Section | Content |
|---------|---------|
| 1 | Introduction — Paper 1, Paper 2, the scaling question |
| 2 | Method — ABCD decomposition, S(M), window definitions |
| 3 | Preregistered tests and falsification of T6 |
| 4 | Post-falsification diagnostic: fixed-n windows (P1–P5, A, B, C) |
| 5 | Empirical vanishing of S and ρ_resid with window position |
| 6 | Model comparison: non-identifiability within the observed range |
| 7 | Constraints and what we do not claim |
| 8 | Outlook and open questions |

---

## 7. Data inventory (versioned)

All CSVs referenced in this protocol are stored with their
sha256 in `paper3_data_inventory.txt`. The set is:

Fixed-n windows (n ≈ 10⁸):
  A  = [10^8,   2.18×10^9)      logp = 19.9616
  P1 = [10^9,   3.145×10^9)     logp = 21.2962
  B  = [10^10,  1.222×10^10)    logp = 23.1261
  P2 = [10^10,  1.2305×10^10)   logp = 23.1296
  P3 = [10^11,  1.02535×10^11)  logp = 25.3410
  C  = [10^12,  1.00277×10^12)  logp = 27.6324
  P4 = [10^12,  1.002765×10^12) logp = 27.6324
  P5 = [10^13,  1.0002995×10^13) logp = 29.9338

Variable-n windows (from protocol v1):
  W1 = [10^8,   3×10^8)          logp = 18.9700
  W2 = [10^9,   3×10^9)          logp = 21.2726
  W3 = [10^10,  3×10^10)         logp = 23.5752

Note: A, P1, B, P2, P3, C, P4, P5 all have n ≈ 10⁸ ± 0.6%.
      W1, W2, W3 vary in n by factors of ~10.

---

## 8. Tools

Source:      test_multiwindow_v1.cpp  (sha256 recorded in inventory)
Binary:      test_multiwindow_v1.exe  (same)
Analysis:    paper3_model_comparison.py
             (sha256 = fd25a2186421d4f97e372449ea7e59045e5b62b29df61edb70ac570c23684fb7)
Output:      model_comparison_output.txt
             (sha256 = ac2044588cf767f7d15189c3fb4857d9e2e366ed4b1173cae85d1cfd9994bfa5)

---

## 9. Version statement

This protocol is versioned (post hoc) as of 2026-10-12.

Any subsequent change to the paper's claims must be documented in a
new version of this file with a changelog entry explaining the
reason and identifying the section affected.

The paper is written to match this protocol, not the reverse.

---

---

## 10. Changelog

- 2026-10-10: Applied updates to match final paper:
  * §3.1: "inverse" renamed "reciprocal".
  * §1: T7 outcome changed from PASS to Descriptive.
  * §2.2: added note on nested pairs B ⊂ P2, C ⊃ P4.
  * §5 C4: "inverse-power" renamed "reciprocal".
  * §5 C7: clarified that paired windows are not independent.
  * §2.9: LOO-RMSE wording updated.
  The scientific content of the claims is unchanged.

- 2026-10-11: Independent sieve verification at 10^12 added:
  * §8: recorded sha256 of sieve_verify.py and sieve_verify_1e12.log.
  * §1, §2.2, §3.1, §5 C3: consistency corrections applied.
  * Reference: Appendix B and paper3_data_inventory.txt §7.

END OF PROTOCOL v2