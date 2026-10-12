# Paper 3 — Project Changelog

This file records the chronological development of Paper 3,
from the initial preregistered protocol through the current
state of the draft. It is not part of the paper.

## 1. Project identity

- Title (working): Position Dependence of Phase-Decomposed
  Lag-One Covariance in Prime-Gap Data
- Author: Reddouane Berramdane
- Predecessors:
    Paper 1: Zenodo DOI 10.5281/zenodo.23162269
    Paper 2: Zenodo DOI 10.5281/zenodo.23222536
- Language: English (manuscript), Arabic (internal notes)

## 2. Chronology

### 2026-10-09 — Protocol v1 frozen

Seven predictions T1–T7 declared before any computation:
  T1: |A+X+Y+D − Cov| < 1e-6 every row
  T2: var_between + var_within = var_e every row
  T3: S(M) monotone increasing in M each window
  T4: ρ_resid < 0 every M every window
  T5: Bootstrap 95% CIs exclude zero
  T6: S(M) at higher window ≥ S(M) at lower window
  T7: A, X, Y, D vary smoothly across windows
Abort condition: any failure halts the run.
File: paper3_protocol_v1.md

### 2026-10-09 — Phase 1: W1

Window W1 = [10^8, 3×10^8).
First run failed with "Sparse class at M=9699690".
Diagnosed as a physical limit, not a code error.

### 2026-10-09 — Dynamic modulus eligibility

A new rule was documented and introduced:
  minimum class count ≥ 100                → standard
  minimum class count 50–99               → diagnostic
  minimum class count < 50                → modulus excluded
This rule is the ONLY change to the modulus set entering a
window-level analysis relative to Paper 2. Runtime arguments
and expanded diagnostics are implementation changes.

### 2026-10-09 — Phases 2–3: W2, W3

W2 = [10^9, 3×10^9), W3 = [10^10, 3×10^10).
W3 reproduces Paper 2 exactly at M = 9699690:
  S = 60.4431%, ρ_resid = −0.010306.

### 2026-10-09 — T6 falsified

Across W1, W2, W3, S(M) decreases monotonically with window
position for every M tested (30/30 ordered pairs).
Protocol v1 abort clause triggered; W4–W6 halted.

### 2026-10-09 — Post-falsification diagnostics

Diagnostic 1 — Quadratic detrending.
  g ≈ a + b·u + c·u², u = log p − 0.5(log LO + log HI)
  Result: S unchanged to six decimal places in all 21 cases.
  File: test_multiwindow_quad_v1.cpp

Diagnostic 2 — Fixed-count windows.
  Eight windows at n ≈ 10^8:
    A, P1, B, P2, P3, C, P4, P5
  Span: prime location 10^8 to 10^13.
  Result: S and |ρ_resid| decrease monotonically with L for
  every M. A pure sample-size explanation strongly disfavoured.

### 2026-10-09 — Model comparison

Four two-parameter models fit to S(M, L) and |ρ_resid(M, L)|:
  power       y = a · L^(−α)
  reciprocal  y = a + b / L
  log         y = a + b · log(L)
  linear      y = a + b · L
Result: no unique winner. Linear-in-L substantially poorer
support for S (ΔAICc ≈ 7–8). Winner changes with dataset.
Files: paper3_model_comparison.py, model_comparison_output.txt

### 2026-10-09 — paper3_protocol_v2.md frozen

Exploratory protocol, distinguishing preregistered analysis
(Section 3) from exploratory analysis (Sections 4–6).

### 2026-10-10 — Draft revisions

Multiple review cycles (external reviewer feedback).
Corrections applied across all sections:
  - Cov(e_n, e_{n+1}) used consistently
  - "inverse" renamed to "reciprocal"
  - "moving-block" renamed to "non-overlapping block"
  - "H1 excluded" softened to "strongly disfavoured"
  - T7 reclassified as descriptive
  - 14 additional text corrections

### 2026-10-10 — Data inventory created

File: paper3_data_inventory.txt
Contains SHA-256 for all sources, protocols, CSVs, and outputs.

### 2026-10-10 — Draft state

Manuscript sections:
  Abstract          complete
  Section 1         complete
  Section 2         complete
  Section 3         complete
  Section 4         complete
  Section 5         complete
  Section 6         complete
  Section 7         complete
  Section 8         complete
