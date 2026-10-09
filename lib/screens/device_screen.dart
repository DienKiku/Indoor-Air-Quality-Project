import 'package:flutter/material.dart';

class DeviceScreen extends StatelessWidget {
  const DeviceScreen({super.key});

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      backgroundColor: const Color(0xffF4F7FB),

      appBar: AppBar(
        title: const Text(
          "Device",
          style: TextStyle(color: Colors.black, fontWeight: FontWeight.bold),
        ),

        centerTitle: true,

        backgroundColor: Colors.white,

        elevation: 0,
      ),

      body: Padding(
        padding: const EdgeInsets.all(18),

        child: Column(
          children: [
            DeviceCard(icon: Icons.memory, title: "ESP32-C3", value: "Online"),

            DeviceCard(icon: Icons.wifi, title: "WiFi", value: "Connected"),

            DeviceCard(
              icon: Icons.battery_full,
              title: "Battery",
              value: "75%",
            ),

            DeviceCard(
              icon: Icons.system_update,
              title: "Firmware",
              value: "v1.0.0",
            ),
          ],
        ),
      ),
    );
  }
}

class DeviceCard extends StatelessWidget {
  final IconData icon;
  final String title;
  final String value;

  const DeviceCard({
    required this.icon,

    required this.title,

    required this.value,
  });

  @override
  Widget build(BuildContext context) {
    return Container(
      margin: const EdgeInsets.only(bottom: 15),

      padding: const EdgeInsets.all(20),

      decoration: BoxDecoration(
        color: Colors.white,

        borderRadius: BorderRadius.circular(20),
      ),

      child: Row(
        children: [
          Icon(icon, color: Colors.green, size: 30),

          const SizedBox(width: 20),

          Expanded(
            child: Text(
              title,
              style: const TextStyle(fontSize: 18, fontWeight: FontWeight.bold),
            ),
          ),

          Text(value),
        ],
      ),
    );
  }
}
