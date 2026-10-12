#!/usr/bin/env python3
# paper3_model_comparison.py
#
# Paper 3 — Model comparison for S(M,L) and rho_resid(M,L)
# across the fixed-n window set (n ~ 10^8).
#
# Four 2-parameter models compared:
#   power    y = a * L^(-alpha)
#   inverse  y = a + b / L
#   log      y = a + b * log(L)
#   linear   y = a + b * L
#
# Metrics:
#   RSS       residual sum of squares (full fit)
#   AICc      small-sample corrected Akaike Information Criterion
#   LOO-RMSE  leave-one-out cross-validation root mean squared error
#
# Requires: numpy, scipy
# Usage:    python paper3_model_comparison.py
#
# Author: Reddouane Berramdane (Paper 3 analysis)

import csv
import os
import numpy as np
from scipy.optimize import curve_fit

# --------------------------------------------------------------------------
# File registry — edit if your filenames differ
# --------------------------------------------------------------------------

FIXED_N_FILES = {
    'A' : 'phase_decomp_100000000_2180000000.csv',
    'P1': 'phase_decomp_1000000000_3145000000.csv',
    'B' : 'phase_decomp_10000000000_12220000000.csv',
    'P2': 'phase_decomp_10000000000_12305000000.csv',
    'P3': 'phase_decomp_100000000000_102535000000.csv',
    'C' : 'phase_decomp_1000000000000_1002770000000.csv',
    'P4': 'phase_decomp_1000000000000_1002765000000.csv',
    'P5': 'phase_decomp_10000000000000_10002995000000.csv',
}

SECONDARY_FILES = {
    'W1': 'phase_decomp_100000000_300000000.csv',
    'W2': 'phase_decomp_1000000000_3000000000.csv',
    'W3': 'phase_decomp_10000000000_30000000000.csv',
}

MODULI = [6, 30, 210, 2310, 30030, 510510]

# --------------------------------------------------------------------------
# IO — robust to old and new CSV column names
# --------------------------------------------------------------------------

def read_window(path):
    if not os.path.exists(path):
        return None
    out = {}
    with open(path, 'r', encoding='utf-8') as f:
        for row in csv.DictReader(f):
            try:
                M = int(row['M'])
            except (KeyError, ValueError):
                continue
            try:
                L = float(row.get('logp_center', 'nan'))
            except ValueError:
                continue
            # S: prefer S_nonD; else compute (A+X+Y)/Cov
            S = float('nan')
            if row.get('S_nonD'):
                try: S = float(row['S_nonD'])
                except ValueError: pass
            if np.isnan(S):
                try:
                    A = float(row.get('A', 'nan'))
                    X = float(row.get('X', 'nan'))
                    Y = float(row.get('Y', 'nan'))
                    cov = float(row.get('cov_total',
                                        row.get('cov_e_lag1', 'nan')))
                    if cov and not np.isnan(cov):
                        S = (A + X + Y) / cov
                except ValueError:
                    pass
            # rho_resid
            rho = float('nan')
            for key in ('rho_resid', 'rho_resid_raw'):
                if row.get(key):
                    try: rho = float(row[key]); break
                    except ValueError: pass
            out[M] = {'L': L, 'S': S, 'rho': rho}
    return out

# --------------------------------------------------------------------------
# Models
# --------------------------------------------------------------------------

def m_power(L, a, alpha):    return a * np.power(L, -alpha)
def m_inverse(L, a, b):      return a + b / L
def m_log(L, a, b):          return a + b * np.log(L)
def m_linear(L, a, b):       return a + b * L

MODELS = {
    'power'  : (m_power,   ['a', 'alpha']),
    'inverse': (m_inverse, ['a', 'b']),
    'log'    : (m_log,     ['a', 'b']),
    'linear' : (m_linear,  ['a', 'b']),
}

# --------------------------------------------------------------------------
# Initial guesses
# --------------------------------------------------------------------------

def p0_power(L, y):
    idx = np.argsort(L); L, y = L[idx], y[idx]
    if L[0] <= 0 or y[0] == 0 or y[-1] == 0:
        return [1.0, 1.0]
    try:
        alpha = np.log(abs(y[0] / y[-1])) / np.log(L[-1] / L[0])
    except Exception:
        alpha = 1.0
    if not np.isfinite(alpha) or alpha < 0.05:
        alpha = 1.0
    return [y[0] * (L[0] ** alpha), alpha]

def default_p0(name, L, y):
    ym, Lm = float(np.mean(y)), float(np.mean(L))
    if name == 'power':   return p0_power(L, y)
    if name == 'inverse': return [ym, ym * Lm]
    if name == 'log':     return [ym, 0.0]
    if name == 'linear':  return [ym, 0.0]
    return None

# --------------------------------------------------------------------------
# Fitting
# --------------------------------------------------------------------------

def fit(func, L, y, p0=None):
    try:
        popt, _ = curve_fit(func, L, y, p0=p0, maxfev=50000)
        pred = func(L, *popt)
        return popt, float(np.sum((y - pred) ** 2))
    except Exception:
        return None, float('nan')

def aicc(rss, n, k):
    if rss <= 0 or n - k - 1 <= 0:
        return float('nan')
    return n * np.log(rss / n) + 2 * k + 2 * k * (k + 1) / (n - k - 1)

def loo_rmse(name, func, L, y):
    n = len(L)
    if n < 4:
        return float('nan')
    errs = []
    for i in range(n):
        mask = np.ones(n, dtype=bool); mask[i] = False
        p0 = default_p0(name, L[mask], y[mask])
        popt, _ = fit(func, L[mask], y[mask], p0=p0)
        if popt is None: continue
        pred_i = func(L[i], *popt)
        errs.append((y[i] - pred_i) ** 2)
    return float(np.sqrt(np.mean(errs))) if errs else float('nan')

