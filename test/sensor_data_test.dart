import 'package:air_quality_app/models/sensor_data.dart';
import 'package:flutter_test/flutter_test.dart';

void main() {
  test('maps the station current payload without converting PM2.5 units', () {
    final data = SensorData.fromMap({
      'environment': {
        'temperature_c': 26.5,
        'humidity_pct': 58,
        'pressure_hpa': 1012.8,
        'gas_resistance_kohm': 145.2,
        'pm25_mg_m3': 0.0186,
        'iaq_status': 'WARNING',
      },
      'power': {
        'bus_voltage_v': 7.92,
        'current_ma': 88.5,
        'power_mw': 700.92,
        'battery_percentage': 80,
      },
      'alerts': {'is_alert': true, 'alert_reason': 'PM2.5 High'},
      'timestamp': 1726848000,
    });

    expect(data.temperature, 26.5);
    expect(data.humidity, 58.0);
    expect(data.pressure, 1012.8);
    expect(data.gas, 145.2);
    expect(data.pm25, 0.0186);
    expect(data.iaqStatus, 'WARNING');
    expect(data.voltage, 7.92);
    expect(data.current, 88.5);
    expect(data.power, 700.92);
    expect(data.battery, 80);
    expect(data.isAlert, isTrue);
    expect(data.alertReason, 'PM2.5 High');
    expect(data.timestamp, 1726848000);
  });

  test('handles absent sections in a partial station payload', () {
    final data = SensorData.fromMap({});

    expect(data.temperature, 0);
    expect(data.humidity, 0);
    expect(data.pressure, 0);
    expect(data.gas, 0);
    expect(data.pm25, 0);
    expect(data.voltage, 0);
    expect(data.current, 0);
    expect(data.power, 0);
    expect(data.battery, 0);
    expect(data.iaqStatus, 'UNKNOWN');
    expect(data.isAlert, isFalse);
    expect(data.alertReason, 'NONE');
    expect(data.timestamp, 0);
  });
}
