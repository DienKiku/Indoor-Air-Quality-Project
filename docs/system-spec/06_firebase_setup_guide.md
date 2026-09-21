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
The firmware configuration is stored in [`src/firmware/include/firebase_config.h`](../../src/firmware/include/firebase_config.h):
```cpp
#ifndef FIREBASE_CONFIG_H
#define FIREBASE_CONFIG_H

#define WIFI_SSID           "Aeduongso8"
#define WIFI_PASSWORD       "20022003"

#define FIREBASE_HOST       "https://iaq-project-57a4f-default-rtdb.asia-southeast1.firebasedatabase.app/"
#define FIREBASE_AUTH       "CIX0VQNsdwG4iaeeTnJqAW9VH1q79wumwuPuUZ49"
#define DEVICE_ID           "ESP32C3_STATION_01"

#endif
```

---

## 4. Obtain Web Credentials for Frontend Dashboard

1. In **Project settings** $\rightarrow$ **General** tab, scroll down to **"Your apps"**.
2. Click the **Web icon** (`</>`) to register a web application.
3. App nickname: `IAQ-Web-Dashboard`.
4. Click **"Register app"**.
5. Firebase provides the `firebaseConfig` snippet integrated into [`src/frontend/js/app.js`](../../src/frontend/js/app.js):

```javascript
const firebaseConfig = {
  apiKey: "AIzaSyDJqoccJHQnIxVQY7A_UR7CB7LKDzqMy_8",
  authDomain: "iaq-project-57a4f.firebaseapp.com",
  databaseURL: "https://iaq-project-57a4f-default-rtdb.asia-southeast1.firebasedatabase.app",
  projectId: "iaq-project-57a4f",
  storageBucket: "iaq-project-57a4f.firebasestorage.app",
  messagingSenderId: "560237387006",
  appId: "1:560237387006:web:06b146658326ffc39819af",
  measurementId: "G-8MC3QB1K5B"
};
```

### 4.1. Configure Web Dashboard
Open [`src/frontend/js/app.js`](../../src/frontend/js/app.js) where the live configuration connects directly to the Singapore RTDB instance.
