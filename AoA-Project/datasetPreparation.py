import csv

INPUT_FILE  = "dataset.csv"
OUTPUT_FILE = "canada_nodes.csv"

def parse_temp(value_str):
    """
    Strip surrounding quotes, return float or None.
    NOAA stores TMAX/TMIN/TAVG in tenths of degrees C
    (e.g. "39" means 3.9 °C, "-47" means -4.7 °C).
    Returns the converted value, or None if missing/invalid.
    """
    v = value_str.strip().strip('"')
    if v == "" or v is None:
        return None
    try:
        return float(v) / 10.0
    except ValueError:
        return None

# station_id -> {lat, lon, tmax_sum, tmin_sum, tavg_sum,
#                tmax_count, tmin_count, tavg_count}
stations = {}

with open(INPUT_FILE, newline="", encoding="utf-8-sig") as f:
    reader = csv.DictReader(f)
    for row in reader:
        sid = row["STATION"].strip().strip('"')

        try:
            lat = float(row["LATITUDE"].strip().strip('"'))
            lon = float(row["LONGITUDE"].strip().strip('"'))
        except (ValueError, KeyError):
            continue   # skip rows without coordinates

        tmax = parse_temp(row.get("TMAX", ""))
        tmin = parse_temp(row.get("TMIN", ""))
        tavg = parse_temp(row.get("TAVG", ""))

        if sid not in stations:
            stations[sid] = {
                "lat": lat, "lon": lon,
                "tmax_sum": 0.0, "tmin_sum": 0.0, "tavg_sum": 0.0,
                "tmax_count": 0,  "tmin_count": 0,  "tavg_count": 0,
            }

        if tmax is not None:
            stations[sid]["tmax_sum"]   += tmax
            stations[sid]["tmax_count"] += 1
        if tmin is not None:
            stations[sid]["tmin_sum"]   += tmin
            stations[sid]["tmin_count"] += 1
        if tavg is not None:
            stations[sid]["tavg_sum"]   += tavg
            stations[sid]["tavg_count"] += 1

written = 0
skipped = 0

with open(OUTPUT_FILE, "w", newline="") as f:
    writer = csv.writer(f)
    writer.writerow(["latitude", "longitude", "avg_temp_c"])

    for sid, s in stations.items():
        # Prefer TAVG if available, otherwise average TMAX and TMIN
        if s["tavg_count"] > 0:
            avg = s["tavg_sum"] / s["tavg_count"]
        elif s["tmax_count"] > 0 and s["tmin_count"] > 0:
            avg = (s["tmax_sum"] / s["tmax_count"] +
                   s["tmin_sum"] / s["tmin_count"]) / 2.0
        else:
            skipped += 1
            continue   # not enough data for this station

        writer.writerow([s["lat"], s["lon"], f"{avg:.4f}"])
        written += 1

print(f"Done: {written} stations written to '{OUTPUT_FILE}', {skipped} skipped (insufficient data).")
