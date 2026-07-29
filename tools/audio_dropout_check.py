#!/usr/bin/env python3
"""Measure HDMI audio dropouts from a captured test-tone recording.

The FPGA emits a steady 1 kHz sine on HDMI. Capture it back through the
capture card and any dropout becomes objective rather than a judgement call:

  * a sink resync            -> a run of silence
  * a starved sample path    -> zeroed or repeated samples
  * an ACR / rate mismatch   -> phase discontinuities (clicks), and a measured
                                tone frequency that differs from 1000 Hz

Usage:  python3 tools/audio_dropout_check.py capture.wav [expected_hz]
"""
import struct
import sys
import wave

path = sys.argv[1]
expect_hz = float(sys.argv[2]) if len(sys.argv) > 2 else 1000.0

w = wave.open(path, "rb")
ch, sw, sr, n = w.getnchannels(), w.getsampwidth(), w.getframerate(), w.getnframes()
raw = w.readframes(n)
w.close()
assert sw == 2, "expected 16-bit"
s = struct.unpack("<%dh" % (len(raw) // 2), raw)
left = s[0::ch]
dur = len(left) / sr
print(f"{path}: {sr} Hz, {ch}ch, {dur:.2f} s, {len(left)} frames")

# Trim leading/trailing silence: the capture card takes a few hundred ms to
# lock, and that gap is a recording artefact, not a dropout.
peak = max(abs(v) for v in left)
if peak >= 500:
    t0 = next(i for i, v in enumerate(left) if abs(v) > peak // 5)
    t1 = len(left) - next(i for i, v in enumerate(reversed(left)) if abs(v) > peak // 5)
    if t0 or t1 != len(left):
        print(f"trimmed {t0/sr*1000:.0f} ms lead-in, "
              f"{(len(left)-t1)/sr*1000:.0f} ms tail (capture lock)")
    left = left[t0:t1]
    dur = len(left) / sr
print(f"peak amplitude: {peak}, analysed span {dur:.2f} s")
if peak < 500:
    print("\n*** NO TONE PRESENT — nothing to measure ***")
    sys.exit(1)

# ---- silence / dropout runs -------------------------------------------------
# A dropout is a run of near-zero samples much longer than a zero crossing.
thresh = peak // 20
min_run = sr // 500            # 2 ms — far longer than a 1 kHz zero crossing
runs, cur = [], 0
for v in left:
    if abs(v) < thresh:
        cur += 1
    else:
        if cur >= min_run:
            runs.append(cur)
        cur = 0
if cur >= min_run:
    runs.append(cur)

total_lost = sum(runs)
print(f"\ndropouts (silent runs >= {min_run} samples / 2 ms): {len(runs)}")
if runs:
    ms = [r * 1000.0 / sr for r in runs]
    print(f"  longest {max(ms):.1f} ms, total {total_lost*1000.0/sr:.1f} ms "
          f"({100.0*total_lost/len(left):.3f}% of stream)")
    print(f"  rate: {len(runs)/dur:.2f} per second")

# ---- exact tone frequency, from zero crossings ------------------------------
# Counting positive-going zero crossings over the whole capture gives a far
# better frequency estimate than an FFT bin, and directly exposes a sample
# rate mismatch between source and sink.
xs = [i for i in range(1, len(left)) if left[i-1] < 0 <= left[i]]
if len(xs) > 10:
    cycles = len(xs) - 1
    span = (xs[-1] - xs[0]) / sr
    meas = cycles / span
    err = (meas - expect_hz) / expect_hz * 1e6
    print(f"\nmeasured tone: {meas:.3f} Hz (expected {expect_hz:.0f})  "
          f"error {err:+.0f} ppm")

# ---- glitches: sudden sample-to-sample jumps --------------------------------
# A clean 1 kHz sine at 48 kHz moves at most ~peak*2*pi*1000/48000 per sample.
lim = int(peak * 6.283 * expect_hz / sr * 3)
glitches = sum(1 for i in range(1, len(left)) if abs(left[i] - left[i-1]) > lim)
print(f"waveform glitches (|step| > {lim}): {glitches}"
      f"  ({glitches/dur:.2f} per second)")

verdict = "CLEAN" if (not runs and glitches < dur) else "DROPOUTS PRESENT"
print(f"\n=> {verdict}")
