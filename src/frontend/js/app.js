// ==========================================
// FIREBASE CONFIGURATION (REPLACE WITH YOUR KEYS)
// ==========================================
const firebaseConfig = {
    apiKey: "YOUR_API_KEY",
    authDomain: "YOUR_PROJECT_ID.firebaseapp.com",
    databaseURL: "https://YOUR_PROJECT_ID-default-rtdb.firebaseio.com",
    projectId: "YOUR_PROJECT_ID",
    storageBucket: "YOUR_PROJECT_ID.appspot.com",
    messagingSenderId: "YOUR_SENDER_ID",
    appId: "YOUR_APP_ID"
};

// Initialize Firebase (if valid config)
let isFirebaseConfigured = false;
let database;

try {
    if (firebaseConfig.apiKey !== "YOUR_API_KEY") {
        firebase.initializeApp(firebaseConfig);
        database = firebase.database();
        isFirebaseConfigured = true;
        console.log("[FIREBASE] Connected to Realtime Database.");
    } else {
        console.warn("[FIREBASE] Using simulated mock telemetry. Update firebaseConfig in app.js to connect live.");
    }
} catch (err) {
    console.error("[FIREBASE] Init error:", err);
}

// Device ID to monitor
const DEVICE_ID = "ESP32C3_STATION_01";

// ==========================================
// CHART.JS INITIALIZATION
// ==========================================
const ctx = document.getElementById('telemetryChart').getContext('2d');
const maxDataPoints = 20;

const telemetryChart = new Chart(ctx, {
    type: 'line',
    data: {
        labels: [],
        datasets: [
            {
                label: 'PM2.5 (\u03bcg/m\u00b3)',
                borderColor: '#eab308',
                backgroundColor: 'rgba(234, 179, 8, 0.1)',
                data: [],
                yAxisID: 'yDust',
                tension: 0.3,
                fill: true
            },
            {
                label: 'VOC Gas (k\u03a9)',
                borderColor: '#38bdf8',
                backgroundColor: 'transparent',
                data: [],
                yAxisID: 'yVoc',
                tension: 0.3
            },
            {
                label: 'Temperature (\u00b0C)',
                borderColor: '#ef4444',
                backgroundColor: 'transparent',
                data: [],
                yAxisID: 'yTemp',
                tension: 0.3
            }
        ]
    },
    options: {
        responsive: true,
        maintainAspectRatio: false,
        interaction: {
            mode: 'index',
            intersect: false,
        },
        scales: {
            x: {
                grid: { color: 'rgba(255, 255, 255, 0.05)' },
                ticks: { color: '#94a3b8' }
            },
            yDust: {
                type: 'linear',
                position: 'left',
                title: { display: true, text: 'PM2.5 (\u03bcg/m\u00b3)', color: '#eab308' },
                grid: { color: 'rgba(255, 255, 255, 0.05)' },
                ticks: { color: '#eab308' },
                min: 0
            },
            yVoc: {
                type: 'linear',
                position: 'right',
                title: { display: true, text: 'VOC (k\u03a9)', color: '#38bdf8' },
                grid: { drawOnChartArea: false },
                ticks: { color: '#38bdf8' }
            },
            yTemp: {
                type: 'linear',
                position: 'right',
                display: false,
                min: 0,
                max: 50
            }
        },
        plugins: {
            legend: {
                labels: { color: '#f8fafc' }
            }
        }
    }
});