# --------------------------------------------------------------------------
# Analysis
# --------------------------------------------------------------------------

def analyze(dataset, label, quantity):
    print()
    print("=" * 78)
    print(f"  {label}   |   quantity = {quantity}")
    print("=" * 78)

    results = {}
    for M in MODULI:
        Ls, ys = [], []
        for wname, byM in dataset.items():
            if M not in byM: continue
            v, L = byM[M][quantity], byM[M]['L']
            if np.isnan(v) or np.isnan(L): continue
            Ls.append(L); ys.append(v)
        if len(Ls) < 4:
            print(f"\nM = {M}: only {len(Ls)} points; skipping.")
            continue
        L = np.array(Ls); y = np.array(ys)
        idx = np.argsort(L); L, y = L[idx], y[idx]

        rows = []
        for name, (func, pnames) in MODELS.items():
            p0 = default_p0(name, L, y)
            popt, rss = fit(func, L, y, p0=p0)
            aic = aicc(rss, len(L), len(pnames))
            lrm = loo_rmse(name, func, L, y)
            rows.append({
                'model': name, 'pnames': pnames,
                'params': popt, 'rss': rss,
                'aicc': aic, 'loo_rmse': lrm,
            })
        rows.sort(key=lambda r: (np.inf if np.isnan(r['aicc']) else r['aicc']))
        aic_best = rows[0]['aicc']
        for r in rows:
            r['daicc'] = (r['aicc'] - aic_best
                          if np.isfinite(r['aicc']) else float('nan'))
        results[M] = rows

        print(f"\nM = {M}   n_points = {len(L)}")
        print(f"  L range: {L.min():.4f} .. {L.max():.4f}   "
              f"(factor {L.max()/L.min():.3f})")
        print(f"  y range: {y.min():.6f} .. {y.max():.6f}")
        print()
        print("  {:<8} {:<28} {:>10} {:>10} {:>9} {:>10}".format(
            "model", "params", "RSS", "AICc", "dAICc", "LOO-RMSE"))
        print("  " + "-" * 78)
        for r in rows:
            if r['params'] is None:
                pstr = "(fit failed)"
            else:
                pstr = ", ".join(f"{n}={v:.4g}"
                                 for n, v in zip(r['pnames'], r['params']))
            print("  {:<8} {:<28} {:>10.3e} {:>10.3f} {:>9.3f} {:>10.3e}".format(
                r['model'], pstr, r['rss'], r['aicc'],
                r['daicc'], r['loo_rmse']))
        print(f"\n  --> AICc winner: {rows[0]['model']}")

    return results

def summarize(res_S, res_rho, label):
    print()
    print("=" * 78)
    print(f"  SUMMARY — winning model per M   ({label})")
    print("=" * 78)
    print(f"  {'M':>8}  {'S(L) winner':<12} {'ΔAICc_2nd':>11}  "
          f"{'rho(L) winner':<14} {'ΔAICc_2nd':>11}")
    print("  " + "-" * 64)
    Ms = sorted(set(res_S.keys()) | set(res_rho.keys()))
    for M in Ms:
        s = res_S.get(M, []); r = res_rho.get(M, [])
        sw = s[0]['model'] if s else '-'
        rw = r[0]['model'] if r else '-'
        sd = s[1]['daicc'] if len(s) > 1 else float('nan')
        rd = r[1]['daicc'] if len(r) > 1 else float('nan')
        print(f"  {M:>8}  {sw:<12} {sd:>11.3f}  {rw:<14} {rd:>11.3f}")
    print()
    print("  Reminder: ΔAICc < 2 means the two models are indistinguishable")
    print("  by this dataset. ΔAICc > 10 is strong evidence in favour of the winner.")

# --------------------------------------------------------------------------
# Main
# --------------------------------------------------------------------------

def main():
    print("Paper 3 — Model comparison for S(M,L) and rho_resid(M,L)")
    print("(four 2-parameter models; metrics: RSS, AICc, LOO-RMSE)")

    fixed = {}
    for name, path in FIXED_N_FILES.items():
        d = read_window(path)
        if d is None:
            print(f"  [skip] missing file: {path}")
            continue
        fixed[name] = d

    print(f"\nLoaded fixed-n windows: {sorted(fixed.keys())}")
    for w in sorted(fixed.keys()):
        Ms = sorted(fixed[w].keys())
        if not Ms: continue
        L0 = fixed[w][Ms[0]]['L']
        print(f"   {w:<3}  L = {L0:.4f}   moduli = {Ms}")

    secondary = {}
    for name, path in SECONDARY_FILES.items():
        d = read_window(path)
        if d is None:
            print(f"  [skip] missing file: {path}")
            continue
        secondary[name] = d
    print(f"\nLoaded secondary windows: {sorted(secondary.keys())}")

    # --- PRIMARY: fixed-n only ---
    res_S   = analyze(fixed, "PRIMARY (fixed-n set)", 'S')
    res_rho = analyze(fixed, "PRIMARY (fixed-n set)", 'rho')
    summarize(res_S, res_rho, "fixed-n set")

    # --- SECONDARY: mixed n ---
    if secondary:
        combined = dict(fixed); combined.update(secondary)
        print()
        print("#" * 78)
        print("#  SECONDARY (mixed-n): including W1–W3")
        print("#" * 78)
        res_S2   = analyze(combined, "SECONDARY (all windows)", 'S')
        res_rho2 = analyze(combined, "SECONDARY (all windows)", 'rho')
        summarize(res_S2, res_rho2, "all windows")

    print()
    print("DONE.")

if __name__ == "__main__":
    main()