import 'package:flutter/material.dart';

import '../models/sensor_data.dart';
import '../services/firebase_service.dart';

import '../widgets/sensor_card.dart';
import '../widgets/aqi_card.dart';
import '../widgets/battery_card.dart';

class HomeScreen extends StatefulWidget {
  const HomeScreen({super.key});

  @override
  State<HomeScreen> createState() => _HomeScreenState();
}

class _HomeScreenState extends State<HomeScreen> {
  final FirebaseService _firebaseService = FirebaseService();
  late final Stream<SensorData?> _sensorDataStream =
      _firebaseService.sensorDataStream;

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      backgroundColor: const Color(0xffF4F7FB),

      appBar: AppBar(
        title: const Text(
          "Air Quality Monitor",
          style: TextStyle(color: Colors.black, fontWeight: FontWeight.bold),
        ),
        centerTitle: true,
        backgroundColor: Colors.white,
        elevation: 0,
      ),

      body: StreamBuilder<SensorData?>(
        stream: _sensorDataStream,

        builder: (context, snapshot) {
          if (snapshot.connectionState == ConnectionState.waiting) {
            return const Center(child: CircularProgressIndicator());
          }

          if (snapshot.hasError) {
            return Center(
              child: Text(
                "Firebase error:\n${snapshot.error}",
                textAlign: TextAlign.center,
              ),
            );
          }

          if (!snapshot.hasData || snapshot.data == null) {
            return const Center(child: Text("No sensor data"));
          }

          final data = snapshot.data!;

          return SingleChildScrollView(
            padding: const EdgeInsets.all(18),

            child: Column(
              children: [
                AQICard(
                  status: data.iaqStatus,
                  isAlert: data.isAlert,
                  alertReason: data.alertReason,
                ),

                const SizedBox(height: 20),

                Row(
                  mainAxisAlignment: MainAxisAlignment.spaceBetween,
                  children: [
                    const Row(
                      children: [
                        Icon(Icons.wifi, color: Colors.green),
                        SizedBox(width: 6),
                        Text(
                          "ESP32-C3 Online",
                          style: TextStyle(
                            color: Colors.green,
                            fontWeight: FontWeight.bold,
                          ),
                        ),
                      ],
                    ),

                    Text(
                      DateTime.fromMillisecondsSinceEpoch(data.timestamp * 1000)
                          .toLocal()
                          .toString()
                          .substring(11, 19),
                      style: const TextStyle(color: Colors.grey),
                    ),
                  ],
                ),

                const SizedBox(height: 20),

                GridView.count(
                  shrinkWrap: true,
                  physics: const NeverScrollableScrollPhysics(),
                  crossAxisCount: 2,
                  crossAxisSpacing: 15,
                  mainAxisSpacing: 15,

                  children: [
                    SensorCard(
                      title: "TEMP",
                      value: data.temperature.toStringAsFixed(1),
                      unit: "°C",
                      icon: Icons.thermostat,
                      color: Colors.red,
                    ),

                    SensorCard(
                      title: "HUMID",
                      value: data.humidity.toStringAsFixed(1),
                      unit: "%",
                      icon: Icons.water_drop,
                      color: Colors.blue,
                    ),

                    SensorCard(
                      title: "PM2.5",
                      value: data.pm25.toStringAsFixed(3),
                      unit: "mg/m³",
                      icon: Icons.air,
                      color: Colors.purple,
                    ),

                    SensorCard(
                      title: "GAS",
                      value: data.gas.toStringAsFixed(1),
                      unit: "kΩ",
                      icon: Icons.cloud,
                      color: Colors.green,
                    ),
                  ],
                ),

                const SizedBox(height: 20),

                Container(
                  padding: const EdgeInsets.all(18),

                  decoration: BoxDecoration(
                    color: Colors.white,
                    borderRadius: BorderRadius.circular(20),
                  ),

                  child: Row(
                    mainAxisAlignment: MainAxisAlignment.spaceAround,
                    children: [
                      Text(
                        "⚡ ${data.voltage.toStringAsFixed(2)}V",
                        style: const TextStyle(
                          fontSize: 16,
                          fontWeight: FontWeight.bold,
                        ),
                      ),

                      Text(
                        "🔋 ${data.current.toStringAsFixed(0)}mA",
                        style: const TextStyle(
                          fontSize: 16,
                          fontWeight: FontWeight.bold,
                        ),
                      ),
                    ],
                  ),
                ),

                const SizedBox(height: 20),

                BatteryCard(percentage: data.battery),
              ],
            ),
          );
        },
      ),
    );
  }
}