// ==========================================
// TELEMETRY UPDATE LOGIC
// ==========================================
function updateDashboardUI(data) {
    const env = data.environment || {};
    const power = data.power || {};
    const alerts = data.alerts || {};

    // 1. Environmental Values
    document.getElementById('pm25-val').innerText = (env.pm25_ug_m3 || 0).toFixed(1);
    document.getElementById('voc-val').innerText = (env.gas_resistance_kohm || 0).toFixed(1);
    document.getElementById('temp-val').innerText = (env.temperature_c || 0).toFixed(1);
    document.getElementById('hum-val').innerText = (env.humidity_pct || 0).toFixed(1);
    document.getElementById('press-val').innerText = (env.pressure_hpa || 1013).toFixed(0);

    // 2. Battery & Power
    const vBat = power.bus_voltage_v || 0;
    const iBat = power.current_ma || 0;
    const soc = power.battery_percentage !== undefined ? power.battery_percentage : 80;

    document.getElementById('bat-volts').innerText = vBat.toFixed(2) + ' V';
    document.getElementById('bat-current').innerText = iBat.toFixed(0) + ' mA';
    document.getElementById('bat-pct').innerText = soc + '%';

    const batFill = document.getElementById('battery-fill');
    batFill.style.width = soc + '%';
    if (soc < 20) {
        batFill.style.backgroundColor = 'var(--accent-red)';
    } else if (soc < 40) {
        batFill.style.backgroundColor = 'var(--accent-yellow)';
    } else {
        batFill.style.backgroundColor = 'var(--accent-green)';
    }

    // 3. Alert Status Banner
    const banner = document.getElementById('alert-banner');
    const icon = document.getElementById('alert-icon');
    const text = document.getElementById('alert-text');

    if (alerts.is_alert || (env.pm25_ug_m3 && env.pm25_ug_m3 > 75)) {
        banner.className = 'alert-banner danger';
        icon.innerText = '\u26a0';
        text.innerText = 'WARNING: Hazardous air quality detected! High PM2.5 particulate level.';
    } else if (env.pm25_ug_m3 && env.pm25_ug_m3 > 35) {
        banner.className = 'alert-banner warning';
        icon.innerText = '\u26a0';
        text.innerText = 'Caution: Moderate air quality. Ventilation recommended.';
    } else {
        banner.className = 'alert-banner good';
        icon.innerText = '\u2713';
        text.innerText = 'Indoor air quality is optimal. All parameters within safe limits.';
    }

    // 4. Update Time Badge
    const now = new Date();
    document.getElementById('last-update-badge').innerText = `Last Update: ${now.toLocaleTimeString()}`;

    // 5. Update Chart
    const timeLabel = now.toLocaleTimeString([], { hour: '2-digit', minute: '2-digit', second: '2-digit' });
    if (telemetryChart.data.labels.length >= maxDataPoints) {
        telemetryChart.data.labels.shift();
        telemetryChart.data.datasets[0].data.shift();
        telemetryChart.data.datasets[1].data.shift();
        telemetryChart.data.datasets[2].data.shift();
    }
    telemetryChart.data.labels.push(timeLabel);
    telemetryChart.data.datasets[0].data.push(env.pm25_ug_m3 || 0);
    telemetryChart.data.datasets[1].data.push(env.gas_resistance_kohm || 0);
    telemetryChart.data.datasets[2].data.push(env.temperature_c || 0);
    telemetryChart.update();
}

// ==========================================
// DATA STREAM SUBSCRIPTION
// ==========================================
if (isFirebaseConfigured && database) {
    const stationRef = database.ref(`/iaq_stations/${DEVICE_ID}/current`);
    stationRef.on('value', (snapshot) => {
        const data = snapshot.val();
        if (data) {
            updateDashboardUI(data);
        }
    });
} else {
    // Generate realistic simulated telemetry when unconfigured
    setInterval(() => {
        const mockData = {
            environment: {
                pm25_ug_m3: 15.0 + Math.random() * 8.0,
                gas_resistance_kohm: 140.0 + (Math.random() - 0.5) * 15.0,
                temperature_c: 26.2 + (Math.random() - 0.5) * 0.8,
                humidity_pct: 58.0 + (Math.random() - 0.5) * 2.0,
                pressure_hpa: 1012.0 + (Math.random() - 0.5) * 1.0
            },
            power: {
                bus_voltage_v: 7.85 + (Math.random() - 0.5) * 0.05,
                current_ma: 88.0 + (Math.random() - 0.5) * 10.0,
                battery_percentage: 79
            },
            alerts: {
                is_alert: false
            }
        };
        updateDashboardUI(mockData);
    }, 3000);
}
