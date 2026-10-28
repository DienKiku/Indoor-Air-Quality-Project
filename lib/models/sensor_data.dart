class SensorData {
  final double temperature;
  final double humidity;
  final double pressure;
  final double pm25;
  final double gas;

  final double voltage;
  final double current;
  final double power;

  final int battery;

  final String iaqStatus;
  final bool isAlert;
  final String alertReason;

  final int timestamp;

  SensorData({
    required this.temperature,
    required this.humidity,
    required this.pressure,
    required this.pm25,
    required this.gas,
    required this.voltage,
    required this.current,
    required this.power,
    required this.battery,
    required this.iaqStatus,
    required this.isAlert,
    required this.alertReason,
    required this.timestamp,
  });

  factory SensorData.fromMap(Map<dynamic, dynamic> data) {
    final environment = Map<dynamic, dynamic>.from(data['environment'] ?? {});

    final powerData = Map<dynamic, dynamic>.from(data['power'] ?? {});

    final alerts = Map<dynamic, dynamic>.from(data['alerts'] ?? {});

    return SensorData(
      temperature: (environment['temperature_c'] as num?)?.toDouble() ?? 0.0,

      humidity: (environment['humidity_pct'] as num?)?.toDouble() ?? 0.0,

      pressure: (environment['pressure_hpa'] as num?)?.toDouble() ?? 0.0,

      pm25: (environment['pm25_mg_m3'] as num?)?.toDouble() ?? 0.0,

      gas: (environment['gas_resistance_kohm'] as num?)?.toDouble() ?? 0.0,

      voltage: (powerData['bus_voltage_v'] as num?)?.toDouble() ?? 0.0,

      current: (powerData['current_ma'] as num?)?.toDouble() ?? 0.0,

      power: (powerData['power_mw'] as num?)?.toDouble() ?? 0.0,

      battery: (powerData['battery_percentage'] as num?)?.toInt() ?? 0,

      iaqStatus: environment['iaq_status']?.toString() ?? 'UNKNOWN',

      isAlert: alerts['is_alert'] as bool? ?? false,

      alertReason: alerts['alert_reason']?.toString() ?? 'NONE',

      timestamp: (data['timestamp'] as num?)?.toInt() ?? 0,
    );
  }

  factory SensorData.demo() {
    return SensorData(
      temperature: 25.2,
      humidity: 80.8,
      pressure: 1012.8,
      pm25: 0.0186,
      gas: 83.6,
      voltage: 7.4,
      current: 75,
      power: 555,
      battery: 75,
      iaqStatus: 'GOOD',
      isAlert: false,
      alertReason: 'NONE',
      timestamp: 0,
    );
  }
}