Remaining:
  References
  Appendix (candidate tables: 5.3–5.5, 6.4–6.5)
  Final title selection

## 3. Key decisions and their rationale

D1. Falsification of T6 reported without modification.
    The preregistered direction was wrong; the paper says so
    plainly.

D2. Position dependence described as empirical, finite-range.
    No asymptotic law, no theoretical mechanism.

D3. Functional form left unidentified.
    Power, log, and reciprocal forms are statistically
    indistinguishable over the observed range.

D4. Cramér heuristic referenced only in its elementary form.
    No claim of general refutation of Cramér–Granville.

D5. No comparison with analytic number theory.
    Montgomery–Odlyzko, GPY, Maynard, Lemke Oliver–Soundararajan
    are not invoked.

D6. No zeta connection.
    Data are strictly empirical and finite-range.

## 4. Current state

Manuscript: 90% complete (Sections 1–8 + Abstract + Keywords + MSC).
Data: all CSVs in data inventory.
Code: test_multiwindow_v1.cpp, test_multiwindow_quad_v1.cpp,
      paper3_model_comparison.py.
Protocols: v1 (frozen, falsified in part), v2 (frozen, exploratory).

## 5. Open items

O1. Independent sieve verification at 10^12 or 10^13.
O2. References section.
O3. Appendix decision (which tables to move).
O4. Final title selection.
O5. Journal selection for submission.

## 6. File manifest

List every file that exists in the project directory with
its sha256. Group by category:
  Sources (.cpp, .py)
  Binaries (.exe)
  Protocols (.md)
  Drafts (.md, .docx)
  Data (.csv)
  Logs (.log, .txt)

### Sources (.cpp, .py)

| File | Size (bytes) | SHA-256 |
|------|--------------|---------|
| test_1e10_final_v3.cpp | 20216 | 9ee6c362a3f40c7999c6ed34a8e9b68e463960bc815c0f3e149bfa802daf6710 |
| test_1e10_final_v3.cpp.bak.20261009_123542 | 20216 | 9ee6c362a3f40c7999c6ed34a8e9b68e463960bc815c0f3e149bfa802daf6710 |
| test_multiwindow_v1.cpp | 24070 | 9d5f894e2130ce23dd28056658f61216c9697ca19dba704e4663d5516d12115b |
| test_multiwindow_v1.cpp.bak.20261009_125527 | 20617 | bf9e58929de9257fecb1606ed29469e2fb5ffa16d30332b33f1c4359e4c1b562 |
| test_multiwindow_quad_v1.cpp | 15319 | 7c9823733998985410164b3b5e9c0d09e6747ad0728a7cfc7bea6fdfbe9794c3 |
| paper3_model_comparison.py | 10971 | fd25a2186421d4f97e372449ea7e59045e5b62b29df61edb70ac570c23684fb7 |

### Binaries (.exe)

| File | Size (bytes) | SHA-256 |
|------|--------------|---------|
| test_multiwindow_v1.exe | 2890419 | ccc90c9f3d0f9ea074a5192dc0206dac7babfa88aba7f3acdb6c1683dab8f6f0 |
| test_multiwindow_quad_v1.exe | 2881418 | 6f7f2fbba63103231a9746f2a2b1b71f143bf2376692067acd7f70c1507b5273 |

### Protocols (.md)

| File | Size (bytes) | SHA-256 |
|------|--------------|---------|
| paper3_protocol_v1.md | 1807 | b65a5315198d0d014a4425be2d6f1ef70adf24ebb984bdb21c5556b211c5e1f8 |
| paper3_protocol_v2.md | 10831 | 1ac42229a38031950192ed9b6094301dcc38e2889ae8aa35eb64284afb4c6d62 |

### Drafts (.md, .docx)

| File | Size (bytes) | SHA-256 |
|------|--------------|---------|
| paper3_draft_v3.docx | 56526 | c50f0c7811791f84683c742461a1a89968aa4e4feed7181cd7bd0feadab50081 |
| Nouveau Microsoft Word Document.docx.bak.20261010_133532 | 60308 | 4ab4f8da7af208de69fe2d60ca166c5c092751caa46d24ba456dbd690e65aecd |
| Nouveau Microsoft Word Document.docx.bak.20261010_143650 | 56526 | c50f0c7811791f84683c742461a1a89968aa4e4feed7181cd7bd0feadab50081 |
| Nouveau document texte.txt | 3568 | fec27acd9370e7664f0f32ed77beae82df022106d7a1721cd044e068b8d3da85 |

