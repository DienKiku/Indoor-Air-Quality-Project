import '../models/sensor_data.dart';

class MockSensorService {
  static SensorData getData() {
    return SensorData.demo();
  }
}
