# Paper 3 — Frozen Protocol v1
# Date: 2026-10-09
# Author: Reddouane Berramdane
# Status: FROZEN — no edits after first run

## 1. Objective

Test whether the ABCD decomposition, S(M), and ρ_resid
are scale-invariant across five decades of log-window.

## 2. Windows (frozen)

W1 = [10^8,  3×10^8)     — test
W2 = [10^9,  3×10^9)     — new
W3 = [10^10, 3×10^10)    — confirm Paper 2
W4 = [10^11, 3×10^11)    — new
W5 = [10^12, 3×10^12)    — new
W6 = [10^13, 3×10^13)    — new

## 3. Moduli (frozen)

M ∈ {6, 30, 210, 2310, 30030, 510510, 9699690}

## 4. Method

Same code as Paper 2 (test_1e10_final_v3.cpp), with LO/HI
as runtime arguments. No logic change.
- ABCD decomposition
- Block bootstrap: 40 blocks, 1000 replicates
- Same bootstrap seeds per window

## 5. Frozen Predictions

T1: |A+X+Y+D − Cov| < 1e-6 for every row.
T2: var_between + var_within = var_e for every row.
T3: S(M) monotone increasing in M for each window.
T4: ρ_resid < 0 for every M in every window.
T5: Bootstrap 95% CIs exclude zero.
T6: S(M) at higher window ≥ S(M) at lower window (same M).
T7: A, X, Y, D vary smoothly across windows (no discontinuity).

## 6. Frozen point predictions

At M = 9699690:
- W3: S ≈ 60.4%, ρ_resid ≈ −0.010306   [confirmed Paper 2]
- W4: S ∈ [55%, 65%]
- W5: S ∈ [55%, 65%]
- W6: S ∈ [55%, 65%]

## 7. What we do NOT claim

- No strict scaling law from 6 points.
- No relation to zeta zeros.
- No direct comparison with Murray.
- No re-analysis of Paper 2 data except W3 confirmation.

## 8. Abort condition

If any of T1–T7 fails, stop and report.

## 9. Execution order

Phase 1: W1 only — verify structure before scaling.
Phase 2: W2 + W3.
Phase 3: W4.
Phase 4: W5.
Phase 5: W6.