### Sections (.md, split deliverable)

| File | Size (bytes) | SHA-256 |
|------|--------------|---------|
| sections/03_preregistered_tests.md | 5809 | 7480025a5535e4e45278535972dd1316a0376477cb911c6df634d197863ce276 |
| sections/04_fixed_count_diagnostic.md | 7449 | f2241ad7f43b5438c9b6114595869ff179911b3b41a9ecf2cab88012894a4c16 |
| sections/05_position_dependence.md | 6230 | 9a13a7926123b0e632f0d295d0e0601272efe476f2ae6bc02a379ef1c6a80a86 |
| sections/06_functional_form_sensitivity.md | 7575 | a2248e9786e1bb005a2112b24c7d24a87555081efd9e03521d05996ffbab82ef |
| sections/07_claims_and_non_claims.md | 8345 | 972ff5731630e2e757eff6a0923177fb1745c15c6777becd41745c2d13915c50 |
| sections/08_outlook_and_open_questions.md | 6810 | 38c7f1a299ed03acdbd304f758e3f68833702fa5fd8be80fa132d6583d774c1b |

### Data (.csv)

| File | Size (bytes) | SHA-256 |
|------|--------------|---------|
| phase_decomp_10000000000000_10002995000000.csv | 2093 | 443ccdd1a23abd1eb1ddf74d9a2e4e6938be723f44acae733e45b0014973aa57 |
| phase_decomp_1000000000000_1002765000000.csv | 2073 | aec4818f8c9b4e58bf8f55c1cd427d666b0e3a726dac3d4bc22108c64f7458ba |
| phase_decomp_1000000000000_1002770000000.csv | 2073 | c1c9ac8d85e306fe5a2bf51616152f7d685b56daf3b714b9b525bbcb0ebcba47 |
| phase_decomp_10000000000_102535000000.csv | 2063 | 7fa28cfafb6f2fab4ac9e7a3af414963048aa3bf467ad5b1556f205c2e83ebd8 |
| phase_decomp_1000000000_12220000000.csv | 2041 | 99235c7155f70e5d980961e1461c24df95a99e770e6e6fc59f041777a16b9083 |
| phase_decomp_1000000000_12305000000.csv | 2041 | 97b280fecee4b8b6d8e33411cfa1666db8ac381fad769c4dffda1f61ba8c595d |
| phase_decomp_1000000000_30000000000.csv | 2355 | 004bd2f5b4a3606d6a580fd702a9f64025fa5d8d7d8afb70cfb60b1f74c28faa |
| phase_decomp_1000000000_3000000000.csv | 2024 | bc2e9d797deefa6d07f7816f3e1312c56cc960c3dabbe8429fb17c255521b2c7 |
| phase_decomp_1000000000_3145000000.csv | 2028 | c0325bb2317389cd2d1f48846983c4fc775e68e4dd9c1d79d55ebf698f9b80ff |
| phase_decomp_100000000_2180000000.csv | 2024 | bc78112eb36fd14822a73b07194d8c9f7324c0f8e8e275d92669979274a5e128 |
| phase_decomp_100000000_300000000.csv | 2000 | a9affaf204ef1bed6b9733901d9b42483d597412c5f4e3b6b70c341d665fd663 |
| phase_decomp_quad_1000000000_300000000.csv | 1921 | a24e5a280a385a4330cd1682a575c21355c57dd7e1460efef1413124dbfed3ca |
| phase_decomp_quad_1000000000_30000000000.csv | 1948 | 33bf4667c7099e374c33d7a5a813b6be0836b9e7be431b411f8de01d10857d43 |
| phase_decomp_quad_10000000000_30000000000.csv | 2271 | dfc181cdf4f1109561237aa65fd694872e81327235f69dad714b01cd24ae8e32 |

### Logs (.log, .txt)

