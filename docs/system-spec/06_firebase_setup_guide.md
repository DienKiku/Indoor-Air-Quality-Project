# 06. Google Firebase Setup & Configuration Guide

This guide provides step-by-step instructions to configure **Google Firebase Realtime Database** for both the ESP32-C3 firmware and the Web Dashboard.

---

## 1. Create a Google Firebase Project

1. Navigate to the [Google Firebase Console](https://console.firebase.google.com/).
2. Sign in with your Google account and click **"Add project"** (or **"Create a project"**).
3. Project Name: Enter `Indoor-Air-Quality` (or your preferred name).
4. Google Analytics: Optional (can be disabled to simplify setup).
5. Click **"Create project"** and wait for provisioning to complete.

---

## 2. Enable Realtime Database (RTDB)

1. In the left navigation menu, go to **Build** $\rightarrow$ **Realtime Database**.
2. Click **"Create Database"**.
3. **Database Location:** Choose a region close to your deployment (e.g., `Singapore (asia-southeast1)` or `United States (us-central1)`).
4. **Security Rules:** Select **"Start in test mode"** (allows read/write during development for 30 days).
5. Click **"Enable"**.

### 2.1. Copy Database URL
At the top of the Data tab, note the database URL. It follows one of these formats:
- `https://your-project-id-default-rtdb.firebaseio.com/` (US region)
- `https://your-project-id-default-rtdb.asia-southeast1.firebasedatabase.app/` (Singapore region)

### 2.2. Apply Security Rules
Switch to the **Rules** tab in Realtime Database, paste the contents of [`src/cloud-firebase/database.rules.json`](../../src/cloud-firebase/database.rules.json), and click **"Publish"**:

```json
{
  "rules": {
    "iaq_stations": {
      ".read": true,
      "$station_id": {
        ".write": true,
        "current": {
          ".validate": "newData.hasChildren(['environment', 'power', 'alerts'])"
        },
        "history": {
          "$record_id": {
            ".validate": "newData.hasChildren(['timestamp', 'pm25_ug_m3', 'temperature_c'])"
          }
        }
      }
    }
  }
}
```

---

## 3. Obtain Credentials for ESP32-C3 Firmware

To allow the ESP32-C3 to write to the Realtime Database using the legacy token / secret:
1. Click the **Gear icon** (⚙️) next to *Project Overview* $\rightarrow$ **Project settings**.
2. Navigate to the **Service accounts** tab.
3. Click on **Database secrets** (in the secondary sub-menu).
4. Click **"Show"** next to your secret key, then copy the alphanumeric string.

### 3.1. Configure Firmware
Create a file named `firebase_config.h` inside `src/firmware/include/`:
```cpp
#ifndef FIREBASE_CONFIG_H
#define FIREBASE_CONFIG_H

#define WIFI_SSID           "Your_WiFi_SSID"
#define WIFI_PASSWORD       "Your_WiFi_Password"

#define FIREBASE_HOST       "https://your-project-id-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH       "your_database_secret_here"
#define DEVICE_ID           "ESP32C3_STATION_01"

#endif
```

---

## 4. Obtain Web Credentials for Frontend Dashboard

1. In **Project settings** $\rightarrow$ **General** tab, scroll down to **"Your apps"**.
2. Click the **Web icon** (`</>`) to register a web application.
3. App nickname: `IAQ-Web-Dashboard`.
4. Click **"Register app"**.
5. Firebase will present your `firebaseConfig` snippet:

```javascript
const firebaseConfig = {
  apiKey: "AIzaSy...",
  authDomain: "indoor-air-quality.firebaseapp.com",
  databaseURL: "https://indoor-air-quality-default-rtdb.firebaseio.com",
  projectId: "indoor-air-quality",
  storageBucket: "indoor-air-quality.appspot.com",
  messagingSenderId: "1234567890",
  appId: "1:1234567890:web:abcdef"
};
```

### 4.1. Configure Web Dashboard
Open [`src/frontend/js/app.js`](../../src/frontend/js/app.js) and replace the placeholder `firebaseConfig` object with your generated keys.
