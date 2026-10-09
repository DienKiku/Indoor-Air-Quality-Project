import 'package:firebase_database/firebase_database.dart';

import '../models/sensor_data.dart';

class FirebaseService {
  final DatabaseReference _currentRef = FirebaseDatabase.instance.ref(
    'iaq_stations/ESP32C3_STATION_01/current',
  );

  Stream<SensorData?> get sensorDataStream {
    return _currentRef.onValue.map((event) {
      final data = event.snapshot.value;

      if (data == null) {
        return null;
      }

      final map = Map<dynamic, dynamic>.from(data as Map);

      return SensorData.fromMap(map);
    });
  }
}