| File | Size (bytes) | SHA-256 |
|------|--------------|---------|
| cerr_P1.log | 4340 | cc18410b665daa1f69bd28d200ae79643c30c521e8c275d92669979274a5e128 |
| cerr_P2.log | 4326 | 50b192590f74dc838202bb3711e3334393b8e7fa4e9c3505dc63675942f4a155 |
| cerr_P3.log | 4338 | 46e9e6cc0c462b25c881abe16794642b145be957fa681871a84b97d6b410ea0c |
| cerr_P4.log | 4344 | 18660f92854a27b43f87eab9e47f9f670f0587095026e04a414df381a5641b7 |
| cerr_P5.log | 4356 | d66129b49892f0a52bf51616152f7d685b56daf3b714b9b525bbcb0ebcba47 |
| cerr_pos_A.log | 4336 | 4d111e422eee15e0b70435b30c99224dd80b7be56567b8d56f24facddde654e |
| cerr_pos_B.log | 4292 | fc174225d6c628071634235ab1d8bd31e9fc15be006c27b197e0f524f9a7ecd |
| cerr_pos_C.log | 4342 | 96f0bb18dcf391e9cda5929f9da21232ee3e3b83f7ec258a44325575c6c7cb6 |
| cerr_w1.log | 4284 | 7010b56db01c287c6de3c5aa0caee50d34ad3e98142dadd1d2d289c1ab51f20f |
| cerr_w2.log | 4288 | 34ea1ec506666260f79bf378c4739b2e5340d32fdde7204a8828d87c91822e22 |
| cerr_w3.log | 4520 | b4e1a16a6ad85413c8e18c5bb731f7d33b20e51afcd25c7196badfbc78b5ae77 |
| cerr_w4.log | 2834 | b27e05180092e843327306085a85d2bdd73912512f6b0bcef622b5f209c9ca57 |
| compile_p1.log | 1192 | e0a29ea6733cd52b917716370d3b1028088ddaf3ab5b16bdcd87578a3e3b63ba |
| run_p1_w1.log | 12282 | db1c543a6f2a2e05f45f01833e5bb5924bedd2c193cfc8d1fb5c2d274fc79653 |
| log_10000000000000_10002995000000.txt | 4021 | bdfd5e784fae131f121f1c903889f3bf6b5a837283f2204e1a948286d517e424 |
| log_1000000000000_1002765000000.txt | 4015 | b0e2ae3d65d478e91b5ca218c65ae36b4e58168fb086dcdbf0eef3107c8392de |
| log_1000000000000_1002770000000.txt | 4015 | 7466459093bf9294e66431ed41e8f0ecb9af648d090b8cd96e198ca5de82c074 |
| log_100000000000_102535000000.txt | 4012 | 07a646c2ea54be9fba167d07c21fa917edb64abe0673da061d5eec0ad3965c8b |
| log_10000000000_12220000000.txt | 3996 | 17f77e34d6b6a8284bb06a8d92c6ed268324fb31248b02fe409c5cb1299fda83 |
| log_10000000000_12305000000.txt | 3996 | 5f76a4537e599c54169ff453114c14befe3ab057409a2ca00d3e5310b9d514a7 |
| log_10000000000_30000000000.txt | 0 | e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855 |
| log_10000000000_3000000000.txt | 4615 | 2bbe7d386970b1167d1ca738242e47173fdf3649dc35effac7879cf151b4e2b9 |
| log_1000000000_300000000.txt | 3981 | 08d6b60534aa0caf4e1e16fc475d4e4864b011888bf285fc9e3519cba048c271 |
| log_100000000_2180000000.txt | 3984 | f29e991ec574f823f88b53d19100a50c824522bccd68864043daf8b0df38badb |
| log_100000000_300000000.txt | 3968 | ec24ad8323b6519238ed6c2a2448579759dc2523fae68af6ba2f22537b75acd8 |
| model_comparison_output.txt | 18968 | ac2044588cf767f7d15189c3fb4857d9e2e366ed4b1173cae85d1cfd9994bfa5 |

### Notes

- `log_10000000000_3000000000.txt` is empty (0 bytes); the run for window W1 was overwritten by the time the changelog was compiled.
- `Nouveau document texte.txt` is the task-protocol prompt, not a results file.
- `python.txt` in the quad folder is an environment note, not a results file.
- All SHA-256 values computed from actual files on disk.
- No file was modified during this task; only `paper3_changelog.md` was created.
